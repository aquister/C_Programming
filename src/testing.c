#include "myheader.h"

void exit_prog(int sig) {
    printf("\nInterrupt detected... Exiting...\n");
    exit(EXIT_SUCCESS);
}

void bitManipTest() {
    byte bit_fld = 0;

//    bit_fld |= 1 << 3;      // set 3rd bit
//    bit_fld &= ~(1 << 4);   // clear 4th bit
//    bit_fld ^= 1 << 5;      // toggle 5th bit

    for (size_t i = 0; i < sizeof(byte) * 8; i++) {
        printf("Bit #%02u: ", i);
        if (bit_fld & (1 << i)) printf("TRUE\n");
        else printf("FALSE\n");
    }
}


int main(int argc, const char *argv[]) {
    (void) signal(SIGINT, exit_prog);
    
    printf("Hello World\n");
    printf("argc = %d\n", argc);
    printf("argv[0] = %s\n", argv[0]);

    printf("size_t = %d bit\n", sizeof(size_t) * 8);
    printf("uint8_t = %d bit\n", sizeof(uint8_t) * 8);
    
    bitManipTest();

    printf("\n-------- END ---------\n"); 
    while(true) sleep(1);
    exit_prog(2);
    return EXIT_SUCCESS;
}

