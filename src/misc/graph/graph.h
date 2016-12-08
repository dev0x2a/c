/*
 * graph.h
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef enum { UNDIRECTED = 0, DIRECTED} graph_type_e;

/*  adjacency list node */
typedef struct adjlist_node
{
  int vertex;
  struct adjlist_node *next;       /* index to adjacency list array */
} adjlist_node_t, *adjlist_node_p; /* pointer to next node          */

/*  adjacency list  */
typedef struct adjlist
{
  int num_members;          /*  num of members in list, for future use  */
  adjlist_node_t *head;     /*  head of adjacency linked list           */
} adjlist_t, *adjlist_p;

/*  graph structure. a graph is an array of adjacency lists.
 *  size of array will be num of vertices in graph
 */
typedef struct graph
{
  graph_type_e type;      /*  directed or indirected graph  */
  int num_vertices;       /*  num of vertices               */
  adjlist_p adjListArr;   /*  adjacency lists' array        */
} graph_t, *graph_p;

/*  exit function to handle fatal errors  */
void err_exit(char* msg)
{
  printf("::\tfatal error\t%s\n::\texiting...\n", msg);
  exit(1);
}

#endif

