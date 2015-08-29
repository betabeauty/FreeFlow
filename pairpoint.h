#ifndef PAIRPOINT_H
#define PAIRPOINT_H

#include <QPoint>
#include <QString>

class pairPoint
{
public:
    pairPoint(QPoint p1, QPoint p2, QString cl = "red");
    pairPoint(){};

    QPoint point_1;
    QPoint point_2;
    QString color;
};

#endif // PAIRPOINT_H
