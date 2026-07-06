#include "../include/inverted_search.h"

int validate_inputs_n_store_files(char *argv, Slist **head)
{
    FILE *fp;
    
    /* File Validation */
    /* Checking if the file extension is .txt at the end of the string */
    int len = strlen(argv);
    if(len < 4)
        return FAILURE;

    if(strcmp(argv + (len - 4), ".txt") != 0)
    {
        printf("File %s is Not a Text File\n",argv);
        return FAILURE;
    }

    /* Checking if the file is present in the directory or not */
    fp = fopen(argv, "r");
    if(fp == NULL)
    {
        printf("File %s does not exists in Current Directory\n", argv);
        return FAILURE;
    }

    /* Checking if the file is empty or not */
    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0)
    {
        printf("File %s has no Contents\n", argv);
        return FAILURE;
    }

    rewind(fp);

    /* Inserting the file name in the list */
    if(file_exists(*head, argv) == FAILURE)
    {
        printf("File %s is already in the List\n", argv);
        return FAILURE;
    }
    
    if(insert_first(head, argv) == FAILURE)
    {
        printf("File %s insertion Failed\n", argv);
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

int insert_first(Slist **head, char *file_name)
{
    Slist *new_node = (Slist *) malloc(sizeof(Slist));
    if(new_node == NULL)
        return FAILURE;

    /* Copying the file name to the new node */
    strcpy(new_node -> file_name, file_name);
    
    if(*head == NULL)
    {
        *head = new_node;
        new_node -> link = NULL;
        return SUCCESS;
    }

    /* Inserting the new node at the beginning of the list */
    new_node -> link = *head;
    *head = new_node;

    return SUCCESS;
}

void print_filename_list(Slist *head)
{
    while(head)
    {
        printf("%s\n",head -> file_name);
        head = head -> link;
    }
    return;
}

int get_hash(char *word)
{
    int hash_idx;
    /* Handling the Upper Case and Special Character Cases */
    if(word[0] >= 'A' && word[0] <= 'Z')
        hash_idx = (word[0] + 32) - 'a';
    else if(!(word[0] >= 'a' && word[0] <= 'z')) 
        hash_idx = 26;
    else
        hash_idx = word[0] - 'a';
    
    return hash_idx;
}
