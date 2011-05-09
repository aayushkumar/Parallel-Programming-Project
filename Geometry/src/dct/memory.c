#include  <stdlib.h>
#include  "defs.h"
#include  "decl.h"

point *p_array;
static edge *e_array;
static edge **free_list_e;
static cardinal n_free_e;

void alloc_memory(cardinal n)
{
  edge *e;
  index i;

  /* Point storage. */
  p_array = (point *)calloc(n, sizeof(point));
  if (p_array == NULL)
    panic("Not enough memory\n");

  /* Edges. */
  n_free_e = 3 * n;   /* Eulers relation */
  e_array = e = (edge *)calloc(n_free_e, sizeof(edge));
  if (e_array == NULL)
    panic("Not enough memory\n");
  free_list_e = (edge **)calloc(n_free_e, sizeof(edge *));
  if (free_list_e == NULL)
    panic("Not enough memory\n");
  for (i = 0; i < n_free_e; i++, e++)
    free_list_e[i] = e;
}

void free_memory()
{
  free(p_array);  
  free(e_array);  
  free(free_list_e);  
}

edge *get_edge()
{
  if (n_free_e == 0)
    panic("Out of memory for edges\n");

   return (free_list_e[--n_free_e]);
}

void free_edge(edge *e)
{
   free_list_e[n_free_e++] = e;
}






