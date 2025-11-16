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
        

        
        // Which specific stock to buy --------------------------------------------------------------------------
        stock_selection:
        type_chars("Which Stock would you like to buy? (enter 0 to leave)");
        std::cout << "Stock: #"; std::cin >> specified_stock;
        if(specified_stock == 0){ // stop buying if user wishes to 
            return; 
        }else if(0 > specified_stock || (int)stocks.size() < specified_stock){ // makesure selection is within a certain range
            std::cout << setColor("red"); std::cout << "Invalid pick. Please try again\n"; std::cout << setColor("white"); 
            goto stock_selection;
        }
        //--------------------------------------------------------------------------------------------------------
        

        // How many of that stock to buy ------------------------------------------------------------------------
        auto it = stocks.begin();
        for(int i = 1 ; i < specified_stock; i++){ it++; }

        stock_quantity:
        double amount;
        // type_chars("\nHow many "+ it->first +" share(s) would you like to buy?");
        std::cout << std::fixed << std::setprecision(2);
        type_chars("\nHow much would you like to invest into " + it->first + "? (Capital: $", std::chrono::milliseconds(60), false); std::cout <<getCapitial() << ")\n"; 
        std::cout << "Amount: $"; std::cin >> amount;

        quantity  = amount / it->second->share_price;
        std::cout << "\nWith $" << amount << ", you are able to buy " << quantity << " share(s)\n"; sleep(1);


        
        //CHECK FOR POSSIBLE DEBT ------------------------
        char c;
        double purchase = quantity * it->second->share_price;
        if(purchase > getCapitial()){
            std::cout << setColor("red");
            type_chars("\nTHIS ACTION WILL INCUR DEBT\n");
            std::cout << "ATTEMPTED PURCHASE:   " << purchase << '\n'; 
            std::cout << "YOUR CURRENT CAPITAL: " << getCapitial() <<'\n';
            std::cout << setColor("white");
            sleep(2);
            type_chars("\nAre you sure you want to go through with this? [Y/n]: ", std::chrono::milliseconds(50), false);
            std::cin >> c;

            if(c == 'n' || c == 'N'){ goto stock_quantity; }
        }else if(quantity == 0){
            std::cout << setColor("red"); std::cout << "Invalid Quantity. Please try again\n"; std::cout << setColor("white"); 
            goto stock_quantity;
        }
        //  --------------------------------------------

        // if stock is not present, then we add it
        if(!stock_present(it->first)){ user_stocks[it->first] = stocks[it->first]; }
        //increment stock count
        user_stocks[it->first]->stock_count += quantity;

        // Prints out the purchase the user just made
        std::string purchase_str = "\nYou've bought " + std::to_string(quantity) + " share(s) of " + it->first +'\n'; 
        std::cout << setColor("green"); type_chars(purchase_str); std::cout << setColor("white");

        // Updates Capital and Stock Capitial
        updateCapital(-stocks[it->first]->share_price * quantity);
        updateStockCapitial(stocks[it->first]->share_price * quantity);

        list_attributes(false);

        // -------------------------------------------------------------------------------------------------------
        // Ask the User if they would like to buy another stock
        std::cout << "Would you like to buy more stocks? [y/n] "; std::cin >> c;
        if(c == 'n' || c == 'N'){ return; }
        clear_terminal();
    }

    clear_terminal();
} 

