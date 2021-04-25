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
isi folder __/tmp__ pada tanggal 9 APR 2021 pukul 16:22:00. Terdapat fie yang didownload dan folder dari hasil ekstraknya.

![image](https://user-images.githubusercontent.com/62102884/115996646-b1f24980-a612-11eb-9dad-caae17710680.png)
isi folder pada 9 APR 2021 pukul 22:22:00. Dapat dilihat zip dan folder yang telah didownload sudah dihapus.

![image](https://user-images.githubusercontent.com/62102884/115996662-c7677380-a612-11eb-8212-18e4325fc89d.png)
pada folder _/home/[user]_ terdapat file zip  __Lopyu_Stevany.zip__

![image](https://user-images.githubusercontent.com/62102884/115996922-d26ed380-a613-11eb-90e4-df35e6baf112.png)
isi daripada file zip __Lopyu_Stephany.zip__



### **Penyelesaian Soal 2**
- 2.a. Mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop” dan menghapus folder-folder yang tidak dibutuhkan
```c
    pid_t child_id;
    int status;
    char direct[]="/home/yudo/Documents/Modul2/petshop";
    char FileName[]="petshop";
  
    struct dirent *dp;
    DIR *dir = opendir(direct);

    child_id = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id == 0) {
        // this is child

        char *argv1[] = {"unzip", "pets.zip", "-d", direct, "*.jpg", NULL};
        execv("/bin/unzip", argv1);

    }
```
Pertama deklarasi char `direct` yang menyimpan alamat folder yang akan dibuat. Lalu program untuk mengextract zip dan menyimpannya dalam directory petshop ditaruh pada pointer `argv1[]` dengan nama program `unzip` dan dieksekusi dengan execv. . Digunakan `-d` untuk menunjukkan path yang akan dituju. Agar folder yang tidak dibutuhkan tidak ikut terextract maka ditambahkan `*.jpg`, hasilnya yang dieksekusi hanya file .jpg.
