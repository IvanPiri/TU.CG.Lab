#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>
#include <vector>

#include "Mesh.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "TextureCache.hpp"

namespace Graphics
{
	class ModelLoader
	{
	private:
		static void ProcessNode(
			const aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes,
			const std::string& modelDirectory, TextureCache& textureCache);

		static Mesh ProcessMesh(
			aiMesh* mesh, const aiScene* scene,
			const std::string& modelDirectory, TextureCache& textureCache);

		static std::vector<Texture> LoadMaterialTextures(
			const aiMaterial* mat, aiTextureType type,
			const std::string& modelDirectory, TextureCache& textureCache);
	public:
		static Model Load(
			const std::string& modelFilePath, TextureCache& textureCache);
	};
}
