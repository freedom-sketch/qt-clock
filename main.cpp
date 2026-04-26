#include "mainwindow.h"

#include <QApplication>

int main (int argc, char *argv[])
{
  QApplication a (argc, argv);

  MainWindow window;
  window.showFullScreen();
  window.show();

  return QApplication::exec ();
}
