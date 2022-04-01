#pragma once

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

		void Clear();
	};
}
