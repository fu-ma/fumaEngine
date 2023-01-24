#include "Particle.h"

bool Particle::Initialize(Model *model)
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particle[i] = ModelObj::Create(model);

		moveFlag[i] = false;
	}
	setFlag = false;
	time = 0;
	return true;
}

void Particle::Update(const int &moveNum, const XMFLOAT3 &particlePos)
{
	if (moveNum == static_cast<int>(TYPE::explosion) && setFlag == false)
	{
		for (int i = 0; i < PARTICLE_NUM; i++)
		{
			this->particlePos[i] = particlePos;
			this->vel[i] = { 0,0,0 };
			particleScale[i] = { 1,1,1 };

			const float rnd_vel = 0.1f;
			vel[i].x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel[i].y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			//moveFlag[i] = true;
		}
	}
	if (moveNum == static_cast<int>(TYPE::explosion) && setFlag == true)
	{
		for (int i = 0; i < PARTICLE_NUM; i++)
		{
			moveFlag[i] = true;
			if (moveFlag[i] == true)
			{

				this->particlePos[i].x += vel[i].x;
				this->particlePos[i].y += vel[i].y;
				particleScale[i].x -= 0.01f;
				particleScale[i].y -= 0.01f;
				particleScale[i].z -= 0.01f;

				particle[i]->SetRotation(particleScale[i]);
				particle[i]->SetPosition(this->particlePos[i]);
				particle[i]->SetScale(particleScale[i]);

				if (particleScale[i].x <= 0.0f)
				{
					particleScale[i] = { 0,0,0 };
				}

				if (particleScale[PARTICLE_NUM-1].x <= 0.0f)
				{
					setFlag = false;
				}
			}
		}
	}

	if (moveNum == static_cast<int>(TYPE::LEFT))
	{
		time++;
		for (int i = 0; i < PARTICLE_NUM; i++)
		{
			if (moveFlag[i] == true)
			{

				this->particlePos[i].x += vel[i].x;
				this->particlePos[i].y += vel[i].y;
				particleScale[i].x -= 0.02f;
				particleScale[i].y -= 0.02f;
				particleScale[i].z -= 0.02f;

				particle[i]->SetRotation(particleScale[i]);
				particle[i]->SetPosition(this->particlePos[i]);
				particle[i]->SetScale(particleScale[i]);

				if (particleScale[i].x <= 0.0f)
				{
					particleScale[i] = { 0,0,0 };
				}

				if (particleScale[i].x <= 0.1f)
				{
					moveFlag[i] = false;
				}
			}
		}
	}

	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particle[i]->Update();
	}
}

void Particle::Set(const XMFLOAT3 &particlePos)
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		if (moveFlag[i] == false)
		{
			this->particlePos[i] = particlePos;
			this->vel[i] = { 0,0,0 };
			particle[i]->SetPosition(particlePos);
			particleScale[i] = { 1,1,1 };
			particle[i]->SetScale(particleScale[i]);

			const float rnd_vel = 0.1f;
			vel[i].y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

			if (time % 20 == 0)
			{
				moveFlag[i] = true;
				time++;
			}
			
		}
	}
}

void Particle::Draw()
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		if (moveFlag[i] == true)
		{
			particle[i]->Draw();
		}
	}
}