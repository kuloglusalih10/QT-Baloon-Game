#ifndef BUTTON_H
#define BUTTON_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>


class button : public QPushButton
{
    Q_OBJECT
public:
    button(QWidget *parrent=0);
    bool tiklandimi;

signals:
public slots:
    void tikla();
    void gizle();
};

#endif // BUTTON_H
