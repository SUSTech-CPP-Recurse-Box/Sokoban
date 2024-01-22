#ifndef _CONTROLER_H_
#define _CONTROLER_H_

#include "cocos2d.h"
#include "ResBox.h"
#include "Panel.h"

#include <vector>

#include "GameFrame/GameScene.h"
#include "Tools/SaveManager.h"

USING_NS_CC;

class ResBox;
using pii = std::pair<int, int>;
extern class controler {
public:
    int lid;
    bool suc;
    bool needLoad;

    ResBox* big;
    ResBox* player;

    std::vector<pii> mv;
    std::vector<Sprite*> boxes;
    std::vector<ResBox*> boxeslist;

    double size;
    GameScene* gs;
    static controler* _instance;
    static controler* get();
    
    controler();

    ~controler();

    void init(int lid);

    void initPanel(Sprite* fa, double size, pii s, Color3B color, ResBox* rb);

    void draw(GameScene* gs, double size);

    void draw(double size, ResBox* draw, Sprite* father, Vec2 pos);

    bool success();

    void move(pii dir);
    void move1(pii dir);

    void reload(std::vector<pii> step);

    void magnify(double a);

};
#endif