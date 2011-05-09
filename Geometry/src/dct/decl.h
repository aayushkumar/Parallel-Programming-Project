/* divide_and_conquer.c */
void divide(point *p_sorted[], index l, index r, edge **l_ccw, edge **r_cw);

/* edge.c */
edge *join(edge *a, point *u, edge *b, point *v, side s);
void delete_edge(edge *e);
void splice(edge *a, edge *b, point *v);
edge *make_edge(point *u, point *v);

/* error.c */
void panic(char *m);

/* i_o.c */
void read_points(cardinal n);
void print_results(cardinal n, char o);

/* memory.c */
void alloc_memory(cardinal n);
void free_memory();
edge *get_edge();
void free_edge(edge *e);

/* sort.c */
void merge_sort(point *p[], point *p_temp[], index l, index r);
