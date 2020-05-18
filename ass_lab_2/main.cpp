#include <stdio.h>
#include <stdlib.h>

// функция для вычисления ответа на языке ассемблера
short asmfun(char x, char y, short z)
{
    short v;
    __asm__(
            // Bвод переменных осуществляется согласно их размеру
            "mov %[y], %%al\n\t"
            "cbtw\n\t"
            "mov %%ax, %%bx\n\t"

            "mov %[z], %%ax\n\t"
            "mov %%ax, %%cx\n\t"

            "mov %[x], %%al\n\t"
            "cbtw\n\t"

            // B индексе a хранится x, в b хранится y и в c хранится z.
            // Значение y расширенно заранее, так как расширение может производиться только
            // в индексе a.

            // Вычисление числителя
            "add $5, %%ax\n\t"
            "imul %%cx\n\t"
            "sub $3, %%ax\n\t"
            "sbb $0, %%dx\n\t"

            // Вычисление знаменателя
            "sub $4, %%bx\n\t"

            // Получение значения выражения
            "idiv %%bx\n\t"
            "sub $2, %%ax\n\t"
            "mov %%ax, %[v]\n\t"
            : [v] "=m" (v)
            : [x] "m" (x), [y] "m" (y), [z] "m" (z));
    return v;
}

// функция для вычисления ответа на языке C
short cfun(char x, char y, short z)
{
    short v = ((x+5)*z - 3)/(y - 4) - 2;
    return v;
}

// функция для удобного вывода результа работы программы
void tester(char x, char y, short z, short v)
{
    short asm_v = asmfun(x, y, z);
    short c_v = cfun(x, y, z);
    printf("Supposed result: %d in decimal form and %X in hexadecimal form\n", v, v);
    printf("Assembler result: %d in decimal form and %X in hexadecimal form\n", asm_v, asm_v);
    printf("C result: %d in decimal form and %X in hexadecimal form\n", c_v, c_v);
}

int main(int argc, char** argv) {
    char x = -0x7, y = -0x3;
    short z = 0x2, v = -0x1;
    printf("First case\n");
    tester(-0x7, -0x3, 0x2, -0x1);
    printf("\nSecond case\n");
    tester(0x7D, -0x7E, 0x3FB5, -0x3FB6);
}


