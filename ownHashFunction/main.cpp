#include <iostream>
#include <string>
#include "BlockChain.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

struct sockaddr_in* createIPv4Address(char *ip, int port);

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


int main() {
    //createTCPIpv4Socket();
    BlockChain chain = BlockChain();
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);

    //this allows you to recreate any socket connection
    struct sockaddr_in *address = createIPv4Address("127.0.0.1", 2000);

    int result = connect(socketFD, reinterpret_cast<const sockaddr *>(address), sizeof(*address));
    cout << "\nstatus of connection: \n " << result;
    if(result != 0){
        cout << "no connection made.\n";
        return 0;
    }

    char *line = NULL;
    size_t lineSize = 0;
    cout << "Type the message you would like to send, any length. You have a max of two messages, if you dont want to send a second message (exit)\n";


    int maxVal = 0;
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

    string blockChainValues = chain.serialize();
    cout << "Here we are deserialzing it after it has been serialized\n";
    chain.deserialize(const_cast<char *>(blockChainValues.c_str()));
    cout << "The total size of everything" << chain.blockChain.size() << "\n";
    int sizeOfItAll = blockChainValues.size();
    ssize_t amountSent = send(socketFD, blockChainValues.c_str(), sizeOfItAll, 0);

    close(socketFD);

    return 0;
}
