/*******************************************************************************
 * Programmers: Jose Robles, Adam Karaki, Nicholas Zheng, Evan Smith
 * Class: CptS 122
 * Programming Assignment: Programming Assignment 9
 * Date: 4/30/21
 *
 * Description: A power up we plan on adding to the game in the future
 ******************************************************************************/
#pragma once
#include "monkey.h"

//class boomerang : public Monkey {
//public:
//	boomerang(const sf::Vector2f& pos) : Monkey(pos) {
//		health = 2;
//		this->initShape();
//	}
//	void updateInput() {
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //left movement
//		{
//			//				    x                   y
//			this->shape.move(-this->movementSpeed, 0.f);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //right movement
//		{
//			//				    x                   y
//			this->shape.move(this->movementSpeed, 0.f);
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //Jump movement
//		{
//			//			   x                   y
//			this->shape.move(0.f, -this->movementSpeed); //first move upward, 
//
//			//then move it down
//			this->shape.move(0.f, this->movementSpeed / 3); //move downwards by a third of the movement speed?? --> TEST LATER
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) //Attack forwardand return attack
//		{
//			std::cout << "Boomerang" << endl;
//			shape2.setFillColor(sf::Color::Cyan);
//			shape2.setRadius(30.f);
//			shape2.move(10.f, 0.f);
//			shape2.move(-10.f, 0.f);
//		}
//	}
//	void initShape()
//	{
//		this->shape.setFillColor(sf::Color::Yellow);
//		this->shape.setSize(sf::Vector2f(50.f, 50.f));
//		this->shape.setPosition(sf::Vector2f(50.f, 650));
//	}
//	void render2(sf::RenderTarget* target)
//	{
//		target->draw(this->shape2);
//	}
//private:
//	sf::CircleShape shape2;
//};