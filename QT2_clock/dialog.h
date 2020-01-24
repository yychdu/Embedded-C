#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QTime>
#include<QMouseEvent>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    int state;
    int nMSCnt;
    QTime sTime;
    QList<int> lstCnt;
    int idx;

    QRect rcBottom;
    QRect rcLeft;
    QRect rcRight;
private slots:
    void mytimer();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *e);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *e);
};

#endif // DIALOG_H
