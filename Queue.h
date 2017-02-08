//
// Created by 金石 张 on 17/2/7.
//

#ifndef BANKSYSTEM_QUEUE_H
#define BANKSYSTEM_QUEUE_H

#include "Event.h"

template <typename T>
class Queue {
public:
    Queue() {
        this->front = new T;
        if(!this->front)    //申请内存失败，则程序退出
            exit(-1);
        this->front->next = NULL;   //节点类型中需要包含next这一成员
        this->rear = this->front;
    }
    ~Queue() {
        Queue::clearQueue();
        this->front = NULL;
    }
    void clearQueue(){
        T *tmp;
        while(this->front->next) { //头结点不变，一直删除头结点之后的一个节点（如果该节点不为空的话）
            tmp = this->front->next;
            this->front->next = tmp->next;
            delete tmp;
        }
        this->front->next = NULL; //可删除该句？
        this->rear = this->front;
    }
    T* enqueue(T &node) {
        T *tmp = new T;
        if(!tmp)
            exit(-1);
        *tmp = node;
        this->rear->next = tmp;
        this->rear = tmp;
    }
    T* dequque(){
        if(!this->front->next)
            return NULL;
        T *tmp = this->front->next;
        this->front->next = tmp->next;
//    delete tmp; 注意出队并不需要真的删除节点
        if(tmp == this->rear)   //如果只有一个节点，那该节点有rear指着，出队后需要把该尾指针移开，否则会内存泄露
            this->rear = this->front;
        return tmp;
    }
    T* orderEnqueue(Event &event) { //专为事件队列设计
        Event *tmp = new Event;
        if(!tmp)
            exit(-1);
        *tmp = event;
        T *pos = this->front;
        //保持队列中越前的节点occur_time越小
        while(pos->next && pos->next->occur_time < event.occur_time) { //要插在pos之后（用了一贯的保存前一个节点信息的方法）
            pos = pos->next;
        }
        tmp->next = pos->next;
        pos->next = tmp;
        return this->front;
    }
    int length() {
        int count = 0;
        T *tmp = this->front->next;
        while(tmp){
            ++count;
            tmp = tmp->next;
        }
        return count;
    }

private:
    T *front;
    T *rear;
};


#endif //BANKSYSTEM_QUEUE_H
