#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 200
#define MAX_TOKENS 50

int main()
{
    char input[MAX_INPUT];
    char *tokens[MAX_TOKENS];
    int count = 0;

    printf("Enter a command: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    char *token = strtok(input, " \t");

    while (token != NULL && count < MAX_TOKENS)
    {
        tokens[count] = token;
        count++;

        token = strtok(NULL, " \t");
    }

    printf("\nTokens:\n");

    for (int i = 0; i < count; i++)
    {
        printf("Token %d: %s\n", i + 1, tokens[i]);
    }

    printf("\nTotal tokens: %d\n", count);

    return 0;
}
