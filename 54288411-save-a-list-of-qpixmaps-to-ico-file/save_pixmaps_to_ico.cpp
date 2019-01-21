#include <qlist.h>
#include <qpixmap.h>
#include <qfileinfo.h>
#include <qfile.h>
#include <qtemporaryfile.h>

namespace {
  template<typename T>
  void write(QFile& f, const T t)
  {
    f.write((const char*)&t, sizeof(t));
  }
}

bool savePixmapsToICO(const QList<QPixmap>& pixmaps, const QString& path)
{
  static_assert(sizeof(short) == 2, "short int is not 2 bytes");
  static_assert(sizeof(int) == 4, "int is not 4 bytes");

  QFile f(path);
  if (!f.open(QFile::OpenModeFlag::WriteOnly)) return false;

  // Header
  write<short>(f, 0);
  write<short>(f, 1);
  write<short>(f, pixmaps.count());

  QList<int> images_size;
  for (int ii = 0; ii < pixmaps.count(); ++ii) {
    QTemporaryFile temp;
    temp.setAutoRemove(true);
    if (!temp.open()) return false;
    
    const auto& pixmap = pixmaps[ii];
    pixmap.save(&temp, "PNG");

    temp.close();

    images_size.push_back(QFileInfo(temp).size());
  }

  // Images directory
  constexpr unsigned int entry_size = sizeof(char) + sizeof(char) + sizeof(char) + sizeof(char) + sizeof(short) + sizeof(short) + sizeof(unsigned int) + sizeof(unsigned int);
  static_assert(entry_size == 16, "wrong entry size");

  unsigned int offset = 3 * sizeof(short) + pixmaps.count() * entry_size;
  for (int ii = 0; ii < pixmaps.count(); ++ii) {
    const auto& pixmap = pixmaps[ii];
    if (pixmap.width() > 256 || pixmap.height() > 256) continue;

    write<char>(f, pixmap.width() == 256 ? 0 : pixmap.width());
    write<char>(f, pixmap.height() == 256 ? 0 : pixmap.height());
    write<char>(f, 0); // palette size
    write<char>(f, 0); // reserved
    write<short>(f, 1); // color planes
    write<short>(f, pixmap.depth()); // bits-per-pixel
    write<unsigned int>(f, images_size[ii]); // size of image in bytes
    write<unsigned int>(f, offset); // offset
    offset += images_size[ii];
  }

  for (int ii = 0; ii < pixmaps.count(); ++ii) {
    const auto& pixmap = pixmaps[ii];
    if (pixmap.width() > 256 || pixmap.height() > 256) continue;
    pixmap.save(&f, "PNG");
  }

  return true;
}
