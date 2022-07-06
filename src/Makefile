GREEN   =   \033[0;32m
RED		=   \033[0;31m
RESET	=   \033[0m

CC=gcc
# Дефолтное значение 1 если не задано с консоли
# Задаем так: make test MODE=4
MODE?=1
ifeq ($(MODE), 2)
	# Собираем с fsanitizer
	ZSH_MESSAGE=BUILD WITH fsanitizer!
	LFLAGS=-g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover \
	-fstack-protector -fanalyzer
	CFLAGS=-Wall -Werror -Wextra -c -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable \
	-fno-sanitize-recover -fstack-protector -fanalyzer
else 
	ifeq ($(MODE), 3)
		# Собираем с отладочной информацией для valgrind
		ZSH_MESSAGE=BUILD FOR valgrind!
    	LFLAGS=-g
    	CFLAGS=-Wall -Werror -Wextra -c -g
    else 
		ifeq ($(MODE), 4)
        	# Собираем со всеми флагами проверок и пишем идеальный код
			ZSH_MESSAGE=BUILD PERFECT CODE!
        	LFLAGS=-g -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -fanalyzer
			CFLAGS=-Wall -Werror -Wextra -c -g -O2 -pedantic -std=c11 -Wshadow -Wlogical-op -Wshift-overflow=2 \
			-Wduplicated-cond -Wcast-align -Wfloat-equal -Wconversion -Wcast-qual -D_GLIBCXX_DEBUG \
			-D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined \
			-fno-sanitize-recover -fstack-protector -fanalyzer
    	else
			# Стандартный режим
			ZSH_MESSAGE=BUILD BASIC!
        	LFLAGS= 
        	CFLAGS=-Wall -Werror -Wextra -c -std=c11
		endif
	endif
endif

# Флаги для lcov
GCOV_FLAGS =-fprofile-arcs -ftest-coverage

ODIR = obj/
TDIR = tests/
RDIR = report/
MDIR = s21_decimal/
GDIR = gcov/

MAIN_TEST_C = s21_decimal_test.c
MAINT_TEST_H = $(TDIR)test.h
DECIMAL_H = s21_decimal.h
ALL_TEST_C = $(wildcard $(TDIR)*.c)
ALL_DECIMAL_C = $(wildcard $(MDIR)*.c)
MAIN_TEST_O = $(MAIN_TEST_C:%.c=$(ODIR)%.o)
ALL_TEST_O = $(ALL_TEST_C:$(TDIR)%.c=$(ODIR)$(TDIR)%.o)
ALL_DECIMAL_O = $(ALL_DECIMAL_C:$(MDIR)%.c=$(ODIR)$(MDIR)%.o)
ALL_DECIMAL_GCOV_O = $(ALL_DECIMAL_C:$(MDIR)%.c=$(ODIR)$(GDIR)%.o)

all: test gcov_report

test: $(ODIR) $(ODIR)$(TDIR) $(ODIR)$(MDIR) s21_decimal.a $(ALL_TEST_O) $(MAIN_TEST_O)
	@echo "\n------------------------------------------------------------"
	@$(CC) $(LFLAGS) $(ALL_TEST_O) $(MAIN_TEST_O) -lcheck s21_decimal.a -o ./test
	@echo "Build: ./test";
	@echo "------------------------------------------------------------"
	@./test

gcov_report: $(ODIR) $(ODIR)$(TDIR) $(ODIR)$(MDIR) $(RDIR) $(ODIR)$(GDIR) libs21_decimal_gcov.a $(ALL_TEST_O) $(MAIN_TEST_O)
	@echo "\n------------------------------------------------------------"
	@$(CC) $(LFLAGS) $(ALL_TEST_O) $(MAIN_TEST_O) -L. -ls21_decimal_gcov -lcheck -lgcov -o ./gcov_report
	@echo "Build: ./gcov_report";
	@echo "------------------------------------------"
	@./gcov_report
	@echo "------------------------------------------"
	gcov -o $(ODIR)$(GDIR) $(ALL_DECIMAL_C)
	@echo "------------------------------------------"
	@lcov -b ./ -d $(ODIR)$(GDIR) --gcov-tool /usr/bin/gcov -c -o output.info
	@genhtml -o $(RDIR) output.info
	@rm *.c.gcov output.info
	@echo "------------------------------------------"
	open $(RDIR)index.html

s21_decimal.a: $(ODIR) $(ODIR)$(MDIR) $(ALL_DECIMAL_O)
	@echo "$(GREEN)*$(RESET)\c"
	@ar rc s21_decimal.a $(ALL_DECIMAL_O)
	@ranlib s21_decimal.a

libs21_decimal_gcov.a: $(ODIR) $(ODIR)$(GDIR) $(ALL_DECIMAL_GCOV_O)
	@echo "$(GREEN)*$(RESET)\c"
	@ar rc libs21_decimal_gcov.a $(ALL_DECIMAL_GCOV_O)
	@ranlib libs21_decimal_gcov.a

$(ODIR)$(MDIR)%.o: $(MDIR)%.c $(DECIMAL_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(CC) $(CFLAGS) -o $@ $<

$(ODIR)$(GDIR)%.o: $(MDIR)%.c $(DECIMAL_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $@ $<

$(ODIR)$(TDIR)%.o: $(TDIR)%.c $(MAINT_TEST_H)
	@echo "$(GREEN)*$(RESET)\c"
	@$(CC) $(CFLAGS) -o $@ $<

$(MAIN_TEST_O): $(MAIN_TEST_C)
	@echo "$(GREEN)*$(RESET)\c"
	@$(CC) $(CFLAGS) -o $@ $<

$(RDIR):
	@mkdir -p $(RDIR)
	@echo "folder: $(GREEN)$(RDIR) was created$(RESET)"
$(ODIR):
	@mkdir -p $(ODIR)
	@echo "folder: $(GREEN)$(ODIR) was created$(RESET)"
$(ODIR)$(TDIR):
	@mkdir -p $(ODIR)$(TDIR)
	@echo "folder: $(GREEN)$(ODIR)$(TDIR) was created$(RESET)"
$(ODIR)$(MDIR):
	@mkdir -p $(ODIR)$(MDIR)
	@echo "folder: $(GREEN)$(ODIR)$(MDIR) was created$(RESET)"
$(ODIR)$(GDIR):
	@mkdir -p $(ODIR)$(GDIR)
	@echo "folder: $(GREEN)$(ODIR)$(GDIR) was created$(RESET)"

clean:
	rm -rf $(ODIR)
	rm -f *.a
	rm -f *.gcno *.gcov *.gcda output.info
	rm -rf $(RDIR)
	rm -f ./gcov_report ./test

rebuild: clean all

cpplint: 
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h $(TDIR)*.c $(TDIR)*.h $(MDIR)*.c $(MDIR)*.h
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h $(TDIR)*.c $(TDIR)*.h $(MDIR)*.c $(MDIR)*.h
leaks:
	leaks --atExit -- ./test
valgrind:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

.PHONY: all clean rebuild cpplint cppcheck leaks
