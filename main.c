#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define CURRENT_DIR "."

void search(const char *fileName, const char *basePath) 
{
    DIR *dir = opendir(basePath);
    
    if (!dir)
    {
        printf("Ошибка при открытии дриектории\n");
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR) 
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

            char path[1024];

            snprintf(path, sizeof(path), "%s/%s", basePath, entry->d_name);
            search(fileName, path);
        } 
        else if (strcmp(entry->d_name, fileName) == 0)
            printf("Найден файл: %s/%s\n", basePath, entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char** argv) 
{
    if (argc != 2)
    {
        printf("Передано неверное количество аргументов\n");
        return EXIT_FAILURE;
    }

    const char *fileName = argv[1];

    search(fileName, CURRENT_DIR);

    return EXIT_SUCCESS;
}
