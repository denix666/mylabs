#include <stdio.h>

int main(void) {
	char buf[256];
	FILE *myFile = fopen("text.txt","a");
	const char output_lines[] = "sdfgsf\n";
	
	fputs(output_lines, myFile);
	fclose(myFile);
}
