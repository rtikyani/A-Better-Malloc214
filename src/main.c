#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Error: Invalid number of arguments.\nUsage: malloc <test case>\n");
        return EXIT_FAILURE;
    }

    int choice = atoi(argv[1]);

    if (choice == 1) {

        char *p = malloc(100);
        free(p);

        p = malloc(100);
        free(p);

    } else if (choice == 2) {

        char *p = malloc(1);
        free(p);
        free(p);

    } else if (choice == 3) {

        char *p = malloc(100);
        free(p + 10);

    } else if (choice == 4) {

        char *test = malloc(500);
        char *test2 = malloc(900);

        strcat(test, "gfdsfhadfg");
        strcat(test2, "dsafsdgsasdfs");
        printf("%s %s\n", test, test2);

        free(test);
        free(test2);

    } else if (choice == 5) {

        char *not_enough_memory = malloc(20000);

    } else if (choice == 6) {

        int x;
        free(&x);

    } else {
        fprintf(stderr, "Error: Invalid test case.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}