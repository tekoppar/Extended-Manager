#pragma once

#ifndef _BOUNDS_H
#define _BOUNDS_H

#include "StringUtils.h"
#include "Vector3.h"

namespace tem {
	class Bounds {
	public:
		tem::Vector3 Center;
		tem::Vector3 Extents;

		Bounds(tem::Vector3 Center, tem::Vector3 Extents)
		{
			this->Center = Center;
			this->Extents = Extents;
		}

		Bounds(app::Bounds* other)
		{
			if (other != nullptr)
			{
				this->Center = other->m_Center;
				this->Extents = other->m_Extents;
			}
			else
			{
				this->Center = tem::Vector3(0.0f);
				this->Extents = tem::Vector3(0.0f);
			}
		}

		Bounds(tem::Bounds& other)
		{
			this->Center = other.Center;
			this->Extents = other.Extents;
		}

		Bounds(std::string& other)
		{
			std::string temp = other;
			auto content = sutil::SplitTem(temp, ";");
			this->Center = tem::Vector3(0.0f);
			this->Extents = tem::Vector3(0.0f);

			if (content.size() > 0)
				this->Center = tem::Vector3(content[0]);

			if (content.size() > 1)
				this->Extents = tem::Vector3(content[1]);
		}

		app::Bounds ToMoon()
		{
			auto Class = GetClass("UnityEngine", "Bounds");
			app::Bounds* moon = (app::Bounds*)il2cpp_object_new(Class);
			moon->m_Center = this->Center.ToMoon();
			moon->m_Extents = this->Extents.ToMoon();

			return *moon;
		}

		app::Bounds* ToMoonP()
		{
			auto Class = GetClass("UnityEngine", "Bounds");
			app::Bounds* moon = (app::Bounds*)il2cpp_object_new(Class);
			moon->m_Center = this->Center.ToMoon();
			moon->m_Extents = this->Extents.ToMoon();

			return moon;
		}

		std::string ToString()
		{
			return this->Center.ToString() + ";" + this->Extents.ToString();
		}
	};
}

#endif