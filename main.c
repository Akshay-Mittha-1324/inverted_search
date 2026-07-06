#include "include/inverted_search.h"

int main(int argc, char *argv[])
{
    Slist *head = NULL;
    if(argc < 2)
    {
        printf("Usage: ./inverted_search file1 file2 ...\n");
        return FAILURE;
    }

    /* Validate inputs and store files in linked list */
    printf("Validating Files...\n");
    for(int i  = 1; i < argc; i++)
    {
        if(validate_inputs_n_store_files(argv[i], &head) == FAILURE)
            continue;
        
        printf("File %s is valid and stored in the List\n", argv[i]);
    }
    if(head == NULL)
    {
        printf("No valid files to search\n");
        return FAILURE;
    }

    print_list(head);


    return SUCCESS;
}