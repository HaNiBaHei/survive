#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
public:
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
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	// Functions //
	std::string debugPrint() const;

	void loseHP(const int hp);
	void gainHP(const int hp);

	void loseEXP(const int exp);
	void gainExp(const int exp);

	void loseScore(const int score);
	void gainScore(const int score);

	const bool isDead() const;

	void updateStats(const bool reset);
	void updateLevel();

	void update();
	
};

#endif