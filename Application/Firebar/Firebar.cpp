#include "Firebar.h"

Firebar::Firebar(float centerX, float centerY, int num,bool direction,float angleSpeed)
{
	this->num = num + 1;//中心のブロック分も含める
	this->centerX = centerX;
	this->centerY = centerY;
	this->direction = direction;
	this->angleSpeed = angleSpeed;
}

Firebar::~Firebar()
{
	for (int i = 0; i < GIMMICK_NUM; i++)
	{
		delete firebar[i];
		firebar[i] = nullptr;
	}

	delete modelGimmick;
	modelGimmick = nullptr;
	delete modelGimmickCenter;
	modelGimmickCenter = nullptr;
}

void Firebar::StaticInit()
{
	modelGimmick = Model::CreateFromOBJ("gimmick", true);
	modelGimmickCenter = Model::CreateFromOBJ("gimmickCenter", true);

	for (int i = 0; i < GIMMICK_NUM; i++)
	{
		firebar[i] = ModelObj::Create(modelGimmick);
	}
}

bool Firebar::Initialize()
{
	for (int i = 0; i < this->num; i++)
	{
		angle[i] = 0;
		addX[i] = 0;
		addY[i] = 0;
		moveFlag[i] = false;
		length[i] = 0;
	}

	for (int i = 0; i < GIMMICK_NUM; i++)
	{
		if (i < this->num)
		{
			firebar[i]->SetScale({ 0.5f,0.5f,0.5f });
			if (i == 0)
			{
				firebar[i]->SetModel(modelGimmickCenter);
				firebar[i]->SetScale({ 0.75f,0.75f,0.75f });
			}
			length[i] = 2.0f * i;
			moveFlag[i] = true;
		}
		else
		{
			if (firebar[i] != nullptr)
			{
				delete firebar[i];
				firebar[i] = nullptr;
			}
		}

		if (moveFlag[i] == true)
		{
			radius[i] = angle[i] * 3.14f / 180.0f;
			addX[i] = cos(radius[i]) * length[i];
			addY[i] = sin(radius[i]) * length[i];

			firebar[i]->SetPosition({ centerX + addX[i], centerY + addY[i], 0 });
		}
	}
	return true;
}

void Firebar::Update()
{
	// 行列の更新など
	for (int i = 0; i < this->num; i++)
	{
		if (firebar[i] == nullptr)
		{
			return;
		}
		firebar[i]->Update();
	}
}

void Firebar::Move()
{
	for (int i = 1; i < this->num; i++)
	{
		if (moveFlag[i] == true)
		{
			radius[i] = angle[i] * 3.14f / 180.0f;
			addX[i] = cos(radius[i]) * length[i];
			addY[i] = sin(radius[i]) * length[i];

			if (direction == false)
			{
				angle[i] -= angleSpeed;
				fireRot[i].z -= MOVE_SPEED;
			}
			if (direction == true)
			{
				angle[i] += angleSpeed;
				fireRot[i].z += MOVE_SPEED;
			}

			firebar[i]->SetPosition({ centerX + addX[i], centerY + addY[i], 0 });
			firebar[i]->SetRotation(fireRot[i]);
		}
	}
}

void Firebar::Draw()
{
	for (int i = 0; i < this->num; i++)
	{
		firebar[i]->Draw();
	}
}