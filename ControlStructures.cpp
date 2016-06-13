/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  ControlStructures.cpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/21/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#include "ControlStructures.hpp"
#include "Object.hpp"
#include "Tree.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
ControlStructures::ControlStructures(){
    deltano=0;
    delta_count=0;
}
void ControlStructures::genControlStructures(node *root){
    pendingdelta.push(root);
    while(!pendingdelta.empty()){
        vector<Object> currentdelta;
        node* current=pendingdelta.front();
        pendingdelta.pop();
        preorder(current,currentdelta);
        delta[deltano++]=currentdelta;
    }
};
void ControlStructures::preorder(node *root,vector<Object> &currentdelta){
    if(root->value=="lambda"){
        if(root->child->value!=","){
            string name="";
            if(root->child->value.substr(0,3)=="<ID"){
                name=root->child->value.substr(4,root->child->value.length()-5);
            }
            Object lambdaclosure("lambdaClosure",name,++delta_count);
            currentdelta.push_back(lambdaclosure);
        }
        else{
            node* commachild=root->child->child;
            string tuple="";
            while(commachild!= NULL){
                string name="";
                if(commachild->value.substr(0,3)=="<ID"){
                    name=commachild->value.substr(4,commachild->value.length()-5);
                }
                tuple+=name+",";
                commachild=commachild->sibling;
            }
            Object lambdaclosure("lambdaClosure",tuple,++delta_count);
            lambdaclosure.isTuple=true;
            currentdelta.push_back(lambdaclosure);
        }
        pendingdelta.push(root->child->sibling);
        if(root->sibling!=NULL)
            preorder(root->sibling,currentdelta);
    }
    else if(root->value=="->"){
        Object betaObject("beta",delta_count+1,delta_count+2);
        currentdelta.push_back(betaObject);
        pendingdelta.push(root->child->sibling);
        node *temp=(node*)malloc(sizeof(node));
        memcpy(temp,root->child->sibling->sibling,sizeof(node));
        pendingdelta.push(temp);
        root->child->sibling->sibling=NULL;
        root->child->sibling=NULL;
        delta_count+=2;
        if(root->child!= NULL)
            preorder(root->child,currentdelta);
        if(root->sibling!=NULL)
            preorder(root->sibling,currentdelta);
    }
    else if(root->value=="tau"){
        string name="tau";
        string type="tau";
        int n=0;
        node *temp=root->child;
        while(temp!=NULL){
            ++n;
            temp=temp->sibling;
        }
        Object t=Object(type,name);
        t.tauno=n;
        currentdelta.push_back(t);
        if(root->child!= NULL)
            preorder(root->child,currentdelta);
        if(root->sibling!=NULL)
            preorder(root->sibling,currentdelta);
    }
    else{
        string type="";
        string name="";
        if(root->value.substr(0,3)=="<ID"){
            type="IDENTIFIER";
            name=root->value.substr(4,root->value.length()-5);
        }
        else if(root->value.substr(0,4)=="<STR"){
            type="STRING";
            name=root->value.substr(5,root->value.length()-6);
        }
        else if(root->value.substr(0,4)=="<INT"){
            type="INTEGER";
            name=root->value.substr(5,root->value.length()-6);
        }
        else if(root->value=="gamma"){
            type="gamma";
            name="gamma";
        }
        else if(root->value=="<Y*>"){
            type="Y*";
            name="Y*";
        }
        else if(root->value=="<true>"){
            type="true";
            name="true";
        }
        else if(root->value=="<false>"){
            type="false";
            name="false";
        }
        else if(root->value=="not"){
            type="not";
            name="not";
        }
        else if(root->value=="neg"){
            type="neg";
            name="neg";
        }
        else if(root->value=="<nil>"){
            type="nil";
            name="nil";
        }
        else if(root->value=="<dummy>"){
            type="dummy";
            name="dummy";
        }
        else if(root->value=="let"||root->value=="in"||root->value=="fn"||root->value=="where"||root->value=="aug"||root->value=="nil"||root->value=="dummy"||root->value=="within"||root->value=="and"||root->value=="rec"||root->value=="list"){
            type="KEYWORD";
            name=root->value;
        }
        else{
            type="OPERATOR";
            name=root->value;
        }
        Object t=Object(type,name);
        currentdelta.push_back(t);
        if(root->child!= NULL)
            preorder(root->child,currentdelta);
        if(root->sibling!=NULL)
            preorder(root->sibling,currentdelta);
    }
};
void ControlStructures::display(){
    for(int i=0;i<=delta_count;++i){
        cout<<"Delta "<<i<<": ";
        for(int j=0;j<delta[i].size();++j){
            //cout<<delta[i][j].type<<" : "<<delta[i][j].name<<",";
            cout<<"\n"<<delta[i][j].name<<","<<delta[i][j].type<<","<<delta[i][j].lambdaenv<<","<<delta[i][j].lambdano<<","<<delta[i][j].lambdavar<<","<<delta[i][j].envno<<","<<delta[i][j].thenno<<","<<delta[i][j].elseno<<","<<delta[i][j].tauno<<","<<delta[i][j].isTuple;
        }
        cout<<"\n";
    }
};
map<int,vector<Object> > ControlStructures::getCS(){
    return delta;
};