/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.1.234(�\���v(open_haiparts)�ꗗ�\��)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F player.cpp
 * �N���X��       �F MJSPlayer�N���X
 * �����T�v       �F �v���[���[�N���X
 * Ver0.0.8�쐬�� �F 2012/05/04 11:41:34
 * Ver0.1.0�쐬�� �F 2022/06/04 10:13:26
 * Ver0.1.1�쐬�� �F 2022/06/30 21:19:01
 * Ver0.1.2�쐬�� �F 2022/08/31 22:19:54
 * �ŏI�X�V��     �F 2025/02/01 09:57:37
 * 
 * Copyright (c) 2010-2025 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "player.h"

/* ---------------------------------------------------------------------------------------------- */
// ��J�n����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyActTakuStart(int tmp_ply_id){

	// �v���[���^�C�v�ݒ�
	ply_type = PLYCHAR_MJSPLY_TEST;

	// �����̃v���[���ԍ���ݒ�
	ply_num = tmp_ply_id;

	// ���Ƃ̃v���[���ԍ���ݒ�
	ply_num_shimo = ( tmp_ply_id + 3 ) % 4;

	// �Ԕv�ő吔�̐ݒ�
	max_aka_count[0] = 4;
	max_aka_count[1] = 4;
	max_aka_count[2] = 4;

}

/* ---------------------------------------------------------------------------------------------- */
// �ǊJ�n����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyActKyokuStart(int  tmp_kaze,
	                      int  tmp_kyoku,
	                      int  tmp_honba,
	                      int  tmp_riichibo,
	                      int  tmp_ie,
	                      int  tmp_dora){

	// �Ə��
	ie = tmp_ie;
	ply_bakaze = TONNUM;
	ply_zikaze = TONNUM + ie;

	// �q�X�g�O����������
	for(int i=0; i< PAI_MAX; i++){
		tehai[i]               = 0;     // ��v����
		open_haiparts_count[i] = 0;     // �v�ԍ����Ƃ̎c�薇��
	}

	// �Ԕv������
	aka_count[0] = 0;
	aka_count[1] = 0;
	aka_count[2] = 0;

	// �v���[���ϐ��̏�����
	ply_act       = NOACT;
	ply_tsumo_hai = 0;
	ply_sute_hai  = 0;

	// ������
	naki_count  = 0;
	ankan_count = 0;
	kakan_count = 0;

	// ���[�`��Ԃ̏�����
	ply_riichi_mode = 0;

	// �����̏�����
	shanten_normal  = 8;
	shanten_kokushi = 8;
	shanten_chitoi  = 8;

	// �̔v��␔
	sutekoho_count  = 0;

	// �����e�[�u��
	nakikoho_tbl_count = 0;
	ply_tehai_naki_stat = false;
	ply_yakuhai_stat = false;

	// ���A�N�V����
	ply_naki_idx = 0;
	ply_naki_aka_count = 0;

}

/* ---------------------------------------------------------------------------------------------- */
// �z�v����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyActHaipai(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// �q�X�g�O�����ɔv�̖��������Z
	tehai[tmp_tsumo_hai]++;

	// �\���v�̉��Z
	open_haiparts_count[tmp_tsumo_hai]++;

}

/* ---------------------------------------------------------------------------------------------- */
// �z�v��̊m�F����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyActPostHaipai(){

	// ���̖������̌������m�F
	ChkTsumoNashiShanten();

	// �v���[���̎�v�X�e�[�^�X�X�V
	PlyChkPlyStat();

}

/* ---------------------------------------------------------------------------------------------- */
// ���̏���
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyActTsumo(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// ���ԑ���1
	action_timestamp1 = GetTickCount();

	// ----------------------------------------
	// �A�N�V�����ݒ�
	// ----------------------------------------

	// ���̃A�N�V�����̐ݒ�
	ply_act = ACTTSUMO;

	// ���̃A�N�V�����̐ݒ�
	ply_tsumo_hai = tmp_tsumo_hai;
	ply_tsumo_aka = tmp_tsumo_aka;

	// �\���v�̉��Z
	open_haiparts_count[tmp_tsumo_hai]++;

	// ----------------------------------------
	// �̔v�ݒ�
	// ----------------------------------------

	// ���̗L�̌����Z�o
	ChkTsumoAriShanten();

	// ----------------------------------------
	// ���̘a���m�F
	// ----------------------------------------
	if (shanten_normal == -1){

		// �A�N�V��������(���̘a��)
		ply_act = ACTTSUMOAGARI;

	}else{

		// ----------------------------------------
		// ���[�`�m���ԂȂ炻�̂܂܎��̐؂�
		// ----------------------------------------
		if (ply_riichi_mode == 2){

			// �A�N�V��������(���̐؂�)
			ply_act = ACTTSUMOGIRI;

			// �̔v�m��
			ply_sute_hai=ply_tsumo_hai;

		// ----------------------------------------
		// ���[�`�m��łȂ��ꍇ�̃A�N�V��������
		// ----------------------------------------
		}else{

			// �A�N�V�����m�F - �Þ�
			if (ply_act == ACTTSUMO){
				PlyChkAnkan(tmp_tsumo_hai, tmp_tsumo_aka);
			}

			// �A�N�V�����m�F - ����
			if (ply_act == ACTTSUMO){
				PlyChkKakan(tmp_tsumo_hai, tmp_tsumo_aka);
			}

			// �A�N�V�����m�F - �̔v
			if (ply_act == ACTTSUMO){
				PlyChkTsumoSute();
			}

		}
	}

	// (�f�o�O�p)���̐؂�A�N�V����
	// ply_act = ACTTSUMOGIRI;
	// ply_sute_hai = ply_tsumo_hai;
	// ply_sute_aka = ply_tsumo_aka;

	// ���ԑ���2
	action_timestamp2 = GetTickCount();

}

