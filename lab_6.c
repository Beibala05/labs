#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) 
{
        int pipefd[2];  // Массив для файловых дескрипторов канала
        pid_t cpid1, cpid2;
        int i, sepIndex = -1;

        // Находим индекс аргумента, который содержит ";;" (Парсер)
        for (i = 1; i < argc; i++)
        {
                if (strcmp(argv[i], ";;") == 0) 
                {
                        sepIndex = i;
                        break;
                }
        }

        if (sepIndex == -1) 
        {
                fprintf(stderr, "Ошибка: разделитель ';;' не найден.\n");
                return 1;
        }

        // Создаем канал
        if (pipe(pipefd) == -1) 
        {
                printf("pipe error");
                exit(EXIT_FAILURE);
        }

        // Создаем первый процесс
        cpid1 = fork();
        if (cpid1 == -1) 
        {
                printf("fork error");
                exit(EXIT_FAILURE);
        }

        if (cpid1 == 0) 
        {
                close(pipefd[0]);  // Закрываем неиспользуемый конец канала
                dup2(pipefd[1], STDOUT_FILENO);  // Перенаправляем stdout на входной конец канала
                close(pipefd[1]);  

                // Запускаем первую программу
                char** args1 = &argv[1];
                argv[sepIndex] = NULL;  // Отделяем аргументы первой программы
                execvp(args1[0], args1);
                printf("execvp error");
                exit(EXIT_FAILURE);
        }

        // Создаем второй процесс
        cpid2 = fork();
        if (cpid2 == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
        }

        if (cpid2 == 0) 
        {
                close(pipefd[1]);  // Закрываем неиспользуемый конец канала
                dup2(pipefd[0], STDIN_FILENO);  // Перенаправляем stdin на выходной конец канала
                close(pipefd[0]);

                // Запускаем вторую программу
                char **args2 = &argv[sepIndex + 1];
                execvp(args2[0], args2);
                perror("execvp");
                exit(EXIT_FAILURE);
        }

        // В родительском процессе закрываем файловые дескрипторы канала
        close(pipefd[0]);
        close(pipefd[1]);

        // Ждем завершения дочерних процессов
        waitpid(cpid1, NULL, 0);
        waitpid(cpid2, NULL, 0);

        return 0;
}


// ls -l - команда, вывод которой будет передан на ввод команды wc -l.
// wc -l - команда подсчета строк, которая примет ввод из ls -l.