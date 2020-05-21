#include <stdio.h>
#include "list.h"

int main() {
    list one;
    create_list(&one);
    print_list(&one);
    printf("Enter power of factor.\n");
    int power = -1;
    scanf("%d", &power);
    while(power < 0)
    {
        printf("Power can not be less than zero. Please try again.\n");
        clear();
        scanf("%d", &power);
    }

    printf("Enter coefficient of factor.\n");
    int coef = 0;
    scanf("%d", &coef);
    while(coef == 0)
    {
        printf("Coefficient can not be equal to zero. Please try again.\n");
        clear();
        scanf("%d", &coef);
    }

    multiply(&one, power, coef);
    print_list(&one);
    destroy_list(&one);
    return 0;
}
