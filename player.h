/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.1.233(�\���v(open_haiparts)�ꗗ�\���F�v������)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F player.h
 * �N���X��       �F MJSPlayer�N���X
 * �����T�v       �F �v���[���[�N���X
 * Ver0.0.8�쐬�� �F 2012/05/04 11:41:34
 * Ver0.1.0�쐬�� �F 2022/06/04 10:13:26
 * Ver0.1.1�쐬�� �F 2022/06/30 21:19:01
 * Ver0.1.2�쐬�� �F 2022/10/23 23:38:32
 * �ŏI�X�V��     �F 2025/01/04 11:21:26
 * 
 * Copyright (c) 2010-2025 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef PLY_H_INCLUDED
#define PLY_H_INCLUDED

#include <windows.h>
#include "stdafx.h"

#include "common.h"
#include "score.h"

/* ---------------------------------------------------------------------------------------------- */
// ���x��(�e���[�h)
/* ---------------------------------------------------------------------------------------------- */

// �v���[���[�L�����N�^�[
typedef enum {

	PLYCHAR_NONAME = 0,                 // 00:�v���[���[��ԂȂ�
	PLYCHAR_TAMPOPO,                    // 01:�v���[���[�L�����N�^�[1
	PLYCHAR_HIMAWARI,                   // 02:�v���[���[�L�����N�^�[2
	PLYCHAR_FATABA,                     // 03:�v���[���[�L�����N�^�[3
	PLYCHAR_WAKABA,                     // 04:�v���[���[�L�����N�^�[4
	PLYCHAR_AOBA,                       // 05:�v���[���[�L�����N�^�[5
	PLYCHAR_AYAME,                      // 06:�v���[���[�L�����N�^�[6
	PLYCHAR_TSUBAKI,                    // 07:�v���[���[�L�����N�^�[7
	PLYCHAR_KOBUSHI,                    // 08:�v���[���[�L�����N�^�[8
	PLYCHAR_NADESHIKO,                  // 09:�v���[���[�L�����N�^�[9
	PLYCHAR_TSUBOMI,                    // 10:�v���[���[�L�����N�^�[10
	PLYCHAR_SAKURA,                     // 11:�v���[���[�T�N��
	PLYCHAR_MJSPLY_TEST,                // 12:�e�X�g�p�L�����N�^�[

} LBPlyChar;

// �v���[���[��v���[�h
typedef enum {

	PLY_TEHAI_NO_MODE = 0,              // 00:��ԂȂ�
	PLY_TEHAI_NORMAL,                   // 01:�ʏ���
	PLY_TEHAI_NAKI_WAIT,                // 02:���҂�
	PLY_TEHAI_RIICHI_SUTEHAI,           // 03:���[�`���̎̔v�I��
	PLY_TEHAI_RIICHI_YUKO,              // 04:���[�`�L�����

} LBPlyTehaiMode;

/* ---------------------------------------------------------------------------------------------- */
// �ϐ���`
/* ---------------------------------------------------------------------------------------------- */

class MJSPlayer{

	public:

	// -----------------------------
	// �������Ԍv��
	// -----------------------------

	int action_timestamp1;
	int action_timestamp2;

	// -----------------------------
	// ����
	// -----------------------------

	// �v���[���̃^�C�v
	LBPlyChar ply_type;

	// �v���[���Ȕԍ�
	int ply_num;                             // �����̃v���[���ԍ�
	int ply_num_shimo;                       // ���Ƃ̃v���[���ԍ�

	// �v���[���̉�
	int ie;                                  // �Ə�� ���ƁF0�A��ƁF1�Aie=2�Ńv���[��������
	int ply_bakaze;                          // �v���[���̏ꕗ�v�̔v�ԍ�(���� = 0�A��� = 1)
	int ply_zikaze;                          // �v���[���̎����v�̔v�ԍ�

	// �Ԕv���
	int max_aka_count[AKA_TYPE_MAX_COUNT];   // �ő�Ԕv����

	// �v����(�c��v����)
	int kyoku_tsumo_count;                   // �ǂ̎��̉�(�ő�70�܂ŁA136��������Ǝc�薇��)
	int open_haiparts_count[PAI_MAX];        // ��v�A�̔v�A���v�A�h���v�Ŋ��ɕ\�����ꂽ�v����(4��������Ǝc�薇��)

	// -----------------------------
	// ��v���
	// -----------------------------

	// ��v���
	int tehai[PAI_MAX];                      // ��v�q�X�g�O����
	int tehai_count;                         // ��v����
	int aka_count[AKA_TYPE_MAX_COUNT];       // �Ԕv����

	// ��v�e�[�u��
	int  tehaitbl[TEHAI_MAX];                // �v�e�[�u��
	bool tehaitbl_aka[TEHAI_MAX];            // �v�e�[�u��(�Ԕv)

	// ���[�`���
	int ply_riichi_mode;                     // ���[�`���(0�F���[�`�����ĂȂ��A1�F���[�`�錾��E�̔v�O�A2�F���[�`�m����)

	/* ----------------------------- */
	// �N���v���
	/* ----------------------------- */

	int naki_count;                          // �����v�ʎq��
	int ankan_count;                         // �Þȍ��v�ʎq��
	int kakan_count;                         // ���ȍ��v�ʎq��

	LBMen naki_stat[MEN_MAX];                // �����
	int naki_hai[MEN_MAX];                   // ���v
	int naki_idx[MEN_MAX];                   // �`�[���̓��v
	int naki_aka[MEN_MAX];                   // �Ԕv�̐�

	/* ----------------------------- */
	// �͏��
	/* ----------------------------- */

	int kawa[30];                            // ��(�̔v���)

	/* ----------------------------- */
	// �v���[���[�A�N�V�������
	/* ----------------------------- */

	// �A�N�V�����X�e�[�^�X
	LBPAct ply_act;                     // �v���[���[�̃A�N�V�����X�e�[�^�X

	// �c���A�N�V����
	int  ply_tsumo_hai;                 // �c���v
	bool ply_tsumo_aka;                 // ���̔v�̐Ԕv�L��

	// �̔v�A�N�V����
	int  ply_sute_hai;                  // �̔v
	bool ply_sute_aka;                  // �̔v�̐Ԕv�L��

	// ���A�N�V����
	int ply_naki_idx;                   // �������̔vINDEX(�J���錾���܂�)
	int ply_naki_aka_count;             // �������̐Ԕv����

	/* ----------------------------- */
	// ��������`
	/* ----------------------------- */

	int shanten_normal;                 // �ʏ������
	int shanten_kokushi;                // ���m������
	int shanten_chitoi;                 // ���Ό�����

	/* ----------------------------- */
	// �ʏ�V�����e���v�Z
	/* ----------------------------- */

	int atama_count;                    // �����̖���(�l��0����1)
	int atama_hai;                      // �����̔v�ԍ�

	int mentsu_count;                   // �ʎq��
	LBMen mentsu_stat[MEN_MAX];         // �ʎq���
	int mentsu_hai[MEN_MAX];            // �ʎq�v

	int taatsu_count;                   // ���q��
	LBMen taatsu_stat[MEN_MAX];         // ���q���
	int taatsu_hai[MEN_MAX];            // ���q�v

	// -----------------------------
	// �ʏ�V�����e���v�Z(������Ɨp)
	// -----------------------------

	int tmp_shanten;                    // (��Ɨp)�ʏ�V�����e��

	int tmp_atama_count;                // �����̖���(�l��0����1)
	int tmp_atama_hai;                  // �����̔v�ԍ�

	int tmp_mentsu_count;               // �ʎq��
	LBMen tmp_mentsu_stat[MEN_MAX];     // �ʎq���
	int tmp_mentsu_hai[MEN_MAX];        // �ʎq�v

	int tmp_taatsu_count;               // ���q��
	LBMen tmp_taatsu_stat[MEN_MAX];     // ���q���
	int tmp_taatsu_hai[MEN_MAX];        // ���q�v

	// -----------------------------
	// �̔v���E�̔v��₲�Ƃ̗L���v
	// -----------------------------

	int sutekoho_count;                 // �̔v���̑���
	int sutekoho_hai[14];               // �̔v���̔v�ԍ�
	int sutekoho_shanten[14];           // �̔v���̌�����
	int sutekoho_priority[14];          // �̔v���̗D�揇��

	bool yuko_hai[14][40];              // �L���v
	int  yuko_haishu_count[14];         // �L���v�̔v��ʐ�
	int  yuko_hai_count[14];            // �L���v�ƂȂ��ʂ̑���
	int  yuko_max_count;                // �L���v�̍ő吔

	int fixed_sutekoho_num;             // �ŏI���肵���̔v�ԍ�

	// -----------------------------
	// �v���[���X�e�[�^�X
	// -----------------------------

	// �v���[���X�e�[�^�X
	bool ply_tehai_ori_stat;            // �I�����
	int  ply_ori_hai;                   // �I����Ԃ̌��I���v
	bool ply_ori_aka;                   // �I����Ԃ̌��I���v�̐Ԕv�L��

	// �a�������֘A
	bool ply_tehai_yaku_stat;           // ��v���̗L��
	bool ply_furiten_stat;              // �t���e�����

	// �������֘A
	bool ply_tehai_naki_stat;           // ������
	bool ply_yakuhai_stat;              // ��v�̕ێ��L��

	// -----------------------------
	// �����e�[�u��
	// -----------------------------

	// �L���v
	bool yuko_hai_13mai[PAI_MAX];       // 13�����̗L���v

	// �����e�[�u��
	int  nakikoho_tbl_count;                             // �����e�[�u���̖���
	LBPAct nakikoho_tbl_act[NAKI_KOHO_MAX_COUNT];        // �����e�[�u��
	int  nakikoho_tbl_hai[NAKI_KOHO_MAX_COUNT];          // �����_�v�e�[�u��
	int  nakikoho_tbl_idx[NAKI_KOHO_MAX_COUNT];          // �����_�`�[�e�[�u��
	bool nakikoho_tbl_yesno[NAKI_KOHO_MAX_COUNT];        // �����_���s�L��

	// -----------------------------
	// �R���X�g���N�^
	// -----------------------------

	// �R���X�g���N�^��`
    MJSPlayer(){};

	// �f�X�g���N�^��`
    ~MJSPlayer(){};

	// -----------------------------
	// �A�N�V��������
	// -----------------------------

	// �N���X�������E�㏈��
	void PlyInit();
	void PlyPost();

	// 1-1.��J�n�E�I��
	void PlyActTakuStart(int tmp_ply_id);
	void PlyActTakuEnd();                         // ��I������

	// 1-2.�ǊJ�n�E�I��
	void PlyActKyokuStart(int  tmp_kaze,          // �ǔԍ�
	                      int  tmp_kyoku,         // �ꕗ�̔v�ԍ�
	                      int  tmp_honba,         // �{��
	                      int  tmp_riichibo,      // ���[�`�_�̖{��
	                      int  tmp_ie,            // �v���[���̉Ɣԍ�
	                      int  tmp_dora);         // �h����

	void PlyActKyokuEnd();                        // �ǏI������

	// 2-1.�z�v����
	void PlyActHaipai(int tmp_tsumo_hai, bool tmp_tsumo_aka);

	// 2-2.�z�v�㏈��
	void PlyActPostHaipai();

	// 3-1.���̏���
	void PlyActTsumo(int tmp_tsumo_hai, bool tmp_tsumo_aka);          // ���̎��̔v����(���C��)
	void PlyChkAISutehai();                                           // (�T�u)�헪���܂߂��̔v�ݒ�
	void PlyChkTehaiOri();                                            // (�T�u)��v�I���m�F
	void PlyCountTsumo();                                             // ���̖������J�E���g

	// 3-1.(�T�u����)�A�N�V�����m�F
	void PlyChkAnkan(int tmp_tsumo_hai, bool tmp_tsumo_aka);          // �ÞȊm�F
	void PlyChkKakan(int tmp_tsumo_hai, bool tmp_tsumo_aka);          // ���Ȋm�F
	void PlyChkTsumoSute();                                           // ���̎��̃A�N�V�����Ǝ̔v�̌���
	void PlyChk9shu9hai();                                            // ����v�m�F

	// 3-2.���[�`�錾������
	void PlyChkRiichiSute(struct MJSPlyInfo *pinfo);                  // ���[�`���̎̔v����(���C��)

	// 3-3.�̔v��A�N�V��������
	void PlyActTsumoSute();                                           // ���̎̔v�A�N�V����

	// 3-3.(�T�u����)�̔v��A�N�V��������
	void PlySetTsumoSuteTehaiHist();                                  // 1.���̎̔v���̎�v�q�X�g�O��������
	void PlyChkPlyStat();                                             // 2.�v���[����v�̏�Ԋm�F
	void PlyChkYaku();                                                // 3.��L��m�F
	void PlyChkFuriten();                                             // 4.�t���e���m�F
	void PlyChkNakitbl();                                             // 5.���e�[�u���̏�Ԋm�F
	void PlySetKawa(int tmp_ply_id, int tmp_hai, int tmp_aka);        // (�ėp����)�͏��̐ݒ�

	// 3-4.�̔v���A�N�V��������(���̎̂ăA�N�V�����ȊO)
	void PlyActAnkan(int tmp_naki_hai);                               // �ÞȃA�N�V����
	void PlyActKakan(int tmp_naki_hai, int tmp_naki_aka_count);       // ���ȃA�N�V����

	// 4-1.���v���[���̊m�F����
	void PlyChkOthPlyTsumo();                                         // ���v���[���̎���
	void PlyChkOthPlyRiichi(int tmp_ply_id);                          // ���v���[���̃��[�`�錾
	void PlyChkNaki(int suteply, int hai);                            // ���m�F

	// 4-2.���A�N�V��������
	void PlyActNaki(int naki_ply_num,                                 // ���v���[��
	                LBPAct naki_ply_act,                              // ���A�N�V�������
	                int hai,                                          // ���v
	                int chi_hai_idx,                                  // ���ʎq(�`�[�ʎq)�̓��v
	                int naki_aka_count);                              // ���ʎq�̐Ԕv����
	void PlyChkNakiSute();                                            // ����̎̔v�m�F

	// 4-3.���̔v�A�N�V����
	void PlyActNakiSute();                                            // ����̎̔v����

	// 5-1.�a���I������
	void PlyAgari();

	// 5-2.���ǏI������
	void PlyRyuKyoku();

	// -----------------------------
	// �������m�F(���C������)
	// -----------------------------

	// �e���p�C�m�F
	void ChkTsumoAriShanten();          // ���̗L��(���̌�B�̔v�O)��Ԃ̌������m�F�F�̔v���Z�o
	void ChkTsumoNashiShanten();        // ���̖���(�̔v��A���̑O)��Ԃ̌������m�F�F���e�[�u�����i�[
	void SetSutekohoPriority();         // �̔v���̗D�揇�ʎZ�o
	void SetFixedSutekoho();            // �ŏI�̔v���̎Z�o

	// ���Ғl�v�Z
	void SetTempaiKitaichi();
	void Set1shantenKitaichi();

	// -----------------------------
	// �������m�F(�T�u����)
	// -----------------------------

	void NormalShanten();               // �������m�F(�ʏ�)
	void mentsu_cut(int hai);           // �ʎq�폜����
	void taatsu_cut(int hai);           // ���q�폜����

	void NormalShanten_detail();        // �������m�F(�ʏ�_�ʎq���t�^��)
	void mentsu_cut_detail(int hai);    // �ʎq�폜����(�ʎq���t�^��)
	void taatsu_cut_detail(int hai);    // ���q�폜����(���q���t�^��)

	void KokushiShanten();              // �������m�F(���m���o)
	void ChitoiShanten();               // �������m�F(���Ύq)

	// -----------------------------
	// ���̑��̊֐�
	// -----------------------------

	// ��v�e�[�u���X�V����
	void settehaitbl();                 // ��v�e�[�u���X�V����

};

#endif/* PLY_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
