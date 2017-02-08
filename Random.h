//
// Created by 金石 张 on 17/2/6.
//

#ifndef BANKSYSTEM_RANDOM_H
#define BANKSYSTEM_RANDOM_H

#include <cstdlib>
#include <cmath>

class Random {
public:
    static double uniform(double max = 1) {
        return ((double)std::rand() / RAND_MAX) * max;
    }
};
#endif //BANKSYSTEM_RANDOM_H
