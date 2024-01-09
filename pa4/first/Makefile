all: first
first: first.c 	
	gcc	-g	-Wall	-Werror	-fsanitize=address	-lm	-std=c11	first.c	-o	first
clean:
	rm	-rf	first