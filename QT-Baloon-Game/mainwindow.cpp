

// Salih Kuloğlu 20010011061


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include <QTime>


int deger =30;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    if(deger > 0){
        ui->setupUi(this);
        this->showMaximized();

        ui->label_png->setGeometry(0,90,this->geometry().width(),this->geometry().height());

        ui->sure_label->setText("Süre = <font color = blue>0</font>");
        ui->sure_label->setGeometry(0,0,250,90);

        ui->label_kesilenKarpuz->setText("Kesilen Karpuz Sayısı : <font color = green>0</font>");
        ui->label_kesilenKarpuz->setGeometry(this->geometry().width()-ui->label_kesilenKarpuz->geometry().width()-50,0,350,45);

        ui->label_kacanKarpuz->setText("Kaçırılan Karpuz Sayısı : <font color = red>0</font>");
        ui->label_kacanKarpuz->setGeometry(this->geometry().width()-ui->label_kacanKarpuz->geometry().width()-50,45,350,45);


        QTimer *zamanlayici = new QTimer(this);
        connect(zamanlayici,&QTimer::timeout,this,&MainWindow::zamanlayıcı);
        zamanlayici->start(1000);

        QTimer *timer=new QTimer(this);
        connect(timer,&QTimer::timeout,this,&MainWindow::butonOlustur);
        timer->start(700);

        QTimer *baslaTimer = new QTimer(this);
        connect(baslaTimer,&QTimer::timeout,this,&MainWindow::basla);
        baslaTimer->start(1000/160);


    }

}


int kesilen = 0;
int kacan = 0;




MainWindow::~MainWindow()
{
    delete ui;
}

QStringList konumListesi;



void MainWindow::butonOlustur()
{

    if(deger > 0){

        QString path ="C:/Gorsel/odev1/konumlar.txt";
        QFile my_file(path);


        if(!my_file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this,"Hata",my_file.errorString());
            return;
        }


        while(!my_file.atEnd()){

            QString line = my_file.readLine().trimmed();
            QStringList konum = line.split(" ");
            konumListesi.append(konum);

        }

        int randIndex = QRandomGenerator::global()->bounded(0,konumListesi.length());

        int randomLocation = konumListesi[randIndex].toInt();


        button *my_button = new button(this);


        my_button->setGeometry(randomLocation,100,55,55);

        my_button->setIcon(QIcon(":/image/images/1.png"));
        my_button->setIconSize(QSize(55, 55));
        my_button->show();
        buttons.append(my_button);

        konumListesi.clear();

    }


}

void MainWindow::basla()
{
    if(deger > 1){

        ui->label_png->setGeometry(0,90,this->geometry().width(),this->geometry().height());
        ui->label_kesilenKarpuz->setGeometry(this->geometry().width()-ui->label_kesilenKarpuz->geometry().width()-50,0,350,45);
        ui->label_kacanKarpuz->setGeometry(this->geometry().width()-ui->label_kacanKarpuz->geometry().width()-50,45,350,45);

        foreach(button *str, buttons)
        {
            if(str->tiklandimi == false){
                str->setGeometry(str->x(),str->y()+1,str->width(),str->height());
            }
            if(str->tiklandimi){
                str->setIcon(QIcon(":/image/images/2.png"));
                kesilen++;
                ui->label_kesilenKarpuz->setText("Kesilen Karpuz Sayısı : <font color = green>"+QString::number(kesilen)+"</font>");
                str->setIconSize(QSize(55, 55));
                buttons.removeOne(str);
            }
            if(this->geometry().height() < str->y()){
                kacan++;
                ui->label_kacanKarpuz->setText("Kaçırılan Karpuz Sayisi :  <font color = red>"+QString::number(kacan)+"</font>");
                buttons.removeOne(str);
                str->hide();
            }
        }

    }


}


QList<int> skorlarListesi;

void MainWindow::zamanlayıcı()
{
    deger--;
    ui->sure_label->setText("Süre = <font color = blue>"+QString::number(deger)+ "</font>");

    if(deger == 0){


        QString path ="C:/Gorsel/odev1/skorlar.txt";
        QFile my_file(path);


        if(!my_file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this,"Hata",my_file.errorString());
            return;
        }


        while(!my_file.atEnd()){

            int line = my_file.readLine().trimmed().toInt();
            skorlarListesi.append(line);

        }

        my_file.close();



         if (!my_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
             QMessageBox::warning(this, "Hata", my_file.errorString());
             return;
         }

         QTextStream stream(&my_file);
         stream.seek(my_file.size());

         stream << kesilen << "\n";
         my_file.close();



        bool rekor = true;
        int enbSkor;
        enbSkor = skorlarListesi[0];

        for(int i = 0 ; i< skorlarListesi.length(); i++){

            if(skorlarListesi[i] > enbSkor){
                enbSkor = skorlarListesi[i];
            }

            if(skorlarListesi[i] > kesilen){
                rekor = false;
            }

        }

        if(rekor)
        {
            QString mesaj = "Oyun Bitti ! Tebrikler Maximum Skor Sizde !\nKesilen Karpuz Sayısı : " + QString::number(kesilen)+"\nKaçırılan Karpuz Sayısı : "+QString::number(kacan)+"\nMaximum Skor : "+QString::number(enbSkor);
            QMessageBox::warning(this,"Bilgi", mesaj);
            baslaTimer->stop();
            return;

        }
        else{
            QString mesaj = "Oyun Bitti ! Maximum Skoru Geçemediniz !\nKesilen Karpuz Sayısı : " + QString::number(kesilen)+"\nKaçırılan Karpuz Sayısı : "+QString::number(kacan)+"\nMaximum Skor : "+QString::number(enbSkor);
            QMessageBox::warning(this,"Bilgi", mesaj);
            baslaTimer->stop();
            return;

        }

    }




}



