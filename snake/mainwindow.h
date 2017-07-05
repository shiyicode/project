#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <board.h>

class QPaintEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool flag;//判断是否暂停状态
    bool isPress;//控制按键频率
    QTimer *timer;//定时器
    Board *board;//游戏所用地图类

    MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);//绘制界面
    void keyPressEvent(QKeyEvent *);//键盘事件处理

signals:

public slots:
    void timerEvent();//定时事件

private:
};

#endif // MAINWINDOW_H