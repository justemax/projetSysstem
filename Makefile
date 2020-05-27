our_term : main.o manage_directory.o manage_file.o
	gcc -o our_term main.o manage_directory.o manage_file.o

main.o : main.c 
	gcc -o main.o -c main.c

manage_directory.o : manage_directory.c
	gcc -o manage_directory.o -c manage_directory.c
	
manage_file.o : manage_file.c
	gcc -o manage_file.o -c manage_file.c
