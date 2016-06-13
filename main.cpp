/*
 NAME: Abhinav Rathi
 UFID: 55935636
*/

//
//  main.cpp
//  RPAL Interpreter
//
//  Created by Abhinav Rathi on 4/17/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#include <iostream>
#include <string.h>
#include "Parser.hpp"
#include "Tree.hpp"
#include "Scanner.hpp"
#include "Standardizer.hpp"
#include "Object.hpp"
#include "ControlStructures.hpp"
#include "CSEMachine.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    /* Expected Command Line Inputs:
     1st input -> ./p1
     2nd input -> -ast,-st or -l (optional)
     3rd input -> filename
     */
    
    // If there are less than 3 nos. Command Line Inputs, then display error and exit
    if(argc==1){
        cout<<"Please provide filename.\nOr, use switch -ast followed by filename to display Abstarct Synatx Tree.\nOr, use switch -st followed by filename to display Standardized Tree.\nOr, use switch -l followed by filename to List the Input File.\n";
        return 0;
    }
    else if(argc==2&&strcmp(argv[1],"-ast")==0&&strcmp(argv[1],"-l")==0&&strcmp(argv[1],"-st")==0){
        cout<<"Please provide filename.\n";
        return 0;
    }
    else if(argc==2){
        Parser o;
        o.set(argv[1]);
        o.E();
        Tree o1=o.gettree();
        Standardizer s;
        ControlStructures cs;
        cs.genControlStructures(s.standardize(o.gettree().stack[0]));
        CSEMachine machine(cs.getCS());
        machine.evaluateControlStructures();
    }
    // If there are more than 3 nos. Command Line Inputs, then display error and exit
    else if(argc>3){
        cout<<"Extra switches used.\nPlease use switch -ast followed by filename to display Abstarct Synatx Tree.\nOr, use switch -st followed by filename to display Standardized Tree.\nOr, use switch -l followed by filename to List the Input File.\nOr, just provide filename to display it's output.\n";
        return 0;
    }
    // If switch is not -ast,-st or -l, then display error and exit
    else if(strcmp(argv[1],"-ast")!=0&&strcmp(argv[1],"-l")!=0&&strcmp(argv[1],"-st")!=0){
        cout<<"Unknown switch used. Please use switch -ast,-st or -l\n";
        return 0;
    }
    // Function call for -ast switch
    else if(strcmp(argv[1],"-ast")==0){
        Parser o;
        o.set(argv[2]);
        o.E();
        Tree o1=o.gettree();
        o1.preorder();
    }
    // Function call for -st switch
    else if(strcmp(argv[1],"-st")==0){
        Parser o;
        o.set(argv[2]);
        o.E();
        Tree o1=o.gettree();
        //o1.preorder();
        Standardizer s;
        o1.traverse(s.standardize(o.gettree().stack[0]),0);
    }
    // Function call for -l switch
    else if(strcmp(argv[1],"-l")==0){
        Scanner s;
        cout<<s.read(argv[2]);
    }
    return 0;
}