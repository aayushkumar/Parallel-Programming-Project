#define  TRUE  1
#define  FALSE  0

/* Edge sides. */
typedef enum {right, left} side;

/* Geometric and topological entities. */
typedef  unsigned int cardinal;
typedef  float  ordinate;
typedef  struct   point   point;
typedef  struct  edge  edge;

struct point {
    ordinate x,y;
    edge *entry_pt;
};

struct edge {
    point *org;
    point *dest;
    edge *onext;
    edge *oprev;
    edge *dnext;
    edge *dprev;
};
