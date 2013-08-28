#include <stdio.h>
#include <sys/stat.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	pid_t pid, sid;

	/* step 1 of daemon writing */
	pid= fork();
	if(pid < 0) {
		exit(0);
	}

	if(pid > 0) {
		printf("The PID of daemon is %d\n", pid);
		exit(0);
	}
 
	/* changing file mode creation mask, step2 of daemon creation*/
	umask(0);

	/* step3 create new session and child becomes part of this new session*/
	sid=setsid();
	if(sid<0) {
		exit(1);
	}
 
	/* step 4 change the current directory to root (/) */
	if(chdir("/")<0) {
		exit(1);
	}

	/* step 5 close all standard input, output and error files */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	/* log to syslog information about daemon */
	syslog(LOG_INFO, "Daemon started. PID: %d", getpid());

	/* last step create infinite loop and add job required to done by daemon */
	while(1) {

	}
}

