//
//  Lex.cpp
//  Lex
//
//  Created by shiyi on 2016/10/18.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#include "Lex.hpp"

Lex::Lex(string _lexFile)
{
    Lex(_lexFile, _lexFile+".c");
}

Lex::Lex(string _lexFile, string _outCFile)
{
    lexFile = _lexFile;
    outCFile = _outCFile;
    
    init();
}

void Lex::init()
{
    //输入输出重定向
    freopen(lexFile.c_str(), "r", stdin);
    freopen(outCFile.c_str(), "w+", stdout);
    
    memset(dfaEnd, -1, sizeof(dfaEnd));
    memset(nfaEnd, -1, sizeof(nfaEnd));
}

void Lex::printError(int line, string str, string mess)
{
    cerr<<"Error："<<mess<<" --> "<<line<<" --> "<<str<<endl;
    exit(1);
}

void Lex::printWaring(int line, string str, string mess)
{
    cerr<<"Waring："<<mess<<" --> "<<line<<" --> "<<str<<endl;
}

//判断正规式是否合法
bool Lex::isExpre(vector<pair<string, bool>> v)
{
    //暂未实现
    return true;
}

//解析预设代码部分
void Lex::getFunc(string str, int line)
{
    string::iterator iter = str.begin();
    string left, right;
    bool flag = false;
    
    while(iter != str.end() && *iter != '=')
    {
        char ch = *iter;
        if((ch <= 'Z' && ch >= 'A')
           || (ch <= 'z' && ch >= 'a')
           || (ch <= '9' && ch >= '0')
           || ch == '_')
            left += *iter;
        else
            flag = true;
        iter++;
    }

    //略过'='
    iter++;
    
    while(iter != str.end())
    {
        char ch = *iter;
        if((ch <= 'Z' && ch >= 'A')
           || (ch <= 'z' && ch >= 'a')
           || (ch <= '9' && ch >= '0')
           || ch == '_')
            right += *iter;
        else
            flag = true;
        iter++;
    }
    
    if(left.size() == 0 || right.size() == 0)
        printError(line, str, "不合规范");
    
    //报出警告
    if(flag)
    {
        char mess[100];
        sprintf(mess, "除字母数字下划线之外的字符均已忽略，请确认 %s = %s", left.c_str(), right.c_str());
        printWaring(line, str, mess);
    }
    
    //插入该辅助函数
    funcMap.insert(pair<string, string>(left, right));
}

//解析规则定义部分
void Lex::getRegular(string str, int line)
{
    string::iterator iter = str.begin();
    vector<pair<string, bool>> left;
    string right;
    
    while(iter != str.end() && (*iter == ' ' || *iter == '\t'))
        iter++;
    if(iter == str.end())
        printError(line, str, "规则缺失");
    
    // [ ][%,(,),{,},|,*,$]
    while(iter != str.end() && *iter != ' ' && *iter != '\t')
    {
        string t;
        if(*iter == '%' && iter+1 != str.end())
        {
            iter++;
            switch(*iter)
            {
                case ' ':
                case '%':
                case '(':
                case ')':
                case '{':
                case '}':
                case '|':
                case '*':
                    t += *iter;
                    //需转义的输入
                    left.push_back(pair<string, bool>(t, false));
                    inputSet.insert(t);
                    break;
                case '$':
                    //空字符输入
                    left.push_back(pair<string, bool>("", false));
                    break;
                default:
                    break;
            }
        }
        else if(*iter == '{')
        {
            iter++;
            while(iter != str.end() && *iter != '}')
                t += *iter++;
            if(iter == str.end())
                printError(line, str, "规则正规式格式错误");
            //自定义输入
            left.push_back(pair<string, bool>(t, false));
            inputSet.insert(t);
        }
        else
        {
            switch(*iter)
            {
                case '(':
                case ')':
                case '*':
                case '|':
                    //加两次，与同样输入相区分
                    t += *iter;
                    t += *iter;
                    //符号
                    left.push_back(pair<string, bool>(t, true));
                    break;
                default:
                    t += *iter;
                    //输入
                    left.push_back(pair<string, bool>(t, false));
                    inputSet.insert(t);
                    break;
            }
        }
        iter++;
    }
    while(iter != str.end() && *iter != ' ' && *iter != '\t')
        iter++;
    
    if(iter == str.end())
        printError(line, str, "规则方法体缺失");
    iter++;
    
    if(*iter != '{')
    {
        printError(line, str, "规则方法体格式错误");
    }
    
    right += *iter++;
    int cnt = 1;
    while(cnt != 0 && iter != str.end())
    {
        if(*iter == '{')
            cnt++;
        else if(*iter == '}')
            cnt--;
        right += *iter++;
    }

    if(cnt != 0)
        printError(line, str, "规则方法体格式错误");

    while(iter != str.end())
    {
        if(*iter != ' ')
        {
            char mess[100];
            sprintf(mess, "规则多余字符已忽略，请确认 %s", string(str.begin(), iter).c_str());
            printWaring(line, str, mess);
            break;
        }
    }
    
    //判断是否合法后保存规则
    if(isExpre(left))
        regrVet.push_back(left);
    
    //保存方法体
    funcVet.push_back(right);
}

