#ifndef _DESIGN_CONTROLER_H_
#define _DESIGN_CONTROLER_H_

#include "cocos2d.h"
#include "ResBox.h"
#include "Panel.h"

#include <vector>

#include "GameFrame/GameScene.h"
#include "Tools/SaveManager.h"
#include "MainMenu/DesignLayer.h"
#define DEFAULT_SIZE 20
USING_NS_CC;

class ResBox;
using pii = std::pair<int, int>;
extern class DesignControler {
public:
    DesignLayer* dl;
    std::vector<Sprite*> disp;
    std::vector<pii> size;
    static DesignControler* _instance;
    static DesignControler* get();
    void init(DesignLayer* dl);
    void addDefault();
    void display();
    DesignControler();

    ~DesignControler();

};
#endif