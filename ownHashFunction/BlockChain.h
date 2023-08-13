//
// Created by Nessma Mohdy on 2023-08-03.
//

#ifndef OWNHASHFUNCTION_BLOCKCHAIN_H
#define OWNHASHFUNCTION_BLOCKCHAIN_H
#include <vector>
#include <string>
#include "Block.h"
#include "mRoot.h"

using namespace std;

class BlockChain{
public:
    int nDifficulty;
    int LinkSize;
    vector<Block> blockChain;
    void addingBlock(std::string userinput);
    BlockChain();
    Block * getLastBlock();
    Block getFirstBlock();
    mRoot roots = mRoot();
    string serialize();
    void deserialize(char* SeralizedValue);


private:
    vector<string> merkleTree;

};
#endif //OWNHASHFUNCTION_BLOCKCHAIN_H
