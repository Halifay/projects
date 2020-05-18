#include <iostream>
#include <string.h>

const int max_length = 402;

    bool check_word(char **string, int left, int right)
    {
        left++; right--;
        if(right - left + 1 > 10)
            return false;
        if(right < left)
            return false;
        for(int i = left; i <= right; i++)
        {
            if(!(('A' <= (*string)[i] && (*string)[i]<= 'Z') ||
                ('a' <= (*string)[i] && (*string)[i]<= 'z') ||
                ('0' <= (*string)[i] && (*string)[i]<= '9')))
                return false;
        }
        return true;
    }

    void find_words(char **string, char ***words, int *size)
    {
        int left = 0, right = 0;
        int string_size = strlen(*string);
        bool is_left_found = false;
        while(left < string_size && right < string_size)
        {
            if(is_left_found)
            {
                if(right < left)
                    right = left + 1;

                if((*string)[right] == '[')
                {
                    left = right;
                }

                if((*string)[right] == ']')
                {
                    is_left_found = false;
                    if(check_word(string, left, right))
                    {
                        (*words)[*size] = (char *)calloc(right - left + 1, sizeof(char));
                        for(int i = left; i <= right; i++)
                        {
                            (*words)[*size][i-left] = (*string)[i];
                        }
                        (*size)++;
                    }
                }
                else
                    right++;
            }
            else
            {
                if(left < right)
                    left = right + 1;
                if((*string)[left] == '[')
                {
                    is_left_found = true;
                }
                else
                    left++;
            }
        }
        // printf("%d\n", right);
    }

    void get_answer(char **string)
    {
        //int size = strlen(*string);
        int size = 0;
        char **words = (char **)calloc(max_length, sizeof(char *));
        //printf("Type your string\n");
        //scanf("%[^\n]", string);
        printf("The input is: %s\n", *string);
        //printf("input size is: %d\n", size);
        find_words(string, &words, &size);
        if(size > 30)
        {
            printf("There are more than 30 words!!!\n\n");
            return;
        }

        if(size == 0)
            printf("The string contains no words.\n");
        else
            printf("The string contains the following words:\n");

        for(int i = 0; i < size; i++)
            printf("%s\n", words[i]);
        //free(string);
        for(int i = 0; i < size; i++)
            free(words[i]);
        free(words);
        printf("\n");
    }

    void test()
    {
        char *test_1 = "[Aa1][]",
            *test_2 = "[[[wqe]qwe]",
            *test_3 = "[qwerпривет]",
            *test_4 = "[qweqweqweqwe]",
            *test_5 = "[Aa1], asdf[][[qwer][хеллоуъ]sdafas, [kana-jambe][228]",
            *test_6 = "[[q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q][q]q][q][q][q][q]";
        get_answer(&test_1);
        get_answer(&test_2);
        get_answer(&test_3);
        get_answer(&test_4);
        get_answer(&test_5);
        get_answer(&test_6);
    }

int main() {
    test();
    return 0;
}
