/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: 
 ******************************************************************************/
#pragma once
#include "character.h"
#include <SFML/Graphics.hpp>

class FinalBoss : public Character {
public:
	FinalBoss() {
		initVariables();
		initTexture();
		initSprite();
		initPhysics(); 
	}

	//Public member functions

	//Updates
	void updatePhysics(); 
	void updateHealthBar();
	void updateWindowsBoundCollisions(sf::RenderTarget* target);
	void moveUp();
	void moveDown(); 
	void resetVelocityY();


	//Renders
	void render(sf::RenderTarget* target);
	void renderExplosion(sf::RenderTarget* target);

	void subHealth() {
		health--;
	}

	// Getters
	sf::Sprite& getExplosionSprite() { 
		return explosion; 
	}

private:
	double maxHealth;
	int currentHealth;
	int maxHealthBarWidth;

	void initTexture();
	void initSprite();
	void initVariables();
	void initPhysics(); 

	sf::Texture popTexture; 
	sf::Sprite popSprite;
	sf::RectangleShape healthBar;


	sf::Texture landScapeGroundTexture; 
	sf::Sprite landScapeGround;
	sf::Sprite background;
	sf::Texture backgroundTexture; 
	sf::Sprite explosion;
	sf::Texture explosionTexture;

	//Physics
	float movementSpeed;
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMaxYDir;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;

};          


////////PUBLIC MEMBER FUNCTIONS BELOW////////
/*************************************************************
 * Function: resetVelocityY()
 * Date Created: 4/27/21
 * Date Last Modified: 4/28/2021
 * Description: Resets the y velocity of the boss
 * Input parameters: void
 * Returns: void
 * Preconditions: We must be on the final level and blimp must be on floor 
 * Postconditions: The Boss's y velocity will be zero
 *************************************************************/
void FinalBoss::resetVelocityY()
{
	this->velocity.y;
}

/*************************************************************
 * Function: updatePhysics()
 * Date Created: 4/27/21
 * Date Last Modified: 4/28/21
 * Description: This function also came from Suraj Sharma's sfml
 *				video on how to make smooth movement. This function
 *				multiplies the boss's velocity vector with different
 *				things in order to acheive acceleration, deceleration,
 *				as well as gravity.
 * Input parameters: void
 * Returns: void
 * Preconditions: We must be on the final level 
 * Postconditions: The Boss's velocity will be smooth in all directions
 *************************************************************/
void FinalBoss::updatePhysics() {
	this->velocity.y += 1.0 * this->gravity; //Gravity

	if (std::abs(this->velocity.x) > this->velocityMax)
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);     //For x directions
	if (std::abs(this->velocity.y) > this->velocityMaxYDir)
		this->velocity.y = this->velocityMaxYDir * ((this->velocity.y < 0.f) ? -1.f : 1.f); //For gravity 
	
	this->velocity *= this->drag;  //Deceleration

	//Limit deceleration 
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->mSprite.move(this->velocity.x, this->velocity.y); //Move the sprite with velocity --> velocity is a vector2f
}

 void FinalBoss::render(sf::RenderTarget* target) {
	target->draw(this->mSprite);
	target->draw(this->healthBar);
}

void FinalBoss::renderExplosion(sf::RenderTarget* target) {
	explosion.setPosition (mSprite.getPosition());
	target->draw(explosion);
}
 /*************************************************************
 * Function: updateHealthBar()
 * Date Created: 4/28/2021
 * Date Last Modified: 4/28/2021
 * Description: Shrink the healthbar by a percent of the max health
 * Input parameters: None
 * Returns: None
 * Preconditions: If the boss is hit, then update its health bar
 * Postconditions: Will allow the health bar to shrink with each hit 
 *************************************************************/
void FinalBoss::updateHealthBar(){
	healthBar.setSize(sf::Vector2f(static_cast<float> ((health / maxHealth) * 960), 30));
}
 /*************************************************************
 * Function: updateWindowsBoundCollisions(target)
 * Date Created: 4/28/2021
 * Date Last Modified: 4/29/2021
 * Description: Keeps the user from going outside the left and top edges of the window.
 * Input parameters: RenderTarget pointer
 * Returns: None
 * Preconditions: We must be on the final level
 * Postconditions: Won't allow the boss to leave the top or bottom of the window
 *				   The boss only moves up and down so left and right do not need to be checked
 *************************************************************/
