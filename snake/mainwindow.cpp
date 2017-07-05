#include "mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("S.Y.贪吃蛇");
    board = new Board(20);
    flag = 0;
    isPress = false;
    //初始化定时器
    timer = new QTimer(this);
    timer->setInterval(board->atime);
    //为定时器设置连接函数
    connect(timer, &QTimer::timeout, this, &MainWindow::timerEvent);

    timer->start();
    resize(800, 800);

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::lightGray);

    //绘制地图
    painter.setBrush(Qt::white);
    for(int i=0; i<=board->length+1; i++)
    {
        painter.drawRect(0*20, i*20, 20, 20);
        painter.drawRect((board->length+1)*20, i*20, 20, 20);
        painter.drawRect(i*20, 0*20, 20, 20);
        painter.drawRect(i*20, (board->length+1)*20, 20, 20);
    }

    //绘制蛇身
    painter.setBrush(Qt::white);
    for(int i=0; i<board->snake->len; i++)
        painter.drawRect(board->snake->s[i][1]*20, board->snake->s[i][0]*20, 20, 20);

    //绘制蛇头
    painter.setBrush(Qt::darkGreen);
    painter.drawRect(board->snake->s[board->snake->len][1]*20,
            board->snake->s[board->snake->len][0]*20, 20, 20);

    //绘制食物
    painter.setBrush(Qt::blue);
    painter.drawRect(board->foodY*20, board->foodX*20, 20, 20);

    //绘制分数信息
    QFont font;
    font.setPointSize(26);
    painter.setFont(font);
    painter.setPen(Qt::blue);

    char s[10];
    sprintf(s, "%3d", board->maxScore);
    painter.drawText((board->length+3)*20+60, 10*20, "最高分");
    painter.drawText((board->length+3)*20+60, 13*20, s);

    sprintf(s, "%3d", board->score);
    painter.drawText((board->length+3)*20+60, 16*20, "当前分");
    painter.drawText((board->length+3)*20+60, 18*20, s);
}

void MainWindow::timerEvent()
{
    timer->setInterval(board->atime);
    timer->start();
    if(board->isEnd())
    {
        timer->stop();
        timer->setInterval(board->atime);
        if (QMessageBox::Yes ==
            QMessageBox::question(this, tr("提醒"), tr("游戏结束，再来一把吧?"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
        {
            QMessageBox::information(this, tr("提醒"), tr("哈哈，准备好了吗"));
            board = new Board(20);
            timer->setInterval(board->atime);
            timer->start();
        }
        //退出
        else
        {
            QMessageBox::information(this, tr("Hmmm..."), tr("下次见，回车我就滚蛋了！"));
            exit(1);
        }
    }
    isPress = false;

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

    if(isPress)
        return;

    if(event->key() == Qt::Key_Up)
    {
        if(!(board->snake->dx == 1 && board->snake->dy == 0))
        {
            board->snake->turnUp();
            isPress = true;
        }
    }
    else if(event->key() == Qt::Key_Down)
    {
        if(!(board->snake->dx == -1 && board->snake->dy == 0))
        {
            board->snake->turnDown();
            isPress = true;
        }
    }
    else if(event->key() == Qt::Key_Left)
    {
        if(!(board->snake->dx == 0 && board->snake->dy == 1))
        {
            board->snake->turnLeft();
            isPress = true;
        }
    }
    else if(event->key() == Qt::Key_Right)
    {
        if(!(board->snake->dx == 0 && board->snake->dy == -1))
        {
            board->snake->turnRight();
            isPress = true;
        }
    }

    //更新界面
    this->update();
}
