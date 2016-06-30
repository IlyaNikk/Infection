#include "cocos2d.h"


#ifndef MYGAME_COORDINATE_H3
#define MYGAME_COORDINATE_H3

using namespace cocos2d;

class FieldAndPoints3 : cocos2d::Sprite{
protected:
    int Step;
    bool IsEmpty;
    Point Coordinate;
    
public:
    FieldAndPoints3();
    ~FieldAndPoints3();
    void SetStep(int newStep) { Step = newStep; };
    void setEmpty(bool newEmpty) {IsEmpty = newEmpty;};
    int GetStep(){return Step;};
    bool GetEmpty(){return IsEmpty;};
    void SetCoordinate(Point newCoordinate){Coordinate = newCoordinate;};
    Point GetCoordinate(){return Coordinate;};
};

class ColorPoints3 : public FieldAndPoints3{
private:
    char Color;
    bool isColor;
    
public:
    ColorPoints3();
    ~ColorPoints3();
    void SetColor(char newColor){Color = newColor;};
    void SetIsEmpty(char newIsColor){isColor = newIsColor;};
    bool GetEmptyColor(){return isColor;};
    char GetColor(){return isColor;};
};

FieldAndPoints3::FieldAndPoints3() {
    IsEmpty = true;
    
}

FieldAndPoints3::~FieldAndPoints3() {; }

ColorPoints3::ColorPoints3() {
    isColor = false;
}

ColorPoints3::~ColorPoints3(){; }

/*
//по координатам находим индексы фишки в массиве
int* CanStopHere(Point locationInNode, int StartX, int StartY,int Step){
    int Result[2];
    Result[0] = (int)(locationInNode.x - StartX) / Step;
    Result[1] = (int)(locationInNode.y - StartY) / Step;
    return Result;
}
 */
/*
//проверяем куда мы передвигаем фишку и делаем это, если возможно
Point newLocation(Point Start, Point End, int Step, bool Cant){
    Point Result;
    Result.x = Start.x;
    Result.y = Start.y;
    if(Cant){
        ;
    }
    else
    {
        float ConditionX = (End.x - Start.x ) / Step;
        float ConditionY = (End.y - Start.y ) / Step;
        if (abs(ConditionX) > 2 || abs(ConditionY) > 2) {
            return Result;
        }
        else if(ConditionX == 0 && ConditionY == 0)
            return Result;
        float X = (int) (ConditionX * 10) % 10;
        float Y = (int) (ConditionY * 10) % 10;
        if (X >= 6)
            ++ConditionX;
        if (Y >= 6)
            ++ConditionY;
        Result.x =  ((int)ConditionX) * Step + 75;
        Result.y =  ((int)ConditionY) * Step + 75;
    }
    return Result;
}
 */

ColorPoints3** BuildField(ColorPoints3** NewField, int Step, Sprite * Field, int StartX, int StartY){
    int Start = StartX;
    double StepX2 = 0;
    for(int i = 0; i < 10; ++i) {
        int None = rand() % 10;
        NewField[i] = new ColorPoints3 [10];
        for(int j = 0; j < 10-i; ++j ){
            NewField[i][j].SetStep(Step);
            auto EmptyPoint = Sprite::create("Empty.png");
            if(j != None) {
                Point CurrentLocation;
                CurrentLocation.x = StartX;
                CurrentLocation.y = StartY;
                NewField[i][j].setEmpty(false);
                NewField[i][j].SetCoordinate(CurrentLocation);
                NewField[i][j].SetStep(Step);
                Field->addChild(EmptyPoint);
                EmptyPoint->setOpacity(0);
                EmptyPoint->setPosition(0, 0);
                
                auto fadeIn = FadeIn::create(1.0f);
                auto move = MoveTo::create(1, Point(StartX, StartY));
                
                auto spawn = Spawn::createWithTwoActions(fadeIn, move);
                EmptyPoint->runAction(spawn);
            }
            else NewField[i][j].setEmpty(true);
            StartX += Step;
        }
        StepX2 += 13.2;
        StartX =Start+StepX2;
        StartY += Step;
    }
    return NewField;
}


#endif //MYGAME_COORDINATE_H3