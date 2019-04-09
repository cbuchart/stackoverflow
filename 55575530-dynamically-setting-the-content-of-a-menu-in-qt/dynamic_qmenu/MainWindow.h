#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_dynamic_qmenu.h"
#include <atomic>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = Q_NULLPTR);

protected slots:
  void onMenuAboutToShow();

private:
  Ui::dynamic_qmenuClass ui;
  std::atomic<bool> m_waiting = false;
};
