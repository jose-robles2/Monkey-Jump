/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: This is the foundation for the game for this project. This game class
 *				houses all the necessary components in order to run the game properly 
 *
 *				The formatting of this class also came from Suraj Sharma's sfml game tutorials. 
 *				The entire group watched his sfml tutorials about a week before pa9 was assigned and it was a huge help. 
 ******************************************************************************/
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <time.h>
#include "Brick.h"
#include <sstream>
using std::cout;
using std::endl;


#include <SFML/Graphics.hpp>
#include "monkey.h"
#include "finalBoss.h"
#include "blueMed.h"
#include "greenStrong.h"
#define FINAL_LEVEL 5

class Game
{
public:
	//Default Constructor
	Game()
	{
		srand(time(NULL));
		this->initVariables();
		this->initWindow();
		this->initLandScape();
		this->initFont(); 
		this->initText(); 
	}

    //  destructor
	virtual ~Game()
	{
		delete this->window; 
		delete this->tempMonkey; 
		delete this->block;
		delete this->block2;
	}

	//Member functions
	void pollEvents();
	void CheckBalloonCollision(redWeakest *balloonPtr); 
	void CheckBossCollision();		
	virtual void update();
	virtual void updateGameText(); 
	virtual void render();
	void renderGrave(sf::RenderTarget* target);
	virtual void renderLandScape();
	void renderFinalLandscape();
	void renderUiText(sf::RenderTarget* target);
	void runGame();

	//Getter
	const bool getWindowIsOpen() const {
		return this->window->isOpen();
	}

protected:

	//Variables
	bool isRedDelete, isBlueDelete, isGreenDelete; 
	bool monkeyDeath, blimpDeath, isBlimpTouchingGround; 
	int landscapeNum, spawnTimer, spawnTimerMax; 


	//Private functions
	void initVariables();
	void initWindow();
	void initLandScape();
	void initOtherTextures(); 
	void initFont(); 
	void initText(); 
	void deleteBalloon(redWeakest* balloonPtr);
	void generateBalloons(int numBalloonsOfEachType);

	//Private variables
	sf::RenderWindow* window; 
	sf::VideoMode videoMode;
	sf::Event eventVar;	

	std::vector<redWeakest*> bloons;


	//Game objects
	sf::Sprite landScapeGround, landscape, finalLandscape, finalLandscapeGround;
	sf::Texture landscapeTexture, landscapeTexture2, finalLandscapeTexture, finalLandscapeGroundTexture;
	Monkey *tempMonkey;
	Tile* block; 
	Tile* block2;
	FinalBoss *finalBoss;

	//Text vars
	sf::Font font; 
	sf::Text uiText;
};


////////Public Member functions below////////

/*************************************************************
 * Function: pollEvents()
 * Date Created: 4/20/21
 * Date Last Modified: 4/20/21
 * Description: Checks if the user click the exit button or the escape key.
				If they did, the display window is closed.
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: If the exit button or the escape key is pressed, the window is closed.
 *************************************************************/
void Game::pollEvents()
{
	while (this->window->pollEvent(this->eventVar)) //If the window detects a pollEvent then save it to the eventVar --> ev
	{
		switch (this->eventVar.type) //there's diff types of events to detect
		{
		case sf::Event::Closed: //If the x button is pressed in the form

			this->window->close(); //Close the window
			break;

		case sf::Event::KeyPressed: //If any key is pressed:

			if (this->eventVar.key.code == sf::Keyboard::Escape) //if esc key is pressed
				this->window->close();
			break;
		}
	}
}

/*************************************************************
 * Function: CheckBossCollision()
 * Date Created: 4/28/21
 * Date Last Modified: 4/29/21  
 * Description: This function checks for collision for the boss. 
 *				It will check if the monkey runs into the boss
 *				(subtracts its health) and then checks if the 
 *				monkey's dart hits the final boss (subtracts health) 
 * Input parameters: void 
 * Returns: void 
 * Preconditions: The monkey must be in the final level 
 * Postconditions: Will allow for the monkey to run into and throw
 * dart at the final boss 
 *************************************************************/
