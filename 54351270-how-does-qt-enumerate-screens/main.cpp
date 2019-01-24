#include <qapplication.h>
#include <qdebug.h>
#include <qscreen.h>
#include <Windows.h>
#include <iostream>

std::ostream& operator<<(std::ostream& of, const RECT& rect)
{
  return of << "RECT(" << rect.left << ", " << rect.top << " " << (rect.right - rect.left) << "x" << (rect.bottom - rect.top) << ")";
}

BOOL CALLBACK printMonitorInfoByHandle(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
  auto index = (int*)dwData;
  std::cout << ++*index << " " << *lprcMonitor << std::endl;
  return TRUE;
}

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  qDebug() << "*** Qt screens ***";
  const auto screens = qApp->screens();
  for (int ii = 0; ii < screens.count(); ++ii) {
    qDebug() << ii+1 << screens[ii]->geometry();
  }

  qDebug() << "*** Windows monitors ***";
  int index = 0;
  EnumDisplayMonitors(NULL, NULL, printMonitorInfoByHandle, (LPARAM)&index);

  return 0;
}
