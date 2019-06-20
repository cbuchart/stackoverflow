#include "mywidget.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qdebug.h>
#include <qevent.h>

MyWidget::MyWidget(QWidget *parent)
  : QWidget(parent)
{
  m_label = new QLabel("Hello world!");
  m_label->setObjectName("m_label");
  m_label->installEventFilter(this);
  m_label->setMouseTracking(true);
  
  auto hlayout = new QVBoxLayout();
  hlayout->addWidget(m_label);
  setLayout(hlayout);
}

bool MyWidget::eventFilter(QObject* sender, QEvent* event)
{
  if (sender == m_label) {
    qDebug() << sender->objectName() << event->type();
    
    if (event->type() == QEvent::Enter) {
      qDebug() << "mouse on label name";
    } else if (event->type() == QEvent::Leave) {
      qDebug() << "mouse not on label name";
    }
  }
  
  return QWidget::eventFilter(sender, event);
}
