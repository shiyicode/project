#include "block.h"
#include "board.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <QPainter>

using namespace std;

Block::Block(Board *board)
{
    this->board = board;
    x = -3;
    y = 4;

    //随机数确定第一个块的类型
    srand((unsigned) time(NULL));
    type = rand()%19;
    nextType = rand()%19;

    //读入方块类型
    freopen("block.bin", "rb", stdin);
    for(int i=0; i<19; i++)
    {
        for(int j=0; j<4; j++)
            cin>>BLOCKS[i][j];
    }

    //next数组模拟指向，用于方块旋转功能
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            NEXT[i*4+j] = i*4+j+1;
        NEXT[i*4+3] = i*4;
    }
    for(int i=12; i<18; i+=2)
    {
        NEXT[i] = i+1;
        NEXT[i+1] = i;
    }
    NEXT[18] = 18;

    //设置每种方块对应的颜色
    COLOR[1] = Qt::blue;
    COLOR[2] = Qt::darkBlue;
    COLOR[3] = Qt::yellow;
    COLOR[4] = Qt::magenta;
    COLOR[5] = Qt::darkMagenta;
    COLOR[6] = Qt::cyan;
    COLOR[7] = Qt::red;
}

//改变块为下一个块，并随机更新下一个块类型
void Block::toNext()
{
    x = -3;
    y = 4;
    type = nextType;
    nextType = rand()%19;
}

//旋转
void Block::moveUp()
{
    type = NEXT[type];
}

//加速向下
void Block::moveDown()
{
    x++;
}

//左移
void Block::moveLeft()
{
    y--;
}

//右移
void Block::moveRight()
{
    y++;
}

//碰撞检测
bool Block::detect(int flag)
{
    int nextX, nextY, nextType;
    switch(flag)
    {
        case 0: nextX = x; nextY = y; nextType = NEXT[type]; break;
        case 1: nextX = x+1; nextY = y; nextType = type; break;
        case 2: nextX = x; nextY = y-1; nextType = type; break;
        case 3: nextX = x; nextY = y+1; nextType = type; break;
    }

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            int tx = nextX+i;
            int ty = nextY+j;
            if(tx < 0 || tx > board->height+1 || ty < 0 || ty > board->width+1)
                continue;
            if(BLOCKS[nextType][i][j] != '#' && (ty == 0 || ty == board->width+1))
                return false;
            if(BLOCKS[nextType][i][j] != '#' && board->map[tx][ty] != '#')
                return false;
        }
    return true; 
}
