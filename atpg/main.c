#include "define.h"


struct Node* newAdjNode(char vertex[15]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->vertex, vertex);
    newNode->next = NULL;
    newNode->not = 'x';

    return newNode;
}

void addEdge(struct Graph* graph, char src[15], char dest[15], int node_count) {
    
    struct Node* newNode = newAdjNode(dest);
    // point next new node to the current head
    newNode->next = graph->llist[node_count].head;
    // point the head to the new node
    graph->llist[node_count].head = newNode;

}

void DFS(struct Graph* graph, int vertex_idx, int* track_node, int total_node, char node_arr[total_node][15], int level) {

    int i;

    int p_idx;

    // If the previous level is less than the current level, replace with new level value
    track_node[vertex_idx] = -1;
    if (graph->llist[vertex_idx].level < level) graph->llist[vertex_idx].level = level;
    struct Node* pCrawl = graph->llist[vertex_idx].head;
    while (pCrawl != NULL) {     
        // Get the index of the vertex 
        p_idx = 0;
        for (i=0; i<total_node; i++) {
            if (strcmp(pCrawl->vertex, graph->llist[i].node_name) == 0) {
                p_idx = i;
                break;
            }
        }

        // Recursion
        DFS(graph, p_idx, track_node, total_node, node_arr, level+1);
        pCrawl = pCrawl->next;
    }
}

void DFS_traverse(struct Graph* graph, int total_node, int in_count, char node_arr[total_node][15], char in_arr[in_count][15]) {
    
    printf("\nHello from function DFS_traverse...\n");

    int i, j;
    int track_count = 0;
    int level = 0;
    int* track_node = (int*)malloc(total_node * sizeof(int));
    for (i=0; i<total_node; i++) {
        track_node[i] = 1;
    }

    for (i=0; i<total_node; i++) {
        level = 0;
        if (track_node[i] == 1) {
            DFS(graph, i, track_node, total_node, node_arr, level);
	}
    }
    
    printf("\nFinished DFS_traverse!\n");
    free(track_node);
}    

struct Graph* createGraph(const char* file_in, int total_node, int in_count, char node_arr[total_node][15], char in_arr[in_count][15]) {
    
    FILE *fp;
    int i;

    printf("\nHello from function creatGraph...\n");

    char line[256];

    fp = fopen(file_in, "r");
    int line_idx = 0;
    int edge_idx = 0;
    int line_count = 0;

    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = total_node;
    graph->llist = (struct LList*)malloc(total_node*sizeof(struct LList));

    // initialize each adjacency list as empty by making head null
    for (i=0; i<total_node; i++) {
        graph->llist[i].head = NULL;
        strcpy(graph->llist[i].node_name, "x");
        graph->llist[i].gate = 'x';
        graph->llist[i].initial = 0;
        graph->llist[i].result = 1;
        graph->llist[i].ready = -1;
        graph->llist[i].count = 0;
        graph->llist[i].inputs = 0;
        graph->llist[i].fanout = -1;
        graph->llist[i].level = -1;
    }

    for (i=0; i<total_node; i++) {
        strcpy(graph->llist[i].node_name, node_arr[i]);
    }

    fgets(line, sizeof(line), fp);
    while (strstr(line, "assign") == NULL) {
        fgets(line, sizeof(line), fp);
    }
    
    char src[15];
    char dest[15];
    int e_count = 0;
    int gate_idx = 0;
    int vertex_idx = 0;
    int dest_idx = 0;
    char gates = 'x';
    char not = 'x';

    while (strstr(line, "always") == NULL) {
        e_count = 0;
        gate_idx = 0;
        vertex_idx = 0;
        gates = 'x';
        dest_idx = 0;
        char* temp_1 = strtok(line, " ");
        while (temp_1 != NULL) {
            not = 'x';
            if (strstr(temp_1, "|") != NULL) {
                gates = '|';
            }
            else if (strstr(temp_1, "&") != NULL) {
                gates = '&';
            }
            if (e_count == 1) {
                strcpy(dest, temp_1);
                for (i=0; i<total_node; i++) {
                    if (strcmp(node_arr[i], temp_1) == 0) {
                        dest_idx = i;
                        break;
                     }
                }
            }
            else if (e_count % 2 == 1) {
                if (strstr(temp_1, "1'b1") == NULL) {
                    if (strstr(temp_1, "1'b0") == NULL) {
                        if (strstr(temp_1, "~") != NULL) {
                            not = '~';
                            removeSubstr(temp_1, "~");
                        }
                        if (strstr(temp_1, ";") != NULL) {
                            removeSubstr(temp_1, ";");
			                removeSubstr(temp_1, "\n");
                        }
                        size_t ln = strlen(temp_1);
                        if (temp_1[ln-1] == 13) temp_1[ln-1] = '\0';
                        strcpy(src, temp_1);
                        for (i=0; i<total_node; i++) {
                            if (strcmp(node_arr[i], temp_1) == 0) {
                                vertex_idx = i;
                                break;
                            }
                        }
                        addEdge(graph, src, dest, vertex_idx);
                        graph->llist[vertex_idx].head->not = not;
                    }
                    else {
                        graph->llist[dest_idx].result = 0;
                    }
                }
                graph->llist[dest_idx].gate = gates;
            }
            temp_1 = strtok(NULL, " ");
            e_count++;
        }
        fgets(line, sizeof(line), fp);
    }

