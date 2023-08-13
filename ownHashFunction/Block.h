//
// Created by Nessma Mohdy on 2023-08-04.
//

#ifndef OWNHASHFUNCTION_BLOCK_H
#define OWNHASHFUNCTION_BLOCK_H
#include <string>
#include "hashfunction.h"

using namespace std;

class Block{
public:
    //the constructor calls the hash function so dw
    Block(string inputOfUser, int LinkSize, string prevHash);
    //the mining creates the call to the constructor
    void MineBlock();
    [[nodiscard]] string getHash() const;
    [[nodiscard]] string getMerckle() const;
    void deserialize(const char *data, size_t size);
    string serialize();
    Block(string hashValue, string prevHash, int currSize);


protected:
    //blockheader is the same as the hash
    string BlockHeader;
    string sPrevHash;
private:
    //you get the merckleValue from the blockchain everytime an instance is made
    string merckleValue;
    string IP_Address;
    string message;
    int chainNumber;
    int blockSize;


};

#endif //OWNHASHFUNCTION_BLOCK_H
