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

	void gainExp(const int exp);

	void updateStats(const bool reset);
	void updateLevel();

	void update();
	
};

#endif