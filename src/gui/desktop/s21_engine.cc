#include <QApplication>
#include <QDir>

#include "s21_frontend.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QFontDatabase::addApplicationFont(":/font/PressStart2P-Regular.ttf");
  s21::MainWindow game;
  game.show();
  return a.exec();
}
