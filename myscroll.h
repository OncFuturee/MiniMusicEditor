#ifndef MYSCROLL_H
#define MYSCROLL_H

#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

class MYSCROLL : public QLabel
{
    Q_OBJECT
public:
    explicit MYSCROLL(QWidget *parent =nullptr);
    ~MYSCROLL();
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
private slots:
    void changeRatio(int Num, int Max);
private:
    int max;
    int num;
signals:
    void ratioChange(int num);
};

#endif // MYSCROLL_H
