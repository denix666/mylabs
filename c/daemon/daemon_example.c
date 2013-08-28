/*
 * program to demonstrate writing daemon programs in C and linux
 * This Daemon print(adds) time or date every minute, depending on
 * user choice t or d to syslog file
 */
#include <stdio.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
/*
 * parameters to daemon using argc and argv
 */
int main(int argc, char *argv[])
{
 pid_t pid, sid;
 char ch;
 time_t t;
 char  buf[80];
 struct tm *ts;

/*
 * this daemon expects one argument
 * as daemon name is count number 1 and one arg to daemon
 * so checking for count <2
 */

 if(argc<2) {
    printf("usage: <program name> d | t \n");
    return 0;
 }

 ch = argv[1][0];
 printf("The choice is %c\n", ch);

 if (!((ch =='d') || (ch == 't'))) {
     printf("Not right choice ..\n");
     return 0;
 }

 /* step 1 of daemon writing */
  pid= fork();
  if(pid < 0) {
     exit(0);
  }

 if(pid > 0){
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

/*
 *  after above step we can do any daemon specific
 * initialization if needed
 */

/* last step create infinite loop and add job required to done by daemon */
while(1){

    t=time(0);
    ts= localtime(&t);

   /* This daemon just prints below message every 60 secs
    * you can run this with choice 'd' or 't' to get below messages
    * else nothing will be logged to syslog messages
    * to see message logged to can cat /var/log/syslog
    * if you configured else nothing will be presented
    */
   if(ch=='d') {
     strftime(buf, sizeof(buf),  "%a %Y-%m-%d %H:%M:%S %Z", ts);
     syslog(LOG_INFO, "Daemon %d: prints %s every minute %s..", getpid(), "date", buf);
     sleep(60);
   } else if(ch == 't'){
     strftime(buf, sizeof(buf),  "%H:%M:%S %Z", ts);
     syslog(LOG_INFO, "Daemon %d: prints %s every minute %s..", getpid(), "time", buf );
     sleep(60);

  }

}

}

/* end of the program */

