#include "HelloWorldScene.h"
#include "string"
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
    int StartX = Step / 2 + 4;
    int StartY = Step / 2 + 4;
    NewField = BuildField(NewField,Step,Field,StartX, StartY);


//задаем счет для синего и зеленого игрока
    string GreenScore  = "1234";
    auto GreenCount = Label::createWithTTF(GreenScore,"/home/ilya/Infection/InfectionGame/Resources/fonts/Magneto-Bold.ttf",32);
    GreenCount->setPosition(Vec2(origin.x + 40 ,
                            origin.y + visibleSize.height - GreenCount->getContentSize().height));
    GreenCount->setColor(ccc3(0,255,0));
    this->addChild(GreenCount,1);

    string BlueScore  = "1234";
    auto BlueCount = Label::createWithTTF(BlueScore,"/home/ilya/Infection/InfectionGame/Resources/fonts/Old-English-Text-MT-Regular.ttf",32);
    BlueCount->setPosition(Vec2(origin.x + 1240 ,
                            origin.y + visibleSize.height - BlueCount->getContentSize().height));
    BlueCount->setColor(ccc3(0,0,255));
    this->addChild(BlueCount,1);

    //ставим зеленную фишку
    int Players = 1;
    auto GreenPoint = Sprite::create("Green.png");
    auto BluePoint = Sprite::create("Blue.png");
    char Color = 'g';
    for(int i = 0; i < Players; ++i) {
        if(i == 0) {
            StarterPoint(NewField,Field, GreenPoint, Color, StartX, StartY);
            //Color = 'b';
        }
    }



    Point* StartLocation = new Point [1];

    //даем возможность перетаскивать фишки
    auto listener1 = EventListenerTouchOneByOne::create();
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    listener1->setSwallowTouches(true);

    // Example of using a lambda expression to implement onTouchBegan event callback function
    listener1->onTouchBegan = [NewField, StartLocation, StartX, StartY, Field, GreenPoint](Touch* touch, Event* event) mutable{

        // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        StartLocation[0] = Field->convertToNodeSpace(touch->getLocation());
        int* CurrentStop = new int [2];
        //ищем координаты начала движения и запоминаем их
        CurrentStop =  CanStopHere(StartLocation[0],StartX,StartY, NewField[0][0].GetStep(), CurrentStop);
        int Index1 = CurrentStop[0];
        int Index2 = CurrentStop[1];
        StartLocation[0] = NewField[Index2][Index1].GetCoordinate();
        Size s = target->getContentSize();

        if(!NewField[Index2][Index1].GetEmptyColor())
            return false;

        //ставим копию фишки
        Sprite *clonedSprite = Sprite::createWithTexture(GreenPoint->getTexture());
        clonedSprite->setScale(GreenPoint->getScaleX(), GreenPoint->getScaleY());
        clonedSprite->setRotation(GreenPoint ->getRotation());
        clonedSprite->setPosition(StartLocation[0]);
        Field->addChild(clonedSprite, 3);

        Rect rect = Rect(0, 0, s.width, s.height);
        delete[] CurrentStop;
        //Check the click area
        if (rect.containsPoint(locationInNode))
        {
            target->setOpacity(180);
            return true;
        }
        return false;
    };

    //Trigger when moving touch
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        //Move the position of current button sprite
        target->setPosition(target->getPosition() + touch->getDelta()*2);
    };

    //Process the touch end event
    listener1->onTouchEnded = [Field,StartX,StartY,Step,StartLocation, Color, NewField](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(255);
        Point locationInNode =target->getPosition();

        //ищем кординаты окончания движения и проверяем можем ли мы там остановиться
        int* CurrentStop = new int [2];
        CurrentStop = CanStopHere(locationInNode,StartX,StartY, NewField[0][0].GetStep(), CurrentStop);
        int Index1 = CurrentStop[0];
        int Index2 = CurrentStop[1];
        bool newLocate;
        if(!NewField[Index2][Index1].GetEmptyColor()) {
            if (NewField[Index2][Index1].GetEmpty())
                newLocate = newLocation(StartLocation[0], NewField[Index2][Index1].GetCoordinate(), Step, true);
            else newLocate = newLocation(StartLocation[0], NewField[Index2][Index1].GetCoordinate(), Step, false);
        }
        else newLocate = false;
        if(newLocate) {
            auto Move = MoveTo::create(0.5, NewField[Index2][Index1].GetCoordinate());
            target->runAction(Move);
        }
        else {
            auto Move = MoveTo::create(0.5, StartLocation[0]);
            target->runAction(Move);
        }
        auto EmptyPoint = Sprite::create("Empty.png");
        NewField[Index2][Index1] = RemovePoint(NewField[Index2][Index1],Field,EmptyPoint,
                                               StartLocation[0], NewField[Index2][Index1].GetCoordinate(),
                                               NewField[Index2][Index1].GetStep());
        NewField[Index2][Index1].SetColor(Color);
        NewField[Index2][Index1].SetColorEmpty(true);

        delete[] CurrentStop;
        //Reset zOrder and the display sequence will change
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, GreenPoint);

    delete[] StartLocation;
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
