#include "myscroll.h"

MYSCROLL::MYSCROLL(QWidget *parent):QLabel(parent)
{
    max=100;
    num=0;
}

MYSCROLL::~MYSCROLL()
{
    ;
}

void MYSCROLL::paintEvent(QPaintEvent *event)
{
    if(event){}
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect;
    rect=QRect(0,6,this->width()-2,6+3);
    painter.drawRoundedRect(rect,5,5);
    int i=((num)/(max*1.0))*this->width();
    if(i<0)
        i=0;
    if(this->width()-i<19)
        i=this->width()-19;
    QBrush brush;
    brush.setColor(QColor(90,100,110,255));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    rect=QRect(i,1,18,18);
    painter.drawEllipse(rect);

}

void MYSCROLL::mouseMoveEvent(QMouseEvent *ev)
{
    int x=ev->x()-8;
    if(x<0)
        x=0;
    num=((x)/((this->width())*1.0))*max;
    if(num<1)
        num=1;
    if(num>max)
        num=max;
    emit ratioChange(num);
    this->repaint();
}

void MYSCROLL::changeRatio(int Num, int Max)
{
    max=Max;
    num=Num;
    this->repaint();
}
