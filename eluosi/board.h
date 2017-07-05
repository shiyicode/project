#ifndef BOARD_H
#define BOARD_H

#include "block.h"
class Block;

class Board
{
public:
    int score;//当前分数
    int maxScore;//最高分
    int time;//每次下落的间隔时间
    int width;//地图宽
    int height;//地图高
    Block *block;//下落的方块
    char map[100][100];//保存地图信息

    Board(int, int);
    void confirm();//将下落到底的块更新到map
    bool isEnd();//判断是否游戏结束
};

#endif // BOARD_H