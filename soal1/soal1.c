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

    char *FILM_ZIP = "film.zip";
    char *PHOTO_ZIP = "photo.zip";
    char *MUSIC_ZIP = "music.zip";

    while (1)
    {
        time_t t = time(NULL);
        struct tm now = *localtime(&t);

        if (now.tm_mday == 9 && now.tm_mon == 3 && now.tm_hour == 22 - 6 &&
            now.tm_min == 22 && now.tm_sec == 0)
        {
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
        }

        if (now.tm_mday == 9 && now.tm_mon == 3 && now.tm_hour == 22 &&
            now.tm_min == 22 && now.tm_sec == 0)
        {
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

        sleep(1);
    }
}
