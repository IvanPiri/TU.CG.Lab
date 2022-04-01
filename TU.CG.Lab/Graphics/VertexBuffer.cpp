#include "VertexBuffer.hpp"

#include <glad/glad.h>

namespace Graphics
{
	VertexBuffer::VertexBuffer(const void* data, const unsigned size)
	{
		glGenBuffers(1, &id);

		Bind();

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		Unbind();
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
		: id(other.id), attributes(std::move(other.attributes))
	{
		other.id = 0;
		other.attributes = VertexAttributeContainer();
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			Delete();

			id = other.id;
			attributes = other.attributes;

			other.id = 0;
			other.attributes = VertexAttributeContainer();
		}

		return *this;
	}

	VertexBuffer::~VertexBuffer()
	{
		Delete();
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::Delete() const
	{
		glDeleteBuffers(1, &id);
	}
}
