/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  Parser.cpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/17/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

/*
 Reads token by token by Calling the "Scanner Class" repeatedly.
 Parses the Grammar as per production rules defined, and builds the Abstract Syntax Tree by subsequent calls to the member funcition of "Tree" Class.
*/

#include "Parser.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
void Parser::set(string x){
    oo.set(x);          // Set filename to Scanner
    tree.initiate();    // Initialize Tree
    NT=oo.tokenize();   // Get 1st token
}
string Parser::next(){
    NT=oo.tokenize();   //Get Next Token
    return NT;
}
void Parser::Read(string a){
    if(NT.compare(a)==0||(a.compare("ID")==0&&NT.substr(1,2).compare(a)==0)||(a.compare("INT")==0&&NT.substr(1,3).compare(a)==0)||(a.compare("STR")==0&&NT.substr(1,3).compare(a)==0)){
        if(a=="ID"||a=="INT"||a=="STR"){
            buildtree(NT,0);
        }
        NT=next();
    }
    else{
        cout<<"Read Error : Expected "<<a<<", but found "<<NT<<"\n";
        exit(1);
    }
}
void Parser::buildtree(string value,int n){ //Build Tree with "value" and n nodes
    tree.build_tree(value,n);
}
Tree Parser::gettree(){ //Returns tree built
    return tree;
}
// Following functions relate to Grammar of RPAL
void Parser::E(){
    if(NT.compare("let")==0){
        Read("let");
        D();
        Read("in");
        E();
        buildtree("let",2);
    }
    else if(NT.compare("fn")==0){
        Read("fn");
        int n=0;
        do{
            Vb();
            ++n;
        }while(NT.compare("(")==0||NT.substr(1,2).compare("ID")==0);
        Read(".");
        E();
        buildtree("lambda",n+1);
    }
    else
        Ew();
}
void Parser::Ew(){
    T();
    if(NT.compare("where")==0){
        Read("where");
        Dr();
        buildtree("where",2);
    }
}
void Parser::T(){
    Ta();
    int n=0;
    while(NT.compare(",")==0){
        Read(",");
        Ta();
        ++n;
    }
    if(n>0)
        buildtree("tau",n+1);
}
void Parser::Ta(){
    Tc();
    while(NT.compare("aug")==0){
        Read("aug");
        Tc();
        buildtree("aug",2);
    }
}
void Parser::Tc(){
    B();
    if(NT.compare("->")==0){
        Read("->");
        Tc();
        Read("|");
        Tc();
        buildtree("->",3);
    }
}
void Parser::B(){
    Bt();
    while(NT.compare("or")==0){
        Read("or");
        Bt();
        buildtree("or",2);
    }
}
void Parser::Bt(){
    Bs();
    while(NT.compare("&")==0){
        Read("&");
        Bs();
        buildtree("&",2);
    }
}
void Parser::Bs(){
    if(NT.compare("not")==0){
        Read("not");
        Bp();
        buildtree("not",1);
    }
    else
        Bp();
}
void Parser::Bp(){
    A();
    if(NT.compare("gr")==0){
        Read("gr");
        A();
        buildtree("gr",2);
    }
    else if(NT.compare(">")==0){
        Read(">");
        A();
        buildtree("gr",2);
    }
    else if(NT.compare("ge")==0){
        Read("ge");
        A();
        buildtree("ge",2);
    }
    else if(NT.compare(">=")==0){
        Read(">=");
        A();
        buildtree("ge",2);
    }
    else if(NT.compare("ls")==0){
        Read("ls");
        A();
        buildtree("ls",2);
    }
    else if(NT.compare("<")==0){
        Read("<");
        A();
        buildtree("ls",2);
    }
    else if(NT.compare("le")==0){
        Read("le");
        A();
        buildtree("le",2);
    }
    else if(NT.compare("<=")==0){
        Read("<=");
        A();
        buildtree("le",2);
    }
    else if(NT.compare("eq")==0){
        Read("eq");
        A();
        buildtree("eq",2);
    }
    else if(NT.compare("ne")==0){
        Read("ne");
        A();
        buildtree("ne",2);
    }
}
void Parser::A(){
    if(NT.compare("+")==0){
        Read("+");
        At();
    }
    else if(NT.compare("-")==0){
        Read("-");
        At();
        buildtree("neg",1);
    }
    else
        At();
    while(NT.compare("+")==0||NT.compare("-")==0){
        if(NT.compare("+")==0){
            Read("+");
            At();
            buildtree("+",2);
        }
        else if(NT.compare("-")==0){
            Read("-");
            At();
            buildtree("-",2);
        }
    }
}
void Parser::At(){
    Af();
    while(NT.compare("*")==0||NT.compare("/")==0){
        if(NT.compare("*")==0){
            Read("*");
            Af();
            buildtree("*",2);
        }
        else if(NT.compare("/")==0){
            Read("/");
            Af();
            buildtree("/",2);
        }
    }
}
void Parser::Af(){
    Ap();
    if(NT.compare("**")==0){
        Read("**");
        Af();
        buildtree("**",2);
    }
}
void Parser::Ap(){
    R();
    while(NT.compare("@")==0){
        Read("@");
        Read("ID");
        R();
        buildtree("@",3);
    }
}
void Parser::R(){
    Rn();
    while(NT!=""&&(NT.substr(1,2).compare("ID")==0||NT.substr(1,3).compare("INT")==0||NT.substr(1,3).compare("STR")==0||NT.compare("true")==0||NT.compare("false")==0||NT.compare("nil")==0||NT.compare("(")==0||NT.compare("dummy")==0)){
        Rn();
        buildtree("gamma",2);
    }
}
void Parser::Rn(){
    if(NT.substr(1,2).compare("ID")==0){
        Read("ID");
    }
    else if(NT.substr(1,3).compare("INT")==0){
        Read("INT");
    }
    else if(NT.substr(1,3).compare("STR")==0){
        Read("STR");
    }
    else if(NT.compare("true")==0){
        Read("true");
        buildtree("<true>",0);
    }
    else if(NT.compare("false")==0){
        Read("false");
        buildtree("<false>",0);
    }
    else if(NT.compare("nil")==0){
        Read("nil");
        buildtree("<nil>",0);
    }
    else if(NT.compare("(")==0){
        Read("(");
        E();
        Read(")");
    }
    else if(NT.compare("dummy")==0){
        Read("dummy");
        buildtree("<dummy>",0);
    }
}
void Parser::D(){
    Da();
    if(NT.compare("within")==0){
        Read("within");
        D();
        buildtree("within",2);
    }
}
void Parser::Da(){
    Dr();
    int n=0;
    while(NT.compare("and")==0){
        Read("and");
        Dr();
        ++n;
    }
    if(n>0)
        buildtree("and",n+1);
}
void Parser::Dr(){
    if(NT.compare("rec")==0){
        Read("rec");
        Db();
        buildtree("rec",1);
    }
    else
        Db();
}
void Parser::Db(){
    if(NT.substr(1,2).compare("ID")==0){
        Read("ID");
        int n=1;
        if(NT.compare("=")==0||NT.compare(",")==0){
            while(NT.compare(",")==0){
                Read(",");
                Read("ID");
                ++n;
            }
            if(n>1)
                buildtree(",",n);
            Read("=");
            E();
            buildtree("=",2);
        }
        else if(NT.substr(1,2).compare("ID")==0||NT.compare("(")==0){
            while(NT.substr(1,2).compare("ID")==0||NT.compare("(")==0){
                Vb();
                ++n;
            }
            Read("=");
            E();
            buildtree("function_form",n+1);
        }
    }
    else{
        Read("(");
        D();
        Read(")");
        Read(";");
    }
}
void Parser::Vb(){
    if(NT.substr(1,2).compare("ID")==0){
        Read("ID");
    }
    else if(NT.compare("(")==0){
        Read("(");
        if(NT.compare(")")!=0){
            Vl();
            Read(")");
        }
        else{
            Read(")");
            buildtree("()",0);
        }
    }
}
void Parser::Vl(){
    Read("ID");
    int n=0;
    while(NT.compare(",")==0){
        Read(",");
        Read("ID");
        ++n;
    }
    if(n>0)
        buildtree(",",n+1);
}