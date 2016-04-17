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
    Background->setAnchorPoint(Vec2(0,0));
    Background->setPosition(0,0);

//устанваливаем поле
    auto Field = Sprite::create("EmptyField.png");
    Field->setScale(0.5);
    Background->addChild(Field);
    Field->setPosition(640,358);

//рандомно генерируем пустые фишки
    int Step = Field->getContentSize().height / 10;

    ColorPoints** NewField = new ColorPoints* [10];
    int StartX = 75;
    int StartY = 75;
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

    //ставим зеленное поле
    auto GreenPoint = Sprite::create("Green.png");
    GreenPoint->setScale(0.95);
    Field->addChild(GreenPoint,3);
    GreenPoint->setPosition(75,75);
    GreenPoint->setOpacity(0);
    auto fadeIn = FadeIn::create(0.4f);
    GreenPoint->runAction(fadeIn);

    this->addChild(Background,0);

    GreenPoint->setOpacity(0);


    Point* StartLocation = new Point [1];

    //даем возможность перетаскивать фишки
    auto listener1 = EventListenerTouchOneByOne::create();
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    listener1->setSwallowTouches(true);

    // Example of using a lambda expression to implement onTouchBegan event callback function
    listener1->onTouchBegan = [NewField, StartLocation, StartX, StartY, Field](Touch* touch, Event* event) mutable{
//        GreenPoint->clone();
        // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        StartLocation[0] = Field->convertToNodeSpace(touch->getLocation());
        int* CurrentStop = CanStopHere(StartLocation[0],StartX,StartY, NewField[0][0].GetStep());
        int Index1 = CurrentStop[0];
        int Index2 = CurrentStop[1];
        StartLocation[0] = NewField[Index2][Index1].GetCoordinate();
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

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
    listener1->onTouchEnded = [=,StartLocation, NewField](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(255);
        Point locationInNode = target->getPosition();
        int* CurrentStop = CanStopHere(locationInNode,StartX,StartY, NewField[0][0].GetStep());
        int Index1 = CurrentStop[0];
        int Index2 = CurrentStop[1];
        Point newLocate;
        if(NewField[Index2][Index1].GetEmpty())
            newLocate = newLocation(StartLocation[0],locationInNode,Step,true);
        else newLocate = newLocation(StartLocation[0],locationInNode,Step,false);
        auto Move = MoveTo::create(0.5,newLocate);
        target->runAction(Move);
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
