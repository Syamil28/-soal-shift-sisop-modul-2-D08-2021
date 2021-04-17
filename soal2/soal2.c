#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

char direct[]="/home/yudo/Documents/Modul2/petshop";

int main() {
    pid_t child_id1, child_id2, child_id3;
    int status;
  
    struct dirent *dp;
    DIR *dir = opendir(direct);

    child_id1 = fork();

    if (child_id1 < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id1 == 0) {
        // this is child

        char *argv1[] = {"unzip", "pets.zip", "-d", direct, "*.jpg", NULL};
        execv("/bin/unzip", argv1);

    } 

    while ((wait(&status)) > 0);
    
    child_id2 = fork();
    if (child_id2 < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }
    if (child_id2 == 0) {
        // this is child

        char path[100];
        
        while ((dp = readdir(dir)) != NULL)
    	{
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
            {
            	
            	child_id3 = fork();
            	if (child_id3 < 0) {
        	    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    		}
    		if (child_id3 == 0) {
    		    char *argv2[]={"mkdir", "-p", path, NULL};
    		    execv("/bin/mkdir", argv2);
    		}
            }
    	}
    } 
    closedir(dir);
}
