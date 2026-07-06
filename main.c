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

    print_filename_list(head);

    /* Hash Table Creation and storage of data */
    hash_t arr[HASH_SIZE];
    for(int i = 0; i < HASH_SIZE; i++)
    {
        arr[i].index = i;
        arr[i].main_link = NULL;
    }

    int option;
    do
    {
        printf("1. Create Database\n2. Search\n3. Display\n4. Update\n5. Exit.\nEnter the option: ");
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                create_database(arr, head);
                break;
            case 2:
                
                break;
            case 3:
                // display(arr);
                display_database(arr);
                break;
            case 4:
                
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Option. Try Again\n");
                break;
        }
    }while(option != 5);
    

    return SUCCESS;
}