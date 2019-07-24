#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qimage.h>

class Widget : public QWidget
{
  Q_OBJECT
  
public:
  Widget(QWidget *parent = 0);
  ~Widget();
  
protected:
  virtual void paintEvent(QPaintEvent* event) override;
  
protected:
  QImage m_image;
};

#endif // WIDGET_H
