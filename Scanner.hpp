/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  Scanner.hpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/17/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

/* Scans the input file, and returns single token on each call to function tokenize() */

#ifndef testScanner_hpp
#define testScanner_hpp
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
class Scanner{
private:string filename;
    fstream ifs;
    char ch,next;
public:
    void set(string x);
    string tokenize();
    void close();
    string read(string x);
};

#endif /* Scanner_hpp */
