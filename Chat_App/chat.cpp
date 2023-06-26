


#include "chat.h"


Chat::Chat(QObject *parent)
    : QObject{parent}
{
    if(!socket.bind(port,QUdpSocket::ShareAddress))
    {
        qInfo() << socket.errorString();
    }
    else
    {
        qInfo() << "Started On :" << socket.localAddress().toString() << ":" << socket.localPort();
        connect(&socket,&QUdpSocket::readyRead,this,&Chat::readyread);
    }
}

void Chat::command(QString value)
{
    QString message = name + ": ";
    if(name.isEmpty())
    {
        name = value;
        message = name + ": Joined";
        send(message);
        return;
    }

    message.append(value);
    send(message);

}

void Chat::send(QString value)
{
    QByteArray data = value.toLocal8Bit();
    QNetworkDatagram datagram(data,QHostAddress::Broadcast,port);
    if(!socket.writeDatagram(datagram))
    {
        qInfo() << socket.errorString();
    }

}

void Chat::readyread()
{
    while(socket.hasPendingDatagrams())
    {
        QNetworkDatagram datagram = socket.receiveDatagram();
        qInfo() << datagram.data();
    }
}
