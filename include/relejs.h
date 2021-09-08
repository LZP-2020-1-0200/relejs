/* File relejs.h */
#ifndef RELEJS_H
#define RELEJS_H
#include <Arduino.h>

#define RELEJS 2

class Relejs
{
private:
    /* data */
public:
    Relejs(/* args */);
    ~Relejs();
    void on(void);
    void off(void);
};

extern Relejs relejs;

#endif /* RELEJS_H */