#pragma once

#include "../Graphics/Model.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/TextureCache.hpp"

namespace Utils
{
	class ContentManager
	{
	private:
		Graphics::TextureCache textureCache;
	public:
		Graphics::Texture GetTexture(const std::string& filePath);
		void DeleteTexture(Graphics::Texture& texture);

		Graphics::Model GetModel(const std::string& filePath);

		void Clear();
	};
}
