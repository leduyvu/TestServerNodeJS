#include "HelloWorldScene.h"
#define PORT 8080
#define HOST "192.168.1.134"
USING_NS_CC;
using namespace network;
using namespace std;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//HelloWorld* HelloWorld::create(){
//    HelloWorld* pRet = new HelloWorld();
//    if(pRet && pRet->init()){
//        pRet->autorelease();
//        return pRet;
//    }
//    else{
//        delete pRet;
//        pRet = NULL;
//        return NULL;
//    }
//
//}

//HelloWorld::HelloWorld(){
//}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    //socket Test    
    char addr[200]="192.168.1.134";
    int port= 8080;
    cs = ClientSocket(addr, port);
    cs.connect();

//    SIOClient *sio = SIOClient::connect("http://localhost:3000");
    this->scheduleUpdate();
    return true;
}

void HelloWorld::update(float delta){
    count++;
    timeSS += delta;
    if(count > 6){
        char buf[48];
        snprintf (buf, sizeof(buf), "%f", timeSS);
        cs.send(buf);
        CCLOG("time: %f", timeSS);
        count = 0;
        cs.recv(re);
        CCLOG("result : %s", re);
    }
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::testFunc(){
}