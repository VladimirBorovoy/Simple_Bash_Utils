#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include "s21_grep.h"

int main(int argc, char **argv) {
    struct Flags fls = {0, 0, 0, 0, 0, 0};
    parser(argc, argv, fls);
}

void parser(int argc, char**argv, struct Flags fls) {
    int file_counter = 0, is_flag = 0;
    char template[MAXBUFLEN] = "";
    for  (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-", 1) == 0) {
            parse_flags(argv[i], &fls);
            is_flag++;
        } else {
            strcpy(template, argv[i]);
            file_counter = argc - i - 1;
            break;
        }
    }
    output_result(argc, argv, fls, file_counter, is_flag, template);
}

void output_result(int argc, char**argv, struct Flags fls, int file_counter, int is_flag, char *template) {
    if (is_flag == 0 || (is_flag == 1 && fls.e)) {
        for (int i = 2 + is_flag; i < argc; i++) {
            simple_search(argv[i], template, file_counter);
        }
    } else {
        for (int i = argc - file_counter; i < argc; i++) {
            output_with_flags(fls, argv[i], template, file_counter);
        }
    }
}

void simple_search(char *file, char *template, int file_counter) {
    FILE *fptr;
    char buffer[MAXBUFLEN];
    fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("%s: No such file or directory\n", file);
    } else {
        while (!feof(fptr)) {
            if (fgets(buffer, MAXBUFLEN, fptr)) {
                regex_output(buffer, file_counter, file, template);
            }
        }
    }
    fclose(fptr);
}

void regex_output(char *line, int file_counter, char *file, char *template) {
    regex_t regex;
    int value = 0;
    value = regcomp(&regex, template, 0);
    value = regexec(&regex, line, 0, NULL, 0);
    if (value == 0) {
        if (file_counter > 1) {
            printf("%s:", file);
        }
        printf("%s", line);
    }
    regfree(&regex);
}

void output_with_flags(struct Flags fls, char *file, char *template, int file_counter) {
    int c_flag_counter = 0, num_of_lines = 0;
    FILE *fptr;
    char buffer[MAXBUFLEN], backup_buffer[MAXBUFLEN];
    fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("%s: No such file or directory\n", file);
    } else {
    while (!feof(fptr)) {
        if (fgets(buffer, MAXBUFLEN, fptr)) {
            num_of_lines++;
            strcpy(backup_buffer, buffer);
            if (fls.i) lowercase(buffer, template);
            if (fls.c || fls.l) {
                c_flag_counter += check_line_regex(buffer, template);
            } else {
                if (fls.v) {
                    if (check_line_regex(buffer, template) == 0) {
                        if (file_counter > 1) printf("%s:", file);
                        if (fls.n) printf("%d:", num_of_lines);
                        printf("%s", backup_buffer);
                        if (feof(fptr)) printf("\n");
                    }
                } else {
                    if (check_line_regex(buffer, template)) {
                        if (file_counter > 1) printf("%s:", file);
                        if (fls.n) printf("%d:", num_of_lines);
                        printf("%s", backup_buffer);
                    }
                }
            }
        }
    }
    }
    fclose(fptr);
    if (fls.c) {
        if (file_counter > 1) printf("%s:", file);
        printf("%d\n", c_flag_counter);
    } else if (fls.l && c_flag_counter > 0) {
        printf("%s\n", file);
    }
}

int check_line_regex(char *line, char *template) {
    regex_t regex;
    int value = 0, counter = 0;
    value = regcomp(&regex, template, 0);
    value = regexec(&regex, line, 0, NULL, 0);
    if (value == 0) {
        counter++;
    }
    regfree(&regex);
    return counter;
}

void lowercase(char *line, char *template) {
    for (int i = 0; i < (int)strlen(line); i++) {
        if (line[i] > 64 && line[i] < 91) line[i] = line[i] + 32;
    }
    for (int i = 0; i < (int)strlen(template); i++) {
        if (template[i] > 64 && template[i] < 91) template[i] = template[i] + 32;
    }
}

void parse_flags(char *flags, struct Flags *fls) {
    for (int i = 0; i < (int)strlen(flags); i++) {
        char c = flags[i];
        switch (c) {
            case 'e' :
                fls -> e = 1;
                break;
            case 'i' :
                fls -> i = 1;
                break;
            case 'v' :
                fls -> v = 1;
                break;
            case 'c' :
                fls -> c = 1;
                break;
            case 'l' :
                fls -> l = 1;
                break;
            case 'n' :
                fls -> n = 1;
                break;
        }
    }
}
