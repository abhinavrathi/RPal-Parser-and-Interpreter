/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  CSEMachine.hpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/23/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#ifndef CSEMachine_hpp
#define CSEMachine_hpp
#include "Object.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <map>
#include <queue>
#include <stack>
using namespace std;
typedef map<string,Object> envMap;
typedef pair<int,string> keyPair;
class CSEMachine {
public:
    CSEMachine(){};
    CSEMachine(map<int,vector<Object> > d);
    void evaluateControlStructures();
    string convert_int_to_string(int i);
    string remove_escape_characters(const string& s);
private:
    map<int,vector<Object> > deltaMap;
    map<keyPair,Object> paramMap;
    map<int,int> envMap;
    stack<int> envStack;
    int deltaCounter,currDeltaNum,env_count,currEnv;
    bool print_call;
};
#endif /* CSEMachine_hpp */
