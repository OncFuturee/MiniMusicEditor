#include "pixelpaint.h"
#include "ui_pixelpaint.h"
#include <QDebug>
PIXELPAINT::PIXELPAINT(QWidget *parent)
    :QMainWindow(parent),ui_Pixe(new Ui::MainWindow)
{
    ui_Pixe->setupUi(this);
    this->resize(960,this->height());
    //!初始界面
    ui_Pixe->groupBox_5->setEnabled(false);
    //!END
    img=new QImage;//!-------img
    imgScaled=new QImage;//!-------imgScaled
    this->setWindowTitle("像素画生成");
    QAction *openFile=new QAction(ui_Pixe->File);
    QAction *tutorial=new QAction(ui_Pixe->File);
    QAction *build=new QAction(ui_Pixe->File);
    openFile->setText("打开图片");
    build->setText("生成lua文件");
    tutorial->setText("教程");
    ui_Pixe->File->addAction(openFile);
    ui_Pixe->File->addAction(build);
    ui_Pixe->menubar->addAction(tutorial);
    connect(openFile,&QAction::triggered,[=](){
        QString filename;
        filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"","images(*.png *.jpg *.jpeg *.bmp *.tiff)"
                                                                 ";;png(*.png);;jpg(*.jpg);;jpeg(*.jpeg)");
        if(!filename.isEmpty())
        {
            if(!(img->load(filename)))
            {
                QMessageBox::information(this,tr("图像打开失败"),tr("图像打开失败!!"));
            }
        }
        *imgScaled=img->scaled(img->width()*scaled,img->height()*scaled,Qt::KeepAspectRatio);
        ui_Pixe->label_7->setPixmap(QPixmap::fromImage(*imgScaled));
        //!change--spinBox--value
        ui_Pixe->spinBox_7->setValue(imgScaled->width());
        ui_Pixe->spinBox_8->setValue(imgScaled->height());
    });
    connect(tutorial,&QAction::triggered,[=](){
        QMessageBox::information(this,tr("教程"),tr("详细教程请查看程序包里的word文档\n"
                                                  "如果你没有此文件,说明该程序经过了第三方转载\n"
                                                  "该程序为免费软件,如果你是付费获得的该软件\n"
                                                  "那么你被骗了"));
    });
    connect(build,&QAction::triggered,[=](){
        ui_Pixe->pushButton->click();
    });
}

PIXELPAINT::~PIXELPAINT()
{
    delete img;
}

void PIXELPAINT::closeEvent(QCloseEvent *event)
{
    if(event){}
    emit pixelpaintClose();
}

void PIXELPAINT::pixelpaintShow()
{
    this->show();
}

void PIXELPAINT::on_horizontalSlider_valueChanged(int value)
{
    scaled=value/100.0;
    ui_Pixe->label_10->setNum(scaled);//!label显示
    if(!img->isNull())
    {
        *imgScaled=img->scaled(img->width()*scaled,img->height()*scaled,Qt::KeepAspectRatio);
        ui_Pixe->label_7->setPixmap(QPixmap::fromImage(*imgScaled));
        ui_Pixe->label_17->setNum(imgScaled->width());
        ui_Pixe->label_18->setNum(imgScaled->height());
    }
    else
    {
        ui_Pixe->label_17->setNum(0);
        ui_Pixe->label_18->setNum(0);
    }
}

void PIXELPAINT::on_comboBox_currentIndexChanged(int index)
{
    if(index==0)
    {
        ui_Pixe->groupBox_5->setEnabled(false);
        ui_Pixe->groupBox_6->setEnabled(true);
    }
    else if(index==1)
    {
        ui_Pixe->groupBox_5->setEnabled(true);
        ui_Pixe->groupBox_6->setEnabled(false);
    }
}

void PIXELPAINT::on_spinBox_7_valueChanged(int arg1)
{
    if(!img->isNull()&&ui_Pixe->spinBox_7->isEnabled())
    {
        *imgScaled=img->scaled(arg1,ui_Pixe->spinBox_8->value());
        ui_Pixe->label_7->setPixmap(QPixmap::fromImage(*imgScaled));
        ui_Pixe->label_17->setNum(imgScaled->width());
        ui_Pixe->label_18->setNum(imgScaled->height());
    }
    else
    {
        ui_Pixe->label_17->setText("NULL");
        ui_Pixe->label_18->setText("NULL");
    }
}

