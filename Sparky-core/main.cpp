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
#if 0
	GLfloat vertices[] = {
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 3, 0,
		8, 0, 0
	};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
#endif

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	//mat4 ortho = mat4::orthographic(-1.0f, 17.0f, -1.0f, 10.0f, -1.0f, 1.0f);

	Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader->enable();
	shader->setUniformMat4("pr_matrix", ortho);

	std::vector<Renderable2D*> sprites;
	TileLayer layer(&(*shader));

	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 0.5f) {
		for (float x = 0; x < 16.0f; x += 0.5f) {
			layer.add(
				new 
#if BATCH_RENDERER
				Sprite
#else
				StaticSprite
#endif
				(x, y, 0.4f, 0.4f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)
#if !BATCH_RENDERER
					, shader
#endif
				));
		}
	}
	
#if BATCH_RENDERER
	BatchRenderer2D renderer;

#else
	StaticSprite sprite(0, 0, 16, 9, maths::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(8, 0, 8, 9, maths::vec4(0, 0.3f, 0.8f, 1.0f), shader);
	Simple2DRenderer renderer;
#endif
#if 0
	shader.setUniform2f("light_pos", vec2(8.0f, 4.5f));
	shader.setUniform4f("colour", vec4(1.0f, 0.3f, 0.8f, 1.0f));
#endif
	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.closed()) {
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader->setUniform2f("light_pos", vec2((float)(x * 16.0f / window.getWidth()), (float)(9.0f - y * 9.0f / window.getHeight())));
#if 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
		vao.bind();
		ibo.bind();

		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT,0);

		ibo.unbind();
		vao.unbind();

#endif
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