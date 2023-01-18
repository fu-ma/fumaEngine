#include "WindowAPI.h"

#pragma comment(lib,"winmm.lib")

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//���b�Z�[�W�ŕ���
	switch (msg)
	{
	case WM_DESTROY://�E�B���h�E���j�����ꂽ
		PostQuitMessage(0);//OS�ɑ΂��āA�A�v���̏I����`����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);//�W���̏������s��
}

void WinApp::Innitialize()
{
	//�V�X�e���^�C�}�[�̕���x��������
	timeBeginPeriod(1);

	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;//�E�B���h�E�v���V�[�W����ݒ�
	w.lpszClassName = L"SUPERJUMP";//�E�B���h�E�N���X��
	w.hInstance = GetModuleHandle(nullptr);//�E�B���h�E�n���h��
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//�J�[�\���w��

	//�E�B���h�E�N���X��OS�ɓo�^
	RegisterClassEx(&w);

	//�E�B���h�E�T�C�Y
	RECT wrc = { 0,0,window_width,window_height };

	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);//�����ŃT�C�Y�␳

	//�E�B���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow
	(
		w.lpszClassName,//�N���X��
		L"SUPERJUMP",//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,//�W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,//�\��X���W(OS�ɔC����)
		CW_USEDEFAULT,//�\��Y���W(OS�ɔC����)
		wrc.right - wrc.left,//�E�B���h�E����
		wrc.bottom - wrc.top,//�E�B���h�E�c��
		nullptr,//�e�E�B���h�E�n���h��
		nullptr,//���j���[�n���h��
		w.hInstance,//�Ăяo���A�v���P�[�V�����n���h��
		nullptr
	);
	//�E�B���h�E�\��
	ShowWindow(hwnd, SW_SHOW);
}

bool WinApp::ProcessMessage()
{
	MSG msg{};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT)
	{
		return true;
	}

	return false;
}

void WinApp::Finalize()
{
	//�E�B���h�E�N���X��o�^����
	UnregisterClass(w.lpszClassName, w.hInstance);
}
