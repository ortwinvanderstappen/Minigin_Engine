#pragma once
#include "structs.h"

namespace minigen
{
	class Transform final
	{
	public:
		const Point2f& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y);
	private:
		Point2f m_Position;
	};
}
