#include "VertexArray.hpp"

#include <glad/glad.h>

namespace Graphics
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &id);
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept
		: id(other.id), vbo(std::move(other.vbo)), ebo(std::move(other.ebo))
	{
		other.id = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		if (this != &other)
		{
			Delete();

			id = other.id;
			vbo = std::move(other.vbo);
			ebo = std::move(other.ebo);

			other.id = 0;
		}

		return *this;
	}

	VertexArray::~VertexArray()
	{
		Delete();
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(id);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetVertexBuffer(std::unique_ptr<VertexBuffer> vb)
	{
		if (vb == nullptr)
			throw std::exception("Vertex Buffer cannot be a nullptr.");

		Bind();
		vb->Bind();

		const auto& attributes = vb->GetAttributeContainer();

		int i = 0;

		for (const auto& attribute : attributes)
		{
			const unsigned count = attribute.GetComponentCount();
			const unsigned glType = attribute.GetComponentGLType();
			const unsigned stride = attributes.GetStride();

			glVertexAttribPointer(
				i, count, glType, GL_FALSE, stride, reinterpret_cast<void*>(attribute.offset));

			glEnableVertexAttribArray(i);

			++i;
		}

		vbo = std::move(vb);
	}

	void VertexArray::SetElementBuffer(std::unique_ptr<ElementBuffer> eb)
	{
		if (eb == nullptr)
			throw std::exception("Element Buffer cannot be a nullptr.");

		Bind();
		eb->Bind();

		ebo = std::move(eb);
	}

	void VertexArray::Delete() const
	{
		glDeleteVertexArrays(1, &id);
	}
}
