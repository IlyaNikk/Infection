#include "HelloWorldScene.h"
#include <string>
#include <FieldAndPoints.h>
#include "Menu.h"
#include "Field.h"

using namespace std;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    int Players = 2;
    int* TotalScore = new int [4]{0,0,0,0};
    Label** TotalCount = new Label* [4];
    int* RecordData = new int [Players]{};
    char* ColorTurn = new char [4]{'g','b','r','o'};

    GameEnviroment BackAndScore(this, Players, TotalCount, RecordData, ColorTurn);

    for(int i = 0; i < Players; ++i)
        ++TotalScore[i];
//рандомно генерируем пустые фишки
    int Step = BackAndScore.GetField()->getContentSize().height / 10;
    int* StartX = new int [1];
    StartX[0] = Step / 2 + 4;
    int* StartY = new int [1];
    StartY[0] = Step / 2 + 4;
    ColorPoints** NewField = Field::getInstance(Step, BackAndScore.GetField(), StartX[0], StartY[0]);

    Point* StartPoint = new Point [4];
    StartPoint[0] = {(float)Step / 2 + 4, (float)Step / 2 + 4};
    StartPoint[1] = {(float)Step / 2 + 4 + 9 * Step, (float)Step / 2 + 4 + 9 * Step};
    StartPoint[2] = {(float)Step / 2 + 4 + 9 * Step, (float)Step / 2 + 4};
    StartPoint[3] = {(float)Step / 2 + 4, (float)Step / 2 + 4 + 9 * Step};

//задаем счет для синего и зеленого игрока

    Point location = Point(Step / 2 + 4, Step / 2 + 4);
    int* Turn = new int [1]();

    //ставим зеленную фишку
    auto GreenPoint = Sprite::create("Green.png");
    auto BluePoint = Sprite::create("Blue.png");
    auto RedPoint = Sprite::create("Red.png");
    auto OrangePoint = Sprite::create("Orange.png");
    Point* StartLocation = new Point [1];
    char Color ;
    for(int i = 0; i < Players; ++i) {
        if(i == 0) {
            Color = 'g';
            StarterPoint(NewField, BackAndScore.GetField(), GreenPoint, Color, TotalScore, TotalCount, StartLocation, StartPoint[RecordData[0]],
                         ColorTurn, Turn, Players);
        }
        if(i == 1){
            Color = 'b';
            Point *StartBlueLocation = new Point[1];
            StarterPoint(NewField, BackAndScore.GetField(), BluePoint, Color, TotalScore, TotalCount, StartBlueLocation, StartPoint[RecordData[1]],
                         ColorTurn, Turn, Players);
            delete[] StartBlueLocation;
        }
        if(i == 2){
            Color = 'r';
            Point *StartRedLocation = new Point[1];
            StarterPoint(NewField, BackAndScore.GetField(), RedPoint, Color, TotalScore, TotalCount, StartRedLocation, StartPoint[RecordData[2]],
                         ColorTurn, Turn, Players);
            delete[] StartRedLocation;
        }
        if(i == 3){
            Color = 'o';
            Point *StartOrangeLocation = new Point[1];
            StarterPoint(NewField, BackAndScore.GetField(), OrangePoint, Color, TotalScore, TotalCount, StartOrangeLocation, StartPoint[RecordData[3]],
                         ColorTurn, Turn, Players);
            delete[] StartOrangeLocation;
        }
    }

       return true;
}
