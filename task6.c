#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int roman_val(char c){
    if (c == 'I') return 1;
    if (c == 'V') return 5;
    if (c == 'X') return 10;
    if (c == 'L') return 50;
    if (c == 'C') return 100;
    if (c == 'D') return 500;
    if (c == 'M') return 1000;
    return 0;
}

int flag_ro(char *s, int *pos){
    int res = 0;
    while (roman_val(s[*pos]) != 0){
        int cur = roman_val(s[*pos]);
        int nx = roman_val(s[*pos + 1]);
        if (cur < nx) res -= cur;
        else res += cur;
        (*pos)++;
    }
    return res;
}

unsigned int flag_zr(char *s, int *pos){ // из 0 и 1 в число
    unsigned int res = 0;
    long w1 = 1;
    long w2 = 2;
    char prev = '0';
    while (s[*pos] == '0' || s[*pos] == '1'){
        if (s[*pos] == '1' && prev == '1'){
            (*pos)++;
            break;
        }
        if (s[*pos] == '1') res += w1;
        long nx = w1 + w2;
        w1 = w2;
        w2 = nx;
        prev = s[*pos];
        (*pos)++;
    }
    return res;
}

int flag_cv(char *s, int *pos, int base){
    int res = 0;
    while (1){
        int d = -1;
        if (s[*pos] >= '0' && s[*pos] <= '9'){
            d = s[*pos] - '0';
        } else if (s[*pos] >= 'a' && s[*pos] <= 'z'){
            d = s[*pos] - 'a' + 10;
        }
        if (d == -1)
            break;
        res = res * base + d;
        (*pos)++;
    }
    return res;
}

int flag_CV(char *s, int *pos, int base){
    int res = 0;
    while (1){
        int d = -1;
        if (s[*pos] >= '0' && s[*pos] <= '9'){
            d = s[*pos] - '0';
        } else if (s[*pos] >= 'A' && s[*pos] <= 'Z'){
            d = s[*pos] - 'A' + 10;
        }
        if (d == -1)
            break;
        res = res * base + d;
        (*pos)++;
    }
    return res;
}

int flag_d(char *s, int *pos){
    int sign = 1;
    if (s[*pos] == '-'){
        sign = -1;
        (*pos)++;
    }
    int res = 0;
    while (s[*pos] >= '0' && s[*pos] <= '9'){
        res = res * 10 + (s[*pos] - '0');
        (*pos)++;
    }
    return sign * res;
}

double flag_lf(char *s, int *pos){
    int sign = 1;
    if (s[*pos] == '-'){
        sign = -1;
        (*pos)++;
    }
    double res = 0;
    while (s[*pos] >= '0' && s[*pos] <= '9'){
        res = res * 10 + (s[*pos] - '0');
        (*pos)++;
    }
    if (s[*pos] == '.'){
        (*pos)++;
        double w = 0.1;
        while (s[*pos] >= '0' && s[*pos] <= '9'){
            res = res + (s[*pos] - '0') * w;
            w /= 10;
            (*pos)++;
        }
    }
    return sign * res;
}

void flag_s(char *s, int *pos, char *out){
    int i = 0;
    while (s[*pos] != '\0' && s[*pos] != ' ' && s[*pos] != '\n'){
        out[i] = s[*pos];
        i++;
        (*pos)++;
    }
    out[i] = '\0';
}

int scan(char *s, char *format, va_list args){
    int pos = 0;
    int fpos = 0;
    int count = 0;
    while (format[fpos] != '\0'){
        if (format[fpos] == ' '){
            while (s[pos] == ' ' || s[pos] == '\n') pos++;
            fpos++;
        }
        else if (format[fpos] == '%'){
            fpos++;
            while (s[pos] == ' ' || s[pos] == '\n')
                pos++;
            if (format[fpos] == 'R' && format[fpos + 1] == 'o'){
                int *p = va_arg(args, int *);
                *p = flag_ro(s, &pos);
                count++;
                fpos += 2;
            }
            else if (format[fpos] == 'Z' && format[fpos + 1] == 'r'){
                unsigned int *p = va_arg(args, unsigned int *);
                *p = flag_zr(s, &pos);
                count++;
                fpos += 2;
            }
            else if (format[fpos] == 'C' && format[fpos + 1] == 'v'){
                int *p = va_arg(args, int *);
                int base = va_arg(args, int);
                *p = flag_cv(s, &pos, base);
                count++;
                fpos += 2;
            }
            else if (format[fpos] == 'C' && format[fpos + 1] == 'V'){
                int *p = va_arg(args, int *);
                int base = va_arg(args, int);
                *p = flag_CV(s, &pos, base);
                count++;
                fpos += 2;
            }
            else if (format[fpos] == 'd'){
                int *p = va_arg(args, int *);
                *p = flag_d(s, &pos);
                count++;
                fpos++;
            }
            else if (format[fpos] == 'l' && format[fpos + 1] == 'f'){
                double *p = va_arg(args, double *);
                *p = flag_lf(s, &pos);
                count++;
                fpos += 2;
            }
            else if (format[fpos] == 'f'){
                float *p = va_arg(args, float *);
                *p = (float)flag_lf(s, &pos);
                count++;
                fpos++;
            }
            else if (format[fpos] == 's'){
                char *p = va_arg(args, char *);
                flag_s(s, &pos, p);
                count++;
                fpos++;
            }
            else if (format[fpos] == 'c'){
                char *p = va_arg(args, char *);
                *p = s[pos];
                pos++;
                count++;
                fpos++;
            }
            else{
                fpos++;
            }
        }
    }
    return count;
}

int oversscanf(char *str, char *format, ...){
    va_list args;
    va_start(args, format);
    int res = scan(str, format, args);
    va_end(args);
    return res;
}

int overfscanf(FILE *stream, char *format, ...){
    int cap = 1024;
    int size = 0;
    char *buf = (char *)malloc(cap);
    int c;
    while ((c = fgetc(stream)) != EOF){
        if (size + 1 >= cap){
            cap *= 2;
            buf = (char *)realloc(buf, cap);
        }
        buf[size] = c;
        size++;
    }
    buf[size] = '\0';
    va_list args;
    va_start(args, format);
    int res = scan(buf, format, args);
    va_end(args);
    free(buf);
    return res;
}


int main(){
    int a = 0;
    unsigned int b = 0;
    int c = 0;
    int d = 0;
    double e = 0;
    char word[100];
    int n = oversscanf("XIV 010011 1a 2B 3.14 privet", "%Ro %Zr %Cv %CV %lf %s", &a, &b, &c, 16, &d, 12, &e, word);
    printf("прочитано %d\n", n);
    printf("%d %u %d %d %.2f %s\n", a, b, c, d, e, word);
    FILE *fin = fopen("test6.txt", "r");
    if (fin == NULL){
        printf("файл не открылся\n");
        return 1;
    }
    int x = 0;
    unsigned int y = 0;
    int m = overfscanf(fin, "%Ro %Zr", &x, &y);
    printf("прочитано %d\n", m);
    printf("%d %u\n", x, y);
    fclose(fin);
    return 0;
}
