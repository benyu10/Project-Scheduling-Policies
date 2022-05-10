#include <stdint.h>
#include <stdlib.h>
#include "scheduler.h"
#include "job.h"
#include "linked_list.h"

// SJF scheduler info
typedef struct {
    /* IMPLEMENT THIS */

    list_t* llist;
    list_node_t* newCurr;
    job_t* sjob;
} scheduler_SJF_t;



int compare(void* x, void* y);
int jobsize(void* x, void* y);



// Creates and returns scheduler specific info
void* schedulerSJFCreate()
{
    scheduler_SJF_t* info = malloc(sizeof(scheduler_SJF_t));
    if (info == NULL) {
        return NULL;
    }
    /* IMPLEMENT THIS */
    
    info->llist = list_create(jobsize);
    return info;
}

// Destroys scheduler specific info
void schedulerSJFDestroy(void* schedulerInfo)
{
    scheduler_SJF_t* info = (scheduler_SJF_t*)schedulerInfo;
    /* IMPLEMENT THIS */

     list_destroy(info->llist);
    free(info);
}

// Called to schedule a new job in the queue
// schedulerInfo - scheduler specific info from create function
// scheduler - used to call schedulerScheduleNextCompletion and schedulerCancelNextCompletion
// job - new job being added to the queue
// currentTime - the current simulated time
void schedulerSJFScheduleJob(void* schedulerInfo, scheduler_t* scheduler, job_t* job, uint64_t currentTime)
{
    scheduler_SJF_t* info = (scheduler_SJF_t*)schedulerInfo;
    /* IMPLEMENT THIS */

    size_t count = list_count(info->llist);

    if (count == 0) //means there is no job so we move forward with this job, start of the queue
    {
        info->sjob = job; //first element in queue
        int value = compare(job, info->sjob);
        if (value == -1) //if equal, get job with smaller ID
        {
            list_insert(info->llist, job); //acts as list and data, then insert in queue
            info->newCurr = list_find(info->llist, job); //new head with the new list
            schedulerScheduleNextCompletion(scheduler, currentTime + jobGetJobTime(job));
        }
        else
        {
            list_insert(info->llist, job); //acts as list and data, then insert in queue
            info->newCurr = list_find(info->llist, job); //new head with the new list
            schedulerScheduleNextCompletion(scheduler, currentTime + jobGetJobTime(job));
        }
    }
    else if (info->sjob != NULL) //there is jobs already so put in queue
    {
        list_insert(info->llist, job);
    }
}

// Called to complete a job in response to an earlier call to schedulerScheduleNextCompletion
// schedulerInfo - scheduler specific info from create function
// scheduler - used to call schedulerScheduleNextCompletion and schedulerCancelNextCompletion
// currentTime - the current simulated time
// Returns the job that is being completed
job_t* schedulerSJFCompleteJob(void* schedulerInfo, scheduler_t* scheduler, uint64_t currentTime)
{
    scheduler_SJF_t* info = (scheduler_SJF_t*)schedulerInfo;
    /* IMPLEMENT THIS */

    size_t count = list_count(info->llist);
    list_node_t* curr = info->newCurr;

    if(count == 1) //means there is one job left, and we do not need to call scheudle next completion

    {
        job_t* tempdata = curr->data; //store the data of the new head
        list_remove(info->llist, curr);
        info->newCurr = NULL; //sets it to null
        //info->llist->head = info->llist->head->next;
        //list_remove(info->llist, nnode); //erases the node but keeps the data then we can return the data

        return tempdata;
    }

    else if (count >= 2) //means theres more jobs remaining, which is 2 or more, and we set new tail to that
    {
        //list_node_t* nnode = list_head(info->llist); //get the head
        job_t* tempdata = curr->data; //store the data of the head

        //info->llist->head = info->llist->head->next;
        list_remove(info->llist, curr);  //erases the node but keepts the data then we can return the data

        list_node_t* nhead = list_tail(info->llist);//new node which is the next head
        info->newCurr = list_find(info->llist,list_data(nhead));
        schedulerScheduleNextCompletion(scheduler, currentTime + jobGetJobTime(list_data(nhead))); //gets the new tail

        return tempdata;

    }
    
    return NULL;
}

int compare(void* x, void* y)
{
    uint64_t id1 = jobGetId((job_t*)x);
    uint64_t id2 = jobGetId((job_t*)y);

    if (id1 > id2)
    {
        return -1;
    }
    else if(id1 < id2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int jobsize(void* x, void* y)
{
    uint64_t js1 = jobGetJobTime((job_t*)x);
    uint64_t js2 = jobGetJobTime((job_t*)y);

    if (js1 > js2)
    {
        return -1;
    }
    else if(js1 < js2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

