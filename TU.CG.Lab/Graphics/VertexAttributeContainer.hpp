#pragma once

#include <string>
#include <vector>

namespace Graphics
{
	enum class VertexAttributeType : int
	{
		FLOAT,
		VEC2F,
		VEC3F,
		MAT3F,
		MAT4F,
	};

	struct VertexAttribute
	{
		std::string name;
		VertexAttributeType type;
		unsigned size;
		unsigned offset;

		VertexAttribute(std::string name, VertexAttributeType type);

		[[nodiscard]] unsigned GetSizeOfType() const;
		[[nodiscard]] unsigned GetComponentCount() const;
		[[nodiscard]] unsigned GetComponentGLType() const;
	};

	class VertexAttributeContainer
	{
	private:
		std::vector<VertexAttribute> attributes;
		unsigned stride = 0;

		VertexAttributeContainer() = default;

		friend class VertexBuffer;
	public:
		using iterator = std::vector<VertexAttribute>::iterator;
		using const_iterator = std::vector<VertexAttribute>::const_iterator;

		VertexAttributeContainer(std::initializer_list<VertexAttribute> attributes);

		[[nodiscard]] unsigned GetStride() const { return stride; }

		iterator begin() { return attributes.begin(); }
		iterator end() { return attributes.end(); }

		[[nodiscard]] const_iterator begin() const { return attributes.begin(); }
		[[nodiscard]] const_iterator end() const { return attributes.end(); }
	};
}
