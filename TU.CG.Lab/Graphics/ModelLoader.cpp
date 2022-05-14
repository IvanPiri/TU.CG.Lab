#include "ModelLoader.hpp"

#include <filesystem>
#include <vector>
#include <assimp/postprocess.h>

namespace Graphics
{
	Model ModelLoader::Load(
		const std::string& modelFilePath, TextureCache& textureCache)
	{
		Assimp::Importer importer;

		constexpr auto flags = aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |aiProcess_FlipUVs;

		const aiScene* scene = importer.ReadFile(modelFilePath, flags);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::string errorMessage = "Could not load model: ";
			errorMessage.append(importer.GetErrorString());

			throw std::exception(errorMessage.c_str());
		}

		const std::string modelDirectory = std::filesystem::path(modelFilePath).parent_path().string();

		std::vector<Mesh> meshes;
		meshes.reserve(scene->mNumMeshes);

		ProcessNode(scene->mRootNode, scene, meshes, modelDirectory, textureCache);

		return Model(std::move(meshes));
	}

	void ModelLoader::ProcessNode(
		const aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes,
		const std::string& modelDirectory, TextureCache& textureCache)
	{
		for (unsigned i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];
			Mesh ourMesh = ProcessMesh(assimpMesh, scene, modelDirectory, textureCache);

			meshes.push_back(std::move(ourMesh));
		}

		for (unsigned i = 0; i < node->mNumChildren; ++i)
			ProcessNode(node->mChildren[i], scene, meshes, modelDirectory, textureCache);
	}

	Mesh ModelLoader::ProcessMesh(
		aiMesh* mesh, const aiScene* scene,
		const std::string& modelDirectory, TextureCache& textureCache)
	{
		std::vector<Vertex> vertices;
		vertices.reserve(mesh->mNumVertices);

		std::vector<unsigned> indices;
		std::vector<Texture> textures;

		Vertex vertex{};
		glm::vec3 vector{};

		for (unsigned i = 0; i < mesh->mNumVertices; ++i)
		{
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;

			if (mesh->mTextureCoords[0])
			{
				vector.x = mesh->mTextureCoords[0][i].x;
				vector.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = glm::vec2(vector);
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f);
			}

			vertices.push_back(vertex);
		}

		for (unsigned i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];

			for (unsigned j = 0; j < face.mNumIndices; ++j)
				indices.push_back(face.mIndices[j]);
		}

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = LoadMaterialTextures(
			material, aiTextureType_DIFFUSE, modelDirectory, textureCache);
		std::vector<Texture> specularMaps = LoadMaterialTextures(
			material, aiTextureType_SPECULAR, modelDirectory, textureCache);

		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		auto result = Mesh(vertices, indices, textures);

		return result;
	}

	std::vector<Texture> ModelLoader::LoadMaterialTextures(
		const aiMaterial* mat, aiTextureType type,
		const std::string& modelDirectory, TextureCache& textureCache)
	{
		const unsigned textureCount = mat->GetTextureCount(type);

		std::vector<Texture> textures;
		textures.reserve(textureCount);

		for (unsigned i = 0; i < textureCount; ++i)
		{
			aiString texturePath;
			mat->GetTexture(type, i, &texturePath);

			Texture texture = textureCache.GetTexture(
				modelDirectory + "/" + texturePath.C_Str());
			textures.push_back(texture);
		}

		return textures;
	}
}
