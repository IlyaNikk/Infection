#include "HelloWorldScene.h"


#ifndef MYGAME_COORDINATE_H
#define MYGAME_COORDINATE_H

#endif //MYGAME_COORDINATE_H

class FieldAndPoints{
private:
    auto Field;
    auto EmptyPoints;
    auto Points;
    int Step;
public:
    FieldAndPoints();
    ~FieldAndPoints();

    float newLocation(int X, int Y, int Step);
};


float* newLocation(int X, int Y, int Step){
    float X1 = (X - 75) / Step;
    float Y1 = (Y - 75) / Step;
    int X2 = (X - 75) / Step;
    int Y2 = (Y - 75) / Step;
    float ConditionX = X1 - X2;
    float ConditionY = Y1 - Y2;
    if(ConditionX > 0.5)
        ++X2;
    if(ConditionY > 0.5)
        ++Y2;
    float Result[2] = {X2 * Step + 75, Y2 * Step + 75};
    return Result;
}
