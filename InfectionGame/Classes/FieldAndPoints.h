#include "HelloWorldScene.h"
#include "cocos2d.h"


#ifndef MYGAME_COORDINATE_H
#define MYGAME_COORDINATE_H

using namespace cocos2d;

class FieldAndPoints : cocos2d::Sprite{
private:
    auto EmptyPoints;
    auto GreenPoints;
    auto BluePoints;
    int Step;
public:
    FieldAndPoints();
    ~FieldAndPoints();

    float newLocation(int X, int Y, int Step);
};

FieldAndPoints::FieldAndPoints() {
    EmptyPoints = Sprite::create("Empty.png");
    GreenPoints = Sprite::create("Green.png");
    BluePoints = Sprite::create("Blue.png");
}


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

#endif //MYGAME_COORDINATE_H