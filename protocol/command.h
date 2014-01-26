#ifndef PROTOCOL_COMMAND_H_
#define PROTOCOL_COMMAND_H_

namespace protocol {

enum CommandType {
  kGameStarted = 1,
  kGameFinished,
  kInvalidMove,
  kMoveRequest,
  kCorrectMove,
  kBoardInfo,
  kAnotherPlayerTurn,
  kGameFailed,
  kWalls,
  WaitingForOpponents
};

struct Command {
  int type;
  Command(int type) : type(type) {}
};

}  // namespace protocol

#endif  // PROTOCOL_COMMAND_H_
