#include <iostream>
#include "Random.h"
#include "Queue.h"
#include "Node.h"
#include "QueueSystem.h"

int main() {
    std::cout << Random::uniform(5) << std::endl;

    std::srand((unsigned int)std::time(0));

    int total_service_time = 240; //8点到12点的服务时间 换成分钟
    int window_num = 4; //窗口数量
    int simulate_num = 10000;


/*    *//*Queue test*//*
    Queue<Node> q; //
    for(int i=0;i<5;i++){
        Node *tmp = new Node(i);
        std::cout<<q.enqueue(*tmp)->arrival_time;
    }
    for(int i=0;i<5;i++)
        std::cout<<q.dequque()->arrival_time;*/

    QueueSystem system(total_service_time, window_num);
    system.simulate(simulate_num);

    std::cout << "The average time of customer stay in bank: "
              << system.getAvgStayTime() << std::endl;
    std::cout << "The number of customer arrive bank per minute: "
              << system.getAvgCustomers() << std::endl;

    return 0;
}