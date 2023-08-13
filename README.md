# longTimeNoCrypto

Hello welcome to the repo of Long Time No.... which is a cryptocurrency that is made by messages you wish you sent to others. This crypto cant be bought but only recieved from an indivdual that wishes they could tell you said secrete message. 

To watch a quick run through: https://www.youtube.com/watch?v=fZaP-H-yOZc&ab_channel=Nessma
**note the hashs show on the users device only for the sake of demonstration. 

CRYPTO OPERATION
In hashfunction.h/.cpp and sha25modif.h/.cpp are the files that contain the creation of the hash. 
- A user input aka the secret message is covered by using Hill cipher - a polygraphic substitution cipher based on linear algebra to hide the message.
- That user input is sent over to the known cryptographic hash (SHA256 w/ slight modification) to create the final hash

The rest of the files are for the creation of the BlockChain entity and all respective Blocks.

SOCKET OPERATION
- the main file in the folder is for the client side
- the main server file outside of the folder is for the server side (note for the server to turn into a P2P system the device you are sending it to must be turned into a server)
  
INSTRUCTIONS
1. replace the main file in the folder with the main server file. To ensure that the connection is made run said command: 
<img width="843" alt="Screen Shot 2023-08-13 at 1 02 10 AM" src="https://github.com/nessmamd/longTimeNoCrypto/assets/113803210/ad389aec-ccec-4225-b09a-409415e96e2b">
2. replace the main file back into the folder and send over all the required messages
3. once sent, go back to the server run and send it to the next individual 
