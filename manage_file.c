/* ============== include libraries ============== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> // mode of file mode_t
#include <ctype.h>    

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
      while ((c = getc(file)) != EOF)
        putchar(c);
      fclose(file);
      printf("\n=================FIN======================\n");
    }else{
      printf("FILE NOT FOUND\n");
      exit(-1);
    }
}

//TO TEST
// ce main sert juste pour tester les fonctions, test unitaire
int main()
{
//juste pour tester
char *file_name = "./test.txt";
printf ("START TEST\n");
create_file(file_name);
return 0;

}
