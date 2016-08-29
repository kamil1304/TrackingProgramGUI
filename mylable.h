#ifndef MYLABLE_H
#define MYLABLE_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>



class MyLable : public QLabel
{
    Q_OBJECT
public:
    explicit MyLable(QWidget *parent = 0);

       void mouseMoveEvent(QMouseEvent *ev);
       void mousePressEvent(QMouseEvent *ev);
       void leaveEvent(QEvent *);
       int x,y;
signals:
       void Mouse_Pressed();
       void Mouse_Pos();
       void Mouse_Left();

public slots:
};

#endif // MYLABLE_H
