#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

/* Include the necessary header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define the return values */
#define SUCCESS 0
#define FAILURE 1

/* Define the structure for a node in the linked list */
typedef struct file_node
{
    char *file_name;
    struct file_node *link;
}Slist;


/* Validation Functions */
int validate_inputs_n_store_files(char *argv, Slist **head);

/* Operation Functions */
int insert_first(Slist **head, char *file_name);

/* Helper Functions */
int file_exists(Slist *head, char *file_name);

void print_list(Slist *head);

#endif /* INVERTED_SEARCH_H */