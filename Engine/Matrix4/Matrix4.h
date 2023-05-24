#pragma once

#include<DirectXMath.h>
#include"Vector3.h"

//MATRIX�^��Matrix4�^�Ƃ��Ĉ��� ���݊����̊m��&�g���̂���
using Matrix4 = DirectX::XMMATRIX;

//�P�ʍs����쐬
Matrix4 identity();

//�g��k���s��̐���
Matrix4 scale(const Vector3 &s);

//��]�s��̐���
Matrix4 rotateX(float angle);
Matrix4 rotateY(float angle);
Matrix4 rotateZ(float angle);

//���s�ړ��s��̐���
Matrix4 translate(const Vector3 &t);

//���W�ϊ��i�x�N�g���ƍs��̊|���Z������j
Vector3 transform(const Vector3 &v, const Matrix4 &m);

//������Z�q�I�[�o�[���[�h
Matrix4 &operator *= (Matrix4 &m1, const Matrix4 &m2);

//2�����Z�q�I�[�o�[���[�h
//Matrix4 operator * (const Matrix4 &m1, const Matrix4 &m2);
Vector3 operator * (const Vector3 &v, const Matrix4 &m);