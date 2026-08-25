#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *command;
    struct Node *next;
} Node;

void add_node(Node **head, const char *text)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_node->command = malloc(strlen(text) + 1);

    if (new_node->command == NULL)
    {
        perror("malloc");
        free(new_node);
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->command, text);

    new_node->next = *head;
    *head = new_node;
}

void print_list(Node *head)
{
    printf("\nCommands stored in linked list:\n");

    while (head != NULL)
    {
        printf("%s\n", head->command);
        head = head->next;
    }
}

void free_list(Node *head)
{
    Node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;

        free(temp->command);
        free(temp);
    }
}

int main()
{
    char *buffer;
    size_t size = 20;

    Node *head = NULL;

    buffer = malloc(size);

    if (buffer == NULL)
    {
        perror("malloc");
        return 1;
    }

    printf("Enter a command: ");

    if (fgets(buffer, size, stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        add_node(&head, buffer);
    }

    print_list(head);

    free(buffer);
    free_list(head);

    printf("\nMemory released successfully.\n");

    return 0;
}
