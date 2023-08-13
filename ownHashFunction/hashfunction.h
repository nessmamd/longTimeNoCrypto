//
// Created by Nessma Mohdy on 2023-07-31.
//

#ifndef OWNHASHFUNCTION_HASHFUNCTION_H
#define OWNHASHFUNCTION_HASHFUNCTION_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class hashfunction{
public:
    //Block Prev Hash Value;
    std::string finalHash;
    hashfunction(std::string userinput);
    std::vector<std::string> sectors;
    map<char, int>hillCipher;
    string revMerckleValue() const;

private:
    std::string secreteMessage;
    void processingMessage();
    void encryptingMessage();
    void mineBlock();
    std::string creatingHash();
    //need to remove this and add it to the BlockChain
    int nDifficulty;
    int mainKey[3][3];
    std::string changedMessage;
    uint32_t placeOfBlock;
    int64_t numberNonce;
    time_t timeCreated;
    int mo3;
};
#endif //OWNHASHFUNCTION_HASHFUNCTION_H
