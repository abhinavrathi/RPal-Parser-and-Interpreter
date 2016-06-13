/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  Scanner.cpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/17/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

/* Scans the input file, and returns single token on each call to function tokenize() */

#include "Scanner.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
void Scanner::set(string x){    // Initialize filename and read first charachter in ch
    filename=x;
    ifs.open(filename.c_str(),fstream::in);
    ifs >> noskipws >> ch;
}
string Scanner::tokenize(){     // Returns 1 token at a time, reading from the file
    string temp="";
    do{
        while((ch==' '||ch=='\n'||ch=='\t')&&!ifs.eof())
            ifs>>noskipws>>ch;
        if(ch=='/'){
            ifs>>noskipws>>ch;
            if(ch!='/'){
                next=ch;
                ch='/';
            }
            else{
                while(ch!='\n'&&!ifs.eof())
                    ifs>>noskipws>>ch;
                ifs>>noskipws>>ch;
                continue;
            }
        }
        if(ifs.eof()){
            return "";
        }
        else if((ch>=65&&ch<=90)||(ch>=97&&ch<=122)){
            temp+=ch;
            ifs>>noskipws>>ch;
            while((ch>=65&&ch<=90)||(ch>=97&&ch<=122)||(ch>=48&&ch<=57)||ch=='_'){
                temp+=ch;
                ifs>>noskipws>>ch;
            }
            if(temp=="let"||temp=="in"||temp=="fn"||temp=="where"||temp=="aug"||temp=="not"||temp=="or"||temp=="gr"||temp=="ge"||temp=="ls"||temp=="le"||temp=="eq"||temp=="ne"||temp=="true"||temp=="false"||temp=="nil"||temp=="dummy"||temp=="within"||temp=="and"||temp=="rec"||temp=="list")
                return temp;
            else{
                temp="<ID:"+temp+">";
                return temp;
            }
        }
        else if(ch>=48&&ch<=57){
            temp+=ch;
            ifs>>noskipws>>ch;
            while(ch>=48&&ch<=57){
                temp+=ch;
                ifs>>noskipws>>ch;
            }
            temp="<INT:"+temp+">";
            return temp;
        }
        else if(ch=='\''){
            char prev,curr;
            temp+=ch;
            prev=ch;
            ifs>>noskipws>>ch;
            curr=ch;
            while(!ifs.eof()){
                if(curr=='\''&&prev!='\\')
                    break;
                temp+=ch;
                prev=ch;
                ifs>>noskipws>>ch;
                curr=ch;
            }
            if(!ifs.eof()){
                temp+=ch;
                ifs>>noskipws>>ch;
            }
            if(temp.length()==1){
                cout<<"Error in String Read";
                exit(1);
            }
            temp="<STR:"+temp+">";
            return temp;
        }
        else if(ch=='('||ch==')'||ch==';'||ch==','){
            temp="";
            temp+=ch;
            ifs>>noskipws>>ch;
            return temp;
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='<'||ch=='>'||ch=='&'||ch=='.'||ch=='@'||ch=='/'||ch==':'||ch=='='||ch=='~'||ch=='|'||ch=='$'||ch=='!'||ch=='#'||ch=='%'||ch=='^'||ch=='_'||ch=='['||ch==']'||ch=='{'||ch=='}'||ch=='\"'||ch=='\''||ch=='?'){
            if(ch=='/'){
                temp="";
                temp+=ch;
                ch=next;
                return temp;
            }
            temp="";
            temp+=ch;
            ifs>>noskipws>>ch;
            if((temp[0]=='>'&&ch=='=')||(temp[0]=='<'&&ch=='=')||(temp[0]=='*'&&ch=='*')||(temp[0]=='-'&&ch=='>')){
                temp+=ch;
                ifs>>noskipws>>ch;
            }
            return temp;
        }
        else{
            temp="Unknown";
            cout<<temp;
            exit(1);
            return temp;
        }
    }while(!ifs.eof());
    return temp;
}
void Scanner::close(){
    ifs>>noskipws>>ch;
    while(ch==' '||ch=='\n')
        ifs>>noskipws>>ch;
    while(ch=='/'){
        while(ch!='\n'&&ch!='\0')
            ifs>>noskipws>>ch;
        while(ch==' '||ch=='\n')
            ifs>>noskipws>>ch;
    }
    if(ch!=EOF){
        cout<<"File Input Still Remains but Scanning Ended\n";
        exit(1);
    }
    ifs.close();
}
// Following function is used for -l switch, just to read the input file
string Scanner::read(string x){
    filename=x;
    ifs.open(filename.c_str(),fstream::in);
    string temp="";
    ifs >> noskipws >> ch;
    while(!ifs.eof()){
        temp+=ch;
        ifs >> noskipws >> ch;
    }
    ifs.close();
    return temp;
}