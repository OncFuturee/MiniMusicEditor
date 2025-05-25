#ifndef PIXELPAINT_H
#define PIXELPAINT_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTemporaryDir>
#include <iostream>
#include <fstream>
#include <QWidget>
#include <QPixmap>
#include <math.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct Color{
    int r;
    int g;
    int b;
    int blockid;
    int blockdata;
}minicolor;


class PIXELPAINT:public QMainWindow
{
    Q_OBJECT
public:
    PIXELPAINT(QWidget *parent = nullptr);
    ~PIXELPAINT();
    virtual void closeEvent(QCloseEvent *event)override;
    void pixelpaintShow();
private:
    Ui::MainWindow *ui_Pixe;
    QImage *img;
    QImage *imgScaled;
    double scaled=1.00;
signals:
    void pixelpaintClose();
private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_comboBox_currentIndexChanged(int index);
    void on_spinBox_7_valueChanged(int arg1);
    void on_spinBox_8_valueChanged(int arg1);
    void on_pushButton_clicked();
};

#endif // PIXELPAINT_H
