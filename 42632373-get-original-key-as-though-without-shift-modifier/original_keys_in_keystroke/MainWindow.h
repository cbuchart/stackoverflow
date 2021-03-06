#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

protected:
  virtual void keyPressEvent(QKeyEvent* e) override;

private:
    Ui::MainWindowClass ui;
};
