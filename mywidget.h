#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>

class MYWIDGET : public QWidget
{
    Q_OBJECT
public:
    explicit MYWIDGET(QWidget *parent = nullptr);
    ~MYWIDGET();
    void paintEvent(QPaintEvent *event) override;
    void settouming(int tm);

private:
    int touming=220;

signals:

};

#endif // MYWIDGET_H
