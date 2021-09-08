#include "task.h"
#include "relejs.h"

Command::Command(const char *cmd_str, void (*ptr_func)(const char *)) //
    : cmd(cmd_str),
      cmd_len(strlen(cmd_str)),
      func(ptr_func)
{ // Regular constructor for command-function pairs
}

Command::Command(void (*ptr_func)(const char *)) //
    : cmd(nullptr),
      cmd_len(0),
      func(ptr_func)
{ // Special constructor for handling unknown commands
} // This error function must be the last one last in the cmd_list!

void HELP_func(const char *); // implementation requires cmd_list, see below

Command cmd_list[] = {
    //command-function pairs
    Command("*IDN?", [](const char *a)
            { Serial.println("Relejs 2021 pro"); }),

    Command("ON", [](const char *a)
            { relejs.on(); }),

    Command("OFF", [](const char *a)
            { relejs.off(); }),


            

    Command("HELP", HELP_func), //
    Command([](const char *a) { // error function must be last!
        Serial.print("unknown command ");
        Serial.print(a);
    })};

void HELP_func(const char *args)
{
    Serial.println(F("Available commands:"));
    for (Command *cl = cmd_list; cl->cmd; cl++)
    {
        Serial.println(cl->cmd);
    }
}

void parse(char *cmd_line, int cmd_line_len)
{
    if (cmd_line_len)
    {
        Command *cl = cmd_list;
        int cmd_num = 0;
        for (; cl->cmd; cl++)
        { // search for known commands
            if (0 == strncasecmp(cmd_line, cl->cmd, cl->cmd_len))
            { // known command found
                char *argument = &cmd_line[cl->cmd_len];
                while (*argument == ' ' || *argument == '\t')
                { // step over empty spaces between command and arguments
                    argument++;
                }
                cl->func(argument); //call the known function
                return;
            }
            cmd_num++;
        }
        cl->func(cmd_line); // this will call cmd_list -> ERROR_func
    }
    else
        Serial.println(F("Empty line"));
}

static int echo_on = 1;
void task_addChar(char ch)
{
    static char cmd_line[MAX_CMD_LEN + 1]; // buffer
    static int n = 0;                      // current char position
    if (echo_on)
        Serial.print(ch); // echo
    if (ch == 10)
        return; // ignore  (LF)

    if (ch == 13)
    {           // end of line
        ch = 0; // replace char by zero terminator
    }
    cmd_line[n++] = ch; // insert symbol

    if (ch == 0)
    {
        if (echo_on)
            Serial.println();
        parse(cmd_line, n - 1);
        n = 0;
    }
    if (n >= MAX_CMD_LEN)
    { // buffer overflow
        n = 0;
    }
}