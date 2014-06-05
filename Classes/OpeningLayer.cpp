//
//  OpeningLayer.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#import "OpeningLayer.h"
//#import "AudioManager.h"
#import "SelectScene.h"
#import "LiquidScene.h"

USING_NS_CC;

OpeningLayer::OpeningLayer()
{
}

OpeningLayer::~OpeningLayer()
{
}

SEL_MenuHandler OpeningLayer::onResolveCCBCCMenuItemSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOGERROR("name_menu_item = %s", pSelectorName);
    
    return NULL;
}

Control::Handler OpeningLayer::onResolveCCBCCControlSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
     CCLOG("name_control = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartSimulationButton", OpeningLayer::tappedStartSimulationButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartRealGameButton", OpeningLayer::tappedStartRealGameButton);
    
    return NULL;
}

void OpeningLayer::onEnter() {
    Layer::onEnter();
    //AudioManager::playBackGroundMusic(AudioManager::startBgmFile);
}

void OpeningLayer::tappedStartSimulationButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedStartSimulationButton eventType = %d", pControlEventType);
    //AudioManager::playTapEffect();
    startSimulationScene();
}

void OpeningLayer::tappedStartRealGameButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedRealGameButton eventType = %d", pControlEventType);
    startRealGameScene();
}

void OpeningLayer::startSimulationScene() {
    auto director = Director::getInstance();
    NodeLoaderLibrary* nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("LiquidScene", LiquidSceneLoader::loader());
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("SelectScene.ccbi");
    LiquidScene* scene = LiquidScene::create();
    if (node != NULL)
    {
        scene->addChild(node);
    }
    ccbReader->release();
    director->pushScene((Scene*)scene);
}

void OpeningLayer::startRealGameScene() {
    auto director = Director::getInstance();
    NodeLoaderLibrary* nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("SelectScene", SelectSceneLoader::loader());
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("SelectScene.ccbi");
    SelectScene* scene = SelectScene::create();
    if (node != NULL)
    {
        scene->addChild(node);
    }
    ccbReader->release();
    director->pushScene((Scene*)scene);
}