void PIXELPAINT::on_spinBox_8_valueChanged(int arg1)
{
    if(!img->isNull()&&ui_Pixe->spinBox_8->isEnabled())
    {
        *imgScaled=img->scaled(ui_Pixe->spinBox_7->value(),arg1);
        ui_Pixe->label_7->setPixmap(QPixmap::fromImage(*imgScaled));
        ui_Pixe->label_17->setNum(imgScaled->width());
        ui_Pixe->label_18->setNum(imgScaled->height());
    }
    else
    {
        ui_Pixe->label_17->setText("NULL");//333
        ui_Pixe->label_18->setText("NULL");
    }
}

void PIXELPAINT::on_pushButton_clicked()
{
    QString filename;
    filename=QFileDialog::getSaveFileName(this,tr("保存为"),"","*.lua");
    char *a=filename.toLocal8Bit().data();
    if(!filename.isEmpty()&&!img->isNull())//!如果文件名,图片不为空
    {
        int imgx=0;
        int imgy=imgScaled->height()-1;
        int bginx=ui_Pixe->spinBox->value();
        int bginy=ui_Pixe->spinBox_2->value();
        int bginz=ui_Pixe->spinBox_3->value();
        int endx=ui_Pixe->spinBox_4->value();
        int endy=ui_Pixe->spinBox_5->value();
        int endz=ui_Pixe->spinBox_6->value();
        int BUILDX=0,BUILDY=0,BUILDZ=0,BLOCKID=0,BlockData=0;
        double k;
        if(abs(endz-bginz)<abs(endx-bginx))
        {
            if(endx-bginx!=0&&endz-bginz!=0)
                k=(endz-bginz)/((endx-bginx)*1.00);
            else
                k=0;
        }
        else {
            if(endx-bginx!=0&&endz-bginz!=0)
                k=(endx-bginx)/((endz-bginz)*1.00);
            else
                k=0;
        }
        //!***********************************
        //!
        QTemporaryDir muban1(QCoreApplication::applicationDirPath()+"/tempfile");
        muban1.setAutoRemove(true);
        if(muban1.isValid()){
            const QString tempfile = muban1.path()+"/muban1.txt";
            const QString tempfile2 = muban1.path()+"/muban2.txt";
            if(QFile::copy(":/muban/muban1.txt",tempfile)){
                ;
            }
            if(QFile::copy(":/muban/muban2.txt",tempfile2)){
                ;
            }
        }
        //!
        //!***********************************
        ofstream op;
        if(bginy==endy)
            op.open(a,ios::out);
        else
            QMessageBox::warning(this,tr("坐标错误"),tr("起点与终点坐标高度(Y)不同\n或者高度与图片高度不同"));
        ifstream muban;
        string mubanstr;
        if(op.is_open())
        {
            int datanum=1;//data文件标识
            bool stop=false;
            minicolor minicolors[251]={{255,204,188,667,15},{255,171,145,669,1},{255,138,101,670,3},\
                    {255, 112, 67,671,5},{255, 87, 34,672,7},{244, 81, 30,673,9},{230, 74, 25,674,11},\
                    {216, 67, 21,675,13},{191, 54, 12,676,15},{221, 44, 0,678,1},{255, 61, 0,679,3},\
                    {255, 110, 64,680,5},{255, 158, 128,681,7},{255, 227, 224,682,9},{215, 204, 200,669,2},\
                    {188, 170, 164,670,4},{161, 136, 127,671,6},{141, 110, 99,672,8},{121, 85, 72,673,10},\
                    {109, 76, 65,674,12},{93, 64, 55,679,0},{78, 52, 46,672,9},{62, 39, 35,678,2},\
                    {236, 239, 241,679,4},{207, 216, 220,680,6},{144, 164, 174,681,8},{120, 144, 156,682,10},\
                    {0, 0, 0,669,3},{255, 255, 255,667,0},{238, 238, 238,670,5},{224, 224, 224,671,7},\
                    {189, 189, 189,675,0},{158, 158, 158,673,11},{117, 117, 117,674,13},{97, 97, 97,674,0},\
                    {66, 66, 66,677,1},{33, 33, 33,682,0},{96, 125, 139,679,5},{84, 110, 122,680,7},\
                    {55, 71, 79,681,9},{38, 50, 56,682,11},{255, 249, 196,667,12},{255, 245, 157,668,14},\
                    {255, 241, 11,668,7},{255, 238, 88,671,2},{255, 235, 59,672,4},{253, 216, 53,673,6},\
                    {251, 192, 45,674,8},{249, 168, 37,675,10},{245, 127, 23,676,12},{255, 214, 0,677,14},\
                    {255, 234, 0,675,14},{255, 255, 0,680,2},{255, 255, 141,681,4},{255, 252, 221,682,6},\
                    {255, 236, 179,667,13},{255, 224, 130,668,15},{255, 213, 79,670,1},{255, 202, 40,671,3},\
                    {255, 193, 7,672,5},{255, 179, 0,673,7},{255, 160, 0,674,9},{255, 143, 0,675,11},\
                    {255, 111, 0,676,13},{255, 171, 0,677,15},{255, 196, 0,679,1},{255, 215, 64,671,0},\
                    {255, 229, 127,681,5},{255, 244, 213,682,7},{255, 224, 178,667,14},{255, 204, 128,671,10},\
                    {255, 183, 77,670,2},{255, 167, 38,671,4},{255, 152, 0,672,6},{251, 140, 0,673,8},\
                    {245, 124, 0,674,10},{239, 108, 0,668,0},{230, 81, 0,676,14},{255, 109, 0,672,15},\
                    {255, 145, 0,679,2},{255, 171, 64,680,4},{255, 209, 128,681,6},{255, 239, 215,682,8},\
                    {200, 230, 201,667,9},{165, 214, 167,668,11},{129, 199, 132,669,13},{102, 187, 106,670,15},\
                    {76, 175, 80,672,1},{67, 160, 71,673,3},{56, 142, 60,674,5},{46, 125, 50,680,0},\
                    {27, 94, 32,676,9},{0, 200, 83,677,11},{0, 230, 118,678,13},{105, 240, 174,679,15},\
                    {185, 246, 202,681,1},{221, 242, 222,682,3},{220, 237, 200,667,10},{197, 225, 165,668,12},\
                    {174, 213, 129,669,14},{156, 204, 101,680,3},{139, 195, 74,672,2},{124, 179, 66,673,4},\
                    {104, 159, 56,674,6},{85, 139, 47,675,8},{51, 105, 30,676,10},{100, 221, 23,677,12},\
                    {118, 255, 3,678,14},{178, 255, 89,675,7},{204, 255, 144,681,2},{237, 249, 223,682,4},\
                    {240, 244, 195,667,11},{230, 238, 156,668,13},{220, 231, 117,669,15},{212, 225, 87,671,1},\
                    {205, 220, 57,672,0},{192, 202, 51,673,5},{175, 180, 43,674,7},{158, 157, 36,675,9},\
                    {130, 119, 23,676,11},{174, 234, 0,677,13},{198, 255, 0,678,5},{238, 255, 65,680,1},\
                    {244, 255, 129,681,3},{248, 251, 219,682,5},{179, 229, 252,667,6},{129, 212, 250,668,8},\
                    {79, 195, 247,669,10},{41, 182, 246,670,12},{3, 169, 244,671,14},{3, 155, 229,669,5},\
                    {2, 136, 209,674,2},{2, 119, 189,675,4},{1, 87, 155,676,6},{0, 145, 234,677,8},\
                    {0, 176, 255,678,10},{64, 196, 255,679,12},{128, 216, 255,680,14},{217, 243, 255,675,12},\
                    {178, 235, 242,667,7},{128, 222, 234,668,9},{77, 208, 225,669,11},{38, 198, 218,670,13},\
                    {0, 188, 212,671,15},{0, 172, 193,673,1},{0, 151, 167,674,3},{0, 131, 143,675,5},\
                    {0, 96, 100,676,7},{0, 184, 212,677,9},{0, 229, 255,678,11},{24, 255, 255,679,13},\
                    {132, 255, 255,680,15},{209, 245, 249,682,1},{178, 223, 219,667,8},{128, 203, 196,668,10},\
                    {77, 182, 172,669,12},{38, 166, 154,670,14},{0, 150, 136,672,3},{0, 137, 123,673,2},\
                    {0, 121, 107,674,4},{0, 105, 92,675,6},{0, 77, 64,676,8},{0, 191, 165,676,0},\
                    {29, 233, 182,678,12},{100, 255, 218,679,14},{167, 255, 235,674,14},{209, 240, 237,682,2},\
                    {209, 196, 233,667,3},{179, 157, 219,668,5},{149, 117, 205,669,7},{126, 87, 194,670,9},\
                    {103, 58, 183,671,11},{94, 53, 177,672,13},{81, 45, 168,673,15},{69, 39, 160,675,1},\
                    {49, 27, 146,676,3},{98, 0, 234,677,5},{101, 31, 255,678,7},{24, 77, 255,679,9},\
                    {179, 136, 255,680,11},{232, 224, 247,681,13},{197, 202, 233,667,4},{159, 168, 218,668,6},\
                    {121, 134, 203,669,8},{92, 107, 192,670,10},{63, 81, 181,671,12},{57, 73, 171,672,14},\
                    {48, 63, 159,675,15},{40, 53, 147,675,2},{26, 35, 126,676,4},{48, 79, 254,677,6},\
                    {61, 90, 254,678,8},{83, 109, 254,679,10},{140, 158, 255,680,12},{223, 226, 245,681,14},\
                    {187, 222, 251,667,5},{144, 202, 249,670,0},{100, 181, 246,669,9},{66, 165, 245,670,11},\
                    {33, 150, 243,671,13},{30, 136, 229,678,0},{25, 118, 210,674,1},{21, 101, 192,675,3},\
                    {13, 71, 161,676,5},{41, 98, 255,677,7},{41, 121, 255,678,9},{68, 138, 255,679,11},\
                    {130, 177, 255,680,13},{214, 234, 251,681,15},{255, 205, 210,668,1},{239, 154, 154,668,2},\
                    {229, 115, 115,669,4},{239, 83, 80,670,6},{244, 67, 54,671,8},{229, 57, 53,672,10},\
                    {211, 47, 47,673,12},{198, 40, 40,681,0},{183, 28, 28,677,10},{213, 0, 0,677,2},\
                    {255, 23, 68,678,4},{255, 82, 82,679,6},{255, 138, 128,680,8},{252, 224, 227,681,10},\
                    {248, 187, 208,667,1},{244, 143, 177,668,3},{240, 98, 146,673,0},{236, 64, 122,670,7},\
                    {233, 30, 99,671,9},{216, 27, 96,672,11},{194, 24, 91,673,13},{173, 20, 87,674,15},\
                    {136, 14, 79,676,1},{197, 17, 98,677,3},{245, 0, 87,678,5},{255, 64, 129,679,7},\
                    {255, 128, 171,680,9},{250, 216, 227,681,11},{225, 190, 231,667,2},{206, 147, 216,668,4},\
                    {186, 104, 200,669,6},{171, 71, 188,670,8},{156, 39, 176,669,0},{142, 36, 170,672,2},\
                    {123, 31, 162,673,14},{106, 27, 154,677,0},{74, 20, 140,676,2},{170, 0, 255,677,4},\
                    {213, 0, 249,678,6},{224, 64, 251,679,8},{234, 128, 252,680,10},{239, 213, 243,681,2}};
            while(!stop)
            {
                if(datanum!=1)
                {
                    string str=filename.toLocal8Bit().data();
                    string newstr=str.substr(str.rfind("/"),str.rfind(".")-str.rfind("/"));
                    str=str.substr(0,str.rfind("/"));
                    newstr=str+newstr+to_string(datanum)+".lua";
                    op.open(newstr,ios::out);//!open
                    if(!op.is_open())
                        QMessageBox::warning(this,tr("错误"),tr("muban打开失败"));
                }
                //写入odata_头
                op<<"local DATD_"<<datanum<<"={";
                //循环
                int n=1;//判断第一次坐标前面有没有逗号
                int j=0;//限制lua文本的一行长度
                //!write
                for(int i=0;i<50000;i++)//1000次//单个lua文件长度
                {
                    BUILDX=bginx;BUILDY=bginy;BUILDZ=bginz;
                    if(imgx<=imgScaled->width()&&imgy<=imgScaled->height())
                    {
                        QColor color=imgScaled->pixelColor(imgx,imgy);
                        //!最小距离
                        int mindisten=0;
                        //!最小颜色下标
                        int minidex=0;
                        for(int i=0;i<251;i++)
                        {
                            if(i==0)
                                mindisten=sqrt(pow(minicolors[i].r-color.red(),2)+\
                                               pow(minicolors[i].g-color.green(),2)+\
                                               pow(minicolors[i].b-color.blue(),2));
                            else {
                                int disten;
                                disten=sqrt(pow(minicolors[i].r-color.red(),2)+\
                                            pow(minicolors[i].g-color.green(),2)+\
                                            pow(minicolors[i].b-color.blue(),2));
                                if(disten<mindisten)
                                {
                                    mindisten=disten;
                                    minidex=i;
                                }
                            }
                        }
                        BLOCKID=minicolors[minidex].blockid;
                        BlockData=minicolors[minidex].blockdata;
                    }
                    if(n==1)
                    {
                        op<<BUILDX<<","<<BUILDY<<","<<BUILDZ<<","<<BLOCKID<<","<<BlockData;
                        n++;
                    }
                    else
                        op<<","<<BUILDX<<","<<BUILDY<<","<<BUILDZ<<","<<BLOCKID<<","<<BlockData;
                    if(++j>=20)
                    {
                        op<<endl;
                        j=0;
                    }
                    if(BUILDY<imgScaled->height()){
                        bginy++;
                        imgy--;
                    }
                    else {
                        if(abs(endz-bginz)<abs(endx-bginx))
                        {
                            if(bginx<endx)
                                bginx++;
                            else
                                bginx--;
                            imgx++;
                            bginz=bginx*k;
                            bginy=ui_Pixe->spinBox_2->value();
                            imgy=imgScaled->height()-1;
                        }
                        else
                        {
                            if(bginz<endz)
                                bginz++;
                            else
                                bginz--;
                            imgx++;
                            bginx=bginz*k;
                            bginy=ui_Pixe->spinBox_2->value();
                            imgy=imgScaled->height()-1;
                        }
                    }
                    if(imgx==imgScaled->width())
                        break;
                }//for循环10000
                //!write
                //写入odata_尾(单个lua文件写满退出)
                if(datanum==1)
                {
                    mubanstr=muban1.path().toLocal8Bit().data();
                    mubanstr=mubanstr+"/muban1.txt";
                    muban.open(mubanstr,ios::in);
                    if(!muban.is_open())
                        QMessageBox::warning(this,tr("文件打开失败"),tr("muban1.txt文件打开失败x0000"));
                    while(getline(muban,mubanstr))
                        op<<mubanstr<<endl;
                    muban.close();
                }
                else
                {
                    mubanstr=muban1.path().toLocal8Bit().data();
                    mubanstr=mubanstr+"/muban2.txt";
                    muban.open(mubanstr,ios::in);
                    if(!muban.is_open())
                        QMessageBox::warning(this,tr("文件打开失败"),tr("muban2.txt文件打开失败x0000"));
                    int xiabiao=0;
                    while(getline(muban,mubanstr))
                    {
                        xiabiao=mubanstr.find("DATA_?");
                        while(xiabiao!=-1)
                        {
                            mubanstr.erase(xiabiao+5,1);
                            mubanstr.insert(xiabiao+5,to_string(datanum));
                            xiabiao=mubanstr.find("DATA_?");
                        }
                        xiabiao=mubanstr.find("DATD_?");
                        while(xiabiao!=-1)
                        {
                            mubanstr.erase(xiabiao+5,1);
                            mubanstr.insert(xiabiao+5,to_string(datanum));
                            xiabiao=mubanstr.find("DATD_?");
                        }
                        xiabiao=mubanstr.find("DATA_!");
                        while(xiabiao!=-1)
                        {
                            mubanstr.erase(xiabiao+5,1);
                            mubanstr.insert(xiabiao+5,to_string(datanum-1));
                            xiabiao=mubanstr.find("DATA_!");
                        }
                        op<<mubanstr<<endl;
                    }
                    muban.close();
                }//写入odata_尾
                op.close();//写满,关闭输出文件
                datanum++;
                if(imgx==imgScaled->width())
                    stop=true;
            }//while循环
            QMessageBox::information(this,tr("结束"),tr("转化结束"));
        }
    }
    if(img->isNull()&&filename.isEmpty())
        QMessageBox::information(this,tr("结束"),tr("未加载图片与未填文件名"));
    else if(filename.isEmpty())
        QMessageBox::information(this,tr("结束"),tr("未填文件名"));
    else if(img->isNull())
        QMessageBox::information(this,tr("结束"),tr("未加载图片"));
}
