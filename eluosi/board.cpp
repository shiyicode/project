#include "board.h"
#include "block.h"
#include <fstream>
#include <iostream>

using namespace std;

Board::Board(int _height, int _width)
    : height(_height), width(_width)
{
    //初始化块，时间间隔，分数
    block = new Block(this);
    time = 200;
    score = 0;

    //从文件读入最高分
    FILE *fd =fopen("score.bin","rb+");
    fscanf(fd, "%d", &maxScore);

    //防止玩家从文件更改最高分信息的一个小处理
    if(maxScore % 5 != 0)
        maxScore = 0;

    //初始化地图
    for(int i=0; i<=height+1; i++)
        for(int j=0; j<=width+1; j++)
            map[i][j] = '#';
    for(int i=0; i<=height+1; i++)
        map[i][0] = map[i][width+1] = '@';
    for(int i=1; i<=width; i++)
        map[height+1][i] = '@';
}

void Board::confirm()
{
    //将块更新到map
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            int tx = block->x + i;
            int ty = block->y + j;
            if(tx<1 || tx > height || ty < 1 || ty > width)
                continue;
            if(block->BLOCKS[block->type][i][j] != '#')
                map[tx][ty] = block->BLOCKS[block->type][i][j];
        }

    //消去完整的行并计算行个数
    int cnt = 0;
    for(int i=height; i>=1; i--)
    {
        bool flag = false;
        for(int j=1; j<=width; j++)
            if(map[i][j] == '#')
            {
                flag = true;
                break;
            }
        if(flag)
            continue;
        cnt++;
        for(int j=i; j>=1; j--)
            for(int k=1; k<=width; k++)
                map[j][k] = map[j-1][k];
    }

    //每下落一个块加5分
    score += 5;
    //根据同时消去的行的数量指数型记分
    //1-10 2-20 3-40 4-80
    if(cnt)
        score += 10*(1<<cnt);

    //实时更新最大值
    maxScore = std::max(maxScore, score);

    //每下落一个块，时间间隔减2
    time -= 2;
    if(time < 0)
        time = 0;

    //更新块
    block->toNext();
}

bool Board::isEnd()
{
    for(int i=1; i<=width; i++)
        if(map[1][i] != '#')
        {
            //如果游戏结束，保存最大值到文件
            FILE *fd =fopen("score.bin","wb+");
            fprintf(fd, "%d\n", maxScore);
            fclose(fd);
            return true;
        }
    return false;
}
