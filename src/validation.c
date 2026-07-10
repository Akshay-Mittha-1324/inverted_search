/**
 * @file    validation.c
 * @author  Akshay Ravikiran Mittha
 * @date    09/07/2026
 * @brief   Validates the input arguments and stores the file names in the linked list.
 * 
 * @details 
 * Functions Performed:
 * - validate_inputs_n_store_files() : Validates the input arguments and stores the file names in the linked list.
 * - file_exists() : Checks if the file name exists in the linked list.
 * - insert_at_last() : Inserts the file name at the end of the linked list.
 * - get_hash() : Returns the hash index for the given character.
 */

#include "../include/inverted_search.h"

/* Function to validate the input arguments and store the file names in the linked list */
int validate_inputs_n_store_files(char *argv, Slist **head)
{
    /* Checking if the file extension is .txt at the end of the string */
    int len = strlen(argv);
    if(len < 4)
        return FAILURE;

    if(strcmp(argv + (len - 4), ".txt") != 0)
    {
        printf(RED "\nINFO: %s => This is not a Text File\n" RESET,argv);
        return FAILURE;
    }

    /* Checking if the file is present in the directory or not */
    FILE *fp = fopen(argv, "r");
    if(fp == NULL)
    {
        printf(RED "\nINFO: %s File is not exist in current Directory\n" RESET, argv);
        return FAILURE;
    }

    /* Checking if the file is empty or not */
    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0)
    {
        printf(RED "\nINFO: %s File is Empty File\n" RESET, argv);
        return FAILURE;
    }

    rewind(fp);

    /* Inserting the file name in the list */
    if(file_exists(*head, argv) == FAILURE)
    {
        printf(RED "\nINFO: %s File is repeated, it will not be stored into the List\n" RESET, argv);
        return FAILURE;
    }
    
    if(insert_at_last(head, argv) == FAILURE)
    {
        printf(RED "\nINFO: %s File Insertion Failed\n" RESET, argv);
        return FAILURE;
    }

    /* Closing the file */
    fclose(fp);
    return SUCCESS;
}

/* Function to check if the file already exists in the list */
int file_exists(Slist *head, char *file_name)
{
    while(head)
    {
        if(strcmp((head -> file_name), file_name) == 0)
            return FAILURE;
        head = head -> link;
    }
    return SUCCESS;
}

int insert_at_last(Slist **head, char *file_name)
{
    Slist *new_node = (Slist *) malloc(sizeof(Slist));
    if(new_node == NULL)
        return FAILURE;

    /* Copying the file name to the new node */
    strcpy(new_node -> file_name, file_name);
    new_node -> link = NULL;

    if(*head == NULL)
    {
        *head = new_node;
        return SUCCESS;
    }

    /* Inserting the new node at the last of the list */
    Slist *temp = *head;
    while(temp -> link)
        temp = temp -> link;

    temp -> link = new_node;

    return SUCCESS;
}

void print_filename_list(Slist *head)
{
    printf(GREEN "\nList of Files:\n" RESET);
    while(head)
    {
        printf(GREEN "%s -> " RESET, head -> file_name);
        head = head -> link;
    }
    printf(GREEN "NULL\n" RESET);
    return;
}

int get_hash(char ch)
{
    int hash_idx;
    /* Handling the Upper Case and Special Character Cases */
    if(!(ch >= 'a' && ch <= 'z'))
        hash_idx = 26;
    else
        hash_idx = ch - 'a';
    
    return hash_idx;
}