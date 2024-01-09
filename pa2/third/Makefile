all: third
third: third.c 	
	gcc	-g	-Wall	-Werror	-fsanitize=address	-std=c11	third.c	-o	third
clean:
	rm	-rf	third