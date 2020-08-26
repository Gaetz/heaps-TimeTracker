#ifndef RENDERER_OGL_H
#define RENDERER_OGL_H

#include "maths/Vector2.h"
#include "maths/Matrix4.h"
#include "VertexArray.h"
#include <GL/glew.h>
#include <SDL_render.h>
#include <vector>
#include <SDL_image.h>

enum class Flip
{
    None = SDL_FLIP_NONE,
    Horizontal = SDL_FLIP_HORIZONTAL,
    Vertical = SDL_FLIP_VERTICAL
};

class RendererOGL
{
public:
	RendererOGL();
	RendererOGL(const RendererOGL&) = delete;
	RendererOGL& operator=(const RendererOGL&) = delete;

	bool initialize(const class WindowSdl& windowP);
	void beginDraw();
	void draw();
	void endDraw();
	void close();

	void addSprite(struct Sprite* sprite);
	void removeSprite(struct Sprite* sprite);
	void drawSprite(const class Actor& actor, const class Texture& tex, struct Rectangle srcRect, Vector2 origin, Flip flip) const;

private:
	void drawSprites();
	VertexArray* spriteVertexArray;
	Matrix4 spriteViewProj;
	std::vector<class Sprite*> sprites;
};

#endif