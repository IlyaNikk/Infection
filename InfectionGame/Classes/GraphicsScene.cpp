//
// Created by ilya on 4/2/16.
//

#include "GraphicsScene.h"

USING_NS_CC;

Scene* GraphicsScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GraphicsScene::create();
    scene->addChild(layer);

    return scene;
}

bool GraphicsScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto sprite = Sprite::create("decepticon.png");
    sprite->setPosition(0, 0);

    this->addChild(sprite, 0);

    return true;
}