#include  "defs.h"
#include  "decl.h"
#include  "extern.h"
#include  "edge.h"
#include  "draw.h"
#include  <stdio.h>
#include <stdlib.h>

static void print_edges(int argc, char *argv[],cardinal n);
static void print_triangles(cardinal n);
/*
void read_points(cardinal np)
{
  unsigned int i;

  for (i = 0; i < np; i++)
    if (scanf("%f %f", &p_array[i].x, &p_array[i].y) != 2)
	panic("Error reading points\n");
}*/

int read_points(int np)
{
  unsigned int i;
  FILE* fp;
  int code=0;
  int n;
   
  fp = fopen("input.txt","r");
  code=fscanf(fp,"%d",&n);
  printf("%d\n",n);
  alloc_memory(n);
  for (i = 0; i < n; i++)
  code=fscanf(fp,"%f %f", &p_array[i].x, &p_array[i].y);

  fclose(fp);
  return n;
}


/*
 * Driver function.
 */
void print_results(int argc, char *argv[],cardinal n, char o)
{
  /* Output edges or triangles. */
  if (o == 't')
    print_triangles(n);
  else
    print_edges(argc, argv,n);
}

/* 
 *  Print the ring of edges about each vertex.
 */
static void print_edges(int argc, char *argv[],cardinal n)
{
  edge *e_start, *e;
  point *u, *v;
  unsigned int i;
  Site* sites = NULL;
  Edges* edges = NULL;
  int numberOfEdges = 0;
  int start=0,end=0;
  int index=0;

  sites = (Site *)malloc(sizeof(Site)*n);

  for (i = 0; i < n; i++) {
    u = &p_array[i];
    sites[i].coord[0] = p_array[i].x;
    sites[i].coord[1] = p_array[i].y;
    e_start = e = u->entry_pt;
    do
    {
      v = Other_point(e, u);
      if (u < v)
	if (printf("%d %d\n", u - p_array, v - p_array) == EOF)
	  panic("Error printing results\n");
        else
        numberOfEdges++;
      e = Next(e, u);
    } while (!Identical_refs(e, e_start));
  }

  edges = (Edges*)malloc(sizeof(Edges)*numberOfEdges);

  for (i = 0; i < n; i++) {
    u = &p_array[i];
    sites[i].coord[0] = p_array[i].x;
    sites[i].coord[1] = p_array[i].y;
    e_start = e = u->entry_pt;
    do
    {
      v = Other_point(e, u);
      if (u < v)
	if (printf("%d %d\n", u - p_array, v - p_array) == EOF)
	  panic("Error printing results\n");
        else
         {
	     start =  u - p_array;
	     end =  v - p_array;
	
	     edges[index].orig[0] = p_array[start].x;
	     edges[index].orig[1] = p_array[start].y;
	     edges[index].dest[0] = p_array[end].x;
	     edges[index].dest[1] = p_array[end].y;
	     index++;
         }
        
      e = Next(e, u);
    } while (!Identical_refs(e, e_start));
  }

  printf("number of edges %d\n",numberOfEdges);
  drawVoronoi(argc, argv,edges,sites,numberOfEdges,n);
}

/* 
 *  Print the ring of triangles about each vertex.
 */
static void print_triangles(cardinal n)
{
  edge *e_start, *e, *next;
  point *u, *v, *w;
  unsigned int i;
  point *t;

  for (i = 0; i < n; i++) {
    u = &p_array[i];
    e_start = e = u->entry_pt;
    do
    {
      v = Other_point(e, u);
      if (u < v) {
	next = Next(e, u);
	w = Other_point(next, u);
	if (u < w)
	  if (Identical_refs(Next(next, w), Prev(e, v))) {  
	    /* Triangle. */
	    if (v > w) { t = v; v = w; w = t; }
	    if (printf("%d %d %d\n", u - p_array, v - p_array, w - p_array) == EOF)
	      panic("Error printing results\n");
	  }
      }

      /* Next edge around u. */
      e = Next(e, u);
    } while (!Identical_refs(e, e_start));
  }
}
