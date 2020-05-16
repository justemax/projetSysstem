#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){

		char entry[50];
		char *arg[20];
		int i=0;
		
		while(1){
				
					
				printf("Promp command or exit to quit: ");
				fgets(entry, 50, stdin);
				
				char *p = strtok(entry, " ");
				
				while(p != NULL){
					arg[i] = p;
					p = strtok(NULL," ");
					i++;
				}
				
				
				
				
				
				if(strcmp("exit",arg[0]) < 1){
					printf("sortie \n");
					exit(0);
				}
				else if(strcmp("echo",arg[0]) < 1){
					printf("echo: %s \n", arg[1]);
				}
				else{
					printf("entre else\n");
					
				}
				
				i = 0;
		}
}
