#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mesh.h>
#include <shader.h>
#include <camera.h>


class Application {
public:
	Application(std::string WindowTitle, int width, int height);
	void Run();
	unsigned int loadTexture(char const* path);
	unsigned int allTexturePaths(int texture);

	
	//float lastFrame = { 0.0f };

private:
	bool openWindow();
	void setupInputs();
	void setupScene();
	bool update();
	bool draw();

	void mousePositionCallback(double xpos, double ypos);

private:

	double xpos;
	double ypos;
	

	bool _running{ false };
	std::string _appName{};
	int _width{};
	int _height{};
	GLFWwindow* _window{ nullptr };

	std::vector<Mesh> _meshes;
	Shader _shader;
	Shader _lightingShader;
	Shader _lightCubeShader;

	Shapes _pointLightPositions;


	Camera _camera;
	glm::vec2 _cameraSpeed;

	
	bool _firstMouse{ false };
	glm::vec2 _lastMousePosition{-1, -1};

	GLuint _metalTexture;
	GLuint _tableTexture;
	unsigned int chosenText{};


};