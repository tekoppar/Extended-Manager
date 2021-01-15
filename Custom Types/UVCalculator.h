#pragma once

enum class Facing { Up, Forward, Right };

class UvCalculator
{
public:
    static std::vector<tem::Vector2> CalculateUVs(std::vector<tem::Vector3> v/*vertices*/, float scale)
    {
        std::vector<tem::Vector2> uvs;
        uvs.reserve(v.size());

        for (int i = 0; i < v.size(); i += 3)
        {
            int i0 = i;
            int i1 = i + 1;
            int i2 = i + 2;

            tem::Vector3 v0 = v[i0];
            tem::Vector3 v1 = v[i1];
            tem::Vector3 v2 = v[i2];

            tem::Vector3 side1 = v1 - v0;
            tem::Vector3 side2 = v2 - v0;
            tem::Vector3 direction = app::Vector3_Cross(side1.ToMoon(), side2.ToMoon(), NULL);
            Facing facing = FacingDirection(direction);
            switch (facing)
            {
                case Facing::Forward:
                    uvs.push_back(ScaledUV(v0.X, v0.Y, scale));
                    uvs.push_back(ScaledUV(v1.X, v1.Y, scale));
                    uvs.push_back(ScaledUV(v2.X, v2.Y, scale));
                    break;
                case Facing::Up:
                    uvs.push_back(ScaledUV(v0.X, v0.Z, scale));
                    uvs.push_back(ScaledUV(v1.X, v1.Z, scale));
                    uvs.push_back(ScaledUV(v2.X, v2.Z, scale));
                    break;
                case Facing::Right:
                    uvs.push_back(ScaledUV(v0.Y, v0.Z, scale));
                    uvs.push_back(ScaledUV(v1.Y, v1.Z, scale));
                    uvs.push_back(ScaledUV(v2.Y, v2.Z, scale));
                    break;
            }
        }
        return uvs;
    }

private:
    static bool FacesThisWay(tem::Vector3 v, tem::Vector3 dir, Facing p, float& maxDot, Facing& ret)
    {
        float t = app::Vector3_Dot(v.ToMoon(), dir.ToMoon(), NULL);
        if (t > maxDot)
        {
            ret = p;
            maxDot = t;
            return true;
        }
        return false;
    }

    static Facing FacingDirection(tem::Vector3 v)
    {
        Facing ret = Facing::Up;
        float maxDot = -std::numeric_limits<float>::infinity();

        if (!FacesThisWay(v, tem::Vector3::Right, Facing::Right, maxDot, ret))
            FacesThisWay(v, tem::Vector3::Left, Facing::Right, maxDot, ret);

        if (!FacesThisWay(v, tem::Vector3::Forward, Facing::Forward, maxDot, ret))
            FacesThisWay(v, tem::Vector3::Back, Facing::Forward, maxDot, ret);

        if (!FacesThisWay(v, tem::Vector3::Up, Facing::Up, maxDot, ret))
            FacesThisWay(v, tem::Vector3::Down, Facing::Up, maxDot, ret);

        return ret;
    }

    static  tem::Vector2 ScaledUV(float uv1, float uv2, float scale)
    {
        return tem::Vector2(uv1 / scale, uv2 / scale);
    }
};