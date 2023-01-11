/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: Class used to create tiles in the game
 ******************************************************************************/
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "monkey.h"

using std::cout; 
using std::endl; 

/*
* Class: Tile
* Description: Contains all tiles for our platformer. Will let us jump from tiles, collide titles etc.
*
*/
class Tile
{
public:
	Tile()
	{
		longTilePos.x = 1000.f; 
		longTilePos.y = 500.f;

		smallTilePos.x = 700.f;
		smallTilePos.y = 500.f;

		this->initTexture();
		this->initSprite();
	}
	~Tile() {}
	void render(sf::RenderTarget* target);
	void updateCollisions(Monkey* tempMonkey);


	//Getters
	sf::Sprite& getLongTileSprite()
	{
		return this->LongtileSprite; 
	}
	sf::Sprite& getSmallTileSprite()
	{
		return this->SmalltileSprite;
	}
	//Setters
	 void SetTilePosition(const sf::Vector2f newSmallTilePos, const sf::Vector2f newLongTilePos)
	{
		smallTilePos = newSmallTilePos;
		longTilePos = newLongTilePos;

		this->initTexture();
		this->initSprite();
	}
	void setLongTileSprite(const sf::Vector2f newLongTilePos){
	longTilePos = newLongTilePos;
	}
	void setSmallTileSprite(const sf::Vector2f newSmallTilePos){
	smallTilePos = newSmallTilePos;
	}

private:
	sf::Sprite LongtileSprite, SmalltileSprite;
	sf::Texture LongtileSpriteTexture, SmalltileSpriteTexture;
	sf::Vector2f longTilePos; 
	sf::Vector2f smallTilePos; 
	void initTexture();
	void initSprite();
};

 /*************************************************************
 * Function: render
 * Date Created: 4/25/2021
 * Date Last Modified: 4/30/2021
 * Description: This function actually draws both tiles to the 
                screen.
 * Input parameters: RenderTarget* target 
 * Returns: None
 * Preconditions: Object is instantiated and is 
                  called in the renderLandScape() function 
				  in game.h 
 * Postconditions: It draws the tiles on the screen
 *************************************************************/
// PUBLIC MEMBER FUNCTIONS
void Tile::render(sf::RenderTarget* target) {
	target->draw(this->LongtileSprite);
	target->draw(this->SmalltileSprite);
}

 /*************************************************************
 * Function: updateCollisions
 * Date Created: 4/25/2021
 * Date Last Modified: 4/30/2021
 * Description: In updateCollisions, we check the bounds of both
                monkey and tile to prevent the player from going
				through the tile. We do this with if statements
				that check if the the small or large tile 
				intersect with the monkey. If the statement is 
				true, we check if its a left/right/up/down 
				collision and update the monkey's position
				appropriately.
 * Input parameters: Monkey* tempMonkey
 * Returns:void
 * Preconditions: The game is running and is called in the 
                  update() function in game.h
 * Postconditions: It does not let the monkey/player go through
                   the tile
 *************************************************************/
