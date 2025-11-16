#include "stock.h"

stock::stock(std::string name, const std::vector<double>& returns){
    this->name = name;
    share_price = 100.0;      // start each stock at $100 in 2014
    stock_count = 0;
    yearly_returns = returns;
}

stock::~stock(){ return; }


void stock::print(bool user, int year){
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\tShare Price: $"<< share_price << '\n'; 
    if(user){
        std::cout << "\tLast Year Returns: " << yearly_returns[year - 2014] << "%\n"; 
        std::cout << "\tStock Count: " <<  stock_count ; 
    }
    std::cout << '\n';
}


void stock::apply_return_for_year(int year){
    int idx = year - BASE_YEAR + 1;
    if (idx < 0 || idx >= (int)yearly_returns.size()) return;

    double r = yearly_returns[idx] / 100.0; // convert % to decimal
    share_price *= (1.0 + r);
}