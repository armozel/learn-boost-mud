// Mud.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Server.hpp"
int main()
{
    std::cout << "Hello World!\n";
    Mud::Server::Server server(5000);

    server.Run();

    std::cout << "Server is finished running..." << std::endl;
}
