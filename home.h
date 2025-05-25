#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QDebug>
#include <QSound>
#include <QSoundEffect>
#include <QThread>
#include "mylabel.h"
#include "myscroll.h"
#include "mywidget.h"
#include "mypiano.h"
#include "pixelpaint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HOME; }
QT_END_NAMESPACE

class HOME : public QMainWindow
{
    Q_OBJECT

public:
    HOME(QWidget *parent = nullptr);
    ~HOME();

private slots:
    void on_button_openFile_clicked();

    void on_button_newFile_clicked();

    void on_button_play_clicked();

    void on_button_function_clicked();

private slots:
    void p_playmusic();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_4_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::HOME *ui;
    bool isplay;
    int choosebg;
    int basetimbre;//基础音色
    PIXELPAINT *pixelpaint;

};
#endif // HOME_H
