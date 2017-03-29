#include "cpu.h"

CPU::CPU(byte * & memory): memory(memory)
{
  //V0 = V1 = V2 = V3 = V4 = V5 = V6 = V7 = V8 = V9 = VA = VB = VC = VD = VE = VF = 0;
  
  srand(time(NULL));

  SP = I = 0;

  PC = 0x200;

}

void CPU::step()
{
  //uint16_t op = *(memory + PC) << 8 | *(memory + PC + 1);
  switch(*(memory + PC) >> 4 << 4)
  {
    case(0x00): ops_0();
                break;
    case(0x10): op_1nnn();
                break;
    case(0x20): op_2nnn();
                break;
    case(0x30): op_3xkk();
                break;
    case(0x40): op_4xkk();
                break;
    case(0x50): op_5xy0();
                break;
    case(0x60): op_6xkk();
                break;
    case(0x70): op_7xkk();
                break;
    case(0x80): ops_8();
                break;
    case(0x90): op_9xy0();
                break;
    case(0xA0): op_Annn();
                break;
    case(0xB0): op_Bnnn();
                break;
    case(0xC0): op_Cxkk();
                break;
    case(0xD0): op_Dxyn();
                break;
    case(0xE0): ops_E();
                break;
    case(0xF0): ops_F();
                break;
  }

}

void CPU::ops_0()
{
  switch(*(memory + PC + 1))
  {
    case(0xEE): op_00EE();
                break;
    case(0xE0): op_00E0();
                break;
    default: op_0nnn();
  }
}

void CPU::ops_8()
{
  switch(*(memory + PC + 1) << 4 >> 4)
  {
    case(0x01): op_8xy1();
                break;
    case(0x02): op_8xy2();
                break;
    case(0x03): op_8xy3();
                break;
    case(0x04): op_8xy4();
                break;
    case(0x05): op_8xy5();
                break;
    case(0x06): op_8xy6();
                break;
    case(0x07): op_8xy7();
                break;
    case(0x0E): op_8xyE();
                break;
  }
}

void CPU::ops_E()
{
  switch(*(memory + PC + 1))
  {
    case(0x9E): op_Ex9E();
                break;
    case(0xA1): op_ExA1();
                break;
  }
}

void CPU::ops_F()
{
  switch(*(memory + PC + 1))
  {
    case(0x07): op_Fx07();
                break;
    case(0x0A): op_Fx0A();
                break;
    case(0x15): op_Fx15();
                break;
    case(0x18): op_Fx18();
                break;
    case(0x1E): op_Fx1E();
                break;
    case(0x29): op_Fx29();
                break;
    case(0x33): op_Fx33();
                break;
    case(0x55): op_Fx55();
                break;
    case(0x65): op_Fx65();
                break;
  }
}

uint16_t CPU::bytes_to_word(byte left, byte right)
{
  return (uint16_t) left << 8 | right;
}

uint16_t CPU::pop()
{
  return stack[SP--];
}

void CPU::push(uint16_t old_PC)
{
  stack[++SP] = old_PC;

  return;
}

