#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void flag_ro(int v, char *out){
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *romans[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int pos = 0;
    for (int i = 0; i < 13; i++){
        while (v >= values[i]){
            int len = strlen(romans[i]);
            memcpy(out + pos, romans[i], len);
            pos += len;
            v -= values[i];
        }
    }
    out[pos] = '\0';
}

void flag_zr(unsigned v, char *out){ // из числа в 0 и 1
    int fib[20];
    int n = 0;
    fib[0] = 1;
    fib[1] = 2;
    n = 2;
    while (1){
        int nx = fib[n - 1] + fib[n - 2];
        if (nx > v) break;
        fib[n] = nx;
        n++;
    }
    char bits[40];
    int b = 0;
    for (int i = n - 1; i >= 0; i--){
        if (v >= fib[i]){
            bits[b] = '1';
            b++;
            v -= fib[i];
        }else{
            bits[b] = '0';
            b++;
        }
    }
    int pos = 0;
    for (int i = b - 1; i >= 0; i--){
        out[pos++] = bits[i];
    }
    out[pos] = '1';
    out[pos+1] = '\0';
}

void flag_cv(int v, int base, char *out){ // из 10 в какую-то сс (процент и деление)
    if (base < 2 || base > 36) base = 10;
    char tmp[64];
    int pos = 0;
    if (v < 0){
        tmp[pos++] = '-';
        v = -v;
    }
    if (v == 0){
        tmp[pos++] = '0';
    }else{
        while (v > 0){
            int d = v % base;
            if (d < 10){
                tmp[pos++] = '0' + d;
            } else{
                tmp[pos++] = 'a' + d - 10;
            }
            v /= base;
        }
    }
    int out_pos = 0;
    int start = 0;
    if (tmp[0] == '-'){
        out[out_pos++] = '-';
        start = 1;
    }
    else{
        start = 0;
    }
    for (int i = pos - 1; i >= start; i--){
        out[out_pos] = tmp[i];
        out_pos++;
    }
    out[out_pos] = '\0';
}

void flag_CV(int v, int base, char *out){
    if (base < 2 || base > 36) base = 10;
    char tmp[64];
    int pos = 0;
    if (v < 0){
        tmp[pos++] = '-';
        v = -v;
    }
    if (v == 0){
        tmp[pos++] = '0';
    }else{
        while (v > 0){
            int d = v % base;
            if (d < 10) tmp[pos++] = '0' + d;
            else tmp[pos++] = 'A' + d - 10;
            v /= base;
        }
    }
    int out_pos = 0;
    int start = 0;
    if (tmp[0] == '-'){
        out[out_pos++] = '-';
        start = 1;
    }
    else{
        start = 0;
    }
    for (int i = pos - 1; i >= start; i--){
        out[out_pos] = tmp[i];
        out_pos++;
    }
    out[out_pos] = '\0';
}

void flag_to(char *s, int base, char *out){ // из какой-то сс в 10
    if (base < 2 || base > 36) base = 10;
    int res = 0;
    int i = 0;
    while (s[i] != '\0'){
        int d = -1;
        if (s[i] >= '0' && s[i] <= '9')
            d = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'z')
            d = s[i] - 'a' + 10;
        if (d < 0 || d >= base) break;
        res = res * base + d;
        i++;
    }
    if (res == 0){
        out[0] = '0';
        out[1] = '\0';
        return;
    }
    char tmp[20];
    int pos = 0;
    while (res > 0){
        tmp[pos] = '0' + res % 10;
        pos++;
        res /= 10;
    }
    for (int j = 0; j < pos; j++){
        out[j] = tmp[pos - 1 - j];
    }
    out[pos] = '\0';
}

void flag_TO(char *s, int base, char *out){
    if (base < 2 || base > 36) base = 10;
    int res = 0;
    int i = 0;
    while (s[i] != '\0'){
        int d = -1;
        if (s[i] >= '0' && s[i] <= '9') d = s[i] - '0';
        else if (s[i] >= 'A' && s[i] <= 'Z') d = s[i] - 'A' + 10;
        if (d < 0 || d >= base) break;
        res = res * base + d;
        i++;
    }
    if (res == 0){
        out[0] = '0';
        out[1] = '\0';
        return;
    }
    char tmp[20];
    int pos = 0;
    while (res > 0){
        tmp[pos] = '0' + res % 10;
        pos++;
        res /= 10;
    }
    for (int j = 0; j < pos; j++){
        out[j] = tmp[pos - 1 - j];
    }
    out[pos] = '\0';
}

