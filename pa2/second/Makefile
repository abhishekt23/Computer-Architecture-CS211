all: second
second: second.c 	
	gcc	-g	-Wall	-Werror	-fsanitize=address	-std=c11	second.c	-o	second
clean:
	rm	-rf	second