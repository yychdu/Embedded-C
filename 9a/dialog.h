#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void paintEvent(QPaintEvent *);
double fa;
double sp;
int zuo;
int you;
public slots:
void mytimer();

private slots:
void on_pushButton_clicked();

void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;




    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);

    // QWidget interface
//protected:
//    void mouseReleaseEvent(QMouseEvent *);
};

#endif // DIALOG_H
