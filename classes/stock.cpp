#include "stock.h"

stock::stock(std::string name, const std::vector<double>& returns){
    this->name = name;
    share_price = 100.0;      // start each stock at $100 in 2014
    stock_count = 0;
    yearly_returns = returns;
}

stock::~stock(){ return; }
