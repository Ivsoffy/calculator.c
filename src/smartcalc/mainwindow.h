#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QAbstractButton>
extern "C" {
#include "../s21_smartcalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<double> x1,y1;
    double xmin = -50, xmax = 50, ymin, ymax;
    QString value_x, xmin_q = "-50", xmax_q = "50", ymin_q = "-50", ymax_q = "50";

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
//    void MainWindow::on_doubleSpinBox_textChanged(const QString &arg1);
//    void on_eq_clicked();

//    void on_lineEdit_2_textChanged(const QString &arg2);
    void engineer();
    void on_doubleSpinBox_textChanged(const QString &arg1);

//    double Qstr_to_double_(QString &arg);
    void on_Xmax_textChanged(const QString &arg1);
    void on_Xmin_textChanged(const QString &arg1);

    void on_Ymax_textChanged(const QString &arg1);
    void on_Ymin_textChanged(const QString &arg1);
    void from_QStr_to_str(char* str, QString val);

private:
    Ui::MainWindow *ui;
    void Printsmt();

    void parser(QAbstractButton *arg1);
//    void parser_x(QAbstractButton *arg2);
    double calculate();
    void clear();
//    void clear_one();
    char* str_x;
    double res;
    QString value;

};
#endif // MAINWINDOW_H
