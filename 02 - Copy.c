#include <stdio.h>
#include <stdlib.h>

struct LCG {
    int Xn; 
    int a, c, m; 
};
void initLCG(struct LCG *lcg, int seed, int multiplier, int increment, int modulus);
int mixedLCG(struct LCG *lcg);
int additiveLCG(struct LCG *lcg);
int multiplicativeLCG(struct LCG *lcg);
void generateSequence(struct LCG *lcg, int option);
int main() {
    int seed, a, c, m;
    printf("Enter seed (X0): ");
    scanf("%d", &seed);
    printf("Enter multiplier (a): ");
    scanf("%d", &a);
    printf("Enter increment (c): ");
    scanf("%d", &c);
    printf("Enter modulus (m): ");
    scanf("%d", &m);
    struct LCG lcg;
    initLCG(&lcg, seed, a, c, m);
    while (1) {
        int option;
        printf("Choose an option:\n");
        printf("1. Mixed LCG\n");
        printf("2. Additive LCG\n");
        printf("3. Multiplicative LCG\n");
        printf("4. Exit\n");
        scanf("%d", &option);
        if (option == 4) {
            printf("Exiting program.\n");
            break;
        }
        generateSequence(&lcg, option);
    }
    return 0;
}
void initLCG(struct LCG *lcg, int seed, int multiplier, int increment, int modulus) {
    lcg->Xn = seed;
    lcg->a = multiplier;
    lcg->c = increment;
    lcg->m = modulus;
}
int mixedLCG(struct LCG *lcg) {
    lcg->Xn = (lcg->a * lcg->Xn + lcg->c) % lcg->m;
    return lcg->Xn;
}
int additiveLCG(struct LCG *lcg) {
    lcg->Xn = (lcg->Xn + lcg->c) % lcg->m;
    return lcg->Xn;
}

int multiplicativeLCG(struct LCG *lcg) {
    lcg->Xn = (lcg->a * lcg->Xn) % lcg->m;
    return lcg->Xn;
}
void generateSequence(struct LCG *lcg, int option) {
    printf("Generating sequence:\n");
    int randomNumber;
    int generatedNumbers[1000] = {0};
    int count = 0;
    while (1) {
        switch (option) {
            case 1:
                randomNumber = mixedLCG(lcg);
                break;
            case 2:
                randomNumber = additiveLCG(lcg);
                break;
            case 3:
                randomNumber = multiplicativeLCG(lcg);
                break;
            default:
                printf("Invalid option!\n");
                return;
        }
        printf("%d ", randomNumber);

        for (int i = 0; i < count; i++) {
            if (generatedNumbers[i] == randomNumber) {
                printf("\nRepeated number generated.\n\n");
                return; 
            }
        }
        generatedNumbers[count++] = randomNumber;
    }
}