/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F �����疃��(Ver0.1.2�F�J����)
 * �o�[�W����     �F 0.1.2.1.225(MJAI���O�\���F3�v���[�����̖����\���̒�`)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F tklog.h
 * �N���X��       �F MJSTklog
 * �����T�v       �F ���񃍃O�N���X
 * �쐬��         �F 2018/11/18 10:12:12
 * Ver0.0.1�쐬�� �F 2022/04/11 15:57:39
 * Ver0.1.2�쐬�� �F 2022/08/31 22:19:54
 * Ver0.1.2���ϓ� �F 2024/09/15 15:28:15
 * �ŏI�X�V��     �F 2024/11/07 19:11:07
 * 
 * Copyright (c) 2010-2024 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef TKLOG_H_INCLUDED
#define TKLOG_H_INCLUDED

#include <windows.h>
#include "stdafx.h"

#include "corelog.h"
#include "tkinfo.h"

/* ---------------------------------------------------------------------------------------------- */
// �N���X��`
/* ---------------------------------------------------------------------------------------------- */
class MJSTklog
{

	/* ----------------------------- */
	// ���J�֐���`
	/* ----------------------------- */
	public:

	// �N���X��`
	MJSCorelog  *core_log;   // �R�A���O�����N���X

	// Windows�p���O�n���h��
	HANDLE   hFile;
	DWORD    dwBytes;

	// ��Ɨp�ϐ�
	char tmp_msg[256];        // �ꎞ�����p

	// �\���p�����v
	char CharHai[41][4];
	char kyokutbl[12][8];

	/* ----------------------------- */
	// �R���X�g���N�^
	/* ----------------------------- */

	// �R���X�g���N�^��`
	MJSTklog() {};

	// �f�X�g���N�^��`
	~MJSTklog() {};

	// -----------------------------
	// �֐���`
	// -----------------------------

	// �S�̏���
	void tklog_init(char *logname);          // ���O�����J�n����
	void tklog_post();                       // ���O�����I������

	// �t�@�C������
	void tklog_file_init(char *logname);     // �t�@�C��������
	void tklog_file_close();                 // �t�@�C���N���[�Y

	// ���O�o��
	void tklog_print(char *msg);             // ���O�o��

	// ���ʊ֐�
	void tklog_space();                      // ��
	void tklog_cr();                         // ���s
	void tklog_time();                       // ���ԏo��

	// -----------------------------
	// MJS���O�o�͊֐�
	// -----------------------------

	// ���C������
	void tklog_print(MJSTkinfo *tk, int log_ver1, int log_ver2, int log_ver3, int log_ver4);   // MJS���O�o�̓��C������

	// �T�u���� - ��J�n
	void tklog_000_MJSlogStart(int log_ver1, int log_ver2, int log_ver3, int log_ver4);        // 000�FMJS���O�J�n
	void tklog_011_TakuStart(MJSTkinfo *tk);                                                   // 011�F��J�n
	void tklog_012_PlayerInfo(MJSTkinfo *tk);                                                  // 012�F�v���[���[���

	// �T�u���� - �Ǐ��
	void tklog_101_KyokuStart(MJSTkinfo *tk, int kyoku_index);                                 // 101�F�ǊJ�n
	void tklog_102_KyokuPlyInfo(MJSTkinfo *tk, int kyoku_index);                               // 102�F�ǃv���[���[���
	void tklog_103_DoraInfo(MJSTkinfo *tk, int kyoku_index);                                   // 103�F�\�h�����
	void tklog_11x_HaipaiInfo(MJSTkinfo *tk, int kyoku_index);                                 // 11x�F�z�v���
	void tklog_201_Actinfo(MJSTkinfo *tk, int kyoku_index);                                    // 201�F�A�N�V�������
	void tklog_21x_Nakiinfo(MJSTkinfo *tk, int kyoku_index);                                   // 21x�F�����
	void tklog_901_AgariInfo(MJSTkinfo *tk, int kyoku_index);                                  // 901�F�a�����
	void tklog_902_YakuInfo(MJSTkinfo *tk, int kyoku_index);                                   // 902�F�����
	void tklog_903_kyokuScore(MJSTkinfo *tk, int kyoku_index);                                 // 903�F�ǂ̍��v���_

	// �T�u���� - ��I��
	void tklog_911_TakuEndScore(MJSTkinfo *tk);                                                // 911�F���_����
	void tklog_919_TakuEnd(MJSTkinfo *tk);                                                     // 919�F��I��
	void tklog_999_MJSlogEnd(int log_ver1, int log_ver2, int log_ver3, int log_ver4);          // 999�FMJS���O�I��

};

#endif/* TKLOG_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- 
 * �\�[�X�I��
 * ---------------------------------------------------------------------------------------------- */
