#include <qtextdocument.h>
#include <qdebug.h>
#include <qregexp.h>

int main(int argc, char* argv[])
{
  const QString content =
    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
    "<html>"
    "    <head>"
    "        <meta name=\"qrichtext\" content=\"1\" />"
    "        <style type=\"text/css\"> p, li { white-space: pre-wrap; } </style>"
    "    </head>"
    "    <body style=\" font-family:'Calibri'; font-size:10pt; font-weight:400; font-style:normal;\">"
    "        <p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
    "            <span style=\" font-family:'Verdana'; color:#0b333c;\">MY TEXT</span>"
    "        </p>"
    "    </body>"
    "</html>";

  qDebug() << "Original content";
  qDebug() << content;
  qDebug() << "";

  QTextDocument doc1;
  doc1.setHtml(content);
  qDebug() << "without removing spaces";
  qDebug() << doc1.toHtml();
  qDebug() << "";

  const QString content2 = QString(content).replace(QRegExp("\\s+<"), "<");
  qDebug() << "Content without spaces";
  qDebug() << content2;
  qDebug() << "";

  QTextDocument doc2;
  doc2.setHtml(content2);
  qDebug() << "without removing spaces";
  qDebug() << doc2.toHtml();

  return 0;
}
