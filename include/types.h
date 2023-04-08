#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <vector>



struct Vertex {
    glm::vec3 Position{0.f, 0.f, 0.f};
    glm::vec3 Color{0.0f, 0.0f, 0.0f};
    glm::vec3 Normal{ 0.f, 0.f, 0.f };
    glm::vec2 Uv{ 1.f, 1.f };

};

struct shapeCylinder {
    static inline std::vector<Vertex> cylVertices={};
    static inline std::vector<unsigned int> cylIndices={};
    
};


struct Rubik {

    glm::vec3 Position[27] = {
        //to move the cube anywhere, create loop that will re create this array based on the common value 1.05
        //Back Cubes
    glm::vec3(1.05f, -1.05f, -1.05f),
    glm::vec3(0.f, -1.05f, -1.05f),
    glm::vec3(-1.05f, -1.05f, -1.05f),
    glm::vec3(1.05f, 0.0f, -1.05f),
    glm::vec3(0.f, 0.0f, -1.05f),
    glm::vec3(-1.05f, 0.0f, -1.05f),
    glm::vec3(1.05f, 1.05f, -1.05f),
    glm::vec3(0.f, 1.05f, -1.05f),
    glm::vec3(-1.05f, 1.05f, -1.05f),

    //Middle Cubes
    glm::vec3(1.05f, -1.05f, .0f),
    glm::vec3(0.f, -1.05f, .0f),
    glm::vec3(-1.05f, -1.05f, .0f),
    glm::vec3(1.05f, 0.0f, .0f),
    glm::vec3(0.f, 0.0f, .0f),
    glm::vec3(-1.05f, 0.0f, .0f),
    glm::vec3(1.05f, 1.05f, .0f),
    glm::vec3(0.f, 1.05f, .0f),
    glm::vec3(-1.05f, 1.05f, .0f),

    //Front Cubes
    glm::vec3(1.05f, -1.05f, 1.05f),
    glm::vec3(0.f, -1.05f, 1.05f),
    glm::vec3(-1.05f, -1.05f, 1.05f),
    glm::vec3(1.05f, 0.0f, 1.05f),
    glm::vec3(0.f, 0.0f, 1.05f),
    glm::vec3(-1.05f, 0.0f, 1.05f),
    glm::vec3(1.05f, 1.05f, 1.05f),
    glm::vec3(0.f, 1.05f, 1.05f),
    glm::vec3(-1.05f, 1.05f, 1.05f)
    
    };
};
    

struct Shapes{

   /* static inline std::vector<Vertex> cylVertices = {

    };*/


    // positions of the point lights
    static inline glm::vec3 pointLightPositions[4] = {
        glm::vec3(-1.7f,  2.2f,  2.0f),
        glm::vec3(1.3f, 5.3f, -3.0f),
        glm::vec3(-2.0f, 5.0f, 3.0f),
        glm::vec3(0.0f,  4.0f, -5.0f)
    };
   
    static inline std::vector<Vertex> planeVertices = {

        {.Position{ -12.0f, -6.0f, -12.0f }, .Color{ 1.f, 1.f, 1.f }, .Uv{ 0.f, 0.f}},//0=bottom left
        {.Position { 12.0f, -6.0f, -12.0f},.Color{ 1.f, 1.f, 1.f }, .Uv{ 1.f, 0.f}},//1=bottom right
        {.Position { 12.0f, -6.0f, 12.0f},.Color{ 1.f, 1.f, 1.f }, .Uv{ 1.f, 1.f}},//2=top right
        {.Position { -12.0f, -6.0f, 12.0f},.Color{ 1.f, 1.f, 1.f }, .Uv{ 0.f, 1.f}},//3=top left

    };

    static inline std::vector<uint32_t> planeElements = {
        0, 1, 2,
        0, 2, 3,
    };
    

    static inline std::vector<Vertex> triVertices = {
        {
            .Position {-0.25f, -0.25f, 0.0f}, //position
            .Color {0.f, 1.f, 0.f} //color
        },
        {
            .Position{0.25f, -0.25f, 0.0f}, //position
            .Color{0.f, 1.f, 0.f} //color
        },
        {
            .Position{0.f, 0.25f, 0.0f}, //position
            .Color {0.f, 1.f, 0.f} //color
        },


    };

    static inline std::vector<uint32_t> triElements = {
        0, 1, 2,
    };


