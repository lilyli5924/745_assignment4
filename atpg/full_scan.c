#include "define.h"

void removeSubstr (char *string, char *sub) {
    char *match;
    size_t len = strlen(sub);
    while ((string = strstr(string, sub))) {
	memmove(string, string + len, 1 + strlen(string + len));
    }
}

void create_stimuli(int rand_vector, char stimuli_f[20], int total_input) {

    printf("\nHello from function create_stimuli...\n");
    int i,j,n;

    char* file_p = stimuli_f;

    file_p = strtok(file_p, "/");
    file_p = strtok(NULL, "/");
    file_p = strtok(NULL, "/");
    file_p = strtok(file_p, ".");
    char file_name[64];
    sprintf(file_name, "../output/%s.stimuli", file_p);
    FILE* f_out = fopen(file_name, "w");

    printf("%d\n", total_input);
    for (i=0; i<rand_vector; i++) {
        for (j=0; j<total_input; j++) {
            n = rand() % 2;
            fprintf(f_out, "%d", n);
        }
        fprintf(f_out, "\n");
    }
    fclose(f_out);
}

struct FullScan* full_scan(const char* file_in)
{
    printf("\nHello from function full_scan...\n");

    struct FullScan* scan_result = (struct FullScan*)malloc(sizeof(struct FullScan));

    scan_result->pi_count = 0;
    scan_result->po_count = 0;
    scan_result->psi_count = 0;
    scan_result->pso_count = 0;
    scan_result->wire_count = 0;
    
    char line[256];
    FILE* FILENAME = fopen(file_in, "r");

    fgets(line, sizeof(line), FILENAME);
    while (strstr(line, "input") == NULL) {
        fgets(line, sizeof(line), FILENAME);
    }
    
    //printf("%s\n", line);
    int end_flag = 0;
    int end_input = 0;
    char* temp_1 = strtok(line, ", ");
    char temp_1_check;
    temp_1 = strtok(NULL, ", ");
    
    while (1) {
        end_flag = 0;
        while (1) {
            temp_1 = strtok(NULL, " ");
            if (temp_1 == NULL) break;
            if (strstr(temp_1, "\n") != NULL) {
                removeSubstr(temp_1, "\n");
            }
            if (strstr(temp_1, ";") != NULL) {
                removeSubstr(temp_1, ";");
                end_input = 1;
                //printf("%s\n", temp_1);
                scan_result->pi_count++;
                break;
            }
            //printf("%s\n", temp_1);
	    if (strcmp(temp_1, "") != 0) {
                scan_result->pi_count++;
	    }
        }
        if (end_input) break;
        fgets(line, sizeof(line), FILENAME);
        if (strstr(line, ",") != NULL) {
            temp_1 = strtok(line, " ");
            removeSubstr(temp_1, ",");
            scan_result->pi_count++;
            //printf("%s\n", temp_1);
        }
        else {
            temp_1 = strtok(line, ";");
            removeSubstr(temp_1, " ");
            scan_result->pi_count++;
            //printf("%s\n", temp_1);
            break;
        }
    }
    printf("pi_count: %d\n", scan_result->pi_count);

    fgets(line, sizeof(line), FILENAME);
    //printf("%s\n", line);
    int end_output = 0;
    int start_output = 0;
    char* temp_2 = strtok(line, " ");
    temp_2 = strtok(NULL, " ");
    int size = strlen(temp_2);
    temp_2[size-1] = '\0';
    if (strstr(temp_2, ";") != NULL) {
        removeSubstr(temp_2, ";");
        start_output = 1;
    }
    //printf("%s\n", temp_2);
    scan_result->po_count++;

