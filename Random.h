//
// Created by 金石 张 on 17/2/6.
//

#ifndef BANKSYSTEM_RANDOM_H
#define BANKSYSTEM_RANDOM_H

#include <cstdlib>
#include <cmath>
enum RandomType {
    UNIFORM,
    EXPONENTAIL,
    POISSON,
};
class Random {
public:
    // 给定分布类型和参数，获得随机值
    static double getRandom(RandomType type, double parameter) {
        switch (type) {
            case UNIFORM:
                return uniform(parameter);
                break;
            case EXPONENTAIL:
                return exponentail(parameter);
            case POISSON:
                return poisson(parameter);
            default:
                return 0;
                break;
        }
    }
    static double uniform(double max = 1) {
        return ((double)std::rand() / RAND_MAX) * max;
    }
    // 服从 lambda-指数分布的随机值
    static double exponentail(double lambda) {
        return -log(1 - uniform()) / lambda;
    }
    // 服从 lambda-泊松分布的随机值
    static double poisson(double lambda) {
        int t = 0;
        double p = exp(-lambda);
        double f = p;
        double u = uniform();
        while (true) {
            if (f > u)
                break;
            t++;
            p = p*lambda / t;
            f += p;
        }
        return t;
    }
};
#endif //BANKSYSTEM_RANDOM_H
