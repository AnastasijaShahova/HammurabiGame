#ifndef GameConditions_h
#define GameConditions_h

struct GameConditions
{

    const unsigned short rounds_count = 10;

    const int start_population = 100;
    const int start_bush_millet = 2800;
    const int start_acre_city = 1000;

    //Данные для контроля
    const int millet_for_person = 20;
    const float millet_for_acre = 0.5f;
    const int max_cultivates_acre = 10;

    //Для завершения игры
    const float death_rate = 0.45f;

    //Мин и макс цена акра
    const int min_acre_price = 17;
    const int max_acre_price = 26;

    //Мин и макс кол-во пшеницы с акра
    const int min_count_millet = 1;
    const int max_count_millet = 6;

    //
    const float max_rat_damage = 0.07f;
    const float min_rat_damage = 0.0f;

    //Мин и макс кол-во  прибывшх жителей
    const int min_arrive_people = 0;
    const int max_arrive_people = 50;

    const float chance_plague = 0.15f;
};


#endif /* GameConditions_h */
