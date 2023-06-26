
#include "commandline.h"


Commandline::Commandline(QObject* parent, FILE* fileHandler)
    : QObject{parent},cin{fileHandler}{}

void Commandline::monitor()
{
    while(1)
    {
        QString value = cin.readLine();
        emit command(value);
    }
}
