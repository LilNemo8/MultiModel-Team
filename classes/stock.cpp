#include "stock.h"

stock::stock(std::string name){
    this->name = name;
    share_price = 0;
    stock_count = 0;
}



stock::~stock(){ return; }
