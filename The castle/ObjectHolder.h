#ifndef OBJECTS_H
#define OBJECTS_H
#include<SFML/Graphics.hpp>
class ObjectHolder;
using sf::Sprite;
using sf::Texture;
using sf::Image;
enum ID { eProfile = 0, eOrcHarpy = 1, eMap = 2, eQuest=3, eMenu = 4, eKnight=5};
/*class Object
{
	std::string name;
	Texture texture;
public:
	Sprite sprite;

	Object();
	Object(std::string NAME)
	{
		Image tImage;
		name = NAME;
		tImage.loadFromFile("images\\" + name + ".png");
		texture.loadFromImage(tImage);
		sprite.setTexture(texture);
	} 
};*/
class ObjectHolders
{
public:
	std::vector<Sprite> mSprites;
	std::vector<Texture> mTextures;

	Sprite sprite;
	Image image;
	Texture texture;
	void add(int id,std::string File)
	{
		std::cout << mTextures.size();
		image.loadFromFile("images\\" + File + ".png");
		texture.loadFromImage(image);
		mTextures.push_back( texture);
		mSprites.push_back (sprite);
		mSprites[id].setTexture(mTextures[id]);
	}
};
#endif