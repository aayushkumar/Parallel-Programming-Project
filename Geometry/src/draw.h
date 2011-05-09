#include <cairo.h>
#include <gtk/gtk.h>

typedef struct Edges
{
	double orig[2];
	double dest[2];
}Edges;


typedef struct Site
{
	double coord[2];
}Site;

Edges* gedges;
int numEdges;
Site*  gsites;
int numSites;

void drawVoronoi(int argc, char *argv[],Edges* edges, Site* site,int numberOfEdges,int numSites);



