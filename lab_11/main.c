#include <stdio.h>
#include "list.h"

int main() {
    list one;
    create_list(&one);
    print_list(&one);
    multiply(&one, 2, 3);
    print_list(&one);
    return 0;
}
