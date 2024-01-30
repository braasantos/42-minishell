#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Allocate a buffer to store the current working directory
    char cwd[1024];

    // Get the current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Print the current working directory
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return EXIT_FAILURE;
    }

    return 0;
}
