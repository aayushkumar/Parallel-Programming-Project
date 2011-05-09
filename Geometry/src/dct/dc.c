#include  <stdio.h>
#include  <stdlib.h>
#include  <stddef.h>
#include  "edge.h"
#include  "dc.h"
#include  "draw.h"

point *p_array;
static edge *e_array;
static edge **free_list_e;
static unsigned int n_free_e;

static void lower_tangent(edge *r_cw_l, point *s, edge *l_ccw_r, point *u,
        edge **l_lower, point **org_l_lower,
        edge **r_lower, point **org_r_lower);

static void merge(edge *r_cw_l, point *s, edge *l_ccw_r, point *u, edge **l_tangent);


void alloc_memory(unsigned int n)
{
    edge *e;
    unsigned int i;

    /* Point storage. */
    p_array = (point *) malloc(n * sizeof(point));
    if (p_array == NULL)
    {
        printf("Not enough memory\n");
        exit(0);
    }

    /* Eulers relation suggests we wouldn't need more than 3n edges*/
    n_free_e = 3 * n;   
    e_array = e = (edge *) malloc(n_free_e * sizeof(edge));
    if (e_array == NULL)
    {
        printf("Not enough memory\n");
        exit(0);
    }

    free_list_e = (edge **)malloc(n_free_e *sizeof(edge *));
    if (free_list_e == NULL)
    {
        printf("Not enough memory\n");
        exit(0);
    }
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
    {
        printf("Out of memory for edges\n");
        exit(0);
    }

    return (free_list_e[--n_free_e]);
}

void free_edge(edge *e)
{
    free_list_e[n_free_e++] = e;
}