void Lex::scanner()
{
    int state = 0;
    int line = 0;
    string str;
    string outStr;
    
    while(!cin.eof())
    {
        line++;
        switch (state)
        {
            case 0:
            {
                getline(cin, str);
                if(str.compare(0, 2, "%{") == 0)
                {
                    state = 1;
                    cout<<"//%{ start"<<endl;
                }
                else if(str.compare(0, 2, "%!") == 0)
                {
                    state = 2;
                    cout<<"//%! start"<<endl;
                }
                else if(str.compare(0, 2, "%%") == 0)
                {
                    state = 3;
                    outStr.clear();
                    cout<<"//%% start"<<endl;
                }
                else
                {
                    state = 0;
                    printWaring(line, str, "不在标志符号内，忽略该行信息");
                }
                break;
            }
            case 1:
            {
                getline(cin, str);
                if(str.compare(0, 2, "%}") == 0)
                {
                    state = 0;
                    cout<<"//%} end"<<endl;
                }
                else
                    cout<<str<<endl;
                break;
            }
            case 2:
            {
                getline(cin, str);
                if(str.compare(0, 2, "%!") == 0)
                {
                    state = 0;
                    cout<<"//%! end"<<endl;
                }
                else
                    getFunc(str, line);
                break;
            }
            case 3:
            {
                getline(cin, str);
                if(str.compare(0, 2, "%%") == 0)
                {
                    state = 0;
                    getRegular(outStr, line);
                    cout<<"//%% end"<<endl;
                }
                else if(str.compare(0, 2, "%$") == 0)
                {
                    getRegular(outStr, line);
                    outStr.clear();
                }
                else
                    outStr += str;
                break;
            }
            default:
            {
                printError(line, str, "结构不完整");
                break;
            }
        }
    }
    if(state != 0)
    {
        printError(line, str, "结构不完整");
    }
}

void Lex::addNFANode(int fromId, string input, int toId)
{
    nfaVet[fromId].push_back(Node(fromId, input, toId));
}

void Lex::addDFANode(int fromId, string input, int toId)
{
    dfaVet[fromId].push_back(Node(fromId, input, toId));
}

