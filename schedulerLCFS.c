#include <stdint.h>
#include <stdlib.h>
#include "scheduler.h"
#include "job.h"
#include "linked_list.h"

// LCFS scheduler info
typedef struct {
    /* IMPLEMENT THIS */
    list_t* llist;
    job_t* sjob;
    list_node_t* newCurr;
} scheduler_LCFS_t;

// Creates and returns scheduler specific info
void* schedulerLCFSCreate()
{
    scheduler_LCFS_t* info = malloc(sizeof(scheduler_LCFS_t));
    if (info == NULL) {
        return NULL;
    }
    /* IMPLEMENT THIS */
    list_t* list = list_create(NULL);

    info->llist = list;
    info->sjob = NULL;


    return info;
}

// Destroys scheduler specific info
void schedulerLCFSDestroy(void* schedulerInfo)
{
    scheduler_LCFS_t* info = (scheduler_LCFS_t*)schedulerInfo;
    /* IMPLEMENT THIS */

    list_destroy(info->llist);
    free(info);
}

// Called to schedule a new job in the queue
// schedulerInfo - scheduler specific info from create function
// scheduler - used to call schedulerScheduleNextCompletion and schedulerCancelNextCompletion
// job - new job being added to the queue
// currentTime - the current simulated time
void schedulerLCFSScheduleJob(void* schedulerInfo, scheduler_t* scheduler, job_t* job, uint64_t currentTime)
{
    scheduler_LCFS_t* info = (scheduler_LCFS_t*)schedulerInfo;
    /* IMPLEMENT THIS */

    size_t count = list_count(info->llist);

    if (count == 0) //means there is no job so we move forward with this job, start of the queue
    {
        info->sjob = job; //first element in queue
        list_insert(info->llist, job); //acts as list and data, then insert in queue
        info->newCurr = list_head(info->llist); //new head with the new list
        schedulerScheduleNextCompletion(scheduler, currentTime + jobGetJobTime(job));
    }
    else if(info->sjob != NULL) //there is jobs already so put in queue
    {
        list_insert(info->llist, job);
    }

}

// Called to complete a job in response to an earlier call to schedulerScheduleNextCompletion
// schedulerInfo - scheduler specific info from create function
// scheduler - used to call schedulerScheduleNextCompletion and schedulerCancelNextCompletion
// currentTime - the current simulated time
// Returns the job that is being completed
job_t* schedulerLCFSCompleteJob(void* schedulerInfo, scheduler_t* scheduler, uint64_t currentTime)
{
    scheduler_LCFS_t* info = (scheduler_LCFS_t*)schedulerInfo;
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

        list_node_t* nhead = list_head(info->llist);//new node which is the next head
        info->newCurr = nhead;
        schedulerScheduleNextCompletion(scheduler, currentTime + jobGetJobTime(list_data(nhead))); //gets the new tail

        return tempdata;

    }
    return NULL;
}
