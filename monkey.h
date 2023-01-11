/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: Class definition for the Monkey class.
 ******************************************************************************/
#pragma once

#include "Character.h"
#include "game.h"



class Monkey : public Character {
public: 

	Monkey() : Character()
	{
		this->initVariables();
		this->initTexture();
		this->initSprite();
		this->initPhysics(); 
		this->initHitMarker();
	}

	//Getters
	float  getSpeed() const {
		return movementSpeed;
	}
	int getHealth() const {
		return this->health;
	}
	bool timeToRenderNewLandscape() const { 
		return this->renderNewLandscape; 
	}
	sf::Sprite& getMonkeySprite() {
		return MonkeySprite;
	}
	sf::Sprite& getDartSprite() {
		return dartSprite;
	}
	sf::Sprite& getHitMarkerSprite() {
		return this->hitMarkerSprite; 
	}

	//Setters
	void setSpeed(float NewSpeed) {
		movementSpeed = NewSpeed;
	}
	void subHealth() {
		health--;
	}
	void setRenderLandscape(const bool newLandscape) {
		this->renderNewLandscape = newLandscape;
	}
	void setMonkeySprite(sf::Sprite newSprite) {
		this->MonkeySprite = newSprite; 
	}


	//Physics
	void resetVelocityY(); 
	void moveWithPhys(const float dirX, const float dirY);
	void updatePhysics(); 

	//Updates
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void updateInput(sf::RenderWindow* target);
	void update(sf::RenderWindow* target);
	void render(sf::RenderTarget* target);
	void renderHitMarker(sf::RenderTarget* target);
	

	int levelTracker; 
	bool touchingLandscape; 
	bool touchingTileGround; 
	bool didWeJump; 
	bool throwDart;
	bool firstDartThrow; 
	bool throwTillEdge;
	bool spaceBarHeld; 
	bool leftMouseHeld; 
	bool renderNewLandscape;
	bool didWeTouchBloon; 
	bool initDartMarker;


protected:
	sf::Sprite MonkeySprite;
	sf::Sprite dartSprite;
	sf::Sprite hitMarkerSprite;
	sf::Texture dartTexture; 
	sf::Texture texture;
	sf::Texture HitMarkertexture;

	//Physics
	float movementSpeed;
	sf::Vector2f velocity; 
	float velocityMax;
	float velocityMaxYDir;
	float velocityMin; 
	float acceleration; 
	float drag; 
	float gravity;

	//Functions
	void initVariables();
	void initSprite();
	void initHitMarker();
	void initDart();
	void initTexture();
	void initPhysics(); 	
};

////////PUBLIC MEMBER FUNCTIONS BELOW////////

 /*************************************************************
 * Function: resetVelocityY()
 * Date Created: 4/22/21
 * Date Last Modified: 4/22/2021
 * Description: Resets the y velocity of the monkey
 * Input parameters: void 
 * Returns: void 
 * Preconditions: Monkey must be on the floor 
 * Postconditions: The monkey's y velocity will be zero 
 *************************************************************/
void Monkey::resetVelocityY()
{
	this->velocity.y; 
}

/*************************************************************
* Function: moveWithPhys()
* Date Created: 4/22/21
* Date Last Modified: 4/24/2021
* Description: This function adds physics to the monkey's x direction
*			   movement. CREDIT: I got this code from youtuber Suraj Sharma. 
*			   We were struggling how to make a jump feature and came across Suraj's 
*			   sfml videos and he used this function in order to get smooth movement 
*				
* Input parameters: const float dirX, const float dirY
* Returns: void
* Preconditions: The update() function in game.h must be executing
* Postconditions: The monkey's x velocity will be higher or lower 
*************************************************************/
void Monkey::moveWithPhys(const float dirX, const float dirY)
{
	this->velocity.x += dirX * this->acceleration; 	// x Acceleration
}

