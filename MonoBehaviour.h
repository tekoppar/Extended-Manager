#pragma once

#include "HString.h"
#include "Behaviour.h"

#pragma pack(push, 1)
namespace Moon {
	class MonoBehaviour : public virtual Moon::Behaviour
	{
	public:

		Moon::HString* GetScriptClassName()
		{
			auto GetScriptClassName_address = Assembly_BaseAddr + 0x234CCB0;
			using __GetScriptClassName = Moon::HString * (*)(Moon::MonoBehaviour*);
			auto GetScriptClassName = reinterpret_cast<__GetScriptClassName>(GetScriptClassName_address);
			return GetScriptClassName(this);
		}
	protected:
	private:

	};
}
#pragma pack(pop)
