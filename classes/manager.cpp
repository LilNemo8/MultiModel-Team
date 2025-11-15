#include "manager.h"



manager::manager(std::string name){
    initialize_stocks();

    this->name = name;
    capital = 10000.0;
    objective = 50000.0;
    stock_capital = 0.0;
    year = 2014;
} 


manager::~manager(){
    // clear all memory that stocks used in heap [NO MEM LEAKS]
    for(auto& s : stocks){
        delete s.second;
    }

} 


void manager::buy_stock(){
    clear_terminal(); type_chars("1. Buy Stocks\n"); sleep(1);

    int specified_stock;
    int quantity;

    while(true){
        
        // List user stocks
        // type_chars("\nHere is a list of the stocks you currently possess "); sleep(1);
        print_stocks("user"); sleep(1); std::cout << '\n';


        // List all stocks
        // type_chars("\nHere is a list of ALL stocks");  sleep(1);
        print_stocks("all"); sleep(1);
        

        
        // Which specific stock to buy ------------------------------------------
        stock_selection:
        type_chars("Which Stock would you like to buy?");
        std::cout << "Stock: #"; std::cin >> specified_stock;

        if(0 > specified_stock  || (int)stocks.size() < specified_stock){
            std::cout << setColor("red"); std::cout << "Invalid pick. Please try again\n"; std::cout << setColor("white"); 
            goto stock_selection;
        }
        //------------------------------------------------------------------------
        

        // How many of that stock to buy ------------------------------------------------
        auto it = stocks.begin();
        for(int i = 1 ; i < specified_stock; i++){ it++; }


        type_chars("\nHow many "+ it->first +" stock(s) would you like to buy?");
        std::cout << "Quantity: "; std::cin >> quantity;

        // if stock is not present, then we add it
        if(!stock_present(it->first)){ user_stocks[it->first] = stocks[it->first]; }

        //increment stock count
        user_stocks[it->first]->stock_count += quantity;

        std::string purchase = "\nYou've bought " + std::to_string(quantity) + " stocks of " + it->first +'\n'; 
        std::cout << setColor("green"); type_chars(purchase); std::cout << setColor("white");

        updateCapital(-stocks[it->first]->share_price * quantity);
        updateStockCapitial(stocks[it->first]->share_price * quantity);


        // ------------------------------------------------------------------------
        list_attributes(false);

        char c;
        std::cout << "Would you like to buy more stocks? [y/n] "; std::cin >> c;
        if(c == 'n' || c == 'N'){ break; }
    }

    clear_terminal();
} 


void manager::sell_stock(){
    clear_terminal(); type_chars("2. Sell Stocks\n"); sleep(1);

    if ((int)user_stocks.size() == 0) {
        std::cout << setColor("red"); 
        std::cout << "Sorry you currently have no stocks to sell. Please buy some stocks first\n\n";
        std::cout << setColor("white"); 
        sleep(2);
        return;
    }

    int specified_stock;
    int quantity;

    while (true) {

        // List all stocks
        // print_stocks("all");  sleep(1);

        // List user stocks
        print_stocks("user"); sleep(1);

    stock_selection:
        type_chars("\n\nWhich Stock would you like to sell?");
        std::cout << "Input: ";
        std::cin >> specified_stock;

        // input validation: 1..user_stocks.size()
        if (specified_stock < 1 || specified_stock > (int)user_stocks.size()) {
            std::cout << setColor("red");
            std::cout << "Invalid pick. Please try again\n";
            std::cout << setColor("white"); 
            goto stock_selection;
        }

        // move iterator to the chosen element (1-based index)
        auto it = user_stocks.begin();
        for (int i = 1; i < specified_stock; ++i) {
            ++it;
        }

        // save key and pointer BEFORE any erase
        std::string symbol = it->first;
        stock* stk = it->second;

    stock_quantity:
        // How many of that stock to sell
        type_chars("\nHow many " + symbol + " stock(s) would you like to sell?");
        std::cout << "Quantity: ";
        std::cin >> quantity;

        // if the quantity specified by user is greater than stock_count : invalid operation
        if (stk->stock_count < quantity) { 
            std::cout << setColor("red");
            std::cout << "Invalid pick. Please try again\n";
            std::cout << setColor("white"); 
            goto stock_quantity;

        // since quantity and stock_count are equal remove stock
        } else if (stk->stock_count == quantity) {
            std::cout << "Removing: " << symbol << '\n'; 
            stk->stock_count = 0;
            user_stocks.erase(symbol);

        // sell specified amount of stocks
        } else {
            stk->stock_count -= quantity;
        }

        std::string purchase = "\nYou've sold " + std::to_string(quantity) + " stocks of " + it->first +'\n'; 
        std::cout << setColor("red"); type_chars(purchase); std::cout << setColor("white");


        // use 'symbol' and 'stk' (no iterator after erase)
        updateCapital(stk->share_price * quantity);
        updateStockCapitial(-stk->share_price * quantity);

        list_attributes(false);

        char c;
        std::cout << "Would you like to sell more stocks? [y/n] ";
        std::cin >> c;
        if (c == 'n' || c == 'N') { break; }
    }

    clear_terminal();
}

