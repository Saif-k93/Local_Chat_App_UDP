

#include <QCoreApplication>
#include <QtConcurrent>
#include <QThread>
#include <QThreadPool>
#include <QFuture>

#include "commandline.h"
#include "chat.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThreadPool pool;

    Commandline cli(&a,stdin);

    QFuture<void> future = QtConcurrent::run(&pool,&Commandline::monitor,&cli);

    Chat chat;

    QObject::connect(&cli,&Commandline::command,&chat,&Chat::command,Qt::QueuedConnection);

    qInfo() << "Enter YourName To Begin";


    return a.exec();
}
