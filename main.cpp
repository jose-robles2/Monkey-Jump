/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: In main.cpp, we use menu.h to display the main menu. The main menu 
 *				consists of 4 options: Play, test, controls, exit. Play allows the 
 *				user to fully play the game. Test runs the user through 5 test cases
 *				it is sort of like a tutorial but also serves as a way to test aspects
 *				of the game. Control will pop up a sub menu and it will show how to play 
 *				the game. And then exit just exits the menu. 
 ******************************************************************************/

#include "menu.h"
#include "game.h"
#include "test.h"

int main()
 {	
		sf::RenderWindow window(sf::VideoMode(600, 600), "MonkeyJump Menu");
		Menu menu(600.f, 600.f);
		while (window.isOpen()) 
		{			
			sf::Event choice;
			while (window.pollEvent(choice)) 
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					menu.MoveUp();
				} 
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					menu.MoveDown();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					int menuOption = menu.getChosenItem();
					if (menuOption == 0) {
						Game gameObj; 
						gameObj.runGame();
						window.close();
					} 
					else if(menuOption==2) {
		
		                sf::RenderWindow *controlsWindow = new sf::RenderWindow(sf::VideoMode(800, 400), "Controls");
						displayRules(controlsWindow);
						delete controlsWindow; 
					}
					else if(menuOption==1) {
						gameTest test;
						test.runTests();
						window.close();
					}
					else {
						window.close();
					}
				}		
			}
			if (window.isOpen()) {
				window.clear();
				menu.draw(window);
				window.display();
			}	
		}
	return 0;
}