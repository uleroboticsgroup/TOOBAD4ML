#include <stdio.h>
#include <string.h>

int main() {


	char buffer[50];

	gets(buffer);

	if ( gets(buffer) != NULL) {
		gets(buffer);
	}

/*	FILE * pFile;

   	pFile = fopen ("myfile.txt" , "r");
   	if (pFile == NULL) perror ("Error opening file");
   	else {
     	if ( fgets (buffer , 100 , pFile) != NULL )
       	puts (buffer);
   	}

   	char letra;

   	char l[1];

   	letra=fgetc(pFile);

   	l[1] = letra;

   	fclose (pFile);

	printf("%c", letra);*/

}


/// ###BEGIN_VULNERABLE_LINES###

/// 9,01;9,01
