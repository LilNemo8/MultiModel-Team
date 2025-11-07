#include "functions.h"



// Gives the illusion of typing each character
void type_chars(const std::string& text, std::chrono::milliseconds per_char, bool newline_at_end) {
    for (char c : text) {
        std::cout << c << std::flush;
        using namespace std::chrono_literals;
        if (c == ' ' || c == '\n') std::this_thread::sleep_for(per_char / 3);
        else if (c == '.' || c == '!' || c == '?' || c == ',') std::this_thread::sleep_for(per_char * 6);
        else std::this_thread::sleep_for(per_char);
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



char getch() {
    static bool inited = false;
    static struct termios saved;     // original settings
    struct termios raw;

    if (!inited) {
        if (tcgetattr(STDIN_FILENO, &saved) < 0) perror("tcgetattr(saved)");
        inited = true;
    }

    // Ensure blocking reads on STDIN
    int fl = fcntl(STDIN_FILENO, F_GETFL);
    if (fl != -1 && (fl & O_NONBLOCK)) fcntl(STDIN_FILENO, F_SETFL, fl & ~O_NONBLOCK);

    raw = saved;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN]  = 1;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) < 0) perror("tcsetattr(raw)");

    char ch;
    for (;;) {
        ssize_t n = read(STDIN_FILENO, &ch, 1);
        if (n == 1) break;
        if (n < 0 && (errno == EINTR || errno == EAGAIN)) continue;
        perror("read"); break;
    }

    // Restore original terminal settings
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &saved) < 0) perror("tcsetattr(saved)");
    return ch;
}

void make_stdio_blocking() {
    for (int fd = 0; fd <= 2; ++fd) {
        int fl = fcntl(fd, F_GETFL);
        if (fl != -1 && (fl & O_NONBLOCK)) fcntl(fd, F_SETFL, fl & ~O_NONBLOCK);
    }
}


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
