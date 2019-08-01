#include "widget.h"
#include <qpainter.h>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
{
}

Widget::~Widget()
{  
}

namespace {
  void drawWithManualDashedLine(QPainter& painter, const QLine& line) {
    const int scale = 10;

    QPen pen;
    pen.setWidth(3);
    
    pen.setColor(Qt::red);
    pen.setDashPattern({ 0.0, 1.0 * scale, 1.0 * scale, 7.0 * scale });
    painter.setPen(pen);
    painter.drawLine(line);
  
    pen.setColor(Qt::green);
    pen.setDashPattern({ 0.0, 4.0 * scale, 1.0 * scale, 4.0 * scale});
    painter.setPen(pen);
    painter.drawLine(line);
  
    pen.setColor(Qt::blue);
    pen.setDashPattern({ 0.0, 7.0 * scale, 1.0 * scale, 1.0 *scale });
    painter.setPen(pen);
    painter.drawLine(line);    
  }

  void drawMultiColorDashedLine(QPainter& painter, const QLine& line, int length, int gap, int width, const QList<QColor>& colors, bool startWithGap = false) {
    const int n = colors.count();
    const int initialGap = startWithGap ? gap : 0;
    
    QPen pen;
    pen.setWidth(width);
    pen.setDashPattern({ (qreal)length, (qreal)(gap * n + length * (n - 1)) });
    for (int ii = 0; ii < n; ++ii) {
      pen.setColor(colors[ii]);
      pen.setDashOffset(-ii * (length + gap) - initialGap);
      painter.setPen(pen);
      painter.drawLine(line);
    }
  }
}

void Widget::paintEvent(QPaintEvent*)
{
  QPainter painter(this);
  
  const QLine line1(0, height() / 2, width(), height() / 2);
  drawWithManualDashedLine(painter, line1);
 
  const QLine line2(0, height() / 3, width(), height() / 3);
  drawMultiColorDashedLine(painter, line2, 10, 20, 3, { Qt::blue, Qt::yellow }, true);

  const QLine line3(0, 2 * height() / 3, width(), 2 * height() / 3);
  drawMultiColorDashedLine(painter, line3, 10, 20, 3, { Qt::red, Qt::black, Qt::blue, Qt::magenta }, false);
}
