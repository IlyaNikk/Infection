#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "string"


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
    //void AddListener(ColorPoints** NewField, int StartX, int StartY, Sprite* Field, int* GreenScore, Sprite* GreenPoint, Label* GreenCount);
};

void AddListener(ColorPoints** NewField, int* StartX, int* StartY, Sprite* Field, int* GreenScore, Sprite* GreenPoint, Label* GreenCount,
                 char Color, Point* StartLocation);

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
bool newLocation(Point Start, Point End, int Step, bool Cant, int* Score){
    if(!Cant)
    {
        float ConditionX = (End.x - Start.x ) / Step;
        float ConditionY = (End.y - Start.y ) / Step;
        if (abs(ConditionX) > 2 || abs(ConditionY) > 2) {
            --Score[0];
           return false;
        }
        else if(ConditionX == 0 && ConditionY == 0) {
            --Score[0];
            return false;
        }
    }
    else {
        --Score[0];
        return false;
    }
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
void StarterPoint(ColorPoints** NewField,Sprite* Field, Sprite* ColorPoint, char WhatColor, int* StartX, int* StartY, int* GreenScore, Label* GreenCount,
                    Point* StartLocation, Point location){
    ColorPoint->setScale(0.95);

    ColorPoint->setPosition(0,0);
    ColorPoint->setOpacity(0);
    auto fadeIn = FadeIn::create(0.4f);
    auto move = MoveTo::create(2, location);

    auto spawn = Spawn::createWithTwoActions(fadeIn, move);
    ColorPoint->runAction(spawn);


    int* CurrentStop = new int [2];
    CurrentStop =  CanStopHere(location,StartX[0],StartY[0], NewField[0][0].GetStep(), CurrentStop);
    int Index1 = CurrentStop[0];
    int Index2 = CurrentStop[1];
    Sprite* Clone = Sprite::createWithTexture(ColorPoint->getTexture());
    Clone->setScale(ColorPoint->getScaleX(), ColorPoint->getScaleY());
    Clone->setPosition(0,0);
    Clone->setOpacity(0);
    Clone->setTag(Index2 * 10 + Index1 );
    //Clone->runAction(spawn);

    Field->addChild(Clone,3);
    Field->addChild(ColorPoint, 3);
    StartX[0] = NewField[Index2][Index1].GetStep() / 2 + 4;
    StartY[0] = NewField[Index2][Index1].GetStep() / 2 + 4;

    NewField[Index2][Index1].SetColor(WhatColor);
    NewField[Index2][Index1].SetColorEmpty(true);
    AddListener(NewField,StartX,StartY,Field, GreenScore, ColorPoint, GreenCount, WhatColor, StartLocation);
}

bool RemovePoint(ColorPoints** NewField, Sprite* Field, Sprite* ColorPoint, Point Start, Point End, int Step, int cloneIndex1, int cloneIndex2,
                 int Index1, int Index2, bool Cant){
    int BorderX = (End.x - Start.x) / Step;
    int BorderY = (End.y - Start.y) / Step;
    if((abs(BorderX) == 2 || abs(BorderY) == 2) && Cant) {
        NewField[cloneIndex2][cloneIndex1].SetColorEmpty(false);
        Field->removeChildByTag(cloneIndex2 * 10 + cloneIndex1, false);

        auto Clone = Sprite::createWithTexture(ColorPoint->getTexture());
        Clone->setScale(ColorPoint->getScaleX(), ColorPoint->getScaleY());
        Clone->setPosition(NewField[Index2][Index1].GetCoordinate());
        Clone->setTag(Index2 * 10 + Index1);
        Field->addChild(Clone, 3);
        return false;
    }
    else return true;
}


void AddListener(ColorPoints** NewField, int* StartX, int* StartY, Sprite* Field, int* GreenScore, Sprite* GreenPoint, Label* GreenCount,
                 char Color, Point* StartLocation){

        auto listener1 = EventListenerTouchOneByOne::create();

        //даем возможность перетаскивать фишки

        // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
        listener1->setSwallowTouches(true);

        // Example of using a lambda expression to implement onTouchBegan event callback function
        listener1->onTouchBegan = [NewField, StartLocation, StartX, StartY, Field, GreenScore, GreenPoint](
            Touch *touch, Event *event) mutable {

        // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
        auto target = static_cast<Sprite *>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        StartLocation[0] = Field->convertToNodeSpace(touch->getLocation());
        int *CurrentStop = new int[2];

        //ищем координаты начала движения и запоминаем их
        CurrentStop = CanStopHere(StartLocation[0], StartX[0], StartY[0], NewField[0][0].GetStep(), CurrentStop);
        int Index1 = CurrentStop[0];
        int Index2 = CurrentStop[1];
        StartLocation[0] = NewField[Index2][Index1].GetCoordinate();
        Size s = target->getContentSize();

        if (!NewField[Index2][Index1].GetEmptyColor())
            return false;

        Rect rect = Rect(0, 0, s.width, s.height);
        delete[] CurrentStop;
        //Check the click area
        if (rect.containsPoint(locationInNode)) {
            target->setOpacity(180);
            return true;
        }
        return false;
    };

//Trigger when moving touch
    listener1->onTouchMoved = [](Touch *touch, Event *event) {
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        //Move the position of current button sprite
        target->setPosition(target->getPosition() + touch->getDelta() * 2);
    };

    //Process the touch end event
    listener1->onTouchEnded = [Field, StartX, StartY, StartLocation, Color, NewField, GreenScore, GreenCount, GreenPoint](
            Touch *touch, Event *event) mutable {
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        target->setOpacity(255);
        Point locationInNode = target->getPosition();

        //ищем кординаты окончания движения и проверяем можем ли мы там остановиться
        int *CurrentStop = new int[2];
        CurrentStop = CanStopHere(locationInNode, StartX[0], StartY[0], NewField[0][0].GetStep(), CurrentStop);
        int Index1 = CurrentStop[0];
        int Index2 = CurrentStop[1];

        bool newLocate;
        if (!NewField[Index2][Index1].GetEmptyColor()) {
            if (NewField[Index2][Index1].GetEmpty()) {
                newLocate = newLocation(StartLocation[0], NewField[Index2][Index1].GetCoordinate(), NewField[Index2][Index1].GetStep(), true,
                                        GreenScore);
            }
            else
                newLocate = newLocation(StartLocation[0], NewField[Index2][Index1].GetCoordinate(), NewField[Index2][Index1].GetStep(), false,
                                        GreenScore);
        }
        else newLocate = false;
        if (newLocate) {

            auto Move = MoveTo::create(0.5, NewField[Index2][Index1].GetCoordinate());
            target->runAction(Move);
        }
        else {
            auto Move = MoveTo::create(0.5, StartLocation[0]);
            target->runAction(Move);
        }

        //удаляем фишку если сделан шаг 2
        int *cloneStart = new int[2];
        cloneStart = CanStopHere(StartLocation[0], StartX[0], StartY[0], NewField[0][0].GetStep(), cloneStart);
        int cloneIndex1 = cloneStart[0];
        int cloneIndex2 = cloneStart[1];


        if (RemovePoint(NewField, Field, GreenPoint, StartLocation[0],NewField[Index2][Index1].GetCoordinate(),
                        NewField[Index2][Index1].GetStep(), cloneIndex1, cloneIndex2, Index1, Index2, newLocate)){

            ++GreenScore[0];

            Sprite* CloneOnFinish = Sprite::createWithTexture(GreenPoint->getTexture());
            CloneOnFinish->setScale(GreenPoint->getScaleX(), GreenPoint->getScaleY());
            CloneOnFinish->setRotation(GreenPoint->getRotation());
            CloneOnFinish->setPosition(NewField[Index2][Index1].GetCoordinate());
            CloneOnFinish->setTag(Index2 * 10 + Index1 );
            CloneOnFinish->setOpacity(0);
            CloneOnFinish->runAction(FadeIn::create(1.0f));
            Field->addChild(CloneOnFinish,3);


            Sprite* CloneOnStart = Sprite::createWithTexture(GreenPoint->getTexture());
            CloneOnStart->setScale(GreenPoint->getScaleX(), GreenPoint->getScaleY());
            CloneOnStart->setRotation(GreenPoint->getRotation());
            CloneOnStart->setPosition(NewField[cloneIndex2][cloneIndex1].GetCoordinate());
            Field->addChild(CloneOnStart,3);

            Point* Start = new Point[1];
            Start[0] = StartLocation[0];
            AddListener(NewField,StartX,StartY,Field,GreenScore, CloneOnStart, GreenCount,Color, Start);
        }
        NewField[Index2][Index1].SetColor(Color);
        NewField[Index2][Index1].SetColorEmpty(true);

        //обновляем счет
        GreenCount->setString(std::to_string(GreenScore[0]));

        delete[] cloneStart;
        delete[] CurrentStop;
        //Reset zOrder and the display sequence will change
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, GreenPoint);
}
#endif //MYGAME_COORDINATE_H