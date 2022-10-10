#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;                                                         //no.of.jobs
    static float timer = 0;                                        //timeline
    int possicounter = 0;                                          //NO.OF.PROCESS AVAILABLE AFTER A PROCESS IS FINISHED
    float fullwaitingtime = 0;
    float fulltattime = 0;
    printf("NO OF JOBS : ");
    scanf("%d",&n);

    int * job_burst_time = (int *)malloc(n*sizeof(int));           //CREATE ARRAY FOR BURST TIME
    int * job_arrival_time = (int *)malloc(n*sizeof(int));         //CREATE ARRAY OF ARRIVAL TIME
    int * job_turnaround_time = (int *)malloc(n*sizeof(int));      //CREATE TURNAROUNDTIME ARRAY
    int * completion_time = (int *)malloc(n*sizeof(int));          //CREATE COMPLETION TIME ARRAY
    int * waiting_time = (int *)malloc(n*sizeof(int));             //CREATE WAITING TIME ARRAY
    int * order_of_exec = (int *)malloc(n*sizeof(int));            //CREATE A SPECIAL ARRAY THAT WILL BE USED TO STORE PROCESSES IN THE ORDER THEY WILL BE EXECUTED
    int * possiblity_index= (int *)malloc(n*sizeof(int));          //CREATE A ARRAY THAT STORES ALL THE PROCESSES AVAILABLE AFTER A PROCESS

    for (int i = 0; i < n; i++){
        printf("\nArrival Time of Job %d : ",(i+1));               //TAKE ARRIVAL TIME
        scanf("%d",&job_arrival_time[i]);
    }

    for (int i = 0; i < n ; i++){
        printf("\nBurst Time of Job %d : ",(i+1));                  //TAKE BURST TIME
        scanf("%d",&job_burst_time[i]);
    }

    for (int i =0; i<n; i++){                                       //INITIALISE THE ORDER OF EXECUTION TO 1 TO LAST FOR NOW
        order_of_exec[i] = i+1;
    }

    void exchange(int ia,int xa){                                   //EXCHANGE FUNCTION TO SWAP TWO PROCESSES IN EXECUTION ORDER
        int temp;

        temp = job_burst_time[ia];
        job_burst_time[ia] = job_burst_time[xa];
        job_burst_time[xa] = temp;

        temp = job_arrival_time[ia];
        job_arrival_time[ia] = job_arrival_time[xa];
        job_arrival_time[xa] = temp;

        temp = order_of_exec[ia];
        order_of_exec[ia] = order_of_exec[xa];
        order_of_exec[xa] = temp;
    }

    void execute(int ia){                                            //EXECUTE A GIVEN PROCESS
        if (job_arrival_time[ia] > timer){
            timer = job_arrival_time[ia];
        }
        waiting_time[ia] = timer - job_arrival_time[ia];
        timer = timer + job_burst_time[ia];
        completion_time[ia] = timer;
        job_turnaround_time[ia] = completion_time[ia] - job_arrival_time[ia];
    }

    void checkpossi(int ia){                                        //CHECK WHAT PROCESS ARE AVAILABLE AFTER A PARTICULAR PROCESS AND STORE THEM IN possibility_index
        int k = 0;
        int size = 0;
        possicounter = 0;

        for (int j = ia + 1; j < n ; j++){
            if (job_arrival_time[j] <= timer){
                possicounter++;
            }
        }

        possiblity_index =(int *)malloc(possicounter*sizeof(int));

        for (int j = ia + 1; j < n ; j++){
            if (job_arrival_time[j] <= timer){
                possiblity_index[k] = j;
                k++;
            }
        }
    }

    int bestburst(){                                                //FIND THE BEST BURST TIME OF ALL THE PROCESSE'S AVILABLE
        int best = possiblity_index[0];
        int x = 0;

        for (int i = 0; i < possicounter; i++){
            for(int x = i+1; x<possicounter; x++){
                if(job_burst_time[possiblity_index[i]] > job_burst_time[possiblity_index[x]]){
                    best = possiblity_index[x];
                    i = x-1;
                    break;
                }
            }
        }
        return best;
    }

    int flag = 0;
    checkpossi(0);
    int bestarrival = 0;
    for (int i = 0; i < n; i++){
        if (job_arrival_time[i] < job_arrival_time[0]){
            bestarrival = i;
            flag = 1;
        }
    }

    if (flag == 0){
        for (int i = 0; i < n; i++){
        if (job_arrival_time[i] == job_arrival_time[0]){
               if (job_burst_time[i] < job_burst_time[0]){
                    exchange(i,0);
               }
            }
        }
    }
    exchange(0,bestarrival);

    for (int i = 0; i<n; i++){                                       //THE MAIN FUNCTION
        execute(i);
        checkpossi(i);
        if (i+1 < n){
        exchange(i+1,bestburst());
        }
    }
    //EVERYTING AHEAD IS OUTPUT
    printf("\n\n\nORDER OF EXECUTION ->");
    for (int i = 0; i < n ; i++){
        printf("process no. %d, ",order_of_exec[i]);
    }
    printf("\n\n");
    for (int i =0; i<n; i++){
        printf("Waiting Time of Process %d -> %d\n",order_of_exec[i],waiting_time[i]);
        fullwaitingtime = fullwaitingtime + waiting_time[i];
    }

    printf("\n");
    for (int i =0; i<n; i++){
        printf("Completion Time of Process %d -> %d\n",order_of_exec[i],completion_time[i]);
    }

    printf("\n");
    for (int i =0; i<n; i++){
        printf("Turn Around Time of Process %d -> %d\n",order_of_exec[i],job_turnaround_time[i]);
        fulltattime = fulltattime + job_turnaround_time[i];
    }

    printf("\n");
    printf("Avg Waiting Time -> %f",fullwaitingtime/n);
    printf("\n");
    printf("Avg Turnaround Time -> %f",(fulltattime/n));
    printf("\n");
    printf("Throughput -> %f",(float)(timer/n));
    printf("\n");
    printf("Execution Time 5-> %f",timer);
    printf("\n");

    return 0;
}