    // Get the level
    DFS_traverse(graph, total_node, in_count, node_arr, in_arr);
    
    return graph;
}

struct Graph* printGraph(const char* file_in, int total_node, int in_count, char node_array[total_node][15], char in_arr[in_count][15]) {

    int v, j;
    int fanout_count = 0;

    printf("\nHello from printGraph...\n");

    struct Graph* graph = createGraph(file_in, total_node, in_count, node_array, in_arr);

    for (v=0; v<graph->V; v++) {
        struct Node* pVertex = graph->llist[v].head;
        fanout_count = 0;
        printf("%s", graph->llist[v].node_name);
        while(pVertex != NULL) {
            printf(" -> %s", pVertex->vertex);
            fanout_count++;
            for (j=0; j<total_node; j++) {
                if (strcmp(pVertex->vertex, graph->llist[j].node_name) == 0) {
                    graph->llist[j].inputs = graph->llist[j].inputs + 1;
                    break;
                }
            }
            pVertex = pVertex->next;
        }
        printf("\n");
        if (fanout_count > 1) graph->llist[v].fanout = 1;
    }

    return graph;
}

void logical_sim(char response_f[20], struct Graph* graph, int total_node, int in_count, int out_count, int total_level, int vector_total, char in_arr[in_count][15], char node_arr[total_node][15], char out_array[out_count][15]) {

    printf("\nHello from function logical_sim...\n");

    int i, j, k;

    char* file_p = response_f;

    file_p = strtok(file_p, "/");
    file_p = strtok(NULL, "/");
    file_p = strtok(NULL, "/");
    file_p = strtok(file_p, ".");
    char file_name[64];
    sprintf(file_name, "../output/%s.stimuli", file_p);
    
    FILE* stimuli = fopen(file_name, "r");
    int* in_num_arr = (int*)malloc(in_count * sizeof(int));

    char file_out[64];
    sprintf(file_out, "../output/%s.responses", file_p);
    FILE* response = fopen(file_out, "w");

    char file_fault[64];
    sprintf(file_fault, "../output/%s.faults", file_p);

    char line[in_count + 256];

    for (i=0; i<in_count; i++) {
        in_num_arr[i] = -1;
    }
    
    int vector_loop = 0;

    int* result_init = (int*)malloc(total_node * sizeof(int));

    for (i=0; i<total_node; i++) {
        result_init[i] = graph->llist[i].result;
    }

    while(fgets(line, sizeof(line), stimuli) && (vector_loop < vector_total)) {
        removeSubstr(line, "\n");
        size_t ln = strlen(line);
        if (line[ln-1] == 13) line[ln-1] = '\0';
        int str_length = strlen(line);
        for (i=0; i<str_length; i++) {
            in_num_arr[i] = line[i] - '0';
        }
    
        for (i=0; i<total_node; i++) {
            graph->llist[i].result = result_init[i];
            graph->llist[i].initial = 0;
        }

        int in_value = -1;
        int p_idx = 0;
        for (j=0; j<total_node; j++) {
            in_value = -1;
            p_idx = 0;
            if (graph->llist[j].level == 0) {
                for (k=0; k<in_count; k++) {
                    if (strcmp(graph->llist[j].node_name, in_arr[k]) == 0) {
                        in_value = in_num_arr[k];
                        break;
                    }
                } 
                graph->llist[j].result = graph->llist[j].result && in_value;
                struct Node* pCrawl = graph->llist[j].head;
                while (pCrawl != NULL) { 
                    for (k=0; k<total_node; k++) {
                        if (strcmp(pCrawl->vertex, node_arr[k]) == 0) {
                            p_idx = k;
                            break;
                        }
                    }
                    int cur_result = 0;
                    if (pCrawl->not == '~') {
                        cur_result = !graph->llist[j].result;
                    }else {
                        cur_result = graph->llist[j].result;
                    }
                    if (graph->llist[p_idx].initial == 1) {
                        if (graph->llist[p_idx].gate == '|') {
                            graph->llist[p_idx].result = graph->llist[p_idx].result | cur_result;
                        }
                        else if (graph->llist[p_idx].gate == '&') {
                            graph->llist[p_idx].result = graph->llist[p_idx].result & cur_result;
                        }
                    }
                    else {
                        graph->llist[p_idx].result = graph->llist[p_idx].result & cur_result;
                    }
                    if (graph->llist[p_idx].initial == 0) graph->llist[p_idx].initial = 1;
                    pCrawl = pCrawl->next;
                }
            }
        }

        for (i=1; i<total_level; i++) {
            for (j=0; j<total_node; j++) {
                p_idx = 0;
                if (graph->llist[j].level == i) {
                    struct Node* pCrawl = graph->llist[j].head;
                    while (pCrawl != NULL) { 
                        for (k=0; k<total_node; k++) {
                            if (strcmp(pCrawl->vertex, node_arr[k]) == 0) {
                                p_idx = k;
                                break;
                            }
                        }
                        int cur_result = 0;
                        if (pCrawl->not == '~') {
                            cur_result = !graph->llist[j].result;
                        }else {
                            cur_result = graph->llist[j].result;
                        }
                        if (graph->llist[p_idx].initial == 1) {
                            if (graph->llist[p_idx].gate == '|') {
                                graph->llist[p_idx].result = graph->llist[p_idx].result || cur_result;
                            }
                            else if (graph->llist[p_idx].gate == '&') {
                                graph->llist[p_idx].result = graph->llist[p_idx].result && cur_result;
                            }
                        }
                        else {
                            graph->llist[p_idx].result = graph->llist[p_idx].result && cur_result;
                        }
                        if (graph->llist[p_idx].initial == 0) graph->llist[p_idx].initial = 1;
                        pCrawl = pCrawl->next;
                    }
                }
            }
        }

        printf("\nThe DAG:\n");
        for (i=0; i<total_node; i++) {
            printf("node: %s, level: %d, gates: %c, inputs: %d, result: %d\n", graph->llist[i].node_name, graph->llist[i].level, graph->llist[i].gate, graph->llist[i].inputs, graph->llist[i].result);
        }

        // Detective Fault Simulation
        DetectiveFaultSim(file_p, graph, total_node, out_count, in_count, out_array, in_arr, vector_loop);

        int* out_arr_check = (int*)malloc(out_count * sizeof(int));

        for (i=0; i<out_count; i++) {
            out_arr_check[i] = -1;
        }

        for (i=0; i<total_node; i++) {
            for (j=0; j<out_count; j++) {
                if (strcmp(graph->llist[i].node_name, out_array[j]) == 0) {
                    out_arr_check[j] = graph->llist[i].result;
                    fprintf(response, "%d", graph->llist[i].result);
                }
            }
        }
        fprintf(response, "\n");
        vector_loop++;

        //SerialFault(graph, total_node, in_count, out_count, total_level, in_arr, node_arr, out_array, out_arr_check);
    }

    fclose(stimuli);
    fclose(response);

    printf("\nDone Logic Simulation!\n");

    free(in_num_arr);
    free(result_init);
}

