# -soal-shift-sisop-modul-2-D08-2021

## **Soal 1**

Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya. Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany. Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi.

A. Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg

B. untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :).

C. Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta

D. memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).

E. Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany).

F. Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip). Kemudian Steven meminta bantuanmu yang memang sudah jago sisop untuk membantunya mendapatkan hati Stevany. Bantu Woy!!

**Penyelesaian**

```
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
```
Pertama-tama dilakukan iclude header files yang dibutuhkan.

```
int main()
{
    pid_t pid, sid;

    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/tmp")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    	...
    	
   }
 
```
 
Pada fungsi main, terdapat _daemon function procces_ yang bertujuan agar program dapat berjalan pada background.

```
    char *FILM_ZIP = "film.zip";
    char *PHOTO_ZIP = "photo.zip";
    char *MUSIC_ZIP = "music.zip";
```

Variabel diatas digunakan untuk menyimpin folder zip dari file yang akan didownload.

```
while (1)
    {
        time_t t = time(NULL);
        struct tm now = *localtime(&t);

        if (now.tm_mday == 9 && now.tm_mon == 3 && now.tm_hour == 22 - 6 &&
            now.tm_min == 22 && now.tm_sec == 0)
        {
        	...
        }
        
        if (now.tm_mday == 9 && now.tm_mon == 3 && now.tm_hour == 22 &&
        now.tm_min == 22 && now.tm_sec == 0)
        {
        	...
        }
        
```

Awalnya waktu saat ini diambil kemudian disimpan ke variable __now__. kemudian program akan mengeck apakah waktu saat ini 6 jam sebelum ulang tahun atau sama dengan ulang tahun. Loop ini akan berjalan pada setiap detik.

```
            pid_t pid1, pid2;

            pid1 = fork();
            if (pid1 < 0)
            {
                exit(EXIT_FAILURE);
            }

            pid2 = fork();
            if (pid2 < 0)
            {
                exit(EXIT_FAILURE);
            }

            if (pid1 == 0 && pid2 > 0)
            {
                while (wait(NULL) > 0);
                
                char *argv[] = {"wget", "--no-check-certificate", "-o", "/dev/null",
                                "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", MUSIC_ZIP, NULL};
                execv("/bin/wget", argv);
            }
            else if (pid1 > 0 && pid2 == 0)
            {
                char *argv[] = {"wget", "--no-check-certificate", "-o", "/dev/null",
                                "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
                                "-O", PHOTO_ZIP, NULL};
                execv("/bin/wget", argv);
            }
            else if (pid1 == 0 && pid2 == 0)
            {
                char *argv[] = {"wget", "--no-check-certificate", "-o", "/dev/null",
                                "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download",
                                "-O", FILM_ZIP, NULL};
                execv("/bin/wget", argv);
            }
            
            while (wait(NULL) > 0);

```

Kemudian jika waktu saat ini 6 jam kurang dari waktu ulang tahun stephany, maka program akan di-fork sebanyak 2 kali sehingga program akan memiliki 2 child dan 1 grandchild. Akan dilakukan download file zip film, foto, musik yang kemudian disimpan sesuai dengan nama variable masing-masing yaitu __FILM_ZIP__, __PHOTO_ZIP__, dan __MUSIC_ZIP__ pada masing-masing proses. Namun procces pada child pertama akan menunggu hingga proses pada grandchild selesai sebelum melakukan download file.

```
            pid1 = fork();
            if (pid1 < 0)
            {
                exit(EXIT_FAILURE);
            }

            pid2 = fork();
            if (pid2 < 0)
            {
                exit(EXIT_FAILURE);
            }

            if (pid1 == 0 && pid2 > 0)
            {
                while (wait(NULL) > 0);

                char *argv[] = {"unzip", "-j", MUSIC_ZIP, "*.mp3", "-d", "./Musyik", NULL};
                execv("/bin/unzip", argv);
            }
            else if (pid1 > 0 && pid2 == 0)
            {
                char *argv[] = {"unzip", "-j", PHOTO_ZIP, "*.jpg", "-d", "./Pyoto", NULL};
                execv("/bin/unzip", argv);
            }
            else if (pid1 == 0 && pid2 == 0)
            {
                char *argv[] = {"unzip", "-j", FILM_ZIP, "*.mp4", "-d", "./Fylm", NULL};
                execv("/bin/unzip", argv);
            }

```
Setelah file selesai didownload, maka parent akan di-fork sebanyak dua kali. Pada masing-masing childnya, program akan melakukan unzip file-file ke dalam folder yang disimpan pada __./Fylm__, __./Pyoto__, dan __./Musyik__.


