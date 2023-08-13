//
// Created by Nessma Mohdy on 2023-08-07.
//

#include "mRoot.h"

using namespace std;

mRoot::mRoot(){
    root = "0";
    node rooT = node();
    totalNodes += 1;
    values.push_back(rooT);

}

void mRoot::addingMerckle(string merckleValue){
    node currNode = node(merckleValue);
    totalNodes += 1;
    //do a while loop, till you reach the top and make the adjustments each time until everything that needs to be replaced is replaced
    if(totalNodes % 2 == 0){

    //make adjustments here to the rooT part
    }
    values.push_back(currNode);
}