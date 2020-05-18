//
//  main.c
//  A4
//
//  Created by Anatoly Korb on 14/05/2019.
//  Copyright © 2019 Anatoly Korb. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Режим отладки
#define DEBUG 1


int main(int argc, const char * argv[]) {
    setlocale(LC_ALL, "rus");
    setlocale(LC_NUMERIC, "eng");
    char A1[17];
    short int B[17], B1[17];
    int n;
    int i = 1, j = 0, a = 0, k = 0, l = 0, k1 = 0;
    printf("Вариант 18. \n");
    printf("___________________________________________________________________\n");
    printf("Дан массив A из 16 байтов. Он разбит последовательно на слова. \n"
           "Если младший байт больше старшего (числа беззнаковые), то поменять их местами, \n"
           "одновременно помещая в массив В их первоначальные адреса.\n"
           "Сосчитать количество таких пар\n");
    printf("___________________________________________________________________\n");
#if DEBUG == 1
    char A[17] = { 2, 50, 51, 3, 53, 1, 18, 0, 57, 5, 18, 50, 1, 52, 53, 51 };
    A[16] = 0;
    for (i = 0; i < 16; i++) {
        printf("%d ", (int)A[i]);
    }
    printf("\n");

#else
    char A[17];
        printf("Массив A:\n");
        for (i = 0; i < 16; i++) {
            printf("A[%d] = ", i);
            scanf("%d", &a);
            A[i] = (char)a;
        }
#endif

    for (i = 0; i < 16; i += 2) {
        if (A[i + 1] > A[i]) {
            A1[j] = A[i + 1];
            B1[l] = i;
            j++;
            l++;
            A1[j] = A[i];
            B1[l] = i + 1;
            j++;
            l++;
            k1 += 2;
        }
        else {
            A1[j] = A[i];
            j++;
            A1[j] = A[i + 1];
            j++;
        }
        k += 2;
    }
    printf("C result:\n");
    printf("Массив А с замененными элементами:\n");
    for (i = 0; i < 16; i++) {
        printf("%d ", (int)A1[i]);
    }
    printf("\n");
    printf("Сдвиги на слова, в который старший байт меньше\n");
    for (l = 0; l < k1; l++) {
        printf("%d ", (int)B1[l]);
    }
    printf("\n");
    printf("Количество пар, в которых старший байт меньше:\n");
    printf("%d\n", k1);
    __asm__
    {
    //обнуляем все регистры
    mov eax, 0
    mov ebx, 0
    mov ecx, 0
    mov edx, 0
    mov esi, 0
    mov edi, 0

    P :
    mov al, byte ptr[A + ecx]//переносим старший разряд в al
    inc ecx//увеличиваем счетчик по массиву А
    mov ah, byte ptr[A + ecx]//переносим младший разряд в ah
    cmp al, ah//сравниваем два разряда
    jge G//если старший больше или равен, то переходим в G
    dec ecx//уменьшаем счетчик по массиву А
    mov byte ptr[B + esi], cl//переносим смещение (адрес) старшего разряда в массив В
    mov byte ptr[A + ecx], ah//помещаем на место старшего разряда младший
    inc esi//увеличиваем счетчик по массиву В
    inc esi//увеличиваем счетчик по массиву В
    inc ecx//увеличиваем счетчик по массиву А
    mov byte ptr[B + esi], cl//переносим смещение (адрес) младшего разряда в массив В
    mov byte ptr[A + ecx], al//помещаем на место младшего разряда старший
    inc esi//увеличиваем счетчик по массиву В
    inc esi//увеличиваем счетчик по массиву В

    G :
    inc ecx//увеличиваем счетчик по массиву А
    cmp ecx, 16//сравниваем счетчик массива A и 16, чтобы не выйти за границы
    jne P //если не вышли - продолжаем движение по циклу
    mov n, esi //сохраняем в n количество замененных элементов
    }
    printf("Asm result:\n");
    printf("Массив А с замененными элементами:\n");
    for (i = 0; i < 16; i++) {
        printf("%d ", (int)A[i]);
    }
    printf("\n");
    printf("Сдвиги на слова, в который старший байт меньше\n");
    for (i = 0; i < n / 2; i++) {
        printf("%x ", (int)B[i]);
    }
    printf("\n");
    printf("Количество пар, в которых старший байт меньше:\n");
    printf("%d\n", n / 2);
    return 0;
}