void Game::CheckBossCollision(/*FinalBoss* boss*/)
{
	if (tempMonkey->leftMouseHeld == true) {		//check if the dart is hitting a balloon  

		if (this->tempMonkey->getDartSprite().getGlobalBounds().intersects(finalBoss->getSprite().getGlobalBounds()))
		{
			if (finalBoss->getHealth() > 0)
			{
				finalBoss->subHealth(); //this function subtracts the health of a balloon by 1
				window->display();
				std::chrono::milliseconds timespan(10);
				std::this_thread::sleep_for(timespan);
				this->tempMonkey->getDartSprite().setPosition(sf::Vector2f(2000.f, 0.f));
			}
		}
		
	}
	if (this->tempMonkey->getMonkeySprite().getGlobalBounds().intersects(finalBoss->getSprite().getGlobalBounds()) && finalBoss->getHealth() > 0)
	{
		tempMonkey->didWeTouchBloon = true;
		if (tempMonkey->getHealth() > 0) { //decrement the health of the monkey d
			tempMonkey->subHealth();

			if (tempMonkey->getMonkeySprite().getPosition().x < finalBoss->getSprite().getPosition().x) { //the monkey touches the balloon from the left
				tempMonkey->moveWithPhys(-5.f, 0.f);
				this->tempMonkey->getHitMarkerSprite().setPosition(sf::Vector2f(this->tempMonkey->getMonkeySprite().getPosition().x + 70, this->tempMonkey->getMonkeySprite().getPosition().y - 25));
				tempMonkey->renderHitMarker(this->window);
				tempMonkey->render(this->window);
				this->window->display();
			}

			else if (tempMonkey->getMonkeySprite().getPosition().x > finalBoss->getSprite().getPosition().x) { //the monkey touches the balloon from the right
				tempMonkey->moveWithPhys(5.f, 0.f);
				this->tempMonkey->getHitMarkerSprite().setPosition(sf::Vector2f(this->tempMonkey->getMonkeySprite().getPosition().x + 70, this->tempMonkey->getMonkeySprite().getPosition().y - 25));
				tempMonkey->renderHitMarker(this->window);
				tempMonkey->render(this->window);
				this->window->display();
			}

			window->display();
			if (tempMonkey->getHealth() == 0) //the monkey has lost all its health 
				monkeyDeath = true;
		}
	} else
		tempMonkey->didWeTouchBloon = false;
}

/*************************************************************
 * Function: CheckBalloonCollision()
 * Date Created: 4/22/21
 * Date Last Modified: 4/24/21
 * Description: This function does checks for collisions between a monkey
 *				and a balloon. If a monkey runs into a balloon then it will 
 *				lose health. If the monkey throws a dart at the balloon then 
 *				the balloon will lose health as well. 
 *				This function utilizes polymorphism since we pass in a general 
 *				red balloon type and it checks for collisions for all the balloon
 *				types
 * Input parameters: redWeakest* balloonPtr
 * Returns: void 
 * Preconditions: If a level is rendered, then check for balloon collisions since
 *				  each level contains balloons
 * Postconditions: Will allow the monkey and balloon to have collisions
 *************************************************************/
void Game:: CheckBalloonCollision(redWeakest* balloonPtr)
{
	if (tempMonkey->leftMouseHeld == true) {		//check if the dart is hitting a balloon  

		if (this->tempMonkey->getDartSprite().getGlobalBounds().intersects(balloonPtr->getSprite().getGlobalBounds()))
		{
			if (balloonPtr->getHealth() > 0)
			{
				balloonPtr->subHealth(); //this function subtracts the health of a balloon by 1
				balloonPtr->setPopSpritePos(sf::Vector2f(balloonPtr->getSprite().getPosition().x - 16, balloonPtr->getSprite().getPosition().y));
				balloonPtr->renderBalloonPop(this->window);
				window->display();
				std::chrono::milliseconds timespan(10);
				std::this_thread::sleep_for(timespan);
				this->tempMonkey->getDartSprite().setPosition(sf::Vector2f(2000.f, 0.f));

				if (balloonPtr->getHealth() == 0)
					deleteBalloon(balloonPtr);
			}
		}
	}
	else
		tempMonkey->leftMouseHeld = false; //THIS IS A TEST 


	//if the monkey runs into a balloon, decrement the monkey health 
	if (this->tempMonkey->getMonkeySprite().getGlobalBounds().intersects(balloonPtr->getSprite().getGlobalBounds()))
	{
		tempMonkey->didWeTouchBloon = true;

		if (tempMonkey->getHealth() > 0) { //decrement the health of the monkey 
			tempMonkey->subHealth();

			if (tempMonkey->getMonkeySprite().getPosition().x < balloonPtr->getSprite().getPosition().x) { //the monkey touches the balloon from the left
				tempMonkey->moveWithPhys(-5.f, 0.f);
				this->tempMonkey->getHitMarkerSprite().setPosition(sf::Vector2f(this->tempMonkey->getMonkeySprite().getPosition().x + 70, this->tempMonkey->getMonkeySprite().getPosition().y - 25));
				tempMonkey->renderHitMarker(this->window);
				tempMonkey->render(this->window);
				this->window->display();
			}

			else if (tempMonkey->getMonkeySprite().getPosition().x > balloonPtr->getSprite().getPosition().x) { //the monkey touches the balloon from the right
				tempMonkey->moveWithPhys(5.f, 0.f);
				this->tempMonkey->getHitMarkerSprite().setPosition(sf::Vector2f(this->tempMonkey->getMonkeySprite().getPosition().x + 70, this->tempMonkey->getMonkeySprite().getPosition().y - 25));
				tempMonkey->renderHitMarker(this->window);
				tempMonkey->render(this->window);
				this->window->display();
			}

			window->display();
			if (tempMonkey->getHealth() == 0) //the monkey has lost all its health 
				monkeyDeath = true;
		}
	}
	else
		tempMonkey->didWeTouchBloon = false; 
}

