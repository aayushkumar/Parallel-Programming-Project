#include  "defs.h"
#include  "decl.h"

void merge_sort(point *p[], point *p_temp[], index l, index r)
{
  index i, j, k, m;

  if (r - l > 0)
  {
    m = (r + l) / 2;
    merge_sort(p, p_temp, l, m);
    merge_sort(p, p_temp, m+1, r);

    for (i = m+1; i > l; i--)
      p_temp[i-1] = p[i-1];
    for (j = m; j < r; j++)
      p_temp[r+m-j] = p[j+1];
    for (k = l; k <= r; k++)
      if (p_temp[i]->x < p_temp[j]->x) {
        p[k] = p_temp[i];
        i = i + 1;
      } else if (p_temp[i]->x == p_temp[j]->x && p_temp[i]->y < p_temp[j]->y) {
        p[k] = p_temp[i];
        i = i + 1;
      } else {
        p[k] = p_temp[j];
        j = j - 1;
      }
  }
}
