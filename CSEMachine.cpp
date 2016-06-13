/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  CSEMachine.cpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/23/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#include "CSEMachine.hpp"
#include "Object.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cmath>
#include <sstream>
typedef pair<int,string> key_pair;
CSEMachine::CSEMachine(map<int,vector<Object> >d){
    deltaMap=d;
    deltaCounter=0;
    currDeltaNum=0;
    env_count=0;
    envStack.push(0);
    currEnv=0;
    envMap=map<int,int>();
    print_call=false;
};
void CSEMachine::evaluateControlStructures(){
    // Code removed
};
string CSEMachine::convert_int_to_string(int i){
    // Code removed
};
string CSEMachine::remove_escape_characters(const string& s){
    // Code removed
};
