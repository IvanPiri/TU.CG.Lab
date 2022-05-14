#pragma once

#include <string>

namespace Graphics
{
	class Texture
	{
	private:
		unsigned id = 0;

		unsigned width = 0;
		unsigned height = 0;

		std::string filePath;
		std::string fileNameWithoutExtension;

		friend class TextureCache;
	public:
		Texture(
			unsigned id, unsigned width, unsigned height,
			std::string filePath, std::string fileNameWithoutExt);

		void BindAndActivate(unsigned textureSlot) const;

		[[nodiscard]] unsigned GetWidth() const { return width; }
		[[nodiscard]] unsigned GetHeight() const { return height; }
		[[nodiscard]] std::string GetFilePath() const { return filePath; }
		[[nodiscard]] std::string GetFileNameWithoutExtension() const { return fileNameWithoutExtension; }
	};
}
