#include"Matrix4.h"
#include"Vector3.h"
#include<cmath>

//単位行列の生成
Matrix4 identity()
{
	static const Matrix4 result
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return result;
}

//拡大縮小行列の生成
Matrix4 scale(const Vector3 &s)
{
	Matrix4 result
	{
		s.x,0.0f,0.0f,0.0f,
		0.0f,s.y,0.0f,0.0f,
		0.0f,0.0f,s.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return result;
}

//x軸まわりの回転行列の生成
Matrix4 rotateX(float angle)
{
	float sin = std::sin(angle);
	float cos = std::cos(angle);

	Matrix4 result
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f, cos, sin,0.0f,
		0.0f,-sin, cos,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return result;
}

//y軸まわりの回転行列の生成
Matrix4 rotateY(float angle)
{
	float sin = std::sin(angle);
	float cos = std::cos(angle);

	Matrix4 result
	{
		cos,0.0f,-sin,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		sin,0.0f,cos,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return result;
}

//z軸まわりの回転行列の生成
Matrix4 rotateZ(float angle)
{
	float sin = std::sin(angle);
	float cos = std::cos(angle);

	Matrix4 result
	{
		cos,sin,0.0f,0.0f,
		-sin,cos,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return result;
}

//平行移動行列の生成
Matrix4 translate(const Vector3 &t)
{
	Matrix4 result
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		t.x,t.y,t.z,1.0f
	};

	return result;
}

//座標変換（ベクトルと行列の掛け算）を行う＊透視変換にも対応している
Vector3 transform(const Vector3 &v, const Matrix4 &m)
{
	float w = v.x * m.r[0].m128_f32[3] + v.y * m.r[1].m128_f32[3] + v.z * m.r[2].m128_f32[3] + m.r[3].m128_f32[3];

	Vector3 result
	{
		(v.x * m.r[0].m128_f32[0] + v.y * m.r[1].m128_f32[0] + v.z * m.r[2].m128_f32[0] + m.r[3].m128_f32[0]) / w,
		(v.x * m.r[0].m128_f32[1] + v.y * m.r[1].m128_f32[1] + v.z * m.r[2].m128_f32[1] + m.r[3].m128_f32[1]) / w,
		(v.x * m.r[0].m128_f32[2] + v.y * m.r[1].m128_f32[2] + v.z * m.r[2].m128_f32[2] + m.r[3].m128_f32[2]) / w
	};

	return result;
}

//代入演算子*=のオーバーロード関数(行列と行列の積)
Matrix4 &operator*=(Matrix4 &m1, const Matrix4 &m2)
{
	DirectX::XMMATRIX result{ 0 };
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result.r[i].m128_f32[j] += m1.r[i].m128_f32[k] * m2.r[k].m128_f32[j];
			}
		}
	}
	m1 = result;
	return m1;
}

////2項演算子*のオーバーロード関数（行列と行列の積）
//Matrix4 operator*(const Matrix4 &m1, const Matrix4 &m2)
//{
//	DirectX::XMMATRIX result = m1;
//
//	return result *= m2;
//}

//2項演算子*のオーバーロード関数（ベクトルと行列の積）
Vector3 operator*(const Vector3 &v, const Matrix4 &m)
{
	return transform(v, m);
}
