all: check_func

check_func:
	cp ./../s21_decimal.a .
	gcc -Wall -Werror -Wextra s21_decimal.a check_func_0.c -o check
	./check

clean:
	-rm -f check *.txt *.a