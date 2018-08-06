#include "MainWindow.h"

#include <qfontmetrics.h>
#include <qspinbox.h>
#include <qdebug.h>

QString cutString(const QString& str, const QFontMetrics& fm, int pixels)
{
  const QChar ellipsis(0x2026);
  if (fm.width(str) <= pixels) return str;
  auto tmpStr = fm.elidedText(str, Qt::ElideRight, pixels + fm.width(ellipsis));
  return tmpStr.left(tmpStr.length() - 1);
}

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);

  connect(ui.spnPixels, SIGNAL(valueChanged(int)), SLOT(updateStrings()));
  connect(ui.txtSource, SIGNAL(textChanged(QString)), SLOT(updateStrings()));

  updateStrings();
}

void MainWindow::updateStrings()
{
  const auto str = ui.txtSource->text();
  const auto pixels = ui.spnPixels->value();

  QFontMetrics fm(ui.lblNone->font());

  ui.lblNone->setText(cutString(str, fm, pixels));
  ui.lblLeft->setText(fm.elidedText(str, Qt::ElideLeft, pixels));
  ui.lblMiddle->setText(fm.elidedText(str, Qt::ElideMiddle, pixels));
  ui.lblRight->setText(fm.elidedText(str, Qt::ElideRight, pixels));
}
