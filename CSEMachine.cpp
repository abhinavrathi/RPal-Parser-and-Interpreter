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
    Object envObject("env",0);
    stack<Object> control;
    stack<Object> execution;
    control.push(envObject);
    execution.push(envObject);
    envMap[0]=-1;
    for(int i=0;i<deltaMap[0].size();++i)
        control.push(deltaMap[0][i]);
    while(control.size()>1){
        Object current=control.top();
        //Remove Current Object from Control Stack
        control.pop();
        if(current.type=="gamma"){
            Object topObject=execution.top();
            execution.pop();
            if(topObject.type=="lambdaClosure"){
                Object env("env",++env_count);
                envMap[env_count] = topObject.lambdaenv;
                envStack.push(env_count);
                currEnv=env_count;
                if(topObject.isTuple==false){
                    string paramName = topObject.lambdavar;
                    Object paramObject = execution.top();
                    execution.pop();
                    pair<int,string> keyPair(env_count,paramName);
                    paramMap[keyPair] = paramObject;
                }
                else{
                    string tuple=topObject.lambdavar;
                    string::iterator it;
                    string temp;
                    vector<string> params;
                    for(it=tuple.begin();it<tuple.end();it++){
                        if(*it==','){
                            params.push_back(temp);
                            temp=string();
                        }
                        else
                            temp+=*it;
                    }
                    Object valueTuple=execution.top();
                    execution.pop();
                    vector<Object> tupleVector = valueTuple.tuple;
                    for(unsigned int i=0;i<params.size();i++){
                        if(params[i]!=""){
                            pair<int,string> keyPair(env_count,params[i].c_str());
                            paramMap[keyPair]=tupleVector[i];
                        }
                    }
                }
                control.push(env);
                execution.push(env);
                int lambdaNum = topObject.lambdano;
                vector<Object> delta = deltaMap[lambdaNum];
                for(int i=0;i<delta.size();i++){
                    control.push(delta[i]);
                }
            }
            else if(topObject.type == "Y*"){
                Object nextObject = execution.top();
                execution.pop();
                nextObject.type ="eta";
                execution.push(nextObject);
            }
            else if(topObject.type=="eta"){
                Object lambdaObject=topObject;
                lambdaObject.type="lambdaClosure";
                execution.push(topObject);
                execution.push(lambdaObject);
                Object gammaObject("gamma","gamma");
                control.push(gammaObject);
                control.push(gammaObject);
            }
            else if(topObject.name=="Stern"||topObject.name=="stern"){
                Object stringObject = execution.top();
                execution.pop();
                string ObjectValue = stringObject.name;
                ObjectValue = ObjectValue.substr(2,ObjectValue.size()-3);
                ObjectValue = "'"+ObjectValue+"'";
                stringObject.name = ObjectValue;
                execution.push(stringObject);
            }
            else if(topObject.name=="Stem"||topObject.name=="stem"){
                Object stringObject=execution.top();
                execution.pop();
                string ObjectValue=stringObject.name;
                ObjectValue=ObjectValue.substr(1,1);
                ObjectValue="'"+ObjectValue+"'";
                stringObject.name=ObjectValue;
                execution.push(stringObject);
            }
            else if(topObject.name=="Conc"||topObject.name=="conc"){
                Object a=execution.top();
                execution.pop();
                Object b=execution.top();
                execution.pop();
                string c="'"+a.name.substr(1,a.name.size()-2)+b.name.substr(1,b.name.size()-2)+"'";
                Object newObject("STRING",c);
                execution.push(newObject);
                control.pop();
            }
            else if(topObject.name=="ItoS"||topObject.name=="itos"){
                Object a=execution.top();
                execution.pop();
                a.type="STRING";
                a.name="'"+a.name+"'";
                execution.push(a);
            }
            else if(topObject.name=="Print"||topObject.name=="print"){
                print_call=true;
                Object t=execution.top();
                execution.pop();
                if(t.isTuple==false){
                    if(t.type=="STRING"){
                        string tempStr=remove_escape_characters(t.name.substr(1,t.name.size()-2));
                        cout<<tempStr;
                        if(tempStr[tempStr.size()-1]=='\n')
                            cout<<endl;
                    }
                    else if(t.type=="lambdaClosure")
                        cout<<"[lambda closure: "<<t.lambdavar<<": "<<t.lambdano<<"]";
                    else
                        cout<<t.name;
                    Object dummy("dummy","dummy");
                    execution.push(dummy);
                }
                else{
                    vector<Object> tupleVector=t.tuple;
                    for(int i=0;i<tupleVector.size();i++){
                        if(i==0){
                            cout<<"(";
                        }
                        else{
                            cout<<", ";
                        }
                        if(tupleVector[i].type=="STRING"){
                            cout<<remove_escape_characters(tupleVector[i].name.substr(1,tupleVector[i].name.size()-2));
                        }
                        else if(tupleVector[i].isTuple == true ){
                            cout<<"Inside else if"<<endl;
                            vector<Object> innerTuple = tupleVector[i].tuple;
                            cout<<"Size"<<innerTuple.size()<<endl;
                            if(innerTuple.size()==1){
                                if(innerTuple[0].type=="STRING")
                                    cout<< remove_escape_characters(innerTuple[0].name.substr(1,innerTuple[0].name.size()-2));
                            }
                        }
                        else
                            cout << tupleVector[i].name;
                        if(i==tupleVector.size()-1)
                            cout<<")";
                    }
                }
            }
            else if(topObject.name=="Isinteger"){
                Object t=execution.top();
                execution.pop();
                Object c;
                if(t.type=="INTEGER")
                    c.type=c.name="true";
                else
                    c.type=c.name="false";
                execution.push(c);
            }
            else if(topObject.name=="Istruthvalue"){
                Object t=execution.top();
                execution.pop();
                Object c;
                if(t.type=="true"||t.type=="false")
                    c.type=c.name="true";
                else
                    c.type=c.name="false";
                execution.push(c);
            }
            else if(topObject.name=="Isstring"){
                Object t=execution.top();
                execution.pop();
                Object c;
                if(t.type=="STRING")
                    c.type=c.name="true";
                else
                    c.type=c.name="false";
                execution.push(c);
            }
            else if(topObject.name=="Istuple"){
                Object t = execution.top();
                execution.pop();
                Object c;
                if(t.isTuple==true)
                    c.type=c.name="true";
                else
                    c.type=c.name="false";
                execution.push(c);
            }
            else if(topObject.name=="Isdummy"){
                Object t = execution.top();
                execution.pop();
                Object c;
                if(t.name=="dummy")
                    c.type=c.name="true";
                else
                    c.type=c.name="false";
                execution.push(c);
            }
            else if(topObject.name=="Isfunction"){
                Object t=execution.top();
                execution.pop();
                Object c;
                if(t.type=="lambdaClosure")
                    c.type=c.name="true";
                else
                    c.type=c.name="false";
                execution.push(c);
            }
            else if(topObject.name=="Order"){
                Object t=execution.top();
                execution.pop();
                Object c;
                c.type="INTEGER";
                c.name=convert_int_to_string((int)t.tuple.size());
                execution.push(c);
            }
            else if(topObject.name=="Null"){
                Object t=execution.top();
                execution.pop();
                Object c;
                if(t.name=="nil")
                    c.type=c.name="true";
                else
                    c.type=c.name="false";
                execution.push(c);
            }
            else if(topObject.isTuple==true){
                Object t=execution.top();
                execution.pop();
                if(t.type=="INTEGER"){
                    int index = atoi(t.name.c_str());
                    index-=1;
                    execution.push(topObject.tuple[index]);
                }
            }
        }
        else if(current.type=="OPERATOR"){
            Object a=execution.top();
            execution.pop();
            Object b=execution.top();
            execution.pop();
            Object c;
            if(a.type=="STRING"){
                if(current.name=="eq"){
                    if(a.name==b.name)
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
                else if(current.name=="ne"){
                    if(a.name!=b.name)
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
            }
            else if(a.type=="INTEGER"){
                int x,y;
                x=atoi(a.name.c_str());
                y=atoi(b.name.c_str());
                if(current.name=="+"){
                    c.type="INTEGER";
                    c.name=convert_int_to_string(x+y);
                }
                else if(current.name=="-"){
                    c.type=a.type;
                    c.name=convert_int_to_string(x-y);
                }
                else if(current.name=="*"){
                    c.type=a.type;
                    c.name=convert_int_to_string(x*y);
                }
                else if(current.name=="/"){
                    c.type=a.type;
                    c.name=convert_int_to_string(x/y);
                }
                else if(current.name=="**"){
                    c.type=a.type;
                    c.name=convert_int_to_string(pow(x,y));
                }
                else if(current.name=="gr"){
                    if(x>y)
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
                else if(current.name=="ge"){
                    if(x>=y)
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
                else if(current.name=="ls"){
                    if(x<y)
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
                else if(current.name=="le"){
                    if(x<=y)
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
                else if(current.name=="eq"){
                    if(x==y)
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
                else if(current.name=="ne"){
                    if(x!=y)
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
            }
            else if(a.type=="true"||a.type=="false"){
                if(current.name=="or"){
                    if(a.name=="true"||b.name=="true")
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
                else if(current.name=="&"){
                    if(a.name=="true"&&b.name=="true")
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
                else if(current.name=="eq"){
                    if(a.name==b.name)
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
                else if(current.name=="or"){
                    if(a.name!=b.name)
                        c.name=c.type="true";
                    else
                        c.name=c.type="false";
                }
            }
            execution.push(c);
        }
        else if(current.type=="neg"){
            Object a=execution.top();
            execution.pop();
            int x=-1*atoi(a.name.c_str());
            Object c("INTEGER",convert_int_to_string(x));
            execution.push(c);
        }
        else if(current.type=="not"){
            Object a=execution.top();
            execution.pop();
            Object c;
            if(a.name=="false")
                c.name=c.type="true";
            else
                c.name=c.type="false";
            execution.push(c);
        }
        else if(current.type=="IDENTIFIER"){
            int t=currEnv;
            pair<int,string> p(t,current.name);
            map<key_pair,Object>::iterator it = paramMap.find(p);
            while(paramMap.end() == it && t>=0){
                t=envMap[t];
                p.first=t;
                it=paramMap.find(p);
            }
            if(paramMap.end()!=it){
                Object c=it->second;
                execution.push(c);
            }
            else{
                execution.push(current);
            }
        }
        else if(current.type=="env"){
            Object topObject = execution.top();
            execution.pop();
            execution.pop();
            execution.push(topObject);
            envStack.pop();
            currEnv=envStack.top();
        }
        else if(current.type=="beta"){
            Object topObject=execution.top();
            execution.pop();
            vector<Object> delta;
            if(topObject.name=="true")
                delta=deltaMap[current.thenno];
            else
                delta=deltaMap[current.elseno];
            for(unsigned int i=0;i<delta.size();i++)
                control.push(delta[i]);
        }
        else if(current.name=="tau"){
            int tauCount=current.tauno;
            string tuple="(";
            vector<Object> tup;
            while(tauCount!=0){
                Object t=execution.top();
                execution.pop();
                tup.push_back(t);
                if(tauCount>1)
                    tuple+=t.name+", ";
                else
                    tuple+=t.name;
                --tauCount;
            }
            tuple+=")";
            Object a(tuple,"tuple");
            a.tuple=tup;
            a.isTuple = true;
            execution.push(a);
        }
        else if(current.name=="nil"){
            current.isTuple = true;
            execution.push(current);
        }
        else if(current.name=="aug"){
            Object tuple=execution.top();
            execution.pop();
            Object toAdd=execution.top();
            execution.pop();
            if(tuple.name=="nil"){
                Object newObject(toAdd.name,"tuple");
                newObject.isTuple = true;
                newObject.tuple = vector<Object>();
                newObject.tuple.push_back(toAdd);
                execution.push(newObject);
            }
            else{
                tuple.tuple.push_back(toAdd);
                execution.push(tuple);
            }
        }
        else if(current.type=="lambdaClosure"){
            current.lambdaenv=currEnv;
            execution.push(current);
        }
        else
            execution.push(current);
    }
    if(print_call==false)
        cout<<"\n";
};
string CSEMachine::convert_int_to_string(int i){
    ostringstream oss;
    oss<<i;
    return oss.str();
};
string CSEMachine::remove_escape_characters(const string& s)
{
    string res;
    string::const_iterator it = s.begin();
    while (it != s.end())
    {
        char c=*it++;
        if(c=='\\'&&it!=s.end())
        {
            switch(*it++){
                case '\\': c = '\\'; break;
                case 'n': c = '\n'; break;
                case 't': c = '\t'; break;
                default: continue;
            }
        }
        res += c;
    }
    return res;
};