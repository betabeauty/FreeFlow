#include "gui.h"
#include "ui_GUI.h"
#include <QPalette>
#include <QMessageBox>
#include <QMouseEvent>
#include <QString>
#include <QDebug>
#include <qmath.h>
#include <QPen>

GUI::GUI(int _size, int _level, QWidget *parent) :
    x(0), y(0),
    size(_size),
    level(_level),
    ui(new Ui::GUI),
    QWidget(parent)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);//set background color

    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::yellow);
    ui->level->setPalette(pa);
    pa.setColor(QPalette::WindowText, Qt::gray);
    ui->size->setPalette(pa);

    back = new QPoint(147, 495);
    restart = new QPoint(215, 495);
    next = new QPoint(287, 495);

    minLevel = 1;
    maxLevel = 3;
    minSize = 5;
    maxSize = 7;

    isDraw = -1;
    //isPressed = false;

    setLabelPoint();

}

void GUI::setLabelPoint()
{
    labelPoint.clear();

    QString l = QString::number(level, 10);
    l = "Level " + l;
    ui->level->setText(l);
    //ui->level->set;
    QString s = QString::number(size, 10);
    s = s+"*"+s;
    ui->size->setText(s);


    //qDebug() << "Exit GUI Constrction()...";
    pairPoint pair1(QPoint(1,0),QPoint(1,2),QStringLiteral("red"));
    pairPoint pair2(QPoint(0,1), QPoint(2,1), QStringLiteral("green"));

    labelPoint.push_back(pair1);
    labelPoint.push_back(pair2);

    rlBackground = new vector<QPoint>[labelPoint.size()];
    rlBackground[0].push_back( QPoint(1,0));
    rootLine = new vector<QPoint>[2*labelPoint.size()];
    delLine = new vector<QPoint>[2*labelPoint.size()];
    isDone = new bool[2*labelPoint.size()];
    for (unsigned int i = 0;i < 2*labelPoint.size();i++){
        isDone[i] = false;
    }
    //rootLine[darw].push_back(three);
    for (unsigned int i = 0;i < labelPoint.size();i ++)
    {
        QPoint one(labelPoint[i].point_1);
        QPoint two(labelPoint[i].point_2);
        rootLine[2*i].push_back(one);
        rootLine[2*i+1].push_back(two);

        delLine[2*i].push_back(one);
        delLine[2*i+1].push_back(two);
    }

    update();
    //qDebug() << "Exit GUI Constrction()...";
}

GUI::~GUI()
{
    delete ui;
    delete back;
    delete restart;
    delete next;
    delete rootLine;
    delete delLine;
    delete isDone;
    delete rlBackground;
}

//int _X = i*eLen+start_X+eLen/2;
//int _Y = j*eLen+start_Y+eLen/2;
int GUI::get_i(double _x)//from 0
{
    //qDebug() <<(x-start_X)<<' '<<eLen;
    return int((_x-start_X)/(eLen) - 1/2);
}
int GUI::get_j(double _y)
{
    return int((_y-start_Y)/(eLen) - 1/2);
}

bool GUI::checkOptions(QPoint O, QPoint P)
{
    if ((qAbs(O.x()-P.x()) < 20) && (qAbs(O.y() - P.y()) < 20))
    {
        return true;
    }
    return false;
}

QString GUI::isEllipse(int i, int j)
{
    QPoint tempPoint(i, j);
    for (unsigned int k = 0; k < labelPoint.size(); k++)
    {
        if ((tempPoint == labelPoint[k].point_1) || (tempPoint == labelPoint[k].point_2)){
            //qDebug() <<'(' <<i<<','<<j<<')';
            return labelPoint[k].color;
        }
    }
    return "";

}


void GUI::drawLog(QPainter * painter)
{
    //qDebug()<<"In drawLog...";
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(eLen*2/5);
    pen.setCapStyle(Qt::RoundCap);

    for (unsigned int i = 0;i < 2*labelPoint.size(); i++){
        QString col = getColor(rootLine[i][0]);
        pen.setBrush(convColor(col));
        painter->setPen(pen);

        for (unsigned int j = 0;j < rootLine[i].size()-1; j++){
            int xx = rootLine[i][j].x();
            int yy = rootLine[i][j].y();
            QPoint p1(xx*eLen+start_X+eLen/2, yy*eLen+start_Y+eLen/2);

            xx = rootLine[i][j+1].x();
            yy = rootLine[i][j+1].y();
            QPoint p2(xx*eLen+start_X+eLen/2, yy*eLen+start_Y+eLen/2);

            painter->drawLine(p1, p2);
        }
    }
    //qDebug() <<"Exit drawLog...";
}

