/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  Tree.hpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/17/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
// Following structure determines the type of node used for the Stack used in building AST
struct node{
    string value;
    node *child;
    node *sibling;
    node(){
        value="";
        child=NULL;
        sibling=NULL;
    }
};
class Tree{
private:
    int pos;
public: vector<node*> stack;    // Vector of type node used as a stack
    void initiate();
    void build_tree(string data,int num);
    void preorder();
    void traverse(node *root,int n);
};
#endif /* Tree_hpp */