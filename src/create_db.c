#include "../include/inverted_search.h"

/* Function to create database */
int create_database(hash_t *arr, Slist *head)
{
    FILE *fp;
    char word[25];
    while(head)
    {
        /* Open the File */
        fp = fopen(head -> file_name, "r");
        if(fp == NULL)
        {
            perror("ERROR: ");
            return FAILURE;
        }
        /* Loop until the end of file and word by word separated by space */
        
        while(fscanf(fp, "%s", word) != EOF)
        {
            /* Loop to Strip Punctuation Marks */
            int len = strlen(word);
            if(len > 0 && !isalnum(word[len - 1]))
                word[len - 1] = '\0';
            /* Loop to Convert Each Char to Lower Case */
            for(int i = 0; word[i]; i++)
                word[i] = tolower(word[i]);

            /* Function to Insert */
            insert_last(arr, word, head -> file_name);
        }
        head = head -> link;
        fclose(fp);
    }
    return SUCCESS;
}

int insert_last(hash_t *arr, char *word, char *file_name)
{
    /* Get the hash index from the function */
    int idx = get_hash(word);

    /* Check if the hash table index is NULL */
    if(arr[idx].main_link == NULL)
    {
        mainnode_t *m_node = (mainnode_t *) malloc(sizeof(mainnode_t));
        subnode_t *s_node = (subnode_t *) malloc(sizeof(subnode_t));
        strcpy(m_node -> word, word);
        strcpy(s_node -> file_name, file_name);
        m_node -> file_count = 1;
        m_node -> sub_link = s_node;
        m_node -> link = NULL;
        s_node -> word_count = 1;
        s_node -> link = NULL;
        arr[idx].main_link = m_node;
    }
    /* Hash Table index has some node */
    else
    {
        /* Loop through each node to check if the word is present or not */
        mainnode_t *temp = arr[idx].main_link;
        mainnode_t *prev_m = NULL; // To keep track of the previous node and to make the links
        while(temp)
        {
            if(strcmp(temp -> word, word) == 0)
                break;
            prev_m = temp;
            temp = temp -> link;
        }
        /* Word is not Present in the list */
        if(temp == NULL)
        {
            mainnode_t *m_node = (mainnode_t *) malloc(sizeof(mainnode_t));
            subnode_t *s_node = (subnode_t *) malloc(sizeof(subnode_t));
            strcpy(m_node ->word, word);
            strcpy(s_node -> file_name, file_name);
            m_node ->link = NULL;
            m_node ->file_count = 1;
            m_node ->sub_link = s_node;
            s_node -> word_count = 1;
            s_node ->link = NULL;
            prev_m -> link = m_node;
        }
        /* Word is present in the Node */
        else
        {
            /* Check the filenames if same increment word count else create subnode */
            subnode_t *file = temp -> sub_link;
            subnode_t *prev_f = NULL; // To keep track of the previous node and to make the links
            while(file)
            {
                if(strcmp(file -> file_name, file_name) == 0)
                    break;
                prev_f = file;
                file = file -> link;
            }
            /* File name found */
            if(file != NULL)
                file -> word_count += 1;
            
            /* File name not found */
            else
            {
                subnode_t *s_node = (subnode_t *) malloc(sizeof(subnode_t));
                strcpy(s_node -> file_name, file_name);
                s_node -> word_count = 1;
                s_node -> link = NULL;
                temp -> file_count += 1;
                prev_f -> link = s_node;
            }
        }
    }
    return SUCCESS;
}