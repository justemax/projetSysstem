/* ============== include libraries ============== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> // mode of file mode_t
#include <ctype.h>    
#include <dirent.h>

int get_inode (int fd);
int create_file(char *file_name);
void ouvrir_fichier(char *file_name);
void write_file(char *fileName, char* chaine);
void our_cp(char *fileName, char *newFileName);
void our_remove(char *path);
void our_chmod(char *path, char *droit);
void recur_mkdir(char *path);
void our_mkdir(char *path);
void our_ls(char *path);

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


void recur_mkdir(char *path){
        char tmp[256];
        char *p = NULL;
        size_t len;

        snprintf(tmp, sizeof(tmp),"%s",path);
        len = strlen(tmp);
        if(tmp[len - 1] == '/')
                tmp[len - 1] = 0;
        for(p = tmp + 1; *p; p++)
                if(*p == '/') {
                        *p = 0;
                        mkdir(tmp, S_IRWXU);
                        *p = '/';
                }
        mkdir(tmp, S_IRWXU);
}
//mkdir -p
void our_mkdir(char *path)
{
	struct stat stats;
    // fichier non existant
    if (stat(path, &stats) == -1) {
		recur_mkdir(path);
	}
	else{
		printf (" chemin existe deja\n");

	}
}
 
//ls
void our_ls(char *path) {

    struct dirent *Dir;
    DIR *dir;

    // tester les droits sur le fichier
	dir = opendir (path);	
    if (dir == NULL) {
        printf ("impossible d'ouvrir '%s'\n", path);
    }
	else{
	    // Paffichage des fichier et dossier
		while ((Dir = readdir(dir)) != NULL) {
			printf ("%s \n", Dir->d_name);
       	}

       	closedir (dir);
    }
}

//TO DO : test avec et sans fichier et aussi la profondeur du dir
void our_remove(char *path)
{
    size_t path_len;
    DIR *dir;
	struct stat stat_path;
	struct dirent *entry;
	size_t len;
	char *buf;

	// tester si fichier existe
	if(stat(path, &stat_path) == -1)
	{
		printf(" chemin n'existe pas");
	}
	
 	// tester les droits d'ouverture sur ce fichier
 	if ((dir = opendir(path)) == NULL) {
        	printf("Can`t open directory %s \n", path);
	}

	path_len = strlen(path);

	// parcourir le retour de readdir ( fichier ou dossier dans le path)
	while ((entry = readdir(dir)) != NULL) {

        // skip entries "." and ".."
       	if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
           	continue;

		len = path_len + strlen(entry->d_name) + 2; 
		buf = malloc(len);

		if (buf) {
			struct stat statbuf;
			//tester si un fichier ou dossier
			snprintf(buf, len, "%s/%s", path, entry->d_name);
			if (!stat(buf, &statbuf)) {
				if (S_ISDIR(statbuf.st_mode))
					our_remove(buf);
				else
					unlink(buf);
			}
			free(buf);
		}

    }

	closedir(dir);
	//rmdir marche juste quand le dossier est vide
	rmdir(path);
}

/* Fonction nous permettant de changer les droits d'un fichier */
void our_chmod(char *path, char *droit){
	
	int i;
	
	i= strtol(droit,0,8);
	if(i > 0 && i < 778){
		chmod(path,i);
		printf("Droits changé\n");
	}else{
		printf("Droit invalide\n");
	}
	
	
}
