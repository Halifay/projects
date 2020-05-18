#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
   short x = 1, y = 1, z = 1;
   short int v_as;
	__asm
	{

		// считаем числитель 
		mov al, x;
		cbw;
		mov bx, y;
		add bx, 2;
		imul bx;
		mov cx, dx;
		mov bx, ax;
		sub bx, 2;
		sbb cx, dx;

		// считаем знаменатель 
		mov al, z; 
		cbw; 
		sub ax, 2; 
		xchg ax, bx;
		idiv bx;
		neg ax;
		sub ax, 1;
		mov v_as, ax; 
	}
	return v_as;
}


