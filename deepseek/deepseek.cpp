#include "deepseek.h"


// Child: attach stdio to the controlling terminal and exec ollama
void child_ds() {

    execlp("xterm", "xterm", "-hold", "-e", "bash", "-i", "-c", "ai_pandoc", (char *)0);
    perror("execlp");
    _exit(127);
}

void deepseek_intro() {
    clear_terminal();
    int input = 0;

    std::cout << "--------------------------------------------------\n";
    std::cout << "              WELCOME TO DEEPSEEK\n";
    std::cout << "--------------------------------------------------\n\n";
    sleep(1);

    while (input != 1 && input != 2) {
        std::cout << "1. Get Started\n";
        std::cout << "2. More Information\n";
        std::cout << "\nInput: ";
        std::cin >> input;
    }

    if (input == 2) {
        type_chars("\nDeepSeek is a Chinese AI company founded in 2023 and based in Hangzhou.\n");
        type_chars("Builds large-language models (LLMs) and generative AI tools that compete with major Western models.\n");
        type_chars("They offer chatbots, APIs, and apps for natural language, code generation, and vision-language tasks.\n");
    }

    type_chars("Great, let us begin!\n");
    type_chars("You are going to talk with r1-8b, which contains ~8 billion parameters.\n\n"); 

    std::cout << "----TYPE '/bye' TO EXIST----\n\n"; sleep(2);
}

void deepseek() {
    // deepseek_intro();

    for (;;) {
        pid_t pid = fork();
        if (pid < 0) {
            std::perror("fork");
            exit(1);
        }

        if (pid == 0) {
            child_ds();
        } else {
            // Parent: just wait; do not read stdin (so child owns the terminal)
            int status = 0;
            if (waitpid(pid, &status, 0) < 0) {
                perror("waitpid");
            }

            clear_terminal();

            // Ask to run again
            char answer;
            while (true) {
                std::cout << "Would you like to talk to 'r1' again? [Y/n]: ";
                std::cin >> answer;
                if (answer == 'Y' || answer == 'y') {
                    sleep(1);
                    break;
                } else if (answer == 'N' || answer == 'n') {
                    return;
                }
            }
        }
    }
}
