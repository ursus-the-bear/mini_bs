//
//  main.c
//  mini_bs
//
//  Created by ursus on 21.03.16.
//  Copyright © 2016 Ursus Schneider. All rights reserved.
//

#include <stdio.h>

typedef struct _tasks tasks_t;

typedef void (* initFunction) (tasks_t * self, uint taskID);
typedef void (* pollFunction) (tasks_t * self);
typedef void (* processEventFunction) (tasks_t * self, uint16_t eventID);

typedef struct _tasks {
    
    initFunction init;
    pollFunction poll;
    processEventFunction processEvent;
    
    uint taskID;
    
} tasks_t;

void init1 (tasks_t * self, uint taskID) {
    self->taskID = taskID + 5;
    printf ("In init 1. taskID = %i\n", self->taskID);
}
void init2 (tasks_t * self, uint taskID) {
    self->taskID = taskID + 7;
    printf ("In init 2. taskID = %i\n", self->taskID);
}
void init3 (tasks_t * self, uint taskID) {
    self->taskID = taskID + 12;
    printf ("In init 3. taskID = %i\n", self->taskID);
}
void poll1 (tasks_t * self) {
    printf ("In poll 1. taskID = %i\n", self->taskID);
}
void poll2 (tasks_t * self) {
    printf ("In poll 2. taskID = %i\n", self->taskID);
}
void poll3 (tasks_t * self) {
    printf ("In poll 3. taskID = %i\n", self->taskID);
}
void processEvent1 (tasks_t * self, uint16_t eventID) {
    printf ("in processEvent 1. taskID = %i. Event received: %i\n", self->taskID, eventID);
}
void processEvent2 (tasks_t * self, uint16_t eventID) {
    printf ("in processEvent 2. taskID = %i. Event received: %i\n", self->taskID, eventID);
}
void processEvent3 (tasks_t * self, uint16_t eventID) {
    printf ("in processEvent 3. taskID = %i. Event received: %i\n", self->taskID, eventID);
}

tasks_t taskList [10];

void os_sendEvent (int noTasks, uint taskID, uint16_t eventID) {

    for (int i = 0; i <= noTasks; i++)
        if (taskList [i].taskID == taskID)
            taskList [i].processEvent (&taskList [i], eventID);
}


int main(int argc, const char * argv[]) {
    
    // setup your task list -> known at start of system
    taskList [0].init = &init1;
    taskList [0].poll = &poll1;
    taskList [0].processEvent = &processEvent1;
    
    taskList [1].init = &init2;
    taskList [1].poll = &poll2;
    taskList [1].processEvent = &processEvent2;

    taskList [2].init = &init3;
    taskList [2].poll = &poll3;
    taskList [2].processEvent = &processEvent3;
    
    
    // call the init
    for (int i = 0; i <= 2; i++)
        taskList [i].init (&taskList [i], i);
    
    // while (1 == 1) {
        
        for (int i = 0; i <= 2; i++)
            taskList [i].poll (&taskList [i]);
        
        os_sendEvent(1, 8, 100);
        
    // }
    
}
