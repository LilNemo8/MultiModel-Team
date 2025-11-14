#ifndef MANAGER_H
#define MANAGER_H

#include "stock.h"

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
        // yearly returns for 2014–2024 (11 years) for each stock
        std::map<std::string, std::vector<double>> returns = {
            { "Intel", {
                44.25, -2.21,  8.76, 30.87,  4.23,
                30.71, -14.69, 6.05, -46.64, 94.56, -59.57
            }},
            { "Disney", {
                24.85, 12.93, 0.67, 4.76, 3.61,
                33.51, 25.27, -14.51, -43.91, 4.26, 24.44
            }},
            { "IBM", {
                -12.39, -11.42, 25.21, -3.99, -22.56,
                23.58, -1.16, 16.65, 10.64, 21.85, 39.27
            }},
            { "AMC", { // AMC Entertainment
                30.62, -5.72, 44.10, -53.09, -7.75,
                -36.60, -70.54, 1183.02, -85.04, -84.96, -34.97
            }},
            { "Verizon", {
                -0.55, 3.62, 20.70, 3.98, 11.26,
                13.84, -0.13, -7.55, -20.02, 2.71, 13.14
            }}
        };

        // create stock objects on the heap and store them in the map
        for (auto& p : returns){
            const std::string& name = p.first;
            const std::vector<double>& r = p.second;
            stock* newStock = new stock(name, r);
            stocks[name] = newStock;
        }
    }


    public:
    //CONSTRUCTOR is responible for declaring and initializing all stocks that the program will hold
    manager(std::string name);

    //DESTRUCTOR is responisble for clearing all heap-initialized memory to avoid memory leaks
    ~manager(); 


    // add a new stock 
    void add_stock(std::string stock);

    // delete specific stock
    void remove_stock(std::string stock); 

    // prints stocks in specificed map [user or all]
    void print_stocks(std::string type);

    // apply this year's % returns to all stocks, update user stock_capital, then year++
    void advance_one_year();

    void list_attributes(bool display_name);

    // list all possible actions user can take
    void actions(int& input);

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