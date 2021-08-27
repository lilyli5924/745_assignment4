#include "define.h"

void StuckAtFault(char fault_f[20], struct Graph* graph, int total_count) {
    
    printf("\nHello from function StuckAtFault...\n");

    int i, j;
    int p_idx;

    int sa_idx;

    int SIZE_MAX = 15;

    int char_size = SIZE_MAX * 64;

    char track_fault_0[total_count][char_size];
    char track_fault_1[total_count][char_size];

    for (i=0; i<total_count; i++) {
        char temp_0[SIZE_MAX];
        char temp_1[SIZE_MAX];
        strcpy(temp_0, graph->llist[i].node_name);
        strcat(temp_0, "/0 ");
        strcpy(track_fault_0[sa_idx], temp_0);

        strcpy(temp_1, graph->llist[i].node_name);
        strcat(temp_1, "/1 ");
        strcpy(track_fault_1[sa_idx], temp_1);

        sa_idx++;
    }

    char remove_0[char_size];
    char remove_1[char_size];
    for (i=0; i<total_count; i++) {
        struct Node* pCrawl = graph->llist[i].head;
        while (pCrawl != NULL) {     
            // Get the index of the vertex 
            p_idx = 0;
            for (j=0; j<total_count; j++) {
                if (strcmp(pCrawl->vertex, graph->llist[j].node_name) == 0) {
                    p_idx = j;
                    break;
                }
            }
            
            if (graph->llist[p_idx].gate == '|') {
                if (graph->llist[i].fanout == -1) {
                    if (pCrawl->not == '~') {
                        //char remove_0[char_size];
                        strcpy(remove_0, track_fault_0[i]);
                        strcat(track_fault_1[p_idx], remove_0);
                        removeSubstr(track_fault_0[i], remove_0);

                    }
                    else {
                        //char remove_1[char_size];
                        strcpy(remove_1, track_fault_1[i]);
                        strcat(track_fault_1[p_idx], remove_1);
                        removeSubstr(track_fault_1[i], remove_1);
                    }
                }
            }
            else if (graph->llist[p_idx].gate == '&') {
                if (graph->llist[i].fanout == -1) {
                    if (pCrawl->not == '~') {
                        //char remove_1[char_size];
                        strcpy(remove_1, track_fault_1[i]);
                        strcat(track_fault_0[p_idx], remove_1);
                        removeSubstr(track_fault_1[i], remove_1);

                    }
                    else {
                        //char remove_0[char_size];
                        strcpy(remove_0, track_fault_0[i]);
                        strcat(track_fault_0[p_idx], remove_0);
                        removeSubstr(track_fault_0[i], remove_0);
                    }
                }
            }
            pCrawl = pCrawl->next;
        }
    }

    char* file_p = fault_f;

    file_p = strtok(file_p, "/");
    file_p = strtok(NULL, "/");
    file_p = strtok(NULL, "/");
    file_p = strtok(file_p, ".");
    char file_name[64];
    sprintf(file_name, "../output/%s.faults", file_p);
    
    FILE* faults = fopen(file_name, "w");

    for (i=0; i<total_count; i++) {
        if (strcmp(track_fault_0[i], "") != 0) {
            fprintf(faults, "%s", track_fault_0[i]);
            fprintf(faults, "\n");
        }
        if (strcmp(track_fault_1[i], "") != 0) {
            fprintf(faults, "%s", track_fault_1[i]);
            fprintf(faults, "\n");
        }
    }
    fclose(faults);
    
    printf("\nDone Generating fault space file!\n");

}

