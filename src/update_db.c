/**
 * @file    update_db.c
 * @author  Akshay Ravikiran Mittha
 * @date    09/07/2026
 * @brief   Updates the database.
 * 
 * @details 
 * Functions Performed:
 * - update_database(): Updates the database.
 * - delete_file_from_list(): Deletes the file from the list.
 */

#include "../include/inverted_search.h"

/* Function to update database */
int update_database(hash_t *arr, Slist **head, char *database_file)
{
    /* Check if database is already created before update */
    for(int i = 0; i < HASH_SIZE; i++)
    {
        /* If database is already created, return failure */
        if(arr[i].main_link != NULL)
        {
            printf(RED "\nINFO: Database is Already Created Cannot Update\n" RESET);
            return FAILURE;
        }
    }

    /* Check if the file is text file */
    int len = strlen(database_file);
    if(strcmp(database_file + (len - 4), ".txt") != 0)
    {
        printf(RED "\nINFO: %s Database File is not a Text File\n" RESET, database_file);
        return FAILURE;
    }

    /* Open the file for further operation */
    FILE *fp = fopen(database_file, "r");
    if(fp == NULL)
    {
        /* Print the error message */
        perror(RED "\nINFO: ERROR: " RESET);
        printf("\n");
        return FAILURE;
    }

    /* Check if the file is a Database File Check first and last char as # */
    if(fgetc(fp) != '#')
    {
        fseek(fp, -1, SEEK_END);
        if(fgetc(fp) != '#')
        {
            printf(RED "\nINFO: %s File is not a Database File\n" RESET, database_file);
            return FAILURE;
        }
    }
    rewind(fp);

    char word[30], file_name[30], end_hash;
    int word_count, file_count;
    short int index;
    /* Reading the Database File and Inserting into the Hash Table */
    while(fscanf(fp, "#%hd;%[^;];%d;", &index, word, &file_count) == 3)
    {
        /* Allocate memory for the main node */
        mainnode_t *m_node = (mainnode_t *) malloc(sizeof(mainnode_t));
        m_node -> file_count = file_count;
        strcpy(m_node -> word, word);
        m_node -> link = NULL;
        m_node -> sub_link = NULL;
        /* Inserting the main node into the Hash Table */
        if(arr[index].main_link == NULL)
            arr[index].main_link = m_node;
        else
        {
            /* Finding the last node of the hash table */
            mainnode_t *main_temp = arr[index].main_link;
            while(main_temp -> link)
                main_temp = main_temp -> link;
            /* Inserting the main node at the last of the hash table */
            main_temp -> link = m_node;
        }
        
        /* Reading the subnodes of the current node */
        for(int i = 0; i < file_count; i++)
        {
            /* Reading the file name and word count */
            fscanf(fp, "%[^;];%d;", file_name, &word_count);
            /* Delete the file from the Slinked list */
            delete_file_from_list(&(*head), file_name);
            /* Allocate memory for the sub node */
            subnode_t *s_node = (subnode_t *) malloc(sizeof(subnode_t));
            strcpy(s_node -> file_name, file_name);
            s_node -> word_count = word_count;
            s_node -> link = NULL;
            /* Inserting the sub node into the Hash Table */
            if(m_node -> sub_link == NULL)
                m_node -> sub_link = s_node;
            else
            {
                /* Finding the last node of the sub node */
                subnode_t *temp = m_node -> sub_link;
                while(temp -> link != NULL)
                    temp = temp -> link;
                /* Inserting the sub node at the last of the hash table */
                temp -> link = s_node;
            }
        }
        /* Reading the end hash */
        fscanf(fp, "%c\n", &end_hash);
    }
    /* Display the Database */
    display_database(arr);

    /* Close the database file */
    fclose(fp);
    return SUCCESS;    
}

void delete_file_from_list(Slist **head, char *file_name)
{
    /* Check if the Slist is empty */
    if(*head == NULL)
        return;
    /* Check if the filename exists in the Slist */
    Slist *temp = *head;
    /* Check if the filename exists in the Slist */
    if(strcmp((*head) -> file_name, file_name) == 0)
    {
        /* Deleting the file from the Slist */
        *head = (*head) -> link;
        free(temp);
        return;
    }
    /* Traverse to find the File name */
    Slist *prev = NULL;
    while(temp)
    {
        /* Delete the file if it exists in the Slist */
        if(strcmp(temp -> file_name, file_name) == 0)
        {
            prev -> link = temp -> link;
            free(temp);
            return;
        }
        /* Move to the next node */
        prev = temp;
        temp = temp -> link;
    }
    /* Return if the file is not found */
    return;
}