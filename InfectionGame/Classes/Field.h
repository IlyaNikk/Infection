//
// Created by ilya on 5/7/16.
//

#include "cocos2d.h"
#include "FieldAndPoints2.h"

#ifndef MYGAME_FIELD_H
#define MYGAME_FIELD_H

using namespace std;

class Field;  // опережающее объявление

class FieldDestroyer
{
private:
    Field* p_instance;
    ColorPoints2** NewField;
public:
    ~FieldDestroyer();
    void initialize( Field* p, ColorPoints2** ThisField);
};

class Field
{
private:
    static Field* p_instance ;
    static ColorPoints2** BuildedField;
    static FieldDestroyer destroyer;
protected:
    Field() ;
    Field( const Field& );
    Field& operator=( Field& );
    ~Field() { }
    friend class FieldDestroyer;
public:
    static ColorPoints2** getInstance(int Step, Sprite* SpriteField, int StartX, int StartY);
};

void BuildField(ColorPoints2** NewField, int Step, Sprite* SpriteField, int StartX, int StartY);

Field* Field::p_instance = 0;
ColorPoints2** Field::BuildedField = 0;
FieldDestroyer Field::destroyer;

FieldDestroyer::~FieldDestroyer() {
    delete p_instance;
    for(int i = 0; i < 10; ++i)
        delete[] NewField[i];

}

void FieldDestroyer::initialize( Field* p , ColorPoints2** ThisField) {
    p_instance = p;
    NewField = ThisField;
}

ColorPoints2** Field::getInstance(int Step, Sprite* SpriteField, int StartX, int StartY) {
    if(!p_instance)     {
        p_instance = new Field ();
        BuildField(Field::BuildedField, Step, SpriteField, StartX, StartY);
        destroyer.initialize(p_instance, Field::BuildedField);
    }
    return Field::BuildedField;
}

Field::Field() {
    Field::BuildedField = new ColorPoints2* [10];
    for(int i = 0; i < 10; ++i)
        Field::BuildedField[i] = new ColorPoints2 [10];
}

void BuildField(ColorPoints2** NewField, int Step, Sprite* Field, int StartX, int StartY){
    int Start = StartX;
    for(int i = 0; i < 10; ++i) {
        int None = rand() % 10;
        while ((i == 0 || i == 9) && (None == 0 || None ==9))
            None = rand() % 10;
        for(int j = 0; j < 10; ++j ){
            auto EmptyPoint = Sprite::create("Empty.png");
            if(j != None) {
                Point CurrentLocation;
                CurrentLocation.x = StartX;
                CurrentLocation.y = StartY;
                NewField[i][j].SetStartX(StartX);
                NewField[i][j].SetStartY(StartY);
                NewField[i][j].setEmpty(false);
                NewField[i][j].SetCoordinate(CurrentLocation);
                NewField[i][j].SetStep(Step);
                Field->addChild(EmptyPoint);
                EmptyPoint->setOpacity(0);
                EmptyPoint->setPosition(5 * Step, 5 * Step);

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
}

#endif //MYGAME_FIELD_H
