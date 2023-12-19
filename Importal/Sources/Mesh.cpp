#include "Mesh.h"

namespace Importal
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, const std::vector<Texture>& textures)
        : vertices(vertices), indices(indices), textures(textures)
    {
        ab = std::make_shared<ArrayBuffer>();
        ab->Bind();
        vb = std::make_shared<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
        ib = std::make_shared<IndexBuffer>(indices.data(), indices.size(), GL_STATIC_DRAW);
        setupMesh();
    }

    void Mesh::Delete()
    {
        for(auto& texture: textures)
        {
            texture.Delete();
        }
    }

    void Mesh::Draw(Shader& shader)
    {
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

        ab->Bind();
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
        ArrayBuffer::Unbind();
        
        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

    void Mesh::setupMesh()
    {
        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);
        ab->AddBuffer(vb, layout);


        ab->Unbind();
        vb->Unbind();
        ib->Unbind();
    }
}