void GUI::showRLB(QPainter * painter){
    for (unsigned int i = 0;i < labelPoint.size(); i++){
        if ((isDraw != -1) && (isDraw/2 == i)){

        }
        else{
            QString col = labelPoint[i].color;
            //QString col = "red";
            painter->setPen(Qt::NoPen);
            QColor qcol=convColor(col);
            qcol.setAlpha(80);

            painter->setBrush(qcol);
            for (unsigned int j = 0;j < rlBackground[i].size(); j++)
            {
                painter->drawRect(start_X+rlBackground[i][j].x()*eLen,start_Y+rlBackground[i][j].y()*eLen,eLen,eLen);
            }
        }
    }
}

void GUI::paintEvent(QPaintEvent *e)
{
    //qDebug() << "In paintEvent...";
    QPainter painter(this);
    drawGrid(&painter);
    showLabel(&painter);
    if (isDraw != -1)
        showPress(&painter);
    drawLog(&painter);

    showRLB(&painter);

}

void GUI::mousePressEvent(QMouseEvent *e)
{
    x = e->x();
    y = e->y();
    ii = get_i(x);
    jj = get_j(y);
    QPoint test(ii, jj);

    if ((ii > -1) && (ii < size) && (jj > -1) && (jj < size))
    {
        //isPressed = true;
       for (int i = 0;i < 2*labelPoint.size(); i++){
           int end = rootLine[i].size()-1;
           if (test == rootLine[i][0])
           {
               rootLine[i].clear();
               rootLine[i].push_back(test);

               if (i % 2 == 0){
                   QPoint temp = rootLine[i+1][0];
                   rootLine[i+1].clear();
                   rootLine[i+1].push_back(temp);
               }
               else{
                   QPoint temp = rootLine[i-1][0];
                   rootLine[i-1].clear();
                   rootLine[i-1].push_back(temp);
               }

               isDraw = i;
               isDone[i] = false;
               update();
           }
           else if(test == rootLine[i][end])
               isDraw = i;
       }
    }

    //three options
    if (checkOptions(*back, QPoint(x,y)))
    {
        if (level > minLevel)
            level --;
        else if(size > minSize){
            level = maxLevel;
            size --;
        }
        else
            qDebug() << "Sorry, no back!";
        setLabelPoint();
    }
    else if (checkOptions(*restart, QPoint(x,y)))
    {
        setLabelPoint();
    }
    else if (checkOptions(*next, QPoint(x, y)))
    {
        if (level < maxLevel)
            level ++;
        else if (size < maxSize){
            level = minLevel;
            size ++;
        }
        else
            qDebug() <<"Sorry, no next!";
        setLabelPoint();
    }

}

void GUI::mouseMoveEvent(QMouseEvent *e)
{
    x = e->x();
    y = e->y();
    ii = get_i(x);
    jj = get_j(y);
    update();

    if ((ii > -1)&&(ii < size)&&(jj > -1)&&(jj < size))
    {
        if ((isDraw != -1)){
            int end = rootLine[isDraw].size()-1;
            int back_x = rootLine[isDraw][end].x();
            int back_y = rootLine[isDraw][end].y();
            if (((ii == back_x) && (qAbs(jj-back_y) == 1)) || ((jj == back_y) && (qAbs(ii - back_x) == 1))){
                if ((end > 0) && (ii == rootLine[isDraw][end-1].x()) && (jj == rootLine[isDraw][end-1].y())){

                    isDone[isDraw] = false;
                    //qDebug() <<"In pop_back...";
                    rootLine[isDraw].pop_back();

                    for (unsigned int i = 0;i < 2*labelPoint.size();i++){
                        int back_end = rootLine[i].size()-1;
                        if (rootLine[i][back_end] == delLine[i][0]){
                            if (delLine[i].size() > 1){
                            while(isInLoad(delLine[i][1]) == -1){
                                rootLine[i].push_back(delLine[i][1]);
                                delLine[i].erase(delLine[i].begin());
                            }
                            }
                            update();
                        }
                    }
                    update();
                }
                else if((ii == back_x) && (jj == back_y)){
                    qDebug() <<"In here...";
                }
                else{
                    QPoint append(ii, jj);

                    if ((isEllipse(ii, jj) != ""))
                    {
                        if ((append == rootLine[isDraw][0])){
                            QPoint st = rootLine[isDraw][0];
                            rootLine[isDraw].clear();
                            rootLine[isDraw].push_back(st);
                            update();
                        }
                        else if (getColor(append) == getColor(rootLine[isDraw][0])){
                            isDone[isDraw] = true;
                            rootLine[isDraw].push_back(append);
                            update();
                        }
                        else{

                        }
                    }
                    //crash other's rootLine
                    else if (isDone[isDraw] == false){
                        int rl = isInLoad(append);
                        if (rl != -1){
                            unsigned int num;
                            for (num = 0;num < rootLine[rl].size(); num++){
                                if (rootLine[rl][num] == append)
                                    break;
                            }
                            int nn = num;
                            if (rl != isDraw){
                                delLine[rl][0] = rootLine[rl][num-1];
                                delLine[rl].insert(delLine[rl].begin()+1, rootLine[rl].begin()+num,rootLine[rl].end());
                            }
                            rootLine[rl].erase(rootLine[rl].begin()+nn,rootLine[rl].end());
                                isDone[rl] = false;
                            //qDebug() <<"In append...";
                        }
                            rootLine[isDraw].push_back(append);
                            update();
                    }
                }
            }

        }
    }
    //isDraw = false;
}

