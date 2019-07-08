#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableWidget->setColumnCount(3);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
  ui->tableWidget->setHorizontalHeaderLabels({"column1", "column2", "column3"});
  
  for (int ii = 0; ii < 3; ++ii) {
    ui->tableWidget->insertRow(ii);
    ui->tableWidget->setItem(ii, 0, new QTableWidgetItem(QString("%1%2").arg("name ").arg(ii + 1)));
    ui->tableWidget->setItem(ii, 1, new QTableWidgetItem(QString("%1%2").arg("value ").arg(ii + 1)));
    ui->tableWidget->setItem(ii, 2, new QTableWidgetItem(QString("%1%2").arg("class ").arg(ii + 1)));
  }
  
  ui->tableWidget->resizeColumnToContents(1);
}

MainWindow::~MainWindow()
{
  delete ui;
}
