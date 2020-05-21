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
				
				
				printf(arg[2]);
				
				
				if(strcmp("exit",arg[0]) == 0){
					printf("sortie \n");
					exit(0);
				}
				else if(strcmp("echo",arg[0]) == 0){
					//On test si on a une redirection vers un fichier
					if(strcmp(arg[2],">") == 0 && strcmp(arg[3],"") > 0){
						printf("dans fichier ercire\n");
					}else{
						printf("echo: %s \n", arg[1]);
					}
					
				}
				else{
					printf("entre else\n");
					
				}
				
				i = 0;
		}
}
