#include <iostream>
#include <unistd.h>
#include <serverevent.h>

int main(int argc, char * argv[])
{
    ServerEvent s(atoi(argv[1]));
    s.ServerEvent_setInitWebPage("normal.txt");
    s.ServerEvent_setEventFile("event.txt");
    s.ServerEvent_startListening();
    while(1)
    {
        s.ServerEvent_acceptConnection();
        s.ServerEvent_sendRequest();
        s.ServerEvent_closeConnection();
    }
}
