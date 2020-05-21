/* ============== include libraries ============== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> // mode of file mode_t
#include <ctype.h>    

int get_inode (int fd);
int create_file(char *file_name);
void ouvrir_fichier(char *file_name);
void write_file(char *fileName, char* chaine);
void our_cp(char *fileName, char *newFileName);


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
					create_file(arg[1]);
				}
				else{
					printf("entre else\n");
					
				}
				
				i = 0;
		}
}





//fonction return inode du fichier
int get_inode (int fd)
{
    struct stat buf;
    int ret;

    ret = fstat(fd, &buf);
    if ( ret <0 ) {
         perror ("fstat");
         return -1;
    }

    return buf.st_ino;
}

/* ================ Creation du fichier ================ */
//creer fichier et return son inode
int create_file(char *file_name){
  int inode;
  int file;
  //creation du fichier
  file = open(file_name, O_RDWR | O_CREAT, (mode_t)0600);

 
  if(file == -1){
    perror("Error: fichier non creer / non ouvert\n");
    return -1;
  }

  write(file, "\0", 1);//signaler la fin du fichier
  inode = get_inode (file);
  printf("inode of file %s is %d\n",file_name,inode);
  return inode;
}
/* ============== end Creation de fichier ============== */

//myopen
void ouvrir_fichier(char *file_name){
    int c;
    FILE *file;
    file = fopen(file_name, "r");
    if (file) {
      printf("=============DEBUT==================\n");
      while ((c = getc(file)) != EOF){
        putchar(c);
      }
      fclose(file);
      printf("\n=================FIN======================\n");
    }else{
      printf("FILE NOT FOUND\n");
      exit(-1);
    }
}
//Ecriture dans un fichier
void write_file(char *fileName, char* chaine){
	
	FILE* file = fopen(fileName,"w");
	
	if(file){
		fputs(chaine,file);
		fclose(file);
	}else{
		printf("Fichier introuvable");
	}
}

//Notre commande ls
void our_ls(char *fileName){
	
}

// Notre commande cp
void our_cp(char *fileName, char *newFileName){
	
	int c;
    FILE *file, *file2;
    
    create_file(newFileName);
    
    file = fopen(fileName, "r");
    file2 = fopen(newFileName, "w");
    
    if (file && file2) {
      while ((c = getc(file)) != EOF){
        fputc(c,file2);
      }
      fclose(file2);
      fclose(file);
    }else{
      printf("FILE NOT FOUND\n");
      exit(-1);
    }
}
