int get_inode (int fd);
int create_file(char *file_name);
void ouvrir_fichier(char *file_name);
void write_file(char *fileName, char* chaine);
void our_cp(char *fileName, char *newFileName);
void our_remove(char *path);
void our_chmod(char *path, char *droit);
void our_mv(char *fileName, char *path);
void our_rmFile(char *fileName);
