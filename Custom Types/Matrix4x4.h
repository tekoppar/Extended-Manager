#pragma once

namespace tem {
	class Matrix4x4
	{
	public:
		float m00; // 0x00
		float m10; // 0x04
		float m20; // 0x08
		float m30; // 0x0C
		float m01; // 0x10
		float m11; // 0x14
		float m21; // 0x18
		float m31; // 0x1C
		float m02; // 0x20
		float m12; // 0x24
		float m22; // 0x28
		float m32; // 0x2C
		float m03; // 0x30
		float m13; // 0x34
		float m23; // 0x38
		float m33; // 0x3C

		Matrix4x4()
		{
			m00 = m10 = m20 = m30 = m01 = m11 = m21 = m31 = m02 = m12 = m22 = m32 = m03 = m13 = m23 = m33 = 0.0f;
		}

		Matrix4x4(float matrix)
		{
			m00 = m10 = m20 = m30 = m01 = m11 = m21 = m31 = m02 = m12 = m22 = m32 = m03 = m13 = m23 = m33 = matrix;
		}

		Matrix4x4(app::Matrix4x4* value)
		{
			m00 = value->m00;
			m10 = value->m01;
			m20 = value->m02;
			m30 = value->m03;
			m01 = value->m10;
			m11 = value->m11;
			m21 = value->m12;
			m31 = value->m13;
			m02 = value->m20;
			m12 = value->m21;
			m22 = value->m22;
			m32 = value->m23;
			m03 = value->m30;
			m13 = value->m31;
			m23 = value->m32;
			m33 = value->m33;
		}

		app::Matrix4x4 ToMoon()
		{
			app::Matrix4x4 value = app::Matrix4x4();
			value.m00 = m00;
			value.m01 = m01;
			value.m02 = m02;
			value.m03 = m03;
			value.m10 = m10;
			value.m11 = m11;
			value.m12 = m12;
			value.m13 = m13;
			value.m20 = m20;
			value.m21 = m21;
			value.m22 = m22;
			value.m23 = m23;
			value.m30 = m30;
			value.m31 = m31;
			value.m32 = m32;
			value.m33 = m33;

			return value;
		}

		app::Matrix4x4* ToMoonP()
		{
			app::Matrix4x4* value = (app::Matrix4x4*)il2cpp_object_new((Il2CppClass*)(*app::Matrix4x4__TypeInfo));
			value->m00 = m00;
			value->m01 = m01;
			value->m02 = m02;
			value->m03 = m03;
			value->m10 = m10;
			value->m11 = m11;
			value->m12 = m12;
			value->m13 = m13;
			value->m20 = m20;
			value->m21 = m21;
			value->m22 = m22;
			value->m23 = m23;
			value->m30 = m30;
			value->m31 = m31;
			value->m32 = m32;
			value->m33 = m33;

			return value;
		}

		Matrix4x4(std::string& other)
		{
			std::string temp = other;
			auto content = sutil::SplitTem(temp, ",");
			m00 = m10 = m20 = m30 = m01 = m11 = m21 = m31 = m02 = m12 = m22 = m32 = m03 = m13 = m23 = m33 = 0.0f;

			if (content.size() > 0)
				m00 = std::stof(content[0]);

			if (content.size() > 1)
				m10 = std::stof(content[1]);

			if (content.size() > 2)
				m20 = std::stof(content[2]);

			if (content.size() > 3)
				m30 = std::stof(content[3]);

			if (content.size() > 4)
				m01 = std::stof(content[4]);

			if (content.size() > 5)
				m11 = std::stof(content[5]);

			if (content.size() > 6)
				m21 = std::stof(content[6]);

			if (content.size() > 7)
				m31 = std::stof(content[7]);

			if (content.size() > 8)
				m02 = std::stof(content[8]);

			if (content.size() > 9)
				m12 = std::stof(content[9]);

			if (content.size() > 10)
				m22 = std::stof(content[10]);

			if (content.size() > 11)
				m32 = std::stof(content[11]);

			if (content.size() > 12)
				m03 = std::stof(content[12]);

			if (content.size() > 13)
				m13 = std::stof(content[13]);

			if (content.size() > 14)
				m23 = std::stof(content[14]);

			if (content.size() > 15)
				m33 = std::stof(content[15]);
		}

		std::string ToString()
		{
			return std::to_string(m00) + ", " + std::to_string(m01) + ", " + std::to_string(m02) + ", " + std::to_string(m03) + ", " +
				std::to_string(m10) + ", " + std::to_string(m11) + ", " + std::to_string(m12) + ", " + std::to_string(m13) + ", " +
				std::to_string(m20) + ", " + std::to_string(m21) + ", " + std::to_string(m22) + ", " + std::to_string(m23) + ", " +
				std::to_string(m30) + ", " + std::to_string(m31) + ", " + std::to_string(m32) + ", " + std::to_string(m33);
		}
	};
}