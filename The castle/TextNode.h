#pragma once
#include<SFML\Graphics.hpp>
#ifndef TEXTNODE_H
#define TEXTNODE_H
class TextNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	Text mText;
	Font mFont;
	explicit TextNode(int size, const std::string& fontName)
	{
	    mFont.loadFromFile(fontName+".ttf");
		mText.setFont(mFont);
		mText.setCharacterSize(size);

		mText.setFillColor(Color(0,0,0)); //default text color
	}
	virtual	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mText, states);
	}
	void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
	}
	void setString(const std::string& text)
	{
		mText.setString(text);
	}
};
#endif