void SerialFault(struct Graph* graph, int total_node, int in_count, int out_count, int total_level, char in_arr[in_count][15], char node_arr[total_node][15], char out_array[out_count][15], int* out_check) {
   
    printf("\nHello from function SerialFault ...\n");

    int i, j, k;
    
    int vector_loop = 0;
    int vector_total = 1;
    int fault_count = 0;
    int fault_size = 2 * total_node;

    char fault_arr[fault_size][15];

    for (i=0; i<fault_size; i++) {
        strcpy(fault_arr[i], "x");
    }

    int* result_queue = (int*)malloc(total_node * sizeof(int));

    for (i=0; i<total_node; i++) {
        result_queue[i] = graph->llist[i].result;
        graph->llist[i].initial = 0;
    }

    int p_idx = 0;
    for (int m=0; m<total_node; m++) {
        for (int n=0; n<2; n++) {
            for (int y=0; y<total_node; y++) {
                graph->llist[y].result = result_queue[y];
                graph->llist[y].initial = 0;
            }
            graph->llist[m].result = n;
            for (i=0; i<total_level; i++) {
                for (j=0; j<total_node; j++) {
                    p_idx = 0;
                    if (graph->llist[j].level == i) {
                        struct Node* pCrawl = graph->llist[j].head;
                        while (pCrawl != NULL) { 
                            if (strcmp(pCrawl->vertex, graph->llist[m].node_name) != 0) {
                            for (k=0; k<total_node; k++) {
                                if (strcmp(pCrawl->vertex, node_arr[k]) == 0) {
                                    p_idx = k;
                                    break;
                                }
                            }
                            int cur_result = 0;
                            if (pCrawl->not == '~') {
                                cur_result = !graph->llist[j].result;
                            }else {
                                cur_result = graph->llist[j].result;
                            }
                            if (graph->llist[p_idx].initial == 1) {
                                if (graph->llist[p_idx].gate == '|') {
                                    graph->llist[p_idx].result = graph->llist[p_idx].result || cur_result;
                                }
                                else if (graph->llist[p_idx].gate == '&') {
                                    graph->llist[p_idx].result = graph->llist[p_idx].result && cur_result;
                                }
                            }
                            else {
                                graph->llist[p_idx].result = cur_result;
                            }
                            if (graph->llist[p_idx].initial == 0) graph->llist[p_idx].initial = 1;
                            }

                            pCrawl = pCrawl->next;
                        }
                    }
                }
            }
            int fault_check = 0;
            
            for (int q=0; q<total_node; q++) {
                for (int p=0; p<out_count; p++) {
                    if (strcmp(graph->llist[q].node_name, out_array[p]) == 0) {
                        if (graph->llist[q].result != out_check[p]) {
                            fault_check = 1;
                            break;
                        }
                    }
                }
            }
            if (fault_check == 1) {
                int fault_flag = 0;
                for (int x=0; x<fault_size; x++) {
                    if (strcmp(fault_arr[x], graph->llist[m].node_name) == 0) {
                        fault_flag = 1;
                        break;
                    }
                }
                if (fault_flag == 0) {
                    printf("%s/%d ", graph->llist[m].node_name, n);
                    strcpy(fault_arr[fault_count], graph->llist[m].node_name);
                    fault_count++;
                }    
            }
        }
    }
    printf("\nfault count: %d\n", fault_count);

}


