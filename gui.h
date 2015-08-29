#ifndef GUI_H
#define GUI_H

#include "pairpoint.h"
#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QVector>
#include <vector>
#include <QColor>
#include <QDebug>
using std::vector;

namespace Ui {
class GUI;
}

class GUI : public QWidget
{
    Q_OBJECT
public:
    explicit GUI(int _size, int _level, QWidget *parent = 0);
    ~GUI();

signals:
    void clicked();

private:
    int x,y;
    int ii,jj;
    int size;
    int level;
    Ui::GUI *ui;

    int maxSize;
    int minSize;
    int minLevel;
    int maxLevel;

    double maxPix;
    //double minSize;
    double start_X;
    double start_Y;
    double eLen;

    int isDraw;
    //bool isPressed;
    QPoint *back;
    QPoint *restart;
    QPoint *next;

    vector<pairPoint> labelPoint;
    vector<QPoint> *rlBackground;
    vector<QPoint> *rootLine;
    vector<QPoint> *delLine;
    bool *isDone;


    void drawGrid(QPainter*);
    void showLabel(QPainter*);
    void drawLog(QPainter*);
    void showPress(QPainter*);
    void showRLB(QPainter*);
    QString isEllipse(int, int);
    int get_i(double x);
    int get_j(double y);
    bool checkOptions(QPoint, QPoint);
    QString getColor(QPoint);
    int isInLoad(QPoint);
    QColor convColor(QString);

    void setLabelPoint();


protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // GUI_H
