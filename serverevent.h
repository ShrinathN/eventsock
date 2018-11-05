#ifndef SERVEREVENT_H
#define SERVEREVENT_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

const char standard_response[] = "HTTP/1.1 200 OK\nContent-type: text/html\nConnection: close\n\n";
const char standard_event_response[] = "HTTP/1.1 200 OK\nContent-Type: text/event-stream;charset=UTF-8\nTransfer-Encoding: identity\n\n";
const char standard_error_response[] = "HTTP/1.1 404 Not Found\nConnection: close\n\n";

enum request
{
    REQUEST_NORMAL = 0,
    REQUEST_EVENT
};

class ServerEvent
{
private:
    int listener_socket;
    int acceptor_socket;
    char one = 1;
    socklen_t siz = sizeof(sockaddr_in);
    struct sockaddr_in serverInfo;
    struct sockaddr_in clientInfo;

    const char * initWebPage;
    const char * eventName;
    const char * eventFile;

    char * globalBuffer;

    enum error
    {
        NOT_CONNECTED = 0,
        UNABLE_TO_WRITE_TO_SOCKET,
        COULD_NOT_OPEN_FILE
    };

    error lastError;
    struct
    {
        uint8_t isConnected : 1;
        uint8_t isListening : 1;
    }status;

public:
    ServerEvent(uint16_t port);
    void ServerEvent_startListening();
    void ServerEvent_setInitWebPage(const char * fileName);
    void ServerEvent_setEventName(const char * eventString);
    void ServerEvent_setEventFile(const char * fileName);
    void ServerEvent_sendRequest();
    void ServerEvent_closeConnection();
    void ServerEvent_acceptConnection();
};

#endif // SERVEREVENT_H
