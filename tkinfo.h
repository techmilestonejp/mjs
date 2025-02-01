/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.1.227(tkinfo�Ɉꔭ�A�_�u���[�ϐ��𓱓�)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F tkinfo.h
 * �N���X��       �F MJSTkinfo
 * �����T�v       �F ����N���X
 * Ver0.0.8�쐬�� �F 2012/05/04 08:57:12
 * Ver0.1.0�쐬�� �F 2022/04/11 15:57:39
 * Ver0.1.1�쐬�� �F 2022/06/30 21:19:01
 * Ver0.1.2�쐬�� �F 2022/08/31 22:19:54
 * �ŏI�X�V��     �F 2024/11/16 06:30:45
 * 
 * Copyright (c) 2010-2023 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef TKINFO_H_INCLUDED
#define TKINFO_H_INCLUDED

#include "stdafx.h"
#include "common.h"
#include "score.h"

/* ---------------------------------------------------------------------------------------------- */
//  �\����
/* ---------------------------------------------------------------------------------------------- */
// �ǃv���t�@�C���\����
struct MJSkyokuinfo{

	// -----------------------------
	// ��������
	// -----------------------------

	// �Ǐ��
	int kyoku_index;                    // �ǐ����ԍ�
	int kyoku;                          // �ǂ͉����H( ����� = 0�A ����� = 1 )
	int tsumibo;                        // �ςݖ_
	int riichbo;                        // ���[�`�_

	// �����V�[�h�ԍ�
	int seed_num;                       // �ǂ��Ƃ̗����V�[�h�ԍ�

	// �v���[���[�Ə��
	int ie[PLAYER_MAX];                 // ���ꂼ��ɉƏ����i�[����A���ƁF0�A��ƁF1�Aie[0]=2�Ńv���[��0������
	int kyoku_oya;                      // ���̋ǂ̐e�v���[���[�ԍ�

	// �v���[���[���_
	int ply_kyoku_start_score[PLAYER_MAX];  
	int ply_kyoku_end_score[PLAYER_MAX];    

	// -----------------------------
	// ��������
	// -----------------------------

	char kyoku_startdate[12];           // �ǂ̊J�n��
	char kyoku_starttime[12];           // �ǂ̊J�n����
	char kyoku_enddate[12];             // �ǂ̏I����
	char kyoku_endtime[12];             // �ǂ̏I������

	// -----------------------------
	// �h�����
	// -----------------------------

	int  doracount;                    // �h��(���h��)�̕\������
	int  dora[5];                      // �ϊ��ϕ\�h���̔v�ԍ�(�W���h��0�A�J���h��1�`4)
	bool dora_aka[5];                  // �\�h���̐Ԕv�L��
	int  dora_actid[5];                // �\�h���̃A�N�V�����ԍ�
	int  uradora[5];                   // �ϊ��ϗ��h���̔v�ԍ�(�W���h��0�A�J���h��1�`4)
	bool uradora_aka[5];               // ���h���̐Ԕv�L��
	int  uradora_actid[5];             // ���h���̃A�N�V�����ԍ�

	// -----------------------------
	// ��v���
	// -----------------------------

	int tehai[PLAYER_MAX][PAI_MAX];                    // �z�v���̎�v
	int tehai_mode[PLAYER_MAX][PAI_MAX];               // �z�v���̎�v��ʃ��[�h(�v4��̋��=2��4��=16)
	int aka_count[PLAYER_MAX][AKA_TYPE_MAX_COUNT];     // �z�v���̐Ԕv�̖���

	// -----------------------------
	// ���ʎq(�N���ʎq)���
	// -----------------------------

	int naki_count[PLAYER_MAX];                   // �������v�����c��
	int ankan_count[PLAYER_MAX];                  // �A���J�����v�ʎq��
	int kakan_count[PLAYER_MAX];                  // �J�J�����v�ʎq��

	int   naki_actid[PLAYER_MAX][MEN_MAX];        // �������A�N�V�����ԍ�(actid)
	LBMen naki_stat[PLAYER_MAX][MEN_MAX];         // ���`��
	int   naki_hai[PLAYER_MAX][MEN_MAX];          // ���v
	int   naki_mode[PLAYER_MAX][MEN_MAX];         // ���v�̔v��ʃ��[�h(�v4��̋�ʁF4�~4�~4=64)
	int   naki_idx[PLAYER_MAX][MEN_MAX];          // �����̓��v
	int   naki_aka[PLAYER_MAX][MEN_MAX];          // �Ԕv�̍��v��

	int   naki_mj_idx[PLAYER_MAX][MEN_MAX];       // mjscore�v���p�̖��C���f�b�N�X(��Ɨp)

	// -----------------------------
	// ��A�N�V�������
	// -----------------------------

	int    act_count;                             // Act�ԍ�
	LBTkSt act_stat[ACTID_MAX];                   // Act�X�e�[�^�X
	int    act_ply[ACTID_MAX];                    // Act�����v���[���̔ԍ�
	int    react_ply[ACTID_MAX];                  // Act���ꂽ(���ꂽ�ꍇ)�v���[���̔ԍ�
	int    act_hai[ACTID_MAX];                    // Act�v�ԍ�
	int    act_hai_mode[ACTID_MAX];               // Act�v�̔v��ʃ��[�h(�v4��̋�ʁF4���)
	int    act_idx[ACTID_MAX];                    // Act�v�̓��v
	bool   act_aka[ACTID_MAX];                    // Act�v�̐Ԕv�L��
	int    act_hai_sutenum[ACTID_MAX];            // Act�v�������牽�Ԗڂɐ؂�ꂽ�̂��H

	// -----------------------------
	// �a�����
	// -----------------------------

	// �a�����\����
	int agari_ply_count;                          // �a���v���[����
	MJSYakuinfo ply_agari_yk[3];                  // 3�v���[���̘a�������(�\����)

	// �𖼃e�[�u�����(���������O�p�F�ʏ���E�𖞋���)
	char yakuname[NORMALYAKU_MAX][40];            // ���

	// �a����v�e�[�u��(MJAI�����p)
	int  agari_tehaicount;                        // ��v�̍��v����(���̔v�͊܂�)
	int  agari_tehaitbl[TEHAI_MAX];               // �v�e�[�u��
	bool agari_tehaitbl_aka[TEHAI_MAX];           // �v�e�[�u��(�Ԕv)

};

/* --------------------------------------------------------------- */
// �N���X��`                                                      
/* --------------------------------------------------------------- */

class MJSTkinfo
{
	public:

	// -----------------------------
	// ���_�v�Z�p�N���X
	// -----------------------------
	MJSScore *sc;                       // ���_�v�Z�����p�N���X

	// -----------------------------
	// �Ǐ��\����
	// -----------------------------

	int kyoku_index;                    // �ǐ�
	MJSkyokuinfo *kyoku;                // �Ǎ\����(�|�C���^��`)

	// -----------------------------
	// GUI���[�h��PLY���[�h���H
	// -----------------------------

	int  ply_hum_mode;                  // �l��COM��(0�FPLY���[�h�E�S��COM�A1�FGUI���[�h�E�l�v���[���[����)
	bool com_no_chk_tehai_flg;          // COM�̎�v���̗L��
	int  runing_mode;                   // ���؃��[�h

	// -----------------------------
	// ����
	// -----------------------------

	char tkgname[32];                   // �Q�[����
	char tkname[64];                    // �얼
	char tkno[8];                       // ��ԍ�
	char startdate[12];                 // �J�n��
	char starttime[12];                 // �J�n����
	char enddate[12];                   // �I����
	char endtime[12];                   // �I������
	int  core_seed_num;                 // �R�A�����V�[�h�ԍ�
	char mjai_seed_num[24];             // MJAI�p�V�[�h�ԍ�

	/* ----------------------------- */
	// �v���[�����
	/* ----------------------------- */

	// �v���[����
	char plyname[PLAYER_MAX][24];       // �v���[���[��
	char plyrate[PLAYER_MAX][8];        // �v���[��Rait

	// MJAI�p�ϐ�
	int ply_mjai_id[PLAYER_MAX];        // �v���[���[����ID(MJAI�p)
	int ply_mjai_hum_id;                // �l�v���[���[��ID(MJAI�p)

	// ��Q�[������
	int plyjun[PLAYER_MAX];             // �v���[���[����
	int plyEndscore[PLAYER_MAX];        // �v���[���ŏI���_

	/* ----------------------------- */
	// �샋�[�����
	/* ----------------------------- */

	int init_score;                     // �������_
	LBTkGmTYPE tkgame_type;             // ��Q�[�����(������A������)
	int aka_max[AKA_TYPE_MAX_COUNT];    // �Ԕv�̍ő喇��

	// -----------------------------
	// �v�R�ǂݍ��݃��[�h
	// -----------------------------
	int yama_setting_mode;              // 0�F�l�ǂݍ��݁A1�F�����_���ݒ�B2�F�V�[�h�l�Œ�

	// -----------------------------
	// �����_�̑�X�e�[�^�X
	// -----------------------------

	bool end_flg;                       // �I���t���O
	LBTkSt stat;                        // ����
	int ply_turn;                       // ���݂̃v���[���[�̏���
	LBPAct ply_act;                     // �v���[���[�A�N�V����

	// -----------------------------
	// �v�R���
	// -----------------------------

	// ���̔v�̃|�C���^
	int hai_point;                      // �v�̓ǂݍ��݂͂ǂ��ł���̂��H
	int rinshan_point;                  // �����V�����v�̓ǂݍ��݂͂ǂ��ł���̂��H

	// �c�薇��(�r���[�A�[�p)
	int remain_hai_count;               // �c�薇��
	int remain_rinshan_count;           // �c�薇��(�����V�����p)

	// �v�R�e�[�u��
	int hai_yama[PAI_COUNT_MAX];        //  0 -   1 �\�h��       - ���h��
                                        //  2 -   3 �\�ȃh��1    - ���ȃh��1
                                        //  4 -   9 �\�ȃh��2�`4 - ���ȃh��2�`4
                                        // 10 -  13 �����V�����v
                                        // 14 -  26 �v���[���[�z�v(�v���[���[1)
                                        // 27 -  39 �v���[���[�z�v(�v���[���[2)
                                        // 40 -  52 �v���[���[�z�v(�v���[���[3)
                                        // 53 -  65 �v���[���[�z�v(�v���[���[4)
                                        // 66 - 135 �c���v

	int yamahai_index[PAI_COUNT_MAX];   // �v�R�̔v���

	// -----------------------------
	// �v���[���[Act��v�q�X�g�O�������
	// -----------------------------

	// ���݂̎�v�q�X�g�O�������
	int ply_act_tehai[PLAYER_MAX][PAI_MAX];                 // �A�N�V������v
	int ply_act_aka_count[PLAYER_MAX][AKA_TYPE_MAX_COUNT];  // �A�N�V������v�̐Ԕv����

	// ���̏��
	int  ply_act_tsumo[PLAYER_MAX];               // ���̔v
	bool ply_act_tsumo_aka[PLAYER_MAX];           // ���̂̐Ԕv
	int  ply_act_tsumo_shanten[PLAYER_MAX];       // ���̂̌�����(���̔v���̂Ă��ꍇ�̌�����)
	bool ply_act_tsumo_can_sute[PLAYER_MAX];      // �̔v�s�L��(���[�`���_�̃m�[�e���v�A���̔v���̋򂢑ւ��֎~�v)

	// ��v����̎̔v���
	int  ply_act_sute[PLAYER_MAX];                // �̔v�v
	bool ply_act_sute_aka[PLAYER_MAX];            // �̔v�̐Ԕv

	// �����v�Z�p���J�E���g
	int naki_count_none_kakan[PLAYER_MAX];        // ���ʎq��(�J�J���Ȃ�)

	// ������
	int shanten_total[PLAYER_MAX];                // �����������F�O��ނ̂����ōł����Ȃ�������
	int shanten_normal[PLAYER_MAX];               // �ʏ������
	int shanten_kokushi[PLAYER_MAX];              // ���m������
	int shanten_chitoi[PLAYER_MAX];               // ���Ό�����

	// �Ҕv
	int ply_act_machi_count[PLAYER_MAX];                                  // �Ҕv���v����
	int ply_act_machi_hai[PLAYER_MAX][NORMAL_MACHI_MAX_COUNT];            // �Ҕv�̔v�ԍ�
	int ply_act_machi_furiten_mode[PLAYER_MAX][NORMAL_MACHI_MAX_COUNT];   // �Ҕv�̃t���e���`��

	// �V�a�L��
	bool tenho_chiho_flg[PLAYER_MAX];             // �V�a�E�n�a�L��
	bool renho_flg[PLAYER_MAX];                   // �l�a�L��

	// ���[�`�L��
	bool riichi_flg[PLAYER_MAX];                  // ���[�`�L��
	bool riichi_ippatsu_flg[PLAYER_MAX];          // ���[�`�ꔭ�L��
	bool double_riichi_flg[PLAYER_MAX];           // �_�u�����[�`�L��

	// �t���e���L��
	bool   furiten_flg[PLAYER_MAX];               // �t���e���L��
	LBCbSt furiten_mode[PLAYER_MAX];              // �t���e�����[�h

	// -----------------------------
	// �v���[���[�A�N�V������v�e�[�u��
	// -----------------------------

	// ��v�e�[�u��
	int  ply_act_tehaicount[PLAYER_MAX];                         // ��v�̍��v����(���̔v�͊܂�)
	int  ply_act_tehaitbl[PLAYER_MAX][TEHAI_MAX];                // �v�e�[�u��
	bool ply_act_tehai_tbl_aka[PLAYER_MAX][TEHAI_MAX];           // �v�e�[�u��(�Ԕv)
	int  ply_act_tehai_shanten_tbl[PLAYER_MAX][TEHAI_MAX];       // �v�e�[�u��(������)
	bool ply_act_tehai_can_sute_tbl[PLAYER_MAX][TEHAI_MAX];      // �v�e�[�u��(���[�`���_�̃m�[�e���v�A���̔v���̋򂢑ւ��֎~�v)

	// �v�e�[�u���̎̔v�ʒu�ԍ�
	int ply_tbl_com_sutehai_statnum[PLAYER_MAX];                 // �v�e�[�u���̎̔v�ʒu�ԍ�(COM�p)
	int ply_tbl_hum_sutehai_statnum;                             // �v�e�[�u���̎̔v�ʒu�ԍ�(HUM�p)

	// -----------------------------
	// �A�N�V�����͏��
	// -----------------------------

	int  ply_act_kawa_count[PLAYER_MAX];                 // �͔v�̍��v����
	int  ply_act_kawa[PLAYER_MAX][KAWA_HAI_MAX];         // �͔v
	bool ply_act_kawa_aka[PLAYER_MAX][KAWA_HAI_MAX];     // �͔v�̐Ԕv
	int  ply_act_kawa_mode[PLAYER_MAX][KAWA_HAI_MAX];    // �͔v�̏��(0:�ʏ�A1:���[�`�A2:�����)

	// -----------------------------
	// �v���[���[���Ƃ̖��m�F����
	// -----------------------------

	int naki_ply_num;                     // ���A�N�V�������s���v���[���ԍ�
	LBPAct ply_act_naki[PLAYER_MAX];      // ���m�F���̊e�v���[���[�A�N�V����
	int ply_naki_hai[PLAYER_MAX];         // ���v
	int ply_naki_idx[PLAYER_MAX];         // �`�[���̓��v
	int ply_naki_aka_count[PLAYER_MAX];   // �ԃJ�E���g��

	// -----------------------------
	// �������Z�o
	// -----------------------------

	int kokushi_hai_num[13];         // ���m���o�̍\���v�̔ԍ�

	int atama_count;                 // ���v�̖���(�l��0����1)
	int atama_hai;                   // ���v�̔v�ԍ�

	int mentu_count;                 // �ʎq��
	LBMen mentu_stat[MEN_MAX];       // �ʎq���
	int mentu_hai[MEN_MAX];          // �ʎq�v

	int taatu_count;                 // ���q��
	LBMen taatsu_stat[MEN_MAX];      // ���q���
	int taatsu_hai[MEN_MAX];         // ���q�v

	// -----------------------------
	// �������Z�o�p(�v�Z�����p)
	// -----------------------------

	int tmp_shanten;                    // (�v�Z�����p)�ʏ�V�����e��

	int tmp_atama_count;                // ���v�̖���(�l��0����1)
	int tmp_atama_hai;                  // ���v�̔v�ԍ�

	int tmp_mentu_count;                // �ʎq��
	LBMen tmp_mentu_stat[MEN_MAX];      // �ʎq���
	int tmp_mentu_hai[MEN_MAX];         // �ʎq�v

	int tmp_taatu_count;                // ���q��
	LBMen tmp_taatsu_stat[MEN_MAX];     // ���q���
	int tmp_taatsu_hai[MEN_MAX];        // ���q�v

	// -----------------------------
	// �R���X�g���N�^
	// -----------------------------

	// �R���X�g���N�^
    MJSTkinfo(){};

	// �f�X�g���N�^
    ~MJSTkinfo(){};

	// -----------------------------
	// �֐�
	// -----------------------------

	// �N���X�������E�㏈��
	void TkinfoInit();
	void TkinfoPost();

	// ��̏������E�㏈��
	void TakuInit();
	void TakuPost();

	// �ǂ̏������E�㏈��
	void KyokuInit();
	void KyokuPost();

	// �A�N�V�������ݒ�
	void SetActInfo(int kyoku_index, LBTkSt tmp_act_stat, int tmp_act_ply, int tmp_react_ply, int tmp_act_hai, bool tmp_act_aka);

	// �����ݒ�
	void SetNakiInfo(int kyoku_index, LBMen tmp_naki_stat, int tmp_naki_ply, int tmp_naki_actid, int tmp_naki_hai, int tmp_naki_idx, int tmp_naki_aka_count);

	// �a�����ݒ�
	void SetAgariInfo(int kyoku_index, LBAgariTehai tmp_agari_stat, int tmp_agari_ply, int tmp_furikomi_ply, bool tmp_tsumoagari_flg, int tmp_agari_hai, bool tmp_agari_aka);

	// �V�a�E���[�`�m�F
	void Check_Tenho_Riichi(int kyoku_index, int tmp_agari_ply);

	// �A�N�V�������擾���C������
	void Check_Ply_ActTehai(int kyoku_index, int actid);                       // �S�v���[���[�̎�v�m�F

	// �A�N�V�������擾
	void Check_Actid_Haipai(int kyoku_index, int actid);                       // �z�v���̏���
	void Check_Actid_Hai_count(int kyoku_index, int actid);                    // ����v���[���[�̎�v���
	void Check_Actid_LastHai(int kyoku_index, int actid);                      // �Ō�v�̏���

	// ��v�e�[�u���ݒ�
	void settehaitbl(int kyoku_index, int actid, int pnum);                    // ��v�e�[�u����`
	void settehaitbl_sute_stat(int kyoku_index, int actid, int pnum);          // �̔v�̃e�[�u���ʒu�ݒ�
	void settehaitbl_shanten(int kyoku_index, int actid, int pnum);            // ���̗L��(�̔v�O)��Ԃ̎̔v���Ƃ̌������m�F
	void setmachi(int kyoku_index, int actid, int pnum);                       // �҂��v�ݒ�

	// �������m�F - ���C������
	void ChkShanten(int pnum);                  // �������m�F(���C��)

	// �������m�F - �ʏ�`��
	void NormalShanten(int pnum);               // �������m�F(�ʏ�)
	void mentu_cut(int pnum,int hai);           // �ʎq�폜����(�T�u�֐�)
	void taatu_cut(int pnum,int hai);           // ���q�폜����(�T�u�֐�)

	// �������m�F - ����`��
	void KokushiShanten(int pnum);              // �������m�F(���m���o)

};

#endif /* TKINFO_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
