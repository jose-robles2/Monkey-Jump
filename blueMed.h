/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: Class definition for blueMed.
 ******************************************************************************/
#pragma once
#include "redWeakest.h"

class blueMed :public redWeakest {
public:
	blueMed() 
	{
		setPos(sf::Vector2f(rand() % 1500 + 400, 725.f));
		//this->speed = 1;
		initTexture();
		initSprite();
		health = 2; 
		this->isDeletedByDart = false;
	}

	~blueMed() 
	{
		//cout<<"inside the destructor";
	}

private:
	void initTexture();
	void initSprite(); 
	float speed;
};

////////Private Member functions below////////

 /*************************************************************
 * Function: initSprite()
 * Date Created: 4/21/2021
 * Date Last Modified: 4/21/2021
 * Description: Sets the texture and position of the blue balloon sprite
 * Input parameters: None
 * Returns: None
 * Preconditions: blueMed object is created
 * Postconditions: The texture for the blue balloon sprite is set 
					and the position of the balloon is initialized
 *************************************************************/
void blueMed::initSprite()
{
	this->mSprite.setTexture(this->mSpriteTexture);
	this->mSprite.setPosition(this->getPos());
	this->mSprite.scale(1.f, 0.99f); //Resize the sprite
}
 /*************************************************************
 * Function: initTexture()
 * Date Created: 4/21/2021
 * Date Last Modified: 4/21/2021
 * Description: Texture file for the blue balloon is loaded from the texture file.
 * Input parameters: None
 * Returns: None
 * Preconditions: blueMed object is created
 * Postconditions: If successful, the texture for the blue balloon is loaded, otherwise
				   a error message is displayed to the console.
 *************************************************************/
void blueMed::initTexture()
{
	//Load a texture from file
	if (!this->mSpriteTexture.loadFromFile("Textures/BlueBalloon.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}