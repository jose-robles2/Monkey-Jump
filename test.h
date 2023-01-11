/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: Class definition for the gameTest class, which tests features of the
				Game class.
 ******************************************************************************/

#pragma once
#include "game.h"


class gameTest : public Game
{
public: 

	gameTest() : Game()
	{
		this->initLandscape();
		balloonTest = new redWeakest;
		timeToMoveBalloon = true; 
		timeToSetBalloon = true; 
		timeToSetTile = true; 
		timeToSetTile2 = true; 
	}

	~gameTest()
	{
		delete balloonTest;
	}
	
	void runTests();
	
private: 
	
	//Bools
	bool timeToMoveBalloon; 
	bool timeToSetBalloon; 
	bool timeToSetTile; 
	bool timeToSetTile2; 

	void initLandscape(); 

	//updates
	void update();
	void updateGameText(); 

	//renders
	void render();
	void renderLandScape();
	void renderTest1();
	void renderTest2();
	void renderTest3();
	void renderTest4();
	void renderTest5();
	
	redWeakest* balloonTest; 
};


// PUBLIC MEMBER FUNCTIONS

/*************************************************************
 * Function: runTests()
 * Date Created: 4/29/21
 * Date Last Modified: 4/29/21
 * Description: Runs 5 test cases that test Game's features. The first one tests whether or not the balloon 
				damages the monkey. The second one tests whether the dart thrown by the monkey is capable of 
				popping a balloon by having the user press the left mouse button. The third one tests the 
				jump feature by having the user jump over a motionless balloon. The fourth one tests brick 
				collision by having the user jump on bricks and seeing if they collide with bricks properly.
				Finally, the fifth one tests whether the health bar, hitbox, and texture of the final boss works
				properly by having the user press the left mouse button while aiming the dart at the final boss. If
				it is not automatically done, the user will have to move to the right side of the screen to render the
				next test.
 * Input parameters: None.
 * Returns: None.
 * Preconditions: The tests must be run through the main menu.
 * Postconditions: All 5 test cases are run for the Game class.
 *************************************************************/
void gameTest::runTests() 
{
	while (this->landscapeNum <= 5) { // Run 5 Test Cases
		
		this->update(); 

		this->render();
	}
}

// PRIVATE MEMBER FUNCTIONS

/*************************************************************
 * Function: initLandscape()
 * Date Created: 4/30/21
 * Date Last Modified: 4/30/21
 * Description: This function does most of the same things as the one in Game, but it loads a
 *				different background texture than the one in game.h. It also reads textures for 
 *				the ground, the final ground, and the final background 
 * 
 * Input parameters: void 
 * Returns: void
 * Preconditions: A test must be ran through the main menu 
 * Postconditions: Will render 
 *************************************************************/
