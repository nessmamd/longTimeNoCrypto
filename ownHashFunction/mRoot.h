//
// Created by Nessma Mohdy on 2023-08-07.
//

#ifndef OWNHASHFUNCTION_MROOT_H
#define OWNHASHFUNCTION_MROOT_H
#include <string>
#include <vector>
#include "node.h"

using namespace std;

class mRoot{
public:
    string root;
    int totalNodes;
    mRoot();
    void addingMerckle(string merckleValue);
private:
    vector<node> values;
};
#endif //OWNHASHFUNCTION_MROOT_H
