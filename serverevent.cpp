#include "serverevent.h"


ServerEvent::ServerEvent(uint16_t port)
{
    status.isConnected = 0;
    status.isListening = 0;

    listener_socket = ::socket(AF_INET, SOCK_STREAM, 0);
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);
    setsockopt(listener_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &one, (socklen_t)sizeof(one));
    bind(listener_socket, (struct sockaddr*)&serverInfo, sizeof(serverInfo));
}


void ServerEvent::startListening()
{
    status.isListening = 1;
    listen(listener_socket, 2);
    acceptor_socket = accept(listener_socket, (struct sockaddr*)&clientInfo, &siz);
    status.isConnected = 1;
    status.isListening = 0;
}

void ServerEvent::setInitWebPage(char * fileName)
{
    initWebPage = fileName;
}

void ServerEvent::setEventName(char * eventString)
{
    eventName = eventString;
}

void ServerEvent::setEventFile(char * fileName)
{
    eventFile = fileName;
}

void ServerEvent::sendRequest(request req)
{
    if(req == REQUEST_NORMAL)
    {
    }
}
