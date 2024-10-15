/// @mainpage
/// @file s21_frontend.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
#ifndef S21_FRONTEND_H
#define S21_FRONTEND_H

#include "s21_defines.h"
#include "s21_field.h"
#include "s21_menu.h"

namespace s21 {

/// @brief Класс основного окна
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /// @brief Базовый конструктор
  MainWindow();
  /// @brief Базоывй деструктор
  ~MainWindow();

 public slots:
  /// @brief Метод вызываемый при получении сигнала
  /// @param newWidget укзатель на новый виджет
  void setNewWidget(QWidget *newWidget);

 private:
  /// @brief Указатель на нынешний виджет
  QWidget *currentWidget;
};

}  // namespace s21
#endif  // S21_FRONTEND_H
