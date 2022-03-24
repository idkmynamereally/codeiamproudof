#include <stdio.h>
#include <stdlib.h>

//PROBLEM - insert_available_to_ready() adn ready_not_empty are adding the same process twoce


static int timer;
int total_process;


struct process {
    int process_id;
    int arrival_time;
    int priority;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    struct process * next;
    struct process * previous;
};

struct ready_process{
    struct process * the_process;
    struct ready_process * next;
    struct ready_process * previous;
};

struct process * first_all = NULL;
struct process * new_process = NULL;
struct process * ptr = NULL;

struct ready_process * first_ready = NULL;
struct ready_process * ptr_ready = NULL;
struct ready_process * new_ready_block = NULL;


int main(){
    timer = 0;
    printf("TOTAL NUMBER OF PROCESS : ");
    scanf("%d",&total_process);

    for (int i = 1; i <= total_process; i++){
        insert_new_process_to_all(i);
    }

    while (alldone()){
        insert_available_to_ready();

        ready_empty();

        sort_ready();

        execute(first_ready->the_process);
        struct ready_process * garbage = first_ready;     //MOVE TO NEXT READY BLOCK
        if (first_ready->next != NULL){                   //IF READY ONLY HAS ONE ELEMENT THEN MAKE IT NULL
            first_ready = first_ready->next;
            first_ready->previous = NULL;
            free(garbage);
        }

        else{                                             //ELSE MOVE TO NEXT ELEMENT
            first_ready = NULL;
            free(garbage);
        }
    }

    printf("\n\nPROCESS NO\tARRIVAL TIME\tCOMPLETION TIME\tTURNAROUND TIME\tPRIORITY");
    print_process();

return 0;
}


void print_process(){
    printf("\n");
    for (ptr = first_all; ptr!=NULL;ptr = ptr->next){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",ptr->process_id,ptr->arrival_time,ptr->completion_time,ptr->turn_around_time,ptr->priority);
    }
}

int alldone(){
    for (ptr = first_all; ptr!=NULL; ptr = ptr->next){
        if (ptr->burst_time!=0){
            return 1;
        }
    }

    return 0;
}

int ready_empty(){                    //IF THR FIRST READY_BLOCK is NULL JUMP TO THE BEST PROCESS AND MAKE FIRST_READYBLOCK
    if (first_ready != NULL){
        return 1;
    }
    struct process * best = NULL;

    for (ptr = first_all; ptr!=NULL; ptr= ptr->next){   //TAKE THE FIRST INCOMPLETE PROCESS AND MAKE IT BEST
        if (ptr->burst_time == 0)
            continue;
        if (ptr->burst_time!=0){
            best = ptr;
            break;
        }
    }

    for (ptr ; ptr!=NULL; ptr = ptr->next){             //FIND THE BEST PROCESS RN IN RESPECT TO AT & PRIORITY
        if (ptr->burst_time == 0)
            continue;
        if (ptr->arrival_time < best->arrival_time)
            best = ptr;
        else if (ptr->arrival_time == best->arrival_time){
            if (ptr->priority > best->priority)
                best = ptr;
        }
    }
    timer = best->arrival_time;                         //MOVE TIME TO THE BEST PROCESS
    insert_available_to_ready();                        //NOW ADD ALL THOSE PROCESS
    return 1;
}

void insert_available_to_ready(){               //ADD ALL PROCESSES AVAILABLE AT CURRENT TIME TO READY QUEUE
    for (ptr = first_all; ptr!=NULL; ptr = ptr->next){
        if (ptr->burst_time == 0)
            continue;
        if (ptr->arrival_time <= timer){
            insert_to_ready(ptr);
        }
    }
}

void insert_to_ready(struct process * process_to_add){  //CREATES READY BLOCKS WITH THE PROCESS PROVIDED TO IT
    if (first_ready == NULL){
        new_ready_block = (struct ready_process *)malloc(sizeof(struct ready_process));
        new_ready_block->next = NULL;
        new_ready_block->previous = NULL;
        new_ready_block->the_process = process_to_add;
        first_ready = new_ready_block;
    return;
    }

    for(ptr_ready = first_ready; ptr_ready->next != NULL; ptr_ready = ptr_ready->next);
        new_ready_block = (struct ready_process *)malloc(sizeof(struct ready_process));
        new_ready_block->the_process = process_to_add;
        new_ready_block->previous = ptr_ready;
        new_ready_block->next = NULL;
        ptr_ready->next = new_ready_block;
}

void sort_ready(){          //SORTS READY ON BASIS OF PRIORITy WORKS
    struct ready_process * ptr_ready2;
    struct ready_process * OG;
    for (ptr_ready = first_ready->next; ptr_ready!=NULL; ptr_ready = ptr_ready->next){    //FIRST READY TO LAST
        OG = ptr_ready;
        for (ptr_ready2=ptr_ready->previous; ptr_ready2!=NULL; ptr_ready2 = ptr_ready2->previous){ //FROM CURRENT READY TO FIRST READY
            if ( ptr_ready->the_process->priority > ptr_ready2->the_process->priority){
                swap_ready(ptr_ready2,ptr_ready);
                ptr_ready = ptr_ready2;
            }
        }
        ptr_ready = OG;
    }

return;
}

void swap_ready(struct ready_process * ready1,struct ready_process * ready2){
    struct process * temp = ready1->the_process;
    ready1->the_process = ready2->the_process;
    ready2->the_process = temp;
}

void execute(struct process * pro){
    printf("%d | P%d | ",timer,pro->process_id);
    pro->waiting_time = timer - pro->arrival_time;
    timer = timer + pro->burst_time;
    pro->burst_time = 0;
    pro->completion_time = timer;
    pro->turn_around_time = timer - pro->arrival_time;
    printf("%d\t",timer);
}

void insert_new_process_to_all(int id){
    new_process = (struct process *)malloc(sizeof(struct process));
    take_process(new_process);
    if (first_all == NULL){
        new_process->next = NULL;
        new_process->previous = NULL;
        new_process->process_id = id;
        first_all = new_process;
        return;
    }
    for (ptr = first_all; ptr->next!=NULL; ptr = ptr->next);
    ptr->next = new_process;
    new_process->previous = ptr;
    new_process->next = NULL;
    new_process->process_id = id;
}

void take_process (struct process * pro){
    printf("Enter Process Priority : ");
    scanf("%d",&pro->priority);
    printf("Enter Process Arrival Time : ");
    scanf("%d",&pro->arrival_time);
    printf("Enter Burst Time : ");
    scanf("%d",&pro->burst_time);
    printf("\n\n");
}
