#ifndef GamePLay_hpp
#define GamePLay_hpp

#include <stdio.h>

#include "GameConditions.h"
#include "TextMessages.hpp"

class GameValue
{
public:
    int year;
    int population;
    int millet;
    int acre_city;

    int acre_price;

    bool is_plague;
    bool is_ended;

    int died_person;
    int arrived_person;
    int rat_eaten_millet;
    int sum_millet;
    int millet_from_city;

    float death_rate_avg;
    float acre_per_person;
    float sum_death_rate;

    EGameResult game_result;

};

class GamePlay
{
public:
    GamePlay(GameConditions *conditions, GameValue *game_value, TextMessage *text_message);
    void FillDefaultValue() const;
    bool PlayYear() const;


private:
    GameConditions *conditions_;
    GameValue *game_value_;
    TextMessage *text_message_;

private:
    int GenerateAreaPrice() const;
    void CalculateValueForNextYear() const;
    void CalculateResult() const;
    void CheckGameEnd(const float death_rate_in_this_year) const;
    void CheckValidInput(int &millet_for_person, int &acre_to_cultivate) const;
};


#endif /* GamePLay_hpp */
