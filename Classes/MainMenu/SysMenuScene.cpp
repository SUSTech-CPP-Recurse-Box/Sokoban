/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "LevelSelectLayer.h"
#include "LoadLayer.h"
#include "HelpLayer.h"
#include "DesignLayer.h"

#include "SysMenuScene.h"

USING_NS_CC;

Scene* SysMenuScene::createScene()
{
    return SysMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SysMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto startItem = MenuItemImage::create(
        "MainMenu/start.png", "MainMenu/start.png",
        [&](Ref* sender) {
            Scene* scene = LevelSelectLayer::scene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene));
        });

    auto loadItem = MenuItemImage::create(
        "MainMenu/resume.png", "MainMenu/resume.png",
        [&](Ref* sender) {
            Scene* scene = LoadLayer::scene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene));
        });

    auto designItem = MenuItemImage::create(
        "MainMenu/create_tool.png", "MainMenu/create_tool.png",
        [&](Ref* sender) {
            Scene* scene = DesignLayer::scene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene));
        });

    auto helpItem = MenuItemImage::create("MainMenu/bubble.png", "MainMenu/bubble.png",
        [&](Ref* sender) {
            Scene* scene = HelpLayer::scene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene));
        });

    //closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, loadItem, helpItem, designItem, NULL);
    menu->alignItemsInColumns(1, 1, 2);
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Recurse Box", "fonts/Marker Felt.ttf", 48);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("MainMenu/MainBG.png");
    if (sprite == nullptr)
    {
        problemLoading("'MainMenu/MainBG.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}