#include "mywidget.h"

MYWIDGET::MYWIDGET(QWidget *parent) : QWidget(parent)
{
    ;
}

MYWIDGET::~MYWIDGET()
{
    ;
}

void MYWIDGET::paintEvent(QPaintEvent *event)
{
    if(event){}
    QPainter painter(this);
    QPen pen;
    QLine line;
    //******************************************背景
    for(int i=1;i<=36;i++)
    {
        QPoint left=QPoint(0,(i-1)*(this->height()/36.0));
        QPoint right=QPoint(this->width(),i*(this->height()/36.0));
        QRect rect=QRect(left,right);
        QColor light=QColor(56,60,68,touming);
        QColor black=QColor(16,20,28,touming);
        switch (i%12)
        {
        case 1:painter.fillRect(rect,light);break;
        case 2:painter.fillRect(rect,black);break;
        case 3:painter.fillRect(rect,light);break;
        case 4:painter.fillRect(rect,black);break;
        case 5:painter.fillRect(rect,light);break;
        case 6:painter.fillRect(rect,light);break;
        case 7:painter.fillRect(rect,black);break;
        case 8:painter.fillRect(rect,light);break;
        case 9:painter.fillRect(rect,black);break;
        case 10:painter.fillRect(rect,light);break;
        case 11:painter.fillRect(rect,black);break;
        case 0:painter.fillRect(rect,light);break;
        }

    }
    //******************************************粗横线
    pen.setWidth(1);
    pen.setColor(QColor(200,200,200));
    painter.setPen(pen);
    line=QLine(0,this->height()/3,this->width(),this->height()/3);
    painter.drawLine(line);
    line=QLine(0,this->height()/3*2,this->width(),this->height()/3*2);
    painter.drawLine(line);
    //******************************************横线
    pen.setWidth(1);
    pen.setColor(QColor(80,100,80));
    painter.setPen(pen);
    for(int i=1;i<=35;i++)
    {
        if(i==12||i==24)
            continue;
        line=QLine(0,this->height()/36.0*i,this->width(),this->height()/36.0*i);
        painter.drawLine(line);
    }
}

void MYWIDGET::settouming(int tm)
{
    touming=tm;
}
