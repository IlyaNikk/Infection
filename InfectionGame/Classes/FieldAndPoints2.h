//#include "GameScene.h"
#include "cocos2d.h"
#include "string"


#ifndef MYGAME_COORDINATE_H
#define MYGAME_COORDINATE_H

using namespace cocos2d;

class FieldAndPoints2 : cocos2d::Sprite{
protected:
    int StartX;
    int StartY;
    int Step;
    bool IsEmpty;
    Point Coordinate;
    
public:
    FieldAndPoints2();
    ~FieldAndPoints2();
    void SetStep(int newStep) { Step = newStep; };
    void setEmpty(bool newEmpty) {IsEmpty = newEmpty;};
    int GetStep(){return Step;};
    bool GetEmpty(){return IsEmpty;};
    void SetCoordinate(Point newCoordinate){Coordinate = newCoordinate;};
    Point GetCoordinate(){return Coordinate;};
    void SetStartX(int newSartX){StartX = newSartX;};
    void SetStartY(int newStartY){StartY = newStartY;};
    int GetStartX(){return StartX;};
    int GetStartY(){return StartY;};
};

class ColorPoints2 : public FieldAndPoints2{
private:
    char Color;
    bool isColor;
    
public:
    ColorPoints2();
    ~ColorPoints2();
    ColorPoints2(const ColorPoints2&);
    void SetColor(char newColor){Color = newColor;};
    void SetColorEmpty(bool newIsColor){isColor = newIsColor;};
    bool GetEmptyColor(){return isColor;};
    char GetColor(){return Color;};
    ColorPoints2& operator= (const ColorPoints2& other);
//    friend  void AddListener(ColorPoints2** NewField, int StartX, int StartY, Sprite* Field, int* GreenScore, Sprite* GreenPoint, Label* GreenCount);
};

void AddListener(ColorPoints2** NewField, Sprite* Field, int* TotalScore, Sprite* ColorPoint, Label** TotalCount,
                 Point* StartLocation, char* ColorTurn, int* Turn, int Players);

FieldAndPoints2::FieldAndPoints2() {
    IsEmpty = true;
}


FieldAndPoints2::~FieldAndPoints2() {; }

ColorPoints2::ColorPoints2() {
    isColor = false;
}

ColorPoints2::ColorPoints2(const ColorPoints2& other){
    IsEmpty = other.IsEmpty;
    isColor = other.isColor;
    Color = other.Color;
    Step  = other.Step;
    Coordinate = other.Coordinate;
}


ColorPoints2& ColorPoints2::operator= ( const ColorPoints2& other){
    IsEmpty = other.IsEmpty;
    isColor = other.isColor;
    Color = other.Color;
    Step  = other.Step;
    Coordinate = other.Coordinate;
    return *this;
}

ColorPoints2::~ColorPoints2(){; }



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
    if(!Cant)
    {
        float ConditionX = (End.x - Start.x ) / Step;
        float ConditionY = (End.y - Start.y ) / Step;
        if (abs(ConditionX) > 2 || abs(ConditionY) > 2) {
            return false;
        }
        else if(ConditionX == 0 && ConditionY == 0) {
            return false;
        }
    }
    else {
        return false;
    }
    return true;
}

