#include "draw.h"

static gboolean
on_expose_event(GtkWidget *widget,
    GdkEventExpose *event,
    gpointer data)
{
  cairo_t *cr;
  int i=0, j=0;
  cr = gdk_cairo_create(widget->window);

  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width (cr, 2.5);


  //printf("number of edges %d\n",numEdges);
  //printf("coming to dd for %d %f %f %f %f edges\n",numEdges,gedges[i].orig[0], gedges[i].orig[1],gedges[i].dest[0], gedges[i].dest[1]);
 
 
  
  cairo_set_source_rgb(cr, 0.3, 0.7, 0.6);
  cairo_set_line_width (cr, 2.5);
 
  for(i=0; i<numEdges; i++) 
  {
     cairo_move_to(cr, gedges[i].orig[0], gedges[i].orig[1]);
     cairo_line_to(cr, gedges[i].dest[0], gedges[i].dest[1]);
    //	 printf("coming to dd for %d %f %f %f %f edges\n",numEdges,gedges[i].orig[0], gedges[i].orig[1],gedges[i].dest[0], gedges[i].dest[1]);
  }

  cairo_stroke(cr);

 float delta=5.0;

  cairo_set_source_rgb(cr,0.7, 0.1, 0.0);
 
  for(i=0; i<numSites; i++) 
  {
     //cairo_translate(cr,gsites[i].coord[0], gsites[i].coord[1]);
     //cairo_move_to(cr, gedges[i].orig[0], gedges[i].orig[1]);
     //cairo_arc(cr,gsites[i].coord[0], gsites[i].coord[1], 1, 0, 2*3.14);
     //cairo_stroke_preserve(cr);
     cairo_move_to(cr, gsites[i].coord[0], gsites[i].coord[1]);
     cairo_line_to(cr, gsites[i].coord[0]-delta, gsites[i].coord[1]);
     
     cairo_move_to(cr, gsites[i].coord[0]-delta, gsites[i].coord[1]);
     cairo_line_to(cr, gsites[i].coord[0]-delta, gsites[i].coord[1]-delta);
     
     cairo_move_to(cr, gsites[i].coord[0]-delta, gsites[i].coord[1]-delta);
     cairo_line_to(cr, gsites[i].coord[0], gsites[i].coord[1]-delta);
     
     cairo_move_to(cr, gsites[i].coord[0], gsites[i].coord[1]-delta);
     cairo_line_to(cr, gsites[i].coord[0], gsites[i].coord[1]);
  }
  cairo_stroke(cr);
  cairo_destroy(cr);

  return FALSE;
}


gboolean clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{

    if (event->button == 3) {
        gtk_widget_queue_draw(widget);
    }

    return TRUE;
}


void drawVoronoi(int argc, char *argv[],Edges* edges, Site* sites,int numberOfEdges,int numberOfSites)
{
  GtkWidget *window;

  gtk_init(&argc, &argv);
  gedges = edges;
  numEdges = numberOfEdges;
  gsites = sites;
  numSites = numberOfSites;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
  gtk_widget_add_events (window, GDK_BUTTON_PRESS_MASK);

  g_signal_connect(window, "expose-event",
      G_CALLBACK(on_expose_event), NULL);
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(window, "button-press-event", 
      G_CALLBACK(clicked), NULL);
 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "lines");
  gtk_window_set_default_size(GTK_WINDOW(window), 1500, 1500); 
  gtk_widget_set_app_paintable(window, TRUE);

  gtk_widget_show_all(window);

  gtk_main();      
}

/*

int main (int argc, char *argv[])
{
  Edges* edges = (Edges *)malloc(sizeof(Edges)*6);
  Site* sites = (Site *)malloc(sizeof(Site)*6);

  edges[0].orig[0] = 20.0;
  edges[0].orig[1] = 20.0;
  edges[0].dest[0] = 35.0;
  edges[0].dest[1] = 40.0;

  edges[1].orig[0] = 35.0;
  edges[1].orig[1] = 40.0;
  edges[1].dest[0] = 70.0;
  edges[1].dest[1] = 20.0;

  edges[2].orig[0] = 70.0;
  edges[2].orig[1] = 20.0;
  edges[2].dest[0] = 35.0;
  edges[2].dest[1] = 80.0;

  edges[3].orig[0] = 35.0;
  edges[3].orig[1] = 80.0;
  edges[3].dest[0] = 20.0;
  edges[3].dest[1] = 20.0;

  edges[4].orig[0] = 20.0;
  edges[4].orig[1] = 20.0;
  edges[4].dest[0] = 0.0;
  edges[4].dest[1] = 0.0;

  edges[5].orig[0] = 35.0;
  edges[5].orig[1] = 40.0;
  edges[5].dest[0] = 50.0;
  edges[5].dest[1] = 0.0;
  
  sites[0].coord[0] = 100.0;
  sites[0].coord[1] = 50.0;
  sites[1].coord[0] = 55.0;
  sites[1].coord[1] = 70.0;

  sites[2].coord[0] = 45.0;
  sites[2].coord[1] = 50.0;
  sites[3].coord[0] = 75.0;
  sites[3].coord[1] = 30.0;

  sites[4].coord[0] = 40.0;
  sites[4].coord[1] = 50.0;
  sites[5].coord[0] = 85.0;
  sites[5].coord[1] = 100.0;

  drawVoronoi(argc, argv,edges,sites,6,2);
  return 0;
}
*/

