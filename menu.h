/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: Class definition for the Menu class.
 ******************************************************************************/
 
#pragma once
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
public:
	Menu(float width, float height); // Constructor
	~Menu() {}; // Destructor

	void draw(sf::RenderWindow &window);
	//Got MoveUp() and MoveDown() from SonarSystems on gitHub
	void MoveUp();
	void MoveDown();
	int getChosenItem() {
		return selectedItemIndex;
	}

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};


/*************************************************************
 * Function: Menu()
 * Date Created: 4/24/21
 * Date Last Modified: 4/28/21
 * Description: Creates a menu with the following options: Play,
				Test, Controls, and Exit. Then, it allows the user to select
				one of the options. If play is selected, the user plays
				the platformer game. If test is selected, the test cases for the 
				Game object are run. If controls are selected, the controls for the
				game are described.
 * Input parameters: width - The width of the menu display window.
					 height - The height of the menu display window.
 * Returns: None.
 * Preconditions: None.
 * Postconditions: A Menu object is instantiated.
 *************************************************************/
Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		// handle error
	}
	//Got setPosition and setString from SonarSystem on gitHub
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2 - 50, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	menu[0].setCharacterSize(55);
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Test");
	menu[1].setPosition(sf::Vector2f(width / 2 - 50, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	menu[1].setCharacterSize(55);
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Controls");
	menu[2].setPosition(sf::Vector2f(width / 2 - 50, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	menu[2].setCharacterSize(55);
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(width / 2 - 50, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));
	menu[3].setCharacterSize(55);

	selectedItemIndex = 0;
}

 /*************************************************************
 * Function: Draw()
 * Date Created: 4/26/2021
 * Date Last Modified: 4/29/2021
 * Description: Draws the menu options to the menu window
 * Input parameters: A render window pointer
 * Returns: None
 * Preconditions: None.
 * Postconditions: All the menu options for the Menu object are drawn to the window.
 *************************************************************/
void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}
 /*************************************************************
 * Function: MoveUp()
 * Date Included: 4/26/2021
 * Date Last Modified: 4/26/2021
 * Description: Moves the choice of options up and changes the color of the current choice index.
 * Input parameters: None
 * Returns: None
 * Preconditions: None.
 * Postconditions: The color of the current menu option is changed to white and the one above
					is changed to red.
 *************************************************************/
void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
 /*************************************************************
 * Function: MoveDown()
 * Date Included: 4/26/2021
 * Date Last Modified: 4/26/2021
 * Description: Moves the choice number down and changes the color of the current index
 * Input parameters: None
 * Returns: None
 * Preconditions: None.
 * Postconditions: Changes the color of the current menu option to white and the color of the
				   menu option below to red.
 *************************************************************/
void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}