int main(int argc, char *argv[])
{
    clock_t my_time;

    int i;

    // initialize the random number generator
    srand((int)time(NULL));
    printf("\n");

    printf("CLOCKS PER SEC is %u\n\n", (unsigned int)CLOCKS_PER_SEC);    

    const char* file_in = argv[1];
    char stimuli_in[20];
    char response_in[20];
    char fault_in[20];
    char file_atpg[20];
    char fault_sim[20];
    char serial_in[20];
    strcpy(stimuli_in, file_in);
    strcpy(response_in, file_in);
    strcpy(fault_in, file_in);
    strcpy(fault_sim, file_in);
    strcpy(file_atpg, file_in);
    strcpy(serial_in, file_in);

    char* p;
    long arg = strtol(argv[2], &p, 10);
    int rand_vector = (int)arg;

    struct FullScan* scan_result = full_scan(file_in);
    
    int total_node = scan_result->pi_count + scan_result->po_count + scan_result->psi_count + scan_result->wire_count;
    int input_count = scan_result->pi_count + scan_result->psi_count;
    int out_count = scan_result->po_count + scan_result->pso_count;
    
    char nodes_array[total_node][15];
    char input_array[input_count][15];
    char out_array[out_count][15];

    fill_node(file_in, total_node, input_count, out_count, nodes_array, input_array, out_array);
    create_stimuli(rand_vector, stimuli_in, input_count);

    //printf("total node:\n");
    //for (i=0; i<total_node; i++) {
    //    printf("%s\n", nodes_array[i]);
    //}

    //printf("input node:\n");
    for (i=0; i<input_count; i++) {
        size_t ln = strlen(input_array[i]);
        if (input_array[i][ln-1] == 13) {
            input_array[i][ln-1] = '\0';
        }
	    //printf("%s\n", input_array[i]);
    }

    //printf("out node:\n");
    for (i=0; i<out_count; i++) {
        size_t ln = strlen(out_array[i]);
        if (out_array[i][ln-1] == 13) {
            out_array[i][ln-1] = '\0';
        }
	    //printf("%s\n", out_array[i]);
    }

    struct Graph* graph = printGraph(file_in, total_node, input_count, nodes_array, input_array);

    //printf("\nThe DAG:\n");
    //for (i=0; i<total_node; i++) {
    //    printf("node: %s, level: %d, gates: %c, inputs: %d, result: %d\n", graph->llist[i].node_name, graph->llist[i].level, graph->llist[i].gate, graph->llist[i].inputs, graph->llist[i].result);
    //}


    int max_level = 0;
    for (i=0; i<total_node; i++) {
        if (graph->llist[i].level > max_level) {
            max_level = graph->llist[i].level;
        }
    }

    // Create x.fault file
    StuckAtFault(fault_in, graph, total_node);
    
    // Logical Simulation
    logical_sim(response_in, graph, total_node, input_count, out_count, max_level, rand_vector, input_array, nodes_array, out_array);
    
    atpg_engine(file_atpg, total_node);


    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("\nMemory usage: %ld KB\n", usage.ru_maxrss);

    return 0;
}
