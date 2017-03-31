#include "cpu.h"

CPU::CPU(byte & main_memory)
{
  //V0 = V1 = V2 = V3 = V4 = V5 = V6 = V7 = V8 = V9 = VA = VB = VC = VD = VE = VF = 0;

  memory = &main_memory;
  
  srand(time(NULL));

  SP = I = 0;

  PC = 0x200;

}

CPU::~CPU()
{
}

void CPU::step()
{
  display_state();
  switch(*(memory + PC) & 0xF0)
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
  //*(memory + PC + 1) & 0xF0)
  switch(*(memory + PC + 1) & 0x0F)
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

void CPU::display_state()
{
  printf("INSTRUCTION: 0x%02X%02X\n", memory[PC], memory[PC + 1]);
  /*
  for(int i = 0; i < 16; ++i)
    printf("V%X: %02X\n", i, V[i]);

  printf("I: %04X\nPC: %04X\nDELAY: %04X\nTIMER: %04X\n\n", I, PC, DELAY, TIMER);

  printf("Stack contents: \n");

  for(int i = 0; i < 16; ++i)
    printf("%02X: %04X\n", i, stack[i]);

  printf("\n");
    */
}

uint16_t CPU::pop()
{
  return stack[--SP];
}

void CPU::push(uint16_t old_PC)
{
  stack[SP++] = old_PC;

  return;
}

void CPU::op_0nnn()
{
  push(PC);
  PC = *(memory + PC) << 8| (byte) *(memory + PC + 1);
}
void CPU::op_00E0()
{
  //TODO GFX
}
void CPU::op_00EE()
{
  PC = pop();
}
void CPU::op_1nnn()
{
  PC = *(memory + PC) << 8 | *(memory + PC + 1);
  PC &= 0x0FFF;

  //PC = bytes_to_word(*(memory + PC), *(memory + PC + 1)) & 0xF0;
}
void CPU::op_2nnn()
{
  push(PC + 2);



  PC = *(memory + PC) << 8| (byte) *(memory + PC + 1);
  PC &= 0x0FFF;
 // PC = bytes_to_word(*(memory + PC), *(memory + PC + 1)) & 0xF0;
}
void CPU::op_3xkk()
{
  if(V[*(memory + PC) & 0x0F] == *(memory + PC + 1))
    PC += 4;
  else
    PC += 2;
}
void CPU::op_4xkk()
{
  if(V[*(memory + PC) & 0x0F] != *(memory + PC + 1))
    PC += 4;
  else
    PC += 2;
}
void CPU::op_5xy0()
{
  if(V[*(memory + PC) & 0x0F] == V[*(memory + PC + 1) & 0x00])
    PC += 2;
}
void CPU::op_6xkk()
{
  V[*(memory + PC) & 0x0F] = *(memory + PC + 1);
  PC += 2;
}
void CPU::op_7xkk()
{
  V[*(memory + PC) & 0x0F] += *(memory + PC + 1);
  PC += 2;
}
void CPU::op_8xy0()
{
  V[*(memory + PC) & 0x0F] = V[*(memory + PC + 1) & 0x0F];
  PC += 2;
}
void CPU::op_8xy1()
{
  V[*(memory + PC) & 0x0F] |= V[*(memory + PC + 1) & 0x0F];
  PC += 2;
}
void CPU::op_8xy2()
{
  V[*(memory + PC) & 0x0F] &= V[*(memory + PC + 1) & 0x0F];
  PC += 2;
}
void CPU::op_8xy3()
{
  V[*(memory + PC) & 0x0F] ^= V[*(memory + PC + 1) & 0x0F];
  PC += 2;
}
void CPU::op_8xy4()
{
  if( (V[*(memory + PC) & 0x0F ] ) + (V[(*(memory + PC + 1) & 0x0F)])  > 0xFF)
    V[0x0F] = 0x01;
  else
    V[0x0F] = 0x00;
  PC += 2;
}
void CPU::op_8xy5()
{
  byte * x = &V[*(memory + PC) & 0x0F];

  byte * y = &V[*(memory + PC + 1) & 0x0F];

  (x > y) ? V[0x0F] = 1 : V[0x0F] = 0;

  *x -= *y;
  
  PC += 2;
}
void CPU::op_8xy6()
{
  byte lsb = V[*(memory + PC) & 0x0F];
  byte * x = &V[*(memory + PC) & 0xF0];

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
  byte * x = &V[*(memory + PC) & 0x0F];

  byte * y = &V[*(memory + PC + 1) >> 4 << 4];

  (y > x) ? V[0x0F] = 1 : V[0x0F] = 0;

  *x = *y - *x;
  
  PC += 2;
}
void CPU::op_8xyE()
{
  byte x_copy = V[*(memory + PC) & 0x0F];
  byte * x = &V[*(memory + PC) & 0x0F];

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
  if(V[*(memory + PC) & 0x0F] != V[*(memory + PC + 1) >> 4 << 4])
    PC += 2;

}
void CPU::op_Annn()
{

  I = *(memory + PC) << 8 | (byte) *(memory + PC + 1);
  I &= 0x0FFF;

  PC += 2;

}
void CPU::op_Bnnn()
{
  PC = ((*(memory + PC) << 8 | (*(memory + PC + 1))) & 0xF0 >> 4) + V[0];
}
void CPU::op_Cxkk()
{
  uint8_t r = rand() % 256;

  V[*(memory + PC) & 0x0F] = r & *(memory + PC + 1);

  PC += 2;
}
void CPU::op_Dxyn()
{
  //TODO GFX
  PC += 2;
}
void CPU::op_Ex9E()
{
  //TODO INPUT
  PC += 2;
}
void CPU::op_ExA1()
{
  //TODO INPUT
  PC += 2;
}
void CPU::op_Fx07()
{
  V[*(memory + PC) & 0x0F] = DELAY;
  PC += 2;
}
void CPU::op_Fx0A()
{
  //TODO INPUT
  PC += 2;
}
void CPU::op_Fx15()
{
  DELAY = V[*(memory + PC) & 0x0F];
  PC += 2;
}
void CPU::op_Fx18()
{
  TIMER = V[*(memory + PC) & 0x0F];
  PC += 2;
}
void CPU::op_Fx1E()
{
  I += V[*(memory + PC) & 0x0F];
  PC += 2;
}
void CPU::op_Fx29()
{
  //TODO GFX
  PC += 2;
}
void CPU::op_Fx33()
{
  //TODO Refresh on binary-coded decimal
  int i;
  cin >> i;
}
void CPU::op_Fx55()
{
  int limit = (*(memory + PC) & 0x0F) + 1;

  for(int i = 0; i < limit; ++i)
  {
    memory[I + i] = *(V + i);
  }
  PC += 2;

  /*
  byte * offset = &*(memory + I);

  for(int i = 0; i < limit; ++i)
  {
    *(offset + i) = *(V + i);
  }
  */
}
void CPU::op_Fx65()
{
  int limit = (*(memory + PC) & 0x0F) + 1;

  for(int i = 0; i < limit; ++i)
  {
    *(V + i) = memory[I + i];
  }
   PC += 2;
}
