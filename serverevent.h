#ifndef SERVEREVENT_H
#define SERVEREVENT_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

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

    char * initWebPage;
    char * eventName;
    char * eventFile;

    struct
    {
        uint8_t isConnected : 1;
        uint8_t isListening : 1;
    }status;

public:
    ServerEvent(uint16_t port);
    void startListening();
    void setInitWebPage(char * fileName);
    void setEventName(char * eventString);
    void setEventFile(char * fileName);
    void sendRequest(request req);
};

#endif // SERVEREVENT_H
