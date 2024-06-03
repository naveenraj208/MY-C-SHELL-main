#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100

// Function prototypes
char** autocompleteGenerator(const char *text, int start, int end);
char* commandGenerator(const char *text, int state);

char* commands[MAX_COMMANDS] = {"ls", "cd", "mkdir", "rm", "cp", "mv", "touch", "grep", "cat", "pwd"};
int numCommands = 10;

void initializeReadline() {
    // Enable tab completion
    rl_attempted_completion_function = autocompleteGenerator;
}

char** autocompleteGenerator(const char *text, int start, int end) {
    char **matches = NULL;
    rl_attempted_completion_over = 1; // Signal readline that we have finished generating completions

    // If this is the first word, attempt command autocompletion
    if (start == 0) {
        matches = rl_completion_matches(text, commandGenerator);
    }

    return matches;
}

char* commandGenerator(const char *text, int state) {
    static int listIndex, len;
    char *name;

    // If this is a new word to complete, initialize listIndex and len
    if (!state) {
        listIndex = 0;
        len = strlen(text);
    }

    // Iterate through commands to find matches
    while (listIndex < numCommands) {
        name = commands[listIndex];
        listIndex++;

        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }

    // No more matches
    return NULL;
}

int main() {
    initializeReadline();

    // Main loop
    char *input;
    while ((input = readline("CustomShell> ")) != NULL) {
        if (input[0] != '\0') {
            add_history(input);
        }

        // Process the input
        printf("You entered: %s\n", input);

        free(input);
    }

    return 0;
}
