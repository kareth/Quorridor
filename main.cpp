#include <cstdio>
#include <string>
#include <iostream>

#include "visualization/console_display.h"
#include "client/client.h"
#include "server/server.h"
#include "control/keyboard.h"

std::string address = "127.0.0.1";
std::string port = "1239";

int main(int argc, char **argv) {
  std::string command = "";
  if (argc != 2 && argc != 4) {
    printf("\nUsage: \n");
    printf("%s client [address] [port] (defaults to localhost:1239)\n", argv[0]);
    printf("%s server [address] [port]\n\n", argv[0]);
    return 0;
  } else if (argc == 2){
    command = argv[1];
  } else if (argc == 4){
    command = argv[1];
    address = argv[2];
    port = argv[3];
  }
  while (command != "c" && command != "s")
    std::cin >> command;

  if (command == "s") {
    server::Server server(address, port);
    server.Start();
  }
  else if (command == "c") {
    visualization::ConsoleDisplay display;
    control::Keyboard input;

    client::Client client(address, port, display, input);
    client.Start();
  }
}
