#ifndef _DEFINE_H
#define _DEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>


struct FullScan {
    int pi_count;
    int psi_count;
    int po_count;
    int wire_count;
    int pso_count;
};

// the edge node pointing to the next vertex
struct Node {
    char vertex[15];
    char not;
    struct Node* next;
};

// the vertex in adjacency list
struct LList {
    struct Node* head;
    char node_name[15];
    int level;
    int fanout;
    int inputs;
    int count;
    int ready;
    int initial;
    int result;
    char gate;
};

struct Graph {
    int V;		 	           // size of the array
    struct LList* llist;	// graph is an array of AdjList
};

void removeSubstr (char *, char *);
struct FullScan* full_scan(const char*);
void fill_node (const char*, int, int, int, char[][15], char[][15], char[][15]);
void create_stimuli(int, char[20], int);
struct Node* newAdjNode(char[15]);
void addEdge(struct Graph*, char[15], char[15], int);
void DFS(struct Graph*, int, int*, int, char[][15], int);
void DFS_traverse(struct Graph*, int, int, char[][15], char[][15]);
void logical_sim(char[20], struct Graph*, int, int, int, int, int, char[][15], char[][15], char[][15]);
void SerialFault(struct Graph*, int, int, int, int, char[][15], char[][15], char[][15], int*);
struct Graph* createGraph(const char*, int, int, char[][15], char[][15]);
struct Graph* printGraph(const char*, int, int, char[][15], char[][15]);
void StuckAtFault(char[20], struct Graph*, int);
void DetectiveFaultSim(char*, struct Graph*, int, int, int, char[][15], char[][15], int);
void atpg_engine(char[20], int);
void my_func_2(unsigned int);

#endif
