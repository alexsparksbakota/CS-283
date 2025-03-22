#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

char *trim_whitespace(char *str) {
    while (isspace((unsigned char)*str)) str++;
    if (*str == '\0') return str;

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';

    return str;
}

char *find_delim(char *str, char delim) {
    while (*str != '\0') {
        if (*str == delim) {
            *str = '\0';
            return str + 1;
        }
        str++;
    }
    return NULL;
}

int build_cmd_list(char *cmd_line, command_list_t *clist) {
    clist->num = 0;
    memset(clist->commands, 0, sizeof(clist->commands));

    char *cursor = cmd_line;
    char *next;

    while (cursor && *cursor != '\0') {
        if (clist->num >= CMD_MAX) {
            return ERR_TOO_MANY_COMMANDS;
        }

        next = find_delim(cursor, '|');
        char *trimmed = trim_whitespace(cursor);

        if (strlen(trimmed) == 0) {
            cursor = next;
            continue;
        }

        char *exe_token = strtok(trimmed, " ");
        if (!exe_token) {
            return WARN_NO_CMDS;
        }

        if (strlen(exe_token) >= EXE_MAX) {
            return ERR_CMD_OR_ARGS_TOO_BIG;
        }
        strcpy(clist->commands[clist->num].exe, exe_token);

        char *args_token = strtok(NULL, "");
        if (args_token) {
            args_token = trim_whitespace(args_token);
            if (strlen(args_token) >= ARG_MAX) {
                return ERR_CMD_OR_ARGS_TOO_BIG;
            }
            strcpy(clist->commands[clist->num].args, args_token);
        }

        clist->num++;
        cursor = next;
    }

    if (clist->num == 0) {
        return WARN_NO_CMDS;
    }

    return OK;
}