void Lex::regrToNFA(vector<pair<string, bool>> regr, int startId, int endId, int &itemId)
{
    stack<int> s_st;
    stack<int> s_ed;
    stack<string> s_str;
    
    s_st.push(startId);
    s_ed.push(endId);
    
    for(auto iter = regr.begin(); iter != regr.end(); iter++)
    {
        string str = (*iter).first;
        bool isSign = (*iter).second;

        if(isSign)
        {
            if(str.compare("((") == 0)
            {
                s_ed.push(itemId++);
                s_str.push("((");
            }
            else if(str.compare("))") == 0)
            {
                int st = s_st.top();
                int ed = s_ed.top();
                string s = s_str.top();
                //将当前最后状态与终态空连接
                addNFANode(st, "", ed);
                
                //将括号内的状态一一退出并连接
                while(!s_str.empty())
                {
                    s = s_str.top();
                    s_str.pop();
                    if(s.compare("((") == 0)
                        break;
                    int nxt = s_st.top();
                    s_st.pop();
                    int pre = s_st.top();
                    if(s.compare("##") != 0)
                        addNFANode(pre, s, nxt);
                }

                //将括号当做一个输入#,使其与普通输入同样规则，解决括号递归问题
                s_str.push("##");
                s_st.push(s_ed.top());
                s_ed.pop();
            }
            else if(str.compare("||") == 0)
            {
                int ed = s_ed.top();
                int st = s_st.top();
                string s;
                //增加当前最后状态到终态的连接
                addNFANode(st, "", ed);

                //将括号至|内的状态一一退出并连接
                while(!s_str.empty())
                {
                    s = s_str.top();
                    if(s.compare("((") == 0)
                        break;
                    s_str.pop();
                    int nxt = s_st.top();
                    s_st.pop();
                    int pre = s_st.top();
                    if(s.compare("##") != 0)
                        addNFANode(pre, s, nxt);
                }
            }
            else if(str.compare("**") == 0)
            {
                int nxt = s_st.top();
                s_st.pop();
                int pre = s_st.top();
                addNFANode(pre, "", nxt);
                addNFANode(nxt, "", pre);
                s_st.push(nxt);
            }
            else
            {
                cerr<<"ERROR::regrToNFA"<<endl;
            }
        }
        else
        {
            s_str.push(str);
            s_st.push(itemId++);
        }
    }
    
    addNFANode(s_st.top(), "", s_ed.top());
    
    while(!s_str.empty())
    {
        int nxt = s_st.top();
        s_st.pop();
        int pre = s_st.top();
        string s = s_str.top();
        s_str.pop();
        if(s.compare("##") != 0)
            addNFANode(pre, s, nxt);
    }
}

void Lex::getNFA()
{
    int startId = 0;
    int endId = 1;
    int itemId = 2;
    int num = 0;
    for(auto iter = regrVet.begin(); iter != regrVet.end(); iter++)
    {
        int iStartId = itemId++;
        int iEndId = itemId++;
        addNFANode(startId, "", iStartId);
        addNFANode(iEndId, "", endId);
        regrToNFA(*iter, iStartId, iEndId, itemId);
        nfaEnd[iEndId] = num++;
        //cerr<<nfaEnd[iEndId]<<"-=="<<iEndId<<endl;
    }

    this->nfaNum = itemId;
    
    string s;
    
}

void Lex::findBeGo(int i, string input, vector<int>* state)
{
    for(auto x : nfaVet[i])
    {
        int sId = x.toId;
        bool flag = true;
//        cerr<<x.fromId<<" "<<x.input<<" "<<x.toId<<endl;
        for(auto iter=state->begin(); iter!=state->end(); iter++)
            if((*iter) == sId)
            {
//                cerr<<i<<"::"<<sId<<endl;
                flag = false;
                break;
            }
        
        if(flag && input.compare(x.input) == 0)
        {
            state->push_back(sId);
            findBeGo(sId, "", state);
        }
    }
//    for(auto iter=state->begin(); iter!=state->end(); iter++)
//        cerr<<*iter<<"<";
//    cerr<<endl;
}

vector<int>* Lex::getState(vector<int>* fromState, string input)
{
    vector<int>* state = new vector<int>;
    
    for(auto iter=fromState->begin(); iter != fromState->end(); iter++)
    {
        //cerr<<"-=-"<<*iter<<endl;
        int num = (*iter);
        findBeGo(num, input, state);
//        for(auto iter=state->begin(); iter!=state->end(); iter++)
//            cerr<<*iter<<" ";
//        cerr<<endl;
    }
    
    sort(state->begin(), state->end());

    return state;
}

