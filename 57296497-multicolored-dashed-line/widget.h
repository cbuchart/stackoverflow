#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
  Q_OBJECT
  
public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget();
  
protected:
  virtual void paintEvent(QPaintEvent* event) override;
};

#endif // WIDGET_H
