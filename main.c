/* ============== include libraries ============== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "manage_directory.h"
#include "manage_file.h"



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
				
				
				strtok(arg[0],"\n");
				
				if(strcmp("exit",arg[0]) == 0){
					printf("sortie \n");
					exit(0);
				}
				else if(strcmp("echo",arg[0]) == 0){
					//On test si on a une redirection vers un fichier
					if(strcmp(arg[2],">") == 0 && strcmp(arg[3],"") > 0){
						//printf(arg[3]);
						write_file(arg[3],arg[1]);
					}else{
						printf("echo: %s \n", arg[1]);
					}
					
				}
				else if(strcmp("cat",arg[0]) == 0){
					ouvrir_fichier(arg[1]);
				}
				else if(strcmp("touch",arg[0]) == 0){
					strtok(arg[1],"\n");
					create_file(arg[1]);
				}
				else if(strcmp("ls",arg[0]) == 0){
					strtok(arg[1],"\n");
					if((strcmp("",arg[1]) == 0) || (strcmp("\n",arg[1]) == 0)){
						printf("Pas de chemin, pour fichier courrant mettre: .");
					}else{
						our_ls(arg[1]);
					}
				}
				else if(strcmp("mkdir",arg[0]) == 0){
					strtok(arg[1],"\n");
					if(strlen(arg[1]) != 0){
						our_mkdir(arg[1]);
					}else{
						printf("entrez un nom de fichier");
					}
				}
				else if(strcmp("rm",arg[0]) == 0){
					strtok(arg[1],"\n");
					if(strlen(arg[1]) != 0){
						our_remove(arg[1]);
					}else{
						printf("entrez un nom de fichier a supp");
					}
				}
				else if(strcmp("chmod",arg[0]) == 0){
					strtok(arg[1],"\n");
					if(strlen(arg[1]) > 0 && strlen(arg[2]) > 0){
						our_chmod(arg[2],arg[1]);
					}else{
						printf("entrez un nom de fichier pour obtenir ses droits");
					}
				}
				else{
					printf("Commande inconnue ou arguments manquants\n");
					
				}
				
				i = 0;
		}
}


