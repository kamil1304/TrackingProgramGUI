#include "mylable.h"

MyLable::MyLable(QWidget *parent) :
    QLabel(parent)
{
setMouseTracking(true);
}

void MyLable::mouseMoveEvent(QMouseEvent *ev)
{
    this->x=ev->x();
    this->y=ev->y();
    emit Mouse_Pos();

}

void MyLable::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Pressed();
}

void MyLable::leaveEvent(QEvent *)
{
    emit Mouse_Left();
}
