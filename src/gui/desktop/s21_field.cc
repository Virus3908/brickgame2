#include "s21_field.h"

namespace s21 {

gameField::gameField(QWidget *parent, gameName_t gameName)
    : QWidget{parent},
      _gameName(gameName),
      controller(new gameController(gameName)) {
  parent->resize(GAME_WINDOW_W, GAME_WINDOW_H);
  this->resize(GAME_WINDOW_W, GAME_WINDOW_H);
  if (gameName == gameName_t::Tetris) {
    parent->setWindowTitle("Tetris");
  } else if (gameName == gameName_t::Snake) {
    parent->setWindowTitle("Snake");
  }

  createButtons();

  MainWindow *mainWindow = qobject_cast<MainWindow *>(parent);
  if (mainWindow) {
    connect(this, &gameField::switchToNewWidget, mainWindow,
            &MainWindow::setNewWidget);
  }
  timerId = startTimer(controller->getGameInfo().speed * 100);
  setFocusPolicy(Qt::StrongFocus);
}

gameField::~gameField() {
  delete controller;
  delete button_exit;
  delete button_menu;
}

void gameField::createButtons() {
  button_menu = new QPushButton("Menu", this);
  button_exit = new QPushButton("Exit", this);

  button_menu->setGeometry(BUTTON_POS_X, BUTTON_POS_Y + BUTTON_SPACE_Y,
                           BUTTON_W, BUTTON_H);
  button_exit->setGeometry(BUTTON_POS_X,
                           BUTTON_POS_Y + (BUTTON_H + 2 * BUTTON_SPACE_Y),
                           BUTTON_W, BUTTON_H);

  setButtonStyle(button_menu);
  setButtonStyle(button_exit);

  connect(button_menu, &QPushButton::clicked, this, &gameField::menuPressed);
  connect(button_exit, &QPushButton::clicked, this, &gameField::quitPressed);
}

void gameField::setButtonStyle(QPushButton *button) {
  button->setStyleSheet(BUTTON_STYLE);
}

void gameField::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.fillRect(rect(), BG_COLOR);
  painter.setFont(QFont("Press Start 2P", 12));
  drawMyLine(&painter);
  drawHelp(&painter);
  controller->getUserInput();
  controller->updateState();
  GameInfo_t game = controller->getGameInfo();
  if (game.pause == 0) {
    drawInfo(&painter, game);
    if (game.field) {
      drawField(&painter, game.field);
    } else {
      drawPressStart(&painter);
    }
    if (game.next) {
      drawNext(&painter, game.next);
    }
  } else if (game.pause == 1) {
    drawPause(&painter);
  } else if (game.pause == 2) {
    drawYouWin(&painter);
  } else if (game.pause == 3) {
    drawYouLose(&painter);
  }
}

void gameField::drawYouWin(QPainter *painter) {
  QRect textRect(0, 0, GAME_WINDOW_W, GAME_WINDOW_H);
  painter->setPen(TEXT_COLOR);
  painter->setFont(QFont("Press Start 2P", 36));
  painter->drawText(textRect, Qt::AlignCenter, QString("YOU WIN"));
}

void gameField::drawPause(QPainter *painter) {
  QRect textRect(0, 0, GAME_WINDOW_W, GAME_WINDOW_H);
  painter->setPen(TEXT_COLOR);
  painter->setFont(QFont("Press Start 2P", 36));
  painter->drawText(textRect, Qt::AlignCenter, QString("PAUSE"));
}

void gameField::drawYouLose(QPainter *painter) {
  QRect textRect(0, 0, GAME_WINDOW_W, GAME_WINDOW_H);
  painter->setPen(TEXT_COLOR);
  painter->setFont(QFont("Press Start 2P", 36));
  painter->drawText(textRect, Qt::AlignCenter, QString("YOU LOSE"));
}

void gameField::drawPressStart(QPainter *painter) {
  QRect textRect(0, 0, GAME_WINDOW_W, GAME_WINDOW_H);
  painter->setPen(TEXT_COLOR);
  painter->setFont(QFont("Press Start 2P", 36));
  painter->drawText(textRect, Qt::AlignCenter, QString("PRESS\n\nSTART"));
}

void gameField::drawMyLine(QPainter *painter) {
  QPen pen(LINE_COLOR);
  pen.setWidth(1);
  painter->setPen(pen);
  painter->drawLine(MENU_WINDOW_W, 0, MENU_WINDOW_W, GAME_WINDOW_H);
  painter->drawLine(GAME_WINDOW_W - MENU_WINDOW_W, 0,
                    GAME_WINDOW_W - MENU_WINDOW_W, GAME_WINDOW_H);
  painter->drawLine(0, MENU_WINDOW_H, MENU_WINDOW_W, MENU_WINDOW_H);
}

void gameField::drawHelp(QPainter *painter) {
  QRect textRect(0, MENU_WINDOW_H, MENU_WINDOW_W,
                 GAME_WINDOW_H - MENU_WINDOW_H);
  painter->setPen(TEXT_COLOR);
  painter->setFont(QFont("Press Start 2P", 10));
  painter->drawText(textRect, Qt::AlignCenter,
                    QString("Enter - START \n\n"
                            "E - MENU\n\n"
                            "Q - EXIT\n\n"
                            "P - PAUSE\n\n"
                            "SPACE - ACTION\n\n"
                            "LEFT\n\n"
                            "RIGHT\n\n"
                            "UP\n\n"
                            "DOWN"));
}

