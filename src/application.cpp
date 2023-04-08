#include <application.h>
#include <iostream>
#include <types.h>
#include <vector>
#include <camera.h>
#include <Cylinder.h>
#include <stb_image.h>
#include <stdlib.h>
#include <time.h> 

#include <glm/gtc/matrix_transform.hpp>



Application::Application(std::string WindowTitle, int width, int height) 
	: _appName{ WindowTitle }, _width{ width }, _height{ height },
	_camera {width, height, {6.0f, 2.0f, 5.0f}, true},
	_cameraSpeed {0.5f, 0.5f}{	
}

float deltaTime = {0.f};
float lastFrame = {0.f};



void Application::Run(){
	//Open the window
	if (!openWindow()) {
		return;
	}

	
	setupInputs();

	_running = true;

	

	//Run application
	while (_running) {
		if (glfwWindowShouldClose(_window)) {
			_running = false;
			continue;
		}

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		

		//Update
		update();

		//Draw
		draw();

	}

	glfwTerminate();
}



bool Application::openWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(800, 600, "Victor Ladoano", nullptr, nullptr);

	if (!_window) {
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(_window);

	glfwSetWindowUserPointer(_window, (void*)this);

	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		//this gets called whenever the window is resized
		glViewport(0, 0, width, height);

		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		app->_width = width;
		app->_height = height;

		app->_camera.SetSize(width, height);

		});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	//Enable Depth
	glEnable(GL_DEPTH_TEST);

	//cull back faces
	/*glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);*/

	return true;
}



//this function gathers the Vertices and Indices of the shape
void Application::setupScene() {
	

	
}

bool Application::update()
{
	glfwPollEvents();

	
	return false;
}

