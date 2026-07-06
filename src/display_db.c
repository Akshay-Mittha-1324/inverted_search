#include "../include/inverted_search.h"

void display_database(hash_t *arr)
{
    mainnode_t *main_temp;
    subnode_t *sub_temp;
    printf("%-10s %-15s %-15s %-15s %-15s\n","INDEX","WORD","FILE_COUNT","FILE_NAME","WORD_COUNT");
    for(int i = 0; i < HASH_SIZE; i++)
    {
        if(arr[i].main_link == NULL)
        {
            printf("NULL\n");
            continue;
        }
        main_temp = arr[i].main_link;
        while(main_temp)
        {
            sub_temp = main_temp -> sub_link;
            while(sub_temp)
            {
                printf("%-10d %-15s %-15d %-15s %-15d\n",i, main_temp -> word, main_temp -> file_count, sub_temp -> file_name, sub_temp -> word_count);
                sub_temp = sub_temp -> link;
            }
            main_temp = main_temp -> link;
        }
    }
    return;
}