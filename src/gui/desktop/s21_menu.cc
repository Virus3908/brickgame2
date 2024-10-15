#include "s21_menu.h"

namespace s21 {

gameMenu::gameMenu(QWidget *parent) : QWidget{parent} {
  parent->resize(MENU_WINDOW_W, MENU_WINDOW_H);
  parent->setWindowTitle("Brick games");
  this->resize(MENU_WINDOW_W, MENU_WINDOW_H);

  createButtons();

  MainWindow *mainWindow = qobject_cast<MainWindow *>(parent);
  if (mainWindow) {
    connect(this, &gameMenu::switchToNewWidget, mainWindow,
            &MainWindow::setNewWidget);
  }

  // setFocusPolicy(Qt::StrongFocus);
}

gameMenu::~gameMenu() {
  delete button_tetris;
  delete button_snake;
  delete button_exit;
}

void gameMenu::createButtons() {
  button_tetris = new QPushButton("Tetris", this);
  button_snake = new QPushButton("Snake", this);
  button_exit = new QPushButton("Exit", this);

  button_tetris->setGeometry(BUTTON_POS_X, BUTTON_POS_Y, BUTTON_W, BUTTON_H);
  button_snake->setGeometry(BUTTON_POS_X,
                            BUTTON_POS_Y + (BUTTON_H + BUTTON_SPACE_Y),
                            BUTTON_W, BUTTON_H);
  button_exit->setGeometry(BUTTON_POS_X,
                           BUTTON_POS_Y + 2 * (BUTTON_H + BUTTON_SPACE_Y),
                           BUTTON_W, BUTTON_H);

  setButtonStyle(button_tetris);
  setButtonStyle(button_snake);
  setButtonStyle(button_exit);

  connect(button_tetris, &QPushButton::clicked, this, &gameMenu::tetrisPressed);
  connect(button_snake, &QPushButton::clicked, this, &gameMenu::snakePressed);
  connect(button_exit, &QPushButton::clicked, this, &gameMenu::quitPressed);
}

void gameMenu::setButtonStyle(QPushButton *button) {
  button->setStyleSheet(BUTTON_STYLE);
}

void gameMenu::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.fillRect(rect(), BG_COLOR);
}

void gameMenu::tetrisPressed() {
  QWidget *newTetris = new gameField(qobject_cast<QWidget *>(this->parent()),
                                     gameName_t::Tetris);
  emit switchToNewWidget(newTetris);
}

void gameMenu::snakePressed() {
  QWidget *newSnake =
      new gameField(qobject_cast<QWidget *>(this->parent()), gameName_t::Snake);
  emit switchToNewWidget(newSnake);
}

void gameMenu::quitPressed() { QApplication::quit(); }

void gameMenu::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Q) {
    quitPressed();
  }
}

// void gameMenu::focusInEvent(QFocusEvent *event) {
//     qDebug() << "gameMenu получил фокус!";
//     QWidget::focusInEvent(event);  // Вызовем родительский метод для
//     правильной работы
// }

}  // namespace s21