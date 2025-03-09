#include "model.h"

void Model::Draw(Shader &shader)
{
}

void Model::loadModel(string path)
{
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                     string typeName)
{
}
