/// @mainpage
/// @file s21_menu.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
#ifndef S21_MENU_H
#define S21_MENU_H

#include "s21_defines.h"
#include "s21_field.h"
#include "s21_frontend.h"

namespace s21 {
/// @brief класс меню
class gameMenu : public QWidget {
  Q_OBJECT
 public:
  /// @brief Стандартный конструктор
  /// @param parent Указатель на родительское окно
  gameMenu(QWidget *parent = nullptr);
  /// @brief Стандартный деструктор
  ~gameMenu();

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
  // void focusInEvent(QFocusEvent *event);

 private:
  /// @brief Создание кнопок
  void createButtons();
  /// @brief Нажатие на кнопку тетриса
  void tetrisPressed();
  /// @brief Нажатие на кнопку змейки
  void snakePressed();
  /// @brief Нажатие на кнопку входа
  void quitPressed();
  /// @brief Установка стиля кнопки
  /// @param button Указатель на кнопку
  void setButtonStyle(QPushButton *button);

  /// @brief Указатель на кнопку змейки
  QPushButton *button_snake;
  /// @brief Указатель на кнопку тетриса
  QPushButton *button_tetris;
  /// @brief Указатель на кнопку выхода
  QPushButton *button_exit;
};
}  // namespace s21
#endif  // S21_MENU_H
