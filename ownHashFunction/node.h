//
// Created by Nessma Mohdy on 2023-08-07.
//

#ifndef OWNHASHFUNCTION_NODE_H
#define OWNHASHFUNCTION_NODE_H

#include <string>
using namespace std;

class node{
public:
    node();
    std::string left;
    std::string merckle;
    std::string right;
    node(string currMer);
    void setLeft(string leftMer);
    void setRight(string rightMer);
    string getLeft();
    string getRight();
    string getMerck();
};
#endif //OWNHASHFUNCTION_NODE_H
