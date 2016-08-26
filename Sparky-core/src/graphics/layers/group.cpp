#include "group.h"

namespace sparky {
	namespace graphics {

		Group::Group(const maths::mat4& transform)
			: m_TransformationMatirx(transform){

		}

		void Group::submit(Renderer2D* renderer) const {
			renderer->push(m_TransformationMatirx);
			for (const Renderable2D* renderable : m_Renderables) {
				renderable->submit(renderer);
			}

			renderer->pop();
		}
	}
}