#pragma once
// GlobalBuffer

class MatrixBuffer : public ConstantBuffer
{
private:
	struct Data
	{
		Matrix matrix;
	};

public:
	MatrixBuffer() :ConstantBuffer(&data, sizeof(Data))
	{
		data.matrix = XMMatrixIdentity();
	}

	void Set(Matrix value)
	{
		data.matrix = XMMatrixTranspose(value);
	}

private:
	Data data;
};

// �� ���� ����
class ColorBuffer : public ConstantBuffer
{
private:
	struct Data
	{
		Float4 color;
	};

public:
	ColorBuffer() :ConstantBuffer(&data, sizeof(Data))
	{
		data.color = { 1.0f,1.0f,1.0f,1.0f };
	}

	void Set(float r, float g, float b, float a = 1.0f)
	{
		data.color = { r,g,b,a };
	}

private:
	Data data;
};

class LightBuffer : public ConstantBuffer
{
private:
	struct Data
	{
		Float3 lightDir;	// ������(���ݻ� : diffuse) + (���ݻ� : specular)
		float shininess;	// ���ݻ� ���� ����
		Float4 ambient;		// ������(ambient)
	};

public:
	LightBuffer() :ConstantBuffer(&data, sizeof(Data))
	{
		data.lightDir = { 0.0f,-1.0f,1.0f};
		data.shininess = 24.0f;
		data.ambient = { 0.1f,0.1f,0.1f,1.0f };
	}

	Float3& GetLightDir() { return data.lightDir; }
	float& GetShininess() { return data.shininess; }
	Float4& GetAmbient() { return data.ambient; }
private:
	Data data;
};


class ViewBuffer : public ConstantBuffer
{
private:
	struct Data
	{
		Matrix view;
		Matrix invView;	// inverse View
	};

public:
	ViewBuffer() :ConstantBuffer(&data, sizeof(Data))
	{
		data.view = XMMatrixIdentity();
		data.invView = XMMatrixIdentity();
	}

	void Set(Matrix view, Matrix invView)
	{
		data.view = XMMatrixTranspose(view);
		data.invView = XMMatrixTranspose(invView);
	}

private:
	Data data;
};

class FloatValueBuffer : public ConstantBuffer
{
public:
	FloatValueBuffer() :ConstantBuffer(values, sizeof(float) * 4 )
	{
	}

	float values[4] = {};
};

/*============================================ �������� �� =======================================================*/
class CameraBuffer : public ConstantBuffer
{
public:
	struct  Data
	{
		Float3 camera_Pos = { 0,0,0 };
		float lenght = 100.0f;
	}data;

	CameraBuffer() : ConstantBuffer(&data, sizeof(Data)) {}
};

class MosterLightBuffer : public ConstantBuffer
{
public:
	struct  Data
	{
		Float4 monster_Pos[3];	// rgb���̸� w���� ���������� �ƴ����� ��Ÿ������
	}data;

	MosterLightBuffer() : ConstantBuffer(&data, sizeof(Data)) {}
};
