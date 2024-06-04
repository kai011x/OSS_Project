#include "Framework.h"
#include "GameMath.h"

float GameMath::Clamp(const float& min, const float& max, float value)
{
    if (value < min)
        value = min;

    if (value > max)
        value = max;

    return value;
}


int GameMath::Random(const int& min, const int& max)
{
    return rand() % (max - min) + min;
}
float GameMath::Random(const float& min, const float& max)
{
    float normal = rand() / (float)RAND_MAX;

    return min + (max - min) * normal;
}

float GameMath::Distance2D(Vector3& pos1, Vector3& pos2)
{
    pos1.y = 0.0f;
    pos2.y = 0.0f;

    return Vector3::Distance(pos1, pos2);
}

Vector3 GameMath::ClosestPointOnLine(const Vector3& start, const Vector3& end, const Vector3& point)
{
    Vector3 line = end - start;

    float x = Vector3::Dot(line, point - start);
    float y = Vector3::Dot(line, line);

    float t = Clamp(0.0f,1.0f,x / y);

    return start + line * t;
}