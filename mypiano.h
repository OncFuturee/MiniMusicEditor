#ifndef MYPIANO_H
#define MYPIANO_H

#include <QLabel>
#include <QPainter>

class MYPIANO : public QLabel
{
    Q_OBJECT
public:
    explicit MYPIANO(QWidget *parent = nullptr);
    ~MYPIANO();
    void paintEvent(QPaintEvent *event) override;

private:
    int touming=255;

signals:

};

#endif // MYPIANO_H
