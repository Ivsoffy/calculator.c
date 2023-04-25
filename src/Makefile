CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -lgcov --coverage

SOURCES = $(wildcard s21_*.c)
OBJECTS = $(SOURCES:.c=.o)

all: install

rebuild: clean all

gcov_report: clean
	$(CC) -c $(SOURCES) $(GCOVFLAGS)
	$(CC) test.c -c -g 
	$(CC) test.o -g -lcheck $(OBJECTS) -o test $(GCOVFLAGS)
	-./test 2> /dev/null
	lcov -t "t" -o test.info -c -d .
	genhtml -o report test.info 
	open ./report/index.html
	rm -f test

test: clean
	$(CC) -c s21_smartcalc.c
	$(CC) -g -o test $(OBJECTS) test.c -lcheck
	./test 2> /dev/null

clean:
	rm -rf *.install* build/ test.dSYM/ *.a *.o test *.gcda *.gcno *.info report *.input *.output */*.exe *.err *.result

clang_format:
	clang-format -n -i -style=Google *.c *.h

install: build
	-mkdir SmartCalc_v1.0
	cp -rf build/SmartCalc.app SmartCalc_v1.0/

build: clean
	-mkdir build
	cd build; qmake ../SmartCalc/SmartCalc.pro
	make -C build > /dev/null

uninstall:
	rm -rf SmartCalc_v1.0/

dist:
	tar -czf SmartCalc.install.tar.gz ./*

dvi:
	open ./dvi.html