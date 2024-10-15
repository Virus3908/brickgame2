QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    s21_engine.cc \
    s21_field.cc \
    s21_frontend.cc \
    ../../brick_game/snake/s21_apple.cc \
    ../../brick_game/snake/s21_backend_snake.cc \
    ../../brick_game/snake/s21_snake.cc \
    ../../brick_game/tetris/s21_backend_tetris.c \
    ../../brick_game/tetris/s21_helper.c \
    ../../brick_game/tetris/s21_singletones.c \
    ../../brick_game/controller/s21_controller.cc \
    s21_menu.cc

HEADERS += \
    s21_field.h \
    s21_frontend.h \
    s21_defines.h \
    ../../brick_game/snake/s21_apple.h \
    ../../brick_game/snake/s21_backend.h \
    ../../brick_game/snake/s21_snake.h \
    ../../brick_game/tetris/s21_backend.h \
    ../../brick_game/tetris/s21_helper.h \
    ../../brick_game/tetris/s21_singletones.h \
    ../../brick_game/controller/s21_controller.h \
    ../../common/header.h \
    s21_menu.h

RESOURCES += \
    resource.qrc