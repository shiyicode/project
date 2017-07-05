#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

const int HERO_BULLET_SPEED = 1000;
const int ENEMY_BULLET_SPEED = 1000;
const float HERO_FIRE_DURATION = 0.3;
const float ENEMY_FIRE_DURATION = 0.8;
const float BIG_ENEMY_CREATE_DURATION = 5.0;
const float SMALL_ENEMY_CREATE_DURATION = 1.5;
const float BACKGROUND_DURATION = 0.005;

enum ContactTag {
    HERO = 0,
    HERO_BULLET,
    ENEMY_BULLET,
    ENEMY
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
   
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    srand((unsigned int)time(NULL));
    
    gameControl(GameState::Start);
    
    return true;
}

void HelloWorld::gameControl(GameState state)
{
    switch (state) {
        case GameState::Welcome:
        {
            gameState = state;
            initBackground();
            break;
        }
        case GameState::Start:
        {
            initBackground();
            gameState = state;
            startGame();
            break;
        }
        case GameState::HighScore:
        {
            gameState = state;
            break;
        }
        case GameState::Result:
        {
            gameState = state;
            break;
        }
        default:
            break;
    }
}

void HelloWorld::initBackground()
{
    bg1 = Sprite::create("background.png");
    bg2 = Sprite::create("background.png");
    
    bg1->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    auto size1 = bg1->getContentSize();
    bg1->setScale(visibleSize.width/size1.width, visibleSize.height/size1.height);
    addChild(bg1);
    
    bg2->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height + visibleSize.height/2);
    auto size2 = bg2->getContentSize();
    bg2->setScale(visibleSize.width/size2.width, visibleSize.height/size2.height);
    addChild(bg2);
}

void HelloWorld::moveBackground(float dt)
{
    bg1->setPositionY(bg1->getPositionY()-2);
    
    if(bg1->getPositionY() <= origin.y-visibleSize.height/2)
        bg1->setPositionY(origin.y+visibleSize.height/2);
    
    bg2->setPositionY(bg1->getPositionY()+visibleSize.height);
}

void HelloWorld::startGame()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    this->schedule(schedule_selector(HelloWorld::moveBackground), BACKGROUND_DURATION);
    
    createHero();
    this->schedule(schedule_selector(HelloWorld::createBigEnemy), BIG_ENEMY_CREATE_DURATION);
    this->schedule(schedule_selector(HelloWorld::createSmallEnemy), SMALL_ENEMY_CREATE_DURATION);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    
    listener->onTouchMoved = [=](Touch* touch, Event* event){
        
        auto newPos = touch->getDelta() + hero->getPosition();
        auto heroSize = hero->getContentSize();
        
        //防止飞机跑出屏幕
        if(newPos.x < origin.x + heroSize.width/2)
            newPos.x = origin.x + heroSize.width/2;
        else if(newPos.x > origin.x + visibleSize.width - heroSize.width/2)
            newPos.x = origin.x + visibleSize.width - heroSize.width/2;
        
        if(newPos.y < origin.y + heroSize.height/2)
            newPos.y = origin.y + heroSize.height/2;
        else if(newPos.y > origin.y + visibleSize.height - heroSize.height/2)
            newPos.y = origin.y + visibleSize.height - heroSize.height/2;
        
        this->hero->setPosition(newPos);
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    EventListenerPhysicsContact* hitListener = EventListenerPhysicsContact::create();
    hitListener->onContactBegin = [=](const PhysicsContact& contact){
        
        auto tagA = contact.getShapeA()->getBody()->getTag();
        auto tagB = contact.getShapeB()->getBody()->getTag();
        
        //Hero die
        if(tagA == ContactTag::HERO
           || tagB == ContactTag::HERO)
        {
            this->unscheduleAllCallbacks();
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            Director::getInstance()->getEventDispatcher()->removeEventListener(hitListener);
            log("hero die");
            
            auto overLabel = CSLoader::createNode("Layer.csb")->getChildByName("OverLabel");
            overLabel->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
            addChild(overLabel);
            
            auto restart = (ui::Button*)overLabel->getChildByName("Bt_restart");
            auto exit = (ui::Button*)overLabel->getChildByName("Bt_exit");
            
            restart->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchRestart, this));
            exit->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchExit, this));
            
        }
        else if(tagA == ContactTag::ENEMY
                || tagB == ContactTag::ENEMY)
        {
            auto a = (Sprite*)contact.getShapeA()->getBody()->getNode();
            auto b = (Sprite*)contact.getShapeB()->getBody()->getNode();
            
            log("%s", a->getName().c_str());
            log("%s", a->getParent()->getName().c_str());
            if(tagA == ContactTag::ENEMY)
                a->getParent()->unscheduleAllCallbacks();
            else
                b->getParent()->unscheduleAllCallbacks();
            
            this->removeChild(a->getParent());
            this->removeChild(b->getParent());
        }
        
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hitListener, this);
}

void HelloWorld::touchRestart(Ref* object, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        log("a");
        removeAllChildren();
        Director::getInstance()->getRunningScene()->getPhysicsWorld()->removeAllBodies();
        Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
        startGame();
    }
}

void HelloWorld::touchExit(Ref* object, ui::Widget::TouchEventType type)
{
    if(type == ui::Widget::TouchEventType::ENDED)
    {
        log("b");
        exit(0);
    }
}

