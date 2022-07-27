s21_cat:
	gcc -Wall -Werror -Wextra -std=c11 s21_cat.c -o s21_cat
checks:
	cppcheck s21_cat.c
	python3 ../../materials/linters/cpplint.py s21_cat.*
	leaks -atExit -- ./s21_cat -v text.txt
test:
	gcc -Wall -Werror -Wextra -std=c11 s21_cat.c -o s21_cat
	bash ./t_cat_2.sh
	rm s21_cat