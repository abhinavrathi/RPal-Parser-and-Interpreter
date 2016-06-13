/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  Object.cpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/23/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#include "Object.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
Object::Object(){
    isTuple=false;
    tuple=vector<Object>();
    type=name=lambdavar="";
    lambdano=lambdaenv=envno=thenno=elseno=tauno=-1;
};
Object::Object(string t,string n){
    type=t;
    name=n;
    isTuple=false;
    tuple=vector<Object>();
    lambdavar="";
    lambdano=lambdaenv=envno=thenno=elseno=tauno=-1;
};
Object::Object(string t,string lambda, int lambda_no){
    type=t;
    lambdavar=lambda;
    lambdano=lambda_no;
    isTuple=false;
    tuple=vector<Object>();
    name="";
    lambdaenv=envno=thenno=elseno=tauno=-1;
};
Object::Object(string t,int env_no){
    type=t;
    envno=env_no;
    isTuple=false;
    tuple=vector<Object>();
    name=lambdavar="";
    lambdano=lambdaenv=thenno=elseno=tauno=-1;
};
Object::Object(string t,int then_no,int else_no){
    type=t;
    thenno=then_no;
    elseno=else_no;
    isTuple=false;
    tuple=vector<Object>();
    name=lambdavar="";
    lambdano=lambdaenv=envno=tauno=-1;
};