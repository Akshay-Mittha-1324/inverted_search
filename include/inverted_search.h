#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

/* Include the necessary header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Define the return values */
#define SUCCESS 0
#define FAILURE 1

/* Define the size of hash table */
#define HASH_SIZE 27

/* Define the structure for a node in the linked list */
typedef struct file_node
{
    char file_name[25];
    struct file_node *link;
}Slist;

/* Define the structure for Sub Node */
typedef struct sub_node
{
    char file_name[25];
    int word_count;
    struct sub_node *link;
}subnode_t;

/* Define the structure for Main Node */
typedef struct main_node
{
    int file_count;
    char word[25];
    struct sub_node *sub_link;
    struct main_node *link;
}mainnode_t;

/* Define the structure for Hash Table */
typedef struct _hash
{
    int index;
    mainnode_t *main_link;
}hash_t;

/* Validation Functions */
int validate_inputs_n_store_files(char *argv, Slist **head);

/* Operation Functions */
int insert_first(Slist **head, char *file_name);
int insert_last(hash_t *arr, char *word, char *file_name);

/* Helper Functions */
int file_exists(Slist *head, char *file_name);

/* Hash Functions */
int get_hash(char *word);

/* Display Functions */
void print_filename_list(Slist *head);

/* Database Functions */
int create_database(hash_t *arr, Slist *head);
void display_database(hash_t *arr);

#endif /* INVERTED_SEARCH_H */