#include "mylabel.h"

MYLABEL::MYLABEL(QWidget *parent) : QLabel(parent)
{
    dataX=0;dataY=0;dataZ=0;dataFace=1;
    isHorizontsl=true;
    isVertical=false;
    Lie=1;
    PianYi=0;
    Chang=40;
    max=100000;//数据最大长度
    datalong=100;//数据长度
    linkLong=0;
    keyPress=false;
    mousePress=false;
    this->setMouseTracking(true);//启用鼠标跟踪
    //!this->grabKeyboard();//捕获键盘事件//***该函数会抓取所有键盘事件,导致其它组件无法输入
    head=new LinkNode;
    head->next=NULL;
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(playmusic()));
    isplay=false;
    this->installEventFilter(this);//注册按钮事件，也即是将按钮加入事件过滤器
    mouseEnt=false;
}

MYLABEL::~MYLABEL()
{
    LinkListp q,p;
    q=head;
    p=head->next;
    while(1)
    {
        delete q;
        q=p;
        if(p==NULL)
            break;
        p=p->next;
    }
}

void MYLABEL::paintEvent(QPaintEvent *event)//绘图事件
{
    if(event){};
    //******************************************初始化
    int nowpos=PianYi;
    int nowlie=Lie;
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    QLine line(nowpos,0,nowpos,this->height());
    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
    //******************************************竖线
    if(!isplay)
    {
        pen.setWidth(1);
        pen.setColor(QColor(0,0,0));
        painter.setPen(pen);
        while(nowpos<this->width())
        {
            painter.drawLine(line);
            nowpos+=Chang;
            line=QLine(nowpos,0,nowpos,this->height());
            if(nowlie>=datalong)
                datalong=nowlie;
            if(datalong>max)
                datalong=max;
            nowlie++;
            if(linkLong<datalong)
                createNullData(head);
        }
    }
    //******************************************高亮方格
    if(mouseEnt)
    {
        pen.setWidth(3);
        pen.setColor(QColor(79, 173, 143,200));
        painter.setPen(pen);
        QRect rect(heightLightPos,QPoint(heightLightPos.x()+Chang,(dataRowColumn.y()+1)*(this->height()/36.0)));
        painter.drawRect(rect);
    }
    //******************************************方块
    if(mouseNowPos.y()<(this->height()/36.0)*12)
        tune=0;
    if(mouseNowPos.y()>(this->height()/36.0)*12&&mouseNowPos.y()<(this->height()/36.0)*24)
        tune=12;
    if(mouseNowPos.y()>(this->height()/36.0)*24)
        tune=24;
    dataeditorOut(timbre,&painter);//数据可视化
    emit sizeadd();
}

void MYLABEL::mousePressEvent(QMouseEvent *ev)//鼠标按下事件
{
    mousePress=true;
    mousePressPos=ev->pos();
}

void MYLABEL::mouseReleaseEvent(QMouseEvent *ev)//鼠标释放事件
{
    mousePress=false;
    mouseReleasePos=ev->pos();
    int yidong=mouseReleasePos.x()-mousePressPos.x();
    interFaceScrolling(yidong);//界面滚动
    if(abs(mousePressPos.x()-mouseReleasePos.x())<4&&abs(mousePressPos.y()-mouseReleasePos.y())<4&&!isplay)
        dataeditorIn(timbre,ev);//可视化输入数据
    if(isplay==true)
    {
        isplay=false;
        emit stopplay();
    }
    this->repaint();
}

void MYLABEL::mouseMoveEvent(QMouseEvent *ev)//鼠标移动事件
{
    //如果鼠标按下
    if(mousePress)
    {
        int temp=PianYi;
        int temp2=Lie;
        //******************************************
        int yidong=ev->x()-mousePressPos.x();
        interFaceScrolling(yidong);
        mouseNowPos=ev->pos();
        if(mouseNowPos.x()<0)
            mouseNowPos.setX(0);
        if(mouseNowPos.x()>this->width())
            mouseNowPos.setX(this->width());
        if(mouseNowPos.y()<0)
            mouseNowPos.setY(0);
        if(mouseNowPos.y()>this->height())
            mouseNowPos.setY(this->height()-1);
        dataRowColumn.setY(mouseNowPos.y()/(this->height()/36.0));
        dataRowColumn.setX(Lie+(mouseNowPos.x()-PianYi)/Chang);
        this->repaint();
        //******************************************恢复
        PianYi=temp;//恢复原来的偏移量
        Lie=temp2;//恢复原来的列
    }
    if(!mousePress)
    {
        mouseNowPos=ev->pos();
        dataRowColumn.setY(mouseNowPos.y()/(this->height()/36.0));
        dataRowColumn.setX(Lie+(mouseNowPos.x()-PianYi)/Chang);
        interFaceScrolling(0);
        if(!isplay)
        this->repaint();
    }
}

