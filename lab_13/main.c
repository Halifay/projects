#include <stdio.h>
#include "BinaryTree.h"
#include "MihaInput.h"

int main() {
    node tree;
    new_node(&tree);
    int length;
    printf("Enter number of words.\n");
    length = get_int();
    // scanf("%d", &length);
    printf("Print words separated by whitespaces with no more than 20 chars.\n");
    // clear_input();
    for(int i = 0; i < length; i++)
    {
        char *string = calloc(str_max_size, sizeof(char));
        scanf("%s", string);
        add_word(&tree, string);
        free(string);
    }

    printf("dfs\n");
    dfs(&tree);

    printf("\nbfs\n");
    bfs(&tree);

    printf("\nget max\n");
    get_max(&tree);

    destroy_tree(&tree);

    return 0;
}
