//
//  main.cpp
//  Lex
//
//  Created by shiyi on 2016/10/18.
//  Copyright © 2016年 shiyi. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include "Lex.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Lex lex("lex.l", "out.c");
    lex.work();
    
    return 0;
}
