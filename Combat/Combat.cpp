#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <vector>
#include <list>
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
        case 8: 
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
void Limb::print()
{
    printf("Limb:\n");
    printf("Strength: %d\n",strength);
    printf("Dexterity: %d\n",dexterity);
    printf("Health: %d\n", health);
    printf("Stamina: %d\n", stamina);
}
void AnthroBody::print()
{
    int i;
    printf("Body:\n");
    printf("Health: %d\n",health);
    printf("Stamina: %d\n", stamina);
    printf("Weight: %d\n", weight);
    printf("Limbs:\n");
    for(i=0;i<NUM_LIMBS;i++)
    {
        limbs[i].print();
    }
}
void Combatant::print()
{
    body.print();
}
void AnthroBody::recalculate()
{
    int i;
    for(i=0,health=0,stamina=0;i<NUM_LIMBS;i++)
    {
        health+=limbs[i].health;
        stamina+=limbs[i].stamina;
    }
    health = health/NUM_LIMBS;
    stamina = stamina/NUM_LIMBS;
}
void Map::print_contenders()
{
    int i;
    printf("Contenders:");
    for(i=0;i<contenders.size();i++)
    {
        contenders[i].print();
    }
}
Tile::Tile()
{
    type = 0;
}
void Tile::print_type()
{
    printf("%d",type);
}
Map::Map(int a, int b)
{
    tiles = NULL; 
    if((a <= MAP_MAX_X) && (b <= MAP_MAX_Y))
    {
        tiles = (Tile *) malloc(a*b*sizeof(Tile));
    }
    if(tiles == NULL)
    {
        printf("Map Creation Error\n");
        x = 0;
        y = 0;
    }
    else
    {
        x = a;
        y = b;
    }
}
void Map::add_combatant(Combatant c)
{
   contenders.push_back(c); 
}
void Map::print_ascii()
{
    int i,j;
    for(i=0;i<x;i++)
    {
        for(j=0;j<y;j++)
        {
            tiles[i*y+j].print_type();
        }
        printf("\n");
    }
}
void Attack::execute()
{
    
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
    
    Map hehe(10,10);
    Combatant hihi[10];
    for(i=0;i<10;i++)
    {
        hehe.add_combatant(hihi[i]);
    }
    //   hehe.print_contenders();
    hehe.print_ascii();
}
