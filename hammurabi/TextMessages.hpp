#ifndef TextMessages_hpp
#define TextMessages_hpp

#include "EGameResult.h"

enum EReasonForError {
    MilletForPersonNotEnough,
    AcreForBuyNotEnough,
    AcreForSellNotEnough,
    AcreToCultivateNotEnough,
    PersonCultivateNotEnough,
    MilletForCultivate
};

class GameValue;

class TextMessage
{
public:
    void FirstMessageInFirstYear(const GameValue *value) const;
    void FirstMessage(const GameValue *value) const;
    void ShowGameResult(const float deaath_rate_avg, const float acre_per_person, const EGameResult game_res) const;
    void InvalidParametrMessage(const EReasonForError &reason) const;
    int HowMuchLandToBuy() const;
    int HowMuchLandToSell() const;
    int HowMuchMilletToEat() const;
    int HowMuchLandCultivate() const;
    bool StartNewGame() const;
    bool RestartGame() const;
    bool ContinueGame() const;
    bool CheckBoolInput() const;
    int CheckInput() const;
    EReasonForError reason;
};
#endif /* TextMessages_hpp */
