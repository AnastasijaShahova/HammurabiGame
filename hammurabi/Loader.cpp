#include "Loader.hpp"
#include "TextMessages.hpp"
#include <fstream>
#include <iostream>

void Loader::Run(const std::string& save_file_path)
{
    GameConditions conditionals;
    TextMessage text_message;
    GameValue *game_value = LoadGame(save_file_path);

    
    while (true)
    {
        const bool start_new_game = game_value == nullptr || text_message.StartNewGame();
        if (start_new_game)
        {
            delete game_value;
            game_value = new GameValue();
        }

        GamePlay game_play(&conditionals, game_value, &text_message);

        if (start_new_game)
        {
            game_play.FillDefaultValue();
            SaveGame(game_value, save_file_path);
        }

        bool is_play = true;
        while(is_play)
        {
            is_play = game_play.PlayYear();
            if (is_play && !game_value->is_ended)
            {
                if (!text_message.ContinueGame())
                    return;
                SaveGame(game_value, save_file_path);
            }
        }

        delete game_value;
        game_value = nullptr;
        std::remove(save_file_path.data());
        if (!text_message.RestartGame())
            return;
    }
}

GameValue* Loader::LoadGame(const std::string& save_file_path)
{
    
    std::fstream file(save_file_path, std::fstream::in);
    GameValue *game_value = nullptr;

    if (file.is_open()) {

        game_value = new GameValue();
        std::cout << "Загрузка сохраненной игры" << std::endl;
        std::string s;
        std::getline(file, s);
        game_value->year = std::stoi(s);
        
        std::getline(file, s);
        game_value->population = std::stoi(s);
        
        std::getline(file, s);
        game_value->millet = std::stoi(s);
        
        std::getline(file, s);
        game_value->acre_city = std::stoi(s);
        
        std::getline(file, s);
        game_value->acre_price = std::stoi(s);
        
        std::getline(file, s);
        game_value->is_plague = std::stoi(s);
        
        std::getline(file, s);
        game_value->is_ended = std::stoi(s);
        
        std::getline(file, s);
        game_value->died_person = std::stoi(s);
        
        std::getline(file, s);
        game_value->arrived_person = std::stoi(s);
        
        std::getline(file, s);
        game_value->rat_eaten_millet = std::stoi(s);
        
        std::getline(file, s);
        game_value->sum_millet = std::stoi(s);
        
        std::getline(file, s);
        game_value->millet_from_city = std::stoi(s);

        std::getline(file, s);
        game_value->death_rate_avg = std::stof(s);
        
        std::getline(file, s);
        game_value->acre_per_person = std::stof(s);
        
        std::getline(file, s);
        game_value->sum_death_rate = std::stof(s);
    }

    file.close();
    return game_value;
}

void Loader::SaveGame(GameValue *game_value, const std::string& save_file_path)
{
    std::fstream file(save_file_path, std::fstream::out);

    try {
        file << game_value->year << '\n' << game_value->population << '\n' << game_value->millet << '\n' << game_value->acre_city << '\n' << game_value->acre_price << '\n' << game_value->is_plague << '\n'
             << game_value->is_ended << '\n' << game_value->died_person << '\n' << game_value->arrived_person << '\n' << game_value->rat_eaten_millet << '\n' << game_value->sum_millet << '\n' << game_value->millet_from_city << '\n'
        << game_value->death_rate_avg << '\n' << game_value->acre_per_person << '\n' << game_value->sum_death_rate << '\n';

    } catch (...) {
        std::cout << "Не удалось сохранить игру" << std::endl;
        system("pause");
    }

    file.close();
}

