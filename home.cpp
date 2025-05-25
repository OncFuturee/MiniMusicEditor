#include "home.h"
#include "ui_home.h"


HOME::HOME(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HOME)
{
    pixelpaint=new PIXELPAINT;//像素画窗口
    ui->setupUi(this);
    this->setWindowTitle("MiNiMusicEditor");
    ui->horizontalSlider->setValue(220);
    this->resize(1200,720);
    isplay=false;
    choosebg=2;
    basetimbre=48;
    connect(ui->label,SIGNAL(changeRatio(int,int)),ui->label_2,SLOT(changeRatio(int,int)));
    connect(ui->label_2,SIGNAL(ratioChange(int)),ui->label,SLOT(ratioChange(int)));
    //! [0]
    connect(ui->label,&MYLABEL::stopplay,[=](){
        on_button_play_clicked();
    });
    //! [0]
    connect(ui->label,&MYLABEL::p_playMusic,[=](){
        p_playmusic();
    });
    connect(ui->label,&MYLABEL::sizeadd,[=](){
        ui->label_size->setText(QString::number(ui->label->getLie()));
    });
    connect(pixelpaint,&PIXELPAINT::pixelpaintClose,[=](){
        this->show();
    });
}

HOME::~HOME()
{
    delete ui;
    delete pixelpaint;
}



void HOME::on_button_openFile_clicked()
{
    ui->label->openFile();
}

void HOME::on_button_newFile_clicked()
{
    ui->label->saveFile();
}

void HOME::on_button_play_clicked()
{
    if(isplay==false)
    {
        ui->button_play->setText("暂停");
        isplay=true;
        ui->label->timerstart();
    }
    else
    {
        ui->button_play->setText("播放");
        isplay=false;
        ui->label->timerstop();
    }
}

void HOME::on_button_function_clicked()
{
    if(choosebg==1){
    ui->groupBox_2->setStyleSheet("QGroupBox#groupBox_2{border-image: url(:/image/bg1.jpg);}");
    choosebg++;
    }else if(choosebg==2){
    ui->groupBox_2->setStyleSheet("QGroupBox#groupBox_2{border-image: url(:/image/bg2.jpg);}");
    choosebg++;
    }else if(choosebg==3){
    ui->groupBox_2->setStyleSheet("QGroupBox#groupBox_2{border-image: url(:/image/bg3.jpg);}");
    choosebg++;
    }else if(choosebg==4){
    ui->groupBox_2->setStyleSheet("QGroupBox#groupBox_2{border-image: url(:/image/bg4.jpg);}");
    choosebg++;
    }else if(choosebg==5){
        ui->groupBox_2->setStyleSheet("QGroupBox#groupBox_2{border-image: url(:/image/bg5.jpg);}");
        choosebg++;
    }else if(choosebg==6){
        ui->groupBox_2->setStyleSheet("QGroupBox#groupBox_2{border-image: url(:/image/bg6.jpg);}");
        choosebg++;
    }else if(choosebg==7){
        ui->groupBox_2->setStyleSheet("QGroupBox#groupBox_2{border-image: url(:/image/bg7.jpg);}");
        choosebg=1;
    }
}

void HOME::p_playmusic()
{
    ;
}






void HOME::on_radioButton_4_clicked()
{
    basetimbre=36;
    ui->label->settimbre(basetimbre+ui->comboBox->currentIndex());
    switch (ui->comboBox->currentIndex())
    {
        case 0:QSound::play(":music/gu-01_WAV_01.wav");break;
        case 1:QSound::play(":music/gu-02_WAV_01.wav");break;
        case 2:QSound::play(":music/gu-03_WAV_01.wav");break;
        case 3:QSound::play(":music/gu-04_WAV_01.wav");break;
        case 4:QSound::play(":music/gu-05_WAV_01.wav");break;
        case 5:QSound::play(":music/gu-06_WAV_01.wav");break;
        case 6:QSound::play(":music/gu-07_WAV_01.wav");break;
        case 7:QSound::play(":music/gu-08_WAV_01.wav");break;
    }

}

void HOME::on_radioButton_5_clicked()
{
    basetimbre=44;
    ui->label->settimbre(basetimbre+ui->comboBox_2->currentIndex());
    switch (ui->comboBox_2->currentIndex())
    {
        case 0:QSound::play(":music/dianzi-01_WAV_01.wav");break;
        case 1:QSound::play(":music/dianzi-02_WAV_01.wav");break;
        case 2:QSound::play(":music/dianzi-03_WAV_01.wav");break;
        case 3:QSound::play(":music/dianzi-04_WAV_01.wav");break;
        case 4:QSound::play(":music/dianzi-05_WAV_01.wav");break;
        case 5:QSound::play(":music/dianzi-06_WAV_01.wav");break;
        case 6:QSound::play(":music/dianzi-07_WAV_01.wav");break;
        case 7:QSound::play(":music/dianzi-08_WAV_01.wav");break;
    }
}

