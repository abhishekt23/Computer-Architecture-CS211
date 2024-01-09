all: eighth
eighth: eighth.c 	
	gcc	-g	-Wall	-Werror	-fsanitize=address	-lm	-std=c11	eighth.c	-o	eighth
clean:
	rm	-rf	eighth