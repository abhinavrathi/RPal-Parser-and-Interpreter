/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  Tree.cpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/17/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#include "Tree.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
// Initialization
void Tree::initiate(){
    pos=-1;
}
// Builds the Stack
void Tree::build_tree(string data,int num){
    node *temp=new node();
    temp->value=data;
    temp->child=NULL;
    temp->sibling=NULL;
    if(num==0){
        stack.push_back(temp);
        pos++;
    }
    else{
        node *a,*b;
        if(pos==-1){
            cout<<"\nStack Empty Error : ";
            cout<<data;
            exit(1);
        }
        a=stack.back();
        stack.pop_back();
        --pos;
        --num;
        while(num!=0){
            if(pos==-1){
                cout<<"\nStack Empty Error : \n";
                cout<<data;
                exit(1);
            }
            b=stack.back();
            stack.pop_back();
            --pos;
            --num;
            b->sibling=a;
            a=b;
        }
        temp->child=a;
        stack.push_back(temp);
        pos++;
    }
}
// Traverse the tree as the last element left on stack after Parsing
void Tree::preorder(){
    traverse(stack[0],0);
}
// Traverses the tree in pre order
void Tree::traverse(node *root,int n){
    if(root){
        for(int i=0;i<n;++i)
            cout<<".";
        cout<<root->value<<"\n";
        traverse(root->child,n+1);
        traverse(root->sibling,n);
    }
}