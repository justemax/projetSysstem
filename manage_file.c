/* ============== include libraries ============== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> // mode of file mode_t
#include <ctype.h>    

#include "manage_directory.h"

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

void our_rmFile(char *fileName){
	if(remove(fileName) != 0){
		printf("Suppression impossible");
	}
}

void our_mv(char *fileName, char *path){
	our_cp(fileName, path);
	our_rmFile(fileName);
}



