#ifndef STOCK_H
#define STOCK_H

#include "../helper/functions.h"
#include <vector>   // NEW: for std::vector

struct stock{
    std::string name;
    double share_price;
    int stock_count;

    // yearly percentage returns for this stock (2014–2024)
    // e.g. 44.25 means +44.25%
    std::vector<double> yearly_returns;

    // first year in the data table
    static const int BASE_YEAR = 2014;

    // constructor: name + all yearly returns
    stock(std::string name, const std::vector<double>& returns);

    ~stock();

    // apply this stock's % return for a given calendar year (e.g. 2014)
    void apply_return_for_year(int year){
        int idx = year - BASE_YEAR;
        if (idx < 0 || idx >= (int)yearly_returns.size()) return;

        double r = yearly_returns[idx] / 100.0; // convert % to decimal
        share_price *= (1.0 + r);
    }
};

#endif
