#ifndef SNAKE_H
#define SNAKE_H

class Board;

class Snake
{
public:
    int len;
    int s[10000][2];
    int dx, dy;
    Board *board;

    Snake(Board *);
    void eat();
    int detect();
    void toNext();
    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();
};

#endif // SNAKE_H