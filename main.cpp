#include "helper/functions.h"
#include "classes/manager.h"
#include "deepseek/deepseek.h"

    
void intro(std::string& name){
    clear_terminal();
    char input;
    
    std::cout << "--------------------------------------------------\n";
    std::cout << "              Financial Literacy\n";
    std::cout << "--------------------------------------------------\n\n";


    type_chars("Welcome " + name + ".\nThe following simulation is designed to help you understand the Stock market and become financially literate.\n"); sleep(2);

    while(true){
        type_chars("Are you ready to become financially literate? [y/n]: "); std::cin >> input;
        if(input == 'y' || input == 'Y' || input == 'N' || input == 'n'){ break; }
    }


    if(input == 'Y' || input == 'y'){ type_chars("\n\nPerfect, let's get started."); sleep(2);}
    else if (input == 'N' || input == 'n'){ type_chars("Alright, stay broke kid");}


    clear_terminal();
}

void story(const std::string& name){
    clear_terminal();

    type_chars("CONGRATULATIONS " + name); sleep(1);
    type_chars("\nYou've just graduated college with a Bacherlors in the Computer Science, YUCK"); sleep(1);
    loading("You know what this means", 1, std::chrono::milliseconds(1000));
    std::cout << setColor("red"); type_chars("\nYOU AREN'T finding a job any time soon.\n"); std::cout << setColor("white"); image("cat_laughing.jpg", 2);
    type_chars("But you are smart, and since FASFA decided to give you more money than you needed, you decided Wall Street is your new home");

    wait_for_enter();

}

void intructions(){
    char c;
    std::cout << "\nWould you like to know how the simulation works? [Y/n] "; std::cin >> c;

    if(c == 'n' || c =='N'){ return; }

    clear_terminal();

    std::cout << "--------------------------------------------------\n";
    std::cout << "                  Instructions\n";
    std::cout << "--------------------------------------------------\n\n";


    type_chars("First the simulation will list your attributes as follows\n");
    type_chars("   Name: (your name)", std::chrono::milliseconds(5)); 
    type_chars("   Year: (current year)", std::chrono::milliseconds(5));
    type_chars("   Capital: (the money you possess)", std::chrono::milliseconds(5)); 
    type_chars("   Stock Capital: (money you possess based on stock value(s))", std::chrono::milliseconds(5));
    type_chars("   Objectives: (the amount one should have at the end)\n", std::chrono::milliseconds(5), true);
    wait_for_enter();

    
    type_chars("Then you will be shown the main menu which includes the following");
    std::cout << "\n   --- Main Menu ---\n\n"; sleep(1);
    type_chars("   1. List All stocks (Displays all stocks)", std::chrono::milliseconds(5));
    type_chars("   2. List MY stocks  (Displays the stocks you currently possess)", std::chrono::milliseconds(5));
    type_chars("   3. Manage My stocks  (Allows you to edit and view your stocks)", std::chrono::milliseconds(5));
    type_chars("   4. My Attributes (List all attributes as shown above)", std::chrono::milliseconds(5));
    type_chars("   5. Talk to a 'finacial advisor' (Allows you to talk to an AI)", std::chrono::milliseconds(5));
    type_chars("   6. Advance Year(s) (Advances a specific amount of years in order to similate the stock market)\n", std::chrono::milliseconds(5), true);
    wait_for_enter();

    
    type_chars("Now you can clearly see that each option has a description but the following need more elaberation");
    type_chars("\n   3. Manage My stocks", std::chrono::milliseconds(10));
    type_chars("   6. Advance Year(s)", std::chrono::milliseconds(10)); sleep(2);

    type_chars("\nOption 3 will display a new menu which allows you to view and edit stocks");
    
    std::cout << "\n   --- Options ---\n\n"; sleep(1);
    type_chars("   1. Buy Stocks", std::chrono::milliseconds(10));
    type_chars("   2. Sell Stocks", std::chrono::milliseconds(10));
    type_chars("   3. Yearly Return(s) (allows you to see how your stocks have been doing after advancing year(s))", std::chrono::milliseconds(10));
    type_chars("   4. Main Menu\n", std::chrono::milliseconds(10), true); 
    wait_for_enter();


    type_chars("Option 6 will allow you to advance into the future in order to simulation reality.");
    type_chars("Advancements will be in incremnets of year(s).");
    type_chars("The simulation will begin in 2014 and end in 2025\n");
    wait_for_enter();


    type_chars("Once the year is 2025, the simulation will give you your results and check to see if you completeled the objective.\n");
    std::cout << setColor("green"); 
    type_chars("If objective is completeled, then you have become finacially literate"); image("celebration.gif", 2);
    std::cout << setColor("red"); 
    type_chars("\nOtherwise you can have fun in a homeless shelter"); image("orange_cat_laughing.gif", 2);
    std::cout << setColor("white"); 

    type_chars("\nAlright then, let us begin"); 
    wait_for_enter();
    

}

void gameplay(const std::string& name){
    clear_terminal();
    
    // type_chars("BEGINNING SIMULATION", std::chrono::milliseconds(10), true); sleep(1);
    loading("BEGINNING SIMULATION", 4, std::chrono::milliseconds(80));
    clear_terminal();

    
    manager market = manager(name);
    market.list_attributes(true); // list all relevent data


    
    // The game play will run until the year becomes 2025
    market.game();

    market.result();
}


int main(){
    clear_terminal();

    // Get the name of the user for better user experience
    std::string name;
    std::cout << "Name: "; std::getline(std::cin, name);


    // Explains what the purpose of this program is for
    intro(name); 

    // Gives the user a story and objective
    story(name);

    // instructions if the player wishes to see them
    intructions();

    //actually gameplay of the program
    gameplay(name);


    std::cout << "Thank you for playing :D\n";
    return 0;
    
}