/*************************************************************
 * Function: update()
 * Date Created: 4/20/21
 * Date Last Modified: 4/28/21
 * Description: Updates the display window of the game.
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The game window is updated to reflect any events in the game.
 *************************************************************/ 
void Game::update()
{	
	if (this->landscapeNum > FINAL_LEVEL)
		this->window->close(); 
	 
	this->pollEvents(); //Detect Actions toward the game window 
	this->tempMonkey->update(this->window); //update our hero 
	this->block->updateCollisions(this->tempMonkey); //check for collisions with the bricks  

	if (landscapeNum > 1)
		this->block2->updateCollisions(tempMonkey);

	if (landscapeNum == FINAL_LEVEL) {

		block->SetTilePosition(/*Small*/ sf::Vector2f(150.f, 500.f), /*Long*/sf::Vector2f(20000.f, 20000.f));

		block2->SetTilePosition(/*Small*/ sf::Vector2f(400.f, 500.f), /*Long*/sf::Vector2f(20000.f, 20000.f));


		this->CheckBossCollision();

		if (!this->blimpDeath) {
			this->finalBoss->updateWindowsBoundCollisions(this->window);
			this->finalBoss->updateHealthBar();
		}
	}

	//check for collision between a monkey and a sprite 
	for (int i = 0; i < bloons.size(); i++) {

		bloons[i]->getSprite().move(-2.f * landscapeNum, 0.f); // As we increase levels, we increase the speed of balloons/difficulty//WE COMMENTED THIS OUT TO TEST THE BRICKS 

		if (/*bloons[i] != nullptr && */!(bloons[i]->isDeletedByDart))
			this->CheckBalloonCollision(this->bloons[i]);
	}

	this->updateGameText();
}

/*************************************************************
 * Function: updateGameText()
 * Date Created: 4/22/21
 * Date Last Modified: 4/27/21
 * Description: Updates the game text in the display window. Shows what level the user is
				on as well as the health of the monkey.
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The game text is updated using the current game information.
 *************************************************************/
void Game::updateGameText()
{
	std::stringstream ss; 

	ss << "LEVEL: " << landscapeNum << endl;
	if (tempMonkey->getHealth() == 0) {
		ss << "Health: 0" << endl;
	}
	else
		ss << "Health: " << this->tempMonkey->getHealth() << std::endl;
	this->uiText.setString(ss.str()); 
	this->renderUiText(this->window);
}

/*************************************************************
 * Function: render()
 * Date Created: 4/19/21
 * Date Last Modified: 4/28/21
 * Description: This function is the main render function for the 
 *				game. It renders all the necessary components for
 *				each of the levels. 
 * Input parameters: void 
 * Returns: void 
 * Preconditions: The game must have been ran from the menu
 * Postconditions: Will render the changes made in the update 
 *				   function and then displays them
 *************************************************************/
