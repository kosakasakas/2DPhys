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

#define MAX_BUTTON_NUM 6
#define MAX_PAGE_NUM 16

class SelectScene : public Layer
, public CCBSelectorResolver
{
// var
private:
    enum NodeTag {
        Header    = 10,
        Footer     = 11,
        TitleLabel = 12,
        ButtonNode    = 20,
        
        SelectButton = 0,
        HatenaButton =1,
    };
    
    enum PageType {
        SelectRouletteType,
        SelectMethod,
        SelectZone,
        InputMinBet,
    };
    
    b2World *world;
    
    void update(float delta);
    
    void createPhysWorld();
    void createGround();
    
    void initTouchEventListener();
    
public:
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName);
    void tappedSelectButton(Object* pSender, Control::EventType pControlEventType);
    void tappedHatenaButton(Object* pSender, Control::EventType pControlEventType);
    
    virtual bool init();
    
    SelectScene();
    virtual ~SelectScene();
    
    void createSpriteAt(Point pos);
    void createSpriteRandom();
    
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
