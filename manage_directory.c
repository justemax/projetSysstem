/* ============== include libraries ============== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>   // mode of file mode_t
#include <ctype.h>
#include <dirent.h>

//fonction recursiv pour faire un mkdir -p
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
   	char *full_path;
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


//TO TEST
// ce main sert juste pour tester les fonctions, test unitaire
int main()
{
        //juste pour tester
    char *path = "jamal/kenza/adam";
		our_mkdir(path);
		our_ls("jamal");
		our_remove("jamal");
    return 0;

}