/*************************************************************
 * Function: updatePhysics()
 * Date Created: 4/22/21
 * Date Last Modified: 4/24/21
 * Description: This function also came from Suraj Sharma's sfml 
 *				video on how to make smooth movement. This function 
 *				multiplies the monkey's velocity vector with different 
 *				things in order to acheive acceleration, deceleration, 
 *				as well as gravity. 
 * Input parameters: void 
 * Returns: void 
 * Preconditions: The update() function in game.h must be executing
 * Postconditions: The monkey's velocity will be smooth in all directions 
 *************************************************************/
void Monkey::updatePhysics()
{
	this->velocity.y += 1.0 * this->gravity; 	//Gravity

	if (std::abs(this->velocity.x) > this->velocityMax)
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);     //For x directions
	
	if (std::abs(this->velocity.y) > this->velocityMaxYDir)		
		this->velocity.y = this->velocityMaxYDir * ((this->velocity.y < 0.f) ? -1.f : 1.f); //For gravity 
	
	this->velocity *= this->drag; 	//Deceleration

	//Limit deceleration 
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->MonkeySprite.move(this->velocity.x , this->velocity.y); //Move the sprite with velocity --> velocity is a vector2f
}

/*************************************************************
 * Function: updateInput()
 * Date Created: 4/20/21
 * Date Last Modified: 4/26/21
 * Description: This function checks for all the actions from the user 
 *				which will then be applied to the monkey. It checks for 
 *				left and right movement, jump, as well as the dart throw. 
 * Input parameters: sf::RenderWindow* target
 * Returns: void 
 * Preconditions: The monkey must be instantiated in game 
 * Postconditions: Will allow the monkey to do things in the game such
 *				   as movement and attack
 *************************************************************/
void Monkey::updateInput(sf::RenderWindow* target)
{
	if (!didWeTouchBloon) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	  //left movement
			this->moveWithPhys(-this->movementSpeed, 0.f);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //right movement
			this->moveWithPhys(this->movementSpeed, 0.f);
	}

	//Jump if touching the ground 
	if (this->touchingLandscape == true || this->touchingTileGround == true)
 	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  //Jump movement
		{
			if (this->spaceBarHeld == false) {
				this->touchingLandscape = false; 
				this->touchingTileGround = false;
				this->spaceBarHeld = true;
				this->didWeJump = true;

												   //jump height
				velocity.y = -sqrtf(1.9f* 981.0f * 7.5f);				//CREDIT: When first creating the jump function we only made the monkey teleport. We decided to make a smooth jump by adding gravity, which allowed the monkey
																		//to smoothly fall down, but the jump up was not smooth yet. When researching ways to make a fully smooth jump, we encountered this equation online and when we 
																		//we implemented it, the monkey smoothly jumped!!
			}
		}
		else { //space bar not pressed
			this->didWeJump = false;
			this->spaceBarHeld = false;
		}
	}

	//Darts can only be thrown if the left mouse button is being held 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{	
		if (this->leftMouseHeld == true) { 
			if (!this->initDartMarker) {
				initDart();
				this->initDartMarker = true;
			}
			this->leftMouseHeld = false;
			this->throwDart = true;
			this->dartSprite.move(35.f, 0.f);					
		}
		else 
			this->leftMouseHeld = true; 
	}
	else {
		this->firstDartThrow = false;
		this->throwDart = false;
		this->dartSprite.setPosition(MonkeySprite.getPosition().x, MonkeySprite.getPosition().y);
	}
}

/*************************************************************
 * Function: updateWindowBoundsCollision()
 * Date Created: 4/20/21
 * Date Last Modified: 4/21/21
 * Description: We came up with this function by watching Suraj Sharma's 
 *				very helpful sfml videos. This function check for the position 
 *				of the monkey. It then compares that position with the borders of the windows
 *				and the landscape. If the monkey exceeds these boundaries, then we move the monkey
 *				back onto the screen. If the monkey goes to the right boundary, then it will set 
 *				a bool variable to true, which will then allow the program to render the next level 
 *				It also checks the boundaries for the dart and brings it back to the monkey if it goes
 *				out of bounds 
 * Input parameters: const sf::RenderTarget* target
 * Returns: void 
 * Preconditions: Monkey must be instantiated 
 * Postconditions: It will not allow the monkey to go offscreen 
 *************************************************************/
