#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
private:
	sf::Music levelup;

	void initMusic();
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
	int damageSword;
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

	void resetHp(const int hpmax);

	const bool isDead() const;

	void updateStats(const bool reset);
	void updateLevel();

	void update();
	
};

#endif