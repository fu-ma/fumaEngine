#pragma once
#include<Windows.h>

//WindowsAPI
class WinApp
{
public://�萔
	//�E�B���h�E����
	static const int window_width = 1280;
	static const int window_height = 720;

private://�����o�ϐ�

	//�E�B���h�E�n���h��
	HWND hwnd = nullptr;

	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};

public://�ÓI�����o�֐�

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public://Getter

	const HWND &GetHwnd() { return hwnd; }
	const HINSTANCE &GetHInstance() { return w.hInstance; }

public://�����o�ϐ�

	//������
	void Innitialize();

	//���b�Z�[�W�̏���
	bool ProcessMessage();

	//�I��
	void Finalize();
};