void Lex::getDFA()
{
    //对状态集合进行查重
    map<vector<int>, int> stateMap;
    queue<pair<vector<int>*, int>> stateQue;
    int id = 0;
    vector<int> *t = new vector<int>;
    t->push_back(0);
    //确定起始状态集合
    vector<int>* startState =  getState(t, "");
    delete t;
    
    startState->push_back(0);
    sort(startState->begin(), startState->end());
    
    stateMap.insert(pair<vector<int>, int>(*startState, id));
    stateQue.push(pair<vector<int>*, int>(startState, id));
    id++;
    
    while(!stateQue.empty())
    {
        auto state = stateQue.front();
        stateQue.pop();
        
        for(string x : inputSet)
        {
            vector<int>* newState = getState(state.first, x);
            if(newState->empty())
                continue;
            
            auto rel = stateMap.find(*newState);
            
            if(rel == stateMap.end())
            {
                stateMap.insert(pair<vector<int>, int>(*newState, id));
                stateQue.push(pair<vector<int>*, int>(newState, id));
                addDFANode(state.second, x, id);
                id++;
            }
            else
            {
                addDFANode(state.second, x, rel->second);
            }
        }
    }
    
    //记录dfa状态总数
    this->dfaNum = id;
    //获取dfa终态集合
    getVt(stateMap);
}

void Lex::getVt(map<vector<int>, int> stateMap)
{
    
    for(auto x : stateMap)
    {
        for(auto i=x.first.begin(); i!=x.first.end(); i++)
        {
            int num = (*i);
            if(nfaEnd[num] != -1)
            {
                dfaEnd[x.second] = nfaEnd[num];
                break;
            }
        }
    }
}

void Lex::outCodeLeft()
{
    cout<<"#include <stdio.h>"<<endl;
    cout<<"#include <stdlib.h>"<<endl;
    cout<<"#include <string.h>"<<endl;
    cout<<endl;
    cout<<"#define SYLEX_MAXSIZE_TEXT 120"<<endl;
    cout<<"#define SYLEX_MAXSIZE_BUFF 1024"<<endl;
    cout<<endl;
    cout<<"char SYLEX_FILE_NAME[100];"<<endl;
    cout<<"char SYLEX_OUT_FILE_NAME[100];"<<endl;
    cout<<"int SYLEX_LINE = 0;"<<endl;
    cout<<"int SYLEX_STATE = 0;"<<endl;
    cout<<"int SYLEX_TEXT_LEN = 0;"<<endl;
    cout<<"char SYLEX_TEXT[SYLEX_MAXSIZE_TEXT];"<<endl;
    cout<<"char SYLEX_BUFF[SYLEX_MAXSIZE_BUFF];"<<endl;
    cout<<endl;
    cout<<"//扫描函数"<<endl;
    cout<<"void SYLEX_scanner(char *str)"<<endl;
    cout<<"{"<<endl;
    cout<<"    char ch = ' ';"<<endl;
    cout<<"    while(ch != '\\0')"<<endl;
    cout<<"    {"<<endl;
    cout<<"        //printf(\"%c %d\\n\", ch, SYLEX_STATE);"<<endl;
    cout<<"        switch(SYLEX_STATE) {"<<endl;
}

void Lex::outCodeRight()
{
    cout<<"        }"<<endl;
    cout<<"    }"<<endl;
    cout<<"}"<<endl;
    cout<<endl;
    cout<<"int main(int argc, char **args)"<<endl;
    cout<<"{"<<endl;
    cout<<"    if(argc == 1)"<<endl;
    cout<<"    {"<<endl;
    cout<<"        printf(\"没有输入源文件名\");"<<endl;
    cout<<"        return 0;"<<endl;
    cout<<"    }"<<endl;
    cout<<"    else if(argc == 2)"<<endl;
    cout<<"    {"<<endl;
    cout<<"        strcpy(SYLEX_FILE_NAME, args[1]);"<<endl;
    cout<<"        sprintf(SYLEX_OUT_FILE_NAME, \"%s.out\", SYLEX_FILE_NAME);"<<endl;
    cout<<"    }"<<endl;
    cout<<"    else"<<endl;
    cout<<"    {"<<endl;
    cout<<"        strcpy(SYLEX_FILE_NAME, args[1]);"<<endl;
    cout<<"        strcpy(SYLEX_OUT_FILE_NAME, args[2]);"<<endl;
    cout<<"    }"<<endl;
    cout<<"    FILE* file = fopen(SYLEX_FILE_NAME, \"r\");"<<endl;
    cout<<"    while(NULL != fgets(SYLEX_BUFF, SYLEX_MAXSIZE_BUFF, file))"<<endl;
    cout<<"    {"<<endl;
    cout<<"        ++SYLEX_LINE;"<<endl;
    cout<<"        SYLEX_scanner(SYLEX_BUFF);"<<endl;
    cout<<"    }"<<endl;
    cout<<"    return 0;"<<endl;
    cout<<"}"<<endl;
}

