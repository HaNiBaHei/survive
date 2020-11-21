#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H

enum Skills {MELEE = 0, RANGE, DEATHEYE, IRONBODY};




class SkillComponent
{
private:	
	class Skill
	{
	private:
		int type;
		int level;
		int levelCap;
		int exp;
		int expNext;

	public:
		Skill(int type)
		{
			this->type = type;
			this->level = 1;
			this->levelCap = 99;
			this->exp = 0;
			this->expNext = 100;
		}
		~Skill() {}

		// Accessors //
		inline const int& getType() const { return this->type; }
		inline const int& getLevel() const { return this->level; }
		inline const int& getExp() const { return this->exp; }
		inline const int& getExpNext() const { return this->expNext; }

		// Modifiers //
		inline void setLevel(const int level) { this->level = level; }
		inline void setLevelCap(const int level_cap) { this->level = level_cap; }


		// Functions //
		void gainExp(const int exp) 
		{ 
			this->exp += exp; 
			this->updateLevel();
		}

		void loseExp(const int exp)
		{
			this->exp -= exp;
		}
		
		void updateLevel(const bool up = true)
		{
			/**
			* Increases or decreases level of the skill
			* 
			*/
			if (up)
			{
				if (this->level < this->levelCap)
				{
					while (this->exp >= this->expNext)
					{
						if (this->level < this->levelCap)
						{
							this->level++;
							this->expNext = static_cast<int>(std::pow(this->level, 2)) * 10 + this->level * 2 + this->level;
						}
					}
				}
			}
			else
			{
				if (this->level > 0)
				{
					while (this->exp < 0)
					{
						if (this->level > 0)
						{
							this->level--;
							this->expNext = static_cast<int>(std::pow(this->level, 2)) * 10 + this->level * 2 + this->level;
						}
					}
				}
			}
		}
		void update()
		{
			
		}

	};

	std::vector<Skill> skills;
public:
	SkillComponent();
	virtual ~SkillComponent();

	const int getSkill(const int index) const;
	const void gainExp(const int skill, const int exp);
};

#endif 