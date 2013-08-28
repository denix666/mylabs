/* Sample UDP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv) {
	int sockfd,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	char mesg[1000];
	int server_port = 32000;
	char buf[256];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(server_port);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	for (;;) {
		len = sizeof(cliaddr);
		n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
		sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
		mesg[n] = 0;

		// Запись в файл (добавление)
		FILE *myFile = fopen("text.txt","a");
		fputs(mesg, myFile);
		fclose(myFile);

		// Вывод на экран содержимого пакета
		printf("-------------------------------------------------------\n");
		printf("Received the following:\n");
		printf("%s",mesg);
		printf("-------------------------------------------------------\n");
	}
}
