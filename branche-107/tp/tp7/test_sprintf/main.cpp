#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Ce test montre l'utilisation de sprintf pour servir a la transmission par UART
 * d'un nombre
 */
int main(void){

	char buff[100];
	sprintf(buff, "mon nombre est %u\n", 123456);
	puts("allo\n");
	puts(buff);
	return 0;
}
