//
//  SelectScene.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#ifndef __Casidra__SelectScene__
#define __Casidra__SelectScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#import "Box2D/Box2D.h"
#include <array>

USING_NS_CC;
USING_NS_CC_EXT;

class SelectScene : public Layer
, public CCBSelectorResolver
{
private:
    enum SpriteType {
        Circle,
        Box,
        Star,
        Heart,
        SpriteTypeNum,
    };
    
    typedef struct Box2dSpriteData {
        const char* file;
        float density;
        float friction;
    } Box2dSpriteData;
    
    b2World *world;
    
    void update(float delta);
    void createPhysWorld();
    void createGround();
    void initTouchEventListener();
    
    Box2dSpriteData createBox2DSpriteData(SpriteType type);
    Box2dSpriteData createRandomBox2DSpriteData();
    
public:
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object* pTarget, const char* pSelectorName);
    void tappedSelectButton(Object* pSender, Control::EventType pControlEventType);
    void tappedHatenaButton(Object* pSender, Control::EventType pControlEventType);
    
    SelectScene();
    virtual ~SelectScene();
    
    virtual bool init();
    
    void drawBox2dSpriteAt(Box2dSpriteData sprite, Point pos);
    
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectScene, create);

};

class SelectSceneLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SelectSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SelectScene);
};


#endif /* defined(__Casidra__SelectScene__) */
