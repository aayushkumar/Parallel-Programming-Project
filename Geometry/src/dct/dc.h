#define Vector(p1,p2,u,v) (u = p2->x - p1->x, v = p2->y - p1->y)


#define  TRUE  1
#define  FALSE  0

void divide(point *p_sorted[], unsigned int l, unsigned int r, edge **l_ccw, edge **r_cw);

void alloc_memory(unsigned int n);
void free_memory();
edge *get_edge();
void free_edge(edge *e);

/* sort.c */
void merge_sort(point *p[], point *p_temp[], unsigned int l, unsigned int r);
