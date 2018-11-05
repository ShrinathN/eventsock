#include "serverevent.h"


ServerEvent::ServerEvent(uint16_t port)
{
    status.isConnected = 0;
    status.isListening = 0;

    globalBuffer = (char *)malloc(1024); //allocating 1KiB as buffer space

    listener_socket = ::socket(AF_INET, SOCK_STREAM, 0);
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);
    setsockopt(listener_socket, SOL_SOCKET, SO_REUSEPORT, &one, sizeof(one));
    bind(listener_socket, (struct sockaddr*)&serverInfo, sizeof(serverInfo));
}


void ServerEvent::ServerEvent_startListening()
{
    status.isListening = 1;
    listen(listener_socket, 2);
}

void ServerEvent::ServerEvent_acceptConnection()
{
    acceptor_socket = accept(listener_socket, (struct sockaddr*)&clientInfo, &siz);
    status.isConnected = 1;
    status.isListening = 0;
}

void ServerEvent::ServerEvent_setInitWebPage(const char * fileName)
{
    initWebPage = fileName;
}

void ServerEvent::ServerEvent_setEventName(const char * eventString)
{
    eventName = eventString;
}

void ServerEvent::ServerEvent_setEventFile(const char * fileName)
{
    eventFile = fileName;
}

void ServerEvent::ServerEvent_sendRequest()
{
    if(!status.isConnected)
        exit(NOT_CONNECTED);
    recv(acceptor_socket, globalBuffer, 1024, 0);
    printf("%s", globalBuffer);
    if(strstr(globalBuffer, "favicon") != NULL) //favicon
    {

    }
    else if(strstr(globalBuffer, "event") == NULL) //event
    {
//        bzero(buffer, 1024);
//        FILE *in = NULL;
//        in = fopen(initWebPage,"r");
//        if(in == NULL)
//            exit(COULD_NOT_OPEN_FILE);
//        int tempCounter = 0;
//        while((buffer[tempCounter] = fgetc(in)) != -1) tempCounter++;
//        fclose(in);
//        send(acceptor_socket, buffer, tempCounter, 0);
    }
    else //normal response
    {
//        bzero(buffer, 1024);
//        FILE *in = NULL;
//        in = fopen(eventFile, "r");
//        if(in == NULL)
//            exit(COULD_NOT_OPEN_FILE);

//        bzero(buffer, sizeof(buffer));
//        int tempCounter = 0;
//        while((buffer[tempCounter] = fgetc(in)) != -1) tempCounter++;
//        fclose(in);

//        send(acceptor_socket, buffer, tempCounter, 0);
    }
}


void ServerEvent::ServerEvent_closeConnection()
{
    shutdown(acceptor_socket, SHUT_RDWR);
    status.isConnected = 0;
    status.isListening = 1;
}

void ServerEvent::ServerEvent_private_sendOK()
{
    if(!status.isConnected)
        exit(NOT_CONNECTED);
    char * localBuffer = (char *)malloc(1024);
    unsigned long * fileSize = (unsigned long *)malloc(sizeof(unsigned long));
    bzero(localBuffer, 1024);
    strcat(localBuffer, standard_response);
    FILE *in = NULL;
    in = fopen(initWebPage, "r");


}

void ServerEvent::ServerEvent_private_sendNOTFOUND()
{
    if(!status.isConnected)
        exit(NOT_CONNECTED);
}

void ServerEvent::ServerEvent_private_sendEvent()
{
    if(!status.isConnected)
        exit(NOT_CONNECTED);
}
