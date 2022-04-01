#pragma once

#include <string>

namespace Graphics
{
	class Texture
	{
	private:
		unsigned id = 0;

		int width = 0;
		int height = 0;

		std::string name;

		friend class TextureCache;
	public:
		Texture(unsigned id, int width, int height, std::string name);

		void BindAndActivate(unsigned textureSlot) const;

		[[nodiscard]] int GetWidth() const { return width; }
		[[nodiscard]] int GetHeight() const { return height; }
		[[nodiscard]] std::string GetName() const { return name; }
	};
}
