#pragma once
#include "globjs.h"
#include "GLM\fwd.hpp"
#include <cstring>

void clearFrameBuffer(const Framebuffer &fb);

namespace tdraw_internal
{
	void tdraw_begin(const Shader &s, const Geometry &g, const Framebuffer &fb);
	void tdraw_close(const Shader &s, const Geometry &g, const Framebuffer &fb);

	size_t tdraw_format(size_t idx, size_t tex, float val);
	size_t tdraw_format(size_t idx, size_t tex, int val);

	size_t tdraw_format(size_t idx, size_t tex, const Texture &val);

	size_t tdraw_format(size_t idx, size_t tex, const glm::vec3 &val);
	size_t tdraw_format(size_t idx, size_t tex, const glm::mat3 &val);
	size_t tdraw_format(size_t idx, size_t tex, const glm::mat4 &val);

	template<typename T, typename ...U>
	void tdraw_unpack(size_t idx, size_t tex, T val, U &&...uniforms)
	{
		tex += tdraw_format(idx, tex, val);
		tdraw_unpack(idx + 1, tex, uniforms...);
	}

	template<typename T>
	void tdraw_unpack(size_t idx, size_t tex, T val)
	{
		tex += tdraw_format(idx, tex, val);
	}
}

template<typename ...U>
void tdraw(const Shader &s, const Geometry &g, const Framebuffer &fb, U ... uniforms)
{
	tdraw_internal::tdraw_begin(s, g, fb);
	tdraw_internal::tdraw_unpack(0, 0, uniforms...);
	tdraw_internal::tdraw_close(s, g, fb);
}

inline void tdraw(const Shader &s, const Geometry &g, const Framebuffer &fb)
{
	tdraw_internal::tdraw_begin(s, g, fb);
	tdraw_internal::tdraw_close(s, g, fb);
}