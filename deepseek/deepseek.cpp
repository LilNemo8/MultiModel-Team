#include "deepseek.h"


void deepseek_intro() {
    clear_terminal();
    int input = 0;

    std::cout << "--------------------------------------------------\n";
    std::cout << "              FINACIAL ADVISOR\n";
    std::cout << "--------------------------------------------------\n\n";
    sleep(1);

    while (input != 1 && input != 2) {
        std::cout << "1. Get Started\n";
        std::cout << "2. More Information\n";
        std::cout << "\nInput: "; std::cin >> input;
    }

    if (input == 2) {
        type_chars("\nYour 'finacial advisor' is actually gemma3, which is an AI\n");
        type_chars("Gemma3 can answer your basic questions such as...\n"); sleep(1);
        type_chars("   What is the stock market?");
        type_chars("   What is a stock?");
        type_chars("   How do stock prices move?\n"); sleep(3);
        type_chars("When you are finished talking to your 'financial advisor,' please close the tap"); sleep(2);
    }

    type_chars("\nGreat, let us begin!\n"); sleep(2);

}

void deepseek() {
    deepseek_intro();
    

    for (;;) {
        pid_t pid = fork();
        if (pid < 0) {
            std::perror("fork");
            exit(1);
        }

        if (pid == 0) {
            // execlp("xterm", "xterm", "-hold", "-e", "bash", "-i", "-c", "ai_pandoc", (char *)0);
            execlp("ollama", "ollama", "run", "deepseek-r1:8b", (char *) NULL);
            perror("execlp");
            _exit(127);
        } else {
            int status = 0;
            if (waitpid(pid, &status, 0) < 0) {
                perror("waitpid");
            }

            kill(pid, SIGKILL);

            clear_terminal();
        }
    }
}
