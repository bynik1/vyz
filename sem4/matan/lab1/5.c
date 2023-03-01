#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int count_numbers_in_line(char *line) {
  int count = 0;
  int in_number = 0;

  for (int i = 0; line[i]; i++) {
    if (isdigit(line[i]) && !in_number) {
      count++;
      in_number = 1;
    } else if (!isdigit(line[i])) {
      in_number = 0;
    }
  }

  return count;
}

int main(int argc, char *argv[]) {
  int i, j;
  if (argc != 2) {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  char line[1024];
  int total_count = 0;

  while (fgets(line, sizeof line, file)) {
    int count = count_numbers_in_line(line);
    printf("Line has %d numbers\n", count);
    total_count += count;
  }

  fclose(file);
  printf("Total number of numbers: %d\n", total_count);


  for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            fscanf(file, "%lf", &a[i][j]);
            printf("%d\n", fscanf(file, "%lf", &a[i][j]));
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%lf ", a[i][j]);
        }
        printf("\n");
    }

  return 0;
}