//задаем игровые начальные фишки
void StarterPoint(ColorPoints2** NewField,Sprite* Field, Sprite* ColorPoint, char WhatColor, int* TotalScore, Label** TotalCount,
                  Point* StartLocation, Point location, char* ColorTurn, int* Turn, int Players){
    ColorPoint->setScale(0.95);
    
    ColorPoint->setPosition(5 * NewField[0][0].GetStep(), 5 * NewField[0][0].GetStep());
    ColorPoint->setOpacity(0);
    auto fadeIn = FadeIn::create(0.4f);
    auto move = MoveTo::create(1, location);
    auto spawn = Spawn::createWithTwoActions(fadeIn, move);
    ColorPoint->runAction(spawn);
    
    int* CurrentStop = new int [2];
    CurrentStop =  CanStopHere(location,NewField[0][0].GetStartX(),NewField[0][0].GetStartY(), NewField[0][0].GetStep(), CurrentStop);
    int Index1 = CurrentStop[0];
    int Index2 = CurrentStop[1];
    Sprite* Clone = Sprite::createWithTexture(ColorPoint->getTexture());
    Clone->setScale(ColorPoint->getScaleX(), ColorPoint->getScaleY());
    Clone->setPosition(5 * NewField[0][0].GetStep(), 5 * NewField[0][0].GetStep());
    Clone->setOpacity(0);
    Clone->setTag(Index2 * 10 + Index1 );
    ColorPoint->setTag(Index2 * 10000 + Index1 * 1000 + 100);
    
    Field->addChild(Clone,3);
    Field->addChild(ColorPoint, 3);
    
    NewField[Index2][Index1].SetColor(WhatColor);
    NewField[Index2][Index1].SetColorEmpty(true);

    AddListener(NewField, Field, TotalScore, ColorPoint, TotalCount, StartLocation,ColorTurn, Turn, Players);
}

bool RemovePoint(ColorPoints2** NewField, int cloneIndex1,int cloneIndex2, Point Start, Point End, int Step, bool Cant){
    int BorderX = (End.x - Start.x) / Step;
    int BorderY = (End.y - Start.y) / Step;
    if((abs(BorderX) == 2 || abs(BorderY) == 2) && Cant) {
        NewField[cloneIndex2][cloneIndex1].SetColorEmpty(false);
        return true;
    }
    else {
        NewField[cloneIndex2][cloneIndex1].SetColorEmpty(true);
        return false;
    }
}

void SetSpriteWithClone(ColorPoints2** NewField, Sprite* Field, int Index1, int Index2, Sprite* ColoredPoint, int* TotalScore,
                        Label** TotalCount, Point* Start, char* ColorTurn, int* Turn, int Players){
    
    Sprite *CloneStatic = Sprite::createWithTexture(ColoredPoint->getTexture());
    CloneStatic->setScale(ColoredPoint->getScaleX(), ColoredPoint->getScaleY());
    CloneStatic->setRotation(ColoredPoint->getRotation());
    CloneStatic->setPosition(NewField[Index2][Index1].GetCoordinate());
    CloneStatic->setTag(Index2 * 10 + Index1 );
    CloneStatic->setOpacity(0);
    CloneStatic->runAction(FadeIn::create(1.0f));
    Field->addChild(CloneStatic,3);
    
    Sprite *CloneMoving = Sprite::createWithTexture(ColoredPoint->getTexture());
    CloneMoving->setScale(ColoredPoint->getScaleX(), ColoredPoint->getScaleY());
    CloneMoving->setRotation(ColoredPoint->getRotation());
    CloneMoving->setPosition(NewField[Index2][Index1].GetCoordinate());
    CloneMoving->setTag(Index2 * 10000 + Index1 * 1000 + 100);
    CloneMoving->setOpacity(0);
    CloneMoving->runAction(FadeIn::create(1.0f));
    Field->addChild(CloneMoving,3);

    AddListener(NewField,Field,TotalScore, CloneMoving, TotalCount,Start, ColorTurn, Turn, Players);
    
}

