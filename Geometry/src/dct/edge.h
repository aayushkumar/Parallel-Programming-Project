#define  Org(e)    ((e)->org)
#define  Dest(e)    ((e)->dest)
#define  Onext(e)  ((e)->onext)
#define  Oprev(e)  ((e)->oprev)
#define  Dnext(e)  ((e)->dnext)
#define  Dprev(e)  ((e)->dprev)

#define  Other_point(e,p)  ((e)->org == p ? (e)->dest : (e)->org)
#define  Next(e,p)  ((e)->org == p ? (e)->onext : (e)->dnext)
#define  Prev(e,p)  ((e)->org == p ? (e)->oprev : (e)->dprev)

#define  Visited(p)  ((p)->f)

#define Identical_refs(e1,e2)  (e1 == e2)
