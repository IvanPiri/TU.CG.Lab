#include "ContentManager.hpp"

#include "../Graphics/ModelLoader.hpp"

namespace Utils
{
	Graphics::Texture ContentManager::GetTexture(const std::string& filePath)
	{
		return textureCache.GetTexture(filePath);
	}

	void ContentManager::DeleteTexture(Graphics::Texture& texture)
	{
		textureCache.DeleteTexture(texture);
	}

	Graphics::Model ContentManager::GetModel(
		const std::string& filePath)
	{
		return Graphics::ModelLoader::Load(filePath, textureCache);
	}

	void ContentManager::Clear()
	{
		textureCache.Clear();
	}
}
