#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

void sigchld_handler(int signo) {
        int status;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        if (WIFEXITED(status)) 
        {
                printf("exited with code %d\n", WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)) 
        {
                printf("killed by signal %d\n", WTERMSIG(status));
        }
}

int main(int argc, char *argv[]) {
        if (argc < 2) {
                printf("Usage: %s program_name [args...]\n", argv[0]);
                return 1;
        }

        signal(SIGCHLD, sigchld_handler);

        pid_t pid = fork();

        if (pid == 0) 
        {
                execvp(argv[1], &argv[1]);
                perror("execvp");
                exit(1);
        } 
        else if (pid < 0) 
        {
                perror("fork");
                return 1;
        } 
        else 
        {
                wait(NULL);
        }

    return 0;
}


/*
Напишите программу, которая принимает произвольное количество (не менее одного) 
аргументов командной строки и рассматривает их как имя и аргументы для запуска внешней программы: 
например, если ваша программа называется prog и пользователь за- пустил её командой

        /prog ls -l -R

-то ваша программа должна запустить программу ls с аргументами -l -R. Сделайте так, чтобы в 
зависимости от того, как запущенная программа завершится, ваша программа печатала либо слово 
exited и код завершения, либо слово killed и номер сигнала, которым за пущенная программа была убита.

*/