/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.0.204(�v�����O���ݒ菈������)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F tpread.h
 * �N���X��       �F MJSTpread
 * �����T�v       �F ���������O�ǂݍ��݃N���X
 * Ver0.1.0�쐬�� �F 2022/04/11 15:57:39
 * Ver0.1.1�쐬�� �F 2022/05/14 22:27:08
 * Ver0.1.2�쐬�� �F 2022/08/31 22:19:54
 * �ŏI�X�V��     �F 2024/10/05 21:35:42
 * 
 * Copyright (c) 2010-2022 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef MJSREADTPLOG_H_INCLUDED
#define MJSREADTPLOG_H_INCLUDED

#include <windows.h>
#include "gui.h"
#include "tkinfo.h"

/* ---------------------------------------------------------------------------------------------- */
// �Œ�l
/* ---------------------------------------------------------------------------------------------- */

// ��ƕ����z��̃T�C�Y

#define MJSCORE_WORK_COL    8192   // ���ڐ�
#define MJSCORE_WORK_BUF    64     // ��Ɨp�z��̃o�b�t�@�T�C�Y

#define MJSCORE_FGET_BUF    128    // fget�����p�̃o�b�t�@�T�C�Y

/* ---------------------------------------------------------------------------------------------- */
// �N���X��`
/* ---------------------------------------------------------------------------------------------- */
class MJSReadTplog
{

	// ------------------------------------------------------------------- 
	// ���J�֐���`
	// ------------------------------------------------------------------- 
	public:

	// fgets�p�t�@�C���\����
	FILE *fp;                 // FILE�^�\����

	// ��Ɨp�����z��
	char** wk_str;            // ��Ɨp�����z��
	int wk_str_count;         // ��Ɨp�����z��̑���
	int wk_index;             // ��Ɨp�����z���INDEX

	// ------------------------------------------------------------------- 
	// �R���X�g���N�^
	// ------------------------------------------------------------------- 

	// �R���X�g���N�^��`
	MJSReadTplog() {};

	// �f�X�g���N�^��`
	~MJSReadTplog() {};

	/* ----------------------------- */
	// �֐���`
	/* ----------------------------- */

	// ���O�m�F����
	int checklog();                          // ���O��ʊm�F�F�Ԃ�l=���O��ʂ̒l

	// �S�̏���
	void TpreadInit(MJSGui *gui);            // ����������
	void TpreadExec(MJSTkinfo *tk);          // �ǂݍ��ݎ��s����
	void TpreadPost();                       // �㏈��

	// Mjscore�ǂݍ��ݏ���
	void Read_mjscore();
	void Set_wk(char* str);

	// �v�ԍ��m�F����
	int Chk_painum(char* str);               // �v�ԍ��̎Z�o
	int Chk_DoraHyoji(int hai);              // �h���\���v�̎Z�o

	// Tkinfo�ݒ菈��
	void Set_tkinfo(MJSTkinfo *tk);                                        // ���C������
	void Set_tkinfo_tkstart(MJSTkinfo *tk);                                // mjscore_read_mode = 1  �F ��J�n���ǂݍ���
	void Set_tkinfo_plyprof(MJSTkinfo *tk);                                // mjscore_read_mode = 2  �F �v���[���[���ǂݍ���
	void Set_tkinfo_kyoku_score(MJSTkinfo *tk, int kyoku_index);           // mjscore_read_mode = 3  �F �Ǐ��ƃv���[���[���_���
	void Set_tkinfo_agariinfo(MJSTkinfo *tk, int kyoku_index);             // mjscore_read_mode = 4  �F �a�����ǂݍ���
	void Set_tkinfo_haipai(MJSTkinfo *tk, int kyoku_index);                // mjscore_read_mode = 5  �F �z�v���
	void Set_tkinfo_haipai_sub(MJSTkinfo *tk, int kyoku_index, int pnum);  // mjscore_read_mode = 5a �F �z�v���(���̃T�u����)
	void Set_tkinfo_dora(MJSTkinfo *tk, int kyoku_index);                  // mjscore_read_mode = 6  �F �h�����
	void Set_tkinfo_actinfo(MJSTkinfo *tk, int kyoku_index);               // mjscore_read_mode = 7  �F �A�N�V�������
	bool Set_tkinfo_checkend();                                            // mjscore_read_mode = 8  �F ��I���m�F
	void Set_tkinfo_tkend(MJSTkinfo *tk);                                  // mjscore_read_mode = 9  �F ��I�����ǂݍ���

};

#endif/* MJSREADTPLOG_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- 
 * �\�[�X�I��
 * ---------------------------------------------------------------------------------------------- */