void flag_mi(int v, char *out){
    unsigned char *p = (unsigned char *)&v;
    int pos = 0;
    for (int i = 0; i < 4; i++){
        for (int bit = 7; bit >= 0; bit--){
            out[pos] = ((p[i] >> bit) & 1) + '0';
            pos++;
        }
        out[pos] = ' ';
    }
    out[pos] = '\0';
}

void flag_mu(unsigned int v, char *out){
    unsigned char *p = (unsigned char *)&v;
    int pos = 0;
    for (int i = 0; i < 4; i++){
        if (i > 0) out[pos++] = ' ';
        for (int bit = 7; bit >= 0; bit--){
            out[pos] = ((p[i] >> bit) & 1) + '0';
            pos++;
        }
    }
    out[pos] = '\0';
}

void flag_md(double v, char *out){
    unsigned char *p = (unsigned char *)&v;
    int pos = 0;
    for (int i = 0; i < 8; i++){
        if (i > 0) out[pos++] = ' ';
        for (int bit = 7; bit >= 0; bit--){
            out[pos] = ((p[i] >> bit) & 1) + '0';
            pos++;
        }
    }
    out[pos] = '\0';
}

void flag_mf(float v, char *out){
    unsigned char *p = (unsigned char *)&v;
    int pos = 0;
    for (int i = 0; i < 4; i++){
        if (i > 0) out[pos++] = ' ';
        for (int bit = 7; bit >= 0; bit--){
            out[pos] = ((p[i] >> bit) & 1) + '0';
            pos++;
        }
    }
    out[pos] = '\0';
}

void flag_d(int v, char *out){
    char tmp[32];
    int pos = 0;
    int neg = 0;
    if (v < 0){
        neg = 1;
        v = -v;
    }
    if (v == 0){
        tmp[pos] = '0';
        pos++;
    }else{
        while (v > 0){
            tmp[pos] = '0' + v % 10;
            pos++;
            v /= 10;
        }
    }
    if (neg){
        tmp[pos] = '-';
        pos++;
    }
    int len = pos;
    for (int i = 0; i < len; i++){
        out[i] = tmp[len - 1 - i];
    }
    out[len] = '\0';
}

void flag_lf(double v, char *out){
    int neg = 0;
    if (v < 0){
        neg = 1;
        v = -v;
    }
    long long ipart = (long long)v;
    double fpart = v - ipart;
    char tmp[64];
    int pos = 0;
    if (ipart == 0){
        tmp[pos] = '0';
        pos = pos + 1;
    }else{
        while (ipart > 0){
            tmp[pos] = '0' + ipart % 10;
            pos = pos + 1;
            ipart = ipart / 10;
        }
    }
    int len = pos;
    int out_pos = 0;
    if (neg){
        out[out_pos] = '-';
        out_pos = out_pos + 1;
    }
    for (int i = 0; i < len; i++){
        out[out_pos] = tmp[len - 1 - i];
        out_pos = out_pos + 1;
    }
    out[out_pos] = '.';
    out_pos++;
    for (int i = 0; i < 6; i++){
        fpart *= 10;
        int d = (int)fpart;
        out[out_pos] = '0' + d;
        out_pos++;
        fpart = fpart - d;
    }
    out[out_pos] = '\0';
}

