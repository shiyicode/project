#include "board.h"
#include "block.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

Board::Board(int _length)
    : length(_length)
{
    srand((unsigned) time(NULL));
    //初始化时间间隔，分数
    atime = 200;
    score = 0;
    memset(map, 0, sizeof(map));

    //从文件读入最高分
    FILE *fd =fopen("score.bin","rb+");
    fscanf(fd, "%d", &maxScore);

    //防止玩家从文件更改最高分信息的一个小处理
    if(maxScore % 5 != 0)
        maxScore = 0;

    //初始化地图
    for(int i=0; i<=length+1; i++)
        map[i][0] = map[i][length+1] = map[0][i] = map[length+1][i] = 1;

    snake = new Snake(this);

    foodY = foodX = 0;
    while(map[foodX][foodY] != 0)
    {
        foodX = rand()%length+1;
        foodY = rand()%length+1;
    }
    map[foodX][foodY] = 2;
}

void Board::makeFood()
{
    foodY = foodX = 0;
    while(map[foodX][foodY] != 0)
    {
        foodX = rand()%length+1;
        foodY = rand()%length+1;
    }
    map[foodX][foodY] = 2;
}

bool Board::isEnd()
{
    int type = snake->detect();
    if(type == 1)
        snake->toNext();
    else if(type == 2)
    {
        snake->eat();
        makeFood();
        score += 5;
        if(atime > 5)
            atime -= 5;
        //cout<<atime<<endl;
    }
    else
    {
        //如果游戏结束，保存最大值到文件
        FILE *fd =fopen("score.bin","wb+");
        fprintf(fd, "%d\n", maxScore);
        fclose(fd);
        return true;
    }
    return false;
}