void FinalBoss::updateWindowsBoundCollisions(sf::RenderTarget* target)
{
	// Top
	if (this->mSprite.getGlobalBounds().top <= 0.f)
		this->mSprite.setPosition(this->mSprite.getGlobalBounds().left, 0.f);
	// Bottom
	else if (this->mSprite.getGlobalBounds().top + this->mSprite.getGlobalBounds().height >= 800.f) {				//		WE MIGHT NEED AN OR STATEMENT HERE FOR THE FINAL LANDSCAPE GROUND 
		this->resetVelocityY();
		this->mSprite.setPosition(this->mSprite.getGlobalBounds().left, 820.f - this->mSprite.getGlobalBounds().height);
	}
}
 /*************************************************************
 * Function: moveUp()
 * Date Created: 4/28/2021
 * Date Last Modified: 4/28/2021
 * Description: Causes the final boss to rise in the air
 * Input parameters: None
 * Returns: None
 * Preconditions: We must be on the final level. If the boss is on the 
 *				  ground then it is time to move up
 * Postconditions: Will smoothly move the boss upwards until a limit is reached
 *************************************************************/
void FinalBoss::moveUp()
{
	velocity.y = -sqrtf(0.1f * 981.0f * 0.5f); // Bring the blimp up 
}
 /*************************************************************
 * Function: moveDown()
 * Date Created: 4/28/2021
 * Date Last Modified: 4/28/2021
 * Description: Moves the final boss down in a visually aethetic way
 * Input parameters: None
 * Returns: None
 * Preconditions: We must be on the final level. If the boss has reached the upper 
 *			      limit then it is time to smoothly move the boss down until the floor 
 *				  is reached
 * Postconditions: Will smoothly move the boss downwards using gravity until floor is hit 
 *************************************************************/
void FinalBoss::moveDown()
{
	this->updatePhysics(); //Bring the blimp down 
}


////////PRIVATE MEMBER FUNCTIONS BELOW////////
 /*************************************************************
 * Function: initTexture()
 * Date Created: 4/28/2021
 * Date Last Modified: 4/29/2021
 * Description: Initializes the final boss texture along with an explosion and pop textures for when the balloons and blimps are hit
				If the png files are not found, then an error message is printed to the console.
 * Input parameters: None
 * Returns: None
 * Preconditions: finalBoss object is created
 * Postconditions: Textures are pulled from a file or else an error message is printed.
 *************************************************************/
void FinalBoss::initTexture()
{
	//Load a texture from file
	if (!this->mSpriteTexture.loadFromFile("Textures/blimp.png"))
		std::cout << "ERROR::FINALBOSS::INITTEXTURE::Could not load blimp texture file." << "\n";
	if (!this->popTexture.loadFromFile("Textures/balloonPop.png"))
		std::cout << "ERROR::FINALBOSS::INITTEXTURE::Could not load blimp balloon pop texture file." << "\n";
	if (!this->explosionTexture.loadFromFile("Textures/explosion.png")) {
		std::cout << "ERROR::FINALBOSS::INITTEXTURE:: Could not load explosion texture file." << "\n";
	}
}
 /*************************************************************
 * Function: initSprite()
 * Date Created: 4/28/2021
 * Date Last Modified: 4/29/2021
 * Description:Sets sprites based on previously loaded texturesand positions and scales them towards the right of the screen
 * Input parameters: None
 * Returns: None
 * Preconditions: The finalBoss object is made
 * Postconditions: The sprites at set up to be called and used elsewhere
 *************************************************************/
void FinalBoss::initSprite()
{
	this->mSprite.setTexture(this->mSpriteTexture);

	//Resize the sprite
	this->mSprite.setPosition(sf::Vector2f(1000, 450));
	this->mSprite.scale(2.0f, 2.0f);

	this->popSprite.setTexture(this->popTexture);
	this->popSprite.setPosition(this->getPos()); // Set the position to the monkey position later
	this->popSprite.scale(0.1f , 0.1f); 

	this->explosion.setTexture(explosionTexture);
	this->explosion.setPosition(mSprite.getPosition());
}
 /*************************************************************
 * Function: initPhysics()
 * Date Created: 4/28/2021
 * Date Last Modified: 4/28/2021
 * Description: Initializes the physics variables used to make aesthetically pleasing movements
 * Input parameters: None
 * Returns: None
 * Preconditions: finalBoss object has been created
 * Postconditions: Variables required for updating and
					using physics are initialized
 *************************************************************/
void FinalBoss::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 5.f;
	this->drag = 0.8f;
	this->gravity = 1.8f;
	this->velocityMaxYDir = 1500.f;
}
 /*************************************************************
 * Function: initVariables()
 * Date Created: 4/28/2021
 * Date Last Modified: 4/28/2021
 * Description: Initializes the max health of the boss and sets the position of
				the health bar along with making the health bar filled red
 * Input parameters: None
 * Returns: None
 * Preconditions: A finalBoss object is created
 * Postconditions: maxHealth and position and fill color variables are initialized
 *************************************************************/
void FinalBoss::initVariables() {

	this->maxHealth = health = 26;
	healthBar.setPosition(sf::Vector2f(480, 80));
	healthBar.setFillColor(sf::Color::Red);
}