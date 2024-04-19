#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LEN 256

int main() {
    char cmd[MAX_CMD_LEN];

    while (1) {
        printf("my_shell> ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            break;
        }

        // Remove trailing newline character
        cmd[strcspn(cmd, "\n")] = 0;

        if (strcmp(cmd, "exit") == 0) {
            break;
        }

        system(cmd);
    }

    return 0;
}