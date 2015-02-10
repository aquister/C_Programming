#include "myheader.h"

char *readUserInput() {
    char tempStringBuffer[4096];
    fgets(tempStringBuffer, 4096, stdin);
    size_t stringSize = strnlen(tempStringBuffer, 4096);
    char *finalString = malloc(stringSize);
    strncpy(finalString, tempStringBuffer, stringSize);
    return finalString;
}

int func1(void *arg) {
    return 1;
}
int func2(void *arg) {
    return 2;
}
void function(int *arg, int(*func)(void *)) {

    printf("%d\n", func(arg));
}


int main(int argc, const char *argv[]) {

    /*
    char c1 = 'a';
    char *c2 = &c1;
    char **c3 = &c2;
    **c3 = 'b';
    char c4 = **c3;
    printf("%c\n", c4);
    */

    /*
    int a = 3;
    int *x = &a;
    function(x, func2);
    */

    long t = 1L;
    void *ptr = (void *) t;
    printf("%ld\n", (long)ptr);


    /*
    char *chPtr1;
    char *chPtr2;
    chPtr1 = readUserInput();
    chPtr2 = readUserInput();

    void *ptr = chPtr1;

    printf("\nchPtr1 %d %s", strlen(chPtr1), chPtr1);
    printf("\nchPtr2 %d %s", strlen(chPtr2), chPtr2);

    printf("\n%p \n%p  \n\n", &chPtr1, &chPtr2);

    free(chPtr1);
    free(chPtr2);
    */

    return EXIT_SUCCESS;
}
