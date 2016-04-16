#include "HelloWorldScene.h"
#include "cocos2d.h"


#ifndef MYGAME_COORDINATE_H
#define MYGAME_COORDINATE_H

using namespace cocos2d;

class FieldAndPoints : cocos2d::Sprite{
private:
    int Step;
    bool IsEmpty;
public:
    FieldAndPoints();
    ~FieldAndPoints();
    void SetStep(int newStep) { Step = newStep; };
    void setEmpty(bool newEmpty) {IsEmpty = newEmpty;};
    int GetStep(){return Step;};
    bool GetEmpty(){return IsEmpty;};
    float newLocation(int X, int Y, int Step);
};

FieldAndPoints::FieldAndPoints() {
        IsEmpty = true;
}

FieldAndPoints::~FieldAndPoints() {; }


int* CanStopHere(Point locationInNode, int StartX, int StartY){
    int Result[2];
    Result[0] = (int)(locationInNode.x - StartX) / 75;
    Result[1] = (int)(locationInNode.y - StartY) / 75;
    return Result;
}

float* newLocation(Point Start, Point End, int Step, bool Cant){
    float Result[2];
    Result[0] = Start.x;
    Result[1] = Start.y;
    if(Cant){
        ;
    }
        else {
        float ConditionX = (End.x - Start.x - Step / 2) / Step;
        float ConditionY = (End.y - Start.y - Step / 2) / Step;
        if (ConditionX > 2 || ConditionY > 2) {
           return Result;
        }
        float X = (int) (ConditionX * 10) % 10;
        float Y = (int) (ConditionY * 10) % 10;
        if (X >= 7)
            ++ConditionX;
        if (Y >= 7)
            ++ConditionY;
        Result[0] =  ((int)ConditionX) * Step + 75;
        Result[1] =  ((int)ConditionY) * Step + 75;
    }
    return Result;
}

FieldAndPoints** BuildField(FieldAndPoints** NewField, int Step, auto Field, int StartX, int StartY){
    for(int i = 0; i < 10; ++i) {
        int None = rand() % 10;
        NewField[i] = new FieldAndPoints [10];
        for(int j = 0; j < 10; ++j ){
            NewField[i][j].SetStep(Step);
            auto EmptyPoint = Sprite::create("Empty.png");
            if(j != None) {
                NewField[i][j].setEmpty(false);
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
        StartX = 75;
        StartY += Step;
    }
    return NewField;
}


#endif //MYGAME_COORDINATE_H