    while (!start_output) {
        end_flag = 0;
        while (1) {
            temp_2 = strtok(NULL, " ");
	        if (temp_2 == NULL) break;
            if (strstr(temp_2, "\n") != NULL) {
                end_flag = 1;
                removeSubstr(temp_2, "\n");
            }
            if (strstr(temp_2, ";") != NULL) {
                removeSubstr(temp_2, ";");
                //printf("%s\n", temp_2);
                scan_result->po_count++;
                end_output = 1;
                break;
            }
            //printf("%s\n", temp_2);
	    if (strcmp(temp_2, "") != 0) {
                scan_result->po_count++;
	    }
        }
        if (end_output) break;
        fgets(line, sizeof(line), FILENAME);
        if (strstr(line, ",") != NULL) {
            temp_2 = strtok(line, " ");
            removeSubstr(temp_2, ",");
            scan_result->po_count++;
            //printf("%s\n", temp_2);
        }
        else {
            temp_2 = strtok(line, ";");
            removeSubstr(temp_2, " ");
            scan_result->po_count++;
            //printf("%s\n", temp_2);
            break;
        }
    }
    printf("po_count: %d\n", scan_result->po_count);

    fgets(line, sizeof(line), FILENAME);
    int end_reg = 0;
    int start_reg = 0;
    char* temp_3 = strtok(line, " ");
    temp_3 = strtok(NULL, " ");
    size = strlen(temp_3);
    temp_3[size-1] = '\0';
    if (strstr(temp_3, ";") != NULL) {
        removeSubstr(temp_3, ";");
        start_reg = 1;
    }
    //printf("%s\n", temp_3);
    scan_result->psi_count++;

    while (!start_reg) {
        end_flag = 0;
        while (1) {
            temp_3 = strtok(NULL, " ");
	        if (temp_3 == NULL) break;
            if (strstr(temp_3, "\n") != NULL) {
                end_flag = 1;
                removeSubstr(temp_3, "\n");
            }
            if (strstr(temp_3, ";") != NULL) {
                removeSubstr(temp_3, ";");
                //printf("%s\n", temp_3);
                scan_result->psi_count++;
                end_reg = 1;
                break;
            }
            //printf("%s\n", temp_3);
	        if (strcmp(temp_3, "") != 0) {
                scan_result->psi_count++;
	        }
        }
        if (end_reg) break;
        fgets(line, sizeof(line), FILENAME);
        if (strstr(line, ",") != NULL) {
            temp_3 = strtok(line, " ");
            removeSubstr(temp_3, ",");
            scan_result->psi_count++;
            //printf("%s\n", temp_3);
        }
        else {
            temp_3 = strtok(line, ";");
            removeSubstr(temp_3, " ");
            scan_result->psi_count++;
            //printf("%s\n", temp_3);
            break;
        }
    }
    printf("psi_count: %d\n", scan_result->psi_count);

    fgets(line, sizeof(line), FILENAME);
    int end_wire = 0;
    int start_wire = 0;
    char* temp_4 = strtok(line, " ");
    temp_4 = strtok(NULL, " ");
    char temp_4_check = temp_4[0];
    size = strlen(temp_4);
    temp_4[size-1] = '\0';
    if (strstr(temp_4, ";") != NULL) {
        removeSubstr(temp_4, ";");
        start_wire = 1;
    }
    //printf("%s\n", temp_4);
    scan_result->wire_count++;

    while (!start_wire) {
        end_wire = 0;
        while (1) {
            temp_4 = strtok(NULL, ", ");
	        if (temp_4[0] != temp_4_check) break;
            if (strstr(temp_4, "\n") != NULL) {
                end_flag = 1;
                removeSubstr(temp_4, "\n");
            }
            if (strstr(temp_4, ";") != NULL) {
                removeSubstr(temp_4, ";");
                //printf("%s\n", temp_4);
                scan_result->wire_count++;
                end_wire = 1;
                break;
            }
            //printf("%s\n", temp_4);
	    if (strstr(temp_4, "") != NULL) {
                scan_result->wire_count++;
	    }
        }
        if (end_wire) break;
        fgets(line, sizeof(line), FILENAME);
        if (strstr(line, ",") != NULL) {
            temp_4 = strtok(line, " ");
            removeSubstr(temp_4, ",");
            scan_result->wire_count++;
            //printf("%s\n", temp_4);
        }
        else {
            temp_4 = strtok(line, ";");
            removeSubstr(temp_4, " ");
            scan_result->wire_count++;
            //printf("%s\n", temp_4);
            break;
        }
    }
    printf("wire_count: %d\n", scan_result->wire_count);

