#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 100

int last_quote(char *s, char to_find) {
    int last_here = -1;
    int i = 0;
    while (s[i]) {
        if (s[i] == to_find)
            last_here = i;
        i++;
    }
    return last_here;
}

char **split_with_quotes(char *str) {
    char **result = (char **)malloc(MAX_TOKENS * sizeof(char *));
    int result_index = 0;
    int start_index = 0;
    int in_quotes = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\"' || str[i] == '\'') {
            int last_quote_index = last_quote(str + i + 1, str[i]) + i + 1;
            if (last_quote_index > i && str[last_quote_index - 1] != '\\') {
                in_quotes = !in_quotes;
                if (!in_quotes) {
                    // Split at the last quote of the same type
                    i = last_quote_index;
                }
            }
        } else if ((str[i] == ' ' || str[i] == '\t') && !in_quotes) {
            // Split if we encounter a space or tab and not inside quotes
            if (start_index < i) {
                result[result_index] = (char *)malloc((i - start_index + 1) * sizeof(char));
                for (int j = start_index; j < i; j++) {
                    result[result_index][j - start_index] = str[j];
                }
                result[result_index][i - start_index] = '\0'; // Null-terminate the string
                result_index++;
            }
            start_index = i + 1;
        }
    }

    // Handle the last token
    if (start_index < strlen(str)) {
        result[result_index] = (char *)malloc((strlen(str) - start_index + 1) * sizeof(char));
        strcpy(result[result_index], str + start_index);
        result_index++;
    }

    // Null-terminate the array
    result[result_index] = NULL;

    return result;
}

int main() {
    char *input1 = "echo ola braulio          santos ";
    char *input2 = "echo \" \"'$USER\"'\"42 \" ''\"  | << -1\"";
    
    char **result1 = split_with_quotes(input1);
    char **result2 = split_with_quotes(input2);

    // Print the results
    for (int i = 0; result1[i] != NULL; i++) {
        printf("%s\n", result1[i]);
        free(result1[i]); // Free memory allocated for each string
    }
    free(result1); // Free memory allocated for the array of strings
    printf("\n");

    for (int i = 0; result2[i] != NULL; i++) {
        printf("%s\n", result2[i]);
        free(result2[i]); // Free memory allocated for each string
    }
    free(result2); // Free memory allocated for the array of strings

    return 0;
}
