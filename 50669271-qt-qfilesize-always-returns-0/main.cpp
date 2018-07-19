#include <qdebug.h>
#include <qfile.h>
#include <qtextstream.h>

int main(int argc, char* argv[])
{
  QFile f("example.txt");
  qDebug() << "f.size() before opening =" << f.size();

  if (!f.open(QFile::WriteOnly)) {
    qDebug() << "Error: not opened!";
    return 1;
  }

  QTextStream out(&f);
  qDebug() << "f.size() before writing =" << f.size(); // 0: file was overwritten

  out << "Hello world!\n";
  qDebug() << "f.size() after writing =" << f.size(); // may be incorrect
  qDebug() << "f.size() after writing =" << f.pos(); // may be incorrect

  out.flush();
  qDebug() << "f.size() after flushing =" << f.size(); // correct

  f.close();
  qDebug() << "f.size() after closing =" << f.size(); // correct

  return 0;
}
