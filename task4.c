#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[255];
    int size;
    int importance;
} File;

typedef struct {
    char **names;
    int count;
    int total_size;
    int total_importance;
} Result;

Result solve(File *files, int n, int capacity) {
    Result res;
    res.names = NULL;
    res.count = 0;
    res.total_size = 0;
    res.total_importance = 0;
    if (n == 0 || capacit
        y == 0) return res;
    
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)calloc(capacity + 1, sizeof(int));
    }
    
    for (int i = 1; i <= n; i++){
        for (int w = 0; w <= capacity; w++) {
            dp[i][w] = dp[i - 1][w];
            if (files[i - 1].size <= w) {
                int val = dp[i - 1][w - files[i - 1].size] + files[i - 1].importance;
                if (val > dp[i][w]) {
                    dp[i][w] = val;
                }
            }
        }
    }
    
    res.total_importance = dp[n][capacity];
    int *taken = (int *)calloc(n, sizeof(int));
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            taken[i - 1] = 1;
            w -= files[i - 1].size;
        }
    }
    
    res.count = 0;
    for (int i = 0; i < n; i++) {
        if (taken[i])
            res.count++;
    }
    if (res.count > 0) {
        res.names = (char **)malloc(res.count * sizeof(char *));
        int idx = 0;
        for (int i = 0; i < n; i++) {
            if (taken[i]) {
                res.names[idx] = (char *)malloc(strlen(files[i].name) + 1);
                strcpy(res.names[idx], files[i].name);
                res.total_size += files[i].size;
                idx++;
            }
        }
    }
    
    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);
    free(taken);
    return res;
}

int main() {
    int n, capacity;
    if (scanf("%d %d", &n, &capacity) != 2) {
        printf("ошибка ввода\n");
        return 1;
    }
    if (n < 0 || capacity < 0) {
        printf("некорректные данные\n");
        return 1;
    }
    File *files = (File *)malloc(n * sizeof(File));
    for (int i = 0; i < n; i++) {
        if (scanf("%s %d %d", files[i].name, &files[i].size, &files[i].importance) != 3) {
            printf("ошибка ввода файла %d\n", i + 1);
            free(files);
            return 1;
        }
        if (strlen(files[i].name) == 0) {
            printf("пустое имя файла\n");
            free(files);
            return 1;
        }
        if (files[i].size <= 0 || files[i].importance < 0) {
            printf("некорректные данные файла %s\n", files[i].name);
            free(files);
            return 1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(files[i].name, files[j].name) == 0) {
                printf("файлы совпадают: %s\n", files[i].name);
                free(files);
                return 1;
            }
        }
    }
    
    Result res = solve(files, n, capacity);
    printf("TOTAL_SIZE %d\n", res.total_size);
    printf("TOTAL_IMPORTANCE %d\n", res.total_importance);
    printf("FILES %d\n", res.count);
    for (int i = 0; i < res.count; i++) {
        printf("%s\n", res.names[i]);
    }
    for (int i = 0; i < res.count; i++)
        free(res.names[i]);
    free(res.names);
    free(files);
    return 0;
}
