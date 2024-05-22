#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) 
{
        int n_commands = 0;
        char *cmd_list[100][100];
        int cmd_index = 0, args_index = 0;

        // Парсим аргументы командной строки
        for (int i = 1; i < argc; i++) 
        {
                if (strcmp(argv[i], ";;") == 0) 
                {
                        cmd_list[cmd_index][args_index] = NULL;
                        cmd_index++;
                        args_index = 0;
                } 
                else
                {
                        cmd_list[cmd_index][args_index++] = argv[i];
                }
        }

        cmd_list[cmd_index][args_index] = NULL; 
        n_commands = cmd_index + 1;

        int pid, status;
        int child_pids[100];

        // Запускаем команды
        for (int i = 0; i < n_commands; i++) 
        {
                pid = fork();
                if (pid == 0) 
                {
                        execvp(cmd_list[i][0], cmd_list[i]);
                        perror("execvp");
                        exit(1);
                } 
                else 
                {
                        child_pids[i] = pid;
                }
        }

        int finished_processes = 0;

        // Ожидаем завершения процессов и выводим имена успешно завершенных команд
        while (finished_processes < n_commands) 
        {
                pid_t done_pid = wait(&status);
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) 
                {
                        for (int i = 0; i < n_commands; i++) 
                        {
                                if (child_pids[i] == done_pid) 
                                {
                                        printf("%s\n", cmd_list[i][0]);
                                        break;
                                }
                        }
                }
                finished_processes++;
        }

        return 0;
}



/*
Напишите программу, которая через аргументы командной строки получает имена и аргументы для запуска 
внешних программ (произвольное их количество), разделённые параметром, состоящим из двух символов ";" 
чтобы при запуске командный интерпретатор не считал параметр ";;" имеющим особый смысл, заключайте его
в апострофы, например:

        ./prog ls -l / ";;" sleep 10 ";;" cat file1.txt file2.txt

Ваша программа должна запустить на одновременное (параллельное) исполнение все указанные программы с 
заданными аргументами и напечатать имена тех из них, которые завершились успешно, то есть вызовом _exit 
с параметром 0. Печатать имена следует по мере завершения запущенных программ. Закончить работу следует
сразу после завершения последней из запущенных программ, но не раньше.

*/


/*
./prog ls -l / ";;" sleep 10 ";;" cat file1.txt file2.txt       
Команды для выполнения разделены ";;", параллельно выполняем ls -l, sleep 10, cat file1.txt file2.txt
*/