//
// Created by 金石 张 on 17/2/7.
//

#include "QueueSystem.h"

QueueSystem::QueueSystem(int total_service_time, int window_num):
        total_service_time(total_service_time),
        window_num(window_num),
        total_customer_stay_time(0),
        total_customer_num(0) {
        this->windows = new ServiceWindow[window_num];  // 创建服务窗口
}
QueueSystem::~QueueSystem() {
    delete[] this->windows;
}
void QueueSystem::simulate(int simulate_num) {
    double sum = 0;
    for(int i = 0; i < simulate_num; ++i) {
        sum += run();
    }
    avg_stay_time = (double)sum / simulate_num;
    avg_customers = (double)total_customer_num / (total_service_time * simulate_num);
}
void QueueSystem::init() {
    Event *event = new Event;   //第一个事件肯定是到达事件，用默认构造
    current_event = event;
}
double QueueSystem::run() {
    this->init();   //注意需要在run中先初始化，不然还得放到外层去做初始化的工作
    while(current_event) {
        if(current_event->event_type == -1)
            customerArrived();
        else
            customerDeparture();
        delete current_event;
        current_event = event_list.dequque();   //获取新的事件
    }
    this->end();
    return static_cast<double>(total_customer_stay_time / total_customer_num);   //返回顾客的平均逗留时间
}
void QueueSystem::end() {
    //所有成员回到初始状态
    for(int i = 0; i < window_num; ++i) //不用删除window,但需要全置为空闲
        windows[i].setIdle();
    current_event = NULL;
    customer_list.clearQueue();
    event_list.clearQueue();
}
void QueueSystem::customerArrived() {
    ++total_customer_num;

    //创建下一个顾客到达的事件，注意不是在模拟一开始就将一整天的时间全都创建好的
    //int inter_time = Random::uniform(100);
    // 下一个顾客到达的时间间隔，假设平均每分钟到两个顾客，则据排队理论，平均间隔时间服从参数为 2 的泊松
    int inter_time = Random::getRandom(POISSON, 0.5);
    Event event(inter_time + current_event->occur_time);

    if(event.occur_time < total_service_time)
        event_list.orderEnqueue(event);

    //处理当前的到达事件
    Customer *customer = new Customer(current_event->occur_time);   //为该事件产生一个顾客
    if(!customer)
        exit(-1);
    customer_list.enqueue(*customer);

    //只有在来了一个顾客后才从顾客队列中删除一个顾客送去服务是否合理？——>并非如此，离开事件也会触发
    int idle_index = getIdleServiceWindow();
    if(idle_index >= 0) {
        customer = customer_list.dequque();
        windows[idle_index].serveCustomer(*customer);
        windows[idle_index].setBusy();

        // 顾客到窗口开始服务时，就需要插入这个顾客的一个离开事件到 event_list 中
        Event leave_event(current_event->occur_time + customer->duration, idle_index);
        event_list.orderEnqueue(leave_event);
    }
    //完成服务，删除该顾客的资源
    delete customer;
}
int QueueSystem::getIdleServiceWindow() {
    for (int i=0; i!=window_num; ++i) {
        if (windows[i].isIdle()) {
            return i;
        }
    }
    return -1;
}
void QueueSystem::customerDeparture() {
    // 如果离开事件的发生时间比中服务时间大，我们就不需要做任何处理
    if(current_event->occur_time < total_service_time) {
        //所有顾客逗留时间 = （当前顾客离开事件发生的时间 - 顾客的到达事件发生时间）的累加
        total_customer_stay_time += current_event->occur_time - windows[current_event->event_type].getArrivaltime();
        //当前事件处理好了，还需产生下一个事件(当前顾客走了，处理下一个)
        if(customer_list.length()) {
            Customer *customer = customer_list.dequque();
            windows[current_event->event_type].serveCustomer(*customer);
//            windows[current_event->event_type].setBusy(); //可不用加，本来也就是忙的
            //注意需要同时为该新服务的顾客产生离开事件
            Event leave_event(
                     current_event->occur_time + customer->duration,
                     current_event->event_type);
            event_list.orderEnqueue(leave_event);

            delete customer;
        } else {
            // 如果队列没有人，且当前窗口的顾客离开了，则这个窗口是空闲的
            windows[current_event->event_type].setIdle();
        }
    }
}