void gameTest::initLandscape()
{
	// Rectangle landscape implementation
	if (!this->landscapeTexture2.loadFromFile("Textures/ground2.png"))					//init the ground 
		std::cout << "ERROR::GAME::INILANDSCAPE::Could not load ground2 texture file." << endl;
	this->landScapeGround.setTexture(landscapeTexture2);
	this->landScapeGround.setPosition(0.f, 800.f);

	if (!this->landscapeTexture.loadFromFile("Textures/cloudsWithAndy.png"))						//init the background 
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
 * Function: update()
 * Date Created: 4/29/21
 * Date Last Modified: 4/29/21
 * Description: This function is the main update function for the test cases. 
 *				it is similar to the test function that is in game.h, except 
 *				it updates certain things depending on which test case we are
 *				on
 * 
 * Input parameters: void 
 * Returns: void 
 * Preconditions: A test must be ran through the main menu
 * Postconditions: Will allow the 5 test cases to make the changes that will 
 * be eventually rendered by the main render function 
 *************************************************************/
void gameTest::update()
{
	if (this->landscapeNum > FINAL_LEVEL) //End the test once we have passed the final boss 
		this->window->close(); 
	 
	this->pollEvents(); //Detect Actions toward the game window 
	this->updateGameText();

	if (this->landscapeNum == 1) {
		this->balloonTest->getSprite().move(-2.0f, 0.f);
		this->CheckBalloonCollision(balloonTest);

		if (this->tempMonkey->getHealth() == 0)
			this->tempMonkey->setRenderLandscape(true);
	}
	else if (this->landscapeNum == 2) {
		this->tempMonkey->update(this->window); //update our hero 
		this->CheckBalloonCollision(this->balloonTest);

		if (timeToSetBalloon) {
			this->balloonTest->getSprite().setPosition(1000.f, 725.f);
			timeToSetBalloon = false;
		}

		if (balloonTest->getHealth() == 0) {
			balloonTest->getSprite().setPosition(2000.f, 2000.f);
		}
	}
	else if (this->landscapeNum == 3) {
		if (timeToMoveBalloon) {
			this->balloonTest->getSprite().setPosition(1000.f, 725.f);
			timeToMoveBalloon = false;
		}
		this->tempMonkey->update(this->window); //update our hero 
	}
	else if (this->landscapeNum == 4) {
		if (timeToSetTile) {
			this->block->SetTilePosition(/*Small*/ sf::Vector2f(450.f, 500.f), /*Long*/sf::Vector2f(20000.f, 20000.f));
			this->block2->SetTilePosition(/*Small*/ sf::Vector2f(650.f, 450.f), /*Long*/sf::Vector2f(850.f, 450.f));
			timeToSetTile = false;
		}
		this->tempMonkey->update(this->window); //update our hero 
		this->block->updateCollisions(this->tempMonkey);
		this->block2->updateCollisions(tempMonkey);
	}
	else if (this->landscapeNum == 5) {

		if (timeToSetTile2) {
			block->SetTilePosition(/*Small*/ sf::Vector2f(150.f, 500.f), /*Long*/sf::Vector2f(20000.f, 20000.f));
			block2->SetTilePosition(/*Small*/ sf::Vector2f(400.f, 500.f), /*Long*/sf::Vector2f(20000.f, 20000.f));
		}
		this->tempMonkey->update(this->window); //update our hero 
		this->block->updateCollisions(this->tempMonkey);
		this->block2->updateCollisions(tempMonkey);
		this->CheckBossCollision();
	}

}

/*************************************************************
 * Function: updateGameText()
 * Date Created: 4/29/21
 * Date Last Modified: 4/29/21
 * Description: Updates the game text, which provides the instructions for the
				user to complete each test case. 
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The game text is updated.
 *************************************************************/
void gameTest::updateGameText()
{
	std::stringstream ss;

	switch (this->landscapeNum)
	{
	case 1: 
		ss << "TEST 1: " << endl << "We are testing balloon damage on the monkey. Let the balloon kill you and the next test will be rendered - Andy" << endl; 
		break; 
	case 2: 
		ss << "Test 2: " << endl << "Now, it is your turn. Hold the left mouse button to pop a balloon with your dart. Then, move to the right side of the screen to render the next test - Andy" << endl;
		break;
	case 3: 
		ss << "Test 3: " << endl << "Okay, now test the jump feature by jumping over that motionless balloon with the space bar! We turned off collisions so you can focus on jumping.\nOnce you have jumped over it, proceed to the right side of the screen to render the next test - Andy" << endl;
		break;
	case 4: 
		ss << "Test 4: " << endl << "Now that you can jump, use your jumping skills to see if our brick collisions work or not! - Andy" << endl;
		break; 
	case 5: 
		ss << "Test 5: " << endl << "Congrats on completing the previous tests, now you can get a peek at the final boss and try to defeat him yourself! - Andy" << endl; 
		break; 
	}

	this->uiText.setString(ss.str());
}

/*************************************************************
 * Function: render()
 * Date Created: 4/29/21
 * Date Last Modified: 4/29/21
 * Description: Renders the characters, landscape, and game text for each landscape. Also,
				it renders a new landscape when it is appropriate.
 * Input parameters: None.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: The display window is rendered with up-to-date information.
 *************************************************************/
void gameTest::render()
{
	this->window->clear(); //Clear the window in the past frame 

	if (tempMonkey->timeToRenderNewLandscape()) { //if it is time to render a new landscape....
		
		this->landscapeNum++;												//Increment the landscape 	
		tempMonkey->getMonkeySprite().setPosition(sf::Vector2f(0.f, 670.f));//Reset monkey pos							
		tempMonkey->firstDartThrow = false;									//Reset first dart throw
		tempMonkey->levelTracker = landscapeNum;							//Set the new level 
		tempMonkey->setRenderLandscape(false);
	}
	
	switch(landscapeNum) {
	case 1:
		renderTest1();
		break;
	case 2:
		renderTest2();

		if (balloonTest->getHealth() == 0)
			cout << "Balloon successfully killed" << endl;
			
		break;
	case 3:
		renderTest3();
		break;
	case 4:
		renderTest4();
		break;
	case 5:

		renderTest5();

		if (!this->blimpDeath) {
			this->finalBoss->updateWindowsBoundCollisions(this->window);
			this->finalBoss->updateHealthBar();
		}

		if (finalBoss->getHealth() == 0) { //check if the boss is alive or not
			finalBoss->renderExplosion(this->window);
			this->window->display();

			std::chrono::milliseconds timespan(1000);
			std::this_thread::sleep_for(timespan);
			this->blimpDeath = true;
			delete finalBoss;
		}
		break;
	default:
		cout << "End of test cases" << endl;
	}
	

	

	tempMonkey->render(this->window);	//Render our hero 
	this->renderUiText(this->window); 	//Render ui text
	this->window->display();			//Display the new renders for next frame 
}

/*************************************************************
 * Function: renderTest1()
 * Date Created: 4/29/21
 * Date Last Modified: 4/29/21
 * Description: This function renders all the things needed for
 *				the first test case. It renders: monkey, balloon, 
 *				and the landscape. 
 * 
 * Input parameters: void
 * Returns: void 
 * Preconditions: The landscape number must equal 1 in order for 
 *				  this function to execute
 * 
 * Postconditions: Will render test case 1 
 *************************************************************/
void gameTest::renderTest1() {
	renderLandScape();
	tempMonkey->render(window);
	balloonTest->render(window);
}

/*************************************************************
 * Function: renderTest2()
 * Date Created: 4/29/21
 * Date Last Modified: 4/29/21
 * Description: This function renders all the things needed for
 *				the second test case. It renders: monkey, balloon,
 *				and the landscape.
 *
 * Input parameters: void
 * Returns: void
 * Preconditions: The landscape number must equal 2 in order for
 *				  this function to execute
 *
 * Postconditions: Will render test case 2
 *************************************************************/
void gameTest::renderTest2() {
	renderLandScape();
	tempMonkey->render(window);
	balloonTest->render(window);
}

/*************************************************************
 * Function: renderTest3()
 * Date Created: 4/29/21
 * Date Last Modified: 4/29/21
 * Description: This function renders all the things needed for
 *				the third test case. It renders: monkey, balloon,
 *				and the landscape.
 *
 * Input parameters: void
 * Returns: void
 * Preconditions: The landscape number must equal 3 in order for
 *				  this function to execute
 *
 * Postconditions: Will render test case 3
 *************************************************************/
void gameTest::renderTest3() {
	renderLandScape();
	tempMonkey->render(window);
	balloonTest->render(window);
}

/*************************************************************
 * Function: renderTest4()
 * Date Created: 4/29/21
 * Date Last Modified: 4/29/21
 * Description: This function renders all the things needed for
 *				the fourth test case. It renders: monkey, balloon,
 *				blocks, and the landscape.
 *
 * Input parameters: void
 * Returns: void
 * Preconditions: The landscape number must equal 4 in order for
 *				  this function to execute
 *
 * Postconditions: Will render test case 4
 *************************************************************/
void gameTest::renderTest4() {
	renderLandScape();
	tempMonkey->render(window);
	block->render(window); 
	block2->render(window); 
}

/*************************************************************
 * Function: renderTest5()
 * Date Created: 4/29/21
 * Date Last Modified: 4/29/21
 * Description: This function renders all the things needed for
 *				the fifth test case. It renders: monkey, 
 *				blocks, blimp boss, and the landscape.
 *
 * Input parameters: void
 * Returns: void
 * Preconditions: The landscape number must equal 5 in order for
 *				  this function to execute
 *
 * Postconditions: Will render test case 5
 *************************************************************/
void gameTest::renderTest5() {
	renderFinalLandscape();
	tempMonkey->render(window);
	if (!blimpDeath)
		finalBoss->render(window);
}

/*************************************************************
 * Function: renderLandScape()
 * Date Created: 4/29/21
 * Date Last Modified: 4/29/21
 * Description: This function renders both the landscape and the 
 *				background for the landscape 
 * 
 * Input parameters: void 
 * Returns: void 
 * Preconditions: Test must be ran through the main menu
 * Postconditions: Will render the landscape 
 *************************************************************/
void gameTest::renderLandScape() {
	this->window->draw(this->landscape);
	this->window->draw(this->landScapeGround);
}
