#include <stdio.h>
#include <stdlib.h>

//Данный пример демонстрирует использование switch-case, if и передачу аргументов

//argc - integer - содержит в себе кол-во переданных аргументов
//argv - char - переданные аргументы

main(int argc, char *argv[]){
	if (argc != 2){
		printf("Usage: <%s> your_args (a or b or something else)\n", argv[0]);
		exit(1);
	} else {
		switch((*argv)[1]){
			case 'a':
				printf("You entered 1\n");
				break;
			case 'b':
				printf("You entered 2\n");
				break;
			default:
				printf("You entered %s\n",argv[1]);
				break;
		}
	}
}