void manager::print_stocks(std::string type){
    std::map<std::string, stock*> &specified_map = (type == "user") ? user_stocks : stocks;
    int num = 1;
    bool user = false;

    if(type == "all"){ type_chars("--- ALL STOCKS ---"); }
    else{ type_chars("--- MY STOCKS ---"); user = true;}
    sleep(1);

    if(specified_map.size() == 0){
        std::cout << setColor("red"); std::cout << "You currently have no Stocks\n"; std::cout << setColor("white");
        return;
    }

    for(auto& pair : specified_map){
        std::cout << "  " << num << ". " << pair.first << '\n'; pair.second->print(user, year);
        num++;
    }

    std::cout << '\n';
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

    list_attributes(true);
}

void manager::graph_user_stocks(){
    return; // TO-DO
}

void manager::list_attributes(bool display_extra){
    // std::cout << '\n';
    if(display_extra){ 
        type_chars("Name: " + name); 
        type_chars("Year: ",  std::chrono::milliseconds(80), false); std::cout << getYear() << '\n';
    }

    std::cout << std::fixed << std::setprecision(2);
    type_chars("Capital: $",  std::chrono::milliseconds(80), false);  std::cout << getCapitial() << '\n';
    type_chars("Stock Capital: $",  std::chrono::milliseconds(80), false); std::cout <<getStockCapital() << '\n';
    type_chars("Objectives: $",  std::chrono::milliseconds(80), false); std::cout << getObjective() << "\n\n";
    
    sleep(2);
}

void manager::manager_stocks(){
    clear_terminal();
    int input;

    // type_chars("Here are your stocks:");
    print_stocks("user"); std::cout << '\n';


    
    while(true){
        std::cout << "--- Options ---\n\n"; sleep(1);
        type_chars("1. Buy Stocks", std::chrono::milliseconds(10));
        type_chars("2. Sell Stocks", std::chrono::milliseconds(10));
        type_chars("3. Graph Stock(s)", std::chrono::milliseconds(10));
        type_chars("4. Main Menu", std::chrono::milliseconds(10));

        std::cout << "\nInput: "; std::cin >> input;
        
        
        switch(input){
            case 1:
                buy_stock();
                break;
            case 2:
                sell_stock();
                break;
            case 3: 
                graph_user_stocks();
                break;
            case 4:
                clear_terminal();
                return; 
            default:
                std::cout << "Invalid Input. Please try again\n\n";
                break;
        }
    }
};


void manager::game(){
    clear_terminal();
    int input;

    while(true){
    
        std::cout << "--- Main Menu ---\n\n"; sleep(1);
        type_chars("1. List All stocks", std::chrono::milliseconds(10));
        type_chars("2. List MY stocks", std::chrono::milliseconds(10));
        type_chars("3. Manage my stocks", std::chrono::milliseconds(10));
        type_chars("4. My Attributes", std::chrono::milliseconds(10));
        type_chars("5. Talk to a 'finacial advisor'", std::chrono::milliseconds(10));
        type_chars("6. Advance one year", std::chrono::milliseconds(10));

        std::cout << "\nInput: "; std::cin >> input;

        clear_terminal();
        
        switch (input){
            case 1:
                print_stocks("all");
                break;
            case 2:
                print_stocks("user");
                break;
            case 3: 
                manager_stocks();
                break;
            case 4: 
                list_attributes(true);
                break;
            case 5:
                deepseek();
                break; 
            case 6:
                advance_one_year();
                break;
            default:
                std::cout << "Invalid Input. Please try again\n\n";
                break;
        }
        
    }
}


int manager::getYear(){ return year; }
void manager::updateYear(){ year++; };


double manager::getCapitial(){ return capital; }; 
void manager::updateCapital(double amount){ capital += amount; } 


double manager::getStockCapital(){ return stock_capital; }
void manager::updateStockCapitial(double amount){ stock_capital += amount;}



int manager::getObjective(){ return objective; }
void manager::updateObjective(double amount){ objective += amount; };