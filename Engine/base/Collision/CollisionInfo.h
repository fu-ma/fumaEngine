#pragma once

#include <DirectXMath.h>

class ModelObj;
class BaseCollider;

/// <summary>
/// �Փˏ��
/// </summary>
struct CollisionInfo
{
public:
	CollisionInfo(ModelObj *modelObj, BaseCollider *collider, const DirectX::XMVECTOR &inter)
	{
		this->modelObj = modelObj;
		this->collider = collider;
		this->inter = inter;
	}

	// �Փˑ���̃I�u�W�F�N�g
	ModelObj *modelObj = nullptr;
	// �Փˑ���̃R���C�_�[
	BaseCollider *collider = nullptr;
	// �Փ˓_
	DirectX::XMVECTOR inter;
};
