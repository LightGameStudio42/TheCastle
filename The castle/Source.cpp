//Copyright(C) 2016-2018 LightGameStudio <theLightGameStudio@gmail.com>
#include<SFML\Graphics.hpp>
#include<iostream>
#include<sstream>
#include<conio.h>
#include"Engine.h"
#include"Update.h"
#include<SFML\Graphics\RenderTarget.hpp>
#include"TextNode.h"
#include"RenderManager.h"
#include"HandleEvents.h"
#pragma warning(disable : 4996)
using namespace sf;

void main()
{
	GameEngine game;
	Clock clock;
sf::Event event;
	float time;
	view.reset(sf::FloatRect(0, 0, Width, Height));
	while (mRenderManager.mWindow.isOpen())
	{
		mRenderManager.mWindow.setFramerateLimit(260);
		
	    time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 730;

		if (mRenderManager.mWindow.pollEvent(event))
		{
		//	if (event.type == Event::Resized){} {mRenderManager.mWindow.setSize(Vector2u(800,600));}
			if (event.type == Event::KeyPressed) keyboardHandler(event);
			if (event.type == Event::MouseButtonPressed)mouseHandler(event);
			if (event.type == sf::Event::Closed) mRenderManager.mWindow.close();
		}
		player.input();
		game.Update(time);

		mRenderManager.mWindow.setView(SetCamera(player.x + 10, player.y + 100));
		mRenderManager.render();
	}
}