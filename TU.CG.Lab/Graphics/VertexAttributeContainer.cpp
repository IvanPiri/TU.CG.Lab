#include "VertexAttributeContainer.hpp"

#include <glad/glad.h>

namespace Graphics
{
	VertexAttribute::VertexAttribute(std::string name, const VertexAttributeType type)
		: name(std::move(name)), type(type), size(GetSizeOfType()), offset(0)
	{
	}

	unsigned VertexAttribute::GetSizeOfType() const
	{
		switch (type)
		{
			case VertexAttributeType::FLOAT:
				return sizeof(float);
			case VertexAttributeType::VEC2F:
				return 2 * sizeof(float);
			case VertexAttributeType::VEC3F:
				return 3 * sizeof(float);
			case VertexAttributeType::MAT3F:
				return 9 * sizeof(float);
			case VertexAttributeType::MAT4F:
				return 16 * sizeof(float);
		}

		const std::string errorMessage = "Unhandled Vertex attribute type { " +
			std::to_string(static_cast<int>(type)) + " }";

		throw std::exception(errorMessage.c_str());
	}

	unsigned VertexAttribute::GetComponentCount() const
	{
		switch (type)
		{
			case VertexAttributeType::FLOAT:
				return 1;
			case VertexAttributeType::VEC2F:
				return 2;
			case VertexAttributeType::VEC3F:
				return 3;
			case VertexAttributeType::MAT3F:
				return 9;
			case VertexAttributeType::MAT4F:
				return 16;
		}

		const std::string errorMessage = "Unhandled Vertex attribute type { " +
			std::to_string(static_cast<int>(type)) + " }";

		throw std::exception(errorMessage.c_str());
	}

	unsigned VertexAttribute::GetComponentGLType() const
	{
		switch (type)
		{
			case VertexAttributeType::FLOAT:
			case VertexAttributeType::VEC2F:
			case VertexAttributeType::VEC3F:
			case VertexAttributeType::MAT3F:
			case VertexAttributeType::MAT4F:
				return GL_FLOAT;
		}

		const std::string errorMessage = "Unhandled Vertex attribute type { " +
			std::to_string(static_cast<int>(type)) + " }";

		throw std::exception(errorMessage.c_str());
	}

	VertexAttributeContainer::VertexAttributeContainer(
		const std::initializer_list<VertexAttribute> attributes)
		: attributes(attributes)
	{
		unsigned offset = 0;

		for (auto& attribute : this->attributes)
		{
			attribute.offset = offset;
			offset += attribute.size;
			stride += attribute.size;
		}
	}
}
