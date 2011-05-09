#include  <stdlib.h>
#include  <stdio.h>

void panic(char *m)
{
  (void)fprintf(stderr, m);
  exit(EXIT_FAILURE);
}
