#include <iostream>

void ass_fun(char **digits)
{
    asm volatile(
    //conditions
    "cmp %[digit_2], %[digit_3]\n\t"
    "jne OTHERWISE\n\t"
    "cmp %[digit_3], %[digit_4]\n\t"
    "je OTHERWISE\n\t"

    //if condition is true
    "cmp $51, %[digit_2]\n\t"
    "jl END\n\t"
    "sub $3, %[digit_2]\n\t"
    "jmp END\n\t"

    //otherwise do
    "OTHERWISE:\n\t"
    "xor %[digit_1], %[digit_2]\n\t"
    "xor %[digit_2], %[digit_1]\n\t"
    "xor %[digit_1], %[digit_2]\n\t"

    //end of program
    "END:\n\t"

    : [digit_1] "+r" ((*digits)[0]),
    [digit_2] "+r" ((*digits)[1]),
    [digit_3] "+r" ((*digits)[2]),
    [digit_4] "+r" ((*digits)[3]));
}

void test(char **digits)
{
    printf("before: %s\n", *digits);
    ass_fun(digits);
    printf("after: %s\n", *digits);
    printf("\n");
}

int main() {
    char *test1, *test2, *test3, *test4;
    test1 = (char *)calloc(4, sizeof(char));
    test2 = (char *)calloc(4, sizeof(char));
    test3 = (char *)calloc(4, sizeof(char));
    test4 = (char *)calloc(4, sizeof(char));
    test1[0] = '5'; test1[1] = '6'; test1[2] = '7'; test1[3] = '8';
    test2[0] = '5'; test2[1] = '3'; test2[2] = '3'; test2[3] = '8';
    test3[0] = '5'; test3[1] = '2'; test3[2] = '2'; test3[3] = '8';
    test4[0] = '5'; test4[1] = '3'; test4[2] = '3'; test4[3] = '3';
    printf("First test\n");
    test(&test1);
    printf("Second test\n");
    test(&test2);
    printf("Third test\n");
    test(&test3);
    printf("Forth test\n");
    test(&test4);
    return 0;
}

