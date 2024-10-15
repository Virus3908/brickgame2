/// @mainpage
/// @file s21_defines.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024

#ifndef S21_DEFINES_H
#define S21_DEFINES_H

#include <QApplication>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>

#include "../../brick_game/controller/s21_controller.h"

/// Размер меню по вертикали
#define MENU_WINDOW_H 180
/// Размер меню по вертикали
#define MENU_WINDOW_W 200

/// Размер кнопки по вертикали
#define BUTTON_H 30
/// Размер кнопки по горизонтали
#define BUTTON_W 120

/// Стартовое положение кнопки по х
#define BUTTON_POS_X (MENU_WINDOW_W - BUTTON_W) / 2
/// Стартовое положение кнопки по у
#define BUTTON_POS_Y 20
/// Пробел между кнопками
#define BUTTON_SPACE_Y 20

/// Размер игрового окна по вертикали
#define GAME_WINDOW_H (MENU_WINDOW_H + 400)
/// Размер игрового окна по горизонтали
#define GAME_WINDOW_W (MENU_WINDOW_W + 600)

/// Стиль кнопки
#define BUTTON_STYLE                    \
  "QPushButton{"                        \
  "border-radius: 5px;"                 \
  "font-family: 'Press Start 2P';"      \
  "border: 0px solid rgb(28, 27, 72);"  \
  "background-color: rgb(97, 95, 137);" \
  "color: LightCyan;"                   \
  "font-size: 12px;"                    \
  "}"                                   \
  "QPushButton:pressed{"                \
  "background-color: rgb(28, 27, 72)"   \
  "}"                                   \
  "QPushButton:hover{"                  \
  "background-color: rgb(47, 45, 90)"   \
  "}"

/// Цвет заднего фона
#define BG_COLOR QColor(70, 68, 114)
/// Цвет линий
#define LINE_COLOR QColor(28, 27, 72)
/// Цвет текста
#define TEXT_COLOR QColor(224, 255, 255)
/// Цвет фона игрового поля
#define FIELD_BG_COLOR QColor(97, 95, 137)
/// Цвет сетки игрового поля
#define GRID_COLOR QColor(28, 27, 72)

/// Цвет для клетки со значением 1
#define SHAPE_COLOR_1 QColor(233, 21, 21)
/// Цвет для клетки со значением 2
#define SHAPE_COLOR_2 QColor(15, 167, 76)
/// Цвет для клетки со значением 3
#define SHAPE_COLOR_3 QColor(75, 165, 169)
/// Цвет для клетки со значением 4
#define SHAPE_COLOR_4 QColor(255, 122, 90)
/// Цвет для клетки со значением 5
#define SHAPE_COLOR_5 QColor(163, 199, 155)
/// Цвет для клетки со значением 6
#define SHAPE_COLOR_6 QColor(237, 238, 185)
/// Цвет для клетки со значением 7
#define SHAPE_COLOR_7 QColor(32, 55, 159)

/// Размер клетки
#define CELL_SIZE 25

/// Положение игрового окна по х
#define FIELD_POS_X ((GAME_WINDOW_W / 2) - (CELL_SIZE) * (W_SIZE / 2))
/// Положение игрового окна по у
#define FIELD_POS_Y ((GAME_WINDOW_H / 2) - (CELL_SIZE) * (H_SIZE / 2))
/// Положение Окна след фигуры по х
#define NEXT_POS_X \
  ((GAME_WINDOW_W - MENU_WINDOW_W / 2) - (CELL_SIZE) * (NEXT_SIZE / 2.0))
/// положение окна след фигуры по у
#define NEXT_POS_Y (MENU_WINDOW_W / 2 - (CELL_SIZE) * (NEXT_SIZE / 2.0)) + 40

#endif