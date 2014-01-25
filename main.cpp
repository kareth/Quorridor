#include <cstdio>
#include <string>
#include <iostream>

#include "visualization/console_display.h"
#include "client/client.h"
#include "server/server.h"
#include "control/keyboard.h"

int main() {
  std::string command = "";
  while (command != "c" && command != "s")
    std::cin >> command;

  if (command == "s") {
    server::Server server;
    server.Start();
  }
  else if (command == "c") {
    visualization::ConsoleDisplay display;
    control::Keyboard input;

    client::Client client(display, input);
    client.Start();
  }
}
