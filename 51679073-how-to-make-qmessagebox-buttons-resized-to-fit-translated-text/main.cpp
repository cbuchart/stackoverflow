#include <QtWidgets/QApplication>
#include <qmessagebox.h>
#include <qlayout.h>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  QMessageBox::StandardButtons iButtons = QMessageBox::Save | QMessageBox::Abort | QMessageBox::Cancel;
  QMessageBox msgClose( QMessageBox::Question, "Test", "Test button translation resizing.", iButtons );
  msgClose.setButtonText(QMessageBox::Save, "Save: super mega long text for testing");
  msgClose.setButtonText(QMessageBox::Cancel, "Cancel: another super mega long text for testing");
  msgClose.layout()->setSizeConstraint(QLayout::SetMinimumSize);
  msgClose.exec();

  return 0;
}