void Monkey::updateWindowBoundsCollision(const sf::RenderTarget* target) {
	// Left
	if (this->MonkeySprite.getGlobalBounds().left <= 0.f)
		this->MonkeySprite.setPosition(0.f, this->MonkeySprite.getGlobalBounds().top);
	// Right
	else if (this->MonkeySprite.getGlobalBounds().left + this->MonkeySprite.getGlobalBounds().width >= target->getSize().x) {
			this->renderNewLandscape = true;
	}

	// Top
	if (this->MonkeySprite.getGlobalBounds().top <= 0.f)
		this->MonkeySprite.setPosition(this->MonkeySprite.getGlobalBounds().left, 0.f);
	// Bottom
	else if (this->MonkeySprite.getGlobalBounds().top + this->MonkeySprite.getGlobalBounds().height >= 800.f) {				//		WE MIGHT NEED AN OR STATEMENT HERE FOR THE FINAL LANDSCAPE GROUND 
		this->touchingLandscape = true; 
		this->resetVelocityY(); 
		this->MonkeySprite.setPosition(this->MonkeySprite.getGlobalBounds().left, 820.f - this->MonkeySprite.getGlobalBounds().height);
	}


	sf::FloatRect dartBounds = this->dartSprite.getGlobalBounds();	//Check dart boundaries

	if (firstDartThrow == false) {
		firstDartThrow = true;
		this->dartSprite.setPosition(sf::Vector2f(this->MonkeySprite.getPosition().x, this->MonkeySprite.getPosition().y + 50));
	}
	else if (dartBounds.left + dartBounds.width >= target->getSize().x) {//check if it goes out of the screen 
		//set it back to the players positons
		this->dartSprite.setPosition(sf::Vector2f(this->MonkeySprite.getPosition().x, this->MonkeySprite.getPosition().y + 50));
	}
}

/*************************************************************
 * Function: update()
 * Date Created: 4/20/21
 * Date Last Modified: 4/22/21
 * Description: This is the main update function for monkey. It calls 
 *				all the other update functions that are associated with 
 *				the monkey. 
 * Input parameters: sf::RenderWindow * target
 * Returns: void 
 * Preconditions: The update() function in main must be executing 
 * Postconditions: Will allow the monkey to move on the screen 
 *************************************************************/
void Monkey::update(sf::RenderWindow* target)
{
	this->updateInput(target); 					//check for keyboard input 
	this->updatePhysics();						//update physics                            
	this->updateWindowBoundsCollision(target);	//check for collisions as we update the character 
}

/*************************************************************
 * Function: render()
 * Date Created: 4/20/21 
 * Date Last Modified: 4/23/21
 * Description: This function renders the monkey, and render the dart 
 *				if it has been thrown 
 * Input parameters: sf::RenderTarget* target
 * Returns: void 
 * Preconditions: The render() function in main must be executing 
 * Postconditions: Will show the changes to the monkey on the screen 
 *************************************************************/
void Monkey::render(sf::RenderTarget* target)
{
	if (throwDart) 
		target->draw(this->dartSprite);
	target->draw(this->MonkeySprite);
}

/*************************************************************
 * Function: renderHitMarker() 
 * Date Created: 4/23/21
 * Date Last Modified: 4/24/21
 * Description: This function renders the hit marker on the monkey 
 * Input parameters: sf::RenderTarget* target
 * Returns: void
 * Preconditions: If the monkey has been hit by a balloon, then render
 *				  a hitmarker on the monkey to indicate that damage has been taken 
 * Postconditions: Will show a hitmarker on the monkey on the screen 
 *************************************************************/
void Monkey::renderHitMarker(sf::RenderTarget* target){
   target->draw(this->hitMarkerSprite);
}

////////PRIVATE MEMBER FUNCTIONS BELOW////////

/*************************************************************
 * Function: initVariables()
 * Date Created: 4/21/21
 * Date Last Modified: 4/26/21
 * Description: This function initializes all the variables associated 
 *				with the monkey 
 * Input parameters: void 
 * Returns: void 
 * Preconditions: If a monkey is instantiated, this is called from the constructor
 * Postconditions: Will initialize al of monkey's variables
 *************************************************************/
