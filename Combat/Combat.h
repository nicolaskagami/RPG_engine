
#define STD_STR     100
#define STD_DEX     100
#define STD_HEALTH  100

class Limb
{
    public:
        int strength;
        int dexterity;
        int health;
        Limb();
}

class AnthroBody
{
    public:
        int mana_points;
        int stamina_points;
        Limb legs[2];
        Limb arms[2];
        int perception;
        int intelligence;
        int lung_capacity;
        int weight;
        int hunger;
        int vital_health;
}