void MYLABEL::wheelEvent(QWheelEvent *event)//鼠标滚轮事件
{
    if(key==Qt::Key_Z)
    {
        if(event->delta()>0)
        {
            if(Chang+10<200)
                Chang+=5;
        }
        if(event->delta()<0)
        {
            if(Chang-10>20)
                Chang-=5;
        }
    }
    else
        interFaceScrolling(event->delta()/abs(event->delta())*Chang);
    //******************************************
    dataRowColumn.setX(Lie+(mouseNowPos.x()-PianYi)/Chang);
    //******************************************
    interFaceScrolling(0);
    //******************************************
    this->repaint();
}

void MYLABEL::keyPressEvent(QKeyEvent *ev)//键盘按下事件
{
    keyPress=true;
    key=ev->key();
    if(key==Qt::Key_Z)
        setCursor(QCursor(QPixmap(":/image/search.png").scaled\
                          (25,25,Qt::KeepAspectRatio,Qt::SmoothTransformation)));//设置光标
    else
        setCursor(Qt::ArrowCursor);
}

void MYLABEL::keyReleaseEvent(QKeyEvent *ev)//键盘释放事件
{
    keyPress=false;
    key=ev->key();
}

bool MYLABEL::eventFilter(QObject *watched, QEvent *event)//事件过滤器
{
    if(watched == this)
        {
            if(event->type() == QEvent::Enter)
            {
                //qDebug()<<tr("监控到按钮事件，鼠标进入按钮事件");
                this->grabKeyboard();//!抓取程序内全部键盘
                mouseEnt=true;
                return true;
            }
            else if(event->type() == QEvent::Leave)
            {
                //qDebug()<<tr("监控到按钮事件，鼠标离开按钮事件");
                this->releaseKeyboard();//!释放键盘抓取
                mouseEnt=false;
                return true;
            }
            else if(event->type() == QEvent::MouseButtonPress)
            {
                //qDebug()<<tr("监控到按钮事件，鼠标摁下按钮事件");
                return QLabel::eventFilter(watched, event);
            }
            else if(event->type() == QEvent::MouseButtonRelease)
            {
                //qDebug()<<tr("监控到按钮事件，鼠标释放按钮事件");
                return QLabel::eventFilter(watched, event);
            }
        }
        return QLabel::eventFilter(watched, event);
}

void MYLABEL::interFaceScrolling(int distance)//界面滚动
{
    if(distance<=0)
    {
        Lie-=(PianYi+distance)/Chang;
        PianYi=(PianYi+distance)%Chang;
    }
    if(distance>0)
    {
        PianYi=((PianYi+distance)%Chang-Chang)%Chang;
        Lie+=(PianYi-distance)/Chang;
    }
    //******************************************
    if(Lie<1)
    {
        Lie=1;
        PianYi=0;
    }
    if(Lie>=max-this->width()/Chang)
    {
        Lie=max-this->width()/Chang;
        PianYi=this->width()-(this->width()/Chang+1)*Chang;
    }
    if(isplay)
    {
        if(Lie>=datalong-this->width()/Chang)
        {
            Lie=datalong-this->width()/Chang;
            PianYi=this->width()-(this->width()/Chang+1)*Chang;
        }
    }
    //******************************************高亮方块
    int x,y;
    x=mouseNowPos.x()-(mouseNowPos.x()-PianYi)%Chang;
    y=dataRowColumn.y()*(this->height()/36.0);
    heightLightPos=QPoint(x,y);
    //******************************************信号
    emit changeRatio(Lie-1,datalong-this->width()/Chang-1);
}

QString MYLABEL::openFile()//打开文件
{
    QString filename=QFileDialog::getOpenFileName\
            (this,"打开",QCoreApplication::applicationDirPath(),"*mobj");
    fileName=filename;
    readData();
    return filename;
}

QString MYLABEL::saveFile()//保存数据
{
    QString filename=QFileDialog::getSaveFileName\
            (this,"存储为",QCoreApplication::applicationDirPath(),"*mobj");
    savefileName=filename;
    writeData();
    return filename;
}

