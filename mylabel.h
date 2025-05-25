#ifndef MYLABEL_H
#define MYLABEL_H

#include <iostream>
#include <fstream>
#include <tchar.h>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <cmath>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFileDialog>
#include <QCoreApplication>
#include <QTimer>
#include <QMessageBox>

using namespace std;


typedef struct data
{

    char tune_1=100;
    char timbre_1=100;

    char tune_2=100;
    char timbre_2=100;

    char tune_3=100;
    char timbre_3=100;
}DATA;

typedef struct LinkList
{
    DATA data;
    LinkList *next=NULL;
}LinkNode,*LinkListp;

class MYLABEL : public QLabel
{
    Q_OBJECT
public:
    explicit MYLABEL(QWidget *parent = nullptr);
    ~MYLABEL();
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *event)override;
    void keyPressEvent(QKeyEvent *ev) override;
    void keyReleaseEvent(QKeyEvent *ev) override;
    bool eventFilter(QObject *watched, QEvent *event)override;
    void interFaceScrolling(int distance);
    QString openFile();
    QString saveFile();
    void readData();
    void writeData();
    void createNullData(LinkNode *head);
    void dataeditorIn(int timbre,QMouseEvent *ev);
    void dataeditorOut(int timbre, QPainter *painter);
    void timerstart();//开启计时器
    void timerstop();//停止计时器
    LinkListp getNowdata();//获取最左边的数据
    void settune(int yindiao);
    void settimbre(int yinshe);
    int getLie();
private:
    int dataX,dataY,dataZ,dataFace;
    int tune=12;
    int timbre=48;
    int linkLong;
    int datalong;
    int max;
    int Lie;
    int PianYi;
    int Chang;
    int key;
    bool mousePress;
    bool keyPress;
    bool isplay;
    bool mouseEnt;
    bool isHorizontsl;
    bool isVertical;
    QPoint mousePressPos;
    QPoint mouseReleasePos;
    QPoint mouseNowPos;
    QPoint dataRowColumn;
    QPoint heightLightPos;
    QTimer *timer;
    LinkNode *head;
    LinkListp nowlieData;
private:                                 /*FILE*/
    QString fileName;
    QString savefileName;
private slots:
    void ratioChange(int num);
    void playmusic();//播放
public:
    void setdataFace(int face);
    void setdataX(int X);
    void setdataY(int Y);
    void setdataZ(int Z);
signals:
    void changeRatio(int Num,int Max);
    void stopplay();
    void p_playMusic();
    void sizeadd();

};

#endif // MYLABEL_H
