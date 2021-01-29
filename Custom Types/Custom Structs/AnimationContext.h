#pragma once

namespace tem {
	class AnimationContext 
	{
	public:
		float NormalizedTime;
		bool ShouldRecord;

		AnimationContext()
		{
			NormalizedTime = 0.0f;
			ShouldRecord = false;
		}

		AnimationContext(float time, bool record)
		{
			NormalizedTime = time;
			ShouldRecord = record;
		}

		AnimationContext(app::AnimationContext* value)
		{
			this->NormalizedTime = value->NormalizedTime;
			this->ShouldRecord = value->_ShouldRecord_k__BackingField;
		}

		app::AnimationContext ToMoon()
		{
			app::AnimationContext* moon = (app::AnimationContext*)il2cpp_object_new((Il2CppClass*)(*app::AnimationContext__TypeInfo));
			moon->NormalizedTime = this->NormalizedTime;
			moon->_ShouldRecord_k__BackingField = this->ShouldRecord;

			return *moon;
		}

		app::AnimationContext* ToMoonP()
		{
			app::AnimationContext* moon = (app::AnimationContext*)il2cpp_object_new((Il2CppClass*)(*app::AnimationContext__TypeInfo));
			moon->NormalizedTime = this->NormalizedTime;
			moon->_ShouldRecord_k__BackingField = this->ShouldRecord;

			return moon;
		}

		std::string ToString()
		{
			return std::to_string(this->NormalizedTime) + ", " + std::to_string(this->ShouldRecord);
		}
	};
}