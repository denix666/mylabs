#include <stdio.h>
#include <stdlib.h>

main(int argc, char *argv[]){

    char cmd[100];

    if (argc != 2){
	printf("Usage: <%s> your_args\n", argv[0]);
	    exit(1);
    } else {
        sprintf(cmd, "cat db | grep '%s' | awk '{print $2}'",argv[1]);
        system(cmd);
        return 0;
    }
}
