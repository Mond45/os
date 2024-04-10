#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int tokenize(char *string, char *delimiters, char ***arrayOfTokens);

int main()
{
    char delim[] = " \t\n";

    while (1)
    {
        char **tokens;
        char string[256];
        int numtokens;

        // read and tokenize input
        printf("mysh >");
        fgets(string, 256, stdin);
        numtokens = tokenize(string, delim, &tokens);

        // if no tokens, continue
        if (numtokens == 0)
        {
            continue;
        }
        // if input is "exit", exit the shell
        if (numtokens == 1 && strcmp(tokens[0], "exit") == 0)
        {
            return 0;
        }

        // fork and execute the command
        pid_t pid;
        pid = fork();
        if (pid < 0)
        {
            printf("Error : cannot fork\n");
            exit(1);
        }
        else if (pid == 0)
        {
            execvp(tokens[0], tokens);
        }
        else
        {
            wait(NULL);
        }
    }
}

int tokenize(char *string, char *delimiters, char ***arrayOfTokens)
{
    char *token;
    int numtokens;
    int i;
    /* skip the beginning delimiters */
    string += strspn(string, delimiters);
    if ((token = malloc(strlen(string) + 1)) == NULL)
        return -1;
    /* count tokens */
    strcpy(token, string);
    numtokens = 0;
    if (strtok(token, delimiters) != NULL)
        for (numtokens = 1; strtok(NULL, delimiters) != NULL;
             numtokens++)
            ;
    /* create array of pointers to tokens */
    if ((*arrayOfTokens = malloc((numtokens + 1) * sizeof(char *))) ==
        NULL)
    {
        free(token);
        return -1;
    }
    /* fill pointers to tokens into the array */
    if (numtokens == 0)
        free(token);
    else
    {
        strcpy(token, string);
        (*arrayOfTokens)[0] = strtok(token, delimiters);
        for (i = 1; i < numtokens; i++)
            (*arrayOfTokens)[i] = strtok(NULL, delimiters);
        (*arrayOfTokens)[numtokens] = NULL;
    }
    return numtokens;
}