void gameField::drawInfo(QPainter *painter, GameInfo_t game) {
  QRect textRect(GAME_WINDOW_W - MENU_WINDOW_W + 20, MENU_WINDOW_H,
                 GAME_WINDOW_W, GAME_WINDOW_H - MENU_WINDOW_H);
  painter->setPen(TEXT_COLOR);
  QString infoText = QString(
                         "Score:\n\n"
                         "%1\n\n"
                         "High score:\n\n"
                         "%2\n\n"
                         "Level:\n\n"
                         "%3\n\n\n\n\n")
                         .arg(game.score)
                         .arg(game.high_score)
                         .arg(game.level);
  painter->drawText(textRect, Qt::AlignVCenter, infoText);
}

void gameField::drawField(QPainter *painter, int **field) {
  painter->setPen(GRID_COLOR);
  QColor colors[8] = {FIELD_BG_COLOR, SHAPE_COLOR_1, SHAPE_COLOR_2,
                      SHAPE_COLOR_3,  SHAPE_COLOR_4, SHAPE_COLOR_5,
                      SHAPE_COLOR_6,  SHAPE_COLOR_7};
  for (int i = 0; i < H_SIZE; ++i) {
    for (int j = 0; j < W_SIZE; ++j) {
      if (field[i][j] < 8)
        painter->fillRect(FIELD_POS_X + (CELL_SIZE)*j,
                          FIELD_POS_Y + (CELL_SIZE)*i, CELL_SIZE, CELL_SIZE,
                          colors[field[i][j]]);
      painter->drawRect(FIELD_POS_X + (CELL_SIZE)*j,
                        FIELD_POS_Y + (CELL_SIZE)*i, CELL_SIZE, CELL_SIZE);
    }
  }
}

void gameField::drawNext(QPainter *painter, int **next) {
  painter->setPen(TEXT_COLOR);
  painter->drawText(
      QRect(NEXT_POS_X, NEXT_POS_Y - 40, CELL_SIZE * NEXT_SIZE, CELL_SIZE),
      Qt::AlignCenter, QString("NEXT"));
  painter->setPen(GRID_COLOR);
  QColor colors[8] = {FIELD_BG_COLOR, SHAPE_COLOR_1, SHAPE_COLOR_2,
                      SHAPE_COLOR_3,  SHAPE_COLOR_4, SHAPE_COLOR_5,
                      SHAPE_COLOR_6,  SHAPE_COLOR_7};
  for (int i = 0; i < NEXT_SIZE; ++i) {
    for (int j = 0; j < NEXT_SIZE; ++j) {
      if (next[i][j] < 8)
        painter->fillRect(NEXT_POS_X + (CELL_SIZE)*j,
                          NEXT_POS_Y + (CELL_SIZE)*i, CELL_SIZE, CELL_SIZE,
                          colors[next[i][j]]);
      painter->drawRect(NEXT_POS_X + (CELL_SIZE)*j, NEXT_POS_Y + (CELL_SIZE)*i,
                        CELL_SIZE, CELL_SIZE);
    }
  }
}

void gameField::menuPressed() {
  QWidget *newMenu = new gameMenu(qobject_cast<QWidget *>(this->parent()));
  emit switchToNewWidget(newMenu);
}

void gameField::quitPressed() { QApplication::quit(); }

void gameField::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
      controller->updateUserAction(UserAction_t::Left, event->isAutoRepeat());
      break;
    case Qt::Key_Right:
      controller->updateUserAction(UserAction_t::Right, event->isAutoRepeat());
      break;
    case Qt::Key_Up:
      controller->updateUserAction(UserAction_t::Up, event->isAutoRepeat());
      break;
    case Qt::Key_Down:
      controller->updateUserAction(UserAction_t::Down, event->isAutoRepeat());
      break;
    case Qt::Key_E:
      controller->updateUserAction(UserAction_t::Exit_game,
                                   event->isAutoRepeat());
      menuPressed();
      break;
    case Qt::Key_Q:
      controller->updateUserAction(UserAction_t::Terminate,
                                   event->isAutoRepeat());
      quitPressed();
      break;
    case Qt::Key_Return:
      controller->updateUserAction(UserAction_t::Start, event->isAutoRepeat());
      break;
    case Qt::Key_Space:
      controller->updateUserAction(UserAction_t::Action, event->isAutoRepeat());
      break;
    case Qt::Key_P:
      controller->updateUserAction(UserAction_t::Pause, event->isAutoRepeat());
      break;
    default:
      controller->updateUserAction(UserAction_t::Nothing,
                                   event->isAutoRepeat());
  }

  this->repaint();
}

void gameField::timerEvent(QTimerEvent *) {
  controller->makeStep();
  controller->updateUserAction(UserAction_t::Nothing, false);
  this->repaint();
  killTimer(timerId);
  timerId = startTimer(controller->getGameInfo().speed * 100);
}

// void gameField::focusInEvent(QFocusEvent *event) {
//   qDebug() << "gameField получил фокус!";
//   QWidget::focusInEvent(
//       event);  // Вызовем родительский метод для правильной работы
// }

}  // namespace s21