bool Application::draw(){


	Path shaderPath = std::filesystem::current_path() / "assets" / "shaders";


	//Might want to move this out of Draw which is on a loop
	_lightingShader = Shader(shaderPath / "6.multiple_lights.vs", shaderPath / "6.multiple_lights.fs");//New
	_lightCubeShader = Shader(shaderPath / "6.light_cube.vs", shaderPath / "6.light_cube.fs");//New

	

	//_shader.Bind();
	_lightingShader.Bind();//new
	_lightingShader.SetInt("material.diffuse", 0);
	_lightingShader.SetInt("material.specular", 1);


	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//world background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_lightingShader.Bind();
	_lightingShader.SetVec3("viewPos", _camera.GetPosition());
	_lightingShader.SetFloat("material.shininess", 32.0f);

	_lightingShader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	_lightingShader.SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	_lightingShader.SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	_lightingShader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	_lightingShader.SetVec3("pointLights[0].position", Shapes::pointLightPositions[0]);
	_lightingShader.SetVec3("pointLights[0].ambient", 0.02f, 0.02f, 0.02f);
	_lightingShader.SetVec3("pointLights[0].diffuse", 0.1f, 0.1f, 0.1f);
	_lightingShader.SetVec3("pointLights[0].specular", .1f, .1f, .1f);
	_lightingShader.SetFloat("pointLights[0].constant", .1f);
	_lightingShader.SetFloat("pointLights[0].linear", .1f);
	_lightingShader.SetFloat("pointLights[0].quadratic", .1f);
	// point Key light
	_lightingShader.SetVec3("pointLights[1].position", Shapes::pointLightPositions[1]);
	_lightingShader.SetVec3("pointLights[1].ambient", .02f, .02f, .02f);
	_lightingShader.SetVec3("pointLights[1].diffuse", 0.f, 0.5f, 0.0f);//color of diffuse light.
	_lightingShader.SetVec3("pointLights[1].specular", .1f, .1f, .1f);
	_lightingShader.SetFloat("pointLights[1].constant", .01f);//3 statements are the intensity
	_lightingShader.SetFloat("pointLights[1].linear", .01f);
	_lightingShader.SetFloat("pointLights[1].quadratic", 0.01f);

	_lightingShader.SetVec3("pointLights[3].position", Shapes::pointLightPositions[2]);
	_lightingShader.SetVec3("pointLights[3].ambient", .02f, .02f, .02f);
	_lightingShader.SetVec3("pointLights[3].diffuse", 0.f, 0.5f, 0.0f);//color of diffuse light.
	_lightingShader.SetVec3("pointLights[3].specular", .1f, .1f, .1f);
	_lightingShader.SetFloat("pointLights[3].constant", .01f);//3 statements are the intensity
	_lightingShader.SetFloat("pointLights[3].linear", .01f);
	_lightingShader.SetFloat("pointLights[3].quadratic", 0.01f);

	_lightingShader.SetVec3("pointLights[4].position", Shapes::pointLightPositions[3]);
	_lightingShader.SetVec3("pointLights[4].ambient", .02f, .02f, .02f);
	_lightingShader.SetVec3("pointLights[4].diffuse", 0.f, 0.5f, 0.0f);//color of diffuse light.
	_lightingShader.SetVec3("pointLights[4].specular", .1f, .1f, .1f);
	_lightingShader.SetFloat("pointLights[4].constant", .01f);//3 statements are the intensity
	_lightingShader.SetFloat("pointLights[4].linear", .01f);
	_lightingShader.SetFloat("pointLights[4].quadratic", 0.01f);
	
	//spotlight --May be needed
	//_lightingShader.SetVec3("spotLight.position", camera.Position);
	//_lightingShader.SetVec3("spotLight.direction", camera.Front); //disable spotlight
	_lightingShader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	_lightingShader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	_lightingShader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	_lightingShader.SetFloat("spotLight.constant", 1.0f);
	_lightingShader.SetFloat("spotLight.linear", 0.09);
	_lightingShader.SetFloat("spotLight.quadratic", 0.032);
	_lightingShader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	_lightingShader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


	//Camera
	glm::mat4 view = _camera.GetViewMatrix();
	glm::mat4 projection = _camera.GetProjectionMatrix();
	_lightingShader.SetMat4("projection", projection);
	_lightingShader.SetMat4("view", view);



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, allTexturePaths(0));
	_lightingShader.SetInt("tex0", 0);
	auto& planeMesh = _meshes.emplace_back(Shapes::planeVertices, Shapes::planeElements);
	planeMesh.Transform = glm::translate(planeMesh.Transform, glm::vec3(.0f, 4.3f, .0f));
	_lightingShader.SetMat4("model", planeMesh.Transform);
	//_shader.SetInt("tex0", 0);
	planeMesh.Draw();


	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, allTexturePaths(2));//May be a problem
	//_shader.SetInt("tex0", 1);
	//Draw Cylinder
	//Tumbler
	Cylinder cyl(1.0f, 1.0f, 6.0f, 36, 9, { 1.f, 1.f, 1.f }, 2);//baseRadius, topRadius, height, sectors, stacks, color, up
	shapeCylinder::cylVertices = cyl.getCylVertices();
	shapeCylinder::cylIndices = cyl.getCylIndices();
	auto& cylMesh = _meshes.emplace_back(shapeCylinder::cylVertices, shapeCylinder::cylIndices);
	cylMesh.Transform = glm::translate(cylMesh.Transform, glm::vec3(3.0f, 1.f, .0f));
	cylMesh.Transform = glm::rotate(cylMesh.Transform, glm::radians(90.0f), glm::vec3(1, 0, 0));
	_lightingShader.SetMat4("model", cylMesh.Transform);
	cylMesh.Draw();

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, allTexturePaths(1));//May be a problem
	//_shader.SetInt("tex0", 2);
	//Top
	Cylinder cyl2(1.07f, 1.0f, .7f, 36, 9, { 1.f, 1.f, 1.f }, 2);
	shapeCylinder::cylVertices = cyl2.getCylVertices();
	shapeCylinder::cylIndices = cyl2.getCylIndices();
	auto& cylMesh2 = _meshes.emplace_back(shapeCylinder::cylVertices, shapeCylinder::cylIndices);
	cylMesh2.Transform = glm::translate(cylMesh2.Transform, glm::vec3(3.0f, 3.7f, .0f));
	cylMesh2.Transform = glm::rotate(cylMesh2.Transform, glm::radians(90.0f), glm::vec3(1, 0, 0));
	_lightingShader.SetMat4("model", cylMesh2.Transform);
	cylMesh2.Draw();

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, allTexturePaths(1));
	//_shader.SetInt("tex0", 2);
	//middle anti-slip part
	Cylinder cyl3(1.01f, 1.01f, 1.8f, 36, 9, { 1.f, 1.f, 1.f }, 2);
	shapeCylinder::cylVertices = cyl3.getCylVertices();
	shapeCylinder::cylIndices = cyl3.getCylIndices();
	auto& cylMesh3 = _meshes.emplace_back(shapeCylinder::cylVertices, shapeCylinder::cylIndices);
	cylMesh3.Transform = glm::translate(cylMesh3.Transform, glm::vec3(3.0f, 2.0f, .0f));
	cylMesh3.Transform = glm::rotate(cylMesh3.Transform, glm::radians(90.0f), glm::vec3(1, 0, 0));
	_lightingShader.SetMat4("model", cylMesh3.Transform);
	cylMesh3.Draw();

	//+++++++NEW++++++//

	_lightCubeShader.Bind();
	_lightCubeShader.SetMat4("projection", projection);
	_lightCubeShader.SetMat4("view", view);

	for (unsigned int i = 0; i < 2; i++)
	{
		auto& cubeMesh = _meshes.emplace_back(Shapes::cubeVertices, Shapes::cubeElements);
		cubeMesh.Transform = glm::translate(cubeMesh.Transform, Shapes::pointLightPositions[i]);
		cubeMesh.Transform = glm::scale(cubeMesh.Transform, glm::vec3(2.0f, 2.0f, 2.0f));
		_lightCubeShader.SetMat4("model", cubeMesh.Transform);
		cubeMesh.Draw();
	}

	
	glfwSwapBuffers(_window);
	

	return false;
}

