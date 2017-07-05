#include "mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <QMessageBox>
#include "block.h"

using namespace std;

MainWindow::MainWindow(Board *board, QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("S.Y.俄罗斯方块");
    this->board = board;
    flag = 0;
    //初始化定时器
    timer = new QTimer(this);
    timer->setInterval(board->time);
    //为定时器设置连接函数
    connect(timer, &QTimer::timeout, this, &MainWindow::timerEvent);

    timer->start();
    resize(380, 440);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::lightGray);

    //绘制地图
    for(int i=0; i<=board->height+1; i++)
    {
        for(int j=0; j<=board->width+1; j++)
        {
            char ch = board->map[i][j];
            if(ch == '@')
            {
                painter.setBrush(Qt::lightGray);
                painter.drawRect(j*20, i*20, 20, 20);
            }
            else if(ch != '#')
            {
                painter.setBrush(board->block->COLOR[ch-'0']);
                painter.drawRect(j*20, i*20, 20, 20);
            }
        }
    }

    for(int i=0; i<=board->width+8; i++)
    {
        painter.setBrush(Qt::lightGray);
        painter.drawRect(i*20, 0, 20, 20);
    }
    for(int i=board->width+2; i<=board->width+8; i++)
    {
        painter.setBrush(Qt::lightGray);
        painter.drawRect(i*20, 20*(board->height+1), 20, 20);
        painter.drawRect(i*20, 7*20, 20, 20);
    }

    for(int i=0; i<=board->height+1; i++)
    {
        painter.setBrush(Qt::lightGray);
        painter.drawRect(20*(board->width+8), i*20, 20, 20);
    }

    //绘制下一个块的提示
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            int ch = board->block->BLOCKS[board->block->nextType][i][j];
            if(ch != '#')
            {
                painter.setBrush(board->block->COLOR[ch-'0']);
                painter.drawRect((j+board->width+3)*20, (i+2)*20, 20, 20);
            }
        }

    //绘制当前正在下落的块
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            int tx = board->block->x + i;
            int ty = board->block->y + j;
            if(tx<1 || tx > board->height || ty < 1 || ty > board->width)
                continue;
            int ch = board->block->BLOCKS[board->block->type][i][j];
            if(ch != '#')
            {
                painter.setBrush(board->block->COLOR[ch-'0']);
                painter.drawRect(ty*20, tx*20, 20, 20);
            }
        }

    //绘制分数信息
    QFont font;
    font.setPointSize(26);
    painter.setFont(font);
    painter.setPen(Qt::blue);

    char s[10];
    sprintf(s, "%3d", board->maxScore);
    painter.drawText(board->width*20+60, 10*20, "最高分");
    painter.drawText(board->width*20+60, 13*20, s);

    sprintf(s, "%3d", board->score);
    painter.drawText(board->width*20+60, 16*20, "当前分");
    painter.drawText(board->width*20+60, 18*20, s);
}

void MainWindow::timerEvent()
{
    //碰撞检测符合条件则下落
    if(board->block->detect(1))
        board->block->moveDown();
    else
    {
        //否则暂停并弹窗提示
        timer->stop();
        board->confirm();
        timer->setInterval(board->time);
        if(board->isEnd())
        {
            timer->stop();
            //重玩
            if (QMessageBox::Yes ==
                    QMessageBox::question(this, tr("提醒"), tr("游戏结束，再来一把吧?"),
                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
            {
                QMessageBox::information(this, tr("提醒"), tr("哈哈，准备好了吗"));

                board->block->toNext();
                board->score = 0;

                //初始化地图
                for(int i=0; i<=board->height+1; i++)
                    for(int j=0; j<=board->width+1; j++)
                        board->map[i][j] = '#';
                for(int i=1; i<=board->height+1; i++)
                    board->map[i][0] = board->map[i][board->width+1] = '@';
                for(int i=1; i<=board->width; i++)
                    board->map[board->height+1][i] = '@';

                board->time = 200;
                timer->setInterval(board->time);

            }
            //退出
            else
            {
                QMessageBox::information(this, tr("Hmmm..."), tr("下次见，回车我就滚蛋了！"));
                exit(1);
            }
        }
        timer->start();
    }
    //更新界面
    this->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //回车键暂停游戏
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        timer->stop();
        flag = 1;
        QMessageBox::information(this, tr("提醒"), tr("回到游戏"));
        flag = 0;
        timer->start();
    }

    //若处在暂停状态则忽略其他的按键
    if(flag)
        return;

    if(event->key() == Qt::Key_Up)
    {
        if(board->block->detect(0))
            board->block->moveUp();
    }
    else if(event->key() == Qt::Key_Down)
    {
        if(board->block->detect(1))
            board->block->moveDown();
    }
    else if(event->key() == Qt::Key_Left)
    {
        if(board->block->detect(2))
            board->block->moveLeft();
    }
    else if(event->key() == Qt::Key_Right)
    {
        if(board->block->detect(3))
            board->block->moveRight();
    }
    //更新界面
    this->update();
}
