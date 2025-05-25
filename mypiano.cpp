#include "mypiano.h"

MYPIANO::MYPIANO(QWidget *parent) : QLabel(parent)
{
    ;
}

MYPIANO::~MYPIANO()
{
    ;
}

void MYPIANO::paintEvent(QPaintEvent *event)
{
    if(event){}
    QPainter painter(this);
    QLine line;
    QPen pen;
    QRect rect=QRect(0,0,this->width(),this->height());
    QColor light=QColor(255,255,255,touming);
    QColor black=QColor(0,0,0,touming);
    painter.fillRect(rect,light);
    for(int i=1;i<=36;i++)
    {
        QPoint left=QPoint(0,(i-1)*(this->height()/36.0));
        QPoint right=QPoint(this->width()*0.5,i*(this->height()/36.0));
        rect=QRect(left,right);
        switch (i%12)
        {

        case 2:painter.fillRect(rect,black);break;

        case 4:painter.fillRect(rect,black);break;


        case 7:painter.fillRect(rect,black);break;

        case 9:painter.fillRect(rect,black);break;

        case 11:painter.fillRect(rect,black);break;

        }
        //******************************************横线
        pen.setWidth(1);
        pen.setColor(QColor(200,200,200));
        painter.setPen(pen);
        if(i==5||i==12||i==17||i==24||i==29)
            line=QLine(0,(this->height()/36.0)*(i),this->width(),(this->height()/36.0)*i);
        else
        line=QLine(this->width()*0.5,(this->height()/36.0)*(i),this->width(),(this->height()/36.0)*i);
        painter.drawLine(line);

    }
}
