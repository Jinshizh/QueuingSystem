//
// Created by 金石 张 on 17/2/7.
//

#ifndef BANKSYSTEM_NODE_H
#define BANKSYSTEM_NODE_H

#include "Random.h"

#define RANDOM_PARAMETER 100

struct Node {
    int arrival_time;
    int duration;
    struct Node* next;

    Node(int arrival_time = 0,
         int duration = Random::uniform(RANDOM_PARAMETER)): //duration是在0到100随机的
            arrival_time(arrival_time),
            duration(duration),
            next(NULL){}
};

typedef struct Node Node;
typedef struct Node Customer;


#endif //BANKSYSTEM_NODE_H