```
            pid_t pid1;

            pid1 = fork();
            if (pid1 < 0)
            {
                exit(EXIT_FAILURE);
            }

            if (pid1 == 0)
            {
                char *username = malloc(33 * sizeof(char));
                cuserid(username);

                char *TARGET_PATH = malloc(50 * sizeof(char));
                sprintf(TARGET_PATH, "/home/%s/Lopyu_Stevany.zip", username);

                char *argv[] = {"zip", "-r", TARGET_PATH, "./Fylm", "./Pyoto", "./Musyik", 		NULL};
                execv("/bin/zip", argv);
            }

            while (wait(NULL) > 0);
```
Selanjutnya jika waktu saat ini sama dengan waktu ulang tahun stephany, maka program akan di-fork. Pada proses childnya, pertama username dari user yang menjalankan program diambil kemudian digabungkan dengan nama zip akhirnya dan disimpan ke __TARGET_PATH__. kemudian folder film, foto, dan musik di-zip dengan nama yang sesuai dengan __TARGET_PATH__. Parent proses akan menunggu hingga proses zip selesai.

```
            pid1 = fork();
            if (pid1 < 0)
            {
                exit(EXIT_FAILURE);
            }

            if (pid1 == 0)
            {
                char *argv[] = {"rm", "-r", "./Fylm", "./Pyoto", "./Musyik",
                                FILM_ZIP, PHOTO_ZIP, MUSIC_ZIP, NULL};
                execv("/bin/rm", argv);
            }
        }
```

Setelah selesai dizip, maka program akan kembali di-fork. folder dan file zip yang dihasilkan pada proses sebelumnya kecuali zip akhir akan dihapus pada proes anaknya.

