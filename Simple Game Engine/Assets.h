#pragma once
#include <map>
#include<string>
#include "Texture.h"
#include "Shader.h"

using std::map;
using std::string;



class Assets
{
public:
	static map<string, Texture> textures;
	static map<string, Shader> shaders;

	static Texture loadTexture(IRenderer& renderer, const string& filename, const string& name);

	static Texture& getTexture(const std::string& name);

	static Shader loadShader(const string& vShaderFile, const string& fShaderFile,
		const string& tcShaderFile, const string& teShaderFile,
		const string& gShaderFile, const string& name);

	static Shader& getShader(const string& name);

	static void clear();

private:
	Assets(){}

	static Texture loadTextureFromFile(IRenderer& renderer, const string& filename);

	static Shader loadShaderFromFile(const string& vShaderPath, const string& fShaderPath,
		const string& tcShaderPath = "", const string& teShaderPath = "", const string& gShaderPath = "" );
};