/* ---------------------------------------------------------------------------------------------- */
// �ÞȊm�F
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyChkAnkan(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// �����m�F
	for( int tmp_i=0; tmp_i < PAI_MAX; tmp_i++ ){

		// ���̂�4����������A�Þ�
		if ( (tehai[tmp_i] >= 3 && tmp_tsumo_hai == tmp_i) ||
		      tehai[tmp_i] >= 4 ){

			// ----------------------------------------
			// �A�N�V�����ݒ� - �Þ�
			// ----------------------------------------

			// �ÞȔv�ݒ�
			ply_naki_idx = tmp_i;

			// �Þȏ���
			ply_act = ACTANKAN;

			// �����𔲂���(�ÞȂ�1�񂵂��ł��Ȃ�����)
			break ;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���Ȋm�F
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyChkKakan(int tmp_tsumo_hai, bool tmp_tsumo_aka){

	// �����J�n
	for( int tmp_i=0; tmp_i < naki_count; tmp_i++ ){

		// �c���v�������̖��v�Ɠ����ł����
		if(naki_stat[tmp_i] == MINKO && naki_hai[tmp_i] == tmp_tsumo_hai){

			// ���Ȕv�ݒ�
			ply_naki_idx = tmp_tsumo_hai;

			// ���Ȑ�
			if(tmp_tsumo_aka == true){
				ply_naki_aka_count=1;
			}else{
				ply_naki_aka_count=0;
			}

			// ���ȏ���
			ply_act = ACTKAKAN;

			// �����𔲂���(���Ȃ�1�񂵂��ł��Ȃ�����)
			break ;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���̎̔v�m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyChkTsumoSute(){

	// �̔v�m��
	ply_sute_hai = sutekoho_hai[fixed_sutekoho_num];

	// ----------------------------------------
	// ���[�`�錾�m�F
	// ----------------------------------------
	if(shanten_normal == 0 && ply_riichi_mode == 0 && naki_count-ankan_count == 0){

		ply_act = ACTRIICH;
		ply_riichi_mode = 1;   // ���[�`�錾���[�h

	// ----------------------------------------
	// ���̐؂�m�F(�����F�u���̔v�Ǝ̔v������v���u��v���̎̔v��0���v�����̐؂�)
	// ----------------------------------------
	}else if(ply_tsumo_hai == ply_sute_hai && tehai[ply_sute_hai] == 0){

		// �A�N�V�����̎w��
		ply_act = ACTTSUMOGIRI;

		// �Ԕv�ݒ�
		ply_sute_aka=ply_tsumo_aka;

		// �O�̃A�N�V�������u���[�`�A�N�V�����v�Ȃ�΁A���[�`���[�h�̕ύX
		if( ply_riichi_mode == 1 ){
			ply_riichi_mode = 2;   // ���[�`�錾�ヂ�[�h
		}

	// ----------------------------------------
	// ���̑��͎̔v����
	// ----------------------------------------
	}else{

		// �A�N�V�����̎w��
		ply_act = ACTSUTE;

		// �Ԕv�ݒ�
		// TODO:�Ԕv�̗D�揇�ʂ���������
		if( ( ply_sute_hai == MAN5NUM && aka_count[0] > 0) || 
		    ( ply_sute_hai == PIN5NUM && aka_count[1] > 0) || 
		    ( ply_sute_hai == SOU5NUM && aka_count[2] > 0) ){
	   		ply_sute_aka=true;
		}else{
			ply_sute_aka=false;
		}

		// �O�̃A�N�V�������u���[�`�A�N�V�����v�Ȃ�΁A���[�`���[�h�̕ύX
		if( ply_riichi_mode == 1 ){
			ply_riichi_mode = 2;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ÞȃA�N�V����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyActAnkan(int tmp_naki_hai){

	// ----------------------------------------
	// ��v�E���̏���
	// ----------------------------------------

	// �q�X�g�O�����ɔv�̖��������Z
	tehai[tmp_naki_hai] = 0;

	// ���̔v���Z
	if ( ply_tsumo_hai != tmp_naki_hai){
		tehai[ply_tsumo_hai]++;           // ���̔v
	}

	// ----------------------------------------
	// �N�������ǉ�
	// ----------------------------------------
	naki_stat[naki_count] = ANKAN;
	naki_hai[naki_count]  = tmp_naki_hai;
	naki_idx[naki_count]  = tmp_naki_hai;

	// �N������(�Ԕv)
	if( tmp_naki_hai == MAN5NUM || 
	    tmp_naki_hai == PIN5NUM || 
	    tmp_naki_hai == SOU5NUM ){

		// �Ԕv�ݒ�
		naki_aka[naki_count] = max_aka_count[(tmp_naki_hai-5)/10];  // �ÞȂ̂��߂ɍő吔���`
		aka_count[(tmp_naki_hai-5)/10] = 0;                         // �莝���Ԃ͂Ȃ�

	}else{
		naki_aka[naki_count] = 0;
	}

	// �N���������Z
	naki_count++;
	ankan_count++;

	// ----------------------------------------
	// ��v��Ԋm�F - �Þ�
	// ----------------------------------------

	// �̔v��(���̖���)�̎�v��Ԋm�F
	ChkTsumoNashiShanten();


}

/* ---------------------------------------------------------------------------------------------- */
// ���ȃA�N�V����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyActKakan(int tmp_naki_hai, int tmp_naki_aka_count){

	// ----------------------------------------
	// ��v�E���̏���
	// ----------------------------------------

	// ���̔v���Z
	if ( ply_tsumo_hai != tmp_naki_hai){
		tehai[ply_tsumo_hai]++;           // ���̔v
		tehai[tmp_naki_hai]--;            // ���Ȃ̔v
	}

	// ----------------------------------------
	// �N�������ǉ�
	// ----------------------------------------

	// �N�������ǉ�
	naki_stat[naki_count]=KAKAN;
	naki_hai[naki_count]=tmp_naki_hai;
	naki_idx[naki_count]=tmp_naki_hai;
	naki_aka[naki_count]=tmp_naki_aka_count;

	// �N���������Z
	naki_count++;
	kakan_count++;

	// ----------------------------------------
	// ��v��Ԋm�F - ����
	// ----------------------------------------

	// �̔v��(���̖���)�̎�v��Ԋm�F
	ChkTsumoNashiShanten();

}

/* ---------------------------------------------------------------------------------------------- */
// 4.�̔v���A�N�V��������
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyActTsumoSute(){

	// ���ԑ���1
	action_timestamp1 = GetTickCount();

	// �v���[���[��v�q�X�g�O�����̍X�V
	PlySetTsumoSuteTehaiHist();

	// �v���[���̎�v�X�e�[�^�X�̍X�V
	PlyChkPlyStat();

	// ���ԑ���2
	action_timestamp2 = GetTickCount();

}

/* ---------------------------------------------------------------------------------------------- */
// ���̎̔v���̎�v�q�X�g�O��������
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlySetTsumoSuteTehaiHist(){

	// ----------------------------------------
	// �̔v����
	// ----------------------------------------

		// �̔v����
		tehai[ply_sute_hai]--;

		// �Ԕv���ύX(�̔v)
		if(      ply_sute_hai == MAN5NUM && ply_sute_aka == true ){
			aka_count[0]--;
		}else if(ply_sute_hai == PIN5NUM && ply_sute_aka == true ){
			aka_count[1]--;
		}else if(ply_sute_hai == SOU5NUM && ply_sute_aka == true ){
			aka_count[2]--;
		}

		// �̔v�̏�����
		ply_sute_hai = 0;

	// ----------------------------------------
	// ���̏���
	// ----------------------------------------

	// ���̔v������ꍇ
	if ( ply_act == ACTSUTE || ply_act == ACTTSUMOGIRI){

		// ��v���ύX
		tehai[ply_tsumo_hai]++;

		// �Ԕv���ύX(����)
		if(      ply_tsumo_hai == MAN5NUM && ply_tsumo_aka == true ){
			aka_count[0]++;
		}else if(ply_tsumo_hai == PIN5NUM && ply_tsumo_aka == true ){
			aka_count[1]++;
		}else if(ply_tsumo_hai == SOU5NUM && ply_tsumo_aka == true ){
			aka_count[2]++;
		}

		// �c���v�̏�����
		ply_tsumo_hai = 0;

	}

	// �̔v��(���̖���)�̎�v��Ԋm�F
	ChkTsumoNashiShanten();

}

/* ---------------------------------------------------------------------------------------------- */
// �v���[����v�̏�Ԋm�F
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyChkPlyStat(){

	ply_tehai_naki_stat = false;
	ply_yakuhai_stat    = false;

	if( tehai[HAKUNUM] > 2 || tehai[HATSUNUM] > 2 || tehai[CHUNNUM] > 2 || tehai[ply_bakaze] > 2 || tehai[ply_zikaze] > 2){

		ply_tehai_naki_stat = true;
		ply_yakuhai_stat    = true;

	}else{

		// ���e�[�u�����m�F���Ė�v������Ă��邩�m�F����
		for( int tmp_i=0; tmp_i < naki_count; tmp_i++){
			if( naki_hai[tmp_i] == HAKUNUM || naki_hai[tmp_i] == HATSUNUM || naki_hai[tmp_i] == CHUNNUM || naki_hai[tmp_i] == ply_bakaze || naki_hai[tmp_i] == ply_zikaze ){
				ply_tehai_naki_stat = true;
				ply_yakuhai_stat    = true;
				break;
			}
		}

	}

	// �v���[���[���e�[�u���̍X�V
	PlyChkNakitbl();

}

/* ---------------------------------------------------------------------------------------------- */
// ���e�[�u���̏�Ԋm�F
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyChkNakitbl(){

	// ���e�[�u���m�F
	for(int tmp_i = 0; tmp_i < nakikoho_tbl_count; tmp_i++){

		if( ply_yakuhai_stat == true ){
			nakikoho_tbl_yesno[tmp_i] = true;
		}else if( nakikoho_tbl_hai[tmp_i]==HAKUNUM    || 
		          nakikoho_tbl_hai[tmp_i]==HATSUNUM   || 
		          nakikoho_tbl_hai[tmp_i]==CHUNNUM    || 
		          nakikoho_tbl_hai[tmp_i]==ply_bakaze || 
		          nakikoho_tbl_hai[tmp_i]==ply_zikaze ){ 
			nakikoho_tbl_yesno[tmp_i] = true;
		}else{
			nakikoho_tbl_yesno[tmp_i] = false;;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyChkNaki(int suteply, int hai){

	// �����ݒ�
	ply_act = ACTNONAKI;
	ply_naki_idx = 0;
	ply_naki_aka_count = 0;

	// �����J�n
	for( int tmp_i=0; tmp_i < nakikoho_tbl_count; tmp_i++){

		// �v���Y�����Ă���̂ł����
		if( nakikoho_tbl_hai[tmp_i] == hai ){

			// ----------------------------------------
			// �����m�F
			// ----------------------------------------
			if( nakikoho_tbl_act[tmp_i] == ACTRON ){

				// �A�N�V�����ݒ�
				ply_act = ACTRON;
				ply_naki_idx = nakikoho_tbl_hai[tmp_i];
				ply_naki_aka_count = 0;

			// ----------------------------------------
			// �|���m�F
			// ----------------------------------------
			}else if( nakikoho_tbl_yesno[tmp_i] == true && nakikoho_tbl_act[tmp_i] == ACTPON ){

				// �A�N�V�����ݒ�
				ply_act = ACTPON;

				// �|�����̔vINDEX
				ply_naki_idx = nakikoho_tbl_hai[tmp_i];

				// �Ԕv�ł���Ȃ��
				if( hai == 5 || hai == 15 || hai == 25){

					// �Ԕv��2���ȏ�Ȃ��
					if(aka_count[(hai-5)/10] > 2){

						// �Ԗ����ݒ�
						ply_naki_aka_count = 2;

					}else{

						// �Ԗ����ݒ�
						ply_naki_aka_count = aka_count[(hai-5)/10];

					}

				}else{

						// �Ԗ����ݒ�
						ply_naki_aka_count = 0;

				}

			// ----------------------------------------
			// �`�[�m�F
			// ----------------------------------------
//			if( nakikoho_tbl_act[tmp_i] == ACTCHI ){
			}else if( nakikoho_tbl_yesno[tmp_i] == true && nakikoho_tbl_act[tmp_i] == ACTCHI && suteply == ply_num_shimo){

				// �A�N�V�����ݒ�
				ply_act = ACTCHI;

				// �`�[���̔vINDEX
				ply_naki_idx = nakikoho_tbl_idx[tmp_i];

				// �Ԕv�̉��ݒ�
				ply_naki_aka_count=0;

				// �Ԕv�m�F(��INDEX��3�̏ꍇ)
				if( ply_naki_idx == 3 || ply_naki_idx == 13 || ply_naki_idx == 23){
					if( ( hai != 5 || hai != 15 || hai != 25) && ( aka_count[(hai-3)/10] > 0 ) ){
						ply_naki_aka_count=1;
					}else{
						ply_naki_aka_count=0;
					}
				}

				// �Ԕv�m�F(��INDEX��4�̏ꍇ)
				if( ply_naki_idx == 4 || ply_naki_idx == 14 || ply_naki_idx == 24){
					if( ( hai != 5 || hai != 15 || hai != 25) && ( aka_count[(hai-4)/10] > 0 ) ){
						ply_naki_aka_count=1;
					}else{
						ply_naki_aka_count=0;
					}
				}

				// �Ԕv�m�F(��INDEX��5�̏ꍇ)
				if( ply_naki_idx == 5 || ply_naki_idx == 15 || ply_naki_idx == 25){
					if( ( hai != 5 || hai != 15 || hai != 25) && ( aka_count[(hai-5)/10] > 0 ) ){
						ply_naki_aka_count=1;
					}else{
						ply_naki_aka_count=0;
					}
				}

			}

		}
	}

	// (�f�o�O�p)�������Ȃ�
/*	if( ply_act != ACTRON){
		ply_act = ACTNONAKI;
	}*/

}

/* ---------------------------------------------------------------------------------------------- */
// ���A�N�V����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyActNaki(int naki_ply_num, LBPAct naki_ply_act, int hai, int chi_hai_idx, int naki_aka_count){

	// ���v���[���[�m�F(�����̂������ł����)
	if( ply_num == naki_ply_num ){

		// ----------------------------------------
		// �N���v�ݒ� - �|���̏ꍇ
		// ----------------------------------------
		if( naki_ply_act == ACTPON ){

			// �q�X�g�O�����ɔv�̖��������Z
			tehai[hai]-=2;

			// �Ԕv�����̌��Z
			if( hai == 5 || hai == 15 || hai == 25){
				aka_count[(hai-5)/10] = aka_count[(hai-5)/10] - ply_naki_aka_count;
			}

			// �N�������ǉ�
			naki_stat[naki_count]=MINKO;
			naki_hai[naki_count] = hai;
			naki_idx[naki_count] = hai;
			naki_aka[naki_count] = naki_aka_count;
			naki_count++;

		// ----------------------------------------
		// �N���v�ݒ� - �`�[�̏ꍇ
		// ----------------------------------------
		}else if( naki_ply_act == ACTCHI ){

			// �q�X�g�O�����ɔv�̖��������Z
			tehai[chi_hai_idx]--;
			tehai[chi_hai_idx+1]--;
			tehai[chi_hai_idx+2]--;
			tehai[hai]++;

			// �Ԕv�����̌��Z
			if( chi_hai_idx == 3 || chi_hai_idx == 13 || hai == 23){
				aka_count[(chi_hai_idx-3)/10] = aka_count[(chi_hai_idx-3)/10] - ply_naki_aka_count;
			}else if( chi_hai_idx == 4 || chi_hai_idx == 14 || hai == 24){
				aka_count[(chi_hai_idx-4)/10] = aka_count[(chi_hai_idx-4)/10] - ply_naki_aka_count;
			}else if( chi_hai_idx == 5 || chi_hai_idx == 15 || hai == 25){
				aka_count[(chi_hai_idx-5)/10] = aka_count[(chi_hai_idx-5)/10] - ply_naki_aka_count;
			}

			// �N�������ǉ�
			naki_stat[naki_count] = MINSHUN;
			naki_hai[naki_count]  = hai;
			naki_idx[naki_count]  = chi_hai_idx;
			naki_aka[naki_count]  = naki_aka_count;
			naki_count++;

		}

		// ----------------------------------------
		// �V�����e���m�F�E�̔v�m��
		// ----------------------------------------
		PlyChkNakiSute();

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���̔v�A�N�V����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyChkNakiSute(){

		// ���̗L�̌����Z�o
		ChkTsumoAriShanten();

		// �̔v�ݒ�
		ply_sute_hai=sutekoho_hai[fixed_sutekoho_num];

		// �Ԕv�ݒ�
		// TODO:�Ԕv�̗D�揇�ʂ���������
		if( ( ply_sute_hai ==  5 && aka_count[0] > 0) || 
		    ( ply_sute_hai == 15 && aka_count[1] > 0) || 
		    ( ply_sute_hai == 25 && aka_count[2] > 0) ){
	   		ply_sute_aka=true;
		}else{
			ply_sute_aka=false;
		}

		// �A�N�V�����̎w��
		ply_act = ACTNAKISUTE;

}

/* ---------------------------------------------------------------------------------------------- */
// ���̔v����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::PlyActNakiSute(){

	// �̔v����
	tehai[ply_sute_hai]--;

	// �Ԕv���ύX(�̔v)
	if( ply_sute_hai == 5 && ply_sute_aka==true ){
		aka_count[0]--;
	}else if(ply_sute_hai == 15 && ply_sute_aka==true){
		aka_count[1]--;
	}else if(ply_sute_hai == 25 && ply_sute_aka==true){
		aka_count[2]--;
	}

	// �̔v��̎�v��Ԋm�F
	ChkTsumoNashiShanten();

	// �v���[���̎�v�X�e�[�^�X�̍X�V
	PlyChkPlyStat();

}

/* ---------------------------------------------------------------------------------------------- */
// ���̗L��̌����Z�o
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::ChkTsumoAriShanten(){

	// ----------------------------------------
	// ������
	// ----------------------------------------
	int tmp_shanten2;        // 14���V�����e���l�̈ꎞ�u��
	sutekoho_count = 0;

	// ----------------------------------------
	// �V�����e���m�F
	// ----------------------------------------

	// ���̔v�̒ǉ�
	if (ply_act == ACTTSUMO){
		tehai[ply_tsumo_hai]++;
	}

	// 14�����_�̃V�����e���m�F
	NormalShanten();  
	tmp_shanten2 = shanten_normal;

	// ----------------------------------------
	// �̔v���̊m�F
	// ----------------------------------------
	for(int i=0; i< PAI_MAX; i++){
		if(tehai[i]>0){
			// ��`������
			sutekoho_shanten[sutekoho_count]  = 0;
			yuko_haishu_count[sutekoho_count] = 0;
			yuko_hai_count[sutekoho_count]    = 0;
			sutekoho_hai[sutekoho_count]      = i;
			sutekoho_count++;
		}
	}

	// ----------------------------------------
	// �̔v��₲�Ƃ̃V�����e���m�F
	// ----------------------------------------
	for(int tmp_count=0; tmp_count< sutekoho_count; tmp_count++){
		// �̔v���̐ݒ�
		tehai[sutekoho_hai[tmp_count]]--; // ���̉��u��
		NormalShanten();
		sutekoho_shanten[tmp_count]=shanten_normal;
		yuko_haishu_count[tmp_count]=0;
		// �L���v�Z�o
		for(int j=1; j< PAI_MAX; j++){
			// ��`������
			yuko_hai[tmp_count][j]=false;
			//�L���v�m�F
			if (j !=10 && j!=20 && j!=30){
				// �V�����e�����������ĂȂ��Ȃ�A�L���v���Z�o
				if (sutekoho_shanten[tmp_count] == tmp_shanten2){
					// �V�����e���m�F����v�͈̔͂����肷��
					if(tehai[j-2] >0 || tehai[j-1] >0 || tehai[j] >0 || tehai[j+1] >0 || tehai[j+2] >0){
						tehai[j]++;
						NormalShanten();
						if(shanten_normal == sutekoho_shanten[tmp_count]-1){
							yuko_hai[tmp_count][j]=true;
							yuko_haishu_count[tmp_count]++;
							yuko_hai_count[tmp_count]=yuko_hai_count[tmp_count]+4-tehai[j]+1;  // +1���Ă���̂�tehai[j]�ŉ��u�����Ă邩��
						}
						tehai[j]--;
					}
				}
			}
		}
		// �̔v���̐ݒ�߂�
		tehai[sutekoho_hai[tmp_count]]++;// ���̖߂�
	}

	// �V�����e���l�̖߂�
	shanten_normal = tmp_shanten2;

	// ���̔v�̉���
	if (ply_act == ACTTSUMO){
		tehai[ply_tsumo_hai]--;
	}

	// ----------------------------------------
	// �̔v�̗D�揇�ʐݒ�
	// ----------------------------------------
	SetSutekohoPriority();

	// ----------------------------------------
	// �̔v��⌈��
	// ----------------------------------------
	SetFixedSutekoho();

}

/* ---------------------------------------------------------------------------------------------- */
// ���̖����̌����Z�o
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::ChkTsumoNashiShanten(){

	// ----------------------------------------
	// ��`������
	// ----------------------------------------
	int tmp_shanten2;        // 14���V�����e���l�̈ꎞ�u��
	nakikoho_tbl_count=0;

	// �V�����e���m�F
	NormalShanten_detail();
	tmp_shanten2 = shanten_normal;

	// �L���v�Z�o
	for(int j=1; j< PAI_MAX; j++){

		// ----------------------------------------
		// ��`������
		// ----------------------------------------
		yuko_hai_13mai[j] = false;

		// ----------------------------------------
		// �L���v�m�F
		// ----------------------------------------
		if (j !=10 && j!=20 && j!=30){
			// �V�����e���m�F����v�͈̔͂����肷��
			if(tehai[j-2] > 0 || tehai[j-1] > 0 || tehai[j] > 0 || tehai[j+1] > 0 || tehai[j+2] > 0){

				// ��v���u��
				tehai[j]++;
				NormalShanten_detail();

				// �V�����e����������ꍇ
				if(shanten_normal == tmp_shanten2-1){

					// �L���v�̐ݒ�
					yuko_hai_13mai[j] = true;

					// �e���p�C�Ȃ�΁A�a���v�Ƃ��ăe�[�u���Ɋi�[����
					if(shanten_normal == -1){

						nakikoho_tbl_hai[nakikoho_tbl_count] = j;
						nakikoho_tbl_act[nakikoho_tbl_count] = ACTRON;
						nakikoho_tbl_idx[nakikoho_tbl_count] = j;
						nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
						nakikoho_tbl_count++;

					}else{

						// �L�����v�̊m�F
						for(int k=0; k< mentsu_count; k++){

							// ���v�ݒ�(�|���̏ꍇ)
							if( mentsu_stat[k] == ANKO && j == mentsu_hai[k] ){
								// ���v�ݒ�
								nakikoho_tbl_hai[nakikoho_tbl_count] = j;
								nakikoho_tbl_act[nakikoho_tbl_count] = ACTPON;
								nakikoho_tbl_idx[nakikoho_tbl_count] = j;
								nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
								nakikoho_tbl_count++;
							}

							// ���v�ݒ�(�`�[�̏ꍇ)
							if( mentsu_stat[k] == SHUNTSU && ( j == mentsu_hai[k] || j == mentsu_hai[k]+1 || j == mentsu_hai[k]+2 )){
								// ���v�ݒ�
								nakikoho_tbl_hai[nakikoho_tbl_count] = j;
								nakikoho_tbl_act[nakikoho_tbl_count] = ACTCHI;
								nakikoho_tbl_idx[nakikoho_tbl_count] = mentsu_hai[k];
								nakikoho_tbl_yesno[nakikoho_tbl_count] = false;
								nakikoho_tbl_count++;
							}

						}
					}
				}

				// ��v���u���̖�����
				tehai[j]--;

			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �̔v���̗D�揇�ʎZ�o
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::SetSutekohoPriority(){

	for(int tmp_count=0; tmp_count< sutekoho_count; tmp_count++){

		// �̔v���̗D�揇�ʐݒ�
		if (sutekoho_hai[tmp_count] < 30){

			// ��������
			if( 5 - (sutekoho_hai[tmp_count] %10) > 0){
				sutekoho_priority[tmp_count] =  5 - (sutekoho_hai[tmp_count] %10);
			}else{
				sutekoho_priority[tmp_count] =( 5 - (sutekoho_hai[tmp_count] %10) )*-1;
			}

		}else if (sutekoho_hai[tmp_count] > 30 && sutekoho_hai[tmp_count] < 35){
			sutekoho_priority[tmp_count]=8;
		}else if (sutekoho_hai[tmp_count] > 34 && sutekoho_hai[tmp_count] < 38){
			sutekoho_priority[tmp_count]=7;
		}else{
			sutekoho_priority[tmp_count]=9;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �̔v���̊m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::SetFixedSutekoho(){

	// ������
	int tmp_sutekoho_priority = -999;
	fixed_sutekoho_num=0;
	yuko_max_count=0;

	// �ő�L���v��
	for(int tmp_count=0; tmp_count< sutekoho_count; tmp_count++){
		if(shanten_normal == sutekoho_shanten[tmp_count]){
			if(yuko_max_count <= yuko_hai_count[tmp_count]){
				yuko_max_count = yuko_hai_count[tmp_count];
			}
		}
	}

	// �̔v�����
	for(int tmp_count=0; tmp_count< sutekoho_count; tmp_count++){
		if(shanten_normal == sutekoho_shanten[tmp_count] && yuko_max_count == yuko_hai_count[tmp_count]){
			if( tmp_sutekoho_priority <= sutekoho_priority[tmp_count]){
				fixed_sutekoho_num = tmp_count;
				tmp_sutekoho_priority = sutekoho_priority[tmp_count];
			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �������m�F(�ʏ�)
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::NormalShanten(){

	// ������
	shanten_normal   = 8;
	tmp_shanten      = 0;
	tmp_atama_count  = 0;
	tmp_mentsu_count  = 0;
	tmp_taatsu_count  = 0;

	// �����J�n
	for(int hai=1; hai<PAI_MAX; hai++){
		//
		if(tehai[hai] >= 2){            
			tmp_atama_count++;
			tehai[hai] -= 2;
			// tmp_atama_hai=i;  // ���v�ԍ��̐ݒ�
			mentsu_cut(1);
			tehai[hai] += 2;
			// tmp_atama_hai=0;  // ���v�ԍ��̖�����
			tmp_atama_count--;
		}
	}

    // ���Ȃ��̏ꍇ
    mentsu_cut(1);

}

/* ---------------------------------------------------------------------------------------------- */
// �����c�폜����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::mentsu_cut(int hai){

	// ----------------------------------------
	// 0���̓X�L�b�v
	// ----------------------------------------
	for(;!tehai[hai]; hai++);

	// ----------------------------------------
	// ������΃^�[�c����
	// ----------------------------------------
	if( hai >= PAI_MAX ){
		taatsu_cut(1);

		// �����̕Ԃ�
		return;
	}

	// ----------------------------------------
	// �A���R���Z�b�g
	// ----------------------------------------
	if(tehai[hai] >= 3){

		tmp_mentsu_count++;
		tehai[hai]-=3;
		mentsu_cut(hai);  // �����c�J�b�g�̍ċN����
		tehai[hai]+=3;
		tmp_mentsu_count--;

	}

	// ----------------------------------------
	// �V�����c���Z�b�g
	// ----------------------------------------
	if(tehai[hai+1] && tehai[hai+2] && hai<30){

		tmp_mentsu_count++;
		tehai[hai]--;
		tehai[hai+1]--;
		tehai[hai+2]--;
		mentsu_cut(hai);   // �����c�J�b�g�̍ċN����
		tehai[hai]++;
		tehai[hai+1]++;
		tehai[hai+2]++;
		tmp_mentsu_count--;

	}

	// ----------------------------------------
	// ���̃����c�J�b�g�̍ċN����
	// ----------------------------------------
	mentsu_cut(hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// �^�[�c�폜����
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::taatsu_cut(int hai){

	// ----------------------------------------
	// 0���̓X�L�b�v
	// ----------------------------------------
	for(;!tehai[hai]; hai++);

	// ----------------------------------------
	// ������΃V�����e���Z�o
	// ----------------------------------------
	if( hai >= PAI_MAX ){

		// �V�����e�����̎Z�o
		tmp_shanten = 8-(naki_count-kakan_count)*2-tmp_mentsu_count*2-tmp_taatsu_count-tmp_atama_count;

		if( tmp_shanten < shanten_normal){

			// �ʏ�V�����e���̉��u��
			shanten_normal=tmp_shanten;

		}

		// �����̕Ԃ�
		return;
	}

	// ----------------------------------------
	// �^�[�c���Z�b�g
	// ----------------------------------------
	if( (naki_count-kakan_count)+tmp_mentsu_count+tmp_taatsu_count < 4 ){

		// �g�C�c�J�b�g
		if(tehai[hai]==2){

			tmp_taatsu_count++;
			tehai[hai]-=2;
			taatsu_cut(hai);
			tehai[hai]+=2;
			tmp_taatsu_count--;
		}

		// ���ʃJ�b�g
		if(tehai[hai+1] && hai<30){

			tmp_taatsu_count++;
			tehai[hai]--, tehai[hai+1]--;
			taatsu_cut(hai);
			tehai[hai]++, tehai[hai+1]++;
			tmp_taatsu_count--;
		}

		// �J���`�����J�b�g
		if( tehai[hai+2]&& hai<30 && hai%10<=8 ){

			tmp_taatsu_count++;
			tehai[hai]--, tehai[hai+2]--;
			taatsu_cut(hai);
			tehai[hai]++, tehai[hai+2]++;
			tmp_taatsu_count--;
		}
	}

	// ----------------------------------------
	// ���̃^�[�c�ċN����
	// ----------------------------------------
	taatsu_cut(hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// �������m�F(�ʏ�_�ʎq���t�^��)
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::NormalShanten_detail(){

	// ������
	shanten_normal   = 8;
	tmp_shanten      = 0;
	tmp_atama_count  = 0;
	tmp_mentsu_count  = 0;
	tmp_taatsu_count  = 0;

	tmp_atama_hai = 0;   // ���v�ԍ��̏�����

	// �����J�n
	for(int hai=1; hai<PAI_MAX; hai++){
		//
		if(tehai[hai] >= 2){            
			tmp_atama_count++;
			tehai[hai] -= 2;
			tmp_atama_hai = hai;   // ���v�ԍ��̐ݒ�
			mentsu_cut_detail(1);
			tehai[hai] += 2;
			tmp_atama_hai = 0;     // ���v�ԍ��̖�����
			tmp_atama_count--;
		}
	}

    // ���Ȃ��̏ꍇ
    mentsu_cut_detail(1);

}

/* ---------------------------------------------------------------------------------------------- */
// �����c�폜����(�ʎq���t�^��)
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::mentsu_cut_detail(int hai){

	// ----------------------------------------
	// 0���̓X�L�b�v
	// ----------------------------------------
	for(;!tehai[hai]; hai++);

	// ----------------------------------------
	// ������΃^�[�c����
	// ----------------------------------------
	if( hai >= PAI_MAX ){
		taatsu_cut_detail(1);

		// �����̕Ԃ�
		return;
	}

	// ----------------------------------------
	// �A���R���Z�b�g
	// ----------------------------------------
	if(tehai[hai] >= 3){

		tmp_mentsu_stat[tmp_mentsu_count] = ANKO;     // �ʎq���ݒ�
		tmp_mentsu_hai[tmp_mentsu_count]  = hai;      // �v�ԍ��ݒ�
		tmp_mentsu_count++;
		tehai[hai]-=3;
		mentsu_cut_detail(hai);  // �����c�J�b�g�̍ċN����
		tehai[hai]+=3;
		tmp_mentsu_count--;
		tmp_mentsu_stat[tmp_mentsu_count] = NOMENTSU;   // �ʎq���ݒ�
		tmp_mentsu_hai[tmp_mentsu_count]  = hai;        // �v�ԍ��ݒ�

	}

	// ----------------------------------------
	// �V�����c���Z�b�g
	// ----------------------------------------
	if(tehai[hai+1] && tehai[hai+2] && hai<30){

		tmp_mentsu_stat[tmp_mentsu_count] = SHUNTSU;  // �ʎq���ݒ�
		tmp_mentsu_hai[tmp_mentsu_count]  = hai;      // �v�ԍ��ݒ�
		tmp_mentsu_count++;
		tehai[hai]--;
		tehai[hai+1]--;
		tehai[hai+2]--;
		mentsu_cut_detail(hai);   // �����c�J�b�g�̍ċN����
		tehai[hai]++;
		tehai[hai+1]++;
		tehai[hai+2]++;
		tmp_mentsu_count--;
		tmp_mentsu_stat[tmp_mentsu_count] = NOMENTSU;   // �ʎq���ݒ�
		tmp_mentsu_hai[tmp_mentsu_count]  = hai;        // �v�ԍ��ݒ�

	}

	// ----------------------------------------
	// ���̃����c�J�b�g�̍ċN����
	// ----------------------------------------
	mentsu_cut_detail(hai+1);

}

/* ---------------------------------------------------------------------------------------------- */
// �^�[�c�폜����(�^�[�c���t�^��)
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::taatsu_cut_detail(int hai){

	// ----------------------------------------
	// 0���̓X�L�b�v
	// ----------------------------------------
	for(;!tehai[hai]; hai++);

	// ----------------------------------------
	// ������΃V�����e���Z�o
	// ----------------------------------------
	if( hai >= PAI_MAX ){

		// �V�����e�����̎Z�o
		tmp_shanten = 8-(naki_count-kakan_count)*2-tmp_mentsu_count*2-tmp_taatsu_count-tmp_atama_count;

		if( tmp_shanten < shanten_normal){

			// �ʏ�V�����e���̉��u��
			shanten_normal=tmp_shanten;

			// �A�^�}���Z�b�g
			atama_count = tmp_atama_count;
			atama_hai   = tmp_atama_hai;

			// �����c���Z�b�g
			mentsu_count = tmp_mentsu_count;
			for(int tmp_i=0;tmp_i<tmp_mentsu_count;tmp_i++){
				mentsu_stat[tmp_i] = tmp_mentsu_stat[tmp_i];  // �ʎq���ݒ�
				mentsu_hai[tmp_i]  = tmp_mentsu_hai[tmp_i];   // �v�ԍ��ݒ�
			}

			// �^�[�c���Z�b�g
			taatsu_count = tmp_taatsu_count;
			for(int tmp_i=0;tmp_i<tmp_taatsu_count;tmp_i++){
				taatsu_stat[tmp_i]=tmp_mentsu_stat[tmp_i];  // �^�[�c���ݒ�
				taatsu_hai[tmp_i]=tmp_taatsu_hai[tmp_i];   // �v�ԍ��ݒ�
			}

		}

		// �����̕Ԃ�
		return;
	}

	// ----------------------------------------
	// �^�[�c���Z�b�g
	// ----------------------------------------
	if( (naki_count-kakan_count)+tmp_mentsu_count+tmp_taatsu_count < 4 ){

		// �g�C�c�J�b�g
		if(tehai[hai]==2){
			tmp_taatsu_stat[tmp_mentsu_count] = TOITSU;   // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentsu_count]  = hai;      // �v�ԍ��ݒ�
			tmp_taatsu_count++;
			tehai[hai]-=2;
			taatsu_cut_detail(hai);
			tehai[hai]+=2;
			tmp_taatsu_count--;
			tmp_taatsu_stat[tmp_mentsu_count] = NOMENTSU;  // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentsu_count]  = hai;       // �v�ԍ��ݒ�
		}

		// ���ʃJ�b�g
		if(tehai[hai+1] && hai<30){

			tmp_taatsu_stat[tmp_mentsu_count] = TOITSU;   // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentsu_count]  = hai;      // �v�ԍ��ݒ�
			tmp_taatsu_count++;
			tehai[hai]--, tehai[hai+1]--;
			taatsu_cut_detail(hai);
			tehai[hai]++, tehai[hai+1]++;
			tmp_taatsu_count--;
			tmp_taatsu_stat[tmp_mentsu_count] = NOMENTSU;  // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentsu_count]  = hai;       // �v�ԍ��ݒ�
		}

		// �J���`�����J�b�g
		if( tehai[hai+2]&& hai<30 && hai%10<=8 ){

			tmp_taatsu_stat[tmp_mentsu_count] = TOITSU;   // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentsu_count]  = hai;      // �v�ԍ��ݒ�
			tmp_taatsu_count++;
			tehai[hai]--, tehai[hai+2]--;
			taatsu_cut_detail(hai);
			tehai[hai]++, tehai[hai+2]++;
			tmp_taatsu_count--;
			tmp_taatsu_stat[tmp_mentsu_count] = NOMENTSU;  // �^�[�c���ݒ�
			tmp_taatsu_hai[tmp_mentsu_count]  = hai;       // �v�ԍ��ݒ�
		}
	}

	// ----------------------------------------
	// ���̃^�[�c�ċN����
	// ----------------------------------------
	taatsu_cut_detail(hai+1);
}

/* ---------------------------------------------------------------------------------------------- */
// ��v�e�[�u����`
/* ---------------------------------------------------------------------------------------------- */
void MJSPlayer::settehaitbl(){

	// �ϐ���`
	tehai_count = 0;

	// �Ԕv���̕ϐ���`
	int tmp_aka_man;
	int tmp_aka_pin;
	int tmp_aka_sou;

	// �Ԕv���̉��ݒ�
	tmp_aka_man = aka_count[0];
	tmp_aka_pin = aka_count[1];
	tmp_aka_sou = aka_count[2];

	// ��v�e�[�u���̐ݒ�
	for(int tmp_i = 1; tmp_i < PAI_MAX; tmp_i++){

		// ��v�̐������J��Ԃ�
		for(int tmp_j = 0; tmp_j < tehai[tmp_i]; tmp_j++){

			// ��v�e�[�u���ݒ�
			tehaitbl[tehai_count] = tmp_i;

			// �Ԕv�e�[�u���ݒ�
			if(tmp_i == 5 && tmp_aka_man > 0){
				tehaitbl_aka[tehai_count] = true;
				tmp_aka_man--;
			}else if(tmp_i == 15 && tmp_aka_pin > 0){
				tehaitbl_aka[tehai_count] = true;
				tmp_aka_pin--;
			}else if(tmp_i == 25 && tmp_aka_sou > 0){
				tehaitbl_aka[tehai_count] = true;
				tmp_aka_sou--;
			}else{
				tehaitbl_aka[tehai_count] = false;
			}

			// ���u����v��;1
			tehai_count ++;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
