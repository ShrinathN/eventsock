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
    char * localBuffer = (char *)malloc(1024);
    bzero(localBuffer, 1024);
    if(strstr(globalBuffer, "favicon") != NULL) //favicon
    {
        strcat(localBuffer, standard_error_response);
    }
    else if(strstr(globalBuffer, "event") != NULL) //event
    {
        char * localFileReadBuffer = (char *)malloc(1024);
        unsigned long * fileSize = (unsigned long *)malloc(sizeof(unsigned long));
        while(1)
        {
            bzero(localFileReadBuffer, 1024);
            bzero(localBuffer, 1024);
            FILE *in = NULL;
            in = fopen(eventFile, "r");
            fseek(in, 0, SEEK_END);
            *fileSize = ftell(in);
            rewind(in);
            fread(localFileReadBuffer, *fileSize, 1, in);
            fclose(in);
            strcat(localBuffer, standard_event_response);
            strcat(localBuffer, localFileReadBuffer);
            send(acceptor_socket, localBuffer, strlen(localBuffer), 0);
            sleep(1);
        }
        free(localFileReadBuffer);
        free(fileSize);

    }
    else //normal response
    {
        char * localFileReadBuffer = (char *)malloc(1024);
        unsigned long * fileSize = (unsigned long *)malloc(sizeof(unsigned long));
        bzero(localFileReadBuffer, 1024);
        FILE *in = NULL;
        in = fopen(initWebPage, "r");
        fseek(in, 0, SEEK_END);
        *fileSize = ftell(in);
        rewind(in);
        fread(localFileReadBuffer, *fileSize, 1, in);
        fclose(in);
        strcat(localBuffer, standard_response);
        strcat(localBuffer, localFileReadBuffer);
        free(localFileReadBuffer);
        free(fileSize);
    }
    send(acceptor_socket, localBuffer, strlen(localBuffer), 0);
    free(localBuffer);

}


void ServerEvent::ServerEvent_closeConnection()
{
    shutdown(acceptor_socket, SHUT_RDWR);
    status.isConnected = 0;
    status.isListening = 1;
}
