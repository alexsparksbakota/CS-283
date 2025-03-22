#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dshlib.h"

#define PROMPT "dsh> "

int main(void) {
    char cmd_buff[SH_CMD_MAX];  // Buffer to store user input
    int rc = 0;                 // Return code from command processing
    command_list_t clist;       // Holds parsed commands

    while (1) {
        // Display the shell prompt
        printf("%s", PROMPT);
        fflush(stdout);

        // Read input from the user
        if (fgets(cmd_buff, SH_CMD_MAX, stdin) == NULL) {
            printf("\n");
            break;
        }

        // Remove trailing newline character
        size_t len = strlen(cmd_buff);
        if (len > 0 && cmd_buff[len - 1] == '\n') {
            cmd_buff[len - 1] = '\0';
        }

        // Exit if the user enters "exit"
        if (strcmp(cmd_buff, "exit") == 0) {
            break;
        }

        // Special case for "dragon"
        if (strcmp(cmd_buff, "dragon") == 0) {
            printf("[DRAGON for extra credit would print here]\n");
            continue;
        }

        // Check for empty input
        if (strlen(cmd_buff) == 0) {
            printf("warning: no commands provided\n");
            continue;
        }

        // Parse the input into a command list
        rc = build_cmd_list(cmd_buff, &clist);

        if (rc == WARN_NO_CMDS) {
            printf("warning: no commands provided\n");
            continue;
        } else if (rc == ERR_TOO_MANY_COMMANDS) {
            printf("error: piping limited to 8 commands\n");
            continue;
        } else if (rc == ERR_CMD_OR_ARGS_TOO_BIG) {
            printf("error: command or arguments too large\n");
            continue;
        } else if (rc != OK) {
            printf("error: unknown error occurred\n");
            continue;
        }

        // Print the parsed command list
        printf("PARSED COMMAND LINE - TOTAL COMMANDS %d\n", clist.num);
        for (int i = 0; i < clist.num; i++) {
            if (strlen(clist.commands[i].args) > 0) {
                printf("<%d> %s [%s]\n", i + 1, clist.commands[i].exe, clist.commands[i].args);
            } else {
                printf("<%d> %s\n", i + 1, clist.commands[i].exe);
            }
        }
    }

    return EXIT_SUCCESS;
}
