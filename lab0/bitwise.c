#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BIT(n) (1 << (n))

char *byte2bin(uint8_t n, char *binstr)
{
    // one element per bit (0/1)
    uint8_t binary[8];

    int i = 0;
    for (i = 0; i < 8; i++)
    {
        binary[i] = n % 2;
        n = n / 2;
    }

    // printing binary array in reverse order
    for (int j = 7, k = 0; j >= 0; j--, k++)
        sprintf(binstr + k, "%d", binary[j]);

    return binstr;
}

void print_usage(char *name)
{
    printf("Usage: %s <action> <byte> <bit no>\n", name);
    printf("\tWhere: <action> one of 'h'|'l'|'r'|'s'|'t'\n"
           "\t\t <byte> 8-bit integer in hexadecimal\n"
           "\t\t <bit no> of bit to operate on\n");
}

int main(int argc, char *argv[])
{
    char a;          // action: 'h', 'l', 'r', 's', 't'
    unsigned long n; // value to convert must be smaller than 256
    int bit;         // bit to operate on: must be between 0 an 7

    { // Validate command line arguments
        if (argc != 4)
        {
            print_usage(argv[0]);
            return 1;
        }

        // In C a string is essentially a null terminated character array
        a = argv[1][0];
        if (a != 'h' && a != 'l' && a != 'r' && a != 's' && a != 't')
        {
            print_usage(argv[0]);
            printf("\t<action> must be one of 'h'|'l'|'r'|'s'|'t'\n");
            return 1;
        }

        // We are expecting the argument to be an hexadecimal string
        n = strtoul(argv[2], NULL, 16);
        if (n < 0 || n > (1 << 8) - 1)
        {
            print_usage(argv[0]);
            printf("\t<byte> must be non-negative and smaller than 256\n");
            return 1;
        }

        bit = atoi(argv[3]);
        if (bit < 0 || bit > 7)
        {
            print_usage(argv[0]);
            printf("\t<bit no> must be between 0 and 7\n");
            return 1;
        }
    } // End of command line arguments validation

    char binary[9]; // array for binary representation of n,
    //  remember that in C strings are terminated with a 0
    byte2bin(n, binary);
    // print arguments after validation
    printf("Arguments:\n");
    printf("\tAction - %c", a);
    printf("\n\tValue - ");
    for (int i = 0; i < 9; i++){
        printf("%c", binary[i]);
    }
    printf("\n\tBit to check - %d", bit);
    printf("\n");
    // treat
    if (a == 'h'){
        uint8_t mask = BIT(bit);
        if (mask & binary[bit])
            printf("True\n");
        else
            printf("False\n");
    }
    else if (a == 'l'){
        uint8_t mask = BIT(bit);
        if (mask & binary[bit])
            printf("False\n");
        else
            printf("True\n");
    }
    else if (a == 's'){
        uint8_t mask = BIT(bit);
        binary[bit] = binary[bit] | 1;
        printf("The bit in the position %d was set to 1.\n", bit);
        printf("Value after change: ");
        for (int i = 0; i < 9; i++){
            printf("%c", binary[i]);
        }
        printf("\n");
    }
    else if (a == 'r'){
        uint8_t mask = BIT(bit);
        binary[bit] = binary[bit] & 0;
        printf("The bit in the position %d was reseted to 0.\n", bit);
        printf("Value after change: ");
        for (int i = 0; i < 9; i++){
            printf("%c", binary[i]);
        }
        printf("\n");
    }
    else if (a == 't'){
        uint8_t mask = BIT(bit);
        binary[bit] = binary[bit] ^ 1;
        printf("The bit in the position %d was toggled.\n", bit);
        printf("Value after change: ");
        for (int i = 0; i < 9; i++){
            printf("%c", binary[i]);
        }
        printf("\n");
    }
    return 0;
}