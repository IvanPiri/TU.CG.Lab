#include "Texture.hpp"

#include <glad/glad.h>

namespace Graphics
{
	Texture::Texture(
		const unsigned id, const unsigned width, const unsigned height,
		std::string filePath, std::string fileNameWithoutExt)
		: id(id), width(width), height(height), filePath(std::move(filePath)),
		fileNameWithoutExtension(std::move(fileNameWithoutExt))
	{
	}

	void Texture::BindAndActivate(const unsigned textureSlot) const
	{
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, id);
	}
}
