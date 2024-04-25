#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s filename program_name [args...]\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char **program_args = &argv[2];

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Redirect stdout to the file
        dup2(fd, STDOUT_FILENO);
        
        // Close the file descriptor
        close(fd);
        
        // Execute the external program
        execvp(program_args[0], program_args);
        
        // If execvp fails
        perror("execvp");
        exit(1);
    } else if (pid < 0) {
        perror("fork");
        return 1;
    } else {
        wait(NULL);
    }

    return 0;
}



/*
Напишите программу, которая принимает не менее двух аргументов командной строки и рассматривает 
первый аргумент как имя файла, остальные как имя и аргументы для запуска внешней программы; 
например, если ваша программа называется prog пользователь запустил её командой

./prog file1.txt ls -l -R

то здесь имеется в виду файл file1.txt, внешняя программа ls и аргументы -l -R. Запустите указанную 
внешнюю программу с указанными аргументами так, чтобы
её стандартный вывод был перенаправлен в указанный файл (если такого файла нет, он должен быть создан, 
если он уже есть перезаписан; если открыть файл не удалось, должна быть выдана диагностика, 
соответствующая возникшей ситуации)

*/