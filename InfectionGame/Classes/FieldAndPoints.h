#include "cocos2d.h"
#include "math.h"



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

/*
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
*/

FieldAndPoints** BuildRoundField(FieldAndPoints** NewField, double Step, Sprite * Field, double StartX, double StartY){

    double tempX = StartX;
    double tempY = StartY;
    double coef1 = 29;
    double coef2 = 0.25;
    int i = 25;
    
    for(int k=0; k < 4; k++){
            double x = -1;
        NewField[k] = new FieldAndPoints [25];
        for(int j = 0; j < i; ++j ){
            NewField[k][j].SetStep(Step);
            auto EmptyPoint = Sprite::create("Empty.png");
                NewField[k][j].setEmpty(false);
                Field->addChild(EmptyPoint);
                EmptyPoint->setOpacity(0);
                EmptyPoint->setPosition(0, 0);
                
                auto fadeIn = FadeIn::create(1.0f);
                auto move = MoveTo::create(1, Point(StartX, StartY));
                const cocos2d::Vec2 ddd = EmptyPoint->getPosition();
                
                auto spawn = Spawn::createWithTwoActions(fadeIn, move);
                EmptyPoint->runAction(spawn);
            
            StartX += sin(x)*coef1;
            StartY += cos(x)*coef1;
            x+=coef2;
        }
        if(k == 0){
            i -= 5;
            tempX += 17;
            tempY += 22;
            StartX = tempX;
            StartY = tempY;
            coef1 -= 1;
            coef2 += 0.065;
        }
        if(k == 1){
            i -= 6;
            tempX += 14;
            tempY += 25;
            StartX = tempX;
            StartY = tempY;
            coef1 -= 1;
            coef2 += 0.13;
        
        }
        if(k == 2){
            i -= 6;
            tempX += 16;
            tempY += 23.5;
            StartX = tempX;
            StartY = tempY;
            coef1 -= 1;
            coef2 += 0.33;
            
        }
        /*
        if(k == 3){
            i -= 7;
            tempX += 8;
            tempY += 23;
            StartX = tempX;
            StartY = tempY;
            
        }
        if(k == 4){
            tempX += -3;
            tempY += 22;
            StartX = tempX;
            StartY = tempY;
            
        }
*/

        }

    return NewField;
}

int getCoordinate(int StartX, int StartY, int Radius){
  
    return 1;
}


#endif //MYGAME_COORDINATE_H