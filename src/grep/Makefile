CFLAGS=-Wall -Werror -Wextra -std=c11
s21_grep:
	gcc -Wall -Werror -Wextra -std=c11 s21_grep.c -o s21_grep
checks:
	cppcheck s21_grep.c
	python3 ../../materials/linters/cpplint.py s21_grep.*
	leaks -atExit -- ./s21_grep -v text.txt
test1:
	gcc ./s21_grep.c -o ./s21_grep $(CFLAGS)
	bash ./test.sh
test2:
	gcc ./s21_grep.c -o ./s21_grep $(CFLAGS)
	bash ./my_test.sh
clean:
	rm ./s21_grep.out