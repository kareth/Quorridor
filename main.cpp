#include <cstdio>
#include <string>
#include <iostream>

#include "visualization/console_display.h"
#include "client/client.h"
#include "server/server.h"
#include "control/keyboard.h"

std::string address = "127.0.0.1";
std::string port = "1239";

int main() {
  std::string command = "";
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
