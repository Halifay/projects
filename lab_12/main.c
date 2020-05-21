#include <stdio.h>
#include "DoublyLinkedList.h"

int main() {
    list text;
    printf("Enter words separated by whitespaces and end input with dot.\n");
    read_list(&text);
    printf("List looks like:\n");
    print_list(&text);
    list text2;
    new_list(&text2);
    clear();
    printf("Enter separation word.\n");
    char *separator = calloc(str_max_length, sizeof(char));
    scanf("%s", separator);
    while(find_word(&text, separator) == NULL)
    {
        printf("No such word in the list as \"%s\". Please try again.\n", separator);
        clear();
        scanf("%s", separator);
    }
    //printf("\n%s\n", separator);
    split_list(&text, &text2, separator);

    printf("The first half looks like:\n");
    print_list(&text);

    printf("The second half looks like:\n");
    print_list(&text2);
    return 0;
}
