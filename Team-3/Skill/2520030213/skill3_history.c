#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 10
#define MAX_INPUT 100

char history[MAX_HISTORY][MAX_INPUT];
int history_count = 0;

void add_history(char *command)
{
    if (history_count < MAX_HISTORY)
    {
        strcpy(history[history_count], command);
        history_count++;
    }
    else
    {
        for (int i = 0; i < MAX_HISTORY - 1; i++)
        {
            strcpy(history[i], history[i + 1]);
        }

        strcpy(history[MAX_HISTORY - 1], command);
    }
}

void show_history()
{
    printf("\nCommand History:\n");

    for (int i = 0; i < history_count; i++)
    {
        printf("%d  %s\n", i + 1, history[i]);
    }
}

int main()
{
    char input[MAX_INPUT];

    printf("Simple Shell History\n");
    printf("Type 'history' to display commands\n");
    printf("Type 'exit' to quit\n\n");

    while (1)
    {
        printf("shell> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
            break;

        if (strcmp(input, "history") == 0)
        {
            show_history();
            continue;
        }

        if (strlen(input) > 0)
        {
            add_history(input);
        }
    }

    return 0;
}
