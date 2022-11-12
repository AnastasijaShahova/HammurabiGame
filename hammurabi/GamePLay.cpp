#include "GamePLay.hpp"
#include "Random.h"
#include<iostream>

GamePlay::GamePlay(GameConditions *conditions, GameValue *game_value, TextMessage *text_message) :
    conditions_(conditions), game_value_(game_value), text_message_(text_message)
{
}

void GamePlay::FillDefaultValue() const
{
    game_value_->population = conditions_->start_population;
    game_value_->millet = conditions_->start_bush_millet;
    game_value_->acre_city = conditions_->start_acre_city;
    game_value_->acre_price = GenerateAreaPrice();
}

int GamePlay::GenerateAreaPrice() const
{
    Distribution generator;
    return generator.random(conditions_->min_acre_price, conditions_->max_acre_price).Mt19937();
}

bool GamePlay::PlayYear() const
{
    if (game_value_->is_ended) {
        text_message_->ShowGameResult(game_value_->death_rate_avg, game_value_->acre_per_person, game_value_->game_result);
        return false;
    }
    
    if (game_value_->year == 0)
        text_message_->FirstMessageInFirstYear(game_value_);
    else
        text_message_->FirstMessage(game_value_);

    CalculateValueForNextYear();
    return true;
}

void GamePlay::CalculateValueForNextYear() const
{
    int millet_for_person = 0;
    int acre_for_cultivate = 0;

    CheckValidInput(millet_for_person, acre_for_cultivate);

    Distribution generator;

    const int survied_people = millet_for_person == 0 ? 0 : millet_for_person / conditions_->millet_for_person;
    game_value_->died_person = survied_people >= game_value_->population ? 0 : game_value_->population - survied_people;
    float death_rate_in_this_year = static_cast<float>(game_value_->died_person) / game_value_->population;
    game_value_->sum_death_rate += death_rate_in_this_year;

    game_value_->millet_from_city =  generator.random(conditions_->min_count_millet, conditions_->max_count_millet).Mt19937();
    game_value_->sum_millet = game_value_->millet_from_city * acre_for_cultivate;
    game_value_->millet =  game_value_->millet + game_value_->sum_millet;

    const float rat_damage_for_millet_ = game_value_->millet * generator.random(conditions_->min_rat_damage, conditions_->max_rat_damage).RealDistribution();;
    game_value_->rat_eaten_millet = static_cast<int>(std::ceilf(rat_damage_for_millet_));
    game_value_->millet =  game_value_->millet - game_value_->rat_eaten_millet;

    game_value_->acre_price = GenerateAreaPrice();

    const float arrived_persons = game_value_->died_person / 2.0f + (5.0f - game_value_->millet_from_city) * game_value_->sum_millet / 600.0f + 1;

    game_value_->arrived_person = std::max(std::min(static_cast<int>(arrived_persons),conditions_->max_arrive_people), conditions_->min_arrive_people);

     game_value_->population =  game_value_->population - game_value_->died_person + game_value_->arrived_person;


     game_value_->is_plague = generator.random(0.0f, 1.0f).Mt19937() <= conditions_->chance_plague;
     if (game_value_->is_plague)
         game_value_->population = game_value_->population / 2;

     ++game_value_->year;
     CheckGameEnd(death_rate_in_this_year);
}

void GamePlay::CheckGameEnd(const float death_rate_in_this_year) const
{
    if (death_rate_in_this_year > conditions_->death_rate)
    {
        game_value_->is_ended = true;
        game_value_->game_result = Bad;
        game_value_->death_rate_avg = game_value_->sum_death_rate / (game_value_->year );
        game_value_->acre_per_person = static_cast<float>(game_value_->acre_city) / game_value_->population;
        
    }

    if (game_value_->year == conditions_->rounds_count)
    {
        game_value_->is_ended = true;
        CalculateResult();
    }
}

void GamePlay::CalculateResult() const
{
    game_value_->death_rate_avg = game_value_->sum_death_rate / game_value_->year;
    game_value_->acre_per_person = static_cast<float>(game_value_->acre_city) / game_value_->population;

    if (game_value_->death_rate_avg > 0.33f &&  game_value_->acre_per_person < 7)
        game_value_->game_result = Bad;
    else if (game_value_->death_rate_avg > 0.1f &&  game_value_->acre_per_person < 9)
        game_value_->game_result = Satisfactorily;
    else if (game_value_->death_rate_avg > 0.03f &&  game_value_->acre_per_person < 10)
        game_value_->game_result = Good;
    else
        game_value_->game_result = Perfect;
}

void GamePlay::CheckValidInput(int &millet_for_person, int &acre_to_cultivate) const
{
    int acre_left;
    int millet_left;

    while (true)
    {
        acre_left = game_value_->acre_city;
        millet_left = game_value_->millet;

        const int acre_to_buy = text_message_->HowMuchLandToBuy();
        acre_left += acre_to_buy;

        if (acre_to_buy * game_value_->acre_price > game_value_->millet)
        {
            text_message_->InvalidParametrMessage(EReasonForError::AcreForBuyNotEnough);
            continue;
        }

        const int acre_to_sell = text_message_->HowMuchLandToSell();
        acre_left -= acre_to_sell;
        millet_left += game_value_->acre_price * acre_to_sell;

        if (acre_to_sell > game_value_->acre_city)
        {
            text_message_->InvalidParametrMessage(EReasonForError::AcreForSellNotEnough);
            continue;
        }

        millet_for_person = text_message_->HowMuchMilletToEat();
        if (millet_for_person > game_value_->millet)
        {
            text_message_->InvalidParametrMessage(EReasonForError::MilletForPersonNotEnough);
            continue;
        }

        millet_left -= millet_for_person;
        if (millet_left < 0)
        {
            text_message_->InvalidParametrMessage(EReasonForError::MilletForPersonNotEnough);
            continue;
        }

        acre_to_cultivate = text_message_->HowMuchLandCultivate();
        if (acre_to_cultivate > acre_left)
        {
            text_message_->InvalidParametrMessage(EReasonForError::AcreToCultivateNotEnough);
            continue;
        }

        if (acre_to_cultivate > game_value_->population * conditions_->max_cultivates_acre)
        {
            text_message_->InvalidParametrMessage(EReasonForError::PersonCultivateNotEnough);
            continue;
        }

        millet_left -= static_cast<int>(std::ceilf(acre_to_cultivate * conditions_->millet_for_acre));
        if (millet_left < 0)
        {
            text_message_->InvalidParametrMessage(EReasonForError::MilletForCultivate);
            continue;
        }

        break;
    }

    game_value_->millet = millet_left;
    game_value_->acre_city = acre_left;
}
