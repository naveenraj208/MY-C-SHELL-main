#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ALIAS_LENGTH 100
#define MAX_COMMAND_LENGTH 100

// Structure to store aliases
typedef struct {
    char alias[MAX_ALIAS_LENGTH];
    char command[MAX_COMMAND_LENGTH];
} Alias;

Alias aliases[10]; 

int aliasCount = 0; 


void addAlias(char *alias, char *command) {
    if (aliasCount < 10) {
        strcpy(aliases[aliasCount].alias, alias);
        strcpy(aliases[aliasCount].command, command);
        aliasCount++;
    } else {
        printf("Maximum number of aliases reached.\n");
    }
}

// Function to execute a command, resolving aliases if applicable
void executeCommand(char *command) {
    // Check if the command is an alias
    for (int i = 0; i < aliasCount; i++) {
        if (strcmp(command, aliases[i].alias) == 0) {
            strcpy(command, aliases[i].command);
            break;
        }
    }
    
    // Execute the command
    system(command);
}

int main() {
    char input[MAX_INPUT_LENGTH];
    
    
    addAlias("naveen", "ls");
    addAlias("utpal", "xeyes");
    addAlias("sajithamaam", "display");
    addAlias("utpal", "display");
     addAlias("BUNAVEENRAJ","discover");
    // Main shell loop
    while (1) {
        printf("CustomShell> ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        
        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;
        
        // Exit shell if "exit" command is entered
        if (strcmp(input, "exit") == 0) {
            break;
        }
        
        // Execute command, resolving aliases if applicable
        executeCommand(input);
    }
    
    return 0;
}
