/*
====================================================
ST5004CEM Operating Systems and Security

Task 1: Process Management and Threading

Features:
- Process creation using fork()
- Multithreading using pthread
- Mutex synchronization
- Semaphore synchronization
- Round Robin scheduling simulation
- Race condition prevention
- Deadlock prevention

====================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>


#define NUM_THREADS 3
#define TOTAL_TASKS 9


// Shared resources
int counter = 0;
int taskIndex = 0;

int tasks[TOTAL_TASKS] = {1,2,3,4,5,6,7,8,9};


// Synchronization tools
pthread_mutex_t mutex;
sem_t semaphore;



/*
----------------------------------------------------
Process Creation

Creates a child process using fork().
Parent waits until child finishes.
----------------------------------------------------
*/
void createProcess()
{
    pid_t pid = fork();

    if(pid < 0)
    {
        printf("Process creation failed\n");
        exit(1);
    }

    else if(pid == 0)
    {
        printf("\nChild Process Created\n");
        printf("Child PID: %d\n", getpid());
        exit(0);
    }

    else
    {
        wait(NULL);
        printf("Parent Process Continued\n");
    }
}



/*
----------------------------------------------------
Thread Function

Each thread takes a task from shared task list.

Mutex prevents race condition while accessing
shared variables.

Semaphore limits simultaneous execution.
----------------------------------------------------
*/
void *worker(void *arg)
{
    int threadID = *(int *)arg;


    while(1)
    {

        // Limit number of active threads
        sem_wait(&semaphore);


        // Critical section
        pthread_mutex_lock(&mutex);


        if(taskIndex >= TOTAL_TASKS)
        {
            pthread_mutex_unlock(&mutex);
            sem_post(&semaphore);
            break;
        }


        int task = tasks[taskIndex];
        taskIndex++;


        counter++;


        printf("Thread %d executed Task %d | Counter = %d\n",
               threadID, task, counter);



        pthread_mutex_unlock(&mutex);

        sem_post(&semaphore);


        sleep(1);
    }


    pthread_exit(NULL);
}



/*
----------------------------------------------------
Round Robin Scheduler Simulation

Each process receives a fixed time quantum.
Processes are executed repeatedly until completion.
----------------------------------------------------
*/
void roundRobin()
{

    printf("\nRound Robin Scheduling\n");


    int burst[] = {5,3,7};
    int remaining[3];


    for(int i=0;i<3;i++)
    {
        remaining[i]=burst[i];
    }


    int quantum = 2;
    int completed;


    do
    {
        completed = 1;


        for(int i=0;i<3;i++)
        {

            if(remaining[i] > 0)
            {
                completed = 0;


                printf("Process P%d running\n",i+1);


                if(remaining[i] > quantum)
                {
                    remaining[i] -= quantum;
                }

                else
                {
                    remaining[i]=0;
                    printf("Process P%d completed\n",i+1);
                }
            }
        }

    }while(!completed);

}



/*
----------------------------------------------------
Main Function
----------------------------------------------------
*/
int main()
{

    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];


    printf("===== Process Management =====\n");


    createProcess();



    // Initialize synchronization objects

    pthread_mutex_init(&mutex,NULL);

    sem_init(&semaphore,0,2);



    printf("\n===== Thread Execution =====\n");


    // Create 3 threads

    for(int i=0;i<NUM_THREADS;i++)
    {
        ids[i]=i+1;


        pthread_create(
            &threads[i],
            NULL,
            worker,
            &ids[i]
        );
    }



    // Wait for threads

    for(int i=0;i<NUM_THREADS;i++)
    {
        pthread_join(threads[i],NULL);
    }



    printf("\nFinal Counter Value: %d\n",counter);



    roundRobin();



    /*
    Deadlock prevention:
    - Single mutex used
    - Lock released immediately
    - No circular waiting condition
    */


    printf("\nDeadlock Prevention Applied\n");


    pthread_mutex_destroy(&mutex);

    sem_destroy(&semaphore);



    printf("\nProgram Completed Successfully\n");


    return 0;
}
