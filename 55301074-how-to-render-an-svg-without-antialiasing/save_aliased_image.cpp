#include <qimage.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qpainter.h>

QImage convertToAliased(const QImage& source)
{
  const auto mask = QPixmap::fromImage(source.createAlphaMask());

  QImage image(source.size(), QImage::Format_ARGB32);
  image.fill(Qt::transparent);

  QPainter p;
  p.begin(&image);
  p.setClipRegion(QRegion(mask));
  p.drawImage(QPoint(0, 0), source.convertToFormat(QImage::Format_RGB32));
  p.end();

  return image;
}
