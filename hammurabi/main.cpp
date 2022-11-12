#include <iostream>
#include "Loader.hpp"

#define DEFAULT_SAVE_FILE_PATH "/Users/shahovaanastasia/Documents/C++ project/Labs/hammurabi/hammurabi/SaveGame.txt"


int main(int argc, const char * argv[]) {
    Loader game;
    game.Run(DEFAULT_SAVE_FILE_PATH);
    
    return 0;
}
