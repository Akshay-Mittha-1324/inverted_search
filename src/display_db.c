/**
 * @file    display_db.c
 * @author  Akshay Ravikiran Mittha
 * @date    09/07/2026
 * @brief   Displays the database.
 * 
 * @details 
 * Functions Performed:
 * - display_database(): Displays the database.
 */

#include "../include/inverted_search.h"

/* Function to display the database */
void display_database(hash_t *arr)
{
    /* Variable to check if the database is empty */
    char status = 0;
    mainnode_t *main_temp;
    subnode_t *sub_temp;

    /* Printing the Database Header */
    printf("+----------+---------------+---------------+---------------+---------------+\n");
    printf(CYAN "| %-8s | %-13s | %-13s | %-13s | %-13s |\n" RESET,"INDEX", "WORD", "FILE_COUNT", "FILE_NAME", "WORD_COUNT");
    printf("+----------+---------------+---------------+---------------+---------------+\n");
    
    /* Loop through the hash table */
    for(int i = 0; i < HASH_SIZE; i++)
    {
        /* Skip empty buckets */
        if(arr[i].main_link == NULL)
            continue;
        
        main_temp = arr[i].main_link;
        status = 1;
        /* Loop through the main array */
        while(main_temp)
        {
            /* Loop through the sub array */
            sub_temp = main_temp -> sub_link;
            
            // Flag to track if this is the first file for the current word
            int is_first = 1; 
            
            while(sub_temp)
            {
                if (is_first)
                {
                    // Print everything for the first row
                    printf("| %-8d | %-13s | %-13d | %-13s | %-13d |\n", i, main_temp->word, main_temp->file_count, sub_temp->file_name, sub_temp->word_count);
                    is_first = 0; // Turn off the flag
                }
                else
                {
                    // For the 2nd, 3rd, 4th file, print empty spaces for the first 3 columns!
                    printf("| %-8s | %-13s | %-13s | %-13s | %-13d |\n", "", "", "", sub_temp->file_name, sub_temp->word_count);
                }
                /* Move to the next node */
                sub_temp = sub_temp -> link;
            }
            /* Print a divider after all files for a word are printed */
            printf("+----------+---------------+---------------+---------------+---------------+\n");
            /* Move to the next node */
            main_temp = main_temp -> link;
        }

    }
    /* Print the failure message */
    if(!status)
        printf(RED "\n\nDATABASE IS EMPTY\n\n" RESET);
    return;
}