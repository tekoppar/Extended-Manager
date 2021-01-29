#pragma once

namespace tem {
	class ExplosionSettings
	{
	public:
		tem::Vector3 Postion;
		float Radius;
		tem::Vector3 Force;
		float RadialForce;
		float RandomForce;
		float Torque;
		float RandomTorque;

		ExplosionSettings()
		{
			Postion = tem::Vector3();
			Radius = 0.0f;
			Force = tem::Vector3();
			RadialForce = 0.0f;
			RandomForce = 0.0f;
			Torque = 0.0f;
			RandomTorque = 0.0f;
		}

		ExplosionSettings(tem::Vector3 postion, float radius, tem::Vector3 force, float radialForce, float randomForce, float torque, float randomTorque)
		{
			Postion = postion;
			Radius = radius;
			Force = force;
			RadialForce = radialForce;
			RandomForce = randomForce;
			Torque = torque;
			RandomTorque = randomTorque;
		}

		ExplosionSettings(app::ApplyForceToPhysicsSystem_ExplosionSettings* value)
		{
			Postion = value->postion;
			Radius = value->radius;
			Force = value->force;
			RadialForce = value->radialForce;
			RandomForce = value->randomForce;
			Torque = value->torque;
			RandomTorque = value->randomTorque;
		}

		app::ApplyForceToPhysicsSystem_ExplosionSettings ToMoon()
		{
			app::ApplyForceToPhysicsSystem_ExplosionSettings value = app::ApplyForceToPhysicsSystem_ExplosionSettings();
			value.postion = Postion.ToMoon();
			value.radius = Radius;
			value.force = Force.ToMoon();
			value.radialForce = RadialForce;
			value.randomForce = RandomForce;
			value.torque = Torque;
			value.randomTorque = RandomTorque;

			return value;
		}

		std::string ToString()
		{
			return this->Postion.ToString() + ", " + std::to_string(this->Radius) + ", " + this->Force.ToString() + ", " + std::to_string(this->RadialForce) + ", " +
				std::to_string(this->RandomForce) + ", " + std::to_string(this->Torque) + ", " + std::to_string(this->RandomTorque);
		}
	};
}