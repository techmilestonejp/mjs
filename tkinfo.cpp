/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.1.228(MJAI���O�\���FDisp�֐��_�u�����\������)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F tkinfo.cpp
 * �N���X��       �F MJSTkinfo
 * �����T�v       �F ����N���X
 * Ver0.0.8�쐬�� �F 2012/05/04 08:57:12
 * Ver0.1.0�쐬�� �F 2022/04/11 15:57:39
 * Ver0.1.1�쐬�� �F 2022/06/30 21:19:01
 * Ver0.1.2�쐬�� �F 2022/08/31 22:19:54
 * �ŏI�X�V��     �F 2024/11/16 10:47:17
 * 
 * Copyright (c) 2010-2023 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "tkinfo.h"

/* ---------------------------------------------------------------------------------------------- */
// �O����
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::TkinfoInit(){

	// HUM�v���C���[�h�̏�����
	ply_hum_mode = 0;

}

/* ---------------------------------------------------------------------------------------------- */
// �㏈��
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::TkinfoPost(){

}

/* ---------------------------------------------------------------------------------------------- */
// �쏉����
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::TakuInit(){

	// �Ǎ\���̂̔z���`
	kyoku = new MJSkyokuinfo[KYOKU_MAX];
	sc    = new MJSScore;

	// ----------------------------------------
	// ����̐ݒ�
	// ----------------------------------------
	end_flg = false;
	stat = TAKUSTART;
	kyoku_index = 0;     // �����Ǘ��p�̋�ID
	hai_point  = 0;      // �c��v��

	// �������_
	init_score = INITSCORE;

	// ���_�ݒ�
	for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){
		kyoku[kyoku_index].ply_kyoku_start_score[tmp_pnum] = init_score;
	}

	// �����V�[�h
	core_seed_num = 0;

	// ----------------------------------------
	// ����̐ݒ�(�Ǌ֘A)
	// ----------------------------------------

	kyoku[kyoku_index].kyoku    = 0;
	kyoku[kyoku_index].tsumibo  = 0;
	kyoku[kyoku_index].riichbo  = 0;
	kyoku[kyoku_index].seed_num = 0;

	// ----------------------------------------
	// ���m�v�̎w��
	// ----------------------------------------

	kokushi_hai_num[0]  = MAN1NUM;
	kokushi_hai_num[1]  = PIN1NUM;
	kokushi_hai_num[2]  = SOU1NUM;
	kokushi_hai_num[3]  = MAN9NUM;
	kokushi_hai_num[4]  = PIN9NUM;
	kokushi_hai_num[5]  = SOU9NUM;
	kokushi_hai_num[6]  = TONNUM;
	kokushi_hai_num[7]  = NANNUM;
	kokushi_hai_num[8]  = SHANUM;
	kokushi_hai_num[9]  = PEINUM;
	kokushi_hai_num[10] = HAKUNUM;
	kokushi_hai_num[11] = HATSUNUM;
	kokushi_hai_num[12] = CHUNNUM;

	// ----------------------------------------
	// �Ǐ�����
	// ----------------------------------------
	KyokuInit();

}

/* ---------------------------------------------------------------------------------------------- */
// ��I������
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::TakuPost(){

	// �ǏI������
	KyokuPost();

	// �Ǎ\���̂̉��
	delete[] kyoku;
	delete sc;

}


