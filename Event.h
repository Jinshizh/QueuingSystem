//
// Created by 金石 张 on 17/2/7.
//

#ifndef BANKSYSTEM_EVENT_H
#define BANKSYSTEM_EVENT_H

#include "Random.h"
#define RANDOM_PARAMETER 100

struct Event {
    int occur_time;

    // 使用 -1 表示到达事件, >=0 表示离开事件, 同时数值表示所离开的服务窗口
    int event_type;

    Event* next;

    // 默认为到达事件，发生事件随机
    //Event(int occur_time = Random::uniform(RANDOM_PARAMETER),
    Event(int occur_time = Random::getRandom(POISSON, 0.5),
          int event_type = -1):
            occur_time(occur_time),
            event_type(event_type),
            next(NULL) {}
};
#endif //BANKSYSTEM_EVENT_H
