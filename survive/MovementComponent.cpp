#include "MovementComponent.h"
// Initializer //

// Constructors //
MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite),
	maxVelocity(maxVelocity) ,acceleration(acceleration) ,deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

// Accessors //
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}



// Functions //

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:

		if (this->velocity.x == 0.f && velocity.y == 0.f)
			return true;

		break;

	case MOVING:

		if (this->velocity.x != 0.f || velocity.y != 0.f)
			return true;

		break;

	case MOVING_LEFT:

		if (this->velocity.x < 0.f)
			return true;

		break;

	case MOVING_RIGHT:

		if (this->velocity.x > 0.f)
			return true;

		break;

	case MOVING_UP:

		if (this->velocity.y < 0.f)
			return true;

		break;

	case MOVING_DOWN:

		if (this->velocity.y > 0.f)
			return true;

		break;
	}

	return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	// Accelerating the sprite until reaches the maximum velocity  //

	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;

}

void MovementComponent::update(const float& dt)
{
	// Decelerating the sprite and control the maximum velocity //
	// Move Sprite //

	if (this->velocity.x > 0.f)			// Check for positive x //			
	{
		// Max velocity check x positive //
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		// Deceleration x positive //
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;

	}
	else if (this->velocity.x < 0.f)	// Check for negative x //
	{
		// Max velocty check x negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		// Deceletion x negative //
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
	if (this->velocity.y > 0.f)			// Check for positive y //			
	{
		// Max velocity check y positive //
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		// Deceleration y positive //
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;

	}
	else if (this->velocity.y < 0.f)	// Check for negative y //
	{
		// Max velocty check y negative
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		// Deceletion y negative //
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}


	// Final Move //
	this->sprite.move(this->velocity * dt);// Use Velocity //
}
