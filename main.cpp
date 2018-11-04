#include <iostream>
#include <serverevent.h>

int main(int argc, char * argv[])
{
    ServerEvent s(8080);
    std::cout << "Listening...";
    std::fflush(stdout);
    s.startListening();
    std::cout << "Connected!\n";
    s.sendRequest(REQUEST_NORMAL);
}
