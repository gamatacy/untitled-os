//
// Created by ShipOS developers on 28.10.23.
// Copyright (c) 2023 SHIPOS. All rights reserved.
//

#ifndef UNTITLED_OS_SHEDULER_H
#define UNTITLED_OS_SHEDULER_H
#include "proc.h"
#include "threads.h"
#define ROUNDS_PER_PROC 5

void scheduler(void);
void yield(void);

#endif //UNTITLED_OS_SHEDULER_H
