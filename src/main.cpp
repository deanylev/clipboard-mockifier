#include <singleapplication.h>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
  SingleApplication app(argc, argv);
  MainWindow mainWindow;
  return app.exec();
}
