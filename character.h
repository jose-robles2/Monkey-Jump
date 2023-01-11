/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: Class definition for the abstract Character class.
 ******************************************************************************/
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Character {

public:

	Character() {}

	virtual void render(sf::RenderTarget* target);  
	virtual void initTexture() = 0;	
	virtual void initSprite() = 0;						


	////////GETTERS BELOW////////
	sf::Vector2f& getPos() {
		return this->mPos; 
	}
	int getHealth() 
	{
		return health;
	}
	sf::Sprite& getSprite() 
	{
		return mSprite;
	}

	////////SETTERS BELOW////////
	void setHealth(int newHealth) 
	{
		(newHealth >= 0) ? health = newHealth : health = 0;
	}
	void setPos(sf::Vector2f newPos) {
		this->mPos = newPos;
	}
protected:
	int health;
	sf::Vector2f mPos;
	sf::Sprite mSprite;
	sf::Texture mSpriteTexture;
};



////////PUBLIC VIRTUAL MEMBER FUNCTIONS BELOW////////

 /*************************************************************
 * Function: render()
 * Date Created: 4/21/21
 * Date Last Modified: 4/21/21
 * Description: Renders the sprite to the target.
 * Input parameters: target - The pointer to the target where the sprite will be drawn.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The sprite is rendered to the target.
 *************************************************************/
void Character::render(sf::RenderTarget* target) {
	target->draw(this->mSprite);
}