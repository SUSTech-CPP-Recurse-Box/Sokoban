#ifndef _PANEL_H_
#define _PANEL_H_
#include <vector>

#include "ResBox.h"
using pii = std::pair<int, int>;

class Target {
public:
    int type;
    int boxId;
    pii pos;
    Target(int type, int id, int x, int y) :type(type), boxId(id), pos({ x, y }) {}
};

class Panel {
public:
    static Panel* instance;
    std::vector<Target> targets;

    std::vector<ResBox*> boxes;
    std::vector<ResBox*> infs;
    std::vector<ResBox*> epss;

    ResBox* initBox;
    ResBox* player;

    Panel() {};
    ~Panel() {};
    static Panel* getInstance();
    bool levelInit(int id);

    friend std::string printCLI(Panel* panel);
};
#endif