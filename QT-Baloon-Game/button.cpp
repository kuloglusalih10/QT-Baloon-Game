#include "button.h"
#include "QDebug"

button::button(QWidget *parent)
    : QPushButton{parent}
{
    tiklandimi=false;
    connect(this,&QPushButton::clicked,this,&button::tikla);
}

void button::tikla()
{
    tiklandimi = !tiklandimi;
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&button::gizle);
    timer->start(500);
}

void button::gizle()
{
    this->hide();
}