void Game::render()
{
	this->window->clear(); //Clear the window in the past frame 

	if (tempMonkey->timeToRenderNewLandscape()) { //if it is time to render a new landscape....

		this->landscapeNum++;												//Increment the landscape 	
		tempMonkey->getMonkeySprite().setPosition(sf::Vector2f(0.f, 670.f));//Reset monkey pos							
		tempMonkey->firstDartThrow = false;									//Reset first dart throw
		tempMonkey->levelTracker = landscapeNum;							//Set the new level 

		if (landscapeNum < FINAL_LEVEL) {
			block->SetTilePosition(/*Small*/sf::Vector2f(static_cast<float> ((rand() % 100) + 600), 500.f),
				/*Long*/sf::Vector2f(static_cast<float> ((rand() % 200) + 800), 500.f));

			block2->SetTilePosition(/*Small*/sf::Vector2f(static_cast<float> ((rand() % 200) + 200), 500.f),
				/*Long*/sf::Vector2f(20000.f, 20000.f));
		}
		this->generateBalloons(landscapeNum);
		tempMonkey->setRenderLandscape(false);
	}
	else  //if it is not time to render a new landscape...
	{
		if (landscapeNum < FINAL_LEVEL)			//not the final level
			this->renderLandScape();	
		else if (landscapeNum == FINAL_LEVEL)	//we are in the final level  
		{
			this->renderFinalLandscape();

			if (this->finalBoss->getSprite().getGlobalBounds().top >= /*0.f*/250.f && this->isBlimpTouchingGround == true)  	//move the blimp up 
			{
				this->finalBoss->moveUp(); 
				this->finalBoss->updatePhysics(); 
				
				if (this->finalBoss->getSprite().getGlobalBounds().top < /*10.f*/ 260.f)
					this->isBlimpTouchingGround = false;
			}
			else 
			{																												//then move the blimp down 
				this->finalBoss->moveDown(); 

				if (this->finalBoss->getSprite().getGlobalBounds().top - this->finalBoss->getSprite().getGlobalBounds().height >= 170.f)
					this->isBlimpTouchingGround = true; 
			}
			if (!this->blimpDeath)
				this->finalBoss->render(this->window);

			if (!this->blimpDeath) 
			{
				if (this->spawnTimer == this->spawnTimerMax) { //Time to spawn new balloons on the final level 
					this->generateBalloons(landscapeNum);
					this->spawnTimer = 0;
				}
				else                                           //Increment the timer if we are not spawning yet 
					this->spawnTimer++;
			}

			if (finalBoss->getHealth() == 0) { //check if the boss is alive or not
				finalBoss->renderExplosion(this->window);
				this->window->display(); 

				std::chrono::milliseconds timespan(1000);
				std::this_thread::sleep_for(timespan);
				this->blimpDeath = true; 
				delete finalBoss;
			}
		}
	}

	//only render balloons if they are not deleted										
	for (int i = 0; i < bloons.size(); i++) {
		if (!(bloons[i]->isDeletedByDart))
			this->bloons[i]->render(this->window);
	}

	tempMonkey->render(this->window);	//Render our hero 
	this->renderUiText(this->window); 	//Render ui text
	this->window->display();			//Display the new renders for next frame 
}

/*************************************************************
 * Function: renderUiText()
 * Date Created: 4/22/21
 * Date Last Modified: 4/22/21
 * Description: This function draws the string stream to the 
 *				the game window
 * Input parameters: void 
 * Returns: void 
 * Preconditions: The game must have been ran from the menu
 * Postconditions: Will draw the necessary components to the game 
 *				   screen. 
 *************************************************************/
void Game::renderUiText(sf::RenderTarget *target)
{
	target->draw(this->uiText);
}

/*************************************************************
 * Function: renderLandScape()
 * Date Created: 4/20/21
 * Date Last Modified: 4/26/21
 * Description: This function draws the ground, the background, 
 *				and the blocks to the screen
 * Input parameters: void 
 * Returns: void 
 * Preconditions: Once it is time to render a new landscape then 
 *				  this function will be called
 * Postconditions: The window will display all the components of 
 *				   the landscape 
 *************************************************************/
void Game::renderLandScape()
{
	this->window->draw(this->landscape);
	this->window->draw(this->landScapeGround);
	block->render(window);
	block2->render(window);
}

/*************************************************************
 * Function: renderFinalLandscape()
 * Date Created: 4/28/21
 * Date Last Modified: 4/28/21
 * Description: Renders the landscape of the final level in the Game class.
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The final landscape is rendered.
 *************************************************************/
void Game::renderFinalLandscape() {
	this->window->draw(this->finalLandscape);
	this->window->draw(this->finalLandscapeGround);
	block->render(window);
	block2->render(window);
}

////////Private Member functions below////////

/*************************************************************
 * Function: initVariables()
 * Date Created: 4/19/21
 * Date Last Modified: 4/29/21
 * Description: This function is called when a Game object is 
 *				instantiated. It initializes all of the variables
 *				that will be used in game.h. It also creates memory 
 *				on the heap for certain objects
 * Input parameters: void 
 * Returns: void 
 * Preconditions: A game object must be instantiated
 * Postconditions: Will initialize all of the game classes variables
 *************************************************************/
