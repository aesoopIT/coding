#ifndef ACTIVE_H
#define ACTIVE_H
#include<passive.h>
#include<vector>

class Active
{
private:
    std::vector<Passive*> observers;
public:
    Active();
    virtual ~Active() = default;
    void attach(Passive* observer);
    void detach(Passive* observer);
    void activate();

    bool isObserverAttached(Passive* observer) const;
};

#endif // ACTIVE_H
