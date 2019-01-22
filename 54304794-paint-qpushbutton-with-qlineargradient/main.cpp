#include <QApplication>
#include <QGridLayout>
#include <QLinearGradient>
#include <QPalette>
#include <QPushButton>

class ButtonResizeWatcher : public QObject {
protected:
  virtual bool eventFilter(QObject* o, QEvent* e) override {
    if (e->type() == QEvent::Resize) {
      auto button = qobject_cast<QPushButton*>(o);

      QLinearGradient gradient_button(0, 0, button->width(), 0);
      gradient_button.setColorAt(0, Qt::white);
      gradient_button.setColorAt(1, Qt::red);

      auto palette = button->palette();
      palette.setBrush(QPalette::Button, QBrush(gradient_button));
      button->setPalette(palette);
    }

    return QObject::eventFilter(o, e);
  }
};

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  // Create layout
  QGridLayout* layout = new QGridLayout;

  // Create first button
  QPushButton* button_1 = new QPushButton();
  layout->addWidget(button_1, 0, 0);
  QPalette palette_1 = button_1->palette();
  palette_1.setColor(QPalette::Button, Qt::red);
  button_1->setPalette(palette_1);
  button_1->update();

  // Create second button
  QPushButton* button_2 = new QPushButton();
  ButtonResizeWatcher resize_watcher;
  button_2->installEventFilter(&resize_watcher);
  layout->addWidget(button_2, 0, 1);

  // Create widget
  QWidget* widget = new QWidget;
  widget->setLayout(layout);
  widget->resize(300, 50);

  /// Show
  widget->show();

  // Run
  return app.exec();
}