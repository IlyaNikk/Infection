#include "GameScene.h"
#include "MainMenuScene.h"
#include "string"
#include <vector>
#include <FieldAndPoints2.h>
#include "Field.h"
#include "Menu.h"
//#include "Memento.h"
#include "Defenitions.h"

using namespace std;



USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    auto Background = Sprite::create("background.png");
    Background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    Background->setScaleX(visibleSize.width / Background->getContentSize().width);
    Background->setScaleY(visibleSize.height / Background->getContentSize().height);
    this->addChild(Background,0);
    
    
    int Players =UserDefault::getInstance()->getIntegerForKey("Players");
    
   // int Players = 2;
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
    ColorPoints2** NewField = Field::getInstance(Step, BackAndScore.GetField(), StartX[0], StartY[0]);
    
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
    
    
    auto BackToMenu = Label::createWithTTF("Back", "fonts/orange.ttf", 32 * 2);
    BackToMenu->setColor(ccc3(0,0,0));
    
    
    auto closeItem = MenuItemLabel::create(BackToMenu,CC_CALLBACK_1(GameScene::GoToMainScene, this));
    
    closeItem->setPosition(Point(28, -25));
    
    auto menu = Menu::create(closeItem, NULL);
    Background->addChild(menu, 1);
    
            return true;
    };

void GameScene::GoToMainScene(cocos2d::Ref *sender){
    UserDefault::getInstance()->setIntegerForKey("Resume", 1);
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}



void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