void manager::sell_stock(){
    clear_terminal(); type_chars("2. Sell Stocks\n"); sleep(1);

    if (user_stocks.empty()) {
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
        type_chars("\n\nWhich Stock would you like to sell? (enter 0 to leave)");
        std::cout << "Stock: #";
        std::cin >> specified_stock;

        // input validation: 1..user_stocks.size()
        if(specified_stock == 0){ // stop buying if user wishes to 
            return; 
        }else if (specified_stock < 1 || specified_stock > (int)user_stocks.size()) {
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
        type_chars("\nHow many " + symbol + " share(s) would you like to sell?");
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
            std::cout << setColor("red");
            std::cout << "\nSelling all " << symbol << " stocks\n"; 
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

    if(type == "all"){ type_chars("--- ALL AVALIABLE STOCKS ---", std::chrono::milliseconds(20)); }
    else{ type_chars("--- MY STOCKS ---", std::chrono::milliseconds(20)); user = true;}
    sleep(1);

    if(specified_map.empty()){
        std::cout << setColor("red"); std::cout << "You currently have no Stocks\n\n"; std::cout << setColor("white");
        return;
    }

    for(auto& pair : specified_map){

        // std::cout << "  " << num << ". " << pair.first << '\n'; pair.second->print(user, year);
        type_chars(("  " + std::to_string(num) + ". " + pair.first + "\n"), std::chrono::milliseconds(5), false);
        pair.second->print(user, year);
        num++;
    }

    std::cout << '\n';
};

void manager::advance_year(bool& end_simulation){
    clear_terminal(); type_chars("6. Advance Year(s)\n"); sleep(1);

    if(user_stocks.empty()){
        char c;
        std::cout << setColor("red");
        std::cout << "You currently possess no stocks, are you sure you wish to advance?? [Y/n]"; 
        std::cout << setColor("white");
        std::cin >> c;
        if(c == 'n' || c == 'N'){ return; }
        std::cout << '\n'; 
    }
    long long int year_s;
    while(true){
        type_chars("How many years would you like to advance? (current " + std::to_string(year) + ")");
        std::cout << "Years: "; std::cin >> year_s;
        if(year_s + year <= 2025){ break;}
        std::cout << setColor("red"); std::cout << "\nToo Far into the Future. Please try again.\n\n"; std::cout << setColor("white"); 
    }

    for(int i = 0 ; i < year_s; i++){

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


    loading("Advancing " + std::to_string(year_s) + " Year(s)", 4, std::chrono::milliseconds(100));
    // clear_terminal();

    list_attributes(true);


    type_chars("Here are your yearly returns");

    yearly_returns_all();


    if (year == 2025) end_simulation = true;
    else end_simulation = false;
}

void manager::yearly_returns_all(){
    print_stocks("user");
    for(auto& it : user_stocks){

        std::string name = it.first;
        stock* s = it.second;
        
        type_chars("Yearly returns for " + name + ":\n");
        
        // We have data from 2014–2024; show only years that have "finished".
        int startYear = 2014;
        int endYear = std::min(year - 1, 2024);  // last completed year
        
        if (endYear < startYear) {
            std::cout << setColor("red");
            type_chars("No historical returns yet. Advance one year first.\n");
            std::cout << setColor("white");
            
            sleep(2);
            clear_terminal();
            return;
        }
        
        // Find the max absolute return to scale the bars
        double maxAbs = 0.0;
        for (int y = startYear; y <= endYear; ++y) {
            int idx = (y - stock::BASE_YEAR) + 1; // because of leading 0
            if (idx < 0 || idx >= (int)s->yearly_returns.size()) continue;
            double r = s->yearly_returns[idx];
            double ar = (r < 0 ? -r : r);
            if (ar > maxAbs) maxAbs = ar;
        }
        if (maxAbs == 0.0) maxAbs = 1.0; // avoid divide-by-zero
        
        const int maxBarWidth = 30;
        
        // Draw the graph
        for (int y = startYear; y <= endYear; ++y) {
            int idx = (y - stock::BASE_YEAR) + 1;
            if (idx < 0 || idx >= (int)s->yearly_returns.size()) continue;
            
            double r = s->yearly_returns[idx];
            double ar = (r < 0 ? -r : r);
            int barLen = (int)((ar / maxAbs) * maxBarWidth + 0.5);
            
            std::string bar;
            if (r > 0)      bar = std::string(barLen, '+');
            else if (r < 0) bar = std::string(barLen, '-');
            else            bar = "";
            
            // Example: 2018   -9.31%  -------|
            if(r < 0){ std::cout << setColor("red"); }
            else{ std::cout << setColor("green"); }
            
            std::cout << y << "  ";
            std::cout << std::fixed << std::setprecision(2) << std::setw(7) << r << "%  ";
            
            if (r < 0) {
                std::cout << bar << "|\n";   // negative to the left of the axis
            } else {
                std::cout << "|" << bar << '\n'; // positive to the right
            }
            std::cout << setColor("white");
        }

        std::cout << '\n'; 
    }
        
    std::cout << setColor("green"); std::cout << "\n( '+' = positive return "; 
    std::cout << setColor("white"); std::cout << '|'; 
    std::cout << setColor("red");   std::cout <<  " '-' = negative return )\n\n";
    std::cout << setColor("white");

}

void manager::yearly_returns(){
    clear_terminal();
    type_chars("3. Yearly Return(s)\n"); 
    sleep(1);

    if (user_stocks.empty()) {
        std::cout << setColor("red");
        std::cout << "You currently have no stocks to graph.\n";
        std::cout << setColor("white");
        sleep(2);
        clear_terminal();
        return;
    }

    // List the user's stocks with numbering
    repeat:
    print_stocks("user");

    int choice;

    stock_selection:
    type_chars("Which stock would you like to view the yearly returns for?",std::chrono::milliseconds(20));
    std::cout << "Input: ";
    std::cin >> choice;

    if (choice < 1 || choice > (int)user_stocks.size()) {
        std::cout << setColor("red");
        std::cout << "Invalid pick. Please try again\n";
        std::cout << setColor("white");
        goto stock_selection;
    }

    // Move iterator to selected stock (1-based index)
    auto it = user_stocks.begin();
    for (int i = 1; i < choice; ++i) { ++it; }

    stock* s = it->second;
    std::string name = it->first;

    // clear_terminal();
    std::cout << setColor("magenta");
    type_chars("Yearly returns for " + name + ":\n");
    std::cout << setColor("white");

    // We have data from 2014–2024; show only years that have "finished".
    int startYear = 2014;
    int endYear = std::min(year - 1, 2024);  // last completed year

    if (endYear < startYear) {
        std::cout << setColor("red");
        type_chars("No historical returns yet. Advance one year first.\n");
        std::cout << setColor("white");

        sleep(2);
        clear_terminal();
        return;
    }

    // Find the max absolute return to scale the bars
    double maxAbs = 0.0;
    for (int y = startYear; y <= endYear; ++y) {
        int idx = (y - stock::BASE_YEAR) + 1; // because of leading 0
        if (idx < 0 || idx >= (int)s->yearly_returns.size()) continue;
        double r = s->yearly_returns[idx];
        double ar = (r < 0 ? -r : r);
        if (ar > maxAbs) maxAbs = ar;
    }
    if (maxAbs == 0.0) maxAbs = 1.0; // avoid divide-by-zero

    const int maxBarWidth = 30;

    // Draw the graph
    for (int y = startYear; y <= endYear; ++y) {
        int idx = (y - stock::BASE_YEAR) + 1;
        if (idx < 0 || idx >= (int)s->yearly_returns.size()) continue;

        double r = s->yearly_returns[idx];
        double ar = (r < 0 ? -r : r);
        int barLen = (int)((ar / maxAbs) * maxBarWidth + 0.5);

        std::string bar;
        if (r > 0)      bar = std::string(barLen, '+');
        else if (r < 0) bar = std::string(barLen, '-');
        else            bar = "";

        // Example: 2018   -9.31%  -------|
        if(r < 0){ std::cout << setColor("red"); }
        else{ std::cout << setColor("green"); }

        std::cout << y << "  ";
        std::cout << std::fixed << std::setprecision(2) << std::setw(7) << r << "%  ";

        if (r < 0) {
            std::cout << bar << "|\n";   // negative to the left of the axis
        } else {
            std::cout << "|" << bar << '\n'; // positive to the right
        }
        std::cout << setColor("white");
    }

    std::cout << setColor("green"); std::cout << "\n( '+' = positive return "; 
    std::cout << setColor("white"); std::cout << '|'; 
    std::cout << setColor("red");   std::cout <<  " '-' = negative return )\n\n";
    std::cout << setColor("white");

    char c;
    std::cout << "Would you like to look at other Yearly Returns? [y/n]: "; std::cin >> c;
    if(c == 'y'||c == 'Y'){ std::cout << '\n'; goto repeat;}
    clear_terminal();
}

void manager::list_attributes(bool display_extra){
    if(display_extra){ 
        type_chars("Name: " + name); 
        type_chars("Year: ",  std::chrono::milliseconds(80), false); std::cout << getYear() << '\n';
    }

    std::cout << std::fixed << std::setprecision(2);
    type_chars("Capital:        $",  std::chrono::milliseconds(30), false); std::cout << getCapitial() << '\n'; sleep(1);
    type_chars("Stock Capital:  $",  std::chrono::milliseconds(30), false); std::cout <<getStockCapital() << '\n'; sleep(1);
    type_chars("Objectives:     $",  std::chrono::milliseconds(30), false); std::cout << getObjective() << "\n\n";
    
    sleep(2);
}

void manager::manager_stocks(){
    clear_terminal();
    int input;
    type_chars("3. Manage My Stocks\n\n"); 

    // type_chars("Here are your stocks:");
    print_stocks("user"); std::cout << '\n';


    
    while(true){
        std::cout << "--- Options ---\n\n"; sleep(1);
        type_chars("1. Buy Stocks", std::chrono::milliseconds(10));
        type_chars("2. Sell Stocks", std::chrono::milliseconds(10));
        type_chars("3. Yearly Return(s)", std::chrono::milliseconds(10));
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
                yearly_returns();
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
    // clear_terminal();
    int input;
    bool end_simulation;

    while(year != 2025){
    
        std::cout << "--- Main Menu ---\n\n"; sleep(1);
        type_chars("1. List All stocks", std::chrono::milliseconds(10));
        type_chars("2. List MY stocks", std::chrono::milliseconds(10));
        type_chars("3. Manage My stocks", std::chrono::milliseconds(10));
        type_chars("4. My Attributes", std::chrono::milliseconds(10));
        type_chars("5. Talk to a 'finacial advisor'", std::chrono::milliseconds(10));
        type_chars("6. Advance Year(s)", std::chrono::milliseconds(10));

        std::cout << "\nInput: "; std::cin >> input;

        clear_terminal();
        
        switch (input){
            case 1:
                print_stocks("all");
                additional_info();
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
                advance_year(end_simulation);
                break;
            default:
                std::cout << "Invalid Input. Please try again\n\n";
                break;
        }
        
        if(end_simulation){break;}
    }
}

void manager::result(){
    clear_terminal();
    type_chars("=== Simulation Result ===\n\n");

    // Show final basic attributes (name, year, capital, stock capital, objective)
    list_attributes(true);

    // Compute total net worth
    double netWorth = capital + stock_capital;

    std::cout << std::fixed << std::setprecision(2);
    type_chars("Total Net Worth (Capital + Stock Capital): $", 
               std::chrono::milliseconds(30), false);
    std::cout << netWorth << "\n\n";

    // Did the player hit the objective?
    if (netWorth >= objective) {
        std::cout << setColor("green");
        type_chars("Congratulations! You met or exceeded your objective.\n");
        std::cout << setColor("white");
    } else {
        std::cout << setColor("red");
        type_chars("You did not reach your objective.\n");
        std::cout << setColor("white");

        double shortfall = objective - netWorth;
        type_chars("You were short by: $", std::chrono::milliseconds(30), false);
        std::cout << shortfall << "\n";
    }

    std::cout << "\n";
    sleep(2);

    // Portfolio breakdown
    type_chars("=== Final Portfolio Breakdown ===\n\n");

    if (user_stocks.empty()) {
        std::cout << setColor("red");
        type_chars("You ended the simulation with no stocks.\n");
        std::cout << setColor("white");
    } else {
        double indexTotal = 0.0;
        double indivTotal = 0.0;
        int num = 1;

        for (auto &p : user_stocks) {
            stock* s = p.second;
            double positionValue = s->share_price * s->stock_count;

            bool isIndex = (p.first.find("Index Fund") != std::string::npos);
            if (isIndex) indexTotal += positionValue;
            else indivTotal += positionValue;

            // Print each holding
            std::cout << num << ". " << p.first << '\n';
            std::cout << "\tShares:      " << s->stock_count << '\n';
            std::cout << "\tShare Price: $" << std::fixed << std::setprecision(2)
                      << s->share_price << '\n';
            std::cout << "\tPosition:    $" << positionValue << "\n\n";

            ++num;
        }

        // Summary by type
        std::cout << std::fixed << std::setprecision(2);
        type_chars("Total in Index Funds:       $", std::chrono::milliseconds(20), false);
        std::cout << indexTotal << '\n';
        type_chars("Total in Individual Stocks: $", std::chrono::milliseconds(20), false);
        std::cout << indivTotal << "\n\n";

        // Simple teaching message
        if (indexTotal > indivTotal) {
            std::cout << setColor("green");
            type_chars("You relied more on diversified index funds than on single stocks.\n");
            std::cout << setColor("white");
        } else if (indivTotal > 0) {
            std::cout << setColor("yellow");
            type_chars("Your portfolio leaned heavily on individual stocks, which are riskier.\n");
            std::cout << setColor("white");
        }
    }

    std::cout << "\n";
    type_chars("Thank you for playing the stock market simulation!\n");
    sleep(4);
    clear_terminal();
}


int manager::getYear(){ return year; }
void manager::updateYear(){ year++; };


double manager::getCapitial(){ return capital; }; 
void manager::updateCapital(double amount){ capital += amount; } 


double manager::getStockCapital(){ return stock_capital; }
void manager::updateStockCapitial(double amount){ stock_capital += amount;}



int manager::getObjective(){ return objective; }
void manager::updateObjective(double amount){ objective += amount; };