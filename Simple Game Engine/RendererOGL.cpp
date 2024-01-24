#include "RendererOGL.h"
#include <GL/glew.h>
#include "Rectangle.h"
#include "Vector2.h"
#include "Log.h"
#include "SpriteComponent.h"

#include <SDL_image.h>

RendererOGL::RendererOGL() : window(nullptr), vertexArray(nullptr), context(nullptr) {
}

RendererOGL::~RendererOGL() {
}

bool RendererOGL::initialize(Window& windowP) {
	window = &windowP;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	context = SDL_GL_CreateContext(windowP.getSDLWindow());
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		Log::error(LogCategory::Video, "Failed to initialize GLEW");
		return false;
	}
	glGetError();

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		Log::error(LogCategory::Video, "Unable to initialize SDL_Image");
		return false;
	}

	vertexArray = new VertexArray(vertices, 4, indices, 6);
	return true;
}

void RendererOGL::beginDraw() {
	glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RendererOGL::draw() {
	drawSprites();
}

void RendererOGL::drawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const
{
}

void RendererOGL::endDraw() {
	SDL_GL_SwapWindow(window->getSDLWindow());
}

void RendererOGL::close() {
	SDL_GL_DeleteContext(context);
	delete vertexArray;
}

void RendererOGL::addSprite(SpriteComponent* sprite) {
	int spriteDrawOrder = sprite->getDrawOrder();
	auto iter = std::begin(sprites);
	for (; iter != end(sprites); ++iter) {
		if (spriteDrawOrder < (*iter)->getDrawOrder())break;
	}
	sprites.insert(iter, sprite);
}

void RendererOGL::removeSprite(SpriteComponent* sprite) {
	auto iter = std::find(begin(sprites), end(sprites), sprite);
	sprites.erase(iter);
}

void RendererOGL::drawSprites() {
	for (auto sprite : sprites) {
		sprite->draw(*this);
	}
}