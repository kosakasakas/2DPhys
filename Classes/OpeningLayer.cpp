//
//  OpeningLayer.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#import "OpeningLayer.h"
#import "RigidScene.h"
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
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartRigidPhysButton", OpeningLayer::tappedStartRigidPhysButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartLiquidPhysButton", OpeningLayer::tappedStartLiquidPhysButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartSampleGameButton", OpeningLayer::tappedStartSampleGameButton);
    
    return NULL;
}

void OpeningLayer::onEnter() {
    Layer::onEnter();
}

void OpeningLayer::tappedStartRigidPhysButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedStartSimulationButton eventType = %d", pControlEventType);
    startRigidPhysScene();
}

void OpeningLayer::tappedStartLiquidPhysButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedRealGameButton eventType = %d", pControlEventType);
    startLiquidPhysScene();
}

void OpeningLayer::tappedStartSampleGameButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedRealGameButton eventType = %d", pControlEventType);
}

void OpeningLayer::startLiquidPhysScene() {
    auto director = Director::getInstance();
    NodeLoaderLibrary* nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("LiquidScene", LiquidSceneLoader::loader());
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("LiquidScene.ccbi");
    Scene* scene = Scene::create();
    if (node != NULL)
    {
        scene->addChild(node);
    }
    ccbReader->release();
    director->replaceScene(scene);
}

void OpeningLayer::startRigidPhysScene() {
    auto director = Director::getInstance();
    NodeLoaderLibrary* nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("RigidScene", RigidSceneLoader::loader());
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("RigidScene.ccbi");
    Scene* scene = Scene::create();
    if (node != NULL)
    {
        scene->addChild(node);
    }
    ccbReader->release();
    director->replaceScene(scene);
}