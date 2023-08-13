//
// Created by Nessma Mohdy on 2023-08-04.
//
#include "BlockChain.h"
#include "Block.h"
#include "mRoot.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <string>
using namespace std;

BlockChain::BlockChain(){
    //in your main you call on the constructor and just go from there
    LinkSize = 1;
    Block starter = Block("Welcome to the world of mesByte", LinkSize, "0");
    blockChain.push_back(starter);

}


string BlockChain::serialize(){
    string theLink;

    for(int x = 0; x < blockChain.size(); x++){
        theLink.append(blockChain[x].getHash());
        theLink.append("\n");
    }

    return theLink;
}

void BlockChain::deserialize(char* SeralizedValue) {
    std::vector<std::string> HashValue;
    std::istringstream iss(SeralizedValue);
    std::string segment;

    while (std::getline(iss, segment, '\n')) {
        HashValue.push_back(segment);
    }

    if(blockChain.size() == 0){
        BlockChain();
        //then add to it
        for(int x = 0; x < HashValue.size(); x++){
            string prev = blockChain[x].getHash();
            Block add = Block(HashValue[x],prev,(x+1));
            blockChain.push_back(add);
        }

    }
    else{
        int sizeOf = blockChain.size();
        for(int x = sizeOf; x < (sizeOf + HashValue.size()); x++){
            string prev = blockChain[x].getHash();
            Block add = Block(HashValue[x], prev, (x+1));
            blockChain.push_back(add);
        }
    }
}



void BlockChain::addingBlock(std::string userinput){
    //should we do some verification?
    LinkSize += 1;
    Block * lastBlock = getLastBlock();
    string lastHash= lastBlock->getHash();
    Block newBlock = Block(userinput, LinkSize, lastHash);
    blockChain.push_back(newBlock);
    roots.addingMerckle(newBlock.getMerckle());
}

Block* BlockChain::getLastBlock() {
    if (blockChain.empty()) {
        // Return a nullptr or handle the error appropriately
        return nullptr;
    }

    return &blockChain.back();
}

Block BlockChain::getFirstBlock(){
    if (blockChain.empty()) {
        // Return a dummy block or handle the error appropriately
        return Block("", 0, "");
    }
    return blockChain[0];
}
