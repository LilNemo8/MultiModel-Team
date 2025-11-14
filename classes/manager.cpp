#include "manager.h"


manager::manager(std::string name){
    initialize_stocks();

    this->name = name;
    capital = 10000;
    stock_capital = 0;
    year = 2015;
} 


manager::~manager(){
    // clear all memory that stocks used in heap [NO MEM LEAKS]
    for(auto& s : stocks){
        delete s.second;
    }

} 


void manager::add_stock(std::string stock){
    // if stock is not present, then we add it
    if(!stock_present(stock)){ user_stocks[stock] = stocks[stock]; }

    //increment stock count
    user_stocks[stock]->stock_count++;

} 



void manager::remove_stock(std::string stock){
    user_stocks.erase(stock);
} 


void manager::print_stocks(std::string type){
    std::map<std::string, stock*> &specified_map = (type == "user") ? user_stocks : stocks;

    int num = 1;
    for(auto& pair : specified_map){
        std::cout << num << ". " << pair.first<< '\n';
        num++;
    }
};

void manager::advance_one_year(){
    // apply this year's return to each stock's share price
    for (auto& p : stocks){
        p.second->apply_return_for_year(year);
    }

    // recompute user's stock capital based on their holdings
    stock_capital = 0.0;
    for (auto& p : user_stocks){
        stock* s = p.second;
        stock_capital += s->share_price * s->stock_count;
    }

    // finally, move to next calendar year
    year++;
}



void manager::list_attributes(bool display_name){
    std::cout << '\n';
    if(display_name){ type_chars("Name: " + name); }
    type_chars("Year: " + std::to_string(getYear()));
    type_chars("Capital: $" + std::to_string(getCapitial())); 
    type_chars("Stock Capital: $" + std::to_string(getStockCapital()));  
    type_chars("Objectives: $" + std::to_string(getStockCapital()) + '\n');  
    
    sleep(2);
}


void manager::actions(int& input){
    
    std::cout << "List...\n"; sleep(1);
    type_chars("1. All stocks\n");
    type_chars("2. MY stocks\n");
    type_chars("3. Attributes\n");

    std::cin >> input;
    std::cout << "Input: "<<  input << '\n';
    
}


int manager::getYear(){ return year; }
void manager::updateYear(){ year++; };


double manager::getCapitial(){ return capital; }; 
void manager::updateCapital(double amount){ capital += amount; } 


double manager::getStockCapital(){ return stock_capital; }
void manager::updateStockCapitial(double amount){ stock_capital += amount;}



int manager::getObjective(){ return objective; }
void manager::updateObjective(double amount){ objective += amount; };