#include <stdio.h>

const char *bit_rep[16] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

int main(){
    __uint8_t a,b,c;
    a = 10;
    b=255;
    c=a^b;
    printf("%s\n",  bit_rep[a]);
    printf("%s%s\n",  bit_rep[b >> 4],bit_rep[b & 0x0F]);
    printf("%s%s\n",  bit_rep[c >> 4],bit_rep[c & 0x0F]);
    return 0;
}