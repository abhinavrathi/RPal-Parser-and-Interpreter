/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  Parser.hpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/17/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

/*
 Reads token by token by Calling the "Scanner Class" repeatedly.
 Parses the Grammar as per production rules defined, and builds the Abstract Syntax Tree by subsequent calls to the member funcition of "Tree" Class.
*/

#ifndef Parser_hpp
#define Parser_hpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include "Tree.hpp"
#include "Scanner.hpp"
using namespace std;
class Parser{
private:
    string NT;          // To store next token
    Tree tree;          // To build tree
    Scanner oo;         // To Scan input from file
public:
    void set(string x);
    string next();
    void Read(string a);
    void buildtree(string value,int n);
    Tree gettree();
    // Following functions relate to Grammar of RPAL
    void E();
    void Ew();
    void T();
    void Ta();
    void Tc();
    void B();
    void Bt();
    void Bs();
    void Bp();
    void A();
    void At();
    void Af();
    void Ap();
    void R();
    void Rn();
    void D();
    void Da();
    void Dr();
    void Db();
    void Vb();
    void Vl();
};
#endif /* Parser_hpp */