void ChangeColor(ColorPoints2** NewField, Sprite* Field, int Index1, int Index2, Sprite* ColoredPoint,
                 int* TotalScore, Label** TotalCount, Point* Start, char* ColorTurn, int* Turn, int Players){
    
    for(int i = Index2 - 1; i <= Index2 + 1; ++i){
        if( i >= 0 && i <= 9) {
            for (int j = Index1 - 1; j <= Index1 + 1; ++j) {
                if( j >= 0 && j <= 9) {
                    if (NewField[i][j].GetEmptyColor() && !NewField[i][j].GetEmpty()) {
                        Field->removeChildByTag(i * 10 + j, false);
                        Field->removeChildByTag(i * 10000 + j * 1000 + 100, false);
                        SetSpriteWithClone(NewField, Field, j, i, ColoredPoint, TotalScore, TotalCount, Start, ColorTurn, Turn, Players);
                        if(NewField[i][j].GetColor() == ColorTurn[0] && NewField[Index2][Index1].GetColor() != ColorTurn[0])
                            --TotalScore[0];
                        else if(NewField[i][j].GetColor() == ColorTurn[1] && NewField[Index2][Index1].GetColor() != ColorTurn[1])
                            --TotalScore[1];
                        else if(NewField[i][j].GetColor() == ColorTurn[2] && NewField[Index2][Index1].GetColor() != ColorTurn[2])
                            --TotalScore[2];
                        else if(NewField[i][j].GetColor() == ColorTurn[3] && NewField[Index2][Index1].GetColor() != ColorTurn[3])
                            --TotalScore[3];
                        NewField[i][j].SetColor(ColorTurn[Turn[0] % Players]);
                        NewField[i][j].SetColorEmpty(true);
                        ++TotalScore[Turn[0] % Players];
                    }
                }
            }
        }
    }
}