void Application::setupInputs() {
	glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

		switch (key) {
		case GLFW_KEY_ESCAPE: {
			if (scancode == GLFW_PRESS) {
				app->_running = false;
			}
			break;
		}
		case GLFW_KEY_P: {
			if (action == GLFW_PRESS) {
				app->_camera.ProcessKeyboard(Camera::ORTHO, deltaTime);
			}
			break;
		}
		case GLFW_KEY_W: {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				app->_camera.ProcessKeyboard(Camera::FORWARD, deltaTime);
			}
			break;
		}
		case GLFW_KEY_S: {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				app->_camera.ProcessKeyboard(Camera::BACKWARD, deltaTime);

			}
			break;
		}
		case GLFW_KEY_A: {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				app->_camera.ProcessKeyboard(Camera::LEFT, deltaTime);
			}
			break;
		}
		case GLFW_KEY_D: {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				app->_camera.ProcessKeyboard(Camera::RIGHT, deltaTime);
			}
			break;
		}
		case GLFW_KEY_Q: {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				app->_camera.ProcessKeyboard(Camera::UPWARD, deltaTime);
			}
			break;
		}
		case GLFW_KEY_E: {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				app->_camera.ProcessKeyboard(Camera::DOWNWARD, deltaTime);
			}
			break;
		}
		default: {}
		}

		//FIX LATER
		double xpos;
		double ypos;
		glfwSetCursorPos(window,app->xpos, app->ypos);
		app->mousePositionCallback(app->xpos, app->ypos);

		});

	glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos) {
		auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

		//glfwSetCursorPos(window, xpos, ypos);
		app->mousePositionCallback(xpos, ypos);

		});

	glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset) {
		auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

		app->_camera.MoreZoom(yOffset * 2);
		});



}

void Application::mousePositionCallback(double xpos, double ypos){
	if (!_firstMouse) {
		_lastMousePosition.x = static_cast<float>(xpos);
		_lastMousePosition.y = static_cast<float>(ypos);
		_firstMouse = true;
	}
	glm::vec2 moveAmount{
		xpos - _lastMousePosition.x,
		_lastMousePosition.y - ypos,
	};

	_lastMousePosition.x = static_cast<float>(xpos);
	_lastMousePosition.y = static_cast<float>(ypos);

	_camera.RotateBy(moveAmount.x * _cameraSpeed.x, moveAmount.y * _cameraSpeed.y);
}

unsigned int Application::loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int Application::allTexturePaths(int texture)
{
	Path texturePath = std::filesystem::current_path() / "assets" / "textures";
	
	switch (texture) {
	case 0: {
		auto tablePath = (texturePath / "wood.jpg").string();//(1)assigns the texture path to a variable
		unsigned int chosenText = loadTexture(tablePath.c_str());//(2)loads that variable in char to an uint to load the stbi_load
		return chosenText;
		break;
	}
	case 1: {
		auto cupPath = (texturePath / "metal2.jpg").string();//(1)assigns the texture path to a variable
		unsigned int chosenText = loadTexture(cupPath.c_str());//(2)loads that variable in char to an uint to load the stbi_load
		return chosenText;
		break;
	}
	case 2: {
		auto holderPath = (texturePath / "antislip.jpg").string();//(1)assigns the texture path to a variable
		unsigned int chosenText = loadTexture(holderPath.c_str());//(2)loads that variable in char to an uint to load the stbi_load
		return chosenText;
		break;
	}
	case 3: {
		auto cubePath = (texturePath / "rubikSide.jpg").string();//(1)assigns the texture path to a variable
		unsigned int chosenText = loadTexture(cubePath.c_str());//(2)loads that variable in char to an uint to load the stbi_load
		return chosenText;
		break;
	}
	default: {}
	}

}
