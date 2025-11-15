#ifndef MANAGER_H
#define MANAGER_H

#include "stock.h"
#include "../deepseek/deepseek.h"

#include <map>

class manager{
    std::map<std::string, stock*> stocks; // all the avaliable stocks the user can choose from
    std::map<std::string, stock*> user_stocks; // the stocks that the user currently possess
    

    std::string name; // name of  player

    double capital; // the current amount of money the user possess
    double stock_capital; // money that derives from total stock_capital
    int year; // current year
    double objective; //the amount the user must aquire to be considered 'Fincially literate'

    // returns true if stock is present in user_stocks
    bool stock_present(std::string name){ return user_stocks.find(name) != user_stocks.end(); } 

    // declares and initializes all listed stocks
    void initialize_stocks(){
        std::map<std::string, std::vector<double>> returns = {
            { "Intel",                         { 44.25, -2.21, 8.76, 30.87, 4.23, 30.71, -14.69, 6.05, -46.64, 94.56, -59.57 } },
            { "Disney",                        { 24.85, 12.93, 0.67, 4.76, 3.61, 33.51, 25.27, -14.51, -43.91, 4.26, 24.44 } },
            { "IBM",                           { -12.39, -11.42, 25.21, -3.99, -22.56, 23.58, -1.16, 16.65, 10.64, 21.85, 39.27 } },
            { "AMC",                           { 30.62, -5.72, 44.10, -53.09, -7.75, -36.60, -70.54, 1183.02, -85.04, -84.96, -34.97 } },
            { "Verizon",                       { -0.55, 3.62, 20.70, 3.98, 11.26, 13.84, -0.13, -7.55, -20.02, 2.71, 13.14 } },
            { "Total Stock Market Index Fund", { 12.56,  0.39, 12.66, 21.17, -5.17, 30.80, 20.99, 25.71, -19.53, 26.01, 23.74 } },
            { "S&P 500 Index Fund",            { 13.51,  1.25, 11.82, 21.67, -4.52, 31.33, 18.25, 28.53, -18.23, 26.11, 24.84 } },
            { "Small Cap Index Fund",          { 7.50, -3.64, 18.30, 16.24, -9.31, 27.37, 19.11, 17.73, -17.61, 18.20, 14.23 } }
        };

        for (auto& p : returns){
            const std::string& name = p.first;
            const std::vector<double>& r = p.second;
            stock* newStock = new stock(name, r);   // matches the new constructor
            stocks[name] = newStock;
        }
    }

    public:
    //CONSTRUCTOR is responible for declaring and initializing all stocks that the program will hold
    manager(std::string name);

    //DESTRUCTOR is responisble for clearing all heap-initialized memory to avoid memory leaks
    ~manager(); 


    // add a new stock 
    void buy_stock();

    // delete specific stock
    void sell_stock(); 

    // prints stocks in specificed map [user or all]
    void print_stocks(std::string type);

    // apply this year's % returns to all stocks, update user stock_capital, then year++
    void advance_one_year();

    // graphs out the user stocks
    void graph_user_stocks();

    // List the attributes of the player
    void list_attributes(bool display_name);

    // This is the function that will allow player to buy or sell stocks
    void manager_stocks();

    // list all possible actions user can take
    void game();





    int getYear(); // returns the current year the program is current in
    void updateYear(); // updates year

    double getCapitial(); // returns user capital 
    void updateCapital(double amount); // updates capital based on stock purchases

    double getStockCapital(); //returns user stock capitial
    void updateStockCapitial(double amount); //updates stock capital

    int getObjective();
    void updateObjective(double amount);




    
};



#endif