void AddListener(ColorPoints2** NewField, Sprite* Field, int* TotalScore, Sprite* ColorPoint, Label** TotalCount,
                 Point* StartLocation, char* ColorTurn, int* Turn, int Players){
    
    auto listener1 = EventListenerTouchOneByOne::create();
    
    //даем возможность перетаскивать фишки
    
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    listener1->setSwallowTouches(true);
    
    // Example of using a lambda expression to implement onTouchBegan event callback function
    listener1->onTouchBegan = [NewField, StartLocation, Field, TotalScore, ColorTurn, Turn, Players](
                                                                                                     Touch *touch, Event *event) mutable {
        
        // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        
        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        StartLocation[0] = Field->convertToNodeSpace(touch->getLocation());
        int *CurrentStop = new int[2];
        
        //ищем координаты начала движения и запоминаем их
        CurrentStop = CanStopHere(StartLocation[0], NewField[0][0].GetStartX(), NewField[0][0].GetStartY(), NewField[0][0].GetStep(), CurrentStop);
        int Index1 = CurrentStop[0];
        int Index2 = CurrentStop[1];
        StartLocation[0] = NewField[Index2][Index1].GetCoordinate();
        Size s = target->getContentSize();
        
        if (!NewField[Index2][Index1].GetEmptyColor())
            return false;
        if (NewField[Index2][Index1].GetColor() != ColorTurn[Turn[0] % Players])
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
        //Move the position of current button sprit
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    //Process the touch end event
    listener1->onTouchEnded = [Field, StartLocation, NewField, TotalScore, TotalCount, ColorPoint, ColorTurn, Turn, Players](
                                                                                                                             Touch *touch, Event *event) mutable {
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        target->setOpacity(255);
        Point locationInNode = target->getPosition();
        
        //ищем кординаты окончания движения и проверяем можем ли мы там остановиться
        int *CurrentStop = new int[2];
        CurrentStop = CanStopHere(locationInNode, NewField[0][0].GetStartX(), NewField[0][0].GetStartY(), NewField[0][0].GetStep(), CurrentStop);
        int Index1 = CurrentStop[0];
        int Index2 = CurrentStop[1];
        
        bool newLocate;
        if (!NewField[Index2][Index1].GetEmptyColor()) {
            if (NewField[Index2][Index1].GetEmpty()) {
                newLocate = newLocation(StartLocation[0], NewField[Index2][Index1].GetCoordinate(), NewField[Index2][Index1].GetStep(), true);
            }
            else
                newLocate = newLocation(StartLocation[0], NewField[Index2][Index1].GetCoordinate(), NewField[Index2][Index1].GetStep(), false);
        }
        else newLocate = false;
        if (newLocate) {
            
            //удаляем фишку если сделан шаг 2
            int *cloneStart = new int[2];
            cloneStart = CanStopHere(StartLocation[0], NewField[0][0].GetStartX(), NewField[0][0].GetStartY(), NewField[0][0].GetStep(), cloneStart);
            int cloneIndex1 = cloneStart[0];
            int cloneIndex2 = cloneStart[1];
            Sprite* NewGreenPoint = Sprite::createWithTexture(ColorPoint->getTexture());
            Field->removeChildByTag(cloneIndex2 * 10000 + cloneIndex1 * 1000 + 100);
            Field->removeChildByTag(cloneIndex2 * 10 + cloneIndex1);
            
            SetSpriteWithClone(NewField, Field, Index1, Index2, NewGreenPoint, TotalScore, TotalCount, StartLocation, ColorTurn,  Turn, Players);
            
            if (!RemovePoint(NewField, cloneIndex1, cloneIndex2, StartLocation[0],NewField[Index2][Index1].GetCoordinate(), NewField[Index2][Index1].GetStep(),newLocate)) {
                SetSpriteWithClone(NewField, Field, cloneIndex1, cloneIndex2, NewGreenPoint, TotalScore, TotalCount, StartLocation, ColorTurn, Turn, Players);
                ++TotalScore[Turn[0] % Players];
            }
            ChangeColor(NewField, Field, Index1, Index2, ColorPoint, TotalScore, TotalCount, StartLocation, ColorTurn, Turn, Players);
            NewField[Index2][Index1].SetColor(ColorTurn[Turn[0] % Players]);
            NewField[Index2][Index1].SetColorEmpty(true);
            
            delete[] cloneStart;
            ++Turn[0];
        }
        else {
            auto Move = MoveTo::create(0.5, StartLocation[0]);
            target->runAction(Move);
        }
        
        //обновляем счет
        for(int i = 0; i < Players ; ++i)
            TotalCount[i]->setString(std::to_string(TotalScore[i]));
        
        delete[] CurrentStop;
        //Reset zOrder and the display sequence will change
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, ColorPoint);
}


#endif //MYGAME_COORDINATE_H



/*
#include "GameScene.h"
#include "cocos2d.h"


#ifndef MYGAME_COORDINATE_H
#define MYGAME_COORDINATE_H

using namespace cocos2d;

class FieldAndPoints2 : cocos2d::Sprite{
protected:
    int Step;
    bool IsEmpty;
    Point Coordinate;
    
public:
    FieldAndPoints2();
    ~FieldAndPoints2();
    void SetStep(int newStep) { Step = newStep; };
    void setEmpty(bool newEmpty) {IsEmpty = newEmpty;};
    int GetStep(){return Step;};
    bool GetEmpty(){return IsEmpty;};
    void SetCoordinate(Point newCoordinate){Coordinate = newCoordinate;};
    Point GetCoordinate(){return Coordinate;};
};

class ColorPoints : public FieldAndPoints2{
private:
    char Color;
    bool isColor;
    
public:
    ColorPoints();
    ~ColorPoints();
    void SetColor(char newColor){Color = newColor;};
    void SetIsEmpty(char newIsColor){isColor = newIsColor;};
    bool GetEmptyColor(){return isColor;};
    char GetColor(){return isColor;};
};

FieldAndPoints2::FieldAndPoints2() {
    IsEmpty = true;
    
}

FieldAndPoints2::~FieldAndPoints2() {; }

ColorPoints::ColorPoints() {
    isColor = false;
}

ColorPoints::~ColorPoints(){; }

//по координатам находим индексы фишки в массиве
int* CanStopHere(Point locationInNode, int StartX, int StartY,int Step){
    int Result[2];
    Result[0] = (int)(locationInNode.x - StartX) / Step;
    Result[1] = (int)(locationInNode.y - StartY) / Step;
    return Result;
}

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

ColorPoints** BuildField(ColorPoints** NewField, int Step, Sprite * Field, int StartX, int StartY){
    int Start = StartX;
    for(int i = 0; i < 10; ++i) {
        int None = rand() % 10;
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
        StartX =Start;
        StartY += Step;
    }
    return NewField;
}


#endif //MYGAME_COORDINATE_H
 */
