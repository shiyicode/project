#ifndef BLOCK_H
#define BLOCK_H

#include "board.h"
#include <QPainter>
class Board;

class Block
{
public:
    char BLOCKS[20][5][5];//各个类型的方块
    int NEXT[20];//模拟指向用于方块旋转
    Qt::GlobalColor COLOR[20];//各个类型方块的颜色
    int x;//块重心起始坐标
    int y;
    int type;//块id
    int nextType;//下一个块id
    Board *board;
    Block(Board *);//构造函数
    void toNext();//更改块id
    void moveUp();//变形
    void moveRight();//加速
    void moveLeft();//左移
    void moveDown();//右移
    bool detect(int);//碰撞检测
};

#endif // BLOCK_H