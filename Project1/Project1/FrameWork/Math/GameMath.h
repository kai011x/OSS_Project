#pragma once

namespace GameMath
{
    float Clamp(const float& min, const float& max, float value);

    int Random(const int& min, const int& max);
    float Random(const float& min, const float& max);

    float Distance2D(Vector3& pos1, Vector3& pos2);

    Vector3 ClosestPointOnLine(const Vector3& start, const Vector3& end, const Vector3& point);
}