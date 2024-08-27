#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int midSquare(int seed, int numDigits)
{
    int squared = seed * seed;
    int squaredDigits = (int)log10(squared) + 1;
    int leadingZeros = (numDigits * 2) - squaredDigits;
    char squaredStr[20];
    snprintf(squaredStr, sizeof(squaredStr), "%0*d", leadingZeros + squaredDigits, squared);
    int start = (leadingZeros + squaredDigits) / 2 - (numDigits / 2);
    char midDigits[10];
    strncpy(midDigits, squaredStr + start, numDigits);
    midDigits[numDigits] = '\0'; // Null-terminate the string
    return atoi(midDigits);
}
int main()
{
    int seed, numDigits, count;
    printf("Enter initial seed: ");
    scanf("%d", &seed);
    printf("Enter number of digits to extract: ");
    scanf("%d", &numDigits);
    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &count);
    printf("Generated random numbers:\n");
    for (int i = 0; i < count; i++)
    {
        seed = midSquare(seed, numDigits);
        printf("%d\n", seed);
    }
}
