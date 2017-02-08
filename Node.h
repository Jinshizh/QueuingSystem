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
         //int duration = Random::uniform(RANDOM_PARAMETER)): //duration是在0到100随机的
         int duration = Random::getRandom(EXPONENTAIL, 0.1)): //假设平均服务时间是10分钟，则服务时间应符合参数为1/10的指数分布
            arrival_time(arrival_time),
            duration(duration),
            next(NULL){}
};

typedef struct Node Node;
typedef struct Node Customer;


#endif //BANKSYSTEM_NODE_H
