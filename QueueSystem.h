//
// Created by 金石 张 on 17/2/7.
//
//QueueSystem 主要是由event队列驱动的，根据事件来决定做什么操作

#ifndef BANKSYSTEM_QUEUESYSTEM_H
#define BANKSYSTEM_QUEUESYSTEM_H

#include "Node.h"
#include "Queue.h"
#include "ServiceWindow.h"

class QueueSystem {
public:
    // 初始化队列系统
    QueueSystem(int total_service_time, int window_num);

    // 销毁
    ~QueueSystem();

    // 启动模拟
    void simulate(int simulate_num);

    inline double getAvgStayTime() const {
        return avg_stay_time;
    }
    inline double getAvgCustomers() const {
        return avg_customers;
    }

private:
    // 让队列系统运行一次
    double run();

    // 初始化各种参数
    void init();

    // 清空各种参数
    void end();

    // 获得空闲窗口索引
    int getIdleServiceWindow();

    // 处理顾客到达事件
    void customerArrived();

    // 处理顾客离开事件
    void customerDeparture();

    // 服务窗口的总数
    int window_num;

    // 总的营业时间
    int total_service_time;

    // 所有顾客的逗留总时间
    int total_customer_stay_time;

    // 总顾客数
    int total_customer_num;

    // 核心成员
    ServiceWindow*  windows;
    Queue<Customer> customer_list;
    Queue<Event>       event_list;
    Event*          current_event;

    // 给外部调用的结果
    double avg_customers;   //营业时间内平均每分钟的顾客数
    double avg_stay_time;   //顾客在银行的平均逗留时间（离开时间减去到达时间）
};


#endif //BANKSYSTEM_QUEUESYSTEM_H
