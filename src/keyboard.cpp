#include "keyboard.h"

void keyboardInit()
{
  DDRD &= ~(1 << BUTTON_PLAY | 1 << BUTTON_FF | 1 << BUTTON_REV);
  PORTD = (1 << BUTTON_PLAY | 1 << BUTTON_FF | 1 << BUTTON_REV);
}

uint8_t readKeys(uint8_t previousKeysState, uint8_t &keyHoldCtr)
{
  uint8_t tempKeys = ~PIND & (1 << BUTTON_PLAY | 1 << BUTTON_REV | 1 << BUTTON_FF);
  uint8_t maskedWorkMode = workMode & 0b01111110;

  if (tempKeys & ~previousKeysState & 1 << BUTTON_PLAY)
  {
    workMode ^= (1 << MOVE_FOLLOW_STARS);
    keyHoldCtr = 0;
  }
  if (tempKeys & previousKeysState & 1 << BUTTON_PLAY)
  {
    keyHoldCtr++;
    if (keyHoldCtr > 20)
    {
      workMode ^= (1 << MOVE_DIRECTION);
      keyHoldCtr = 0;
    }
  }
  if (tempKeys & ~previousKeysState & 1 << BUTTON_FF)
  {
    workMode &= ~(1 << MOVE_REVERSE_4X | 1 << MOVE_REVERSE_8X | 1 << MOVE_REVERSE_MAX);
    switch (maskedWorkMode)
    {
    case (1 << MOVE_REVERSE_4X):
      workMode &= ~(1 << MOVE_REVERSE_4X);
      break;
    case (1 << MOVE_REVERSE_8X):
      workMode &= ~(1 << MOVE_REVERSE_8X);
      break;
    case (1 << MOVE_REVERSE_MAX):
      workMode &= ~(1 << MOVE_REVERSE_MAX);
      break;
    case (1 << MOVE_FORWARD_4X):
      workMode &= ~(1 << MOVE_FORWARD_4X);
      workMode |= (1 << MOVE_FORWARD_8X);
      break;
    case (1 << MOVE_FORWARD_8X):
      workMode &= ~(1 << MOVE_FORWARD_8X);
      workMode |= (1 << MOVE_FORWARD_MAX);
      break;
    case (1 << MOVE_FORWARD_MAX):
      workMode &= ~(1 << MOVE_FORWARD_MAX);
      break;
    default:
      workMode |= (1 << MOVE_FORWARD_4X);
      break;
    }
  }
  if (tempKeys & ~previousKeysState & 1 << BUTTON_REV)
  {
    workMode &= ~(1 << MOVE_FORWARD_4X | 1 << MOVE_FORWARD_8X | 1 << MOVE_FORWARD_MAX);
    switch (maskedWorkMode)
    {
    case (1 << MOVE_FORWARD_4X):
      workMode &= ~(1 << MOVE_FORWARD_4X);
      break;
    case (1 << MOVE_FORWARD_8X):
      workMode &= ~(1 << MOVE_FORWARD_8X);
      break;
    case (1 << MOVE_FORWARD_MAX):
      workMode &= ~(1 << MOVE_FORWARD_MAX);
      break;
    case (1 << MOVE_REVERSE_4X):
      workMode &= ~(1 << MOVE_REVERSE_4X);
      workMode |= (1 << MOVE_REVERSE_8X);
      break;
    case (1 << MOVE_REVERSE_8X):
      workMode &= ~(1 << MOVE_REVERSE_8X);
      workMode |= (1 << MOVE_REVERSE_MAX);
      break;
    case (1 << MOVE_REVERSE_MAX):
      workMode &= ~(1 << MOVE_REVERSE_MAX);
      break;
    default:
      workMode |= (1 << MOVE_REVERSE_4X);
      break;
    }
  }

  return tempKeys;
}
