#pragma once
class FireAttributeComponent
{
public:
	// Enemy //
	int hpMaxFire;
	int levelFire;
	int damageFire;

	int hpMaxRedBat;
	int levelRedBat;
	int damageRedBat;

	// Level //
	int level;
	int exp;
	int expNext;
	int attributePoints;

	// Attributes //
	int strength;
	int vitality;
	int dexterity;
	int agility;
	int intelligence;

	// Stats //
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int def;   // dont want //
	int luck;  // dont want //
	int score;

	// Consttructors //
	FireAttributeComponent(int level);
	virtual ~FireAttributeComponent();

	// Functions //
	void loseHP(const int hp);
	void gainHP(const int hp);

	const bool isDead() const;

	void updateStatsLevel1(const bool reset);
	void updateStatsLevel2(const bool reset);
	void updateStatsLevel3(const bool reset);
	void updateStatsLevel4(const bool reset);
	void updateStatsLevel5(const bool reset);

	void update();
};

