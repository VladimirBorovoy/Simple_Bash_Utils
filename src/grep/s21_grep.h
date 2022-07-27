#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#define MAXBUFLEN 1024

struct Flags {
    int e, i, v, c, l, n;
};

void parser(int argc, char**argv, struct Flags fls);
int file_exists(const char *filename);
void parse_flags(char *flags, struct Flags *fls);
void simple_search(char *file, char *template, int file_counter);
void output_result(int argc, char**argv, struct Flags fls, int file_counter, int is_flag, char *template);
void lowercase(char *line, char *template);
void regex_output(char *line, int file_counter, char *file, char *template);
void output_with_flags(struct Flags fls, char *file, char *template, int file_counter);
int check_line_regex(char *line, char *template);

#endif  // SRC_GREP_S21_GREP_H_
