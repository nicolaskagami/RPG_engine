#ifndef COMBAT_HEADER
#define COMBAT_HEADER
#define STD_STR     100
#define STD_DEX     100
#define STD_HEALTH  100

#define NUM_LIMBS   5 

class Injury
{
    public:
        char * name;
        unsigned char probability;
        unsigned char HP_static_coefficient;
        unsigned char HP_dynamic_coefficient;
        unsigned char STA_static_coefficient;
        unsigned char STA_dynamic_coefficient;
};

class Limb
{
    public:
        unsigned char strength;
        unsigned char dexterity;
        unsigned char health;
        unsigned char stamina;
        unsigned char position;
        unsigned char area;
        Injury * injuries;
        Limb();
};

class AnthroBody
{
    public:
        unsigned char health;
        unsigned char stamina;
        unsigned char weight;
        unsigned char height;
        Limb limbs[NUM_LIMBS];

        //Limbs
        // armL;
        // armR;
        // legL;
        // legR;
        // torso;
        // head;
};

class Submove
{
    public:
        unsigned char limb;
        unsigned char initial_mask;
        unsigned char final_mask;
};

class Equipment
{
};

class Move
{
    public:
        Submove * submoves;
};

class Technique
{
    public:
        char * name;
        unsigned char id;
        Move * moves;
};

class Weapon
{
};

class Combatant
{
    public:
        AnthroBody body;
        Equipment equip;
        Technique * techs;
        unsigned char x;
        unsigned char y;
};

#endif
