//
// Created by ilya on 4/2/16.
//

#ifndef MYGAME_GRAPHICSSCENE_H
#define MYGAME_GRAPHICSSCENE_H

#endif //MYGAME_GRAPHICSSCENE_H

#pragma once

#include "cocos2d.h"

class GraphicsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GraphicsScene);
};

