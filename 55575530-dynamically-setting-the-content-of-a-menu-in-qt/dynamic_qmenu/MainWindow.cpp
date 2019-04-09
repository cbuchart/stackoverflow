#include "MainWindow.h"
#include <qtimer.h>
#include <qthread.h>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);

  connect(ui.menuDynamicMenu, &QMenu::aboutToShow, this, &MainWindow::onMenuAboutToShow);
}

void MainWindow::onMenuAboutToShow()
{
  m_waiting = true;
  QTimer::singleShot(2000, this, [this]() {
    ui.menuDynamicMenu->clear();
    ui.menuDynamicMenu->addAction("Some action from network query");
    ui.menuDynamicMenu->addAction("Another action from network query");

    m_waiting = false;
  });

  while (m_waiting) {
    qApp->processEvents(QEventLoop::WaitForMoreEvents);
  }
}
