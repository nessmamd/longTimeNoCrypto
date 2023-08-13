//
// Created by Nessma Mohdy on 2023-08-04.
//
#include <string>
#include "hashfunction.h"
#include "Block.h"
#include "BlockChain.h"

using namespace std;

Block::Block(string inputOfUser, int LinkSize, string prevHash){

    blockSize = 0;
    message = inputOfUser;
    blockSize += sizeof(message);
    chainNumber = LinkSize;
    blockSize += sizeof(chainNumber);
    sPrevHash = prevHash;
    blockSize += sizeof(sPrevHash);

    MineBlock();

}
void Block::MineBlock(){
    hashfunction hashObj(message);
    cout << "we've entered this";
    BlockHeader = hashObj.finalHash;
    cout << "Block header\n" << BlockHeader;
    blockSize += sizeof(BlockHeader);
    merckleValue = BlockHeader.substr(0,1);
    cout << "Merckle Value: " << merckleValue << "\n";
    blockSize += sizeof(merckleValue);
    cout << "The block size: " << blockSize << "\n";
}

Block::Block(string hashValue, string prevHash, int currSize){
    chainNumber = currSize;
    blockSize += sizeof(chainNumber);
    sPrevHash = prevHash;
    blockSize += sizeof(sPrevHash);
    BlockHeader = hashValue;
    blockSize += sizeof(BlockHeader);
}

string Block::getHash() const{
    return BlockHeader;
}

string Block::getMerckle() const {
    return merckleValue;
}

string Block::serialize() {
    std::string serializedData;

    serializedData.append(reinterpret_cast<const char*>(&blockSize), sizeof(int));

    int strSize = BlockHeader.length();
    serializedData.append(reinterpret_cast<const char*>(&strSize), sizeof(int));
    serializedData.append(BlockHeader);

    int merV = merckleValue.length();
    serializedData.append(reinterpret_cast<const char*>(&merV), sizeof(int));
    serializedData.append(merckleValue);


    return serializedData;
}

void Block::deserialize(const char *data, size_t size) {
    // Use pointers to extract data from the byte stream
    const char *ptr = data;

    memcpy(&blockSize, ptr, sizeof(int));
    ptr += sizeof(int);

    int headerSize;
    memcpy(&headerSize, ptr, sizeof(int));
    ptr += sizeof(int);

    BlockHeader.resize(headerSize);
    memcpy(&BlockHeader[0], ptr, headerSize);
    ptr += headerSize;

    int merkleSize;
    memcpy(&merkleSize, ptr, sizeof(int));
    ptr += sizeof(int);

    merckleValue.resize(merkleSize);
    memcpy(&merckleValue[0], ptr, merkleSize);
    ptr += merkleSize;

}

