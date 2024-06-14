ifeq ($(shell uname -s),Linux)
    CHECK_FLAGS = $(shell pkg-config --libs gtest --cflags)
endif
ifeq ($(shell uname -s),Darwin)
    CHECK_FLAGS = $(shell pkg-config --libs gtest --cflags)
endif
CC = g++
ADD_FLAG = -std=c++17 --coverage
CFLAGS = -Wall -Werror -Wextra
now:=$(shell date)

all: test_all

test: clean
	$(CC) $(CFLAGS) $(ADD_FLAG) -c --coverage tests/*.cc
	$(CC) $(ADD_FLAG) *.o ${CHECK_FLAGS} -o run_tests

test_all: test
	./run_tests

valgrind: clean
	$(CC) $(CFLAGS) $(ADD_FLAG) -c  -g0 -O0 tests/*.cc
	$(CC) $(ADD_FLAG) *.o ${CHECK_FLAGS} -o run_tests
	valgrind --leak-check=yes --track-origins=yes ./run_tests

gcov_report: clean test
	./run_tests
	lcov -t "test" -o  test.info --no-external -c -d  .
	genhtml -o report test.info

style:
	clang-format -style=google -i tests/*  containers/*.h containers_plus/*.h
	clang-format -style=google -n tests/*  containers/*.h containers_plus/*.h

push: clean
	git add -A
	git commit -m "update ${now}"
	git push origin develop

clean: 
	rm -rf *.o *.a *.gcno *.gcda run_tests run_hand_tests *.info report

leaks: test
	leaks -atExit -- ./run_tests

cpp_check:
	cppcheck --language=c++ --suppress=missingIncludeSystem *.h containers/*.h containers_plus/*.h tests/*.cc tests/*.h
