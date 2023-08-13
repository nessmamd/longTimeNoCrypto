#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "BlockChain.h"
#include "Block.h" // Include the Block class definition


using namespace std;
//this should just recieve it
struct sockaddr_in* createIPv4Address(char *ip, int port);

struct AcceptedSocket{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool acceptedSuccessfully;
};
struct AcceptedSocket *acceptIncomingConnection(int serverSocketFD){
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, reinterpret_cast<sockaddr *>(&clientAddress), reinterpret_cast<socklen_t *>(&clientAddressSize));

    AcceptedSocket *acceptedSocket = new AcceptedSocket;
    acceptedSocket->address = clientAddress;
    acceptedSocket->acceptedSocketFD = clientSocketFD;
    acceptedSocket->acceptedSuccessfully = clientSocketFD > 0;

    if(!acceptedSocket->acceptedSuccessfully)
        acceptedSocket->error = clientSocketFD;

    return acceptedSocket;
}
struct sockaddr_in* createIPv4Address(char *ip, int port){
    struct sockaddr_in *address = new struct sockaddr_in;
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    if(strlen(ip) == 0)
        address->sin_addr.s_addr = INADDR_ANY;
    else
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    return address;
}

//THIS IS THE SERVER SIDE OF THINGS
int main() {
    int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in *serverAddress = createIPv4Address("127.0.0.1", 2000);
    int result = ::bind(serverSocketFD, reinterpret_cast<struct sockaddr *>(serverAddress), sizeof(*serverAddress));
    while(result != 0){
        cout << "socket was not created \n";
        int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in *serverAddress = createIPv4Address("127.0.0.1", 2000);
        int result = ::bind(serverSocketFD, reinterpret_cast<struct sockaddr *>(serverAddress), sizeof(*serverAddress));
    }
    cout << "socket was bound successfully \n";

    int listenResult = listen(serverSocketFD, 10);

    struct AcceptedSocket *clientSocket = acceptIncomingConnection(serverSocketFD);

    char buffer[50000];

    while(true){
        ssize_t amountReceived = recv(clientSocket->acceptedSocketFD, buffer, 1024, 0);

        if(amountReceived > 0){
            buffer[amountReceived] = 0;
//            cout << "Hashs sent over " << buffer;
        }

        if(amountReceived == 0)
            break;
    }

    BlockChain chain = BlockChain();
    chain.deserialize(buffer);
    cout << chain.blockChain.size();
    for(int x = 0; x < chain.blockChain.size(); x++){
        cout << "Block chain #" << x << " "<< chain.blockChain[x].getHash() << endl;
    }

    //closing the connection that you are trying to send over
    close(clientSocket->acceptedSocketFD);
    //shutting down the things we are getting
    shutdown(serverSocketFD, SHUT_RDWR);

    //allowing the user to create two more things
    char *line = NULL;
    char * ip = NULL;
    int maxVal = 0;
    size_t lineSize = 0;
    size_t okok = 0;
    cout << "You now have access to the Message BlockChain as you have recieve one\n to send one, please give us (max 2) messages (exit) as well as the \n individuals IP address" << endl;
    cout << "IP address: ";
    getline(&ip, &okok, stdin);
    while(maxVal < 2) {
        cout << "Message #" << maxVal+1 << ": ";
        ssize_t charCount = getline(&line, &lineSize, stdin);
        if (charCount > 0) {
            if(strcmp(line, "exit\n") == 0){
                break;
            }
            maxVal++;
            chain.addingBlock(line);
        }
    }

    cout << "displaying all of the blocks after addition of blocks:" << endl;
    for(int x = 0; x < chain.blockChain.size(); x++){
        cout << "Block chain #" << x << " "<< chain.blockChain[x].getHash() << endl;
    }

    int socketFD = socket(AF_INET, SOCK_STREAM, 0);

    //this allows you to recreate any socket connection
    struct sockaddr_in *address = createIPv4Address(ip, 2000);

    int connectionStatus = connect(socketFD, reinterpret_cast<const sockaddr *>(address), sizeof(*address));
    if(connectionStatus == 0){
        cout << "connection made and the coin has been send " << endl;
    }
    return 0;
}