void MYLABEL::readData()//读入数据
{
    char* a;
    QByteArray ba=fileName.toLocal8Bit();
    a=ba.data();
    ifstream op;
    if(fileName!=NULL)
    {
        op.open(a,ios::in|ios::binary);
    }
    if(!op.is_open())//打开失败
        QMessageBox::warning(this,tr("错误"),tr("你未选择文件或readData未打开"));
    else
    {
        char b[500];
        op.seekg(10);
        op.read((char*)&dataX,sizeof (int));
        op.read(b,1);
        op.read((char*)&dataY,sizeof (int));
        op.read(b,1);
        op.read((char*)&dataZ,sizeof (int));
        op.read(b,10);
        op.read((char*)&dataFace,sizeof (int));
        int size;
        {
            int i=op.tellg();
            op.seekg(0,ios::end);
            int m=op.tellg();
            size=m-i;
            op.seekg(i);
        }
        if(size%6==0)
        {
            LinkListp q,p,u;
            q=head;
            p=head->next;
            for(int i=1;i<=size/6;i++)
            {
                if(p==NULL)
                {
                    DATA x;
                    op.read((char*)&x.tune_1,1);
                    op.read((char*)&x.timbre_1,1);
                    op.read((char*)&x.tune_2,1);
                    op.read((char*)&x.timbre_2,1);
                    op.read((char*)&x.tune_3,1);
                    op.read((char*)&x.timbre_3,1);
                    u=new LinkNode;
                    u->data=x;
                    u->next=q->next;
                    q->next=u;
                    p=u->next;
                    linkLong++;
                }
                else
                {
                    op.read((char*)&p->data,6);
                    p=p->next;
                }
                q=q->next;
            }
        }
    }
}

void MYLABEL::writeData()//写出数据
{
    char *a;
    ofstream op;
    if(savefileName!=NULL)
    {
        savefileName=savefileName+".mobj";
        QByteArray ba=savefileName.toLocal8Bit();
        a=ba.data();
        op.open(a,ios::out|ios::binary);
    }
    if(!op.is_open())//打开失败
        QMessageBox::warning(this,tr("错误"),tr("你未选择文件或writeData未打开"));
    else
    {
        char fileData[19]={'b','e','g','i','n','_','p','o',\
                           's','_','d','a','t','a','_','f','a','c','e'};
        op.write(fileData,10);
        op.write((char*)&dataX,sizeof (int));
        op.write(&fileData[5],1);
        op.write((char*)&dataY,sizeof (int));
        op.write(&fileData[5],1);
        op.write((char*)&dataZ,sizeof (int));
        op.write(&fileData[5],1);
        op.write(&fileData[10],9);
        op.write((char*)&dataFace,sizeof (int));
        //************************************************
        LinkListp q;
        q=head->next;
        while(q)
        {
            op.write((char*)&q->data,6);
            q=q->next;
        }
    }
    op.close();
}

void MYLABEL::createNullData(LinkNode *head)//在链表结尾创建新节点
{
    DATA x;
    x.tune_1=100;x.tune_2=100;x.tune_3=100;
    x.timbre_1=100;x.timbre_2=100;x.timbre_3=100;
    LinkListp q,p,u;
    u=new LinkNode;
    u->data=x;
    q=head;
    p=head->next;
    while(p)
    {
        q=q->next;
        p=p->next;

    }
    u->next=q->next;
    q->next=u;
    linkLong++;
}

void MYLABEL::dataeditorIn(int timbre,QMouseEvent *ev)//可视化输入数据
{
    int x=dataRowColumn.x();
    int y=dataRowColumn.y();
    int count=0;
    LinkListp q,p;
    q=head;
    p=head->next;
    while(p)
    {
        q=q->next;
        p=p->next;
        count++;
        if(count>=x)
            break;
    }
    if(ev->button()==Qt::LeftButton)
    {
        if(q->data.tune_1==100)
        {
            q->data.tune_1=y;
            q->data.timbre_1=timbre;
        }
        else if(q->data.tune_2==100)
        {
            q->data.tune_2=y;
            q->data.timbre_2=timbre;
        }
        else if(q->data.tune_3==100)
        {
            q->data.tune_3=y;
            q->data.timbre_3=timbre;
        }
        else
        {
            q->data.tune_1=q->data.tune_2;
            q->data.timbre_1=q->data.timbre_2;
            q->data.tune_2=q->data.tune_3;
            q->data.timbre_2=q->data.timbre_3;
            q->data.tune_3=y;
            q->data.timbre_3=timbre;
        }
    }
    if(ev->button()==Qt::RightButton)
    {
        if(q->data.tune_1==y)
        {
            q->data.tune_1=q->data.tune_2;
            q->data.timbre_1=q->data.timbre_2;
            q->data.tune_2=q->data.tune_3;
            q->data.timbre_2=q->data.timbre_3;
            q->data.tune_3=100;
            q->data.timbre_3=100;
        }
        else if(q->data.tune_2==y)
        {
            q->data.tune_2=q->data.tune_3;
            q->data.timbre_2=q->data.timbre_3;
            q->data.tune_3=100;
            q->data.timbre_3=100;
        }
        else if(q->data.tune_3==y)
        {
            q->data.tune_3=100;
            q->data.timbre_3=100;
        }
    }
}

