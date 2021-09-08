/* File task.h */
#ifndef RELEJS_TASK_H
#define RELEJS_TASK_H
#include <Arduino.h>

#define MAX_CMD_LEN 80

void task_addChar(char ch);

class Command
{
private:
    /* data */
public:
    Command(const char *, void (*)(const char *));
    Command(void (*)(const char *)); // display command not found error message

    ~Command(){};
    const char *cmd;
    const size_t cmd_len;
    void (*func)(const char *);
};

#endif /* RELEJS_TASK_H */