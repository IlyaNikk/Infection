#include "HelloWorldScene.h"
#include <string>
#include <vector>
#include <FieldAndPoints.h>

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


 //создаем фон
    auto Background = Sprite::create("background.png");
    Background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    Background->setScaleX(visibleSize.width / Background->getContentSize().width);
    Background->setScaleY(visibleSize.height / Background->getContentSize().height);
    this->addChild(Background,0);

//устанваливаем поле
    auto Field = Sprite::create("EmptyField.png");
    Field->setScale(0.5);
    Field->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(Field);


//рандомно генерируем пустые фишки
    int Step = Field->getContentSize().height / 10;

    ColorPoints** NewField = new ColorPoints* [10];
    int* StartXGreen = new int [1];
    StartXGreen[0] = Step / 2 + 4;
    int* StartYGreen = new int [1];
    StartYGreen[0] = Step / 2 + 4;

    NewField = BuildField(NewField,Step,Field,StartXGreen[0], StartYGreen[0]);


//задаем счет для синего и зеленого игрока
    int* GreenScore = new int [1]();
    ++GreenScore[0];
    auto GreenCount = Label::createWithTTF(to_string(GreenScore[0]),"/home/ilya/Infection/InfectionGame/Resources/fonts/Magneto-Bold.ttf",32);
    GreenCount->setPosition(Vec2(origin.x + Step ,
                            origin.y + visibleSize.height - GreenCount->getContentSize().height));
    GreenCount->setColor(ccc3(0,255,0));
    GreenCount->setTag(222);
    this->addChild(GreenCount,1);

    int* BlueScore  = new int[1]();
    ++BlueScore[0];
    auto BlueCount = Label::createWithTTF(to_string(BlueScore[0]),"/home/ilya/Infection/InfectionGame/Resources/fonts/Magneto-Bold.ttf",32);
    BlueCount->setPosition(Vec2(origin.x + visibleSize.width - Step ,
                            origin.y + visibleSize.height - BlueCount->getContentSize().height));
    BlueCount->setColor(ccc3(0,0,255));
    GreenCount->setTag(333);
    this->addChild(BlueCount,1);

    Point location = Point(Step / 2 + 4, Step / 2 + 4);

    //ставим зеленную фишку
    int Players = 2;
    auto GreenPoint = Sprite::create("Green.png");
    auto BluePoint = Sprite::create("Blue.png");
    char Color ;
    for(int i = 0; i < Players; ++i) {
        if(i == 0) {
            Color = 'g';
            Point *StartGreenLocation = new Point[1];
            StarterPoint(NewField, Field, GreenPoint, Color, StartXGreen, StartYGreen, GreenScore, GreenCount, StartGreenLocation, location);
        }
        if(i == 1){
            Color = 'b';
            Point *StartBlueLocation = new Point[1];
            int* StartXBlue = new int [1];
            int* StartYBlue = new int [1];
            StartXBlue[0] = location.x;
            StartYBlue[0] = location.y;
            location.x = location.x + 9 * NewField[0][0].GetStep();
            location.y = location.y + 9 * NewField[0][0].GetStep();
            StarterPoint(NewField, Field, BluePoint, Color, StartXBlue, StartYBlue, BlueScore, BlueCount, StartBlueLocation, location);
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
