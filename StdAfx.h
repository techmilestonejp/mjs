// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
// 
// �ŏI�X�V���F2023/10/07

#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS // �Â��֐����������g���Ă���̂ŁB�Â��̂�u�������ł���Ȃ�s�v�B

#include <memory.h>
#include <conio.h>    // getch
#include <objbase.h>  // CoCreateGuid
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// �t�@�C���̑��݊m�F
#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )
