OS = $(shell uname)
CC = gcc
CXX = g++
GCOV = gcov
ifeq ("$(OS)","Linux")
	LEAKS_RUN_TEST = valgrind --tool=memcheck --leak-check=yes --log-file=1.txt ./test
	PKG =`pkg-config --cflags --libs gtest`
else
	LEAKS_RUN_TEST = leaks -atExit -- ./test
	PKG =`pkg-config --cflags --libs gtest gtest_main`
endif

CSTD = -std=c11
CXXSTD = -std=c++17
CFLAGS = -Wall -Werror -Wextra -pedantic

TETRIS_PATH = brick_game/tetris/
SNAKE_PATH = brick_game/snake/
CLI_PATH = gui/cli/
CONTROLLER_PATH = brick_game/controller/

EXTRA_LIBS = -lm -lncurses $(PKG)
BACKEND_C = $(wildcard $(TETRIS_PATH)*.c)
BACKEND_CC = $(wildcard $(SNAKE_PATH)*.cc)
FRONTEND_CLI = $(wildcard $(CLI_PATH)*.c)
CLI_ENGINE = $(wildcard $(CLI_PATH)*.cc)
CONTROLLER = $(wildcard $(CONTROLLER_PATH)*.cc)


TEST_LIB_C = $(BACKEND_C:.c=.o)
TEST_LIB_C_A = $(TEST_LIB_C:.o=.a)
TEST_LIB_CC = $(BACKEND_CC:.cc=.o) $(CONTROLLER:.cc=.o)
TEST_LIB_CC_A = $(TEST_LIB_CC:.o=.a)

OBJECTS_GCOV_C = $(addprefix gcov_obj/,$(TEST_LIB_C)) 
OBJECTS_GCOV_CC = $(addprefix gcov_obj/,$(TEST_LIB_CC))

all:  install install_cli

install:
	mkdir -p game/
	cd ./gui/desktop && qmake && make && cp ./desktop.app/Contents/MacOS/desktop ../../game/game_desktop.exe
	

install_cli: $(FRONTEND_CLI:.c=.o) $(BACKEND_CC:.cc=.o) $(BACKEND_C:.c=.o) $(CONTROLLER:.cc=.o)
	mkdir -p game/
	$(CXX) $(CFLAGS) $(CXXSTD) $(CLI_ENGINE) $(addprefix obj/,$(^F)) -o game/cli_game.exe $(EXTRA_LIBS)

play_desktop: install
	./game/game_desktop.exe

play_cli: install_cli
	./game/cli_game.exe

%.a: %.o
	mkdir -p obj	
	ar rc obj/$(@F) obj/$(<F)
	ranlib obj/$(@F)

%.o: %.c
	mkdir -p obj
	$(CC) $(CSTD) $(CFLAGS) -g -c $< -o obj/$(@F)

%.o: %.cc
	mkdir -p obj
	$(CXX) $(CXXSTD) $(CFLAGS) -g -c $< -o obj/$(@F)

dvi:
	doxygen
	open ./html/index.html

dist:
	mkdir -p dist
	tar -czvf brick_game.tar ./
	mv brick_game.tar dist/

uninstall: clean
	rm -rf ./game


include ./Makefiles/gcov_report.mk
include ./Makefiles/test.mk
include ./Makefiles/utilites.mk