void MYLABEL::dataeditorOut(int timbre, QPainter *painter)//数据可视化
{
    if(timbre){}
    int count=0;
    LinkListp q,p;
    q=head;
    p=head->next;
    while(p)
    {
        q=q->next;
        p=p->next;
        count++;
        if(count>=Lie)
            break;
    }
    nowlieData=q;
    int pianyi=PianYi;
    QBrush brush;
    for(int i=0;i<=this->width()/Chang+1;i++)
    {
        QPoint left=QPoint(pianyi+1,(this->height()/36.0)*q->data.tune_1+2);
        QPoint right=QPoint(pianyi+Chang-2,left.y()+(this->height()/36.0)-4);
        QRect rect(left,right);
        QPen pen;
        pen.setWidth(0);
        painter->setPen(pen);
        if(q->data.timbre_1>=36&&q->data.timbre_1<44)
        brush.setColor(QColor(255, 242, 0,85));
        else if(q->data.timbre_1>=44&&q->data.timbre_1<52)
        brush.setColor(QColor(0, 162, 232,85));
        else if(q->data.timbre_1>=52&&q->data.timbre_1<60)
        brush.setColor(QColor(34, 177, 76,85));
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(brush);
        if(q->data.tune_1<36)
        painter->drawRoundedRect(rect,4,4);/*低音*/
        left=QPoint(pianyi+1,(this->height()/36.0)*q->data.tune_2+2);
        right=QPoint(pianyi+Chang-2,left.y()+(this->height()/36.0)-4);
        rect=QRect(left,right);
        if(q->data.timbre_2>=36&&q->data.timbre_2<44)
        brush.setColor(QColor(255, 242, 0,85));
        else if(q->data.timbre_2>=44&&q->data.timbre_2<52)
        brush.setColor(QColor(0, 162, 232,85));
        else if(q->data.timbre_2>=52&&q->data.timbre_2<60)
        brush.setColor(QColor(34, 177, 76,85));
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(brush);
        if(q->data.tune_2<36)
        painter->drawRoundedRect(rect,4,4);/*中音*/
        left=QPoint(pianyi+1,(this->height()/36.0)*q->data.tune_3+2);
        right=QPoint(pianyi+Chang-2,left.y()+(this->height()/36.0)-4);
        rect=QRect(left,right);
        if(q->data.timbre_3>=36&&q->data.timbre_3<44)
        brush.setColor(QColor(255, 242, 0,85));
        else if(q->data.timbre_3>=44&&q->data.timbre_3<52)
        brush.setColor(QColor(0, 162, 232,85));
        else if(q->data.timbre_3>=52&&q->data.timbre_3<60)
        brush.setColor(QColor(34, 177, 76,85));
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(brush);
        if(q->data.tune_3<36)
        painter->drawRoundedRect(rect,4,4);/*高音*/
        if(p!=NULL)
        {
            q=q->next;
            p=p->next;
        }
        else
        {
            break;
        }
        pianyi+=Chang;
    }
}

void MYLABEL::playmusic()
{
    interFaceScrolling(-Chang);
    emit p_playMusic();
    this->repaint();
}

int MYLABEL::getLie()
{
    return Lie;
}

void MYLABEL::setdataFace(int face)
{
    dataFace=face;
}

void MYLABEL::setdataX(int X)
{
    dataX=X;
}

void MYLABEL::setdataY(int Y)
{
    dataY=Y;
}

void MYLABEL::setdataZ(int Z)
{
    dataZ=Z;
}

void MYLABEL::timerstart()
{
    isplay=true;
    timer->start(50);
}

void MYLABEL::timerstop()
{
    isplay=false;
    timer->stop();
}

LinkListp MYLABEL::getNowdata()
{
    return nowlieData;
}

void MYLABEL::settune(int yindiao)
{
    tune=yindiao;
}

void MYLABEL::settimbre(int yinshe)
{
    timbre=yinshe;
}

void MYLABEL::ratioChange(int num)
{
    Lie=num;
    emit changeRatio(Lie-1,datalong-this->width()/Chang-1);
    this->repaint();
}

