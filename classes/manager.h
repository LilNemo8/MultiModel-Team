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

    // delcares and initializes all listed stocks
    void initialize_stocks(){
        std::vector<std::string> stocks_str = {"Nvidia","Apple","Microsoft","Amazon","Meta","Broadcom","Tesla","Pinterst"};

        for(auto& s : stocks_str){
            stock* newStock = new stock(s);
            stocks[s] = (newStock);
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


    // returns the current year the program is current in
    int getYear(); 
    
    // updates year
    void updateYear();


    // returns user capital 
    int getCapitial();
    
    // updates capital based on stock purchases
    void updateCapital(double amount);

    //returns user stock capitial
    int getStockCapital();

    //updates stock capital
    void updateStockCapitial(double amount);

    int getObjective();
    void updateObjective(double amount);

    void list_attributes(bool list_name);

    // list all possible actions user can take
    void actions(int& input);

    
};



#endif