//
//  Lex.hpp
//  Lex
//
//  Created by shiyi on 2016/10/18.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#ifndef Lex_hpp
#define Lex_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <queue>

using namespace std;

struct Node
{
    Node(int fromId, string input, int toId)
    {
        this->fromId = fromId;
        this->input = input;
        this->toId = toId;
    }
    int fromId;
    string input;
    int toId;
};

class Lex
{
public:
    static const int MAXID = 100000;
    
    Lex(string _lexFile);
    Lex(string _lexFile, string _outCFile);
    void init();
    
    //写入scanner函数之前
    void outCodeLeft();
    //写入scanner函数之后
    void outCodeRight();
    //写入scanner函数
    void outCodeMid();
    //解析lex源文件
    void scanner();
    //错误警告等输出
    inline void printError(int line, string str, string mess);
    inline void printWaring(int line, string str, string mess);
    //解析方法体
    void getFunc(string str, int line);
    //解析正规式
    void getRegular(string str, int line);
    
    //------日后补充
    //判断正规式是否合法
    bool isExpre(vector<pair<string, bool>>);
    //DFA最小化
    void getSimpDFA();
     
    // -----------
    
    //添加NFA节点
    inline void addNFANode(int fromId, string input, int toId);
    //添加DFA节点
    inline void addDFANode(int fromId, string input, int toId);

    //正规式转NFA
    void regrToNFA(vector<pair<string, bool>> regr, int startId, int endId, int &itemId);
    //生成NFA
    void getNFA();
    //生成DFA
    void getDFA();
    //nfa查询
    void findBeGo(int i, string input, vector<int>* state);
    //获取nfa目标状态集合
    vector<int>* getState(vector<int>* fromState, string input);
    //获取终态
    void getVt(map<vector<int>, int> stateMap);

    //执行操作
    void work();
    
    //输出-测试-
    inline void print();
    
private:
    string lexFile;
    string outCFile;
    //自定义输入对应方法体
    map<string, string> funcMap;
    //正规式
    vector<vector<pair<string, bool>>> regrVet;
    //方法体
    vector<string> funcVet;
    //NFA
    vector<Node> nfaVet[MAXID];
    //DFA
    vector<Node> dfaVet[MAXID];
    //储存所有输入
    set<string> inputSet;
    //DFAend
    int dfaEnd[MAXID];
    //NFAend   值为funcVet item的下标
    int nfaEnd[MAXID];
    int nfaNum;
    int dfaNum;
};

#endif /* Lex_hpp */
