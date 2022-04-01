#include "ContentManager.hpp"

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

	void ContentManager::Clear()
	{
		textureCache.Clear();
	}
}