    fgets(line, sizeof(line), FILENAME);
    while (strstr(line, "assign") != NULL) {
        fgets(line, sizeof(line), FILENAME);
    }
    fgets(line, sizeof(line), FILENAME);
    char* temp_5;
    while (strstr(line, "end") == NULL) {
        temp_5 = strtok(line, "<= ");
        temp_5 = strtok(NULL, "<= ");
        removeSubstr(temp_5, ";\n");
        //printf("%s\n", temp_5);
        scan_result->pso_count++;
        fgets(line, sizeof(line), FILENAME);
    }
    printf("pso_count: %d\n", scan_result->pso_count);
    fclose(FILENAME);

    return scan_result;
}

void fill_node(const char* file_in, int total_node, int input_node, int out_size, char node_arr[total_node][15], char input_arr[input_node][15], char out_arr[out_size][15]) {
    
    char line[256];

    FILE* FILENAME = fopen(file_in, "r");

    fgets(line, sizeof(line), FILENAME);
    while (strstr(line, "input") == NULL) {
        fgets(line, sizeof(line), FILENAME);
    }
    
    int end_flag = 0;
    int end_input = 0;
    int p_count = 0;
    int out_cnt = 0;
    if (strstr(line, "\n") != NULL) {
        removeSubstr(line, "\n");
    }
    char* temp_1 = strtok(line, ", ");
    temp_1 = strtok(NULL, ", ");

    int node_count = 0;
    int in_count = 0;
    
    while (1) {
        while (1) {
            temp_1 = strtok(NULL, " ");
            if (temp_1 == NULL) break;
            if (strstr(temp_1, "\n") != NULL) {
                removeSubstr(temp_1, "\n");
            }
            if (strstr(temp_1, ";") != NULL) {
                removeSubstr(temp_1, ";");
		        size_t ln = strlen(temp_1);
		        if (temp_1[ln-1] == 13) temp_1[ln-1] = '\0';
                end_input = 1;
                strcpy(node_arr[node_count], temp_1);
                strcpy(input_arr[in_count], temp_1);
                in_count++;
                node_count++;
                //printf("%s\n", temp_1);
                break;
            }
            if (strstr(temp_1, ",") != NULL) {
                removeSubstr(temp_1, ",");
                size_t ln = strlen(temp_1);
                if (temp_1[ln-1] == 13) {
                    temp_1[ln-1] = '\0';
                }
            }
            strcpy(node_arr[node_count], temp_1);
            strcpy(input_arr[in_count], temp_1);
            in_count++;
            node_count++;
            p_count++;
            //printf("%s\n", temp_1);
        }
        if (end_input) break;
        fgets(line, sizeof(line), FILENAME);
        if (strstr(line, ",") != NULL) {
            removeSubstr(line, "\n");
            temp_1 = strtok(line, " ");
            removeSubstr(temp_1, ",");
            strcpy(node_arr[node_count], temp_1);
            strcpy(input_arr[in_count], temp_1);
            in_count++;
            node_count++;
            //printf("%s\n", temp_1);
        }
        else {
            temp_1 = strtok(line, ";");
            removeSubstr(temp_1, " ");
            strcpy(node_arr[node_count], temp_1);
            strcpy(input_arr[in_count], temp_1);
            in_count++;
            node_count++;
            //printf("%s\n", temp_1);
            break;
        }
    }

    fgets(line, sizeof(line), FILENAME);
    if (strstr(line, "\n") != NULL) {
        removeSubstr(line, "\n");
    }
    int end_output = 0;
    int start_output = 0;
    char* temp_2 = strtok(line, " ");
    temp_2 = strtok(NULL, " ");
    if (strstr(temp_2, ",") != NULL) {
        removeSubstr(temp_2, ",");
    }
    size_t size = strlen(temp_2);
    if (temp_2[size-1] == 13) temp_2[size-1] = '\0';
    if (strstr(temp_2, ";") != NULL) {
        removeSubstr(temp_2, ";");
        size_t ln = strlen(temp_2);
	    if (temp_2[ln-1] == 13) temp_2[ln-1] = '\0';
        start_output = 1;
    }
    strcpy(node_arr[node_count], temp_2);
    strcpy(out_arr[out_cnt], temp_2);
    out_cnt++;
    node_count++;

    //printf("%s\n", temp_2);

    while (!start_output) {
        while (1) {
            temp_2 = strtok(NULL, " ");
            if (temp_2 == NULL) break;
            if (strstr(temp_2, "\n") != NULL) {
                removeSubstr(temp_2, "\n");
            }
            if (strstr(temp_2, ";") != NULL) {
                removeSubstr(temp_2, ";");
		        size_t ln = strlen(temp_2);
		        if (temp_2[ln-1] == 13) temp_2[ln-1] = '\0';
                strcpy(node_arr[node_count], temp_2);
                strcpy(out_arr[out_cnt], temp_2);
                out_cnt++;
                node_count++;
                //printf("%s\n", temp_2);
                end_output = 1;
                break;
            }
            if (strstr(temp_2, ",") != NULL) {
                removeSubstr(temp_2, ",");
                size_t ln = strlen(temp_2);
                if (temp_2[ln-1] == 13) {
                    temp_2[ln-1] = '\0';
                }
            }
            strcpy(node_arr[node_count], temp_2);
            strcpy(out_arr[out_cnt], temp_2);
            out_cnt++;
            node_count++;
            //printf("%s\n", temp_2);
        }
        if (end_output) break;
        fgets(line, sizeof(line), FILENAME);
        if (strstr(line, ",") != NULL) {
            removeSubstr(line, "\n");
            temp_2 = strtok(line, " ");
            removeSubstr(temp_2, ",");
            strcpy(node_arr[node_count], temp_2);
            strcpy(out_arr[out_cnt], temp_2);
            out_cnt++;
            node_count++;       
            //printf("%s\n", temp_2);
        }
        else {
            temp_2 = strtok(line, ";");
            removeSubstr(temp_2, " ");
            strcpy(node_arr[node_count], temp_2);
            strcpy(out_arr[out_cnt], temp_2);
            out_cnt++;
            node_count++;
            //printf("%s\n", temp_2);
            break;
        }
    }

    fgets(line, sizeof(line), FILENAME);
    int end_reg = 0;
    int start_reg = 0;
    if (strstr(line, "\n") != NULL) {
	    removeSubstr(line, "\n");
    }
    char* temp_3 = strtok(line, " ");
    temp_3 = strtok(NULL, " ");
    if (strstr(temp_3, ",") != NULL) {
        removeSubstr(temp_3, ",");
    }
    char temp_3_check = temp_3[0];
    size = strlen(temp_3);
    if (temp_3[size-1] == 13) temp_3[size-1] = '\0';
    if (strstr(temp_3, ";") != NULL) {
        removeSubstr(temp_3, ";");
	    size_t ln = strlen(temp_3);
	    temp_3[ln-1] = '\0';
        start_reg = 1;
    }
    strcpy(node_arr[node_count], temp_3);
    strcpy(input_arr[in_count], temp_3);
    in_count++;
    node_count++;

    while (!start_reg) {
        while (1) {
            temp_3 = strtok(NULL, " ");
            if (temp_3 == NULL) break;
            if (strstr(temp_3, "\n") != NULL) {
		        removeSubstr(temp_3, "\n");
	        }
            if (strstr(temp_3, ";") != NULL) {
                removeSubstr(temp_3, ";");
		        size_t ln = strlen(temp_3);
		        if (temp_3[ln-1] == 13) temp_3[ln-1] = '\0';
                strcpy(node_arr[node_count], temp_3);
                strcpy(input_arr[in_count], temp_3);
                in_count++;
                node_count++;
                //printf("%s\n", temp_3);
                end_reg = 1;
                break;
            }
            if (strstr(temp_3, ",") != NULL) {
                removeSubstr(temp_3, ",");
                size_t ln = strlen(temp_3);
                if (temp_3[ln-1] == 13) {
                    temp_3[ln-1] = '\0';
                }
                
            }
            strcpy(node_arr[node_count], temp_3);
            strcpy(input_arr[in_count], temp_3);
            in_count++;
            node_count++;
            //printf("%s\n", temp_3);
        }
        if (end_reg) break;
        fgets(line, sizeof(line), FILENAME);
        if (strstr(line, ",") != NULL) {
            removeSubstr(line, "\n");
            temp_3 = strtok(line, " ");
	        removeSubstr(temp_3, ",");
            strcpy(node_arr[node_count], temp_3);
            strcpy(input_arr[in_count], temp_3);
            in_count++;
            node_count++;
            //printf("%s\n", temp_3);
        }
        else {
            temp_3 = strtok(line, ";");
            removeSubstr(temp_3, " ");
            strcpy(node_arr[node_count], temp_3);
            strcpy(input_arr[in_count], temp_3);
            in_count++;
            node_count++;
            //printf("%s\n", temp_3);
            break;
        }
    }

    fgets(line, sizeof(line), FILENAME);
    if (strstr(line, "\n") != NULL) {
	    removeSubstr(line, "\n");
    }
    int end_wire = 0;
    int start_wire = 0;
    char* temp_4 = strtok(line, " ");
    temp_4 = strtok(NULL, " ");
    if (strstr(temp_4, ",") != NULL) {
        removeSubstr(temp_4, ",");
    }
    char temp_4_check = temp_4[0];
    size = strlen(temp_4);
    if (temp_4[size-1] == 13) temp_4[size-1] = '\0';
    if (strstr(temp_4, ";") != NULL) {
        removeSubstr(temp_4, ";");
	    size_t ln = strlen(temp_4);
	    temp_4[ln-1] = '\0';
        start_wire = 1;
    }
    strcpy(node_arr[node_count], temp_4);
    node_count++;
    //printf("%s\n", temp_4);

    while (!start_wire) {
        end_wire = 0;
        while (1) {
            temp_4 = strtok(NULL, " ");
            if (temp_4 == NULL) break;
            if (strstr(temp_4, "\n") != NULL) {
                removeSubstr(temp_4, "\n");
            }
            if (strstr(temp_4, ";") != NULL) {
                removeSubstr(temp_4, ";");
		        size_t ln = strlen(temp_4);
		        if (temp_4[ln-1] == 13) temp_4[ln-1] = '\0';
                strcpy(node_arr[node_count], temp_4);
                node_count++;
                //printf("%s\n", temp_4);
                end_wire = 1;
                break;
            }
            if (strstr(temp_4, ",") != NULL) {
                removeSubstr(temp_4, ",");
                size_t ln = strlen(temp_4);
                if (temp_4[ln-1] == 13) {
                    temp_4[ln-1] = '\0';
                }
            }
            strcpy(node_arr[node_count], temp_4);
            node_count++;
            //printf("%s\n", temp_4);
        }
        if (end_wire) break;
        fgets(line, sizeof(line), FILENAME);
        if (strstr(line, ",") != NULL) {
            removeSubstr(line, "\n");
            temp_4 = strtok(line, " ");
            removeSubstr(temp_4, ",");
            strcpy(node_arr[node_count], temp_4);
            node_count++;
            //printf("%s\n", temp_4);
        }
        else {
            temp_4 = strtok(line, ";");
            removeSubstr(temp_4, " ");
            strcpy(node_arr[node_count], temp_4);
            node_count++;
            //printf("%s\n", temp_4);
            break;
        }
    }

    fgets(line, sizeof(line), FILENAME);
    while (strstr(line, "assign") != NULL) {
        fgets(line, sizeof(line), FILENAME);
    }

    fgets(line, sizeof(line), FILENAME);
    char* temp_5;
    while (strstr(line, "end") == NULL) {
        temp_5 = strtok(line, "<= ");
        temp_5 = strtok(NULL, "<= ");
        removeSubstr(temp_5, ";");
	    removeSubstr(temp_5, "\n");
        strcpy(out_arr[out_cnt], temp_5);
        out_cnt++;
        fgets(line, sizeof(line), FILENAME);
    }

    fclose(FILENAME);
}
