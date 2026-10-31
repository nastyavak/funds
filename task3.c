#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int compare_str(char *s1, char *s2, int n){
    for (int i = 0; i < n; i++){
        if (s1[i] != s2[i]) return 1;
    }
    return 0;
}

char *unescape(char *s){
    int len = strlen(s);
    char *res = (char *)malloc(len + 1);
    int pos = 0;
    for (int i = 0; i < len; i++){
        if (s[i] == '\\'){
            if (s[i + 1] == 'n'){
                res[pos] = '\n';
                pos++;
                i++;
            }
            else if (s[i + 1] == 't'){
                res[pos] = '\t';
                pos++;
                i++;
            }
            else if (s[i + 1] == '\\'){
                res[pos] = '\\';
                pos++;
                i++;
            }
            else {
                res[pos] = s[i];
                pos++;
            }
        }
        else {
            res[pos] = s[i];
            pos++;
        }
    }
    res[pos] = '\0';
    return res;
}

void func(char *substr, int file_count, ...){
    va_list args;
    va_start(args, file_count);
    int patt_len = strlen(substr);
    for (int f = 0; f < file_count; f++){
        char *path = va_arg(args, char *);
        FILE *fin = fopen(path, "r");
        if (fin == NULL){
            printf("файл не открылся\n");
            continue;
        }
        printf("файл %s\n", path);
        int cap = 1024;
        int pos = 0;
        int line_num = 1;
        int found_any = 0;
        char *line = (char *)malloc(cap);
        int c;
        while (1){
            c = fgetc(fin);
            if (c == EOF){
                break;
            }
            if (c == '\n'){
                line[pos] = '\0';
                for (int j = 0; j <= pos - patt_len; j++){
                    if (compare_str(line + j, substr, patt_len) == 0){
                        printf("  строка %d, символ %d\n", line_num, j + 1);
                        found_any = 1;
                    }
                }
                pos = 0;
                line_num++;
                continue;
            }
            if (pos + 1 >= cap){
                cap *= 2;
                char *new_line = (char *)realloc(line, cap);
                if (new_line == NULL){
                    printf("ошибка выделения памяти\n");
                    fclose(fin);
                    free(line);
                    va_end(args);
                    return;
                }
                line = new_line;
            }
            line[pos] = c;
            pos++;
        }
        if (pos > 0){
            line[pos] = '\0';
            for (int j = 0; j <= pos - patt_len; j++){
                if (compare_str(line + j, substr, patt_len) == 0){
                    printf("  строка %d, символ %d\n", line_num, j + 1);
                    found_any = 1;
                }
            }
        }
        if (!found_any){
            printf("  вхождений не найдено\n");
        }
        fclose(fin);
        free(line);
    }
    va_end(args);
}

int main(int argc, char **argv){
    if (argc < 4){
        printf("некорректный ввод\n");
        return 1;
    }
    char *substr = unescape(argv[1]);
    if (strlen(substr) == 0){
        printf("подстрока не может быть пустой\n");
        free(substr);
        return 1;
    }
    int file_count = 0;
    if (sscanf(argv[2], "%d", &file_count) != 1 || file_count < 1){
        printf("некорректное количество файлов\n");
        free(substr);
        return 1;
    }
    if (argc - 3 < file_count){
        printf("недостаточно путей к файлам\n");
        free(substr);
        return 1;
    }
    if (file_count > 5){
        printf("максимум 5 файлов\n");
        free(substr);
        return 1;
    }
    char *paths[5];
    for (int i = 0; i < file_count; i++){
        paths[i] = argv[3 + i];
    }
    for (int i = 0; i < file_count; i++){
        char *real_i = realpath(paths[i], NULL);
        for (int j = i + 1; j < file_count; j++){
            char *real_j = realpath(paths[j], NULL);
            if (real_i && real_j && strcmp(real_i, real_j) == 0){
                printf("файлы совпадают\n");
                free(real_i);
                free(real_j);
                free(substr);
                return 1;
            }
            free(real_j);
        }
        free(real_i);
    }
    switch (file_count){
        case 1:
            func(substr, file_count, paths[0]);
            break;
        case 2:
            func(substr, file_count, paths[0], paths[1]);
            break;
        case 3:
            func(substr, file_count, paths[0], paths[1], paths[2]);
            break;
        case 4:
            func(substr, file_count, paths[0], paths[1], paths[2], paths[3]);
            break;
        case 5:
            func(substr, file_count, paths[0], paths[1], paths[2], paths[3], paths[4]);
            break;
    }
    free(substr);
    return 0;
}
