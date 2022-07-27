gcc s21_cat.c -o s21_cat
cat -v text.txt > p1.txt
./s21_cat -v text.txt > p2.txt
gcc conv1.c
./a.out > p3.txt
gcc conv2.c
./a.out > p4.txt
comm -3 p1.txt p2.txt
comm -3 p3.txt p4.txt