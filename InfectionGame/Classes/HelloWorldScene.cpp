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

    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
   /* auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
*/
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

    int StartX = 75;
    int StartY = 75;
    auto Act = Sequence::create(nullptr);
    for(int i = 0; i < 10; ++i) {
        int None = rand() % 10;
        for(int j = 0; j < 10; ++j ){
            if(j != None) {
                auto EmptyPoint = Sprite::create("Empty.png");
                Field->addChild(EmptyPoint);
                EmptyPoint->setOpacity(0);
                EmptyPoint->setPosition(0, 0);

                auto fadeIn = FadeIn::create(1.0f);
                auto move = MoveTo::create(1, Point(StartX, StartY));

                auto spawn = Spawn::createWithTwoActions(fadeIn, move);
                EmptyPoint->runAction(spawn);
            }
            StartX += Step;
            }
        StartX = 75;
        StartY += Step;
        }

//задаем счет для синего и зеленого игрока
    string GreenScore  = "0000";
    auto GreenCount = Label::createWithTTF(GreenScore,"/home/ilya/Infection/InfectionGame/Resources/fonts/MarkerFelt.ttf",32);
    GreenCount->setPosition(Vec2(origin.x + 40 ,
                            origin.y + visibleSize.height - GreenCount->getContentSize().height));
    GreenCount->setColor(ccc3(0,255,0));
    this->addChild(GreenCount,1);

    string BlueScore  = "0000";
    auto BlueCount = Label::createWithTTF(BlueScore,"/home/ilya/Infection/InfectionGame/Resources/fonts/MarkerFelt.ttf",32);
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
/*
    auto BluePoint = Sprite::create("Blue.png");
    BluePoint->setScale(0.95);
    Field->addChild(BluePoint);
    BluePoint->setPosition(240,380);
*/
    this->addChild(Background,0);

    GreenPoint->setOpacity(0);



    //даем возможность перетаскивать фишки
    auto listener1 = EventListenerTouchOneByOne::create();
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    listener1->setSwallowTouches(true);

    // Example of using a lambda expression to implement onTouchBegan event callback function
    listener1->onTouchBegan = [](Touch* touch, Event* event){
//        GreenPoint->clone();
        // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
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
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(255);
        Point locationInNode = target->getPosition();
        float* newLocate = newLocation(locationInNode.x,locationInNode.y,Step);

        auto Move = MoveTo::create(0.5,Point(newLocate[0], newLocate[1]));
        target->runAction(Move);
        //Reset zOrder and the display sequence will change
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, GreenPoint);


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
