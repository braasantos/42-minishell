#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
    const char* input = "echo \"aspas -> \'\"";
    int size;
    char** tokens = parseString(input, &size);

    printf("Array of Arrays:\n");
    for (int i = 0; i < size; ++i) {
        printf("String %d: %s\n", i + 1, tokens[i]);
    }

    freeTokens(tokens, size);
    return 0;
}
