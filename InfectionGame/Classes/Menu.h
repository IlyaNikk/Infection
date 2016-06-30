//
// Created by ilya on 5/5/16.
//
#include "GameScene.h"
#include "cocos2d.h"
#include "string"
#include "Defenitions.h"

#ifndef MYGAME_MENU_H
#define MYGAME_MENU_H

using namespace std;

class GameEnviroment{
public:
    GameEnviroment(Layer *Scene, int Players, Label** Score, int* Record, char* WhatColor);
    ~GameEnviroment();
    void BuildBackGround(Layer* Scene);
    void BuildEmptyFiled(Layer* Scene);
    void BuildScore(Layer *Scene, int Players, Point* Positions, Label** Score, int* Record, char* WhatColor);
    Sprite* GetField(){return Field;};
private:
    Size visibleSize;
    Vec2 origin;
    Sprite* Background;
    Sprite* Field;
};

//конструктор создает 4 возможных позиции счета и задаем фон и поле
GameEnviroment::GameEnviroment(Layer *Scene, int Players, Label** Score, int* Record, char* WhatColor) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

  //  BuildBackGround(Scene);
    BuildEmptyFiled(Scene);

    int Step = Field->getContentSize().height / 10;
    Label* Test = Label::createWithTTF(to_string(0), "fonts/orange.ttf",32 * 3);

    Point* LabelPosition = new Point [4];
    LabelPosition[0] = {origin.x + Step, origin.y + Test->getContentSize().height};
    LabelPosition[1] = {origin.x + visibleSize.width - Step, origin.y + visibleSize.height - Test->getContentSize().height};
    LabelPosition[2] = {origin.x + visibleSize.width - Step, origin.y + Test->getContentSize().height};
    LabelPosition[3] = {origin.x +  Step, origin.y + visibleSize.height - Test->getContentSize().height};

    BuildScore(Scene, Players, LabelPosition, Score, Record, WhatColor);
}


// создаем фон

void GameEnviroment::BuildBackGround(Layer* Scene) {
    Background = Sprite::create("background.png");
    Background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    Background->setScaleX(visibleSize.width / Background->getContentSize().width);
    Background->setScaleY(visibleSize.height / Background->getContentSize().height);
    Scene->addChild(Background,0);
    

}


//задем пустое поле
/*
auto Field = Sprite::create("TriangleField.png");
Field->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
this->addChild(Field);
const cocos2d::Vec2 ddd = Field->getPosition();
*/
void GameEnviroment::BuildEmptyFiled(Layer *Scene) {
    Field = Sprite::create("RectangleField.png");
    Field->setScale(1);
    Field->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    Scene->addChild(Field);
}

//задаем счет случайно в одном из 4 углов
void GameEnviroment::BuildScore(Layer *Scene, int Players, Point* Positions, Label** Score, int* Record, char* WhatColor) {
    for(int i = 0; i < Players; ++i){
        int WhatPosition = rand() % 4;
        for(int j = 0; j < i; ++j) {
            if (Record[j] == WhatPosition) {
                WhatPosition = rand() % 4;
                j = -1;
            }
        }
        Record[i] = WhatPosition;
        ++Score[i];
        Score[i] = Label::createWithTTF(to_string(1),"fonts/orange.ttf",32 * 3);
        Score[i]->setPosition(Positions[WhatPosition]);
        if(WhatColor[i] == 'g')
            Score[i]->setColor(ccc3(0,255,0));
        else if (WhatColor[i] == 'b')
            Score[i]->setColor(ccc3(0,0,255));
        else if (WhatColor[i] == 'r')
            Score[i]->setColor(ccc3(255,0,0));
        else
            Score[i]->setColor(ccc3(255,255,0));
        Scene->addChild(Score[i],1);
    }
}

GameEnviroment::~GameEnviroment() {
    ;
}

#endif //MYGAME_MENU_H
