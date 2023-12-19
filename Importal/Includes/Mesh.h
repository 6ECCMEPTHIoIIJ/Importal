#pragma once
#include "GlExt.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture.h"
#include "ArrayBuffer.h"
#include <string>
#include <vector>

#include "IndexBuffer.h"

namespace Importal
{
    struct Vertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
    };

    class Mesh {
    public:
        // mesh Data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        // constructor
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
        
        // render the mesh
        void Draw(Shader &shader);

        void Delete();

    private:
        // initializes all the buffer objects/arrays
        void setupMesh();

        std::shared_ptr<ArrayBuffer> ab;
        std::shared_ptr<VertexBuffer> vb;
        std::shared_ptr<IndexBuffer> ib;
    };
};

