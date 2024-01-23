#pragma once
#include <map>
#include<string>
#include "Texture.h"

using std::map;
using std::string;



class Assets
{
public:
	static map<string, Texture> textures;

	static Texture loadTexture(IRenderer& renderer, const string& filename, const string& name);

	static Texture& getTexture(const std::string& name);

	static void clear();

private:
	Assets(){}

	static Texture loadTextureFromFile(IRenderer& renderer, const string& filename);
};

