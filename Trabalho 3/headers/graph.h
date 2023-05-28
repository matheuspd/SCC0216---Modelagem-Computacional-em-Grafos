#ifndef __GRAPH__
#define __GRAPH__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct representing a node in the adjacency list
typedef struct Node {
    int dest;           // Destination vertex
    struct Node* next;  // Pointer to the next node
} Node;

// Struct representing the adjacency list of a graph
typedef struct List {
    Node* head;         // Pointer to the head of the list
} List;

// Struct representing a graph
typedef struct Graph {
    int num_vertices;   // Number of vertices in the graph
    List* adj_list;     // Array of adjacency lists
} Graph;


/*          Graph functions         */

// Create a new node with the given destination vertex
Node* createNode(int dest);

// Create a new graph with the given number of vertices
Graph* createGraph(int num_vertices);

// Free the memory allocated for the graph
void freeGraph(Graph* graph);

// Add an edge to the graph
void addEdge(Graph* graph, int src, int dest);

// Perform depth-first search and fill the order of vertices in the stack
void DFS(Graph* graph, int v, bool* visited, int* stack, int* stack_index);

// Perform depth-first search traversal and store the vertices in a component
void auxDFS(Graph* graph, int v, bool* visited, int* components, int* component_index);

// Get the reversed graph of a given graph
Graph* getReversedGraph(Graph* graph);

// Compare two components based on the first element of each component
int compareComponents(const void* a, const void* b);

// Compare two integers
int compareIntegers(const void* a, const void* b);

// Count the number of strongly connected components in a graph and store them in a matrix
int countStronglyConnectedComponents(Graph* graph, int*** strongly_connected_components);

// Print a strongly connected component
void printComponent(int* component);

// Print all the strongly connected components
void printComponents(int** strongly_connected_components, int num_components);

// Sort the strongly connected components
void sortComponents(int** strongly_connected_components, int num_components);

#endif