//
//  SelectScene.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#include "SelectScene.h"
#import "SelectScene.h"

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

SEL_MenuHandler SelectScene::onResolveCCBCCMenuItemSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOGERROR("name_menu_item = %s", pSelectorName);
    
    return NULL;
}

Control::Handler SelectScene::onResolveCCBCCControlSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOG("name_control = %s", pSelectorName);
    /*
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedPreviousButton", SelectScene::tappedPreviousButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedNextButton", SelectScene::tappedNextButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBackButton", SelectScene::tappedBackButton);
     */
    return NULL;
}

bool SelectScene::init() {
    if ( !Layer::init() ) {
        return false;
    }
    createPhysWorld();
    createSprite();
    //schedule( schedule_selector(SelectScene::updateWorld) , 0.01);
    scheduleUpdate();
    return true;
}


void SelectScene::update(float delta){
    int velocityIterations = 8;
    int positionIteretions = 1;
    world->Step(delta, velocityIterations, positionIteretions);
}

void SelectScene::createPhysWorld() {
    b2Vec2 gravity;
    gravity.Set(0,-10);
    world = new b2World(gravity);
}

void SelectScene::createSprite() {
    Size winSize = Director::getInstance()->getWinSize();
    
    b2Body* body;
    b2BodyDef bodyDef;
    b2CircleShape shape;
    b2FixtureDef fixtureDef;
    
    PhysicsSprite* physicsSprite = PhysicsSprite::create("clickme.png");
    
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((winSize.width / 2) / PT_RATIO, (winSize.height) / PT_RATIO);
    bodyDef.userData = physicsSprite;
    
    body = world->CreateBody(&bodyDef);
    
    shape.m_radius = physicsSprite->getContentSize().width / PT_RATIO;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.9;
    
    body->CreateFixture(&fixtureDef);
    
    this->addChild(physicsSprite);
    physicsSprite->setB2Body(body);
    physicsSprite->setPTMRatio(PT_RATIO);
    physicsSprite->setPosition(Point(winSize.width / 2, winSize.height / 2));
    
}