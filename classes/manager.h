#ifndef MANAGER_H
#define MANAGER_H

#include "stock.h"

#include <map>


class manager{
    std::map<int, stock*> list; // list stock manager
    int num; // total size

    bool stock_present(); // would tell us if a stock is already present

    public:
    manager(); // constructor
    ~manager(); // destructor


    void add_stock(int num); // add a new stock 
    void delete_stock(int num); // delete specific stock

    
};



#endif