void CPU::op_0nnn()
{
  push(PC);
  PC = bytes_to_word(*(memory + PC), *(memory + PC + 1));
}
void CPU::op_00E0()
{
  //TODO GFX
}
void CPU::op_00EE()
{
  PC = stack[SP];
  --SP;
}
void CPU::op_1nnn()
{
  PC = bytes_to_word(*(memory + PC), *(memory + PC + 1)) << 4 >> 4;
}
void CPU::op_2nnn()
{
  push(PC);
  PC = bytes_to_word(*(memory + PC), *(memory + PC + 1)) << 4 >> 4;
}
void CPU::op_3xkk()
{
  if(V[*(memory + PC) << 4 >> 4] == *(memory + PC + 1))
    PC += 2;
}
void CPU::op_4xkk()
{
  if(V[*(memory + PC) << 4 >> 4] != *(memory + PC + 1))
    PC += 2;
}
void CPU::op_5xy0()
{
  if(V[*(memory + PC) << 4 >> 4] == V[*(memory + PC + 1) >> 4 << 4])
    PC += 2;
}
void CPU::op_6xkk()
{
  V[*(memory + PC) << 4 >> 4] = *(memory + PC + 1);
  PC += 2;
}
void CPU::op_7xkk()
{
  V[*(memory + PC) << 4 >> 4] += *(memory + PC + 1);
  PC += 2;
}
void CPU::op_8xy0()
{
  V[*(memory + PC) << 4 >> 4] = V[*(memory + PC + 1) >> 4 << 4];
  PC += 2;
}
void CPU::op_8xy1()
{
  V[*(memory + PC) << 4 >> 4] |= V[*(memory + PC + 1) >> 4 << 4];
  PC += 2;
}
void CPU::op_8xy2()
{
  V[*(memory + PC) << 4 >> 4] &= V[*(memory + PC + 1) >> 4 << 4];
  PC += 2;
}
void CPU::op_8xy3()
{
  V[*(memory + PC) << 4 >> 4] ^= V[*(memory + PC + 1) >> 4 << 4];
  PC += 2;
}
void CPU::op_8xy4()
{
  if( (int) (V[*(memory + PC) << 4 >> 4 ] ) + (int) (V[*(memory + PC + 1) >> 4 << 4 ] ) > 0xFF)
    V[0x0F] = 0x01;
  else
    V[0x0F] = 0x00;
  PC += 2;
}
void CPU::op_8xy5()
{
  byte * x = &V[*(memory + PC) << 4 >> 4];
  byte * y = &V[*(memory + PC + 1) >> 4 << 4];

  (x > y) ? V[0x0F] = 1 : V[0x0F] = 0;

  *x -= *y;
  
  PC += 2;
}
void CPU::op_8xy6()
{
  byte lsb = V[*(memory + PC) << 4 >> 4];
  byte * x = &V[*(memory + PC) << 4 >> 4];

  lsb &= 0xFF - lsb + 0x01; 

  if(lsb)
    V[0x0F] = 1;
  else
    V[0x0F] = 0;

  *x /= 2;

  PC += 2;
}
void CPU::op_8xy7()
{
  byte * x = &V[*(memory + PC) << 4 >> 4];
  byte * y = &V[*(memory + PC + 1) >> 4 << 4];

  (y > x) ? V[0x0F] = 1 : V[0x0F] = 0;

  *x = *y - *x;
  
  PC += 2;
}
void CPU::op_8xyE()
{
  byte x_copy = V[*(memory + PC) << 4 >> 4];
  byte * x = &V[*(memory + PC) << 4 >> 4];

  unsigned msb = 0;

  while (x_copy >>= 0x01) {
        ++msb;
  }

  if(msb)
    V[0x0F] = 1;
  else
    V[0x0F] = 0;

  *x *= 2;

  PC += 2;
}
void CPU::op_9xy0()
{
  if(V[*(memory + PC) << 4 >> 4] != V[*(memory + PC + 1) >> 4 << 4])
    PC += 2;

}
void CPU::op_Annn()
{
  I = *(memory + PC) << 8 | *(memory + PC + 1) << 4 >> 4;
  PC += 2;

}
void CPU::op_Bnnn()
{
  PC = *(memory + PC) << 8 | (*(memory + PC + 1) << 4 >> 4) + V[0];
}
void CPU::op_Cxkk()
{
  uint8_t r = rand() % 256;

  V[*(memory + PC) << 4 >> 4] = r & *(memory + PC + 1);

}
void CPU::op_Dxyn()
{
}
void CPU::op_Ex9E()
{
}
void CPU::op_ExA1()
{
}
void CPU::op_Fx07()
{
}
void CPU::op_Fx0A()
{
}
void CPU::op_Fx15()
{
}
void CPU::op_Fx18()
{
}
void CPU::op_Fx1E()
{
}
void CPU::op_Fx29()
{
}
void CPU::op_Fx33()
{
}
void CPU::op_Fx55()
{
}
void CPU::op_Fx65()
{
}
