#include "helper/functions.h"
#include "classes/manager.h"

    


void story(std::string name){
    type_chars("CONGRATULATIONS " + name); sleep(1);
    type_chars("You've just graduated college with a bacherlors in the computer science, YUCK"); sleep(1);
    loading("You know what this means", 4);
    std::cout << setColor("red"); type_chars("\nYOU AREN'T finding a job any time soon.\n"); std::cout << setColor("white");
    type_chars("But you are smart, and since FASFA decided to give you more money than you needed, you decided Wall Street is your new home");

    sleep(4);

}

void gameplay(std::string name){
    clear_terminal();
    
    type_chars("BEGINNING SIMULATION", std::chrono::milliseconds(100), true);
    
    manager market = manager(name);
    market.list_attributes(true); // list all relevent data

    

    type_chars("Here is a list of stocks that are avaliable right now\n");
    
    
    market.print_stocks("all");

    sleep(2);

}
// share price 
// display graph 
// dollar gain lost
// percentage gain lose


int main(){
    clear_terminal();

    std::string name;
    // char input;

    std::cout << "Name: ";
    std::getline(std::cin, name);


    // clear_terminal();


    
    // std::cout << "--------------------------------------------------\n";
    // std::cout << "              Financial Literacy\n";
    // std::cout << "--------------------------------------------------\n\n";


    // std::string welcome = "Welcome " + name + ". The following is designed to help you understand the Stock market and become financially literate.\n"; 
    // type_chars(welcome); sleep(2);


    // while(true){
    //     type_chars("Are you ready? [y/n]: "); std::cin >> input;
    //     if(input == 'y' || input == 'Y' || input == 'N' || input == 'n'){ break; }
    // }


    // if(input == 'Y' || input == 'y'){ type_chars("\n\nPerfect, let's get started."); sleep(2);}
    // else if (input == 'N' || input == 'n'){ type_chars("Alright, stay broke kid");}


    // clear_terminal();


    story(name);

    gameplay(name);



    


    std::cout << "Terminate Program\n";
    return 0;
    
}


// starting captial give the player money 
// you just got out of college and you have to begin to invest 
/*
capital 50k
what performs better, indivudal or index
goals reach certain amount 
each year is a new mile stone 
set year to 2015, end year 2025


*/