void Game::initVariables()
{ 
	this->tempMonkey = new Monkey;
	this->block = new Tile; 
    this->block2=new Tile;
	this->finalBoss = new FinalBoss;
	this->monkeyDeath = false;
	this->blimpDeath = false; 
	this->isBlimpTouchingGround = true; 
	this->window = nullptr;
	this->spawnTimer = 0;
	this->spawnTimerMax = 300;
	this->landscapeNum = /*1*/1;												//THIS IS A TEST
	this->generateBalloons(landscapeNum);						
}

/*************************************************************
 * Function: initWindow()
 * Date Created: 4/20/21
 * Date Last Modified: 4/20/21
 * Description: Initializes the display window to 1920 x 1080 with a 60 fps cap.
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The game window is initialized.
 *************************************************************/
void Game::initWindow()
{
	//Choose a resolution
	this->videoMode.width = 1920;
	this->videoMode.height = 1080;

	this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode.width, this->videoMode.height), "Monkey Jump", sf::Style::Titlebar | sf::Style::Close); //Initialize our window 

	this->window->setFramerateLimit(60);	//Set a max fps
}

/*************************************************************
 * Function: initLandScape()
 * Date Created: 4/21/21
 * Date Last Modified: 4/28/21
 * Description: The function initializes the texture and sprite
 *				variables with the necessary components to display
 *				the games landscape to the window. This is also 
 *				called from the constructor 
 * Input parameters: void 
 * Returns: void 
 * Preconditions: A game object must be instantiated
 * Postconditions: Sprite and texture variables will be initialized
 *************************************************************/
void Game::initLandScape()
{
	// Rectangle landscape implementation
	if(!this->landscapeTexture2.loadFromFile("Textures/ground2.png"))					//init the ground 
		std::cout << "ERROR::GAME::INILANDSCAPE::Could not load ground2 texture file." << endl;
     this->landScapeGround.setTexture(landscapeTexture2);
	this->landScapeGround.setPosition(0.f, 800.f);

	if(!this->landscapeTexture.loadFromFile("Textures/clouds.png"))						//init the background 
		std::cout << "ERROR::GAME::INILANDSCAPE::Could not load clouds texture file." << endl;
	this->landscape.setTexture(landscapeTexture);
	this->landscape.setPosition(0.f, 0.f);

	
	
	if (!this->finalLandscapeGroundTexture.loadFromFile("Textures/FinalGround.png"));	//init the ground for the final boss 
		std::cout << "ERROR::GAME::INITLANDSCAPE:: Could not load final ground texture file " << endl; 
	this->finalLandscapeGround.setTexture(finalLandscapeGroundTexture);
	this->finalLandscapeGround.setPosition(0.f, 800.f);
	
	if (!this->finalLandscapeTexture.loadFromFile("Textures/FinalBossBackground.png"));	//init the background for the final boss 
		std::cout << "ERROR::GAME::INITLANDSCAPE:: Could not load final boss background texture file " << endl;
	this->finalLandscape.setTexture(finalLandscapeTexture);
	this->finalLandscape.setPosition(0.f, 0.f); 

}

/*************************************************************
 * Function: initFont()
 * Date Created: 4/20/21
 * Date Last Modified: 4/20/21
 * Description: Initializes the font of the text displayed to the screen.
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The font of the text displayed to the screen is initialized.
 *************************************************************/
void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf")) 
		std::cout << "ERROR::GAME::INITFONTS() -- Failed to load font\n";
}

/*************************************************************
 * Function: initText()
 * Date Created: 4/23/21
 * Date Last Modified: 4/24/21
 * Description: This function initialized our text variable with 
 *				the font type variable. 
 * Input parameters: void
 * Returns: void 
 * Preconditions: Game object must be instantiated
 * Postconditions: Text variable will be initaialized with our 
 *				   font type 
 *************************************************************/
void Game::initText()
{
	//default position for font is 0,0

	this->uiText.setFont(this->font); //font is initialized above
	this->uiText.setCharacterSize(35); //12 pt font
	this->uiText.setFillColor(sf::Color::White);
}

/*************************************************************
 * Function: deleteBalloon()
 * Date Created: 4/24/21
 * Date Last Modified: 4/25/21
 * Description: Renders a pop sprite over the current balloon and sets the position of the
				balloon outside the screen so it appears to be deleted.
 * Input parameters: balloonPtr - The pointer to the balloon to be deleted.
 * Returns: None.
 * Preconditions: balloonPtr must not be nullptr.
 * Postconditions: The popsprite is rendered, and the balloon is "deleted".
 *************************************************************/
