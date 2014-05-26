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
    createGround();
    
    initTouchEventListener();
    
    scheduleUpdate();
    
    return true;
}

void SelectScene::initTouchEventListener() {
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(SelectScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SelectScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SelectScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(SelectScene::onTouchCancelled, this);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 100);
}

bool SelectScene::onTouchBegan(Touch *touch, Event *event) {
    return true;
}

void SelectScene::onTouchEnded(Touch *touch, Event *event) {
    createSpriteAt(touch->getLocation());
};

void SelectScene::onTouchMoved(Touch *touch, Event *event) {
}

void SelectScene::onTouchCancelled(Touch *touch, Event *event) {
}

void SelectScene::update(float delta){
    int velocityIterations = 8;
    int positionIteretions = 1;
    world->Step(delta, velocityIterations, positionIteretions);
    
    // 物体静止時に演算を省略する
    world->SetAllowSleeping(true);
    
    // 貫通しないように連続計算
    world->SetContinuousPhysics(true);
}

void SelectScene::createPhysWorld() {
    b2Vec2 gravity;
    gravity.Set(0,-10);
    world = new b2World(gravity);
}

void SelectScene::createSpriteAt(Point pos) {
    b2Body* body;
    b2BodyDef bodyDef;
    b2CircleShape shape;
    b2FixtureDef fixtureDef;
    
    PhysicsSprite* physicsSprite = PhysicsSprite::create("circle.png");
    float scale = Director::getInstance()->getContentScaleFactor();
    physicsSprite->cocos2d::Node::setScale(scale);
    
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((pos.x) / PT_RATIO, (pos.y) / PT_RATIO);
    bodyDef.userData = physicsSprite;
    
    body = world->CreateBody(&bodyDef);
    
    shape.m_radius = physicsSprite->getContentSize().width / PT_RATIO;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    
    body->CreateFixture(&fixtureDef);
    
    this->addChild(physicsSprite);
    physicsSprite->setB2Body(body);
    physicsSprite->setPTMRatio(PT_RATIO);
    physicsSprite->setPosition(pos);
}

void SelectScene::createSpriteRandom() {
    Size winSize = Director::getInstance()->getWinSize();
    int num = 20;
    for (int i = 0; i < num; i++) {
        int idx = CCRANDOM_0_1() * winSize.width;
        int idy = CCRANDOM_0_1() * winSize.height;
        createSpriteAt(Point(idx, idy));
    }
}

void SelectScene::createGround() {
    Size winSize = Director::getInstance()->getWinSize();
    b2BodyDef groundBodyDef;
    groundBodyDef.position.SetZero();
    
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    b2EdgeShape groundBox;
    
    // bottom
    groundBox.Set(b2Vec2(0,0), b2Vec2(winSize.width/PT_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(0,winSize.height/PT_RATIO), b2Vec2(winSize.width/PT_RATIO,winSize.height/PT_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // left
    //groundBox.Set(b2Vec2(0,winSize.height/PT_RATIO), b2Vec2(0,0));
    //groundBody->CreateFixture(&groundBox,0);
    
    // right
    //groundBox.Set(b2Vec2(winSize.width/PT_RATIO,winSize.height/PT_RATIO), b2Vec2(winSize.width/PT_RATIO,0));
    //groundBody->CreateFixture(&groundBox,0);
}