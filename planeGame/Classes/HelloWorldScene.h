#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

enum GameState
{
    Welcome = 0,
    Start,
    HighScore,
    Result
};

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    void createHero();
    void createBigEnemy(float dt);
    void createSmallEnemy(float dt);
    
    void heroFire(float dt);
    void enemyFire(float dt);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void touchRestart(Ref* object, cocos2d::ui::Widget::TouchEventType type);
    
    void touchExit(Ref* object, cocos2d::ui::Widget::TouchEventType type);

    void startGame();
    
    void initBackground();
    
    void moveBackground(float dt);
    
    void gameControl(GameState state);
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Node* hero;
    cocos2d::Sprite* bg1;
    cocos2d::Sprite* bg2;
    GameState gameState;
};

#endif // __HELLOWORLD_SCENE_H__
