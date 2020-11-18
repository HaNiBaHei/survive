#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
public:
	// Level //
	int level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;

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

	// Consttructors //
	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();

	// Functions //
	std::string debugPrint() const;

	void gainExp(const unsigned exp);

	void updateStats(const bool reset);
	void updateLevel();

	void update();
	
};

#endif