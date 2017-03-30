#include "includes.h"
#include <time.h>
#include <stdlib.h>



class CPU
{
  public:
    CPU(byte & memory);
    ~CPU();

    void step();

  private:

    //byte V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF, 
    byte V[16], SP;

    uint16_t pop();
    void push(uint16_t old_PC);
    void display_state();

    void ops_0();   void ops_8();   void ops_E();   void ops_F();

		void op_0nnn(); void op_00E0(); void op_00EE(); void op_1nnn();
		void op_2nnn(); void op_3xkk(); void op_4xkk(); void op_5xy0();
		void op_6xkk(); void op_7xkk(); void op_8xy0(); void op_8xy1();
		void op_8xy2(); void op_8xy3(); void op_8xy4(); void op_8xy5();
		void op_8xy6(); void op_8xy7(); void op_8xyE(); void op_9xy0();
		void op_Annn(); void op_Bnnn(); void op_Cxkk(); void op_Dxyn();
		void op_Ex9E(); void op_ExA1(); void op_Fx07(); void op_Fx0A();
		void op_Fx15(); void op_Fx18(); void op_Fx1E(); void op_Fx29();
		void op_Fx33(); void op_Fx55(); void op_Fx65();

    uint16_t I, PC, DELAY, TIMER;

    uint16_t stack[16];

    byte * memory;
  
};

