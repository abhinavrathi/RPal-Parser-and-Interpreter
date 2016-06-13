/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  Object.hpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/23/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
class Object{
public:
    string type,name,lambdavar;
    int lambdano,lambdaenv,envno,thenno,elseno,tauno;
    bool isTuple;
    vector<Object> tuple;
public:
    Object();
    Object(string t,string n);
    Object(string t,string lambda, int lamda_no);
    Object(string t,int env_no);
    Object(string t,int then_no,int else_no);
};
#endif /* Object_hpp */
