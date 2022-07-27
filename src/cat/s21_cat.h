#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#define MAXBUFLEN 1024

struct Flags {
    int b, e, n, s, t, v, capT, capE;
};

static const char *const s21_cat_spec_symbols[255] = {
        [0] = "^@",
        [1] = "^A",
        [2] = "^B",
        [3] = "^C",
        [4] = "^D",
        [5] = "^E",
        [6] = "^F",
        [7] = "^G",
        [8] = "^H",
        [9] = "\t",
        [10] = "\n",
        [11] = "^K",
        [12] = "^L",
        [13] = "^M",
        [14] = "^N",
        [15] = "^O",
        [16] = "^P",
        [17] = "^Q",
        [18] = "^R",
        [19] = "^S",
        [20] = "^T",
        [21] = "^U",
        [22] = "^V",
        [23] = "^W",
        [24] = "^X",
        [25] = "^Y",
        [26] = "^Z",
        [27] = "^[",
        [28] = "^\\",
        [29] = "^]",
        [30] = "^^",
        [31] = "^_",
        [127] = "^?",
        [128] = "M-^@",
        [129] = "M-^A",
        [130] = "M-^B",
        [131] = "M-^C",
        [132] = "M-^D",
        [133] = "M-^E",
        [134] = "M-^F",
        [135] = "M-^G",
        [136] = "M-^H",
        [137] = "M-^I",
        [138] = "M-^J",
        [139] = "M-^K",
        [140] = "M-^L",
        [141] = "M-^M",
        [142] = "M-^N",
        [143] = "M-^O",
        [144] = "M-^P",
        [145] = "M-^Q",
        [146] = "M-^R",
        [147] = "M-^S",
        [148] = "M-^T",
        [149] = "M-^U",
        [150] = "M-^V",
        [151] = "M-^W",
        [152] = "M-^X",
        [153] = "M-^Y",
        [154] = "M-^Z",
        [155] = "M-^[",
        [156] = "M-^\\",
        [157] = "M-^]",
        [158] = "M-^^",
        [159] = "M-^_",
};

void output_with_no_flags(char *f);
void output_with_flags(struct Flags fls, char *f);
void print_line(char *line, int flagb, int flagn,
int flage, int flagt, int flagv, int flagT, int flagE, int num_of_lines);
void print_symbol(char chr, int flage, int flagt, int flagv, int flagT, int flagE);
int gnu_check(char *flags, struct Flags *fls);
void parse_string(char *flags, struct Flags *fls);

#endif  // SRC_CAT_S21_CAT_H_
