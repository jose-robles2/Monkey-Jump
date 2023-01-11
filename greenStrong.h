/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: Class definition for the greenStrong class.
 ******************************************************************************/
#pragma once
#include "redWeakest.h"
#include <SFML/Graphics.hpp>

class greenStrong :public redWeakest {
public:
	greenStrong() {
		setPos(sf::Vector2f(rand() % 1500 + 400, 725.f));
		speed = 1;
		this->initTexture();
		this->initSprite();
		health = 3;
		this->isDeletedByDart = false;
	}
	~greenStrong() 
	{
		//cout<<"inside the destructor"
	}
	//int getHealth();
private:
	void initTexture();
	void initSprite(); 
	float speed;
};

////////Private Member functions below////////
 /*************************************************************
 * Function: initSprite()
 * Date Created: 4/21/2021
 * Date Last Modified: 4/22/2021
 * Description: Sets the initial position of the green balloon to a random location on the screen
				at least 400 pixels away from the left edge of the window.
 * Input parameters: None
 * Returns: None
 * Preconditions: greenStrong object is created
 * Postconditions: Position of sprite is initialized.
 *************************************************************/
void greenStrong::initSprite()
{
	//Resize the sprite
	this->mSprite.setPosition(getPos());
	this->mSprite.scale(0.99f, 0.99f);
}
 /*************************************************************
 * Function: initTexture()
 * Date Created: 4/21/2021
 * Date Last Modified: 4/21/2021
 * Description: Loads the texture for the green balloon from the file.
				If the .png file is not found, and error notice is printed to the console window
 * Input parameters: None
 * Returns: None
 * Preconditions: greenStrong object is created
 * Postconditions: GreenBalloon.png is pulled from a file or else an error message is printed to the console
 *************************************************************/
void greenStrong::initTexture()
{
	//Load a texture from file
	if (!this->mSpriteTexture.loadFromFile("Textures/GreenBalloon.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}