#ifndef STOCK_H
#define STOCK_H

#include "../helper/functions.h"

struct stock{
    std::string name;
    double share_price;
    int stock_count;

    // stock();
    stock(std::string name);
    ~stock();




    // void graph();



};


#endif