void GUI::mouseReleaseEvent(QMouseEvent *e)
{
    isDraw = -1;
    //isPressed = false;
    for (unsigned int i = 0;i < 2*labelPoint.size(); i++){
        delLine[i].clear();
        vector<QPoint>().swap(delLine[i]);
        delLine[i].push_back(rootLine[i][0]);
    }
    update();

}

void GUI::drawGrid(QPainter *painter)
{
    //qDebug() << "In DrawGrid()...";
    QString col = "yellow";
    painter->setPen(col);

    maxPix = 400;
    //minSize = 0;
    start_X = 25;
    start_Y = 50;
    eLen = maxPix / size;

    for (int i = 0;i <= size;i++)
    {
        painter->drawLine(QPoint(start_X, i*eLen+start_Y), QPoint(maxPix+start_X, i*eLen+start_Y));
        painter->drawLine(QPoint(i*eLen+start_X, start_Y), QPoint(i*eLen+start_X, maxPix+start_Y));
    }

    //qDebug() << "Exit drawGrid()...";
}

void GUI::showLabel(QPainter *painter)
{
    for (int i = 0;i < size; i++)
    {
        for (int j = 0;j < size; j++)
        {
            QString colString = isEllipse(i, j);
            if (colString != "")
            {
                int _X = i*eLen+start_X+eLen/2;
                int _Y = j*eLen+start_Y+eLen/2;
                QPoint pp(_X, _Y);

                painter->setPen(Qt::NoPen);
                painter->setBrush(convColor(colString));
                double r = (eLen*2) / 5;
                painter->drawEllipse(pp, r, r);
            }
        }
    }
}

void GUI::showPress(QPainter *painter)
{
    QString colo = getColor(rootLine[isDraw][0]);
    QColor qcol = convColor(colo);
    qcol.setAlpha(80);

    painter->setBrush(qcol);
    painter->setPen(Qt::NoPen);

    QPoint here(x, y);
    painter->drawEllipse(here, eLen, eLen);
}

QString GUI::getColor(QPoint Po)
{
    int len = labelPoint.size();
    for (int i = 0;i < len;i++)
    {
        if ((Po == labelPoint[i].point_1) || (Po == labelPoint[i].point_2))
        {
            return labelPoint[i].color;
        }

    }
    return "";
}

int GUI::isInLoad(QPoint check){
    for (unsigned int i = 0;i < 2*labelPoint.size();i++){
        for (unsigned int j = 1;j < rootLine[i].size(); j++){
           if (check == rootLine[i][j])
               return i;
        }
    }
    return -1;
}


QColor GUI::convColor(QString s)
{
    if (s == "green")
        return Qt::green;
    else if(s == "blue")
        return Qt::blue;
    else if(s == "yellow")
        return Qt::yellow;
    else if(s == "cyan")
        return Qt::cyan;
    else if(s == "gray")
        return Qt::gray;
    else if (s == "magenta")
        return Qt::magenta;
    else if(s == "darkGreen")
        return Qt::darkGreen;
    else if(s == "darkRed")
        return Qt::darkRed;
    else if(s == "darkBlue")
        return Qt::darkBlue;
    else if (s == "red")
        return Qt::red;
    else{
        return Qt::black;
    }
}