void DetectiveFaultSim(char* fault_sim, struct Graph* graph, int total_node, int out_count, int in_count, char out_array[out_count][15], char in_array[in_count][15], int vector_count) {

    printf("\nHello from DetectiveFaultSim function for vector %d...\n", vector_count+1);

    int i,j,k;

    char line[256];
    
    int CHAR_MAX = 15;
    
    char file_fault[64];
    sprintf(file_fault, "../output/%s.faults", fault_sim);
    FILE* fault_file = fopen(file_fault, "r");

    char file_detected[64];
    sprintf(file_detected, "../output/%s.detected", fault_sim);


    int fault_size = 2 * total_node;
    char** fault_space_0 = (char**)malloc(total_node * sizeof(char*));
    char** fault_space_1 = (char**)malloc(total_node * sizeof(char*));

    for (i=0; i<total_node; i++) {
        fault_space_0[i] = (char *)malloc(CHAR_MAX * sizeof(char));
        fault_space_1[i] = (char *)malloc(CHAR_MAX * sizeof(char));
        strcpy(fault_space_0[i], "x");
        strcpy(fault_space_1[i], "x");
    }
    
    int s_idx_0 = 0;
    int s_idx_1 = 0;
    while(fgets(line, sizeof(line), fault_file)) {
        removeSubstr(line, "\n");
        char* temp = strtok(line, " ");
        while (temp != NULL) {
            if (strstr(temp, "/0") != NULL) {
                strcpy(fault_space_0[s_idx_0], temp);
                s_idx_0++;
            }
            else if (strstr(temp, "/1") != NULL) {
                strcpy(fault_space_1[s_idx_1], temp);
                s_idx_1++;
            }
            temp = strtok(NULL, " ");
        }
    }

    // Allocate detected string array for each node
    // -1: Nothing    0: node_low    1: node_high
    int** detected_arr = (int**)malloc(total_node * sizeof(int*));
    for (i=0; i<total_node; i++) {
        graph->llist[i].initial = -1;
        graph->llist[i].ready = -1;
        graph->llist[i].count = 0;
        detected_arr[i] = (int*)malloc(total_node * sizeof(int));
        for (j=0; j<total_node; j++) {
            detected_arr[i][j] = -1;
        }
    }

    int p_idx;
    int remove_idx;
    int cur_element;
    int count_nodes = 0;
    int cur_result = -1;
    int out_flag = 0;

    while(count_nodes < total_node) {
        for (i=0; i<total_node; i++) {
            if (graph->llist[i].count == graph->llist[i].inputs && graph->llist[i].ready == -1) {
                count_nodes++;
                graph->llist[i].ready = 1;

                out_flag = 0;
                for (j=0; j<out_count; j++) {
                    if (strcmp(graph->llist[i].node_name, out_array[j]) == 0 && graph->llist[i].inputs == 0) {
                        out_flag = 1;
                        break;
                    }
                }

                for (j=0; j<in_count; j++) {
                    if (strcmp(graph->llist[i].node_name, in_array[j]) == 0) {
                        out_flag = 0;
                        break;
                    }
                }

                if (out_flag == 0) detected_arr[i][i] = !graph->llist[i].result;

                struct Node* pCrawl = graph->llist[i].head;
                while (pCrawl != NULL) {     
                    p_idx = 0;
                    for (j=0; j<total_node; j++) {
                        if (strcmp(pCrawl->vertex, graph->llist[j].node_name) == 0) {
                            p_idx = j;
                            break;
                        }
                    }
                    graph->llist[p_idx].count++;
                    if (pCrawl->not ==  '~') {
                        cur_result = !graph->llist[i].result;
                    }
                    else {
                        cur_result = graph->llist[i].result;
                    }

                    if (graph->llist[p_idx].initial == -1) {
                        for (j=0; j<total_node; j++) {
                            if (detected_arr[i][j] != -1) {
                                detected_arr[p_idx][j] = detected_arr[i][j];
                            }
                        }
                        if (pCrawl->not == '~') {
                            graph->llist[p_idx].initial = !graph->llist[i].result;
                        }
                        else {
                            graph->llist[p_idx].initial = graph->llist[i].result;
                        }
                    }
                    else {
                        if (graph->llist[p_idx].gate == '|') {
                            if (graph->llist[p_idx].initial == 0 && cur_result == 0) {
                                for (j=0; j<total_node; j++) {
                                    if (detected_arr[i][j] != -1) {
                                        detected_arr[p_idx][j] = detected_arr[i][j];
                                    }
                                }
                                graph->llist[p_idx].initial = 0;
                            }
                            else if (graph->llist[p_idx].initial == 1 && cur_result == 0) {
                                for (j=0; j<total_node; j++) {
                                    if (detected_arr[i][j] != -1) {
                                        if (detected_arr[p_idx][j] == detected_arr[i][j]) {
                                            detected_arr[p_idx][j] = -1;
                                        }
                                    }
                                }
                                graph->llist[p_idx].initial = 1;
                            }
                            else if (graph->llist[p_idx].initial == 0 && cur_result == 1) {
                                int detc_copy[total_node];
                                for (j=0; j<total_node; j++) {
                                    detc_copy[j] = detected_arr[i][j];
                                }
                                for (j=0; j<total_node; j++) {
                                    if (detected_arr[p_idx][j] != -1) {
                                        if (detected_arr[p_idx][j] == detc_copy[j]) {
                                            detc_copy[j] = -1;
                                        }
                                    }
                                }
                                for (j=0; j<total_node; j++) {
                                    detected_arr[p_idx][j] = detc_copy[j];
                                }
                                graph->llist[p_idx].initial = 1;
                            }
                            else if (graph->llist[p_idx].initial == 1 && cur_result == 1) {
                                for (j=0; j<total_node; j++) {
                                    if (detected_arr[i][j] != -1) {
                                        if (detected_arr[p_idx][j] != -1) {
                                            if (detected_arr[p_idx][j] == detected_arr[i][j]) {
                                                detected_arr[p_idx][j] = detected_arr[i][j];
                                            }
                                            else {
                                                detected_arr[p_idx][j] = -1;
                                            }
                                        }
                                        else {
                                            detected_arr[p_idx][j] = -1;
                                        }
                                    }
                                    else {
                                        detected_arr[p_idx][j] = -1;
                                    }
                                }
                                graph->llist[p_idx].initial = 1;
                            }
                        }
                        else if (graph->llist[p_idx].gate == '&') {
                            if (graph->llist[p_idx].initial == 1 && cur_result == 1) {
                                for (j=0; j<total_node; j++) {
                                    if (detected_arr[i][j] != -1) {
                                        detected_arr[p_idx][j] = detected_arr[i][j];
                                    }
                                }
                                graph->llist[p_idx].initial = 1;
                            }
                            else if (graph->llist[p_idx].initial == 0 && cur_result == 1) {
                                for (j=0; j<total_node; j++) {
                                    if (detected_arr[i][j] != -1) {
                                        if (detected_arr[p_idx][j] == detected_arr[i][j]) {
                                            detected_arr[p_idx][j] = -1;
                                        }
                                    }
                                }
                                graph->llist[p_idx].initial = 0;
                            }
                            else if (graph->llist[p_idx].initial == 1 && cur_result == 0) {
                                int detc_copy[total_node];
                                for (j=0; j<total_node; j++) {
                                    detc_copy[j] = detected_arr[i][j];
                                }
                                for (j=0; j<total_node; j++) {
                                    if (detected_arr[p_idx][j] != -1) {
                                        if (detected_arr[p_idx][j] == detc_copy[j]) {
                                            detc_copy[j] = -1;
                                        }
                                    }
                                }
                                for (j=0; j<total_node; j++) {
                                    detected_arr[p_idx][j] = detc_copy[j];
                                }
                                graph->llist[p_idx].initial = 0;
                            }
                            else if (graph->llist[p_idx].initial == 0 && cur_result == 0) {
                                for (j=0; j<total_node; j++) {
                                    if (detected_arr[i][j] != -1) {
                                        if (detected_arr[p_idx][j] != -1) {
                                            if (detected_arr[p_idx][j] == detected_arr[i][j]) {
                                                detected_arr[p_idx][j] = detected_arr[i][j];
                                            }
                                            else {
                                                detected_arr[p_idx][j] = -1;
                                            }
                                        }
                                        else {
                                            detected_arr[p_idx][j] = -1;
                                        }
                                    }
                                    else {
                                        detected_arr[p_idx][j] = -1;
                                    }
                                }
                                graph->llist[p_idx].initial = 0;
                            }
                        }
                    }
                    pCrawl = pCrawl->next;
                }
            }
        }
    }

    char** detected_char = (char**)malloc(fault_size * sizeof(char*));

    for (i=0; i<fault_size; i++) {
        detected_char[i] = (char *)malloc(CHAR_MAX * sizeof(char));
        strcpy(detected_char[i], "");
    }
    
    char detected[CHAR_MAX];
    int c_idx = 0;
    int duplicate_flag = 0;
    int char_idx = 0;
    strcpy(detected, "x");
    for (i=0; i<total_node; i++) {
        for (int n=0; n<out_count; n++) {
            if (strcmp(graph->llist[i].node_name, out_array[n]) == 0) {
                c_idx = i;
                for (j=0; j<total_node; j++) {
                    if (detected_arr[c_idx][j] == 0) {
                        strcpy(detected, graph->llist[j].node_name);
                        strcat(detected, "/0");
                    }
                    else if (detected_arr[c_idx][j] == 1) {
                        strcpy(detected, graph->llist[j].node_name);
                        strcat(detected, "/1");
                    }
                    duplicate_flag = 0;
                    for (k=0; k<fault_size; k++) {
                        if (strcmp(detected_char[k], detected) == 0) {
                            duplicate_flag = 1;
                            break;
                        }
                    }
                    if (duplicate_flag == 0 && strcmp(detected, "x") != 0) {
                        strcpy(detected_char[char_idx], detected);
                        char_idx++;
                    }
                }
                break;
            }
        }
    }

    if (vector_count > 0) {
        FILE* detect_file = fopen(file_detected, "a");
        for (i=0; i<fault_size; i++) {
            fprintf(detect_file, "%s ", detected_char[i]);
        }
        fprintf(detect_file, "\n");
        printf("\n");

        fclose(detect_file);
    }else {
        FILE* detect_file = fopen(file_detected, "w");
        for (i=0; i<fault_size; i++) {
            fprintf(detect_file, "%s ", detected_char[i]);
        }
        fprintf(detect_file, "\n");
        printf("\n");

        fclose(detect_file);
    }

    printf("detect_count: %d\n", char_idx);


    printf("\nDone computing detected faults!\n");

    for (i=0; i<total_node; i++) {
        free(fault_space_0[i]);
        free(fault_space_1[i]);
        free(detected_arr[i]);
    }
    free(fault_space_0);
    free(fault_space_1);
    free(detected_arr);

    for (i=0; i<fault_size; i++) {
        free(detected_char[i]);
    }
    free(detected_char);
}

