#include "MainWindow.h"
#include <qkeysequence.h>
#include <qevent.h>
#include <qdebug.h>
#include <Windows.h>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
}

void MainWindow::keyPressEvent(QKeyEvent* ke)
{
  const auto vk = ke->nativeVirtualKey();
  const auto unshifted_key = MapVirtualKeyA(vk, MAPVK_VK_TO_CHAR);

  qDebug() << "Original key:" << (char)ke->key();
  qDebug() << "Unshifted key:" << (char)unshifted_key;

  if (unshifted_key > 0) {
    // Printing the full key sequence just for comparison purposes
    QString modifier;
    if (ke->modifiers() & Qt::ShiftModifier) modifier += "Shift+";
    if (ke->modifiers() & Qt::ControlModifier) modifier += "Ctrl+";
    if (ke->modifiers() & Qt::AltModifier) modifier += "Alt+";
    if (ke->modifiers() & Qt::MetaModifier) modifier += "Meta+";
    const QKeySequence ks(modifier + QChar(ke->key()));
    qDebug() << "Full key sequence:" << ks.toString();
  }
}
