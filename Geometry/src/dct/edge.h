#define  Org(e)    ((e)->org)
#define  Dest(e)    ((e)->dest)
#define  Onext(e)  ((e)->onext)
#define  Oprev(e)  ((e)->oprev)
#define  Dnext(e)  ((e)->dnext)
#define  Dprev(e)  ((e)->dprev)

#define  Other_point(e,p)  ((e)->org == p ? (e)->dest : (e)->org)
#define  Next(e,p)  ((e)->org == p ? (e)->onext : (e)->dnext)
#define  Prev(e,p)  ((e)->org == p ? (e)->oprev : (e)->dprev)

typedef enum {right, left} side;

typedef  struct   point   point;
typedef  struct  edge  edge;

struct point {
    float x,y;
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



edge *join(edge *a, point *u, edge *b, point *v, side s);
void delete_edge(edge *e);
void splice(edge *a, edge *b, point *v);
edge *make_edge(point *u, point *v);

