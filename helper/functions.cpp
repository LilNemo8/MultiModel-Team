#include "functions.h"
#include <csignal>



// Gives the illusion of typing each character
void type_chars(const std::string& text, std::chrono::milliseconds per_char, bool newline_at_end) {
    for (char c : text) {
        std::cout << c << std::flush;
        using namespace std::chrono_literals;
        if (c == ' ' || c == '\n') std::this_thread::sleep_for(per_char);
        else if (c == '.' || c == '!' || c == '?' || c == ',') std::this_thread::sleep_for(per_char * 7);
        else std::this_thread::sleep_for(per_char-std::chrono::milliseconds(5));
    }
    if (newline_at_end) std::cout << '\n';
}


// This is the 'loading' that happens when choosing a specific application (CHAT WROTE THIS)
void loading(const std::string& msg, int time) {
    const int maxDots = 3;
    int d = 1; // show 1,2,3 dots, then reset to none (0), repeat
    int x  = time;
    while (x!=0) {
        std::cout << "\r " << msg
        << std::string(d, '.')
        << std::string(maxDots - d, ' ')   // overwrite old dots
        << std::flush;
        
        sleep(1);
        d = (d + 1) % (maxDots + 1); // cycles: 1→2→3→0→1→...
        x--;
    }
    std::cout<<'\n';
}

int play_again(std::string category){
    char answer;
    while(true){
        std::cout << "\nWould you like to look at the other than " << category << "? [Y/n]:";
        std::cin >> answer;
        if(answer == 'Y' || answer == 'n'){break;}
    }

    if(answer == 'Y'){ 
        std::cout<< "\n\nAlright lets look at some more " << category << " :D \n\n";
        return 1; //continue
    }else{
        return 0; //break
    }
}


void clear_terminal(){
    std::cout << "\033[2J\033[1;1H"; 
};



std::string setColor(std::string color) {
    if (color == "red") {
        return "\033[31m";
    } else if (color == "green") {
        return "\033[32m";
    } else if (color == "yellow") {
        return "\033[33m";
    } else if (color == "blue") {
        return "\033[34m";
    } else if (color == "magenta") {
        return "\033[35m";
    } else if (color == "cyan") {
        return "\033[36m";
    } else if (color == "white") {
        return "\033[37m";
    }
    // Default to white if no valid color is chosen
    return "\033[37m";
}


void image(std::string file_name){

    pid_t pid = fork();


   if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // CHILD: silence output
        int devnull = open("/dev/null", O_WRONLY);
        if (devnull != -1) {
            dup2(devnull, STDOUT_FILENO);  // redirect stdout
            dup2(devnull, STDERR_FILENO);  // redirect stderr
            close(devnull);
        }

        // Now run eog
        std::string path = "helper/images/" + file_name;
        execlp("eog", "eog", path.c_str(), (char*)NULL);
        _exit(1); // only reached if execlp fails
    } else {
        // PARENT
        sleep(2);
        kill(pid, SIGTERM);
    }
}