void Lex::outCodeMid()
{
    for(int i=0; i<dfaNum; i++)
    {
        cout<<"        case "<<i<<":"<<endl;
        cout<<"        {"<<endl;
        cout<<"            ch = *str++;"<<endl;
        cout<<"            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;"<<endl;

        for(auto x : dfaVet[i])
        {
            cout<<"            if(";
            auto func =  funcMap.find(x.input);
            if(func == funcMap.end())
            {
                cout<<"ch == '";
                cout<<x.input;
                cout<<"'";
            }
            else
            {
                cout<<func->second;
                cout<<"(ch)";
            }
            cout<<"){"<<endl;
        
            cout<<"                SYLEX_STATE = "<<x.toId<<";"<<endl;;
            
            cout<<"            }"<<endl;
            
            cout<<"            else"<<endl;
        }
        cout<<"            {"<<endl;
        if(dfaEnd[i] != -1)
        {
            cout<<"SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\\0';"<<endl;
            cout<<"SYLEX_TEXT_LEN=0;"<<endl;
            cout<<"SYLEX_STATE=0;"<<endl;
            cout<<"str--;"<<endl;
            cout<<"//**************s"<<endl;
            cout<<funcVet[dfaEnd[i]]<<endl;
            cout<<"//**************e"<<endl;
        }
        else
        {
            cout<<"printf(\"Error in line %d\\n\", SYLEX_LINE);"<<endl;
            cout<<"exit(1);"<<endl;
        }
        cout<<"            }"<<endl;
        cout<<"            break;"<<endl;
        cout<<"        }"<<endl;
    }
}

void Lex::work()
{
    cerr<<"Lex文本解析start"<<endl;
    scanner();
    cerr<<"Lex文本解析end"<<endl;
    
    cerr<<"正规式转NFAstart"<<endl;
    getNFA();
    cerr<<"正规式转NFAend"<<endl;

    cerr<<"NFA转DFAstart"<<endl;
    getDFA();
    cerr<<"NFA转DFAend"<<endl;

    //print();
    
    outCodeLeft();
    outCodeMid();
    outCodeRight();
    
    cerr<<"已生成词法分析器out.c"<<endl;
}

//调试输出
void Lex::print()
{
    for(auto x : regrVet)
        for(auto y : x)
        cerr<<y.first<<" "<<y.second<<endl;
    cerr<<"-=-=-"<<endl;
    
    for(auto x : funcMap)
        cerr<<x.first<<" "<<x.second<<endl;
    
    cerr<<"-=-=-"<<endl;
    
    for(auto x : funcVet)
        cerr<<x<<endl;
    
    cerr<<"-=-=-"<<endl;
    
    for(auto x : inputSet)
        cerr<<x<<endl;
    
    cerr<<"-=-=-"<<endl;
    
    for(int i=0; i<nfaNum; i++)
    {
        for(auto x : nfaVet[i])
            cerr<<x.fromId<<"--["<<x.input<<"]--"<<x.toId<<endl;
    }
    
//    cerr<<"-=-ss-"<<endl;
//    cerr<<dfaNum<<endl;
//    for(int i=0; i<dfaNum; i++)
//    {
//        for(auto x : dfaVet[i])
//            cerr<<x.fromId<<"--["<<x.input<<"]--"<<x.toId<<endl;
//    }
//    
//    cerr<<"-=-=-"<<endl;
//    for(int i=0; i<dfaNum; i++)
//    {
//        if(dfaEnd[i] != -1)
//            cerr<<i<<endl;
//    }
    
}
