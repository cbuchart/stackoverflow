#include "widget.h"
#include <qpainter.h>
#include <qpolygon.h>

Widget::Widget(QWidget *parent)
  : QWidget(parent),
    m_image(":/qt.png")
{
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *)
{
  qreal r = 35.0 * 3.1415926 / 180.0;
  qreal s = 1.5;
  
  // Image
  auto transform = QTransform().rotateRadians(r).scale(s, s);
  auto image = m_image.transformed(transform, Qt::SmoothTransformation);
  
  QPainter painter(this);
  painter.drawImage(0, 0, image);
  
  const auto rect = m_image.rect();
  QPolygonF pol;
  pol << rect.topLeft();
  pol << rect.topRight();
  pol << rect.bottomRight();
  pol << rect.bottomLeft();
  
  // First transform
  const auto center = rect.center();
  transform = transform.translate(-center.x(), -center.y());
  
  // Second transform
  auto pol2 = transform.map(pol);
  const auto rect2 = pol2.boundingRect();
  
  painter.setPen(Qt::red);
  painter.drawPolygon(QTransform().translate(rect2.width() / 2, rect2.height() / 2).map(pol2));
}
