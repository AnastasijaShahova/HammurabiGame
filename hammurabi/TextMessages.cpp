#include "TextMessages.hpp"
#include "GamePlay.hpp"
#include <iostream>
#include <string>

void TextMessage::FirstMessageInFirstYear(const GameValue *value) const
{
    std::cout << "Мой повелитель, да начнется же твое правление.Впереди нас ждет очень непростой  первый год.\n"
              << "\tНа данный момент население твоего города " << value->population << " человек.\n"
              << "\tГород занимает " << value->acre_city << " акров земли\n"
              << "\tУ нас имеется " << value->millet << " бушелей пшеницы\n"
              << "\tОдин акр земли стоит " << value->acre_price << " бушелей" << std::endl;
}

void TextMessage::FirstMessage(const GameValue *value) const
{
    std::cout << "Мой повелитель, да начнется же твой " << value->year + 1 << " год правления\n";

    if (value->is_plague)
        std::cout << "\tЧума уничтожила половину населения; \n";

    std::cout << "\tНа данный момент население  города составляет " << value->population << " человек.\n"
    << "\tМы собрали " << value->sum_millet << " бушелей пшеницы, по " << value->millet_from_city << " бушеля с акра\n";
    
    if (value->rat_eaten_millet != 0)
        std::cout << "\tКрысы истребили " << value->rat_eaten_millet << " бушелей пшеницы, оставив " << value->millet << " бушеля в амбарах\n";
    else
        std::cout << "В амбарах находится " << value->millet << " бушелей\n";
    
    std::cout << "\tГород занимает " << value->acre_city << " акров земли\n"
              << "\tОдин акр земли стоит " << value->acre_price << " бушелей" << std::endl;
}

void TextMessage::ShowGameResult(const float deaath_rate_avg, const float acre_per_person, const EGameResult game_res) const
{
    std::cout << "Вот и закончилось Ваше правление\n"
              << "Среднегодовой процент умерших составил " << static_cast<int>(deaath_rate_avg * 100) << " % населения\n"
              << "На одного жителя приходится  " << acre_per_person << " акров земли" << std::endl;

    switch (game_res) {
    case EGameResult::Bad:
        std::cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. Теперь вы вынуждены влачить жалкое существование в изгнании" << std::endl;
        break;
    case EGameResult::Satisfactorily:
        std::cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем" << std::endl;
        break;
    case EGameResult::Good:
        std::cout << "Вы справились вполне неплохо,у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова" << std::endl;
        break;
    case EGameResult::Perfect:
        std::cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше" << std::endl;
        break;
    default:
        throw std::out_of_range("EGameResult");
    }
}

int TextMessage::CheckInput() const
{
    std::string number = "";
    int output = -1;
    do 
    {
        std::cin >> number;
        try 
        {
            output = std::stoi(number);
        }
        catch (...) 
        {
            std::cout << "Введите целое положительное число" << std::endl;
        }
        
    } while (output < 0);

    return output;
}

bool TextMessage::CheckBoolInput() const
{
    char y_n = ' ';
    do
    {
        std::cin >> y_n;
    } while (y_n != 'y' && y_n != 'n');
    
    if (y_n == 'y')
        return true;
    else
        return false;
}


int TextMessage::HowMuchLandToBuy() const
{
    std::cout << "Сколько акров земли ты хочешь купить? " << std::endl;
    return CheckInput();
}

int TextMessage::HowMuchLandToSell() const
{
    std::cout << "Сколько акров земли ты хочешь продать? ";
    return CheckInput();
}

int TextMessage::HowMuchMilletToEat() const
{
    std::cout << "Сколько бушелей пшеницы ты хочешь использовать в качестве еды? " << std::endl;;
    return CheckInput();
}

int TextMessage::HowMuchLandCultivate() const
{
    std::cout << "Сколько акров земли ты хочешь засеять? " << std::endl;
    return CheckInput();
}

bool TextMessage::StartNewGame() const
{
    std::cout << "Начать новую игру? (y/n) " << std::endl;;
    return CheckBoolInput();
}

bool TextMessage::RestartGame() const
{
    std::cout << "Начать сначала? (y/n) " << std::endl;
    return CheckBoolInput();
}

bool TextMessage::ContinueGame() const
{
    std::cout << "Игра сохранена. Продолжить игру? (y/n) " << std::endl;
    return CheckBoolInput();
}

void TextMessage::InvalidParametrMessage(const EReasonForError &reason) const
{
    switch (reason) {
    case AcreForBuyNotEnough:
        std::cout << "Недостаточно пшеницы для покупки ";
        break;
    case AcreForSellNotEnough:
        std::cout << "Недостаточно пшеницы для продажи ";
        break;
    case AcreToCultivateNotEnough:
        std::cout << "Недостаточно акров ";
        break;
    case MilletForPersonNotEnough:
        std::cout << "Недостаточно пшеницы для еды ";
        break;
    case PersonCultivateNotEnough:
        std::cout << "Недостаточно жителей для обработки акров земли ";
        break;
    case MilletForCultivate:
        std::cout << "Недостаточно пшеницы для посева ";
        break;
    default:
        break;
    }
}
