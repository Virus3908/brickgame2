/// @mainpage
/// @file s21_field.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
#ifndef S21_FIELD_H
#define S21_FIELD_H

#include "s21_defines.h"
#include "s21_frontend.h"
#include "s21_menu.h"

namespace s21 {

/// @brief Класс для виджета игрового поля
class gameField : public QWidget {
  Q_OBJECT
 public:
  /// @brief Конструктор виджета игрового поля
  /// @param parent Указатель на родительский виджет
  /// @param gameName Название игры
  gameField(QWidget *parent = nullptr, gameName_t gameName = Not_a_game);
  /// @brief Деструктор вмджета
  ~gameField();

 signals:
  /// @brief Сигнал для смены виджета
  /// @param newWidget указатель на новый виджет
  void switchToNewWidget(QWidget *newWidget);

 protected:
  /// @brief событие перерисовки
  /// @param event указатель на обытие которое к этому привел
  void paintEvent(QPaintEvent *event) override;
  /// @brief События нажатия клавиши
  /// @param event указатель на событие нажатия на клавишу
  void keyPressEvent(QKeyEvent *event) override;
  /// @brief Событие таймера
  /// @param event указатель на событие таймера
  void timerEvent(QTimerEvent *event) override;
  // void focusInEvent(QFocusEvent *event);

 private:
  /// @brief Создание кнопок
  void createButtons();
  /// @brief Нажатие на кнопку меню
  void menuPressed();
  /// @brief Нажатие на кнопку выхода
  void quitPressed();
  /// @brief Установка стиля кнопки
  /// @param button Ссылка на кнопку
  void setButtonStyle(QPushButton *button);
  /// @brief Отрисовка линий
  /// @param painter Указатель на painter
  void drawMyLine(QPainter *painter);
  /// @brief Отрисовка вспомогательной информации
  /// @param painter Указатель на painter
  void drawHelp(QPainter *painter);
  /// @brief Отрисовка информации игры
  /// @param painter Указатель на painter
  /// @param game Состояние игры
  void drawInfo(QPainter *painter, GameInfo_t game);
  /// @brief Заполнение след фигуры ничем
  /// @param painter Указатель на painter
  void fillNext(QPainter *painter);
  /// @brief Отрисовка поля
  /// @param painter Указатель на painter
  /// @param field Указатель на матрицу с полем
  void drawField(QPainter *painter, int **field);
  /// @brief Отрисовка окошка некст фигуры
  /// @param painter Указатель на painter
  /// @param next указатель на матрицу со след фигурой
  void drawNext(QPainter *painter, int **next);
  /// @brief Окошко с выйгрышем
  /// @param painter Указатель на painter
  void drawYouWin(QPainter *painter);
  /// @brief Окошко с поражением
  /// @param painter Указатель на painter
  void drawYouLose(QPainter *painter);
  /// @brief Пауза
  /// @param painter Указатель на painter
  void drawPause(QPainter *painter);
  /// @brief Старт игры
  /// @param painter Указатель на painter
  void drawPressStart(QPainter *painter);

  /// @brief Указатель на кнопку меню
  QPushButton *button_menu;
  /// @brief Указатель на кнопку выхода
  QPushButton *button_exit;
  /// @brief Назввание игры
  gameName_t _gameName;
  /// @brief Указатель на контроллер
  gameController *controller;
  /// @brief ИД таймера
  int timerId;
};

}  // namespace s21

#endif  // S21_FIELD_H
