#include "visualization/console_display.h"

namespace visualization {

ConsoleDisplay::ConsoleDisplay() {}

void ConsoleDisplay::ShowBoard(const game::Board& board) const {

  for (int x = 0; x < board.size(); x++) {
    for (int y = 0; y < board.size(); y++) {
      game::Field field(x, y);
      game::Field next(x, y + 1);
      int who = board.At(field);
      PrintColoredField(who);

      if (y != board.size() - 1 &&
          board.IsBlocked(field, next))
        printf("\033[0;31m|\033[0m");
      else
        printf(" ");
    }
    printf("\n");

    for (int y = 0; y < board.size(); y++) {
      game::Field from(x, y);
      game::Field to(x + 1, y);

      if (board.IsBlocked(from, to))
        printf("\033[1;31m---\033[0m");
      else
        printf("   ");

      if (y != board.size() - 1) {
        game::Field from_next(x, y + 1);
        game::Field to_next(x + 1, y + 1);

        if (board.IsBlocked(from, to) &&
            board.IsBlocked(from_next, to_next))
          printf("\033[1;31m-\033[0m");
        else if (board.IsBlocked(from, from_next) &&
            board.IsBlocked(to, to_next))
          printf("\033[0;31m|\033[0m");
        else
          printf(" ");
      }
      else {
        printf(" ");
      }
    }

    printf("\n");
  }
}

void ConsoleDisplay::PrintColoredField(int who) const {
  if (who == 0) {
    printf("[ ]");
  } else {
    SetColor(who);
    printf("[x]");
    ClearColor();
  }
}

void ConsoleDisplay::SetColor(int color) const {
  if (color == 1) printf("\033[1;32m");
  if (color == 2) printf("\033[1;33m");
  if (color == 3) printf("\033[1;34m");
  if (color == 4) printf("\033[1;35m");
}

void ConsoleDisplay::ClearColor() const {
  printf("\033[0m");
}

void ConsoleDisplay::ShowWalls(int count) const {
  printf("Remaining walls: %d\n", count);
}

void ConsoleDisplay::ShowMessageFor(const protocol::Command& command) const {
  printf("Server: ");
  switch(command.type) {
    case protocol::kGameStarted:
      printf("Game started");
      break;
    case protocol::kCorrectMove:
      printf("Correct move");
      break;
    case protocol::kInvalidMove:
      printf("Invalid move");
      break;
    case protocol::kGameFailed:
      printf("Game failed. One of players disconnected.");
      break;
    case protocol::WaitingForOpponents:
      printf("You have been added to lobby. Waiting for other players.");
      break;
    case protocol::kAnotherPlayerTurn:
      printf("Waiting for another player turn...");
      break;
  }
  printf("\n");
}

void ConsoleDisplay::ShowPlayerInfo(int id) const {
  SetColor(id);
  printf("Your id: %d\n", id);
  ClearColor();
  printf("\n");
}

void ConsoleDisplay::ShowWinner(int winner, int me) const {
  if (winner == me) {
    printf("\033[0;32mYou Won!\033[0m\n");
  } else {
    printf("\033[0;31mYou have lost. Player %d won. \033[0m\n", winner);
  }
  printf("\n");
}


}  // namespace visualization
