#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gui.h"
#include "selection.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void choose();
    void showPlayGUI(int _size, int _level);

private:
    Ui::MainWindow *ui;
    Selection *se;
    GUI *gui;
};

#endif // MAINWINDOW_H
