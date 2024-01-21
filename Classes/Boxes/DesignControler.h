#ifndef _DESIGN_CONTROLER_H_
#define _DESIGN_CONTROLER_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ResBox.h"
#include "Panel.h"

#include <vector>

#include "GameFrame/GameScene.h"
#include "Tools/SaveManager.h"
#include "MainMenu/DesignLayer.h"
#define DEFAULT_SIZE 20
#define MAX_SIZE 15
USING_NS_CC;
using namespace ui;

class ResBox;
using pii = std::pair<int, int>;
class dataset {
public:
    int cnt;
    int x;
    int y;
    char data1[MAX_SIZE][MAX_SIZE];
    char data2[MAX_SIZE][MAX_SIZE];
    dataset(int cnt, int x, int y) :x(x), y(y), cnt(cnt) {
        for (int i = 0; i < MAX_SIZE; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                data1[i][j] = '.';
                data2[i][j] = ' ';
            }
        }
    }
};

extern class DesignControler {
public:
    int size_x;
    int size_y;
    int boxcnt;
    int this_box;
    Sprite* chosen;
    DesignLayer* dl;
    std::vector<Sprite*> board;
    std::vector<dataset*> data;
    std::vector<Sprite*> disp;
    static DesignControler* _instance;
    static DesignControler* get();
    void init(DesignLayer* dl);
    void addDefault();
    void display();
    void setChosen(Sprite* s);
    void drawBox(dataset* dc);
    void putBox(Sprite* box);
    DesignControler();

    ~DesignControler();

};
#endif
