#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>

char direct[50]="/home/yudo/Documents/Modul2/petshop";

void proceed(char perintah[],char *arg[]){
        int status;
        pid_t child_id;
        child_id=fork();
        
        if(child_id==0){
            execv(perintah,arg);
        }
        else{
           ((wait(&status))>0);
        }
}

char* cut(char *arr){
        int n,i;
        char* cuts; 
        for(i=0;arr[i]!='\0';i++);
           n=i-4+1;

        cuts=(char*)malloc(n*sizeof(char));

        for(i=0;i<n-1;i++)
            cuts[i]=arr[i];
        cuts[i]='\0';
        return cuts;
}

int main() {
        pid_t pid1;
        int status;
        pid1 = fork();

        if(pid1<0){
            exit(EXIT_FAILURE);
        }

        if(pid1==0){
            char *argv[]={"mkdir","-p",direct,NULL};
            proceed("/bin/mkdir",argv);

            char *argv2[]={"unzip","-q","pets.zip","-d",direct,NULL};
            execv("/usr/bin/unzip",argv2);
        }

        while((wait(NULL))>0);

        DIR *dir=opendir(direct);
        struct dirent *dent;
        if(dir!=NULL){
        while((dent=readdir(dir))!=NULL){
                if(strcmp(dent->d_name,".")==0 || strcmp(dent->d_name,"..")==0) continue; 
                if(fork()==0)  continue;
                else if(dent->d_type==DT_DIR){
                        char fileName[100]="/home/yudo/Documents/Modul2/petshop/";
                        strcat(fileName,dent->d_name);
                        
                        char *argv[]={"rm","-rf",fileName,NULL};
                        proceed("/bin/rm",argv);
                        exit(EXIT_SUCCESS); 
                }
                char *newname=cut(dent->d_name); 
                char *photos;

                while(photos=strtok_r(newname,"_",&newname)){
                        int i=0;
                        char pet[30], pName[30], pAge[30];
                        char *ph=photos;
                        char *photo;
                        
                        while(photo=strtok_r(ph,";",&ph)){
                                if(i==0){
                                    char files[80]="/home/yudo/Documents/Modul2/petshop/";
                                    strcat(files,photo);
                                    char *argv[]={"mkdir","-p",files,NULL};
                                    proceed("/bin/mkdir",argv);
                                    strcpy(pet,photo);
                                }
                                if(i==1){
                                    strcpy(pName,photo);
                                }
                                if(i==2){
                                    strcpy(pAge,photo);
                                }
                                i++;
                        }
                        
                        while((wait(NULL))>0);
                        char newfile[100]="/home/yudo/Documents/Modul2/petshop/";
                        strcat(newfile,dent->d_name);
                  
                        char dest[100]="/home/yudo/Documents/Modul2/petshop/";
                        strcat(dest,pet);
                        strcat(dest,"/");
                        strcat(dest,pName);
                        strcat(dest,".jpg");
                        char *argv[]={"cp",newfile,dest,NULL};
                        proceed("/bin/cp",argv);

                        char file[50]="/home/yudo/Documents/Modul2/petshop/";
                        strcat(file,pet);
                        strcat(file,"/keterangan.txt");

                        char ket[50];
                        strcat(ket,"nama : ");
                        strcat(ket,pName);
                        strcat(ket,"\numur: ");
                        strcat(ket,pAge);
                        strcat(ket,"tahun\n\n");

                        FILE *fp;
                        fp=fopen(file,"a");
                        fputs(ket,fp);
                        fclose(fp);
         }
        char hapus[100]="/home/yudo/Documents/Modul2/petshop/";
        strcat(hapus,dent->d_name);
        char *args[]={"rm",hapus,NULL};
        execv("/bin/rm",args);

      }
      closedir(dir);
    }
  return 0;
}
