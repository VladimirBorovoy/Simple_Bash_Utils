#include <stdio.h>
#include <string.h>
#include "s21_cat.h"
#include "stdlib.h"

int main(int argc, char **argv) {
    struct Flags fls = {0, 0, 0, 0, 0, 0, 0, 0};
    int is_flag = 0, file_counter = 0;
    char flags[MAXBUFLEN] = "";
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-", 1) == 0) {
            strcat(flags, argv[i]);
            is_flag = 1;
        } else {
            file_counter++;
        }
    }
    if (is_flag == 0) {
        for (int i = 1; i < argc; i++) {
            output_with_no_flags(argv[i]);
        }
    } else {
        if (gnu_check(flags, &fls) == 0) {parse_string(flags, &fls);}
        for (int i = argc - file_counter; i < argc; i++) output_with_flags(fls, argv[i]);
    }
    return 0;
}

void output_with_no_flags(char *f) {
    FILE *fptr;
    char buffer;
    fptr = fopen(f, "r");
    if (fptr == NULL) {
        printf("%s: No such file or directory\n", f);
    } else {
        buffer = fgetc(fptr);
        while (buffer != EOF) {
            printf("%c", buffer);
            buffer = fgetc(fptr);
        }
    fclose(fptr);
    }
}

void output_with_flags(struct Flags fls, char *f) {
    FILE *fptr;
    char buffer[MAXBUFLEN];
    int line_counter = 0, prev_len = 0;
    if (fls.b ==1) fls.n=0;
    fptr = fopen(f, "r");
    if (fptr == NULL) {
        printf("%s: No such file or directory\n", f);
    } else {
        char c = fgetc(fptr);
        while (c != EOF) {
            int j = 0;
            while (c != '\n' && c != EOF) {
                buffer[j++] = c;
                c = fgetc(fptr);
            }
            if (c =='\n' && c != EOF)
                buffer[j++] = c;
            buffer[j] = '\0';
            c = fgetc(fptr);
            line_counter++;
            if (fls.s && strlen(buffer) == 1 && prev_len == 1) {
                line_counter--;
                continue;
            } else {print_line(buffer, fls.b, fls.n, fls.e, fls.t, fls.v, fls.capT, fls.capE, line_counter);}
            prev_len = strlen(buffer);
            for (int i = 0; i < MAXBUFLEN; i++) buffer[i] = EOF;
        }
        fclose(fptr);
    }
}

void print_line(char *line, int flagb, int flagn, int flage,
int flagt, int flagv, int flagT, int flagE, int num_of_lines) {
    char text[100];
    static int counter = 0;
    sprintf(text, "%d", num_of_lines - counter);
    if (flagb) {
        if (strlen(line) == 1 && line[0] == '\n') {
            counter++;
        } else {
            for (int i = 0; i < 6 - (int)strlen(text); i++) printf(" ");
            printf("%d\t", num_of_lines - counter);
        }
    }
    if (flagn) {
        for (int i = 0; i < 6 - (int)strlen(text); i++) printf(" ");
        printf("%d\t", num_of_lines - counter);
    }
    for (int i = 0; i < (int)strlen(line); i++) {
        print_symbol(line[i], flage, flagt, flagv, flagT, flagE);
    }
}

void print_symbol(char chr, int flage, int flagt, int flagv, int flagT, int flagE) {
    if (chr == '\t' && (flagt || flagT)) {
        printf("^I");
    } else {
        if (chr == '\n' && (flage || flagE)) {
            printf("$\n");
        } else {
            if (((int)chr < 32 || (int)chr > 126) && (flagv || flagt || flage) && (!flagT || !flagE)) {
                printf("%s", s21_cat_spec_symbols[(int)chr]);
            } else {
                printf("%c", chr);
            }
        }
    }
}

int gnu_check(char *flags, struct Flags *fls) {
    int flag = 0;
    if (strstr(flags, "--number-nonblank")) {
        fls -> b = 1;
        flag = 1;
    }
    if (strstr(flags, "--number") && strstr(flags, "--number-nonblank") == 0) {
        // "This option is ignored if -b is in effect" ; https://www.gnu.org/software/coreutils/manual/html_node/cat-invocation.html#cat-invocation
        fls -> n = 1;
        flag = 1;
    }
    if (strstr(flags, "--squeeze-blank")) {
        fls -> s = 1;
        flag = 1;
    }
    return flag;
}

void parse_string(char *flags, struct Flags *fls) {
    for (int i = 0; i < (int)strlen(flags); i++) {
        char c = flags[i];
        switch (c) {
            case 'b' :
                fls -> b = 1;
                break;
            case 'e' :
                fls -> e = 1;
                break;
            case 'n' :
                fls -> n = 1;
                break;
            case 's' :
                fls -> s = 1;
                break;
            case 't' :
                fls -> t = 1;
                break;
            case 'v' :
                fls -> v = 1;
                break;
            case 'T' :
                fls -> capT = 1;
                break;
            case 'E' :
                fls -> capE = 1;
                break;
        }
    }
}
