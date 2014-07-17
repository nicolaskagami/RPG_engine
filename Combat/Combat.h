#ifndef COMBAT_HEADER
#define COMBAT_HEADER

#define STD_STR         100
#define STD_DEX         100
#define STD_HEALTH      100

#define NUM_LIMBS       5 
#define BODY_WEAPONS    4

//Positions
//Circular!
#define NW              0
#define N               1
#define NE              2
#define E               3
#define SE              4
#define S               5
#define SW              6
#define W               7

#define VERY_LOW        0
#define LOW             1
#define HIGH            2
#define VERY_HIGH       3

#define DIST0           0
#define DIST1           7
#define DIST2           14
#define DIST3           18
#define DIST4           20

#define MAP_MAX_X       30
#define MAP_MAX_Y       30

class Direction
{
    public:
        std::bitset<3> h_orientation;
        std::bitset<2> v_orientation;
        std::bitset<2> stretch;

        static int horizontal_difference(Direction A, Direction B);
        void print();
};

class Injury
{
    public:
        char * name;
        float probability;
        unsigned char HP_static_coefficient;
        unsigned char HP_dynamic_coefficient;
        unsigned char STA_static_coefficient;
        unsigned char STA_dynamic_coefficient;
};

class Weapon
{
    public:
        char * name;
        float penetration_coefficient;
        unsigned char height;
        unsigned char weight;
        unsigned char point_of_balance;
        Direction dir;
};

class Armor
{
    public:
        unsigned char penetration_threshold;
        unsigned char momentum_absorption;
        float weight;
        unsigned char quality;
        unsigned char durability; //255 = 100%
};

class Limb
{
    public:
        unsigned char strength;
        unsigned char dexterity;
        int health;
        int stamina;
        unsigned char area;
        Direction dir;
        Armor * armor;
        Injury * injuries;

        Limb();
        void print();
};

class AnthroBody
{
    public:
        int health;
        int stamina;
        int weight;
        float height;
        Limb limbs[NUM_LIMBS];

        //Limbs
        // armL;
        // armR;
        // legL;
        // legR;
        // torso;
        // head;
        //
        void print();
        void recalculate();
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

        void print();
};

class Tile
{
    public:
        int type;
        Combatant * occupant;

        void print_type();
        Tile();
};

class Map
{
    public:
        Tile * tiles;     
        int x;
        int y;
        std::vector <Combatant> contenders;

        void print_contenders();
        void add_combatant(Combatant c);
        void print_ascii();
        Map(int a, int b);
};

class Attack
{
    public:
        Combatant * attacker;
        Combatant * defender;
        Map * map;
        
        void execute();
};
#endif
