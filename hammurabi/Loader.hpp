#ifndef Loader_hpp
#define Loader_hpp

#include "GamePlay.hpp"
#include <string>

class Loader
{
public:
    void Run(const std::string& save_file_path);

private:
    GameValue *LoadGame(const std::string& save_file_path);
    void SaveGame(GameValue *game_value, const std::string& save_file_path);
};

#endif /* Loader_hpp */
