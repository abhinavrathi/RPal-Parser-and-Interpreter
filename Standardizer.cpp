/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  Standardizer.cpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/18/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#include "Standardizer.hpp"
#include "Tree.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
node* Standardizer::standardize(node *root){
    if(root){
        if(root->child!=NULL){
            node *childNode=root->child;
            while(childNode!=NULL){
                standardize(childNode);
                childNode = childNode->sibling;
            }
        }
        //standardize(root->child);
        //standardize(root->sibling);
        node *temp=NULL;
        if(root->value=="let"){
            if(root->child->value=="="){
                temp=root->child->sibling;
                root->child->sibling=root->child->child->sibling;
                root->child->child->sibling=temp;
                root->value="gamma";
                root->child->value="lambda";
            }
        }
        else if(root->value=="where"){
            temp=root->child;
            root->child=temp->sibling;
            root->child->sibling=temp->sibling->child->sibling;
            root->child->child->sibling=temp;
            root->child->child->sibling->sibling=NULL;
            root->value="gamma";
            root->child->value="lambda";
        }
        else if(root->value=="within"){
            temp=new node();
            temp->value="gamma";
            temp->child=new node();
            temp->child->value="lambda";
            temp->child->sibling=root->child->child->sibling;
            root->child->child->sibling=NULL;
            temp->child->child=root->child->child;
            temp->child->child->sibling=root->child->sibling->child->sibling;
            root->child->sibling->child->sibling=NULL;
            root->child=root->child->sibling->child;
            root->child->sibling=temp;
            root->value="=";
        }
        else if(root->value=="function_form"){
            temp=root->child->sibling;
            root->child->sibling=new node();
            root->child->sibling->value="lambda";
            root->child->sibling->child=temp;
            while(temp->sibling->sibling!=NULL){
                node *temp1=temp->sibling;
                temp->sibling=new node();
                temp=temp->sibling;
                temp->value="lambda";
                temp->child=temp1;
                temp=temp->child;
            }
            root->value="=";
        }
        else if(root->value=="lambda"&&root->child->value==","){
            
        }
        else if(root->value=="lambda"){
             temp=root;
             temp=temp->child;
             while(temp->sibling->sibling!=NULL){
                 node *temp1=temp->sibling;
                 temp->sibling=new node();
                 temp=temp->sibling;
                 temp->value="lambda";
                 temp->child=temp1;
                 temp=temp->child;
             }
        }
        else if(root->value=="rec"){
            temp=new node();
            temp->value="lambda";
            temp->child=(node*)malloc(sizeof(node));
            memcpy(temp->child,root->child->child,sizeof(node));
            node *temp1=new node();
            temp1->value="gamma";
            temp1->child=new node();
            temp1->child->value="<Y*>";
            temp1->child->sibling=temp;
            root->child=root->child->child;
            root->child->sibling=temp1;
            root->value="=";
        }
        else if(root->value=="and"){
            node *temp1=new node;
            node *temp2=new node;
            temp1->value=",";
            temp2->value="tau";
            temp=root->child;
            temp2->child=temp->child->sibling;
            temp->child->sibling=NULL;
            temp1->child=temp->child;
            node *it1,*it2;
            it1=temp1->child;
            it2=temp2->child;
            temp=temp->sibling;
            while(temp!=NULL){
                it2->sibling=temp->child->sibling;
                temp->child->sibling=NULL;
                it1->sibling=temp->child;
                temp=temp->sibling;
                it1=it1->sibling;
                it2=it2->sibling;
            }
            root->child=temp1;
            root->child->sibling=temp2;
            root->value="=";
        }
        else if(root->value=="@"){
            temp=new node();
            temp->value="gamma";
            temp->sibling=root->child->sibling->sibling;
            temp->child=root->child->sibling;
            temp->child->sibling=root->child;
            temp->child->sibling->sibling=NULL;
            root->child=temp;
            root->value="gamma";
        }
    }
    return root;
};