int func(const char *format, va_list args, char **pbuf, int *pcap){
    char *buf = *pbuf;
    int cap = *pcap;
    int size = 0; //буфера
    int fpos = 0;
    while (format[fpos] != '\0'){
        char tmp[128];
        int tlen = 0;
        if (format[fpos] == '%'){
            fpos++;
            if (format[fpos] == 'R' && format[fpos + 1] == 'o'){
                flag_ro(va_arg(args, int), tmp);
                fpos += 2;
            }
            else if (format[fpos] == 'Z' && format[fpos + 1] == 'r'){
                flag_zr(va_arg(args, unsigned), tmp);
                fpos += 2;
            }
            else if (format[fpos] == 'C' && format[fpos + 1] == 'v'){
                int v = va_arg(args, int);
                int base = va_arg(args, int);
                flag_cv(v, base, tmp);
                fpos += 2;
            }
            else if (format[fpos] == 'C' && format[fpos + 1] == 'V'){
                int v = va_arg(args, int);
                int base = va_arg(args, int);
                flag_CV(v, base, tmp);
                fpos += 2;
            }
            else if (format[fpos] == 't' && format[fpos + 1] == 'o'){
                char *s = va_arg(args, char *);
                int base = va_arg(args, int);
                flag_to(s, base, tmp);
                fpos += 2;
            }
            else if (format[fpos] == 'T' && format[fpos + 1] == 'O'){
                char *s = va_arg(args, char *);
                int base = va_arg(args, int);
                flag_TO(s, base, tmp);
                fpos += 2;
            }
            else if (format[fpos] == 'm' && format[fpos + 1] == 'i'){
                flag_mi(va_arg(args, int), tmp);
                fpos += 2;
            }
            else if (format[fpos] == 'm' && format[fpos + 1] == 'u'){
                flag_mu(va_arg(args, unsigned), tmp);
                fpos += 2;
            }
            else if (format[fpos] == 'm' && format[fpos + 1] == 'd'){
                flag_md(va_arg(args, double), tmp);
                fpos += 2;
            }
            else if (format[fpos] == 'm' && format[fpos + 1] == 'f'){
                flag_mf((float)va_arg(args, double), tmp);
                fpos += 2;
            }
            else if (format[fpos] == 'd'){
                flag_d(va_arg(args, int), tmp);
                fpos++;
            }
            else if (format[fpos] == 'l' && format[fpos + 1] == 'f'){
                flag_lf(va_arg(args, double), tmp);
                fpos += 2;
            }
            else if (format[fpos] == 's'){
                char *s = va_arg(args, char *);
                int i = 0;
                while (s[i]){
                    tmp[i] = s[i];
                    i++;
                }
                tmp[i] = '\0';
                fpos++;
            }
            else if (format[fpos] == 'c'){
                tmp[0] = (char)va_arg(args, int);
                tmp[1] = '\0';
                fpos++;
            }
            else{ //если после % неизв флаг
                tmp[0] = '%';
                tmp[1] = format[fpos];
                tmp[2] = '\0';
                fpos++;
            }
        }
        else{ //если встретился не %
            tmp[0] = format[fpos];
            tmp[1] = '\0';
            fpos++;
        }
        tlen = strlen(tmp);
        if (size + tlen + 1 >= cap){
            cap = cap * 2;
            buf = (char *)realloc(buf, cap);
        }
        memcpy(buf + size, tmp, tlen);
        size += tlen;
    }
    buf[size] = '\0';
    *pbuf = buf;
    *pcap = cap;
    return size;
}

int oversprintf(char *str, const char *format, ...){
    if (str == NULL || format == NULL){
        printf("пустая строка или формат\n");
        return -1;
    }
    va_list args;
    va_start(args, format);
    int cap = 1024;
    char *buf = (char *)malloc(cap);
    if (buf == NULL){
        va_end(args);
        return -1;
    }
    int len = func(format, args, &buf, &cap);
    strcpy(str, buf);
    free(buf);
    va_end(args);
    return len;
}

int overfprintf(FILE *file, const char *format, ...){
    if (file == NULL || format == NULL){
        printf("пустой файл или формат\n");
        return -1;
    }
    va_list args;
    va_start(args, format);
    int cap = 1024;
    char *buf = (char *)malloc(cap);
    if (buf == NULL){
        va_end(args);
        return -1;
    }
    int len = func(format, args, &buf, &cap);
    fputs(buf, file);
    free(buf);
    va_end(args);
    return len;
}

int main(){
    char buf[1024];
    int l1 = oversprintf(buf, "%Ro %Zr %Cv %CV %to %TO %mi %mu %md %mf %d %s %c\n",
                14, 10u, 26, 16, 26, 16, "1a", 16, "2B", 12, 1, 4294967295u, 1.0, 1.0f, 42, "privet", 'A');
    printf("%d %s\n", l1, buf);
    int l2 = oversprintf(NULL, "%d", 42);
    printf("%d\n", l2);
    FILE *f = fopen("test5.txt", "w");
    if (f == NULL){
        printf("не удалось открыть файл\n");
        return -1;
    }
    int l3 = overfprintf(f, "%Ro %Zr %d\n", 2026, 10u, 472);
    fclose(f);
    printf("%d\n", l3);
    return 0;
}
