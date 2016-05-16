//
// Created by ilya on 5/16/16.
//
#include "FieldAndPoints.h"


#ifndef MYGAME_MEMENTO_H
#define MYGAME_MEMENTO_H

class Memento{
private:
    int Players;
    int* Score;
    ColorPoints** Field;
    int* RecordData;
    int* Turn;
    Label** TotalCount;
public:
    Memento(int newPlayers, int* newScore, ColorPoints** Field, int* newRecordData, int* newTurn, Label** newTotalCount);
    ~Memento();
    ColorPoints** RebuildField(Sprite* FieldBack);
    friend void SetSpriteWithClone(ColorPoints** NewField, Sprite* Field, int Index1, int Index2, Sprite* ColoredPoint, int* TotalScore,
                                   Label** TotalCount, Point* Start, char* ColorTurn, int* Turn, int Players);
};

Memento::Memento(int newPlayers, int *newScore, ColorPoints** NewField, int* newRecordData, int* newTurn, Label** newTotalCount) {
    Players = newPlayers;
    Score = newScore;
    Field = NewField;
    RecordData = newRecordData;
    Turn = newTurn;
    TotalCount = newTotalCount;
}

Memento::~Memento() {
    delete[] Players;
    delete[] Score;
    for(int i = 0; i < 10; ++i)
        delete[] Field[i];
    delete[] RecordData;
}

ColorPoints** Memento::RebuildField(Sprite* FieldBack){

    Point* StartLocation = new Point [1];

    auto GreenPoint = Sprite::create("Green.png");
    auto BluePoint = Sprite::create("Blue.png");
    auto RedPoint = Sprite::create("Red.png");
    auto OrangePoint = Sprite::create("Orange.png");

    char* ColorTurn = new char [4]{'g','b','r','o'};

    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10;++j) {
            if (!Field[0][0].GetEmpty()) {
                auto EmptyPoint = Sprite::create("Empty.png");
                FieldBack->addChild(EmptyPoint);
                EmptyPoint->setPosition(Field[i][j].GetCoordinate());
                if(Field[i][j].GetEmptyColor()) {
                    switch (Field[i][j].GetColor()) {
                        case 'g':
                            SetSpriteWithClone(Field, FieldBack, j, i, GreenPoint, Score, TotalCount, StartLocation,
                                               ColorTurn, Turn, Players);
                            break;
                        case 'b':
                            SetSpriteWithClone(Field, FieldBack, j, i, BluePoint, Score, TotalCount, StartLocation,
                                               ColorTurn, Turn, Players);
                            break;
                        case 'r':
                            SetSpriteWithClone(Field, FieldBack, j, i, RedPoint, Score, TotalCount, StartLocation,
                                               ColorTurn, Turn, Players);
                            break;
                        case 'o':
                            SetSpriteWithClone(Field, FieldBack, j, i, OrangePoint, Score, TotalCount, StartLocation,
                                               ColorTurn, Turn, Players);
                            break;
                    }
                }
            }
        }
    }
    return Field;
}

#endif //MYGAME_MEMENTO_H