void atpg_engine(char file_atpg[20], int total_node) {

    printf("\nHello from function atpg_engine...\n");

    int i,j,k;
    int fault_size = 2 * total_node;
    int CUR_MAX = fault_size * 15;
    char line[CUR_MAX];
    char d_line[CUR_MAX];

    char* atpg_f = file_atpg;

    char** undetected_char = malloc(fault_size * sizeof(char*));

    for (i=0; i<fault_size; i++) {
        undetected_char[i] = (char *)malloc(13*sizeof(char));
        strcpy(undetected_char[i], "");
    }

    atpg_f = strtok(atpg_f, "/");
    atpg_f = strtok(NULL, "/");
    atpg_f = strtok(NULL, "/");
    atpg_f = strtok(atpg_f, ".");
    char fault_list[64];
    sprintf(fault_list, "../output/%s.faults", atpg_f);

    char fault_detect[64];
    sprintf(fault_detect, "../output/%s.detected", atpg_f);

    char fault_undetect[64];
    sprintf(fault_undetect, "../output/%s.undetected", atpg_f);

    FILE* f_detected = fopen(fault_detect, "r");

    int detected_flag = 0;
    int u_idx = 0;

    int line_idx = 0;
    
    FILE* f_fault = fopen(fault_list, "r");
    while(fgets(line, sizeof(line), f_fault)) {
        detected_flag = 0;
        char* target_fault = strtok(line, " ");
        while (fgets(d_line, sizeof(d_line), f_detected)) {
            removeSubstr(d_line, "\n");
            char* detected_fault = strtok(d_line, " ");
            while (detected_fault != NULL) {
                if (strcmp(target_fault, detected_fault) == 0) {
                    detected_flag = 1;
                    break;
                } 
                detected_fault = strtok(NULL, " ");
            }
            if (detected_flag == 1) break;
        }
        if (detected_flag == 0) {
            strcpy(undetected_char[u_idx], target_fault);
            u_idx++;
        }
        // Let the file pointer rewind to beginning of the file for read again purpose
        rewind(f_detected);
    }

/*    for (i=0; i<fault_size; i++) {
        printf("%s ", undetected_char[i]);
    }
    printf("\n");*/

    FILE* undetect_file = fopen(fault_undetect, "w");
    for (i=0; i<fault_size; i++) {
        fprintf(undetect_file, "%s \n", undetected_char[i]);
    }
    fclose(undetect_file);
    

    printf("\nDone generation test pattern using atpg!\n");

    for (i=0; i<fault_size; i++) {
        free(undetected_char[i]);
    }
    free(undetected_char);
}
