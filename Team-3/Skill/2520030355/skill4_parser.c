#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 200
#define MAX_TOKENS 50

typedef struct Node
{
    char value[50];
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(const char *value)
{
    Node *node = malloc(sizeof(Node));

    if (node == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(node->value, value);
    node->left = NULL;
    node->right = NULL;

    return node;
}

void print_tree(Node *root, int level)
{
    if (root == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("  ");

    printf("|-- %s\n", root->value);

    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}

void free_tree(Node *root)
{
    if (root == NULL)
        return;

    free_tree(root->left);
    free_tree(root->right);

    free(root);
}

int main()
{
    char input[MAX_INPUT];
    char *tokens[MAX_TOKENS];
    int count = 0;

    printf("Enter command: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
        return 1;

    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0)
    {
        printf("Error: Empty command.\n");
        return 1;
    }

    char *token = strtok(input, " \t");

    while (token != NULL && count < MAX_TOKENS)
    {
        tokens[count++] = token;
        token = strtok(NULL, " \t");
    }

    if (count == 0)
    {
        printf("Error: No tokens found.\n");
        return 1;
    }

    Node *root = create_node("COMMAND");

    root->left = create_node(tokens[0]);

    if (count > 1)
    {
        root->right = create_node("ARGUMENTS");

        Node *current = root->right;

        for (int i = 1; i < count; i++)
        {
            current->left = create_node(tokens[i]);

            if (i < count - 1)
            {
                current->right = create_node("NEXT");
                current = current->right;
            }
        }
    }

    printf("\nParse Tree:\n");
    print_tree(root, 0);

    free_tree(root);

    return 0;
}
