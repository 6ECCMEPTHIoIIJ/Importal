#include "Mesh.h"

namespace Importal
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    void Mesh::Draw(Shader& shader)
    {
        ab.Bind();
        
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (int i = 0; i < textures.size(); i++)
        {
            std::string number;
            std::string name = textures[i].GetType();
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to string
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to string
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to string
        
            // now set the sampler to the correct texture unit
            shader.SetInt((name + number), i);
            // and finally bind the texture
            textures[i].Bind(i);
        }
        
        // draw mesh
        
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
        ArrayBuffer::Unbind();
        
        // always good practice to set everything back to defaults once configured.
        // glActiveTexture(GL_TEXTURE0);
    }

    void Mesh::setupMesh()
    {
        // create buffers/arrays
        ab.Bind();
        VertexBuffer vb(&vertices[0], vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
        IndexBuffer ib(&indices[0], indices.size() * sizeof(unsigned int), GL_STATIC_DRAW);

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);

        ab.AddBuffer(vb, layout);

        VertexBuffer::Unbind();
        ArrayBuffer::Unbind();
        IndexBuffer::Unbind();
    }
}
