#include <qapplication.h>
#include <qwidget.h>
#include <qtabwidget.h>
#include <qtabbar.h>
#include <qproxystyle.h>
#include <qstyleoption.h>

class TabBackgroundProxyStyle_Index : public QProxyStyle {
public:
  TabBackgroundProxyStyle_Index(const QString& base_style_name, const QMap<int, QBrush>& backgrounds)
    : QProxyStyle(base_style_name),
      m_backgrounds(backgrounds) {
  }

  void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const override {
    if (element == CE_TabBarTab) {
      if (auto tab = qstyleoption_cast<const QStyleOptionTab*>(option)) {
        auto tabBar = qobject_cast<const QTabBar*>(widget);
        for (auto index : m_backgrounds.keys()) {
          if (tab->rect == tabBar->tabRect(index)) {
            QStyleOptionTab opt(*tab);
            opt.palette.setBrush(QPalette::Background, m_backgrounds[index]);
            return QProxyStyle::drawControl(element, &opt, painter, widget);
          }
        }
      }
    }
    QProxyStyle::drawControl(element, option, painter, widget);
  }

private:
  const QMap<int, QBrush> m_backgrounds;
};

class TabBackgroundProxyStyle_Label : public QProxyStyle {
public:
  TabBackgroundProxyStyle_Label(const QString& base_style_name, const QMap<QString, QBrush>& backgrounds)
    : QProxyStyle(base_style_name),
      m_backgrounds(backgrounds) {
  }

  void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const override {
    if (element == CE_TabBarTab) {
      if (auto tab = qstyleoption_cast<const QStyleOptionTab*>(option)) {
        if (m_backgrounds.contains(tab->text)) {
          QStyleOptionTab opt(*tab);
          opt.palette.setBrush(QPalette::Background, m_backgrounds[tab->text]);
          return QProxyStyle::drawControl(element, &opt, painter, widget);
        }
      }
    }
    QProxyStyle::drawControl(element, option, painter, widget);
  }

private:
  const QMap<QString, QBrush> m_backgrounds;
};

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  const QMap<int, QBrush> backgrounds_index = {
    {1, QBrush(Qt::red)},
    {4, QBrush("#c0b050")},
  };

  const QMap<QString, QBrush> backgrounds_label = {
    {"Tab 2", QBrush(Qt::red)},
    {"Tab 7", QBrush("#c0b050")},
  };

  auto theTabWidget1 = new QTabWidget();
  theTabWidget1->tabBar()->setStyle(new TabBackgroundProxyStyle_Index("", backgrounds_index));
  for (int ii = 0; ii < 10; ++ii) theTabWidget1->addTab(new QWidget(), QString("Tab %1").arg(ii + 1));
  theTabWidget1->show();

  auto theTabWidget2 = new QTabWidget();
  theTabWidget2->tabBar()->setStyle(new TabBackgroundProxyStyle_Label("", backgrounds_label));
  for (int ii = 0; ii < 10; ++ii) theTabWidget2->addTab(new QWidget(), QString("Tab %1").arg(ii + 1));
  theTabWidget2->show();

  return a.exec();
}
