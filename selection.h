#ifndef SELECTION_H
#define SELECTION_H

#include <QDialog>

namespace Ui {
class Selection;
}

class Selection : public QDialog
{
    Q_OBJECT

public:
    explicit Selection(QWidget *parent = 0);
    ~Selection();
    void accept();

    int size;
    int level;

signals:
    void getChoice(int, int);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Selection *ui;
};

#endif // SELECTION_H
