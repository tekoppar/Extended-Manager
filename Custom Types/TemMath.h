#pragma once

#include <math.h>
#include <algorithm>

namespace tem {
	static float Angle(tem::Vector2 a, tem::Vector2 b) {
        float x = atan2(a.y - b.y, a.x - b.x);
        return (x > 0.0f ? x : (2.0f * PI + x)) * 360.0f / (2.0f * PI);
    }

    static float Angle(float ax, float ay, float bx, float by) {
        float x = atan2(ay - by, ax - bx);
        return (x > 0.0f ? x : (2.0f * PI + x)) * 360.0f / (2.0f * PI);
    }

    static float Angle(tem::Vector3 a, tem::Vector3 b) {
        float x = atan2(a.Y - b.Y, a.X - b.X);
        return (x > 0.0f ? x : (2.0f * PI + x)) * 360.0f / (2.0f * PI);
    }

    static float AngleDiff(tem::Vector2 x, tem::Vector2 y, tem::Vector2 z) {
        float a1 = tem::Angle(x, y);
        float a2 = tem::Angle(y, z);
        float diff = std::abs(a1 - a2);
        return diff <= 180.0f ? diff : 360.0f - diff;
    }

    static float AngleDiff(tem::Vector3 x, tem::Vector3 y, tem::Vector3 z) {
        float a1 = tem::Angle(x, y);
        float a2 = tem::Angle(y, z);
        float diff = std::abs(a1 - a2);
        return diff <= 180.0f ? diff : 360.0f - diff;
    }

    static float MapRange(float value, float inMin, float inMax, float outMin, float outMax) {
        return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    }

    static int MapRange(int value, int inMin, int inMax, int outMin, int outMax) {
        return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    }
}