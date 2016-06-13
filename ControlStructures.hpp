/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  ControlStructures.hpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/21/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#ifndef ControlStructures_hpp
#define ControlStructures_hpp
#include "Tree.hpp"
#include "Object.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <map>
using namespace std;
class ControlStructures{
private:
    map<int,vector<Object> > delta;
    queue<node*> pendingdelta;
    int deltano,delta_count;
public:
    ControlStructures();
    void genControlStructures(node *root);
    void preorder(node *root,vector<Object> &currentdelta);
    void display();
    map<int,vector<Object> > getCS();
};
#endif /* ControlStructures_hpp */
