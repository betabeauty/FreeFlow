#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //qDebug() << "In MainWindow Constrction...";
    ui->setupUi(this);
    //this->setWindowModality(Qt::ApplicationModal);

    QObject::connect(ui->playing, SIGNAL(clicked(bool)), this, SLOT(choose()));
    //qDebug() << "Exit MainWindow Constrction...";
}

void MainWindow::choose()
{
    //qDebug() << "In choose()...";
    se = new Selection();
    se->setModal(true);
    se->show();
    QObject::connect(se, SIGNAL(getChoice(int,int)), this, SLOT(showPlayGUI(int,int)));
    //QObject::connect(se, SIGNAL(se->getChoice(int, int)), this, SLOT(showPlayGUI(int, int)));

    //qDebug() << "Exit choose()...";
}

void MainWindow::showPlayGUI(int _size, int _level){
    //qDebug() << "In showPlayGUI()...";

    int size = _size;
    int level = _level;
        //qDebug() << "size : " <<size << "  level : "<<level;
    gui = new GUI(size, level);
    gui->show();

    //qDebug() << "Exit showPlayGUI()...";
}

MainWindow::~MainWindow()
{
    delete ui;
}
