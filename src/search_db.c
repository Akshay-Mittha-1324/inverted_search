/**
 * @file    search_db.c
 * @author  Akshay Ravikiran Mittha
 * @date    09/07/2026
 * @brief   Searches for a word in the database.
 * 
 * @details 
 * Functions Performed:
 * - search_database(): Searches for a word in the database.
 */

#include "../include/inverted_search.h"

/* Function to search for a word in the database */
int search_database(hash_t *arr, char *word)
{
    /* Convert the word to lowercase */
    for(int i = 0; word[i]; i++)
        word[i] = tolower(word[i]);

    /* Check if the word is NULL */
    if(word == NULL)
    {
        printf(RED "\nINFO: Empty String/Word\n" RESET);
        return FAILURE;
    }
    
    /* Get the hash index of the word */
    int idx = get_hash(word[0]);
    /* Check if the hash index is empty */
    if(arr[idx].main_link == NULL)
    {
        printf(RED "\nINFO: %s Not Found\n" RESET, word);
        return FAILURE;
    }

    /* Traverse through the Main Array */
    mainnode_t *m_temp = arr[idx].main_link;
    while(m_temp)
    {
        /* Compare the word with the current main node */
        if(strcmp(m_temp ->word, word) == 0)
        {
            /* Print the success message */
            printf(GREEN "\nINFO: Successful: " RESET);
            printf(GREEN "Word %s is present in %d Files\n" RESET, word, m_temp -> file_count);
            /* Traverse through the Sub Array */
            subnode_t *s_temp = m_temp ->sub_link;
            for(int i = 0; i < m_temp -> file_count; i++)
            {
                /* Print the file name and word count */
                printf(YELLOW "In %s => %d Times\n" RESET, s_temp -> file_name, s_temp -> word_count);
                /* Move to the next node */
                s_temp = s_temp -> link;
            }
            /* Return success */
            return SUCCESS;
        }
        /* Move to the next node */
        m_temp = m_temp -> link;
    }
    /* Print the failure message */
    printf(RED "\nINFO: %s Word Not Found in Database\n" RESET, word);
    /* Return failure */
    return FAILURE;
}