void Game:: deleteBalloon(redWeakest* balloonPtr) {
	balloonPtr->setPopSpritePos(sf::Vector2f(balloonPtr->getSprite().getPosition().x, balloonPtr->getSprite().getPosition().y));
	balloonPtr->renderBalloonPop(this->window);
	window->display(); 

	this->tempMonkey->getDartSprite().setPosition(sf::Vector2f(2000.f , 0.f));

	std::chrono::milliseconds timespan(10);
	std::this_thread::sleep_for(timespan); 
	
	balloonPtr->isDeletedByDart = true; 
	
	balloonPtr->getSprite().setPosition(-2000.f, 0.f);				
}

/*************************************************************
 * Function: generateBalloons()
 * Date Created: 4/23/21
 * Date Last Modified: 4/26/21
 * Description: This function first clears a vector of balloon types, 
 *				and then fills up another vector of balloon types. 
 *				Each time the landscape is incremented, the number
 *				of balloons will increase. 
 *				During the final boss fight, this function is called 
 *				multiple times to generate many balloons in one level 
 * Input parameters: int numBalloonsOfEachType
 * Returns: void 
 * Preconditions: This function is called if it is time to render  
 *				  a new landscape. It is also call
 * Postconditions: Will determine how many balloons to render.
 *************************************************************/
void Game::generateBalloons(int numBalloonsOfEachType) {
/*
	Formula for Bloons Generated
	1st Landscape: 1 R, 1 B, 1 G
	2nd Landscape: 2 R, 2 B, 2 G
	.
	.
	.
	nth Landscape: n R, n B, n G
	*/
	
	bloons.clear();

	for(int i = 0; i < numBalloonsOfEachType; i++) {
		bloons.push_back(new redWeakest);
		bloons.push_back(new blueMed);
		bloons.push_back(new greenStrong);
	}
}

/*************************************************************
 * Function: runGame()
 * Date Created: 4/19/21
 * Date Last Modified: 4/19/21
 * Description: Runs a Mario platformer game. The goal of the user is to reach the 
				right side of the screen. For each level, the number of balloons spawned 
				increases. Also, for the final level, the user has to kill a giant blimp
				which spawns balloons every few seconds. 
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The game is run.
 *************************************************************/
void Game::runGame()
{
	//game loop
	while (this->getWindowIsOpen() && !monkeyDeath) //While window is open and monkey is alive run the game
	{	
		this->update(); //update game. 

		this->render();	// render the game changes to the window
	}
}

////////NON MEMBER FUNCTIONS BELOW////////

/*************************************************************
 * Function: display()
 * Date Created: 4/26/21	
 * Date Last Modified: 4/27/21
 * Description: This function takes a window ptr as a parameter and 
 *				displays the rules to the window 
 * Input parameters: sf::RenderWindow *controlsWindow
 * Returns: void 
 * Preconditions: The rules option must be selected in the menu 
 * Postconditions: Will show the rules to the window 
 *************************************************************/
void displayRules(sf::RenderWindow *controlsWindow)
{
	sf::Font font;
	sf::Text uiText;
	std::stringstream ss;

	if (!font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::INITFONTS() -- Failed to load font\n";

	uiText.setFont(font); //font is initialized above
	uiText.setCharacterSize(35); //12 pt font
	uiText.setFillColor(sf::Color::White);

	ss << "- Press Escape to Exit\n" << endl;
	ss << "- Rules: " << endl;
	ss << "- Use the W, A, and D keys to move. W = up, A = left, D = right" << endl;
	ss << "- Hold the left mouse button to shoot darts and kill balloons" << endl;
	ss << "- Press the space bar to jump." << endl;
	ss << "- Your objective is to reach the right side of the screen while" << endl
		<< "losing minimal health" << endl;

	uiText.setString(ss.str());

	sf::Text escapeRules;
	escapeRules.setFont(font); //font is initialized above
	escapeRules.setCharacterSize(55); //12 pt font
	escapeRules.setFillColor(sf::Color::Red);
	escapeRules.setLetterSpacing(25);
	escapeRules.setPosition(0.f, 400.f);

	controlsWindow->draw(uiText);
	controlsWindow->draw(escapeRules);
	controlsWindow->display();

	while (controlsWindow->isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			controlsWindow->close();
		}
	}
}
