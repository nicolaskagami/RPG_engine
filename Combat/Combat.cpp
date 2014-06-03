#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <bitset>
#include "Combat.h"


void Direction::print()
{
    printf("Orientation: ");
    switch(h_orientation.to_ulong())
    {
        case NW:
            printf("NW");break;
        case N:
            printf("N");break;
        case NE:
            printf("NE");break;
        case W:
            printf("W");break;
        case E:
            printf("E");break;
        case SW:
            printf("SW");break;
        case S:
            printf("S");break;
        case SE:
            printf("SE");break;
        default:
            printf("Impossiburu\n");
    }
    printf("\nHeight: %d\n", v_orientation.to_ulong());
}
int Direction::horizontal_difference(Direction A, Direction B)
{
   switch(abs(A.h_orientation.to_ulong() - B.h_orientation.to_ulong()))
   {
        case 0: 
            return DIST0;
        case 1:
        case 7:
            return DIST1;
        case 2:
        case 6:
            return DIST2;
        case 3:
        case 5:
            return DIST3;
        case 4:
            return DIST4;
   }
}
Limb::Limb()
{
    strength = STD_STR;
    dexterity = STD_DEX;
    health = STD_HEALTH;
}
int main()
{
    Limb A,B;
    int i;
    for(i=0;i<12;i++)
    {
    printf("Diferença: %d\n",Direction::horizontal_difference(A.dir, B.dir));
    A.dir.h_orientation = A.dir.h_orientation.to_ulong() +1;
    //A.dir.print();
    }
}

