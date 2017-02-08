//
// Created by 金石 张 on 17/2/7.
//

#ifndef BANKSYSTEM_SERVICEWINDOW_H
#define BANKSYSTEM_SERVICEWINDOW_H

#include "Node.h"

enum WindowStatus {
    SERVICE,
    IDLE,
};

class ServiceWindow {
public:
    inline ServiceWindow(){
        window_status = IDLE;
    }
    inline bool isIdle() const {
        return (window_status == IDLE)?true:false;
    }
    inline void setIdle() {
        window_status = IDLE;
    }
    inline void setBusy() {
        window_status = SERVICE;
    }
    inline void serveCustomer(Customer &customer) {
        this->customer = customer;
    }
    inline int getArrivaltime() const {
        return customer.arrival_time;
    }
    inline int getDuration() const {
        return customer.duration;
    }


private:
    WindowStatus window_status;
    Customer customer;
};


#endif //BANKSYSTEM_SERVICEWINDOW_H
