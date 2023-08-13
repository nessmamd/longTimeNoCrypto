//
// Created by Nessma Mohdy on 2023-08-07.
//

#include <string>
#include "node.h"
using namespace std;

node::node(){
    left = " ";
    merckle = "";
    right = " ";
}
node::node(string currMer){
    left = " ";
    merckle = currMer;
    right = " ";
}

void node::setLeft(string leftMer){
    left = leftMer;
}

void node::setRight(string rightMer){
    right = rightMer;
}

string node::getLeft(){
    return left;
}

string node::getRight(){
    return right;
}

string node::getMerck(){
    return merckle;
}


