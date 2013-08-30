#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>

#define port_address 0x0378

int main(int argc, char **argv)
{
	void show_usage()
	{
		printf("Usage: <lptctrl VALUE>\n");
		printf("\n");
		printf("\tVALUE 0..255\n");
		printf("\n");
	}
	
	int value;
	
	printf("*****************************************\n");
	printf("**            LPT control              **\n");
	printf("*****************************************\n");
	printf("\n");
	
	if(argc<2)
	{
		show_usage();
		fprintf(stderr,"Error, Wrong number of arguments!\n");
		exit(1);
	}
	if(sscanf(argv[1],"%i",&value)!=1)
	{
		show_usage();
		fprintf(stderr,"Error, Parameter is not a number!\n");
		exit(1);
	}
	if ((value<0) || (value>255))
	{
		show_usage();
		fprintf(stderr,"Error, Invalid numeric value!\n");
		exit(1);
	}
	if (ioperm(port_address,1,1))
	{
		fprintf(stderr,"Error, Couldn't get the port at %x!\n",port_address);
		exit(1);
	}
	outb((unsigned char)value,port_address);
	printf("Value %i",value);
	printf(" sended to port\n");
	return 0;
}