void merge_sort(point *p[], point *p_temp[], unsigned int l, unsigned int r)
{
    unsigned int i, j, k, m;

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


float cross_prod_vec(float x1, float y1, float x2, float y2)
{
    return (x1*y2 - y1*x2);
}


float cross_prod_pts(point *a, point *b, point *c)
{
    return cross_prod_vec((b->x - a->x), (b->y - a->y), (c->x - a->x), (c->y - a->y));
}

float dot_prod(float x1, float y1, float x2, float y2)
{
    return ((x1*x2) + (y1*y2));
}

/*
 * This is the divide method
 */
void divide(point *p_sorted[], unsigned int l, unsigned int r, edge **l_ccw, edge **r_cw)
{
    edge *l_ccw_l, *r_cw_l, *l_ccw_r, *r_cw_r, *l_tangent;

    unsigned int num_points = r - l + 1;

    /* 
     * Base Case with two points.
     * It creates an edge between these two points
     */
    if (num_points == 2) 
    {
        *r_cw = make_edge(p_sorted[l], p_sorted[r]);
        *l_ccw = *r_cw;
    } 
    /*
     * Base Case with three points.
     * It either creates a triangle (if the points are non-collinear)
     * or creates two segments between the three points (if the points are
     * collinear
     */
    else if (num_points == 3) 
    {
        edge *a, *b, *c;
        a = make_edge(p_sorted[l], p_sorted[l+1]);
        b = make_edge(p_sorted[l+1], p_sorted[r]);
        splice(a, b, p_sorted[l+1]);
        /*
         * We now calculate the cross product of the three points (by first
         * calculating the vector magnitudes and then calculating the cross-
         * product of the two vectors.
         */
        float c_p = cross_prod_pts(p_sorted[l], p_sorted[l+1], p_sorted[r]);

        /*
         * From the sign (+, -) of the cross_product we will get the direction
         * of the points.
         * There are two orientations essentially - the three points could be
         * either clockwise (CW) or Counter-ClockWise (CCW)
         */
        if (c_p > 0.0)
        {
            /* 
             * Case when the points are oriented counter-clockwise 
             * Note that when the points are oriented counter-clockwise
             * they share a common right side 
             */
            c = join(a, p_sorted[l], b, p_sorted[r], right);
            *l_ccw = a;
            *r_cw = b;
        } 
        else if (c_p < 0.0) 
        {
            /* 
             * Case when the points are oriented clockwise 
             * When the points are oriented clockwise, they share a common
             * left side
             */
            c = join(a, p_sorted[l], b, p_sorted[r], left);
            *l_ccw = c;
            *r_cw = c;
        } 
        else 
        {
            /* 
             * Points are collinear - So, we'll have just two edges.
             * We have already created those edges
             */ 
            *l_ccw = a;
            *r_cw = b;
        }
    }
    /* 
     * When the number of points is greater than three, then we merge them
     * further into two halfs
     */ 
    else if (num_points  > 3) 
    {
        /* Calculate the mid point */
        unsigned int mid = (l + r) / 2;

        /* Divide into two halves*/
        divide(p_sorted, l, mid, &l_ccw_l, &r_cw_l);
        divide(p_sorted, mid+1, r, &l_ccw_r, &r_cw_r);

        /* Merge the two resulting halves*/
        merge(r_cw_l, p_sorted[mid], l_ccw_r, p_sorted[mid+1], &l_tangent);

        /* 
         * The lower tangent added by merge may have invalidated 
         * l_ccw_l or r_cw_r. Update them if necessary. 
         */
        if (Org(l_tangent) == p_sorted[l])
            l_ccw_l = l_tangent;
        if (Dest(l_tangent) == p_sorted[r])
            r_cw_r = l_tangent;

        /* Update edge refs to be passed back */ 
        *l_ccw = l_ccw_l;
        *r_cw = r_cw_r;
    }
}

/*
 *  Determines the lower tangent of two triangulations. 
 */
static void lower_tangent(edge *r_cw_l, point *s, edge *l_ccw_r, point *u,
        edge **l_lower, point **org_l_lower,
        edge **r_lower, point **org_r_lower)
{
    edge *l, *r;
    point *o_l, *o_r, *d_l, *d_r;
    int finished;

    l = r_cw_l;
    r = l_ccw_r;
    o_l = s;
    d_l = Other_point(l, s);
    o_r = u;
    d_r = Other_point(r, u);
    finished = FALSE;

    while (!finished)
        /* 
         * This is the case when (roughly speaking) d_l is above o_l and o_r is
         * above d_l. That is the three points are counter-clockwise.  
         * If that is the case then we have to __
         */
        if (cross_prod_pts(o_l, d_l, o_r) > 0.0) {
            l = Prev(l, d_l);
            o_l = d_l;
            d_l = Other_point(l, o_l);
        } 
    /* 
     * This is the case when (roughly speaking) the d_r (dest of right edge)
     * is "above" o_r (origin of right edge).  If this is NOT the case then
     * we enter the if clause
     */
        else if (cross_prod_pts(o_r, d_r, o_l) < 0.0) {
            r = Next(r, d_r);
            o_r = d_r;
            d_r = Other_point(r, o_r);
        } else
            finished = TRUE;

        *l_lower = l;
        *r_lower = r;
        *org_l_lower = o_l;
        *org_r_lower = o_r;
}

/* 
 *  The merge function is where most of the work actually gets done.  It is
 *  written as one (longish) function for speed.
 */ 
static void merge(edge *r_cw_l, point *s, edge *l_ccw_r, point *u, edge **l_tangent)
{
    edge *base, *l_cand, *r_cand;
    point *org_base, *dest_base;
    float vec_x_lc_orig_base, vec_y_lc_orig_base, vec_x_lc_dest_base, vec_y_lc_dest_base;
    float vec_x_rc_orig_base, vec_y_rc_orig_base, vec_x_rc_dest_base, vec_y_rc_dest_base;
    
    float cross_prod_left_cand, cross_prod_right_cand;
    float dot_prod_left_cand, dot_prod_right_cand;
    int above_l_cand, above_r_cand, above_next, above_prev;
    point *dest_l_cand, *dest_r_cand;
    float cot_l_cand, cot_r_cand;
    edge *l_lower, *r_lower;
    point *org_r_lower, *org_l_lower;

    /* Creating the first cross edge or the base - this is the lower tangent */
    lower_tangent(r_cw_l, s, l_ccw_r, u, &l_lower, &org_l_lower, &r_lower, &org_r_lower);
    base = join(l_lower, org_l_lower, r_lower, org_r_lower, right);
    org_base = org_l_lower;
    dest_base = org_r_lower;

    /* We are returning the lower tangent that was found */
    *l_tangent = base;

    /* Main merge loop */
    do 
    {
        /* Initialise l_cand and r_cand */
        l_cand = Next(base, org_base);
        r_cand = Prev(base, dest_base);
        dest_l_cand = Other_point(l_cand, org_base);
        dest_r_cand = Other_point(r_cand, dest_base);

        /* Vectors for above and "in_circle" tests. */
        Vector(dest_l_cand, org_base, vec_x_lc_orig_base, vec_y_lc_orig_base);
        Vector(dest_l_cand, dest_base, vec_x_lc_dest_base, vec_y_lc_dest_base);
        Vector(dest_r_cand, org_base, vec_x_rc_orig_base, vec_y_rc_orig_base);
        Vector(dest_r_cand, dest_base, vec_x_rc_dest_base, vec_y_rc_dest_base);

        /* 
         * Here, we are trying to figure out if the point in the destination
         * of the left candidate(and dest of right candidate) is above or 
         * below the base tangent.
         * We create a vector from the candidate point to the origin of the
         * base and another vector from the candidate point to the dest of
         * the base.  We take the cross-products of these two vectors.  
         * If the candidate point is above the base then the cross-product
         * will be positive else it will be negative
         */
        cross_prod_left_cand = cross_prod_vec(vec_x_lc_orig_base, vec_y_lc_orig_base, vec_x_lc_dest_base, vec_y_lc_dest_base);
        cross_prod_right_cand = cross_prod_vec(vec_x_rc_orig_base, vec_y_rc_orig_base, vec_x_rc_dest_base, vec_y_rc_dest_base);
        above_l_cand = cross_prod_left_cand > 0.0;
        above_r_cand = cross_prod_right_cand > 0.0;
        
        /*
         * If we have no candidates above the base then we're done :)
         */
        if (!above_l_cand && !above_r_cand)
            break;        /* Finished. */

        /* 
         * This is the case when the left candidate exists.
         * We will Advance through l_cand ccw, deleting the old l_cand edge,
         *  until the "in_circle" test fails. 
         */
        if (above_l_cand)
        {
            float vec_x_pot_orig_base, vec_y_pot_orig_base, vector_x_pot_dest_base, vector_y_pot_dest_base;
            float cross_prod_pot, dot_prod_pot, cot_next;
            edge *next;
            point *dest_next;

            dot_prod_left_cand = dot_prod(vec_x_lc_orig_base, vec_y_lc_orig_base, vec_x_lc_dest_base, vec_y_lc_dest_base);
            /*
             * We find the cotangent (cot theta) by dividing the dot prod
             * by the cross prod
             */
            cot_l_cand = dot_prod_left_cand / cross_prod_left_cand;

            do 
            {
                /*
                 * This is the next potential left candidate
                 */
                next = Next(l_cand, org_base);
                dest_next = Other_point(next, org_base);
                Vector(dest_next, org_base, vec_x_pot_orig_base, vec_y_pot_orig_base);
                Vector(dest_next, dest_base, vector_x_pot_dest_base, vector_y_pot_dest_base);

                /*
                 * Calculating the cross product of the next potential left
                 * candidate and checking if it is above the base or not
                 */
                cross_prod_pot = cross_prod_vec(vec_x_pot_orig_base, vec_y_pot_orig_base, vector_x_pot_dest_base, vector_y_pot_dest_base);
                above_next = cross_prod_pot > 0.0;

                /*
                 * If it isn't above the base, then the current candidate we
                 * have will be the candidate on the left half
                 */
                if (!above_next) 
                    break;    /* Finished. */

                dot_prod_pot = dot_prod(vec_x_pot_orig_base, vec_y_pot_orig_base, vector_x_pot_dest_base, vector_y_pot_dest_base);
                cot_next = dot_prod_pot / cross_prod_pot;

                /*
                 * Not we have that if cot(theta1) < cot(theta2) then 
                 * theta1 > theta 2.
                 * Thus, if the base is common (which it is in this case)
                 * the circle formed with theta1 > theta2 will be smaller
                 * and thus we choose the candidate with the larger theta
                 * or smaller cot(theta)
                 */
                if (cot_next > cot_l_cand)
                    break;    /* Finished. */

                delete_edge(l_cand);
                l_cand = next;
                cot_l_cand = cot_next;

            } while (TRUE);
        }

        /* Now do the symmetrical for r_cand */
        if (above_r_cand)
        {
            float u_p_o_b, v_p_o_b, u_p_d_b, v_p_d_b;
            float c_p_prev, d_p_prev, cot_prev;
            edge *prev;
            point *dest_prev;

            dot_prod_right_cand = dot_prod(vec_x_rc_orig_base, vec_y_rc_orig_base, vec_x_rc_dest_base, vec_y_rc_dest_base);
            cot_r_cand = dot_prod_right_cand / cross_prod_right_cand;

            do
            {
                prev = Prev(r_cand, dest_base);
                dest_prev = Other_point(prev, dest_base);
                Vector(dest_prev, org_base, u_p_o_b, v_p_o_b);
                Vector(dest_prev, dest_base, u_p_d_b, v_p_d_b);
                c_p_prev = cross_prod_vec(u_p_o_b, v_p_o_b, u_p_d_b, v_p_d_b);
                above_prev = c_p_prev > 0.0;

                if (!above_prev) 
                    break;    /* Finished. */

                d_p_prev = dot_prod(u_p_o_b, v_p_o_b, u_p_d_b, v_p_d_b);
                cot_prev = d_p_prev / c_p_prev;

                if (cot_prev > cot_r_cand)
                    break;    /* Finished. */

                delete_edge(r_cand);
                r_cand = prev;
                cot_r_cand = cot_prev;

            } while (TRUE);
        }

        /*
         *  Now add a cross edge from base to either l_cand or r_cand. 
         *  If both are valid choose on the basis of the in_circle test . 
         *  Advance base and  whichever candidate was chosen.
         */
        dest_l_cand = Other_point(l_cand, org_base);
        dest_r_cand = Other_point(r_cand, dest_base);
        if (!above_l_cand || (above_l_cand && above_r_cand && cot_r_cand < cot_l_cand))
        {
            /* Connect to the right */
            base = join(base, org_base, r_cand, dest_r_cand, right);
            dest_base = dest_r_cand;
        } else {
            /* Connect to the left */
            base = join(l_cand, dest_l_cand, base, dest_base, right);
            org_base = dest_l_cand;
        }

    } while (TRUE);
}

/* 
 *  Prints the edges of the delaunay triangulation.
 */
static void print_edges(int argc, char *argv[],unsigned int n)
{
    edge *e_start, *e;
    point *u, *v;
    unsigned int i;
    Site* sites = NULL;
    Edges* edges = NULL;
    int numberOfEdges = 0;
    int start=0,end=0;
    int index=0;

    /* Counting number of edges in the delaunay triangulation */
    for (i = 0; i < n; i++) {
        u = &p_array[i];
        e_start = e = u->entry_pt;
        do
        {
            v = Other_point(e, u);
            if (u < v)
                numberOfEdges++;
            e = Next(e, u);
        } while (!(e == e_start));
    }

    edges = (Edges*)malloc(sizeof(Edges)*numberOfEdges);
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
                {
                    printf("Error printing results\n");
                    exit(0);
                }
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
        } while (!(e == e_start));
    }

    printf("number of edges %d\n",numberOfEdges);
    drawVoronoi(argc, argv,edges,sites,numberOfEdges,n);
}

/*
 * Reads input points from a file
 */
int read_points()
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


int main(int argc, char *argv[])
{
    unsigned int n;
    edge *l_cw, *r_ccw;
    unsigned int i;
    point **p_sorted, **p_temp;

    n = read_points(n);

    /* Initialise entry edge pointers. */
    for (i = 0; i < n; i++)
        p_array[i].entry_pt = NULL;

    /* Sort. */
    p_sorted = (point **)malloc((unsigned)n*sizeof(point *));
    if (p_sorted == NULL)
    {
        printf("triangulate: not enough memory\n");
        exit(0);
    }
    p_temp = (point **)malloc((unsigned)n*sizeof(point *));
    if (p_temp == NULL)
    {
        printf("triangulate: not enough memory\n");
        exit(0);
    }
    for (i = 0; i < n; i++)
        p_sorted[i] = p_array + i;

    merge_sort(p_sorted, p_temp, 0, n-1);

    free((char *)p_temp);

    /* Find the delaunay triangulation using divide and conquer */
    divide(p_sorted, 0, n-1, &l_cw, &r_ccw);

    free((char *)p_sorted);

    print_edges(argc, argv,n);

    free_memory();

    exit(1);
    return 1;
}
