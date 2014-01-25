#include "control/keyboard.h"

#include <cstdio>

namespace control {

Keyboard::Keyboard() : indexes_() {
  int alp[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
  for (int i = 0; i < 9; i++)
    indexes_[alp[i]] = i;
}

void Keyboard::GetMove(game::Move* move) const {
  printf("\nSpecify move (e.g. wall A0 B1)\n");

  char type[10];
  scanf(" %s", type);
  if (type[0] == 'w') {
    move->type = game::kWall;
    ReadFields(move);
  }
  else if (type[0] == 'm') {
    move->type = game::kMove;
    ReadFields(move);
  }
  else {
    printf("Invalid type. Re. \n");
    GetMove(move);
  }
}

void Keyboard::ReadFields(game::Move* move) const {
  game::Field from, to;

  int correct = 0;
  correct += ReadField(&from);
  correct += ReadField(&to);

  if (correct == 2) {
    move->from = from;
    move->to = to;
  } else {
    ReadFields(move);
  }
}

int Keyboard::ReadField(game::Field* field) const {
  char f[5];
  scanf(" %s", f);

  if (indexes_.find(f[0]) == indexes_.end() ||
      strlen(f) > 2 ||
      !(f[1] >= '0' && f[1] <= '9')) {
    printf("Invalid field format\n");
    return 0;
  } else {
    field->x = indexes_.at(f[0]);
    field->y = f[1] - '0';
    return 1;
  }
}

}  // namespace keyboard
