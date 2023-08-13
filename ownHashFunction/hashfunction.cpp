//
// Created by Nessma Mohdy on 2023-07-31.
//

#include <string>
#include <iostream>
#include <typeinfo>
#include <cmath>
#include <algorithm>
#include <random>
#include <sstream>
#include "hashfunction.h"
#include "sha256modif.h"


using namespace std;

hashfunction::hashfunction(std::string userinput) {
    secreteMessage = userinput;
    //fix the place of the block for now
    placeOfBlock = 0;
    numberNonce = -1;
    nDifficulty = 6;
    timeCreated = time(nullptr);
    processingMessage();
}

void hashfunction::processingMessage(){
    //creating the variables
    int totalSize;
    char *pointing;

    //doing the cleaning
    totalSize = secreteMessage.length();
    secreteMessage.erase(std::remove_if(secreteMessage.begin(), secreteMessage.end(), ::isspace), secreteMessage.end());

    //creating the allocation
    char* charArray = new char[secreteMessage.length() + 1];
    pointing = charArray;
    std::strcpy(charArray, secreteMessage.c_str());

    //creating the sections
    mo3 = std::round(totalSize/3);
    for (int i = 1; i <= mo3; i++) {
        std::string newString(pointing, 3);

        for (char& letter : newString) {
            if (letter == '\0') {
                letter = 'a';
            }
        }
        sectors.push_back(newString);
        pointing += 3;
    }

    for(int y = 0; y <= 25; y++) {
        hillCipher[char(97 + y)] = y;
    }

    //creating the key that will be used for that time
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 25);
    for (int p = 0; p < 3; p++) {
        for (int q = 0; q < 3; q++) {
            mainKey[p][q] = distribution(gen);
        }
    }
    encryptingMessage();
}

void hashfunction::encryptingMessage(){
    int mat[mo3][3];
    for(int l = 0; l < mo3; l++){
        std::string reference = sectors[l];
        for(int p = 0; p < 3; p++){
            mat[l][p] = hillCipher[reference[p]];
        }
    }

    for(int x = 0; x < mo3; x++){
        for(int z = 0; z<3; z++){
            int sumOk = 0;
            for(int p = 0; p<3; p++){
                sumOk += ((mainKey[z][p]*mat[x][p]) % 26);
            }
            changedMessage += std::to_string(sumOk);
        }
    }
    //calling the proof of work that is done
    mineBlock();
}

void hashfunction::mineBlock(){
    //proof of work is that the first (diff) have to be divisble by 2
    numberNonce++;
    finalHash = creatingHash();
    int x = 1;
    while( x <= nDifficulty){
        int index = x - 1;
        if(!(std::isdigit(finalHash[index]))) {
            numberNonce++;
            finalHash = creatingHash();
            x = 1;
            continue;
        }

        if((finalHash[index] - '0') % 2 != 0){
            numberNonce++;
            finalHash = creatingHash();
            x = 1;
            continue;
        }
        x++;
    }
    //attach to finalHash at the end the message to be deciphered
    finalHash = finalHash + changedMessage;
    cout << "Block mined: " << finalHash << endl;
}

string hashfunction::creatingHash() {
    stringstream addedElements;

    addedElements << placeOfBlock << numberNonce << timeCreated;
    return sha256(addedElements.str());
}

string hashfunction::revMerckleValue() const{
    return finalHash.substr(0,2);
}