void Tile::updateCollisions( Monkey* tempMonkey)
{
	//small tile
	if (SmalltileSprite.getGlobalBounds().intersects(tempMonkey->getMonkeySprite().getGlobalBounds()))
	{
		sf::FloatRect monkeyBounds = tempMonkey->getMonkeySprite().getGlobalBounds();
		sf::FloatRect smallTileBounds = SmalltileSprite.getGlobalBounds();

		//Left collision
		if (monkeyBounds.left < smallTileBounds.left

			&& monkeyBounds.left + monkeyBounds.width < smallTileBounds.left + smallTileBounds.width

			&& monkeyBounds.top < smallTileBounds.top + smallTileBounds.height

			&& monkeyBounds.top + monkeyBounds.height > smallTileBounds.top)
		{
			tempMonkey->getMonkeySprite().setPosition(smallTileBounds.left - monkeyBounds.width + 35.f, monkeyBounds.top);
		}

		//Right collision
		else if (monkeyBounds.left > smallTileBounds.left

			&& monkeyBounds.left + monkeyBounds.width > smallTileBounds.left + smallTileBounds.width

			&& monkeyBounds.top < smallTileBounds.top + smallTileBounds.height

			&& monkeyBounds.top + monkeyBounds.height > smallTileBounds.top)
		{
			tempMonkey->getMonkeySprite().setPosition(smallTileBounds.left + smallTileBounds.width - 35.f, monkeyBounds.top);
		}

		//Bottom collision											 
		if (monkeyBounds.top > smallTileBounds.top

			&& monkeyBounds.top + monkeyBounds.height > smallTileBounds.top + smallTileBounds.height

			&& monkeyBounds.left < smallTileBounds.left + smallTileBounds.width - 50.f

			&& monkeyBounds.left + monkeyBounds.width - 50.f > smallTileBounds.left)
		{
			tempMonkey->getMonkeySprite().setPosition(monkeyBounds.left, smallTileBounds.top + smallTileBounds.height);
		}

		//Top collision
		else if (monkeyBounds.top < smallTileBounds.top

			&& monkeyBounds.top + monkeyBounds.height < smallTileBounds.top + smallTileBounds.height

			&& monkeyBounds.left < smallTileBounds.left + smallTileBounds.width - 50.f

			&& monkeyBounds.left +  monkeyBounds.width - 50.f > smallTileBounds.left)
		{
			tempMonkey->resetVelocityY();
			tempMonkey->touchingTileGround = true;
			tempMonkey->getMonkeySprite().setPosition(monkeyBounds.left, smallTileBounds.top - monkeyBounds.height + 25.f);
		}
	}		


	//long tile
	if (LongtileSprite.getGlobalBounds().intersects(tempMonkey->getMonkeySprite().getGlobalBounds()))
	{
		sf::FloatRect monkeyBounds = tempMonkey->getMonkeySprite().getGlobalBounds();
		sf::FloatRect longtileBounds = LongtileSprite.getGlobalBounds();

		//Left collision
		if (monkeyBounds.left < longtileBounds.left

			&& monkeyBounds.left + monkeyBounds.width < longtileBounds.left + longtileBounds.width

			&& monkeyBounds.top < longtileBounds.top + longtileBounds.height

			&& monkeyBounds.top + monkeyBounds.height > longtileBounds.top)
		{
			tempMonkey->getMonkeySprite().setPosition(longtileBounds.left - monkeyBounds.width + 35.f, monkeyBounds.top);
		}

		//Right collision
		else if (monkeyBounds.left > longtileBounds.left

			&& monkeyBounds.left + monkeyBounds.width > longtileBounds.left + longtileBounds.width

			&& monkeyBounds.top < longtileBounds.top + longtileBounds.height

			&& monkeyBounds.top + monkeyBounds.height > longtileBounds.top)
		{
			tempMonkey->getMonkeySprite().setPosition(longtileBounds.left + longtileBounds.width - 35.f, monkeyBounds.top);
		}

		//Bottom collision											
		if (monkeyBounds.top > longtileBounds.top

			&& monkeyBounds.top + monkeyBounds.height > longtileBounds.top + longtileBounds.height

			&& monkeyBounds.left < longtileBounds.left + longtileBounds.width - 50.f

			&& monkeyBounds.left + monkeyBounds.width - 50.f> longtileBounds.left)
		{
			tempMonkey->getMonkeySprite().setPosition(monkeyBounds.left, longtileBounds.top + longtileBounds.height);
		}

		//Top collision
		else if (monkeyBounds.top < longtileBounds.top

			&& monkeyBounds.top + monkeyBounds.height < longtileBounds.top + longtileBounds.height

			&& monkeyBounds.left < longtileBounds.left + longtileBounds.width - 50.f

			&& monkeyBounds.left + monkeyBounds.width - 50.f> longtileBounds.left)
		{
			tempMonkey->resetVelocityY();
			tempMonkey->touchingTileGround = true;
			tempMonkey->getMonkeySprite().setPosition(monkeyBounds.left, longtileBounds.top - monkeyBounds.height + 25.f);
		}
	}
}

 /*************************************************************
 * Function: initSprite
 * Date Created: 4/25/2021
 * Date Last Modified: 4/30/2021
 * Description:This function initializes our block png file 
 *			   to the long and small tile
 * Input parameters: void
 * Returns: void
 * Preconditions: The object "Tile" must be instantiated
 * Postconditions: The png is assigned to each tile
 *************************************************************/
// PRIVATE MEMBER FUNCTIONS
void Tile::initSprite()
{
	//Long tile initilization
	this->LongtileSprite.setTexture(this->LongtileSpriteTexture);
	//Resize the sprite
	this->LongtileSprite.setPosition(longTilePos);
	this->LongtileSprite.scale(1.f, 1.f);

	//Small tile intilization
	this->SmalltileSprite.setTexture(this->SmalltileSpriteTexture);
	//Resize the sprite
	this->SmalltileSprite.setPosition(smallTilePos);
	this->SmalltileSprite.scale(1.f, 1.f);
}
 /*************************************************************
 * Function: initTexture
 * Date Created: 4/25/2021
 * Date Last Modified: 4/30/2021
 * Description: We are retreiving the images from the "Textures" 
                folder to use it for the sprite.
 * Input parameters: void
 * Returns: void
 * Preconditions: The object "Tile" is instantiated
 * Postconditions: Grabs the pngs from the file and sets it 
                   to the texture variable
 *************************************************************/
void Tile::initTexture()
{
	//Load a texture from file
	if (!this->LongtileSpriteTexture.loadFromFile("Textures/LongTile.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";

	if (!this->SmalltileSpriteTexture.loadFromFile("Textures/SmallTile.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	
}