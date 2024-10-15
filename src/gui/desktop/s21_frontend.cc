#include "s21_frontend.h"

namespace s21 {

MainWindow::MainWindow() {
  gameMenu *menu = new gameMenu(this);
  setCentralWidget(menu);
  currentWidget = menu;
}

MainWindow::~MainWindow() {
  if (currentWidget) {
    delete currentWidget;
  }
}

void MainWindow::setNewWidget(QWidget *newWidget) {
  if (currentWidget) {
    currentWidget->deleteLater();
  }
  setCentralWidget(newWidget);
  currentWidget = newWidget;
  newWidget->setFocus();
}

// QPushButton *MainWindow::createButton(std::function<void()> buttonAction,
// char *buttonName){
//   static int count_button = 0;
//   QPushButton *button = new QPushButton(buttonName, this);
//   button->setGeometry(BUTTON_POS_X, BUTTON_POS_Y + count_button * BUTTON_H,
//   BUTTON_W, BUTTON_H); connect(button, &QPushButton::clicked, this,
//   buttonAction);
// }

}  // namespace s21