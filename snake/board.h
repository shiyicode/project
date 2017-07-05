#ifndef BOARD_H
#define BOARD_H

#include "snake.h"
class Board
{
public:
    int score;//当前分数
    int maxScore;//最高分
    int atime;//每次下落的间隔时间
    int length;//地图边长
    int foodX;//食物所在坐标
    int foodY;
    Snake *snake;//蛇
    int map[100][100];//保存地图信息

    Board(int);
    void makeFood();
    bool isEnd();
};

#endif // BOARD_H