    static inline std::vector<Vertex> cubeVertices {

        //Front face 
        {
            .Position = {-0.5f, 0.5f, 0.5f},
            .Color = {0.f, 0.f, 1.f},
            .Normal = {0.0f,  0.0f,  1.0f},
            .Uv{ 0.f, 1.f}
        },
        {
            .Position = {-0.5f, -0.5f, 0.5f},
            .Color = {0.f, 0.f, 1.f},
            .Normal = {0.0f,  0.0f,  1.0f},
            .Uv{ 0.f, 0.f}
        },
        {
            .Position = {0.5f, -0.5f, 0.5f},
            .Color = {0.f, 0.f, 1.f},
            .Normal = {0.0f,  0.0f,  1.0f},
            .Uv{ 1.f, 0.f}
        },
        {
            .Position = {0.5f, 0.5f, 0.5f},
            .Color = {0.f, 0.f, 1.f},
            .Normal = {0.0f,  0.0f,  1.0f},
            .Uv{ 1.f, 1.f}
        },

        //Right face - RED
       {
           .Position = {0.5f, 0.5f, 0.5f},
           .Color = {1.f, 0.f, 0.f},
           .Normal = {1.0f,  0.0f,  0.0f},
           .Uv{ 1.f, 1.f}
       },
       {
           .Position = {0.5f, -0.5f, 0.5f},
           .Color = {1.f, 0.f, 0.f},
           .Normal = {1.0f,  0.0f,  0.0f},
           .Uv{ 1.f, 0.f}
       },
       {
           .Position = {0.5f, -0.5f, -0.5f},
           .Color = {1.f, 0.f, 0.f},
           .Normal = {1.0f,  0.0f,  0.0f},
           .Uv{ 0.f, 0.f}
       },
       {
           .Position = {0.5f, 0.5f, -0.5f},
           .Color = {1.f, 0.f, 0.f},
           .Normal = {1.0f,  0.0f,  0.0f},
           .Uv{ 0.f, 1.f}
       },

        //Back face - WHITE
      {
          .Position = {0.5f, 0.5f, -0.5f},
          .Color = {1.f, 1.f, 1.f},
          .Normal = {0.0f,  0.0f,  -1.0f},
          .Uv{ 0.f, 0.f}
      },
      {
          .Position = {0.5f, -0.5f, -0.5f},
          .Color = {1.f, 1.f, 1.f},
          .Normal = {0.0f,  0.0f,  -1.0f},
          .Uv{ 0.f, 0.f}
      },
      {
          .Position = {-0.5f, -0.5f, -0.5f},
          .Color = {1.f, 1.f, 1.f},
          .Normal = {0.0f,  0.0f,  -1.0f},
          .Uv{ 0.f, 0.f}
      },
      {
          .Position = {-0.5f, 0.5f, -0.5f},
          .Color = {1.f, 1.f, 1.f},
          .Normal = {0.0f,  0.0f,  -1.0f},
          .Uv{ 0.f, 0.f}
      },

        //Left face - GREEN
      {
          .Position = {-0.5f, 0.5f, -0.5f},
          .Color = {0.f, 0.5f, 0.f},
          .Normal = {-1.0f,  0.0f,  0.0f},
      },
      {
          .Position = {-0.5f, -0.5f, -0.5f},
          .Color = {0.f, 0.5f, 0.f},
          .Normal = {-1.0f,  0.0f,  0.0f},
      },
      {
          .Position = {-0.5f, -0.5f, 0.5f},
          .Color = {0.f, 0.5f, 0.f},
          .Normal = {-1.0f,  0.0f,  0.0f},
      },
      {
          .Position = {-0.5f, 0.5f, 0.5f},
          .Color = {0.f, 0.5f, 0.f},
          .Normal = {-1.0f,  0.0f,  0.0f},
      },

        //Top face YELLOW
     {
         .Position = {-0.5f, 0.5f, -0.5f},
         .Color = {1.f, 1.f, 0.f},
         .Normal = {0.0f,  1.0f,  0.0f},
     },
     {
         .Position = {-0.5f, 0.5f, 0.5f},
         .Color = {1.f, 1.f, 0.f},
         .Normal = {0.0f,  1.0f,  0.0f},
     },
     {
         .Position = {0.5f, 0.5f, 0.5f},
         .Color = {1.f, 1.f, 0.f},
         .Normal = {0.0f,  1.0f,  0.0f},
     },
     {
         .Position = {0.5f, 0.5f, -0.5f},
         .Color = {1.f, 1.f, 0.f},
         .Normal = {0.0f,  1.0f,  0.0f},
     },

        //Bottom face ORANGE
    {
        .Position = {0.5f, -0.5f, 0.5f},
        .Color = {1.f, 0.5f, 0.f},
        .Normal = {0.0f,  -1.0f,  0.0f},
    },
    {
        .Position = {0.5f, -0.5f, -0.5f},
        .Color = {1.f, 0.5f, 0.f},
        .Normal = {0.0f,  -1.0f,  0.0f},
    },
    {
        .Position = {-0.5f, -0.5f, -0.5f},
        .Color = {1.f, 0.5f, 0.f},
        .Normal = {0.0f,  -1.0f,  0.0f},
    },
    {
        .Position = {-0.5f, -0.5f, 0.5f},
        .Color = {1.f, 0.5f, 0.f},
        .Normal = {0.0f,  -1.0f,  0.0f},
    },
    };


    static inline std::vector<uint32_t> cubeElements{
    
        0, 1, 3, 1, 2, 3, //front face
        4, 5, 7, 5, 6, 7, //right face
        8, 9, 11, 9, 10, 11, //back face
        12, 13, 15, 13, 14, 15, //left face
        16, 17, 19, 17, 18, 19, //top face
        20, 21, 23, 21, 22, 23, //bottom face
    };

 

};
