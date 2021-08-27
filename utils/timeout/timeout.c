// code retrieved from https://stackoverflow.com/questions/5237482/how-do-i-execute-external-program-within-c-code-in-linux-with-arguments/5237520

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAT_RUNS 10
#define STR_LEN 50
#define NO_ARGS 4
#define ABORT_TIME 500 // in ms
#define MAX_STATUS 3
#define FINISH  0
#define ABORT   1
#define FAIL    2

#define WAIT_FOR_COMPLETION

unsigned int exec_prog(char **argv, unsigned int abort_time)
{
    pid_t   my_pid;
    int     status, timeout /* unused ifdef WAIT_FOR_COMPLETION */;

    if (0 == (my_pid = fork())) {
        if (-1 == execve(argv[0], (char **)argv , NULL)) {
            perror("child process execve failed [%m]");
            return FAIL;
        }
    }

#ifdef WAIT_FOR_COMPLETION
    timeout = abort_time;

    while (0 == waitpid(my_pid , &status , WNOHANG)) {
        if ( --timeout < 0 ) {
            perror("timeout");
            kill(my_pid, SIGINT);
            return ABORT;
        }
        usleep(1000); // wait for 1 ms
    }
#endif

    return FINISH;
}

int main () {

    unsigned int i, rc;
    char    *my_argv[NO_ARGS];
    for (i = 0; i < NO_ARGS; i++)
        my_argv[i] = (char *)malloc(sizeof(char)*STR_LEN);

    unsigned int status[MAX_STATUS];
    for (i = 0; i < MAX_STATUS; i++)
        status[i] = 0;

    strcpy(my_argv[0], "../sat-solver/glucose");
    my_argv[3] = NULL;

    i = 0;
    while (i < SAT_RUNS) {
        sprintf(my_argv[1], "../cnf-examples/sat-%d.cnf", i);
        sprintf(my_argv[2], "../cnf-examples/res-%d.txt", i);
        rc = exec_prog(my_argv, ABORT_TIME);
        status[rc]++;
        i++;
    }

    printf("\nStatistics for %d SAT runs\n", SAT_RUNS);
    printf("Finish:\t%d\n", status[FINISH]);
    printf("Abort:\t%d\n", status[ABORT]);
    printf("Fail:\t%d\n", status[FAIL]);

    for (i = 0; i < NO_ARGS; i++)
        free(my_argv[i]);
}
