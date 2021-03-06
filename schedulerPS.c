#include <stdint.h>
#include <stdlib.h>
#include "scheduler.h"
#include "job.h"
#include "linked_list.h"

// PS scheduler info
typedef struct {
    /* IMPLEMENT THIS */
} scheduler_PS_t;

// Creates and returns scheduler specific info
void* schedulerPSCreate()
{
    scheduler_PS_t* info = malloc(sizeof(scheduler_PS_t));
    if (info == NULL) {
        return NULL;
    }
    /* IMPLEMENT THIS */
    return info;
}

// Destroys scheduler specific info
void schedulerPSDestroy(void* schedulerInfo)
{
    scheduler_PS_t* info = (scheduler_PS_t*)schedulerInfo;
    /* IMPLEMENT THIS */
    free(info);
}

// Called to schedule a new job in the queue
// schedulerInfo - scheduler specific info from create function
// scheduler - used to call schedulerScheduleNextCompletion and schedulerCancelNextCompletion
// job - new job being added to the queue
// currentTime - the current simulated time
void schedulerPSScheduleJob(void* schedulerInfo, scheduler_t* scheduler, job_t* job, uint64_t currentTime)
{
    scheduler_PS_t* info = (scheduler_PS_t*)schedulerInfo;
    /* IMPLEMENT THIS */
}

// Called to complete a job in response to an earlier call to schedulerScheduleNextCompletion
// schedulerInfo - scheduler specific info from create function
// scheduler - used to call schedulerScheduleNextCompletion and schedulerCancelNextCompletion
// currentTime - the current simulated time
// Returns the job that is being completed
job_t* schedulerPSCompleteJob(void* schedulerInfo, scheduler_t* scheduler, uint64_t currentTime)
{
    scheduler_PS_t* info = (scheduler_PS_t*)schedulerInfo;
    /* IMPLEMENT THIS */
    return NULL;
}
