all: Helloworld
Helloworld: geometry.c
	gcc -Wall -Werror -o hello geometry.c 
