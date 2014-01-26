#ifndef PROTOCOL_BOARD_H_
#define PROTOCOL_BOARD_H_

namespace protocol {

struct Board {
  int fields[9][9];
  int blocked[81][81];
};

}  // namespace protocol

#endif  // PROTOCOL_BOARD_H_
