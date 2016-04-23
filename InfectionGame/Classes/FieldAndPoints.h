#include "HelloWorldScene.h"
#include "cocos2d.h"


#ifndef MYGAME_COORDINATE_H
#define MYGAME_COORDINATE_H

using namespace cocos2d;

class FieldAndPoints : cocos2d::Sprite{
protected:
    int Step;
    bool IsEmpty;
    Point Coordinate;

public:
    FieldAndPoints();
    ~FieldAndPoints();
    void SetStep(int newStep) { Step = newStep; };
    void setEmpty(bool newEmpty) {IsEmpty = newEmpty;};
    int GetStep(){return Step;};
    bool GetEmpty(){return IsEmpty;};
    void SetCoordinate(Point newCoordinate){Coordinate = newCoordinate;};
    Point GetCoordinate(){return Coordinate;};

};

class ColorPoints : public FieldAndPoints{
private:
    char Color;
    bool isColor;

public:
    ColorPoints();
    ~ColorPoints();
    ColorPoints(const ColorPoints&);
    void SetColor(char newColor){Color = newColor;};
    void SetColorEmpty(char newIsColor){isColor = newIsColor;};
    bool GetEmptyColor(){return isColor;};
    char GetColor(){return isColor;};
    ColorPoints& operator= (const ColorPoints& other);
};

FieldAndPoints::FieldAndPoints() {
    IsEmpty = true;

}

FieldAndPoints::~FieldAndPoints() {; }

ColorPoints::ColorPoints() {
    isColor = false;
}

ColorPoints::ColorPoints(const ColorPoints& other){
    IsEmpty = other.IsEmpty;
    isColor = other.isColor;
    Color = other.Color;
    Step  = other.Step;
    Coordinate = other.Coordinate;
}


ColorPoints& ColorPoints::operator= ( const ColorPoints& other){
    IsEmpty = other.IsEmpty;
    isColor = other.isColor;
    Color = other.Color;
    Step  = other.Step;
    Coordinate = other.Coordinate;
    return *this;
}

ColorPoints::~ColorPoints(){; }

//по координатам находим индексы фишки в массиве
int* CanStopHere(Point locationInNode, int StartX, int StartY,int Step, int* Result){
    float PromResult[2];
    PromResult[0] = (locationInNode.x - StartX) / Step;
    PromResult[1] = (locationInNode.y - StartY) / Step;
    float X =  (PromResult[0] * 10) ;
    X = (int)X % 10;
    float Y =  (PromResult[1] * 10);
    Y = (int)Y % 10;
    if (X >= 4)
        ++PromResult[0];
    if (Y >= 4)
        ++PromResult[1];
    Result[0] = PromResult[0];
    Result[1] = PromResult[1];
    return Result;
}

//проверяем куда мы передвигаем фишку и делаем это, если возможно
bool newLocation(Point Start, Point End, int Step, bool Cant){
    Point Result;
    Result.x = Start.x;
    Result.y = Start.y;
    if(!Cant)
    {
        float ConditionX = (End.x - Start.x ) / Step;
        float ConditionY = (End.y - Start.y ) / Step;
        if (abs(ConditionX) > 2 || abs(ConditionY) > 2) {
           return false;
        }
        else if(ConditionX == 0 && ConditionY == 0)
            return false;
    }
    else
        return false;
    return true;
}

//строим поле
ColorPoints** BuildField(ColorPoints** NewField, int Step, Sprite* Field, int StartX, int StartY){
    int Start = StartX;
    for(int i = 0; i < 10; ++i) {
        int None = rand() % 10;
        while ((i == 0 || i == 9) && (None == 0 || None ==9))
            None = rand() % 10;
        NewField[i] = new ColorPoints [10];
        for(int j = 0; j < 10; ++j ){
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
        StartX = Start;
        StartY += Step;
    }
    return NewField;
}

//задаем игровые начальные фишки
void StarterPoint(ColorPoints** NewField,Sprite* Field, Sprite* ColorPoint, char WhatColor, int StartX, int StartY){
    ColorPoint->setScale(0.95);
    Field->addChild(ColorPoint, 3);
    ColorPoint->setPosition(0,0);
    ColorPoint->setOpacity(0);
    auto fadeIn = FadeIn::create(0.4f);
    auto move = MoveTo::create(1, Point(StartX, StartY));

    auto spawn = Spawn::createWithTwoActions(fadeIn, move);
    ColorPoint->runAction(spawn);

    Point location = Point(StartX, StartY);
    int* CurrentStop = new int [2];
    CurrentStop =  CanStopHere(location,StartX,StartY, NewField[0][0].GetStep(), CurrentStop);
    int Index1 = CurrentStop[0];
    int Index2 = CurrentStop[1];
    NewField[Index2][Index1].SetColor(WhatColor);
    NewField[Index2][Index1].SetColorEmpty(true);
}

ColorPoints RemovePoint(ColorPoints NewField,Sprite* Field, Sprite* Empty, Point Start, Point End, int Step){
    int BorderX = (End.x - Start.x) / Step;
    int BorderY = (End.y - Start.y) / Step;
    if(abs(BorderX) == 2 || abs(BorderY) == 2){
        NewField.SetColorEmpty(false);
        Empty->setPosition(Start);
        Field->addChild(Empty,3);
        auto fadeIn = FadeIn::create(1.0f);
        Empty->setOpacity(0);
        Empty->runAction(fadeIn);
    }
    return NewField;
}


#endif //MYGAME_COORDINATE_H