# -soal-shift-sisop-modul-2-D08-2021

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
