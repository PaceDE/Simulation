#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void drunkard_walk(int steps) {
  int x = 0, y = 0;
  srand(time(NULL));
  for (int i = 0; i < steps; i++) {
    int direction = rand() % 4;
    switch (direction) {
      case 0:
        y++;
        break;
      case 1:
        y--;
        break;
      case 2:
        x++;
        break;
      case 3:
        x--;
        break;
    }
    printf("Step %d: (%d, %d)\n", i + 1, x, y);
  }
  printf("Final position: (%d, %d)\n", x, y);
}

int main() {
  int steps;
  printf("Enter the number of steps: ");
  scanf("%d", & steps);
  drunkard_walk(steps);
  return 0;
}