void HelloWorld::createHero()
{
    //英雄
    hero = CSLoader::createNode("HeroNode.csb");
    auto heroAction = CSLoader::createTimeline("HeroNode.csb");
    hero->runAction(heroAction);
    heroAction->play("HeroIdle", true);
    hero->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/4);
    
    Size size = hero->getChildByName("HeroSprite")->getContentSize();
    hero->setContentSize(size);
    
    auto body = PhysicsBody::createBox(hero->getContentSize());
    body->setTag(ContactTag::HERO);
    body->setCategoryBitmask(0x0001);
    body->setCollisionBitmask(0x1010);
    body->setContactTestBitmask(0x1010);
    
    hero->getChildByName("HeroSprite")->setPhysicsBody(body);
    addChild(hero);
    
    this->schedule(schedule_selector(HelloWorld::heroFire), HERO_FIRE_DURATION);
}

void HelloWorld::createBigEnemy(float dt)
{
    //大怪物
    auto bigEnemy = CSLoader::createNode("BigEnemyNode.csb");
    auto bigEnemyAction = CSLoader::createTimeline("BigEnemyNode.csb");
    bigEnemy->runAction(bigEnemyAction);
    bigEnemyAction->play("BigEnemyIdle", true);
    
    Size size = bigEnemy->getChildByName("BigEnemySprite")->getContentSize();
    bigEnemy->setContentSize(size);

    int x = rand()%(int)(origin.x + visibleSize.width - size.width) + size.width/2;
    auto startPos = Point(x, origin.y + visibleSize.height + size.height);
    auto endPos = Point(x, origin.y + visibleSize.height/5*4);
    bigEnemy->setPosition(startPos);

    auto move = MoveTo::create(2.5, endPos);
    bigEnemy->runAction(Sequence::create(move, CallFunc::create([=](){
        bigEnemy->schedule(schedule_selector(HelloWorld::enemyFire), ENEMY_FIRE_DURATION);
        //bigEnemy->removeFromParent();
    }), NULL));
    
    auto body = PhysicsBody::createBox(bigEnemy->getContentSize());
    body->setTag(ContactTag::ENEMY);
    body->setCategoryBitmask(0x0010);
    body->setCollisionBitmask(0x0101);
    body->setContactTestBitmask(0x0101);
    
    bigEnemy->getChildByName("BigEnemySprite")->setPhysicsBody(body);
    
    addChild(bigEnemy);
}

void HelloWorld::createSmallEnemy(float dt)
{
    //小怪物
    auto smallEnemy = CSLoader::createNode("SmallEnemyNode.csb");
    auto smallEnemyAction = CSLoader::createTimeline("SmallEnemyNode.csb");
    smallEnemy->runAction(smallEnemyAction);
    smallEnemyAction->play("SmallEnemyIdle", true);
    
    Size size = smallEnemy->getChildByName("SmallEnemySprite")->getContentSize();
    smallEnemy->setContentSize(size);
    
    int x = rand()%(int)(origin.x + visibleSize.width - size.width) + size.width/2;
    auto startPos = Point(x, origin.y + visibleSize.height + size.height);
    auto endPos = Point(x, origin.y - size.height/2);
    smallEnemy->setPosition(startPos);
    
    auto move = MoveTo::create(1, endPos);
    smallEnemy->runAction(Sequence::create(move, CallFunc::create([=](){
        smallEnemy->removeFromParent();
    }), NULL));
    
    auto body = PhysicsBody::createBox(smallEnemy->getContentSize());
    body->setTag(ContactTag::ENEMY);
    body->setCategoryBitmask(0x0010);
    body->setCollisionBitmask(0x0101);
    body->setContactTestBitmask(0x0101);

    smallEnemy->getChildByName("SmallEnemySprite")->setPhysicsBody(body);
    
    addChild(smallEnemy);
}

void HelloWorld::heroFire(float dt)
{
    auto bullet = Sprite::create("bullet1.png");
    
    auto body = PhysicsBody::createBox(bullet->getContentSize());
    body->setTag(ContactTag::HERO_BULLET);
    body->setCategoryBitmask(0x0100);
    body->setCollisionBitmask(0x0010);
    body->setContactTestBitmask(0x0010);
    
    bullet->setPhysicsBody(body);
    
    auto startPos = hero->getPosition() + Point(0, hero->getContentSize().height/2);
    auto endPos = Point(hero->getPositionX(), origin.x + visibleSize.height + hero->getContentSize().height/2);

    auto duraction = (endPos.y - startPos.y) / HERO_BULLET_SPEED;
    bullet->setPosition(startPos);
    addChild(bullet);
    
    auto fire = Sequence::create(MoveTo::create(duraction, endPos), CallFunc::create([=](){
        bullet->removeFromParent();
    }), NULL);
    bullet->runAction(fire);
}

void HelloWorld::enemyFire(float dt)
{
    auto bullet = Sprite::create("bullet2.png");
    
    auto body = PhysicsBody::createBox(bullet->getContentSize());
    body->setTag(ContactTag::ENEMY_BULLET);
    body->setCategoryBitmask(0x1000);
    body->setCollisionBitmask(0x0001);
    body->setContactTestBitmask(0x0001);
    
    bullet->setPhysicsBody(body);
    
    auto startPos = this->getPosition() + Point(0, -this->getContentSize().height/2);
    auto endPos = Point(this->getPositionX(), origin.x - this->getContentSize().height/2);
    
    auto duraction = (startPos.y - endPos.y) / ENEMY_BULLET_SPEED;
    bullet->setPosition(startPos);
    getParent()->addChild(bullet);
    
    auto fire = Sequence::create(MoveTo::create(duraction, endPos), CallFunc::create([=](){
        bullet->removeFromParent();
    }), NULL);
    bullet->runAction(fire);
}
