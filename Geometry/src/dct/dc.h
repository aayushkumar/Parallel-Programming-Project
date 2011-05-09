#define Vector(p1,p2,u,v) (u = p2->x - p1->x, v = p2->y - p1->y)

#define Cross_product_2v(u1,v1,u2,v2) (u1 * v2 - v1 * u2)

#define Cross_product_3p(p1,p2,p3) ((p2->x - p1->x) * (p3->y - p1->y) - (p2->y - p1->y) * (p3->x - p1->x))

#define Dot_product_2v(u1,v1,u2,v2) (u1 * u2 + v1 * v2)
