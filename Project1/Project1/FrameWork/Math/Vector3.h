#pragma once

class Vector3
{
public:
	//소멸자 생략
	Vector3(Float3 value) { data = XMLoadFloat3(&value); }
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) { data = XMVectorSet(x, y, z, 0); }
	Vector3(Vector4 value) :data(value) {}

	operator Vector4() { return data; }
	operator Float3()
	{
		Float3 result;
		XMStoreFloat3(&result, data);

		return result;
	}

	void SetX(const float& value) { data = XMVectorSetX(data, value); }
	void SetY(const float& value) { data = XMVectorSetY(data, value); }
	void SetZ(const float& value) { data = XMVectorSetZ(data, value); }

	float GetX() { return XMVectorGetX(data); }
	float GetY() { return XMVectorGetY(data); }
	float GetZ() { return XMVectorGetZ(data); }

	// .x , .y , .z로 값을 가져오는 방법
	_declspec(property(get = GetX, put = SetX)) float x;
	_declspec(property(get = GetY, put = SetY)) float y;
	_declspec(property(get = GetZ, put = SetZ)) float z;

	Vector3 operator+(const Vector3& value)const { return data + value.data; }
	Vector3 operator-(const Vector3& value)const { return data - value.data; }

	void operator+=(const Vector3& value) { data += value.data; }
	void operator-=(const Vector3& value) { data -= value.data; }

	void operator*=(const float& value) { data *= value; }
	void operator/=(const float& value) { data /= value; }

	Vector3 operator*(const float& value) { return data * value; }
	Vector3 operator/(const float& value) { return data / value; }

	Vector3 operator*(const Matrix& value) const { return XMVector3TransformNormal(data, value); }
	void operator*= (const Matrix& value) { data = XMVector3TransformNormal(data, value); }

	bool operator==(const Vector3& value) { return XMVector3Equal(data, value.data); }

	// 앞뒤 바뀐경우 대비 float  + Vector3의 경우
	friend Vector3 operator+(const Float3& value1, const Vector3& value2) { return value2 + value1; }
	friend Vector3 operator-(const Float3& value1, const Vector3& value2) { return value2 - value1; }
	friend Vector3 operator+(const float& value1, const Vector3& value2) { return value2.data * value1; }
	friend Vector3 operator/(const float& value1, const Vector3& value2) { return value2.data / value1; }
	friend void operator+=(Float3& value1,const Vector3& value2) { 
		XMVECTOR temp = XMLoadFloat3(&value1) + value2.data; 
		XMStoreFloat3(&value1, temp);
	}
	friend void operator-=(Float3& value1, const Vector3& value2) {
		XMVECTOR temp = XMLoadFloat3(&value1) - value2.data;
		XMStoreFloat3(&value1, temp);
	}

	float operator[](const UINT& index) const
	{
		switch (index){
		case 0:
			return XMVectorGetX(data);
		case 1:
			return XMVectorGetY(data);
		case 2:
			return XMVectorGetZ(data);
		}
	}

//	void Normalize() { data = XMVector3Normalize(data); }	// 헷깔릴까봐
	Vector3 Normalize() { return XMVector3Normalize(data); }
	float length() { return XMVectorGetX(XMVector3Length(data)); }
	Vector4* GetData() { return &data; }

	static Vector3 Cross(const Vector3& vec1, const Vector3& vec2){return XMVector3Cross(vec1.data, vec2.data);}
	static float Dot(const Vector3& vec1, const Vector3& vec2) { return XMVectorGetX(XMVector3Dot(vec1.data, vec2.data)); }
	static float Distance(const Vector3& vec1, const Vector3& vec2)
	{
		return (vec1 - vec2).length();
	}


private:
	// Vector4은 각항에 접근이 너무 어려움
	Vector4 data;
};