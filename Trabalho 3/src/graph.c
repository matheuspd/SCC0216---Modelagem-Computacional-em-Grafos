#include "graph.h"

Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int num_vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adj_list = (List*)malloc(num_vertices * sizeof(List));

    for (int i = 0; i < num_vertices; ++i)
        graph->adj_list[i].head = NULL;

    return graph;
}


void freeGraph(Graph* graph) {
    if (graph) {
        if (graph->adj_list) {
            for (int i = 0; i < graph->num_vertices; ++i) {
                Node* node = graph->adj_list[i].head;
                while (node != NULL) {
                    Node* next = node->next;
                    free(node);
                    node = next;
                }
            }
            free(graph->adj_list);
        }
        free(graph);
    }
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adj_list[src].head;
    graph->adj_list[src].head = newNode;
}

void fillOrder(Graph* graph, int v, bool* visited, int* stack, int* stack_index) {
    visited[v] = true;

    Node* node = graph->adj_list[v].head;
    while (node != NULL) {
        int adj_vertex = node->dest;
        if (!visited[adj_vertex]) {
            fillOrder(graph, adj_vertex, visited, stack, stack_index);
        }
        node = node->next;
    }

    stack[(*stack_index)++] = v;
}

void DFSUtil(Graph* graph, int v, bool* visited, int* components, int* component_index) {
    visited[v] = true;
    components[(*component_index)++] = v;

    Node* node = graph->adj_list[v].head;
    while (node != NULL) {
        int adj_vertex = node->dest;
        if (!visited[adj_vertex]) {
            DFSUtil(graph, adj_vertex, visited, components, component_index);
        }
        node = node->next;
    }

    components[(*component_index)++] = -1; // Definir o último elemento como -1
}

Graph* getReversedGraph(Graph* graph) {
    int num_vertices = graph->num_vertices;
    Graph* reversed_graph = createGraph(num_vertices);

    for (int v = 0; v < num_vertices; ++v) {
        Node* node = graph->adj_list[v].head;
        while (node != NULL) {
            addEdge(reversed_graph, node->dest, v);
            node = node->next;
        }
    }

    return reversed_graph;
}

void reverseDFS(Graph* graph, int v, bool* visited) {
    visited[v] = true;
    Node* node = graph->adj_list[v].head;
    while (node != NULL) {
        int adj_vertex = node->dest;
        if (!visited[adj_vertex]) {
            reverseDFS(graph, adj_vertex, visited);
        }
        node = node->next;
    }
}

int compareComponents(const void* a, const void* b) {
    int* pa = *(int**)a;
    int* pb = *(int**)b;
    return pa[0] - pb[0];
}

int compareIntegers(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int countStronglyConnectedComponents(Graph* graph, int*** strongly_connected_components) {
    int num_vertices = graph->num_vertices;
    bool* visited = (bool*)calloc(num_vertices, sizeof(bool));
    int* stack = (int*)malloc(num_vertices * sizeof(int));
    int stack_index = 0;
    int count = 0;

    for (int i = 0; i < num_vertices; ++i) {
        if (!visited[i]) {
            fillOrder(graph, i, visited, stack, &stack_index);
        }
    }

    Graph* reversed_graph = getReversedGraph(graph);

    for (int i = 0; i < num_vertices; ++i)
        visited[i] = false;

    for (int i = stack_index - 1; i >= 0; --i) {
        int v = stack[i];
        if (!visited[v]) {
            int* components = (int*)malloc(num_vertices * sizeof(int));
            int component_index = 0;
            DFSUtil(reversed_graph, v, visited, components, &component_index);
            components[component_index] = -1; // Adiciona -1 no final para indicar o término da componente
            (*strongly_connected_components)[count] = components;
            count++;
        }
    }

    free(visited);
    free(stack);
    freeGraph(reversed_graph);
    return count;
}

void printComponent(int* component) {
    for (int i = 0; component[i] != -1; ++i) {
        printf("%d ", component[i]);
    }
    printf("\n");
}

void printComponents(int** strongly_connected_components, int num_components) {
    for (int i = 0; i < num_components; ++i) {
        //printf("Componente fortemente conexa %d: ", i);
        printComponent(strongly_connected_components[i]);
    }
}

void sortComponents(int** strongly_connected_components, int num_components) {   
    for (int i = 0; i < num_components; ++i) {
        int* component = strongly_connected_components[i];
        int j;
        for (j = 0; component[j] != -1; ++j) {}
        qsort(component, j, sizeof(int), compareIntegers);
    }
    qsort(strongly_connected_components, num_components, sizeof(int*), compareComponents);
}