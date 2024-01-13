#ifndef UNTITLED_OS_SCHED_STATES_H
#define UNTITLED_OS_SCHED_STATES_H

#define NUMBER_OF_SCHED_STATES 6

enum sched_states {
    NEW = 0,
    RUNNABLE,
    ON_CPU,
    WAIT,
    EXIT,
    UNUSED
};

#endif
