#include "helper/functions.h"
#include "classes/manager.h"
#include "deepseek/deepseek.h"

    
void intro(std::string& name){
    clear_terminal();
    char input;

    std::cout << "Name: ";
    std::getline(std::cin, name);


    
    std::cout << "--------------------------------------------------\n";
    std::cout << "              Financial Literacy\n";
    std::cout << "--------------------------------------------------\n\n";


    type_chars("Welcome " + name + ".\nThe following is designed to help you understand the Stock market and become financially literate.\n"); sleep(2);


    while(true){
        type_chars("Are you ready? [y/n]: "); std::cin >> input;
        if(input == 'y' || input == 'Y' || input == 'N' || input == 'n'){ break; }
    }


    if(input == 'Y' || input == 'y'){ type_chars("\n\nPerfect, let's get started."); sleep(2);}
    else if (input == 'N' || input == 'n'){ type_chars("Alright, stay broke kid");}


    clear_terminal();

}

void story(std::string name){
    type_chars("Year: 2014", std::chrono::milliseconds(60), true); sleep(3);
    clear_terminal();


    type_chars("CONGRATULATIONS " + name); sleep(1);
    type_chars("You've just graduated college with a Bacherlors in the Computer Science, YUCK"); sleep(1);
    loading("You know what this means", 4);
    std::cout << setColor("red"); type_chars("\nYOU AREN'T finding a job any time soon.\n"); std::cout << setColor("white"); image("cat.gif");
    type_chars("But you are smart, and since FASFA decided to give you more money than you needed, you decided Wall Street is your new home");

    sleep(4);

}

void gameplay(std::string name){
    clear_terminal();
    
    // type_chars("BEGINNING SIMULATION", std::chrono::milliseconds(100), true);
    
    manager market = manager(name);
    // market.list_attributes(true); // list all relevent data

    // The game play will run until the year becomes 2025
    type_chars("Alright then, let us begin\n"); sleep(1);
    while(market.getYear() != 2025){
        market.game();
    }
    

    
    




    sleep(2);

}
// share price 
// display graph 
// dollar gain lost
// percentage gain lose


int main(){
    clear_terminal();

    // Get the name of the user for better user experience
    std::string name;
    std::cout << "Name: "; std::getline(std::cin, name);
    clear_terminal();

    // deepseek();

    // // Explains what the purpose of this program is for
    // intro(name); 


    // // Gives the user a story and objective
    // story(name);

    // //actually gameplay of the program
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