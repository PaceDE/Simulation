#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float numbers[20];
  float D, tabulatedD;
  float Dplusmax, Dminusmax;
  float Dplus[20], Dminus[20];
  float ratio[20], ratiominus[20];
  int i, j, n;
} KS;

void getdata(KS *ks) {
  printf("How many numbers?:\n");
  scanf("%d", &ks->n);
  printf("Enter %d numbers\n", ks->n);
  for (ks->i = 0; ks->i < ks->n; ks->i++) {
    scanf("%f", &ks->numbers[ks->i]);
  }
}

void BubbleSort(KS *ks) {
  int i, j;
  float temp;
  for (i = 0; i < ks->n - 1; i++) {
    for (j = 0; j < ks->n - i - 1; j++) {
      if (ks->numbers[j] > ks->numbers[j + 1]) {
        temp = ks->numbers[j];
        ks->numbers[j] = ks->numbers[j + 1];
        ks->numbers[j + 1] = temp;
      }
    }
  }
  printf("The numbers in ascending order are:\n");
  for (i = 0; i < ks->n; i++) {
    printf("%.2f ", ks->numbers[i]);
  }
  printf("\n");
}

void calculate(KS *ks) {
  for (ks->i = 0; ks->i < ks->n; ks->i++) {
    ks->j = ks->i + 1;
    ks->ratio[ks->i] = (float)ks->j / ks->n;
    ks->ratiominus[ks->i] = (float)ks->i / ks->n;
    ks->Dplus[ks->i] = ks->ratio[ks->i] - ks->numbers[ks->i];

    ks->Dminus[ks->i] = ks->numbers[ks->i] - ks->ratiominus[ks->i];
  }
}

void display(KS *ks) {
  int i;
  printf("\n\n%10s", "i");
  for (i = 1; i <= ks->n; i++) {
    printf("%10d", i);
  }
  printf("\n%10s", "R(i)");
  for (i = 0; i < ks->n; i++) {
    printf("%10.2f", ks->numbers[i]);
  }
  printf("\n%10s", "i/n");
  for (i = 0; i < ks->n; i++) {
    printf("%10.2f", ks->ratio[i]);
  }
  printf("\n%10s", "D+");
  for (i = 0; i < ks->n; i++) {
    printf("%10.2f", ks->Dplus[i]);
  }
  printf("\n%10s", "D-");
  for (i = 0; i < ks->n; i++) {
    printf("%10.2f", ks->Dminus[i]);
  }
  printf("\n");

  ks->Dplusmax = ks->Dplus[0];
  ks->Dminusmax = ks->Dminus[0];
  for (i = 1; i < ks->n; i++) {
    if (ks->Dplus[i] > ks->Dplusmax) {
      ks->Dplusmax = ks->Dplus[i];
    }
    if (ks->Dminus[i] > ks->Dminusmax) {
      ks->Dminusmax = ks->Dminus[i];
    }
  }
  printf("D+ max: %.2f\n", ks->Dplusmax);
  printf("D- max: %.2f\n", ks->Dminusmax);
  printf("D = max(%.2f, %.2f) =", ks->Dplusmax, ks->Dminusmax);
  if (ks->Dplusmax > ks->Dminusmax) {
    ks->D = ks->Dplusmax;
  } else {
    ks->D = ks->Dminusmax;
  }
  printf("%.2f\n", ks->D);
}

void conclusion(KS *ks) {
  printf("Enter the tabulated value:\n");
  scanf("%f", &ks->tabulatedD);

  if (ks->D < ks->tabulatedD) {
    printf("The test is accepted.\n");
  } else {
    printf("The test is rejected.\n");
  }
}

int main() {
  KS ks1;
  getdata(&ks1);
  BubbleSort(&ks1);
  calculate(&ks1);
  display(&ks1);
  conclusion(&ks1);
  return 0;
}