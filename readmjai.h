/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.0.220(MJAI���O�\���F�J���h���\��)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F readmjai.h
 * �N���X��       �F MJSReadMjai
 * �����T�v       �F MJAI���O�ǂݍ��݃N���X
 * Ver0.1.2�쐬�� �F 2023/10/07 22:32:26
 * �ŏI�X�V��     �F 2024/10/30 16:22:54
 * 
 * Copyright (c) 2022-2023 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef MJSREADMJAI_H_INCLUDED
#define MJSREADMJAI_H_INCLUDED

#include "stdafx.h"

#include <windows.h>
#include "player.h"
#include "gui.h"
#include "corelog.h"

/* ---------------------------------------------------------------------------------------------- */
// �Œ�l
/* ---------------------------------------------------------------------------------------------- */

// ��ƕ����z��̃T�C�Y
#define MJAI_LINE_BUF     1024     // ���C��1�s(fget������1���C��)�̃o�b�t�@�T�C�Y

/* ---------------------------------------------------------------------------------------------- */
// �N���X��`
/* ---------------------------------------------------------------------------------------------- */
class MJSReadMjai
{

	// ------------------------------------------------------------------- 
	// ���J�֐���`
	// ------------------------------------------------------------------- 
	public:

	// fgets�p�t�@�C���\����
	FILE *fp;                      // FILE�^�\����

	// ���C���p�o�b�t�@
	char line_buf[MJAI_LINE_BUF];  // ���C�������p

	// �f�o�O���O�p
	MJSCorelog  *mjaidebug;        // Mjai�f�o�O���O�����N���X
	char mjaidebug_name[50];       // Mjai�f�o�O���O�t�@�C����
	char mjaidebug_buf[1024];      // Mjai�f�o�O���O�o�b�t�@

	// ------------------------------------------------------------------- 
	// �R���X�g���N�^
	// ------------------------------------------------------------------- 

	// �R���X�g���N�^��`
	MJSReadMjai(){};

	// �f�X�g���N�^��`
	~MJSReadMjai(){};

	/* ----------------------------- */
	// �֐���`
	/* ----------------------------- */

	// ���O�t�@�C���ǂݍ���
	void read_logfile_init(MJSGui *gui);                    // ����������
	void read_logfile_exec(MJSTkinfo *tk, MJSGui *gui);     // �ǂݍ��ݎ��s����
	void read_logfile_post();                               // �㏈��

	// MJAI���O�̓ǂݍ��ݏ���
	void Read_logline(MJSGui *gui);
	void set_wkinfo(MJSGui *gui, char* str);

	// ����N���X�̐ݒ菈��
	void set_tkinfo(MJSTkinfo *tk, MJSGui *gui);                                // ���C������
	void set_type_startgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);        // 01:type_startgame
	void set_type_startkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);       // 02:type_startkyoku
	void set_type_tsumo(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);            // 03:type_tsumo
	void set_type_dahai(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);            // 04:type_dahai
	void set_type_ankan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);            // 05:type_ankan
	void set_type_kakan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);            // 06:type_kakan
	void set_type_riichi(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);           // 07:type_riichi
	void set_type_reach_accepted(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);   // 08:set_type_reach_accepted
	void set_type_pon(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);              // 09:set_type_pon
	void set_type_chi(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);              // 10:set_type_chi
	void set_type_minkan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);           // 11:set_type_minkan
	void set_type_dora_open(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);        // 95:type_dora
	void set_type_hora(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);             // 96:type_hora
	void set_type_ryukyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);         // 97:type_ryukyoku
	void set_type_endkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);         // 98:type_endkyoku
	void set_type_endgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);          // 99:type_endgame

	// �T�u����
	int Get_hainum(char hai_str[]);

};

#endif /* MJSREADMJAI_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- 
 * �\�[�X�I��
 * ---------------------------------------------------------------------------------------------- */
