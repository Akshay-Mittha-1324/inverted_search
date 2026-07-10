/**
 * @file    save_db.c
 * @author  Akshay Ravikiran Mittha
 * @date    09/07/2026
 * @brief   Saves the database to a file.
 * 
 * @details 
 * Functions Performed:
 * - save_database(): Saves the database to a file.
 */

#include "../include/inverted_search.h"

/* Function to save database */
int save_database(hash_t *arr, char *file_name)
{
    /* Opening the File for Writing */
    FILE *fp = fopen(file_name, "w");
    if(fp == NULL)
    {
        perror(RED "\nINFO: ERROR: " RESET);
        return FAILURE;
    }
    
    /* Checking if the file is .txt */
    int len = strlen(file_name);
    if(strcmp(file_name + (len - 4), ".txt") != 0)
    {
        printf(RED "\nINFO: %s File is Not a Text File\n" RESET, file_name);
        return FAILURE;
    }

    /* Traverse through the Main Array and Sub Array and store in the database file */
    mainnode_t *m_temp;
    subnode_t *s_temp;
    for(int i = 0; i < HASH_SIZE; i++)
    {
        /* Skip empty buckets */
        if(arr[i].main_link == NULL)
            continue;
        
        m_temp = arr[i].main_link;
        /* Traverse through the Main Array */
        while(m_temp)
        {
            /* Traverse through the Sub Array */
            s_temp = m_temp -> sub_link;
            /* Writing the database file */
            fprintf(fp, "#%hd;%s;%d;", arr[i].index, m_temp -> word, m_temp -> file_count);
            for(int j = 0; j < m_temp -> file_count; j++)
            {
                /* Writing the file name and word count */
                fprintf(fp, "%s;%d;", s_temp -> file_name, s_temp -> word_count);
                s_temp = s_temp -> link;
            }
            /* Writing the end hash */
            fprintf(fp, "#\n");
            /* Moving to the next node */
            m_temp = m_temp -> link;
        }
    }
    /* Closing the file */
    fclose(fp);
    return SUCCESS;
}