**Dokumentasi**
![image](https://user-images.githubusercontent.com/62102884/115996471-fa5d3780-a611-11eb-8d39-59af2fbdb500.png)
isi folder _/tmp_ pada tanggal 9 APR 2021 pukul 16:22:00. Terdapat fie yang didownload dan folder dari hasil ekstraknya.

![image](https://user-images.githubusercontent.com/62102884/115996646-b1f24980-a612-11eb-9dad-caae17710680.png)
isi folder pada 9 APR 2021 pukul 22:22:00. Dapat dilihat zip dan folder yang telah didownload sudah dihapus.

![image](https://user-images.githubusercontent.com/62102884/115996662-c7677380-a612-11eb-8212-18e4325fc89d.png)
pada folder _/home/[user]_ terdapat file zip  _Lopyu_Sten=vany.zip_ 





## **Soal 2**

### **Penyelesaian**

```c
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
```
```c
char direct[50]="/home/yudo/Documents/Modul2/petshop";
```
Pertama deklarasi char `direct` yang menyimpan path folder yang akan dibuat. 

- 2.a. Mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop” dan menghapus folder-folder yang tidak dibutuhkan
```c
            char *argv[]={"mkdir","-p",direct,NULL};
            proceed("/bin/mkdir",argv);
```
Program untuk membuat directory petshop ditaruh pada pointer argv1[] dan proses dengan memanggil fungsi `proceed`. 
```c
            char *argv2[]={"unzip","-q","pets.zip","-d",direct,NULL};
            execv("/usr/bin/unzip",argv2);
```
Program untuk meng-unzip dile yang ada di dalam zip ditaruh pada pointer `argv2[]`, agar file yang di unzip masuk ke folder petshop, digunakan command -d diikuti dengat path directory petshop.
```c
        DIR *dir=opendir(direct);
        struct dirent *dent;
        if(dir!=NULL)
```
Untuk mengakses folder petshop, digunakan `opendir(direct)`. Jika isi directory bukan NULL, program akan membaca file satu persatu.
```c
                else if(dent->d_type==DT_DIR){
                        char fileName[100]="/home/yudo/Documents/Modul2/petshop/";
                        strcat(fileName,dent->d_name);
                        
                        char *argv[]={"rm","-rf",fileName,NULL};
                        proceed("/bin/rm",argv);
                        exit(EXIT_SUCCESS); 
                }
```
Jika yang terbaca bertipe `directory` akan masuk ke program penghapusan folder. Untuk menghapus folder yang tidak diperlukan, pertama membuat variabel untuk menyimpan path folder petshop. Lalu tipe folder digabungkan dengan path folder petshop menggunakan `strcat()`. Path folder yang akan dihapus tersimpan dalam variabel `filename`. Lalu membuat program yang akan menghapus folder yang tidak berguna dalam pointer `argv[]`, menggunakan command `-rf`diikuti path folder, dan diproses dengan memanggil fungsi `proceed`. 
```c
                char *newname=cut(dent->d_name); 
```
Membuat pointer `newname` yang diisi dengan nama file dimana `.jpg` sudah dihapus. Untuk menghapus penamaan .jpg dilakukan dengan memanggil fungsi `cut()`.
```c
                while(photos=strtok_r(newname,"_",&newname))
```
Untuk memisahkan tanda `_` untuk hewan yang berbeda namun dalam jenis yang sama, digunakan `strtok_r(cutss,"_",&cutss)`.
```c
                        while(photo=strtok_r(ph,";",&ph))
```
Penamaan file sekarang adalah `[jenis];[nama];[umur]`. Untuk membacanya satu satu digunakan `strtok_r(ph,";",&ph)`. 

- 2.b. Membuat folder sesuai jenis peliharaan
```c
                                if(i==0){
                                    char files[80]="/home/yudo/Documents/Modul2/petshop/";
                                    strcat(files,photo);
                                    char *argv[]={"mkdir","-p",files,NULL};
                                    proceed("/bin/mkdir",argv);
                                    strcpy(pet,photo);
                                }
```
Jika yang terbaca adalah iterasi ke-nol atau jenis hewan maka membuat folder jenis hewan. Pertama membuat variabel files untuk menyimpan path folder pershop. Lalu path tersebut digabungkan dengan nama jenis menggunakan `strcat(files,photo)`. Berikutnya dibuat program untuk membuat folder baru dengan nama jenis hewan dalam pointer argv[] dan diproses dengan memanggil fungsi `proceed()`. 
```c
                                if(i==1){
                                    strcpy(pName,photo);
                                }
```
Jika yang terbaca adalah iterasi kesatu nama hewan maka akan mengcopy ke variabel `pName`.
```c
                                if(i==2){
                                    strcpy(pAge,photo);
                                }
```
Jika yang terbaca adalah iterasi kedua atau umur hewan maka akan mengcopy ke variabel `pAge`.
```c
                        while((wait(NULL))>0);
                        char newfile[100]="/home/yudo/Documents/Modul2/petshop/";
                        strcat(newfile,dent->d_name);
```
Membuat char `newfile` yang berisi path folder petshop. Selanjutnya digabungkan dengan nama jenis hewan menggunakan fungsi `strcat`. Sekarang  char `newfile` menyimpan path folder jenis hewan.

- 2.c&d. Memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
```c
                        char dest[100]="/home/yudo/Documents/Modul2/petshop/";
                        strcat(dest,pet);
                        strcat(dest,"/");
                        strcat(dest,pName);
                        strcat(dest,".jpg");
                        char *argv[]={"cp",newfile,dest,NULL};
                        proceed("/bin/cp",argv);
```
Membuat char `dest` yang berisi path folder petshop. Selanjutnya char `dest` digabungkan dengan `[jenis hewan]/[nama hewan].jpg`. Sekarang char `dest` menyimpan path foto hewan dalam folder jenis hewan. Selanjutnya membuat pointer `argv[]` untuk menyimpan program mengcopy foto hewan dari folder petshop ke dalam folder jenis hewan. Diproses dengan memanggil fungsi `proceed`.

- 2.e. Membuat file `keterangan.txt` di setiap folder.
```c
                        char file[50]="/home/yudo/Documents/Modul2/petshop/";
                        strcat(file,pet);
                        strcat(file,"/keterangan.txt");
```
Membuat char `file` yang berisi path folder petshop, lalu digabungkan dengan string `[jenis hewan]/keterangan.txt`, sehingga char `file` menyimpan path file `keterangan.txt` di dalam folder jenis hewan.
```c
                        char ket[50];
                        strcat(ket,"nama : ");
                        strcat(ket,pName);
                        strcat(ket,"\numur: ");
                        strcat(ket,pAge);
                        strcat(ket,"tahun\n\n");
```
Membuat char `ket` untuk menyimpan isi file `keterangan.txt`. Caranya dengan menggabungkan string yang sesuai format soal dengan nama hewan dan umur hewan, menggunakan fungsi `strcat`.
```c
                        FILE *fp;
                        fp=fopen(file,"a");
                        fputs(ket,fp);
                        fclose(fp);
```
Selanjutnya mengakses file `keterangan.txt` lalu memesukkan string keterangan hewan ke dalam file.
```c
        char hapus[100]="/home/yudo/Documents/Modul2/petshop/";
        strcat(hapus,dent->d_name);
        char *args[]={"rm",hapus,NULL};
        execv("/bin/rm",args);
```
Setelah foto dipindah ke dalam folder sesuai jenisnya, foto yang masih di luar folder jenis hewan dihapus. Caranya dengan membuat char yang menyimpan path folder petshop, lalu digabungkan dengan nama file foto. Lalu diproses untuk diremove filenya dengan `rm [path file]`.

**Dokumentasi**
Isi folder petshop:
![alt text](https://i.postimg.cc/N0XccGZV/Virtual-Box-Ubuntu-20-04-2-0-25-04-2021-21-03-57.png)

Isi folder cat:
![alt text](https://i.postimg.cc/wx0nns7M/Virtual-Box-Ubuntu-20-04-2-0-25-04-2021-21-04-42.png)

Isi file `keterangan.txt` dalam folder cat:
![alt text](https://i.postimg.cc/NGdfbFt7/Virtual-Box-Ubuntu-20-04-2-0-25-04-2021-21-12-45.png)

### Kendala
Kesulitan dalam memisahkan jenis, nama, dan umur dari penamaan file. Solusinya dengan memanfaatkan fungsi `strtok()`.
