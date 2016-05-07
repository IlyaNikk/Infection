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
    char Color ;
    for(int i = 0; i < Players; ++i) {
        if(i == 0) {
            Color = 'g';
            Point *StartGreenLocation = new Point[1];
            StarterPoint(NewField, BackAndScore.GetField(), GreenPoint, Color, StartX, StartY, TotalScore, TotalCount, StartGreenLocation, location,
                         ColorTurn, Turn, Players);
        }
        if(i == 1){
            Color = 'b';
            Point *StartBlueLocation = new Point[1];
            location.x = location.x + 9 * NewField[0][0].GetStep();
            location.y = location.y + 9 * NewField[0][0].GetStep();
            StarterPoint(NewField, BackAndScore.GetField(), BluePoint, Color, StartX, StartY, TotalScore, TotalCount, StartBlueLocation, location,
                         ColorTurn, Turn, Players);
        }
        if(i == 2){
            Color = 'r';
            Point *StartRedLocation = new Point[1];
            location.x = Step / 2 + 4 + 9 * NewField[0][0].GetStep();
            location.y = Step / 2 + 4;
            StarterPoint(NewField, BackAndScore.GetField(), RedPoint, Color, StartX, StartY, TotalScore, TotalCount, StartRedLocation, location,
                         ColorTurn, Turn, Players);
        }
        if(i == 3){
            Color = 'o';
            Point *StartOrangeLocation = new Point[1];
            location.y = Step / 2 + 4 + 9 * NewField[0][0].GetStep();
            location.x = Step / 2 + 4;
            StarterPoint(NewField, BackAndScore.GetField(), OrangePoint, Color, StartX, StartY, TotalScore, TotalCount, StartOrangeLocation, location,
                         ColorTurn, Turn, Players);
        }
    }

       return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
