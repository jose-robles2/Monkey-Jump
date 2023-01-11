/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: Class definition for the redWeakest class.
 ******************************************************************************/
#pragma once 
#include "game.h"
#include "Character.h"
#include <SFML/Graphics.hpp>

class redWeakest : public Character
{
public:
	redWeakest() {
		setSpeed(1.f);
		setPos(sf::Vector2f(rand() % 1500 + 400, 725.f));
		this->health = 1; 
		this->isDeletedByDart = false; 
		this->deleteBalloon = false;
		initTexture();
		initSprite();
	}

	~redWeakest()
	{}

	////////PUBLIC MEMBER FUNCTIONS BELOW////////
	void resetVelocityY();
	void moveWithPhys(const float dirX, const float dirY);
	void updatePhysics();

	void subHealth() {
		this->health--;
	}


	////////GETTERS BELOW////////
	float getSpeed() {
		return speed;
	}
	int getHealth() {
		return  health; 
	}
	bool timeToDelete() const { 
		return deleteBalloon; 
	}

	////////SETTERS BELOW////////
	void setSpeed(float newSpeed) {
		speed = newSpeed;
	}
	void setHealth(int newHealth) {
		health = newHealth;
	}
	void setPopSpritePos(const sf::Vector2f &pos) {
		popSprite.setPosition(pos.x, pos.y);
	}

	//Public Variables
	bool isDeletedByDart;
	void renderBalloonPop(sf::RenderTarget* target);
	void updateSpot(sf::RenderTarget* target);
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
private:
	void initTexture();
	void initSprite();
	float speed;
	bool deleteBalloon;

	sf::Texture popTexture; 
	sf::Sprite popSprite; 
};


////////Public Member functions below////////

 /*************************************************************
 * Function: renderBalloonPop()
 * Date Created: 4/22/21
 * Date Last Modified: 4/23/21
 * Description: Renders the balloon pop sprite to the target.
 * Input parameters: target - The pointer to the target which the balloon will be rendered.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The pop sprite is render to the target.
 *************************************************************/
void redWeakest::renderBalloonPop(sf::RenderTarget* target) {
	target->draw(this->popSprite);
}

////////Private Member functions below////////

 /*************************************************************
 * Function: initSprite()
 * Date Created: 4/21/21
 * Date Last Modified: 4/23/21
 * Description: Initializes the sprite and pop sprite of the balloon object.
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The sprites of redWeakest are initialized.
 *************************************************************/
void redWeakest::initSprite()
{
	this->mSprite.setTexture(this->mSpriteTexture);

	//Resize the sprite
	this->mSprite.setPosition(this->getPos());
	this->mSprite.scale(0.1f, 0.1f);

	this->popSprite.setTexture(this->popTexture);
	this->popSprite.setPosition(this->getPos()); // Set the position to the monkey position later
	this->popSprite.scale(0.1f , 0.1f); 
}

 /*************************************************************
 * Function: initTexture()
 * Date Created: 4/21/21
 * Date Last Modified: 4/23/21
 * Description: Initializes the textures of the sprites of redWeakest. If they
				could not be initialized, a message is printed to the console.
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The textures of the sprites are initialized or a error
					message is printed to the console.
 *************************************************************/
void redWeakest::initTexture()
{
	//Load a texture from file
	if (!this->mSpriteTexture.loadFromFile("Textures/Redballoon.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	if (!this->popTexture.loadFromFile("Textures/balloonPop.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
}