#include "crenderutils.h"
#include "GLM\ext.hpp"

int main()
{
	Window window;
	window.init(1280, 720, "Daaaaaaaaa Bears");

	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);
	Geometry spear = loadOBJ("../res/models/soulspear.obj");
	Geometry sphere = loadOBJ("../res/models/sphere.obj");
	Geometry plane = genGrid(512, 2);
	
	Texture spear_normal = loadTexture("../res/textures/soulspear_normal.tga");
	Texture spear_diffuse = loadTexture("../res/textures/soulspear_diffuse.tga");
	Texture spear_specular = loadTexture("../res/textures/soulspear_specular.tga");

	Shader qdraw = loadShader("../res/shaders/quad.vert", "../res/shaders/quad.frag", false);
	Shader gpass = loadShader("../res/shaders/gpass.vert", "../res/shaders/gpass.frag");
	Shader rpass = loadShader("../res/shaders/ripple.vert", "../res/shaders/ripple.frag");
	
	Shader spass = loadShader("../res/shaders/spass.vert", "../res/shaders/spass.frag", true, false, false);
	Shader lpass = loadShader("../res/shaders/lspass.vert", "../res/shaders/lspass.frag", false, true);

	const unsigned char norm_pixels[4] = { 127, 127, 255, 255 };
	Texture vertex_normals = makeTexture(1, 1, 4, norm_pixels);
	
	const unsigned char white_pixels[4] = { 255, 200, 255, 255 };
	Texture white = makeTexture(1, 1, 4, white_pixels);

	Framebuffer screen = { 0, 1280, 720 };
	
	bool isFTex[] = { false, true, false, true };
	Framebuffer gframe = makeFramebuffer(1280, 720, 4, isFTex);
	Framebuffer lframe = makeFramebuffer(1280, 720, 3);
	
	//Temporary Shadow FBuffer, will be cleared and reused by every light
	//Resolution will greatly effect quality
	Framebuffer sframe = makeFramebuffer(2048, 2048, 0);
		
	glm::mat4 camView = glm::lookAt(glm::vec3(-2, 2, 6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 camProj = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);
	
	float rotate = 0;

	glm::mat4 spearModel; //= glm::scale(glm::vec3(0.1f, 0.1f, 0.1f)) * glm::translate(glm::vec3(0, -2, 0)) * glm::rotate(rotate, glm::vec3(0, 1, 0));;
	glm::mat4 wallModel = glm::rotate(45.f, glm::vec3(0, -1, 0)) * glm::translate(glm::vec3(0, 0, -2)) * glm::scale(glm::vec3(4, 4, 1));
	glm::mat4 planeModel = glm::scale(glm::vec3(2, 1, 2)) * glm::translate(glm::vec3(-0.6f, -1, 2.28f));
	
	glm::mat4 lightProj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);

	glm::mat4 lightView = glm::lookAt(glm::normalize(-glm::vec3(1, -1, -1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 lightColor = glm::vec4(0.5f, 0, 0.75f, 1);

	glm::mat4 greenView = glm::lookAt(glm::normalize(-glm::vec3(10, 0.5f, -1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 greenColor = glm::vec4(1, 1, 1, 1);

	//Modifiers for ripple shader used on rpass
	float time = 0;
	float speed = 4;
	float scale = 1.0f;
	float frequency = 0.2f;

	while (window.step())
	{
		time += 0.016f;
		spearModel = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -2, 0));
		glm::vec4 SSFT = glm::vec4(speed, scale, frequency, time);

		clearFrameBuffer(gframe);
		tdraw(gpass, spear, gframe, spearModel, camView, camProj, spear_diffuse, spear_normal, spear_specular);
		tdraw(gpass, quad, gframe, wallModel, camView, camProj, white, vertex_normals, white);
		tdraw(rpass, plane, gframe, planeModel, camView, camProj, white, vertex_normals, white, SSFT);

		clearFrameBuffer(sframe);
		tdraw(spass, spear, sframe, spearModel, lightView, lightProj);
		tdraw(spass, quad, sframe, wallModel, lightView, lightProj);
		tdraw(spass, plane, sframe, planeModel, lightView, lightProj);

		clearFrameBuffer(lframe);
		tdraw(lpass, quad, lframe, camView, gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3], sframe.depth, lightColor, lightView, lightProj);

		clearFrameBuffer(sframe);
		tdraw(spass, spear, sframe, spearModel, greenView, lightProj);
		tdraw(spass, quad, sframe, wallModel, greenView, lightProj);
		tdraw(spass, plane, sframe, planeModel, greenView, lightProj);

		tdraw(lpass, quad, lframe, camView, gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3], sframe.depth, greenColor, greenView, lightProj);

		glm::mat4 mod = glm::translate(glm::vec3( 0, 0, 0));
		tdraw(qdraw, quad, screen, lframe.colors[0], mod);
	}

	window.term();
}