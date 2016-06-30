#include "GameRoundScene.h"
#include "MainMenuScene.h"
#include "Defenitions.h"
#include "string"
#include <FieldAndPoints.h>


USING_NS_CC;

Scene* GameRoundScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = GameRoundScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameRoundScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    // add "HelloWorld" splash screen"
    
    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
    backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);
    this->addChild(backgroundSprite);
    
    int a = visibleSize.width/2;
    int b = visibleSize.height/2;
    int aa = origin.x;
    int bb = origin.y;
    
    
    
    
    auto Field = Sprite::create("EmptyField 2.png");
    Field->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(Field);
    const cocos2d::Vec2 ddd = Field->getPosition();
 
    //рандомно генерируем пустые фишки
    double Step = Field->getContentSize().height / 10;
    
    FieldAndPoints** NewField = new FieldAndPoints* [10];
    double StartX = 85;
    double StartY = 30;
    NewField = BuildRoundField(NewField, Step, Field, StartX, StartY);
    /*
    
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    edgeNode->setPhysicsBody(edgeBody);
    
    this->addChild( edgeNode);
    */
    
    
    auto BackToMenu = Label::createWithTTF("Back", "fonts/orange.ttf", 32);
    BackToMenu->setColor(ccc3(0,0,0));
    
    
    auto closeItem = MenuItemLabel::create(BackToMenu,CC_CALLBACK_1(GameRoundScene::GoToMainScene, this));
    
    closeItem->setPosition(Point(28, -25));
    
    auto menu = Menu::create(closeItem, NULL);
    backgroundSprite->addChild(menu, 1);
    
    
    
    return true;
}

void GameRoundScene::GoToMainScene(cocos2d::Ref *sender){
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

