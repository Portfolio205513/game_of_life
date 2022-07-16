#include <stdio.h>

int pole(int **field) {
  int j, i;
  for (int j = 0; j < WIDTH; j++) {
    for (int i = 0; i < LENGTH; i++)
      if (field[j][i] == 1)
        printf("*");
      else
        printf(" ");
    printf("\n");
  }
}