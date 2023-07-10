#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "button.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool tiklandimi;
private:

    Ui::MainWindow *ui;
    void butonOlustur();
    void basla();
    void zamanlayıcı();
    QList<button*> buttons;
    QTimer *baslaTimer;
};
#endif // MAINWINDOW_H
