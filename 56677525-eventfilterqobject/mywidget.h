#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QLabel;

class MyWidget : public QWidget
{
  Q_OBJECT
  
public:
  MyWidget(QWidget *parent = nullptr);
  ~MyWidget() = default;
  
protected:
  bool eventFilter(QObject* sender, QEvent* event) override;
  
private:
  QLabel* m_label;
};

#endif // MAINWINDOW_H
