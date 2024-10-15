CLANG_FORMAT = ../materials/linters/.clang-format

clang:
	clang-format --style=file:$(CLANG_FORMAT) -i $(TETRIS_PATH)*.c \
	$(TETRIS_PATH)*.h $(SNAKE_PATH)*.cc $(SNAKE_PATH)*.h \
	$(CLI_PATH)*.c $(CLI_PATH)*.cc $(CLI_PATH)*.h \
	$(CONTROLLER_PATH)*.cc $(CONTROLLER_PATH)*.h \
	gui/desktop/*.cc gui/desktop/*.h

clang_check:
	clang-format --style=file:$(CLANG_FORMAT) -n $(TETRIS_PATH)*.c \
	$(TETRIS_PATH)*.h $(SNAKE_PATH)*.cc $(SNAKE_PATH)*.h \
	$(CLI_PATH)*.c $(CLI_PATH)*.cc $(CLI_PATH)*.h \
	$(CONTROLLER_PATH)*.cc $(CONTROLLER_PATH)*.h

check:
	cppcheck -q --enable=warning,portability --check-level=exhaustive --inconclusive ./

#.PHONY: all clean rebuild clang check

clean:
	rm -rf $(LIBS) $(TEST_LIB) *.o *.so *.a *.out *.gcda *.gcno *.info test test.c test_gcov report obj gcov_obj tetris
	rm -rf ./html ./latex
	rm -f *.txt
	rm -rf ./dist
	rm -rf ./gui/desktop/desktop.app
	rm -f ./gui/desktop/*.o
	rm -f ./gui/desktop/Makefile ./gui/desktop/desktop.pro.user ./gui/desktop/moc_predefs.h ./gui/desktop/ui_s21_ui.h ./gui/desktop/.qmake.stash ./gui/desktop/*.cpp
	

rebuild: clean all