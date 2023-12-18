CC               = g++
STANDART         = --std=c++17
DEBUG 			 = -g
CFLAGS           = -Wall -Werror -Wextra -Weffc++ $(DEBUG)
OUT              = -o
RM               = rm -rf
GTEST_FLAGS      = -lgtest
GCOV_FLAG        = --coverage
TEST_TARGET      = graph_test
TEST_DIR         = tests
REPORT_DIR       = gcov_report

ifeq ($(shell uname), Linux)
	GTEST_FLAGS      += -lpthread
endif

HEADERS          = model/graph/s21_graph.h \
                   model/matrix/s21_matrix.h \
				   model/graph_algorithm/s21_graph_algorithm.h

TEST_SRCS        = $(TEST_DIR)/test.cc \
				   $(TEST_DIR)/bfstest.cc \
				   $(TEST_DIR)/dfstest.cc \
				   $(TEST_DIR)/tsptest.cc \
				   $(TEST_DIR)/betweenallverticestest.cc \
				   $(TEST_DIR)/betweenverticestest.cc \
				   $(TEST_DIR)/minspantreetest.cc

SRCS			 = model/graph/s21_graph.cc \
				   model/matrix/s21_matrix.cc \
				   model/graph_algorithm/s21_graph_algorithm.cc \
				   model/graph_algorithm/s21_tsp.cc \
				   model/interface/interface.cc

TEST_OBJS        = $(TEST_SRCS:.cc=.o)

OBJS			 = $(SRCS:.cc=.o)

all: gcov_report main

main:
	$(CC) $(SRCS) model/main.cc -o main
	./main
	rm -f main

clean:
	$(RM) .clang-format *.gcda *.gcno *.gcov *.info gcov_report
	$(RM) model/graph/a.out model/graph_algorithm/a.out $(OBJS) *.a *.o
	cd $(TEST_DIR) $(RM) $(TEST_TARGET) $(TEST_OBJS)
	rm -rf graph_test main

test:
	$(CC) $(STANDART) $(SRCS) $(TEST_SRCS) $(GCOV_FLAG) $(GTEST_FLAGS) -o graph_test
	./$(TEST_TARGET)

gcov_report: test
	@lcov --directory . -t "graph_test" -o s21_graph.info -c --no-external
	@lcov -r s21_graph.info '*/model/*.h' '*/model/graph/*' '*/model/interface/*' '*/model/matrix/*' -o s21_graph.info
	@genhtml $(OUT) $(REPORT_DIR) s21_graph.info

build:
	$(CC) $(SRCS) model/main.cc model/interface/interface.cc -o out

debug:
	$(CC) $(SRCS) model/main.cc model/interface/interface.cc -g

s21_graph.o: model/graph/s21_graph.cc
	$(CC) -c $^ $(CFLAGS) $(STANDART) $(OUT) $@

s21_graph_algorithm.o: model/graph_algorithm/s21_graph_algorithm.cc
	$(CC) -c $^ $(CFLAGS) $(STANDART) $(OUT) $@

s21_graph.a: s21_graph.o
	ar rcs s21_graph.a s21_graph.o
	ranlib s21_graph.a

s21_graph_algorithm.a: s21_graph_algorithm.o
	ar rcs s21_graph_algorithm.a s21_graph_algorithm.o
	ranlib s21_graph_algorithm.a
	
clang:
	cp -f ../materials/linters/.clang-format clang-format
	#clang-format -i model/graph/*.* model/graph_algorithm/*.* model/matrix/*.* model/interface/*.*
	clang-format -n model/graph/*.* model/graph_algorithm/*.* model/matrix/*.* model/interface/*.*
	rm -rf clang-format

leaks: test
	CK_FORK=no leaks --atExit -- ./graph_test

rebuild: clean all