void HOME::on_radioButton_6_clicked()
{
    basetimbre=52;
    ui->label->settimbre(basetimbre+ui->comboBox_3->currentIndex());
    switch (ui->comboBox_3->currentIndex())
    {
        case 0:QSound::play(":music/zonghe-01_WAV_01.wav");break;
        case 1:QSound::play(":music/zonghe-02_WAV_01.wav");break;
        case 2:QSound::play(":music/zonghe-03_WAV_01.wav");break;
        case 3:QSound::play(":music/zonghe-04_WAV_01.wav");break;
        case 4:QSound::play(":music/zonghe-05_WAV_01.wav");break;
        case 5:QSound::play(":music/zonghe-06_WAV_01.wav");break;
        case 6:QSound::play(":music/zonghe-07_WAV_01.wav");break;
        case 7:QSound::play(":music/zonghe-08_WAV_01.wav");break;
    }
}

void HOME::on_comboBox_currentIndexChanged(int index)
{
    ui->label->settimbre(basetimbre+index);
    switch (index)
    {
        case 0:QSound::play(":music/gu-01_WAV_01.wav");break;
        case 1:QSound::play(":music/gu-02_WAV_01.wav");break;
        case 2:QSound::play(":music/gu-03_WAV_01.wav");break;
        case 3:QSound::play(":music/gu-04_WAV_01.wav");break;
        case 4:QSound::play(":music/gu-05_WAV_01.wav");break;
        case 5:QSound::play(":music/gu-06_WAV_01.wav");break;
        case 6:QSound::play(":music/gu-07_WAV_01.wav");break;
        case 7:QSound::play(":music/gu-08_WAV_01.wav");break;
    }
}

void HOME::on_comboBox_2_currentIndexChanged(int index)
{
    ui->label->settimbre(basetimbre+index);
    switch (index)
    {
        case 0:QSound::play(":music/dianzi-01_WAV_01.wav");break;
        case 1:QSound::play(":music/dianzi-02_WAV_01.wav");break;
        case 2:QSound::play(":music/dianzi-03_WAV_01.wav");break;
        case 3:QSound::play(":music/dianzi-04_WAV_01.wav");break;
        case 4:QSound::play(":music/dianzi-05_WAV_01.wav");break;
        case 5:QSound::play(":music/dianzi-06_WAV_01.wav");break;
        case 6:QSound::play(":music/dianzi-07_WAV_01.wav");break;
        case 7:QSound::play(":music/dianzi-08_WAV_01.wav");break;
    }
}

void HOME::on_comboBox_3_currentIndexChanged(int index)
{
    ui->label->settimbre(basetimbre+index);
    switch (index)
    {
        case 0:QSound::play(":music/zonghe-01_WAV_01.wav");break;
        case 1:QSound::play(":music/zonghe-02_WAV_01.wav");break;
        case 2:QSound::play(":music/zonghe-03_WAV_01.wav");break;
        case 3:QSound::play(":music/zonghe-04_WAV_01.wav");break;
        case 4:QSound::play(":music/zonghe-05_WAV_01.wav");break;
        case 5:QSound::play(":music/zonghe-06_WAV_01.wav");break;
        case 6:QSound::play(":music/zonghe-07_WAV_01.wav");break;
        case 7:QSound::play(":music/zonghe-08_WAV_01.wav");break;
    }
}

void HOME::on_horizontalSlider_valueChanged(int value)
{
    ui->label_touming->setText(QString::number(value));
    ui->widget->settouming(value);
    ui->widget->repaint();
}


void HOME::on_spinBox_valueChanged(int arg1)
{
    ui->label->setdataX(arg1);
}

void HOME::on_spinBox_2_valueChanged(int arg1)
{
    ui->label->setdataY(arg1);
}

void HOME::on_spinBox_3_valueChanged(int arg1)
{
    ui->label->setdataZ(arg1);
}

void HOME::on_spinBox_4_valueChanged(int arg1)
{
    ui->label->setdataFace(arg1);
}

void HOME::on_pushButton_clicked()
{
    pixelpaint->pixelpaintShow();
    this->hide();
}

void HOME::on_pushButton_2_clicked()
{
    QMessageBox::information(this,tr("教程"),tr("详细教程请查看程序包里的word文档\n"
                                              "如果你没有此文件,说明该程序经过了第三方转载\n"
                                              "该程序为免费软件,如果你是付费获得的该软件\n"
                                              "那么你被骗了"));
}
