#include "mainwindow.h"

#include <cstring>
#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->write, &QButtonGroup::buttonClicked, this, &MainWindow::parser);
  connect(ui->eq, &QPushButton::clicked, this, &MainWindow::calculate);
  //    connect(ui->eq, &QPushButton::clicked, this,
  //    &MainWindow::on_doubleSpinBox_textChanged);
  connect(ui->AC, &QPushButton::clicked, this, &MainWindow::clear);
  connect(ui->dot_2, &QPushButton::clicked, this, &MainWindow::engineer);

  this->setStyleSheet("background-color: #1c1c1c;");
  this->setFixedSize(630, 550);
}

void MainWindow::engineer() {
  double rr=0;
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  QString copy_value(value);

  xmax = xmax_q.toDouble();
  xmin = xmin_q.toDouble();
  ymax = ymax_q.toDouble();
  ymin = ymin_q.toDouble();

  double h = (xmax - xmin) / 10000;
//  double h = 0.1;
  char *tempstr = new char[value.length() + 1];
  from_QStr_to_str(tempstr, value);

  if (!postfix_calculation(tempstr, &rr, "0")) {
    if ((xmin < xmax) && (ymax > ymin)) {
      for (double X = xmin; X <= xmax; X += h) {
        x1.push_back(X);
        value_x = QString::number(X);
        double res = calculate();
        clear();
        value = copy_value;
        y1.push_back(res);
      }
      ui->widget->xAxis->setRange(xmax, xmin);
      ui->widget->yAxis->setRange(ymax, ymin);

      ui->widget->addGraph();
      ui->widget->graph(0)->setData(x1, y1);
      ui->widget->replot();
      x1.clear();
      y1.clear();
    } else {
      ui->lineEdit->setText("error");
    }
    clear();
  } else {
    value = "error";
    ui->lineEdit->setText(value);
  }
  value_x = QString::number(ui->doubleSpinBox->value());
  delete[] tempstr;
}

void MainWindow::from_QStr_to_str(char *str, QString val) {
  for (int i = 0; i < val.length(); ++i) {
    str[i] = val.toStdString().c_str()[i];
  }
  str[val.length()] = '\0';
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_lineEdit_textChanged(const QString &arg1) { value = arg1; }

void MainWindow::Printsmt() { std::cout << "clicked"; }

void MainWindow::parser(QAbstractButton *arg1) {
  value += arg1->text();
  ui->lineEdit->setText(value);
}

double MainWindow::calculate() {
  double res = 0;
  char *res_str = new char[100];
  char *tempstr = new char[value.length() + 1];
  from_QStr_to_str(tempstr, value);
  char *tempstr_x = new char[value_x.length() + 1];
  from_QStr_to_str(tempstr_x, value_x);

  value.clear();
  if (!(postfix_calculation(tempstr, &res, tempstr_x))) {
    sprintf(res_str, "%.7lf", res);
    for (int i = 0; i < (int)strlen(res_str); i++) {
      value += res_str[i];
    }
  } else {
    value = "error";
  }
  ui->lineEdit->setText(value);

  delete[] tempstr;
  delete[] tempstr_x;
  return res;
}

void MainWindow::clear() {
  value.clear();
  ui->lineEdit->setText(value);
}

void MainWindow::on_doubleSpinBox_textChanged(const QString &arg1) {
  value_x = arg1;
}

void MainWindow::on_Xmax_textChanged(const QString &arg1) { xmax_q = arg1; }

void MainWindow::on_Xmin_textChanged(const QString &arg1) { xmin_q = arg1; }

void MainWindow::on_Ymax_textChanged(const QString &arg1) { ymax_q = arg1; }

void MainWindow::on_Ymin_textChanged(const QString &arg1) { ymin_q = arg1; }
