#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H
#include <string>

struct Input {
    int horizontal;
    int vertical;
    std::string command;
};

class AbstractController
{
public:
    virtual Input move() = 0;
    AbstractController();
    virtual ~AbstractController() = default;
};

#endif // ABSTRACTCONTROLLER_H
