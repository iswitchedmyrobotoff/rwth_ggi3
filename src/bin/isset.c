#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int verbose = 0;

    if (argc < 2) {
        return 1;
    }

    if (argc > 2 && strcmp(argv[1], "-v") == 0) {
        verbose = 1;
    }

    if (argc > 2 + verbose) {
        printf("Only one variable is checkable at the same time!");
        return 2;
    }

    char *key = argv[1 + verbose];
    char *value = getenv(key);

    if (value != NULL && verbose == 1) {
        printf("%s is set with value = %s", key, value);
    } else if (value != NULL && verbose == 0){
        printf("Given variable '%s' is set.", key);
    } else {
        printf("Given variable '%s' is not set.", key);
    }

    return value == NULL;
}