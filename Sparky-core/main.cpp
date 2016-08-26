#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src/utils/timer.h"

#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/layers/tilelayer.h"

#include <iostream>
#include <vector>
#include <time.h>

#define BATCH_RENDERER 1
int main() {
	
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky!",INIT_WIN_WIDTH,INIT_WIN_HEIGHT);
	glClearColor(0, 0, 0, 1.0f);

	Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader->enable();

	std::vector<Renderable2D*> sprites;
	TileLayer layer(&(*shader));

	srand(time(NULL));
	for (float y = -9.0f; y < 9.0f; y += 0.5f) {
		for (float x = -16.0f; x < 16.0f; x += 0.5f) {
			layer.add(new Sprite(x, y, 0.4f, 0.4f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}
	
	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.closed()) {
		window.clear();		
		double x, y;
		window.getMousePosition(x, y);
		shader->setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
		layer.render();
		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	shader->disable();
	return 0;
}