/* ---------------------------------------------------------------------------------------------- */
// �Ǐ���������
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::KyokuInit(){

	// ----------------------------------------
	// �Ǐ�����
	// ----------------------------------------
	kyoku[kyoku_index].act_count = 0;
	ply_turn = 0;

	// �h������
	kyoku[kyoku_index].doracount = 1;

	// �h���\���v
	for( int tmp_i = 0; tmp_i < 5; tmp_i++){
		kyoku[kyoku_index].dora[tmp_i] = 0;
		kyoku[kyoku_index].uradora[tmp_i] = 0;
		kyoku[kyoku_index].dora_aka[tmp_i] = false;
		kyoku[kyoku_index].uradora_aka[tmp_i] = false;
	}

	// �v�e�[�u���̎̔v�ʒu�ԍ�
	ply_tbl_hum_sutehai_statnum = 0;               // �v�e�[�u���̎̔v�ʒu�ԍ�(HUM�p)

	// COM�̎�v���̗L��
	com_no_chk_tehai_flg = false;

	// ----------------------------------------
	// ply�A�N�V�������
	// ----------------------------------------
	ply_act = NOACT;

	// ----------------------------------------
	// �v�R�|�C���^
	// ----------------------------------------
	hai_point     = HAI_POINT_START;
	rinshan_point = RINSHAN_POINT_START;

	// �a����
	kyoku[kyoku_index].agari_ply_count = 0;

	// ���ǎ�
	kyoku[kyoku_index].ply_agari_yk[0].ply_tempai_count = 0;

	// ----------------------------------------
	// �Ǐ��̏�����(�v���[���[����)
	// ----------------------------------------
	for( int tmp_pnum = 0; tmp_pnum  < PLAYER_MAX; tmp_pnum++){

		// ----------------------------------------
		// �ǔz����̏�����
		// ----------------------------------------

		// �z�v������
	    for(int tmp_i=0; tmp_i< PAI_MAX; tmp_i++){
			kyoku[kyoku_index].tehai[tmp_pnum][tmp_i] = 0;
		}

		// �Ԕv������
		kyoku[kyoku_index].aka_count[tmp_pnum][0] = 0;
		kyoku[kyoku_index].aka_count[tmp_pnum][1] = 0;
		kyoku[kyoku_index].aka_count[tmp_pnum][2] = 0;

		// �v���[���[���Ƃ̎N�����̏�����
		kyoku[kyoku_index].naki_count[tmp_pnum]  = 0;
		kyoku[kyoku_index].ankan_count[tmp_pnum] = 0;
		kyoku[kyoku_index].kakan_count[tmp_pnum] = 0;

		// ���ǎ�
		kyoku[kyoku_index].ply_agari_yk[kyoku[kyoku_index].agari_ply_count].ply_tempai_flg[tmp_pnum] = false;

		// ----------------------------------------
		// ��v�q�X�g�O�����E��v�e�[�u���̏�����
		// ----------------------------------------

		// �v�e�[�u���̏�����
		ply_act_tehaicount[tmp_pnum] = 0;
		ply_tbl_com_sutehai_statnum[tmp_pnum] = 0;
		ply_tbl_hum_sutehai_statnum = 0;

		// �v�e�[�u��(�z��)�̏�����
	    for(int tmp_i=0; tmp_i< TEHAI_MAX; tmp_i++){
			ply_act_tehai_shanten_tbl[tmp_pnum][tmp_i] = 8; // �v�e�[�u��(������)
		}

		// ���̏��
		ply_act_tsumo[tmp_pnum] = 0;              // ���̔v
		ply_act_tsumo_aka[tmp_pnum] = false;      // ���̂̐Ԕv
		ply_act_tsumo_shanten[tmp_pnum] = 8;      // ���̂̌�����

		// �̔v���
		ply_act_sute[tmp_pnum] = 0;               // �̔v
		ply_act_sute_aka[tmp_pnum] = false;       // �̔v�̐Ԕv

		// ������
		shanten_total[tmp_pnum]   = 14;           // ����������
		shanten_normal[tmp_pnum]  = 14;           // �ʏ������
		shanten_chitoi[tmp_pnum]  = 14;           // ���Ό�����
		shanten_kokushi[tmp_pnum] = 14;           // ���m������

		// �V�����e���Z�o����
		naki_count_none_kakan[tmp_pnum] = 0;

		// �Ҕv
		ply_act_machi_count[tmp_pnum] = 0;        // �Ҕv���v��

		// �v���[���[���Ƃ̖��A�N�V����������
		ply_act_naki[tmp_pnum] = ACTNONAKI;

		// �v�e�[�u���̎̔v�ʒu�ԍ�
		ply_tbl_com_sutehai_statnum[tmp_pnum] = 0;     // �v�e�[�u���̎̔v�ʒu�ԍ�(COM�p)

		// ----------------------------------------
		// �A�N�V������񏉊���
		// ----------------------------------------

		// ���ʒm���
		ply_naki_hai[tmp_pnum] = 0;
		ply_naki_idx[tmp_pnum] = 0;
		ply_naki_aka_count[tmp_pnum] = 0;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI������
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::KyokuPost(){

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�������ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::SetActInfo(int kyoku_index, LBTkSt tmp_act_stat, int tmp_act_ply, int tmp_react_ply, int tmp_act_hai, bool tmp_act_aka){

	// �A�N�V�����ԍ��̉��Z
	kyoku[kyoku_index].act_count++;

	// �A�N�V�������o�^
	kyoku[kyoku_index].act_stat[kyoku[kyoku_index].act_count]  = tmp_act_stat;
	kyoku[kyoku_index].act_ply[kyoku[kyoku_index].act_count]   = tmp_act_ply;
	kyoku[kyoku_index].react_ply[kyoku[kyoku_index].act_count] = tmp_react_ply;
	kyoku[kyoku_index].act_hai[kyoku[kyoku_index].act_count]   = tmp_act_hai;
	kyoku[kyoku_index].act_aka[kyoku[kyoku_index].act_count]   = tmp_act_aka;

}

/* ---------------------------------------------------------------------------------------------- */
// �����ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::SetNakiInfo(int kyoku_index, LBMen tmp_naki_stat, int tmp_naki_ply, int tmp_naki_actid, int tmp_naki_hai, int tmp_naki_idx, int tmp_naki_aka_count){

	// �����̐ݒ�
	kyoku[kyoku_index].naki_actid[tmp_naki_ply][kyoku[kyoku_index].naki_count[tmp_naki_ply]]     = tmp_naki_actid;
	kyoku[kyoku_index].naki_stat[tmp_naki_ply][kyoku[kyoku_index].naki_count[tmp_naki_ply]]      = tmp_naki_stat;
	kyoku[kyoku_index].naki_hai[tmp_naki_ply][kyoku[kyoku_index].naki_count[tmp_naki_ply]]       = tmp_naki_hai;
	kyoku[kyoku_index].naki_idx[tmp_naki_ply][kyoku[kyoku_index].naki_count[tmp_naki_ply]]       = tmp_naki_idx;
	kyoku[kyoku_index].naki_aka[tmp_naki_ply][kyoku[kyoku_index].naki_count[tmp_naki_ply]] = tmp_naki_aka_count;

	// �������c���̉��Z
	kyoku[kyoku_index].naki_count[tmp_naki_ply]++;

	// �ÞȂ̌������Z
	if(tmp_naki_stat == ANKAN){
		// �ÞȂ̌������Z
		kyoku[kyoku_index].ankan_count[tmp_naki_ply]++;
	}

	// ���Ȃ̌������Z
	if(tmp_naki_stat == KAKAN){
		// ���Ȃ̌������Z
		kyoku[kyoku_index].kakan_count[tmp_naki_ply]++;
	}else{
		// ���ȂȂ����������Z
		naki_count_none_kakan[tmp_naki_ply]++;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �a�����ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::SetAgariInfo(int kyoku_index, LBAgariTehai tmp_agari_stat, int tmp_agari_ply, int tmp_furikomi_ply, bool tmp_tsumoagari_flg, int tmp_agari_hai, bool tmp_agari_aka){

	// ���[�`��Ԋm�F
	Check_Tenho_Riichi(kyoku_index, tmp_agari_ply);

	// �a�����ݒ�(�a�����\���̂̐ݒ�)
	sc->SetAgari(
	&kyoku[kyoku_index].ply_agari_yk[kyoku[kyoku_index].agari_ply_count],  // �a�������\����
	kyoku[kyoku_index].kyoku,                          // �ǔԍ�
	kyoku[kyoku_index].ie,                             // �v���[���̉Ə��
	kyoku[kyoku_index].doracount,                      // �\�h���v����
	kyoku[kyoku_index].dora,                           // �\�h���v���
	kyoku[kyoku_index].doracount,                      // ���h���v����
	kyoku[kyoku_index].uradora,                        // ���h���v���
	tmp_agari_stat,                                    // �a���`��
	tmp_agari_ply,                                     // �a���v���[��
	tmp_furikomi_ply,                                  // �U���v���[��
	tmp_tsumoagari_flg,                                // ���̘a���̗L��
	tmp_agari_hai,                                     // �a���v
	tmp_agari_aka,                                     // �a���v�̐Ԕv�L��
	ply_act_tehai[tmp_agari_ply],                      // �a�����̎�v�q�X�g�O����
	ply_act_aka_count[tmp_agari_ply],                  // ��v�̐Ԕv����
	atama_hai,                                         // ���v
	mentu_count,                                       // �ʎq��
	mentu_stat,                                        // �ʎq���
	mentu_hai,                                         // �ʎq�v
	mentu_hai,                                         // �ʎqINDEX
	kyoku[kyoku_index].naki_count[tmp_agari_ply],      // ���ʎq��
	kyoku[kyoku_index].naki_stat[tmp_agari_ply],       // ���ʎq���
	kyoku[kyoku_index].naki_hai[tmp_agari_ply],        // ���ʎq�v
	kyoku[kyoku_index].naki_idx[tmp_agari_ply],        // ���ʎqINDEX
	kyoku[kyoku_index].naki_aka[tmp_agari_ply],        // ���ʎq�Ԕv����
	riichi_flg[tmp_agari_ply],                         // ���[�`�t���O
	riichi_ippatsu_flg[tmp_agari_ply],                 // ���[�`�ꔭ�t���O
	double_riichi_flg[tmp_agari_ply]                   // �_�u�����[�`�t���O
	);

	// �ǏI�����_�̐ݒ�
	for(int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++){
		kyoku[kyoku_index].ply_kyoku_end_score[tmp_i] = kyoku[kyoku_index].ply_kyoku_start_score[tmp_i] 
		                                              + kyoku[kyoku_index].ply_agari_yk[kyoku[kyoku_index].agari_ply_count].kyoku_score[tmp_i];
	}

	// �a���v���[�����̉��Z
	kyoku[kyoku_index].agari_ply_count++;

}

/* ---------------------------------------------------------------------------------------------- */
// �V�a�E���[�`�m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::Check_Tenho_Riichi(int kyoku_index, int tmp_agari_ply){

	// -----------------------------
	// ��Ɨp�ϐ��̒�`
	// -----------------------------

	// �ꔭ���t���O
	bool tmp_ippatsu_naki_flg;
	int tmp_agari_ply_tsumo_count;
	int tmp_agari_ply_riichi_count;

	// -----------------------------
	// �a���v���[���[�̘a�����̉񐔁E���[�`��Ԋm�F(������)
	// -----------------------------

	riichi_flg[tmp_agari_ply]          = false;
	riichi_ippatsu_flg[tmp_agari_ply]  = false;
	double_riichi_flg[tmp_agari_ply]   = false;
	tmp_agari_ply_tsumo_count  = 0;
	tmp_agari_ply_riichi_count = 0;

	// -----------------------------
	// �a���v���[���[�̘a�����̉񐔁E���[�`��Ԋm�F(���C������)
	// -----------------------------

	// ���O����
	tmp_ippatsu_naki_flg = false;

	// �A�N�V�����̊m�F
	for(int tmp_i = 0; tmp_i < kyoku[kyoku_index].act_count+1; tmp_i++){

		// -----------------------------
		// �a���v���[���̎��̉񐔃J�E���g
		// -----------------------------
		if(kyoku[kyoku_index].act_stat[tmp_i] == PLYACTTSUMO &&
		   kyoku[kyoku_index].act_ply[tmp_i]  == tmp_agari_ply ){
			// ���̃J�E���g
			tmp_agari_ply_tsumo_count++;
		}

		// -----------------------------
		// ���[�`�m�F
		// -----------------------------
		if(kyoku[kyoku_index].act_stat[tmp_i] == PLYACTRIICH &&
		   kyoku[kyoku_index].act_ply[tmp_i]  == tmp_agari_ply ){

			// ���[�`���[�h�ύX
			riichi_flg[tmp_agari_ply]=true;

			// �_�u�����[�`�m�F
			if(tmp_agari_ply_tsumo_count == 1){
				// ���[�`���[�h�ύX
				double_riichi_flg[tmp_agari_ply]=true;
			}else{
				// ���[�`���[�h�ύX
				double_riichi_flg[tmp_agari_ply]=false;
			}	

			// ���[�`���ڂ̐ݒ�
			tmp_agari_ply_riichi_count = tmp_agari_ply_tsumo_count;

			// �ꔭ���t���O�̉��ݒ�
			tmp_ippatsu_naki_flg = true;

		}

		// -----------------------------
		// ���m�F
		// -----------------------------
		if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTPON ||
		    kyoku[kyoku_index].act_stat[tmp_i] == PLYACTCHI ||
		    kyoku[kyoku_index].act_stat[tmp_i] == PLYACTMINKAN ){

			// �ꔭ���t���O�̉��ݒ�
			tmp_ippatsu_naki_flg = false;

		}

		// -----------------------------
		// ���[�`�ꔭ�m�F(���̘a��)
		// -----------------------------
		if (kyoku[kyoku_index].act_stat[tmp_i] == PLYTSUMOAGARI && 
			riichi_flg[tmp_agari_ply]    == true &&
		    tmp_agari_ply == kyoku[kyoku_index].act_ply[tmp_i]){

			// �����Ŋ������Ȃ��Ȃ�Έꔭ�a��
			if( tmp_agari_ply_riichi_count + 1 == tmp_agari_ply_tsumo_count &&
			    tmp_ippatsu_naki_flg == true){
				// �ꔭ�a��
				riichi_ippatsu_flg[tmp_agari_ply]=true;
			}else{
				// �ꔭ�a���Ȃ�
				riichi_ippatsu_flg[tmp_agari_ply]=false;
			}
		}

		// -----------------------------
		// ���[�`�ꔭ�m�F(�����a��)
		// -----------------------------
		if (kyoku[kyoku_index].act_stat[tmp_i] == PLYACTRON && 
			riichi_flg[tmp_agari_ply] == true &&
		    kyoku[kyoku_index].act_ply[tmp_i]  == tmp_agari_ply ){

			// �����ł���Έꔭ
			if(tmp_agari_ply_riichi_count == tmp_agari_ply_tsumo_count &&
			    tmp_ippatsu_naki_flg == true){
				// �ꔭ�a��
				riichi_ippatsu_flg[tmp_agari_ply]=true;
			}else{
				// �ꔭ�a���Ȃ�
				riichi_ippatsu_flg[tmp_agari_ply]=false;
			}
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �S�v���[���[�̎�v�m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::Check_Ply_ActTehai(int kyoku_index, int actid){

	// �z�v
	Check_Actid_Haipai(kyoku_index, actid);

	// ���C������
	Check_Actid_Hai_count(kyoku_index, actid);

	// �Ō�v�̏���
	Check_Actid_LastHai(kyoku_index, actid);

}

/* ---------------------------------------------------------------------------------------------- */
// �z�v���̏���
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::Check_Actid_Haipai(int kyoku_index, int actid){

	// ----------------------------------------
	// �z�v����̐ݒ�
	// ----------------------------------------

	// �e�[�u�����̍X�V(�S�v���[���[)
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

		// �̔v������
		ply_act_kawa_count[tmp_pnum] = 0;

		// ----------------------------------------
		// ��v�m�F(�z�v)
		// ----------------------------------------
		for(int tmp_i = 0; tmp_i < PAI_MAX; tmp_i++){
			ply_act_tehai[tmp_pnum][tmp_i] = kyoku[kyoku_index].tehai[tmp_pnum][tmp_i];
		}

		// ----------------------------------------
		// �Ԕv�m�F(�z�v)
		// ----------------------------------------
		for(int tmp_aka_grp = 0; tmp_aka_grp < AKA_TYPE_MAX_COUNT; tmp_aka_grp++){
			// �Ԕv�m�F(�z�v)
			ply_act_aka_count[tmp_pnum][tmp_aka_grp] = kyoku[kyoku_index].aka_count[tmp_pnum][tmp_aka_grp];
		}

		// ----------------------------------------
		// �Ō�v�m�F�F�z�v��
		// ----------------------------------------
		if( kyoku[kyoku_index].act_stat[actid] == HAIPAI ){

			// ----------------------------------------
			// 1. ���́E�̔v���̏�����
			// ----------------------------------------
			ply_act_tsumo[tmp_pnum] = 0;
			ply_act_sute[tmp_pnum]  = 0;
			ply_tbl_com_sutehai_statnum[tmp_pnum] = 0 ;
			ply_act_tsumo_aka[tmp_pnum] = false ;
			ply_act_sute_aka[tmp_pnum]  = false ;

			// ----------------------------------------
			// 2. �V�����e���m�F(���̂Ȃ��F���Ȃ�)
			// ----------------------------------------
			if(com_no_chk_tehai_flg == false){
				ChkShanten(tmp_pnum);
			}

			// ----------------------------------------
			// 3. �Ҕv�ݒ�
			// ----------------------------------------
			setmachi(kyoku_index, actid, tmp_pnum);

			// ----------------------------------------
			// 4. �e�[�u�����ݒ�
			// ----------------------------------------
			settehaitbl(kyoku_index, actid, tmp_pnum);

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��v�q�X�g�O�����A��v�e�[�u���ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::Check_Actid_Hai_count(int kyoku_index, int actid){

	// ----------------------------------------
	// ��Ɨp�ϐ�
	// ----------------------------------------
	int tmp_chi_num;
	int pnum;

	// �c�莩�̐�
	remain_hai_count = PAI_COUNT_MAX - 14 - TEHAI_MAX*PLAYER_MAX; // �c�莩�̔v�̐��F136 - 14 - 13*4(52)
	remain_rinshan_count = 4;                                     // �c�胊���V�����v�̐�

	// �N���C�A���g���[�h�p�E������`
	if(com_no_chk_tehai_flg == true){
		// �����w��
		ply_act_tehaicount[0] = TEHAI_MAX;
		ply_act_tehaicount[1] = TEHAI_MAX;
		ply_act_tehaicount[2] = TEHAI_MAX;
	}

	// ----------------------------------------
	// ��v�m�F(��A��ActID)
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i <= actid; tmp_i++){

		// �A�N�V�����v���[���̒�`
		pnum = kyoku[kyoku_index].act_ply[tmp_i];

		// ----------------------------------------
		// �� 1.���̎��̎�v���̑���
		// ----------------------------------------
		if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTTSUMO ){

			// ��v�q�X�g�O�����̒ǉ�
 			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]++;

			// �Ԕv�̏���
			if( kyoku[kyoku_index].act_aka[tmp_i] == true ){
				ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[tmp_i]/10]++;
			}

			// �c��v
			remain_hai_count--;

		// ----------------------------------------
		// �� 1.���̎�(�����V����)�̎�v���̑���
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYRINSHAN ){

			// ��v�q�X�g�O�����̒ǉ�
 			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]++;

			// �Ԕv�̏���
			if( kyoku[kyoku_index].act_aka[tmp_i] == true ){
				ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[tmp_i]/10]++;
			}

			// �c��v
			remain_hai_count--;
			remain_rinshan_count--;

		// ----------------------------------------
		// �� 2.�̔v�E���̐؂�
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTSUTE || 
		          kyoku[kyoku_index].act_stat[tmp_i] == PLYACTTSUMOGIRI ){

			// ��v�q�X�g�O�������Z
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]--;

			// �͐ݒ�
			ply_act_kawa[pnum][ply_act_kawa_count[pnum]] = kyoku[kyoku_index].act_hai[tmp_i];

			// �Ԕv�̏���
			if( kyoku[kyoku_index].act_aka[tmp_i] == true ){
				ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[tmp_i]/10]--;
				ply_act_kawa_aka[pnum][ply_act_kawa_count[pnum]] = true;
			}else{
				// �̔v�͍��v�ݒ�
				ply_act_kawa_aka[pnum][ply_act_kawa_count[pnum]] = false;
			}

			// �̓��[�h�ݒ�(���[�`��Ԋm�F)
			if( kyoku[kyoku_index].act_stat[tmp_i-1] == PLYACTRIICH ){
				ply_act_kawa_mode[pnum][ply_act_kawa_count[pnum]] = RIICHI_STAT_NUM;
			}else{
				ply_act_kawa_mode[pnum][ply_act_kawa_count[pnum]] = 0;
			}

			// �͖����̉��Z
			ply_act_kawa_count[pnum]++;

		// ----------------------------------------
		// �� 3.���̔v
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTNAKISUTE ){

			// ��v�q�X�g�O�������Z
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]--;

			// �͐ݒ�
			ply_act_kawa[pnum][ply_act_kawa_count[pnum]] = kyoku[kyoku_index].act_hai[tmp_i];

			// �Ԕv�̏���
			if( kyoku[kyoku_index].act_aka[tmp_i] == true ){
				ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[tmp_i]/10]--;
				ply_act_kawa_aka[pnum][ply_act_kawa_count[pnum]] = true;
			}else{
				// �̔v�͍��v�ݒ�
				ply_act_kawa_aka[pnum][ply_act_kawa_count[pnum]] = false;
			}

			// �̓��[�h�ݒ�
			ply_act_kawa_mode[pnum][ply_act_kawa_count[pnum]] = 0;

			// �͖����̉��Z
			ply_act_kawa_count[pnum]++;

		// ----------------------------------------
		// �� 4.�A�N�V�������Ƃ̎�v���̑��� - �|��
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTPON ){

			// ��v����2�����炷
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]-=2;

			// ���ꂽ�v���[���̎̔v���D�F�ɒ��F����B
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] = 
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] + HAI_COLOR_NUM_GRAY;

			// ���v�̖�������
			if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
				ply_act_tehaicount[pnum]-=3;
			}

		// ----------------------------------------
		// �� 5.�A�N�V�������Ƃ̎�v���̑��� - �`�[
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTCHI ){

			// �������̎N���ԍ����o
			for(int tmp_j = 0; tmp_j < kyoku[kyoku_index].naki_count[pnum]; tmp_j++){
				if(kyoku[kyoku_index].naki_actid[pnum][tmp_j] == tmp_i){
					tmp_chi_num = tmp_j;
				}
			}

			// ���v�폜
			ply_act_tehai[pnum][kyoku[kyoku_index].naki_idx[pnum][tmp_chi_num]]--;
			ply_act_tehai[pnum][kyoku[kyoku_index].naki_idx[pnum][tmp_chi_num]+1]--;
			ply_act_tehai[pnum][kyoku[kyoku_index].naki_idx[pnum][tmp_chi_num]+2]--;
			ply_act_tehai[pnum][kyoku[kyoku_index].naki_hai[pnum][tmp_chi_num]]++;

			// ���ꂽ�v���[���̎̔v���D�F�ɒ��F����B
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] = 
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] + HAI_COLOR_NUM_GRAY;

			// ���v�̖�������
			if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
				ply_act_tehaicount[pnum]-=3;
			}

		// ----------------------------------------
		// �� 5.�A�N�V�������Ƃ̎�v���̑��� - ����
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTMINKAN ){

			// �v�̌��Z
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]-=3 ;

			// ���ꂽ�v���[���̎̔v���D�F�ɒ��F����B
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] = 
			ply_act_kawa_mode[kyoku[kyoku_index].react_ply[tmp_i]][ply_act_kawa_count[kyoku[kyoku_index].react_ply[tmp_i]]-1] + HAI_COLOR_NUM_GRAY;

			// ���v�̖�������
			if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
				ply_act_tehaicount[pnum]-=3;
			}

		// ----------------------------------------
		// �� 6.�A�N�V�������Ƃ̎�v���̑��� - �Þ�
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTANKAN ){
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]-=4 ;

			// ���v�̖�������
			if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
				ply_act_tehaicount[pnum]-=3;
			}

		// ----------------------------------------
		// �� 7.�A�N�V�������Ƃ̎�v���̑��� - ����
		// ----------------------------------------
		}else if( kyoku[kyoku_index].act_stat[tmp_i] == PLYACTKAKAN ){
			ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[tmp_i]]--;

		// ----------------------------------------
		// �� 8.��O����
		// ----------------------------------------
		}else{
			// ���̑��̏���
		}

	}

	// ----------------------------------------
	// �Ԕv�m�F(���E�N���v)
	// ----------------------------------------

	// �e�[�u�����̍X�V(�S�v���[���[)
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

		// �v���[���[���Ƃ̖��ʎq��
		for(int tmp_i = 0; tmp_i < kyoku[kyoku_index].naki_count[tmp_pnum]; tmp_i++){

			// ���v�̐Ԕv�̐����m�F
			if( kyoku[kyoku_index].naki_actid[tmp_pnum][tmp_i] <= actid && 
			    kyoku[kyoku_index].naki_aka[tmp_pnum][tmp_i] > 0){

				// �����̐Ԕv�����������炷
				ply_act_aka_count[tmp_pnum][kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i]/10] = 
				ply_act_aka_count[tmp_pnum][kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i]/10] - kyoku[kyoku_index].naki_aka[tmp_pnum][tmp_i];

				// ���A�N�V����(�̔v)�ŏE���Ă����Ȃ�A+1����
				if(kyoku[kyoku_index].act_aka[kyoku[kyoku_index].naki_actid[tmp_pnum][tmp_i]-1]  == true       && 
				   ( kyoku[kyoku_index].act_stat[kyoku[kyoku_index].naki_actid[tmp_pnum][tmp_i]-1] == PLYACTSUTE || 
				     kyoku[kyoku_index].act_stat[kyoku[kyoku_index].naki_actid[tmp_pnum][tmp_i]-1] == PLYACTTSUMOGIRI || 
				     kyoku[kyoku_index].act_stat[kyoku[kyoku_index].naki_actid[tmp_pnum][tmp_i]-1] == PLYACTNAKISUTE  ) 
				   ){

					// ��v�q�X�g�O�����̉��Z
					ply_act_aka_count[tmp_pnum][kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i]/10]++;

				}
			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �Ō�v�̏���
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::Check_Actid_LastHai(int kyoku_index, int actid){

	// ----------------------------------------
	// �Ō�v�Ɋւ���A�N�V�������Ƃ̏���)
	// ----------------------------------------

	int pnum;
	int tmp_tsumoari_shanten_total;
	int tmp_tsumoari_shanten_normal;
	int tmp_tsumoari_shanten_kokushi;
	int tmp_tsumoari_shanten_chitoi;

	// �A�N�V�����v���[���̒�`
	pnum = kyoku[kyoku_index].act_ply[actid];

	// �A�N�V�����v�̒�`
	// tmp_act_hai  = kyoku[kyoku_index].act_hai[actid];

	// (�f�o�O�p)�A�N�V�����v���K��̔ԍ��ł���Ȃ�
	// if ( tmp_act_hai > 0 && tmp_act_hai < PAI_MAX){

	// ----------------------------------------
	// �� 1.�Ō�v�F����
	// ----------------------------------------
	if ( kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMO || 
	     kyoku[kyoku_index].act_stat[actid] == PLYRINSHAN  ){

		// ----------------------------------------
		// 1-1.���́E�̔v���̏�����
		// ----------------------------------------
		for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

			ply_act_tsumo[tmp_pnum] = 0;
			ply_act_tsumo_aka[tmp_pnum] = false ;
			ply_act_tsumo_shanten[pnum] = 0;

			ply_act_sute[tmp_pnum]  = 0;
			ply_tbl_com_sutehai_statnum[tmp_pnum] = 0 ;
			ply_act_sute_aka[tmp_pnum]  = false ;

		}

		// ----------------------------------------
		// 1-2.���̏���`
		// ----------------------------------------
		ply_act_tsumo[pnum]      = kyoku[kyoku_index].act_hai[actid];
		ply_act_tsumo_aka[pnum]  = kyoku[kyoku_index].act_aka[actid];

		// ----------------------------------------
		// 1-3.���̗L�������
		// ----------------------------------------
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		// ���u��
		// tmp_tsumoari_shanten = shanten_normal[pnum];
		tmp_tsumoari_shanten_total = shanten_total[pnum];
		tmp_tsumoari_shanten_normal = shanten_normal[pnum];
		tmp_tsumoari_shanten_kokushi = shanten_kokushi[pnum];
		tmp_tsumoari_shanten_chitoi = shanten_chitoi[pnum];

		// ----------------------------------------
		// 1-8.�e�[�u����v���Ƃ̃V�����e���Z�o
		// ----------------------------------------
// 		if( shanten_normal[pnum] == 0){
 		if( shanten_total[pnum] == 0){
			settehaitbl_shanten(kyoku_index, actid, pnum);
		}

		// ----------------------------------------
		// 1-4.���̔v�̎�v�q�X�g�O������-1����
		// ----------------------------------------
		if ( ply_act_tsumo[pnum] > 0 && ply_act_tsumo[pnum] < 38){
			ply_act_tehai[pnum][ply_act_tsumo[pnum]]--;
		}

		// �Ԕv�̏���
		if( ply_act_tsumo_aka[pnum] == true ){
			ply_act_aka_count[pnum][ply_act_tsumo[pnum]/10]--;
		}
		
		// ----------------------------------------
		// 1-5.���̐؂�̃V�����e��(���̂Ȃ��V�����e��)
		// ----------------------------------------
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}
		// �V�����e�����̐ݒ�
		ply_act_tsumo_shanten[pnum] = shanten_total[pnum];
		// �̔v�s�L���̐ݒ�
		if( shanten_total[pnum] == 0){
			ply_act_tsumo_can_sute[pnum] = true;
		}else{
			ply_act_tsumo_can_sute[pnum] = false;
		}
		// ----------------------------------------
		// 1-6.�V�����e�����̐ݒ�
		// ----------------------------------------
		// shanten_normal[pnum] = tmp_tsumoari_shanten;
		shanten_total[pnum] = tmp_tsumoari_shanten_total;
		shanten_normal[pnum] = tmp_tsumoari_shanten_normal;
		shanten_kokushi[pnum] = tmp_tsumoari_shanten_kokushi;
		shanten_chitoi[pnum] = tmp_tsumoari_shanten_chitoi;

		// ----------------------------------------
		// 1-7.�e�[�u�����ݒ�
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

	// ----------------------------------------
	// �� 2.�Ō�v�F�̔v
	// ----------------------------------------
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYACTSUTE      || 
			  kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMOGIRI ){

		// ----------------------------------------
		// 2-1. ���̖����V�����e���̎Z�o
		// ----------------------------------------
		// naki_count[pnum] =  kyoku[kyoku_index].naki_count[pnum] - kyoku[kyoku_index].kakan_count[pnum] ;   // ���ʎq��
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		// ----------------------------------------
		// 2-2. �Ҕv�ݒ�
		// ----------------------------------------
		setmachi(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 2-3. ���̔v��`
		// ----------------------------------------
		if (kyoku[kyoku_index].act_stat[actid-1] == PLYACTRIICH){
			ply_act_tsumo[pnum]     = kyoku[kyoku_index].act_hai[actid-2];
			ply_act_tsumo_aka[pnum] = kyoku[kyoku_index].act_aka[actid-2];
		}else{
			ply_act_tsumo[pnum]     = kyoku[kyoku_index].act_hai[actid-1];
			ply_act_tsumo_aka[pnum] = kyoku[kyoku_index].act_aka[actid-1];
		}

		// ----------------------------------------
		// 2-4. �̔v��`
		// ----------------------------------------
		ply_act_sute[pnum]     = kyoku[kyoku_index].act_hai[actid];
		ply_act_sute_aka[pnum] = kyoku[kyoku_index].act_aka[actid]; // �Ԕv��`

		// ----------------------------------------
		// 2-5. �c�����͌��Z
		// ----------------------------------------
		if(ply_act_tsumo[pnum] > 0 && ply_act_tsumo[pnum] < PAI_MAX){
			ply_act_tehai[pnum][ply_act_tsumo[pnum]]--;
			// �Ԕv�̏���
			if( ply_act_tsumo_aka[pnum] == true ){
				ply_act_aka_count[pnum][ply_act_tsumo[pnum]/10]--;
			}
		}

		// ----------------------------------------
		// 2-6. �̔v���͉��Z
		// ----------------------------------------
		if(ply_act_sute[pnum] > 0 && ply_act_sute[pnum] < PAI_MAX){
			ply_act_tehai[pnum][ply_act_sute[pnum]]++;
			// �Ԕv�̏���
			if( ply_act_sute_aka[pnum] == true ){
				ply_act_aka_count[pnum][ply_act_sute[pnum]/10]++;
			}
		}

		// ----------------------------------------
		// 2-7. �e�[�u�����ݒ�
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 2-8. �̔v�̃e�[�u���ʒu����
		// ----------------------------------------
		settehaitbl_sute_stat(kyoku_index, actid, pnum);

	// ----------------------------------------
	// �� 3.�Ō�v�F���̔v
	// ----------------------------------------
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYACTNAKISUTE ){

		// ----------------------------------------
		// 3-1. ���̖����V�����e���̎Z�o
		// ----------------------------------------
		// naki_count[pnum] =  kyoku[kyoku_index].naki_count[pnum] - kyoku[kyoku_index].kakan_count[pnum] ;   // ���ʎq��
		// NormalShanten(pnum);
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		// ----------------------------------------
		// 3-2. �Ҕv�ݒ�
		// ----------------------------------------
		setmachi(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 3-3. �̔v����`
		// ----------------------------------------
		ply_act_sute[pnum]     = kyoku[kyoku_index].act_hai[actid]; // �̔v��`
		ply_act_sute_aka[pnum] = kyoku[kyoku_index].act_aka[actid]; // �Ԕv��`

		// ----------------------------------------
		// 3-4. �̔v�̎�v�q�X�g�O������+1����
		// ----------------------------------------
		ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[actid]]++;

		// �Ԕv�̏���
		if( kyoku[kyoku_index].act_aka[actid] == true ){
			ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[actid]/10]--;
		}

		// ----------------------------------------
		// 3-5. �e�[�u�����ݒ�
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 3-6. �̔v�̃e�[�u���ʒu����
		// ----------------------------------------
		settehaitbl_sute_stat(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 3-7. ���v�̖�������
		// ----------------------------------------
		if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
			ply_act_tehaicount[pnum]++;
		}

	// ----------------------------------------
	// �� 4.�Ō�v�F�|���A�`�[
	// ----------------------------------------
	// �Ōオ�|���E�`�[�Ȃ玩�̂���V�����e���Z�o
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYACTPON ||
			  kyoku[kyoku_index].act_stat[actid] == PLYACTCHI ){

		// ----------------------------------------
		// 4-1. ���̗L�������
		// ----------------------------------------
		// �V�����e���m�F(���̂���)
		// naki_count[pnum] =  kyoku[kyoku_index].naki_count[pnum] - kyoku[kyoku_index].kakan_count[pnum] ;   // ���ʎq��
		// NormalShanten(pnum);
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		// ----------------------------------------
		// 4-2. ���́E�̔v���̏�����
		// ----------------------------------------
		for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){
			ply_act_tsumo[tmp_pnum] = 0;
			ply_act_sute[tmp_pnum]  = 0;
			ply_tbl_com_sutehai_statnum[tmp_pnum] = 0 ;
			ply_act_tsumo_aka[tmp_pnum] = false ;
			ply_act_sute_aka[tmp_pnum]  = false ;
		}

		// ----------------------------------------
		// 4-3. �e�[�u�����ݒ�
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

		// ----------------------------------------
		// 4-4. �̔v�s�e�[�u���̍X�V
		// ----------------------------------------
		for(int tmp_i = 0; tmp_i < ply_act_tehaicount[pnum]; tmp_i++){
			ply_act_tehai_can_sute_tbl[pnum][tmp_i] = true;
		}

		// ----------------------------------------
		// 4-5. ���v�̖�������
		// ----------------------------------------
		if(com_no_chk_tehai_flg == true && pnum != HUM_PLY_SEKI_NUM){
			// ply_act_tehaicount[pnum]++;
		}

	// ----------------------------------------
	// �� 5.�Ō�v�F�A���J���A�~���J���A�J�J��
	// ----------------------------------------
	// �Ōオ�J���Ȃ�A�������̂�
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYACTMINKAN || 
	          kyoku[kyoku_index].act_stat[actid] == PLYACTANKAN  || 
	          kyoku[kyoku_index].act_stat[actid] == PLYACTKAKAN  ){

		// ----------------------------------------
		// 5-1. ���́E�̔v���̏�����
		// ----------------------------------------
		for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

			ply_act_tsumo[tmp_pnum] = 0;
			ply_act_sute[tmp_pnum]  = 0;
			ply_tbl_com_sutehai_statnum[tmp_pnum] = 0 ;
			ply_act_tsumo_aka[tmp_pnum] = false ;
			ply_act_sute_aka[tmp_pnum]  = false ;

		}

		// ----------------------------------------
		// 5-2. ���̂Ȃ��V�����e���v�Z
		// ----------------------------------------


		// ----------------------------------------
		// 5-3. �e�[�u�����ݒ�
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

	// ----------------------------------------
	// �� 6.�Ō�v�F���̘a����
	// ----------------------------------------
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI){

		// ----------------------------------------
		// �a���v���܂߂��V�����e���v�Z
		// ----------------------------------------
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		// ----------------------------------------
		// ���̕���-1
		// ----------------------------------------
		ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[actid]]--;  // ���̔v�̖߂�

		// �Ԕv�̏���
		if( kyoku[kyoku_index].act_aka[actid] == true ){
			ply_act_aka_count[pnum][kyoku[kyoku_index].act_hai[actid]/10]--;
		}

		// ----------------------------------------
		// �e�[�u�����ݒ�
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

	// ----------------------------------------
	// �� 7.�Ō�v�F�ǌ��ʕ\��(���̘a��)
	// ----------------------------------------
	}else if( kyoku[kyoku_index].act_stat[actid]   == KYOKURESULT && 
	          kyoku[kyoku_index].act_stat[actid-1] == PLYTSUMOAGARI){

		// ----------------------------------------
		// �a���v���܂߂��V�����e���v�Z
		// ----------------------------------------

		// �V�����e���v�Z
		if(com_no_chk_tehai_flg == false){
			ChkShanten(kyoku[kyoku_index].act_ply[actid-1]);
		}

		// ----------------------------------------
		// ���̕���-1
		// ----------------------------------------
		ply_act_tehai[kyoku[kyoku_index].act_ply[actid-1]][kyoku[kyoku_index].act_hai[actid-1]]--;             // ���̔v�̖߂�

		// �Ԕv�̏���
		if( kyoku[kyoku_index].act_aka[actid] == true ){
			ply_act_aka_count[kyoku[kyoku_index].act_ply[actid-1]][kyoku[kyoku_index].act_hai[actid-1]/10]--;  // �Ԕv�߂�
		}

		// ----------------------------------------
		// �e�[�u�����ݒ�
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, kyoku[kyoku_index].act_ply[actid-1]);

	// ----------------------------------------
	// �� 8.�Ō�v�F�����a����
	// ----------------------------------------
	}else if( kyoku[kyoku_index].act_stat[actid] == PLYACTRON){

		// ----------------------------------------
		// 8-1. �a���v���܂߂��V�����e���v�Z
		// ----------------------------------------
		ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[actid]]++;   // �����v��+1

		// �V�����e���v�Z
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}

		ply_act_tehai[pnum][kyoku[kyoku_index].act_hai[actid]]--;   // �����v�̖߂�

		// ----------------------------------------
		// 8-2. �e�[�u�����ݒ�
		// ----------------------------------------
		settehaitbl(kyoku_index, actid, pnum);

	// ----------------------------------------
	// �� 9.�Ō�v�F���̑��A�����v���[���ȊO
	// ----------------------------------------
	}else{

	}

	// ----------------------------------------
	// �e�[�u�����̍X�V(���̑��v���[���[)
	// ----------------------------------------
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

		// �Ō�A�N�V�����v���[���[�łȂ��ꍇ
		if ( kyoku[kyoku_index].act_stat[actid] != HAIPAI && tmp_pnum != pnum){

			// ----------------------------------------
			// x-1. �e�[�u�����ݒ�
			// ----------------------------------------
			settehaitbl(kyoku_index, actid, tmp_pnum);

			// ----------------------------------------
			// x-2.���̖����V�����e���̎Z�o
			// �����a��	�A���̘a�����̏ꍇ�A�U���v���[���[�̓��ꏈ�����K�v�ƂȂ�B
			// ����ȊO�̓V�����e�����Z�o����
			// ----------------------------------------
			if( kyoku[kyoku_index].act_stat[actid] != PLYACTRON && 
				kyoku[kyoku_index].act_stat[actid] != PLYTSUMOAGARI){ 

				// �V�����e���Z�o
				if(com_no_chk_tehai_flg == false){
					ChkShanten(tmp_pnum);
				}

			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��v�e�[�u���ݒ�p
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::settehaitbl(int kyoku_index, int actid, int pnum){

	// �Ԕv���̉��ݒ�
	int tmp_aka_man;
	int tmp_aka_pin;
	int tmp_aka_sou;

	tmp_aka_man = ply_act_aka_count[pnum][0];
	tmp_aka_pin = ply_act_aka_count[pnum][1];
	tmp_aka_sou = ply_act_aka_count[pnum][2];

	// ----------------------------------------
	// �e�[�u�����̊i�[
	// ----------------------------------------

	// �N���C�A���g���[�h��COM�v���[���[�͏������Ȃ�
	if(com_no_chk_tehai_flg == false || pnum == HUM_PLY_SEKI_NUM){

		// ��v���̏�����
		ply_act_tehaicount[pnum] = 0;

		// ��v�e�[�u���̐ݒ�
		for(int tmp_i = 1; tmp_i < PAI_MAX; tmp_i++){

			// ��v�̐������J��Ԃ�
			for(int tmp_j = 0; tmp_j < ply_act_tehai[pnum][tmp_i]; tmp_j++){

				// ��v�e�[�u���ݒ�
				ply_act_tehaitbl[pnum][ply_act_tehaicount[pnum]]=tmp_i;

				// �Ԕv�e�[�u���ݒ�
				if(tmp_i == 5 && tmp_aka_man > 0){
					ply_act_tehai_tbl_aka[pnum][ply_act_tehaicount[pnum]] = true;
					tmp_aka_man--;
				}else if(tmp_i == 15 && tmp_aka_pin > 0){
					ply_act_tehai_tbl_aka[pnum][ply_act_tehaicount[pnum]] = true;
					tmp_aka_pin--;
				}else if(tmp_i == 25 && tmp_aka_sou > 0){
					ply_act_tehai_tbl_aka[pnum][ply_act_tehaicount[pnum]] = true;
					tmp_aka_sou--;
				}else{
					ply_act_tehai_tbl_aka[pnum][ply_act_tehaicount[pnum]] = false;
				}

				// ��v����+1
				ply_act_tehaicount[pnum]++;

			}
		}
	}
}

/* ---------------------------------------------------------------------------------------------- */
// �̔v�̃e�[�u���ʒu�ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::settehaitbl_sute_stat(int kyoku_index, int actid, int pnum){

	// ��v�̐������J��Ԃ�
	for(int tmp_i = 0; tmp_i < ply_act_tehaicount[pnum]; tmp_i++){
		// �̔v�ł����
		if(ply_act_tehaitbl[pnum][tmp_i]      == ply_act_sute[pnum]     && 
		   ply_act_tehai_tbl_aka[pnum][tmp_i] == ply_act_sute_aka[pnum] ){
			// �ʒu��`
			ply_tbl_com_sutehai_statnum[pnum] = tmp_i;
			break;
		}
	}

		// ���̐؂�ł����
		if( ply_act_tsumo[pnum]     == ply_act_sute[pnum]     && 
		    ply_act_tsumo_aka[pnum] == ply_act_sute_aka[pnum] ){
			// �ʒu��`
			ply_tbl_com_sutehai_statnum[pnum] = ply_act_tehaicount[pnum];
		}

}

/* ---------------------------------------------------------------------------------------------- */
// �v�e�[�u�����Ƃ̃V�����e��
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::settehaitbl_shanten(int kyoku_index, int actid, int pnum){

	// ----------------------------------------
	// ��v���Ƃ̃V�����e��
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < ply_act_tehaicount[pnum]; tmp_i++){
		ply_act_tehai[pnum][ply_act_tehaitbl[pnum][tmp_i]]--;  // �e�[�u���v���Ƃ̉��������
		if(com_no_chk_tehai_flg == false){
			ChkShanten(pnum);
		}
		// ��v���Ƃ̃V�����e�����̐ݒ�
		ply_act_tehai_shanten_tbl[pnum][tmp_i] = shanten_total[pnum]; 
		// �̔v�֎~�e�[�u���̐ݒ�
		if( shanten_total[pnum] == 0){
			ply_act_tehai_can_sute_tbl[pnum][tmp_i] = true;
		}else{
			ply_act_tehai_can_sute_tbl[pnum][tmp_i] = false;
		}
		ply_act_tehai[pnum][ply_act_tehaitbl[pnum][tmp_i]]++;  // ���������̖߂�
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �Ҕv�m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::setmachi(int kyoku_index, int actid, int pnum){

	// ----------------------------------------
	// �Ҕv�m�F
	// ----------------------------------------

	// �Ҕv���̏�����
	ply_act_machi_count[pnum] = 0;

	// �e���p�C�m�F
//	if( shanten_normal[pnum] == 0){
	if( shanten_total[pnum] == 0){

		// �Ҕv�m�F
		for(int tmp_pai_num = 1; tmp_pai_num < PAI_MAX; tmp_pai_num++){

			if( tmp_pai_num != 10 && tmp_pai_num != 20 && tmp_pai_num != 30){

				// ���̔v�̉��ݒ�
				ply_act_tehai[pnum][tmp_pai_num]++;

				// �V�����e���m�F
				if(com_no_chk_tehai_flg == false){
					ChkShanten(pnum);
				}

				// �a���ł���Ȃ�
				if( shanten_total[pnum] == -1){

					// �Ҕv�ݒ�
					ply_act_machi_hai[pnum][ply_act_machi_count[pnum]] = tmp_pai_num;
					ply_act_machi_count[pnum]++;

				}

				// ���̔v�̉��ݒ�̉���
				ply_act_tehai[pnum][tmp_pai_num]--;

			}

		}

	}

	// ----------------------------------------
	// �Ҕv�̃t���e���m�F
	// ----------------------------------------


}

/* ---------------------------------------------------------------------------------------------- */
// �������m�F(���C��)
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::ChkShanten(int pnum){

	// �V�����e���Z�o
	NormalShanten(pnum);
	KokushiShanten(pnum);

	// �����V�����e���̐ݒ�
	if(shanten_normal[pnum] > shanten_chitoi[pnum] && shanten_kokushi[pnum] > shanten_chitoi[pnum]){
		shanten_total[pnum] = shanten_chitoi[pnum];
	}else if(shanten_normal[pnum] > shanten_kokushi[pnum]){
		shanten_total[pnum] = shanten_kokushi[pnum];
	}else{
		shanten_total[pnum] = shanten_normal[pnum];
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �������m�F(���m���o)
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::KokushiShanten(int pnum){

	int  tmp_kokushi_hai_count = 0;
	bool tmp_kokushi_atama_flg = false;

	// ���m�v�m�F
	for(int tmp_i=0; tmp_i<13; tmp_i++){
		if(ply_act_tehai[pnum][kokushi_hai_num[tmp_i]] > 0){
			tmp_kokushi_hai_count++;
		}
		if(ply_act_tehai[pnum][kokushi_hai_num[tmp_i]] > 1){
			tmp_kokushi_atama_flg = true;
		}
	}

	// ���m�̓�����m�F
	if(tmp_kokushi_atama_flg == true){
		tmp_kokushi_hai_count++;
	}

	// �V�����e���Z�o
	shanten_kokushi[pnum] = 13 - tmp_kokushi_hai_count;

}

/* ---------------------------------------------------------------------------------------------- */
// �������m�F(�ʏ�)
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::NormalShanten(int pnum){

	// ----------------------------------------
	// ������
	// ----------------------------------------
	shanten_normal[pnum] = 8;
	tmp_shanten          = 0;
	tmp_atama_count      = 0;
	tmp_mentu_count      = 0;
	tmp_taatu_count      = 0;

	tmp_atama_hai = 0;   // ���v�ԍ��̏�����

	int tmp_chitoi_atama_count = 0;

	// ----------------------------------------
	// �����J�n
	// ----------------------------------------
	for(int hai=1; hai<PAI_MAX; hai++){

		// �������m�F
		if(ply_act_tehai[pnum][hai] >= 2){

			tmp_atama_count++;
			tmp_chitoi_atama_count++;       // �`�[�g�C��������
			ply_act_tehai[pnum][hai] -= 2;
			tmp_atama_hai = hai;   // ���v�ԍ��̐ݒ�
			mentu_cut(pnum, 1);
			ply_act_tehai[pnum][hai] += 2;
			tmp_atama_hai = 0;     // ���v�ԍ��̖�����
			tmp_atama_count--;

		}
	}

	// ----------------------------------------
    // ���Ȃ��̏ꍇ
	// ----------------------------------------
    mentu_cut(pnum, 1);

	// ----------------------------------------
    // �`�[�g�C�V�����e��
	// ----------------------------------------
	shanten_chitoi[pnum] = 6 - tmp_chitoi_atama_count;

}

/* ---------------------------------------------------------------------------------------------- */
// �ʎq�폜����
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::mentu_cut(int pnum, int hai){

	// ----------------------------------------
	// 0���̓X�L�b�v
	// ----------------------------------------
	for(;!ply_act_tehai[pnum][hai]; hai++);

	// ----------------------------------------
	// ������΃^�[�c����
	// ----------------------------------------
	if( hai >= PAI_MAX ){
		taatu_cut(pnum, 1);

		// �����̕Ԃ�
		return;
	}

	// ----------------------------------------
	// �A���R���Z�b�g
	// ----------------------------------------
	if(ply_act_tehai[pnum][hai] >= 3){

		tmp_mentu_stat[tmp_mentu_count] = ANKO;      // �ʎq���ݒ�
		tmp_mentu_hai[tmp_mentu_count]  = hai;       // �v�ԍ��ݒ�
		tmp_mentu_count++;
		ply_act_tehai[pnum][hai]-=3;
		mentu_cut(pnum, hai);                               // �����c�J�b�g�̍ċN����
		ply_act_tehai[pnum][hai]+=3;
		tmp_mentu_count--;
		tmp_mentu_stat[tmp_mentu_count] = NOMENTSU;   // �ʎq���ݒ�
		tmp_mentu_hai[tmp_mentu_count]  = hai;        // �v�ԍ��ݒ�

	}

	// ----------------------------------------
	// �V�����c���Z�b�g
	// ----------------------------------------
	if(ply_act_tehai[pnum][hai+1] && ply_act_tehai[pnum][hai+2] && hai<30){

		tmp_mentu_stat[tmp_mentu_count] = SHUNTSU;  // �ʎq���ݒ�
		tmp_mentu_hai[tmp_mentu_count]  = hai;      // �v�ԍ��ݒ�
		tmp_mentu_count++;
		ply_act_tehai[pnum][hai]--;
		ply_act_tehai[pnum][hai+1]--;
		ply_act_tehai[pnum][hai+2]--;
		mentu_cut(pnum, hai);   // �����c�J�b�g�̍ċN����
		ply_act_tehai[pnum][hai]++;
		ply_act_tehai[pnum][hai+1]++;
		ply_act_tehai[pnum][hai+2]++;
		tmp_mentu_count--;
		tmp_mentu_stat[tmp_mentu_count] = NOMENTSU;   // �ʎq���ݒ�
		tmp_mentu_hai[tmp_mentu_count]  = hai;        // �v�ԍ��ݒ�

	}

	// ----------------------------------------
	// ���̃����c�J�b�g�̍ċN����
	// ----------------------------------------
	mentu_cut(pnum, hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// ���q�폜����
/* ---------------------------------------------------------------------------------------------- */
void MJSTkinfo::taatu_cut(int pnum, int hai){

	// ----------------------------------------
	// 0���̓X�L�b�v
	// ----------------------------------------
	for(;!ply_act_tehai[pnum][hai]; hai++);

	// ----------------------------------------
	// ������΃V�����e���Z�o
	// ----------------------------------------
	if( hai >= PAI_MAX ){

		// �V�����e�����̎Z�o
		// tmp_shanten = 8-tmp_mentu_count*2-tmp_taatu_count-tmp_atama_count;
		// tmp_shanten = 8-naki_count[pnum]*2-tmp_mentu_count*2-tmp_taatu_count-tmp_atama_count;
		tmp_shanten = 8-naki_count_none_kakan[pnum]*2-tmp_mentu_count*2-tmp_taatu_count-tmp_atama_count;

		if( tmp_shanten < shanten_normal[pnum]){

			// �ʏ�V�����e���̉��u��
			shanten_normal[pnum] = tmp_shanten;

			// �A�^�}���Z�b�g
			atama_count = tmp_atama_count;
			atama_hai   = tmp_atama_hai;

			// �����c���Z�b�g
			mentu_count = tmp_mentu_count;
			for(int tmp_i=0;tmp_i<tmp_mentu_count;tmp_i++){
				mentu_stat[tmp_i] = tmp_mentu_stat[tmp_i];  // �ʎq���ݒ�
				mentu_hai[tmp_i]  = tmp_mentu_hai[tmp_i];   // �v�ԍ��ݒ�
			}

			// �^�[�c���Z�b�g
			taatu_count = tmp_taatu_count;
			for(int tmp_i=0;tmp_i<tmp_taatu_count;tmp_i++){
				taatsu_stat[tmp_i]=tmp_mentu_stat[tmp_i];  // �^�[�c���ݒ�
				taatsu_hai[tmp_i]=tmp_taatsu_hai[tmp_i];   // �v�ԍ��ݒ�
			}

		}

		// �����̕Ԃ�
		return;
	}

	// ----------------------------------------
	// �^�[�c���Z�b�g
	// ----------------------------------------
	// if(tmp_mentu_count+tmp_taatu_count<4){
	// if( naki_count[pnum]  +tmp_mentu_count+tmp_taatu_count < 4 ){
	if( naki_count_none_kakan[pnum]+tmp_mentu_count+tmp_taatu_count < 4 ){

		// �g�C�c�J�b�g
		if( ply_act_tehai[pnum][hai] == 2 ){
			tmp_taatsu_stat[tmp_mentu_count] = TOITSU;   // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentu_count]  = hai;      // �v�ԍ��ݒ�
			tmp_taatu_count++;
			ply_act_tehai[pnum][hai]-=2;
			taatu_cut(pnum, hai);
			ply_act_tehai[pnum][hai]+=2;
			tmp_taatu_count--;
			tmp_taatsu_stat[tmp_mentu_count] = NOMENTSU;  // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentu_count]  = hai;       // �v�ԍ��ݒ�
		}

		// ���ʃJ�b�g
		if( ply_act_tehai[pnum][hai+1] && hai<30 ){

			tmp_taatsu_stat[tmp_mentu_count] = TOITSU;   // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentu_count]  = hai;      // �v�ԍ��ݒ�
			tmp_taatu_count++;
			ply_act_tehai[pnum][hai]--, ply_act_tehai[pnum][hai+1]--;
			taatu_cut(pnum, hai);
			ply_act_tehai[pnum][hai]++, ply_act_tehai[pnum][hai+1]++;
			tmp_taatu_count--;
			tmp_taatsu_stat[tmp_mentu_count] = NOMENTSU;  // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentu_count]  = hai;       // �v�ԍ��ݒ�
		}

		// �J���`�����J�b�g
		if( ply_act_tehai[pnum][hai+2]&& hai<30 && hai%10<=8 ){

			tmp_taatsu_stat[tmp_mentu_count] = TOITSU;   // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentu_count]  = hai;      // �v�ԍ��ݒ�
			tmp_taatu_count++;
			ply_act_tehai[pnum][hai]--, ply_act_tehai[pnum][hai+2]--;
			taatu_cut(pnum, hai);
			ply_act_tehai[pnum][hai]++, ply_act_tehai[pnum][hai+2]++;
			tmp_taatu_count--;
			tmp_taatsu_stat[tmp_mentu_count] = NOMENTSU;  // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentu_count]  = hai;       // �v�ԍ��ݒ�
		}
	}

	// ----------------------------------------
	// ���̃^�[�c�ċN����
	// ----------------------------------------
	taatu_cut(pnum, hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