void Monkey::initVariables()
{	
	this->touchingTileGround = false; 
	this->didWeTouchBloon = false;
	this->initDartMarker = false;
	this->health = 50;						//TESTING
	this->movementSpeed = 15.f;
	this->firstDartThrow = false; 
	this->spaceBarHeld = false;
	this->leftMouseHeld = true; 
	this->renderNewLandscape = false;
}

/*************************************************************
 * Function: initSprite()
 * Date Created: 4/21/21
 * Date Last Modified: 4/22/21
 * Description: This function initializes our transparent png file 
 *				to our player 
 * Input parameters: void 
 * Returns: void 
 * Preconditions: Monkey must be instatiated
 * Postconditions: Allows for the window to display a monkey player 
 *************************************************************/
void Monkey::initSprite()
{
    this->MonkeySprite.setPosition(sf::Vector2f(0.f, 670.f));		
	this->MonkeySprite.setTexture(this->texture);
	this->MonkeySprite.scale(0.5f, 0.5f);
}

/*************************************************************
 * Function: initHitMarker()
 * Date Created: 4/23/21
 * Date Last Modified: 4/24/21
 * Description: This function initializes the sprite with the hit
 *				marker texture that we loaded from a file 
 * Input parameters: void 
 * Returns: void 
 * Preconditions: Monkey must be instantiated
 * Postconditions: Allows for the monkey sprite to be set to our monkey
 *				   png
 *************************************************************/
void Monkey::initHitMarker(){
    this->hitMarkerSprite.setTexture(this->HitMarkertexture);
	this->hitMarkerSprite.scale(0.5f, 0.5f);
}

/*************************************************************
 * Function: initDart()
 * Date Created: 4/22/21
 * Date Last Modified: 4/24/21
 * Description: This function initializes our dart sprite with a texture
 * Input parameters: void 
 * Returns: void 
 * Preconditions: When the monkey throws its first dart, the dart will be initialized
 *				  so that the first dart throw can start from the monkey's current position 
 * Postconditions: Will allow for a dart to be shown on the screen 
 *************************************************************/
void Monkey::initDart()
{
    this->dartSprite.setPosition(sf::Vector2f(this->MonkeySprite.getPosition().x, this->MonkeySprite.getPosition().y + 50)); //set the position of the dart to wherever the monkey currently is 
	this->dartSprite.setTexture(this->dartTexture);	//Set the texture to the sprite
	this->dartSprite.scale(0.1f, 0.1f);
}

/*************************************************************
 * Function: initTexture()
 * Date Created: 4/20/21
 * Date Last Modified: 4/25/21
 * Description: This function grabs png files from the main folder that 
 *				this project is in and assigns them to our texture vars
 * Input parameters: void 
 * Returns: void 
 * Preconditions: Monkey must be instantiated 
 * Postconditions: Will allow all sprites relating to the monkey to 
 *				   be shown on the screen with actual textures 
 *************************************************************/
void Monkey::initTexture()
{
	//init monkey texture 
	if (!this->texture.loadFromFile("Textures/RestMonke.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	//init dart texture
	if (!this->dartTexture.loadFromFile("Textures/dart.png"))
		std::cout << "ERROR::PLAYER::DARTTEXTURE::Could not load texture file." << "\n";
	//init hitmarker texture
	if (!this->HitMarkertexture.loadFromFile("Textures/hitmarker.png"))
		std::cout << "ERROR::PLAYER::HITMARKER::Could not load texture file." << "\n";
}

/*************************************************************
 * Function: initPhysics() 
 * Date Created: 4/23/21
 * Date Last Modified: 4/21/21
 * Description: This function initializes all of the physics 
 *				variables associated with the monkey 
 * Input parameters: void 
 * Returns: void 
 * Preconditions: Monkey must be instantiated 
 * Postconditions: Will have initialized all the physics vars relating to the monkey 
 *************************************************************/
void Monkey::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 5.f;
	this->drag = 0.8f;
	this->gravity = 4.f;
	this->velocityMaxYDir = 1500.f;
}