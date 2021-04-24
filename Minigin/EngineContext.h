#pragma once
#include "Singleton.h"

namespace minigen {
	class Renderer;

	class EngineContext final: public Singleton<EngineContext>
	{
	public:
		Renderer* GetRenderer() const;
	protected:
		EngineContext() = default;
	private:
		Renderer* m_pRenderer = nullptr;
	};
}

