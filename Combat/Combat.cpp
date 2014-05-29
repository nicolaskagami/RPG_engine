#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <bitset>
#include "Combat.h"

Limb::Limb()
{
    strength = STD_STR;
    dexterity = STD_DEX;
    health = STD_HEALTH;
    int i;
    for(i=0;i<5;i++)
    {
        position[i] = 0;
    }
}
int main()
{
    Limb A;
    std::cout << A.position;
}

