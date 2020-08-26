#include "RendererOGL.h"
#include "Assets.h"
#include "WindowSdl.h"
#include "maths/Rectangle.h"
#include "Sprite.h"
#include "GlDebug.hpp"

const float spriteVertices[] = {
	-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, // top left
	0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, // top right
	0.5f,-0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, // bottom right
	-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f  // bottom left
};

const unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

RendererOGL::RendererOGL():
	spriteVertexArray(nullptr)
{
}

bool RendererOGL::initialize(const WindowSdl& windowP)
{
	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// Depth buffering
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	// GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		LOG(Error) << "Failed to initialize GLEW.";
		return false;
	}

        
    // Get graphics info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    LOG(Info) << "Renderer: " << renderer;
    LOG(Info) << "OpenGL version supported " << version;

    glViewport(0, 0, windowP.getWidth(), windowP.getHeight());

	// On some platforms, GLEW will emit a benign error code, so clear it
	glGetError();

    if (glDebugMessageControlARB != nullptr) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback((GLDEBUGPROCARB) debugGlErrorCallback, nullptr);
        GLuint unusedIds = 0;
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, GL_TRUE);
    }

    // Window color
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		LOG(Error) << "Unable to initialize SDL_image";
		return false;
	}

	spriteVertexArray = new VertexArray(spriteVertices, 4, indices, 6);
    spriteViewProj = Matrix4::createSimpleViewProj(windowP.getWidth(), windowP.getHeight());
    return true;
}

void RendererOGL::beginDraw()
{
	glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Enable alpha blending on the color buffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Active shader and vertex array
	Assets::getShader("Sprite").use();
	Assets::getShader("Sprite").setMatrix4("uViewProj", spriteViewProj);
	spriteVertexArray->setActive();
}

void RendererOGL::draw()
{
	drawSprites();
}

void RendererOGL::drawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const
{
    /*
	Matrix4 scaleMat = Matrix4::createScale((float)tex.getWidth(), (float)tex.getHeight(), 1.0f);
	Matrix4 world = scaleMat * actor.getWorldTransform();
	//Matrix4 pixelTranslation = Matrix4::createTranslation(Vector3(-WINDOW_WIDTH / 2 - origin.x, -WINDOW_HEIGHT / 2 - origin.y, 0.0f)); // Screen pixel coordinates
	Assets::getShader("Sprite").setMatrix4("uWorldTransform", world); //pixelTranslation);
	tex.setActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    */
}

void RendererOGL::endDraw()
{
    // Check OpenGL error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        LOG(Error) << "OpenGL error: " << err;
    }
}

void RendererOGL::close()
{
	delete spriteVertexArray;
}

void RendererOGL::addSprite(Sprite* sprite)
{
	// Insert the sprite at the right place in function of drawOrder
    /*
	int spriteDrawOrder = sprite->getDrawOrder();
	auto iter = begin(sprites);
	for (; iter != end(sprites); ++iter)
	{
		if (spriteDrawOrder < (*iter)->getDrawOrder()) break;
	}
	sprites.insert(iter, sprite);
    */
}

void RendererOGL::removeSprite(Sprite* sprite)
{
    /*
	auto iter = std::find(begin(sprites), end(sprites), sprite);
	sprites.erase(iter);
    */
}

void RendererOGL::drawSprites()
{
    /*
	for (auto sprite : sprites)
	{
		sprite->draw(*this);
	}
    */
}