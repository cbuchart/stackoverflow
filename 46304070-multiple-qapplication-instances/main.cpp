#include <QtCore>

void oneQApplication(int argc, char* argv[])
{
  qDebug() << __FUNCTION__;

  QTranslator tr1;

  QCoreApplication a1(argc, argv);
  a1.setApplicationName("a1");
  a1.installTranslator(&tr1);
  qDebug() << qApp << &a1;
  qDebug() << "a1.applicationName() =" << a1.applicationName();

  // qApp == &a1
  QObject::connect(&a1, &QCoreApplication::aboutToQuit, []() { qDebug() << "Hello world from a1!"; });
  QTimer::singleShot(2000, &a1, &QCoreApplication::quit); // as if connected to latest qApp

  qDebug() << qApp->removeTranslator(&tr1); // false if the translator is not installed
  a1.installTranslator(&tr1); // it is installed in the latest instance (as if called from qApp)
  qDebug() << qApp->removeTranslator(&tr1); // false if the translator is not installed

  qApp->exec();
  qDebug() << "-----";
}

void twoQApplications(int argc, char* argv[])
{
  qDebug() << __FUNCTION__;

  QTranslator tr1;

  QCoreApplication a1(argc, argv);
  a1.setApplicationName("a1");
  a1.installTranslator(&tr1);
  qDebug() << qApp << &a1;
  qDebug() << "a1.applicationName() =" << a1.applicationName();

  // qApp == &a1
  QObject::connect(&a1, &QCoreApplication::aboutToQuit, []() { qDebug() << "Hello world from a1!"; });
  QTimer::singleShot(2000, &a1, &QCoreApplication::quit); // as if connected to latest qApp

  QCoreApplication a2(argc, argv);
  a2.setApplicationName("a2");
  qDebug() << qApp << &a1 << &a2;
  qDebug() << "a2.applicationName() =" << a2.applicationName();
  qDebug() << "a1.applicationName() =" << a1.applicationName(); // as if called from qApp
  QObject::connect(&a2, &QCoreApplication::aboutToQuit, []() { qDebug() << "Hello world from a2!"; });

  qDebug() << qApp->removeTranslator(&tr1); // false if the translator is not installed
  a1.installTranslator(&tr1); // it is installed in the latest instance (as if called from qApp)
  qDebug() << qApp->removeTranslator(&tr1); // false if the translator is not installed

  qApp->exec();
  qDebug() << "-----";
}

int main(int argc, char* argv[])
{
  oneQApplication(argc, argv);
  twoQApplications(argc, argv);

  return 0;
}
