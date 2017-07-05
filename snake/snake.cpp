#include "snake.h"
#include "board.h"

Snake::Snake(Board *_board)
{
    board = _board;
    len = 2;
    dx = 0;
    dy = 1;

    for(int i=0; i<=len; i++)
    {
        s[i][0] = board->length/2;
        s[i][1] = board->length/2-len+i;
        board->map[ s[i][0] ][ s[i][1] ] = 1;
    }
}

void Snake::eat()
{
    len++;
    s[len][0] = s[len-1][0] + dx;
    s[len][1] = s[len-1][1] + dy;
    board->map[ s[len][0] ][ s[len][1] ] = 1;
}

int Snake::detect()
{
    int tx = s[len][0] + dx;
    int ty = s[len][1] + dy;
    if(tx > 0 && tx <= board->length && ty > 0 && ty <= board->length)
    {
        if(board->map[tx][ty] == 2)
            return 2;
        else if(board->map[tx][ty] == 0)
            return 1;
    }
    return 0;
}

void Snake::toNext()
{
    board->map[ s[0][0]] [ s[0][1] ] = 0;
    for(int i=0; i<len; i++)
    {
        s[i][0] = s[i+1][0];
        s[i][1] = s[i+1][1];
    }
    s[len][0] += dx;
    s[len][1] += dy;

    board->map[ s[len][0] ] [ s[len][1] ] = 1;
}

void Snake::turnUp()
{
    dx = -1;
    dy = 0;
}

void Snake::turnDown()
{
    dx = 1;
    dy = 0;
}

void Snake::turnLeft()
{
    dx = 0;
    dy = -1;
}

void Snake::turnRight()
{
    dx = 0;
    dy = 1;
}
