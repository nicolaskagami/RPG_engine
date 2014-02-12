#ifndef COMBAT_HEADER
#define COMBAT_HEADER

#define STD_STR         100
#define STD_DEX         100
#define STD_HEALTH      100

#define NUM_LIMBS       5 
#define BODY_WEAPONS    4

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

class Weapon
{
    public:
        char * name;
        unsigned char penetration_coefficient;
        unsigned char height;
        unsigned char weight;
};

class Armor
{
    unsigned char penetration_threshold;
    unsigned char momentum_absorption;
    unsigned char weight;
    unsigned char quality;
    unsigned char durability; //255 = 100%
}

class Limb
{
    public:
        unsigned char strength;
        unsigned char dexterity;
        unsigned char health;
        unsigned char stamina;
        unsigned char position;
        unsigned char area;
        Armor * armor;
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
        Weapon weapons[2];

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
        unsigned char initial_mask;
        unsigned char lower_initial_position;
        unsigned char upper_initial_position;
        unsigned char final_position;
};

class Equipment
{

};

class Move
{
    public:
        Submove submoves[NUM_LIMBS];
};

class Technique
{
    public:
        char * name;
        Move * moves;
        Technique();
};

class TechniqueSkill
{
    unsigned char id;
    unsigned char level;
};

class Combatant
{
    public:
        AnthroBody body;
        Equipment equip;
        TechniqueSkill * techs;
        unsigned char x;
        unsigned char y;
};

#endif
