#ifndef MODEL_H
#define MODEL_H

#include "bettermesh.h"
#include "shaders.h"

#include <../dependencies/glm/glm/glm.hpp>
#include <../dependencies/glm/glm/gtc/matrix_transform.hpp>
#include <../dependencies/glm/glm/gtc/type_ptr.hpp>
#include <../dependencies/stb/include/stb_image.h>
#include <../dependencies/assimp/include/assimp/Importer.hpp>
#include <../dependencies/assimp/include/assimp/scene.h>
#include <../dependencies/assimp/include/assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

class Model {
public:
    Model(const char *path)
    {
        loadModel(path);
    }

    void Draw(Shader &shader);
    void PrintData();
private:
    // model data
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};

#endif
