#ifndef TYPE_CHAR_H
#define TYPE_CHAR_H

#include <iostream>
#include <sys/wait.h>  // wait()
#include <signal.h>     // kill(), SIGTERM
#include <unistd.h>
#include <chrono>
#include <thread>
#include <termios.h>  // terminal input
#include <fcntl.h>
#include <errno.h>
#include <iomanip>
#include <csignal>


#include <string>
#include <vector>

void type_chars(const std::string& text = "", std::chrono::milliseconds per_char = std::chrono::milliseconds(60), bool newline_at_end = true);

void loading(const std::string& msg, int time);

int play_again(std::string category);

void clear_terminal();

// char getch();

// void make_stdio_blocking();

std::string setColor(std::string color);

void image(std::string file_name);


#endif