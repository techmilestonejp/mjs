/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.1.229(���������O�ǂݍ��ݏ����C��)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F tpread.cpp
 * �N���X��       �F MJSReadTplog
 * �����T�v       �F ���������O�ǂݍ��݃N���X
 * Ver0.1.0�쐬�� �F 2022/04/11 15:57:39
 * Ver0.1.1�쐬�� �F 2022/05/14 22:27:08
 * Ver0.1.2�쐬�� �F 2022/08/31 22:19:54
 * �ŏI�X�V��     �F 2024/11/17 16:53:23
 * 
 * Copyright (c) 2010-2022 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "tpread.h"

/* ---------------------------------------------------------------------------------------------- */
// ����������
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::TpreadInit(MJSGui *gui){

	// ----------------------------------------
	// �l�̏�����
	// ----------------------------------------
	wk_str_count = 0;

	// ----------------------------------------
	// malloc��`
	// ----------------------------------------

	// malloc��`(�\���̖{��)
	wk_str = (char**)malloc(sizeof(char*) * MJSCORE_WORK_COL);

	// malloc��`(�\���̂̊e�v�f)
	for(int i = 0; i < MJSCORE_WORK_COL; i++){
		wk_str[i] = (char*)malloc(sizeof(char) * MJSCORE_WORK_BUF);
	}

	// ----------------------------------------
	// �t�@�C��������
	// ----------------------------------------

	// �t�@�C����
	// char fname[] = "mjscore.txt";

	// C11�œ����@VisualC++2012�ȍ~�ł͂�����̂ݎg�p�\
	errno_t err;                        // errno_t�^(int�^)

	// fopen����
	// err = fopen_s(&fp, fname, "r");     // �t�@�C�����J���B���s����ƃG���[�R�[�h��Ԃ��B
	err = fopen_s(&fp, gui->log_name_mjsocre, "r");     // �t�@�C�����J���B���s����ƃG���[�R�[�h��Ԃ��B
	if(err != 0) {
		MessageBox(NULL, "fopen���s", "���s", MB_OK);
	} 

}

/* ---------------------------------------------------------------------------------------------- */
// �㏈��
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::TpreadPost(){

	// ----------------------------------------
	// free��`
	// ----------------------------------------

	// free��`
	for(int i = 0; i < MJSCORE_WORK_COL; i++){
		free(wk_str[i]);
	}

	// free��`
	free(wk_str);

	// ----------------------------------------
	// �t�@�C���N���[�Y
	// ----------------------------------------

	// �t�@�C���N���[�Y
	fclose(fp); 

}

/* ---------------------------------------------------------------------------------------------- */
// �ǂݍ��ݎ��s����
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::TpreadExec(MJSTkinfo *tk){

	// Mjscore�ǂݍ��ݏ���
	Read_mjscore();

	// Tkinfo�ݒ菈��
	Set_tkinfo(tk);

}

/* ---------------------------------------------------------------------------------------------- */
// mjscore�̓ǂݍ���
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Read_mjscore(){

	// ----------------------------------------
	// ������
	// ----------------------------------------

	// �o�b�t�@��`
	char fgets_buf[MJSCORE_FGET_BUF];   //  fgets��1�s�ǂݍ��ݗp
	int  fgets_buf_point;               //  fget�̃o�b�t�@�̈ʒu���

	// �ǂݍ��ݕ�����`�p
	char tmp_wk_str[MJSCORE_WORK_BUF];  //  1���[�h�̃o�b�t�@�p
	char tmp_buf[3];                    //  ���������p

	// �󔒊m�F�t���O
	int space_flg;                      // 0�F�����Ȃ�(�󔒃X�y�[�X�̂�) 1�F�󔒈ȊO�̕�����

	// ----------------------------------------
	// fgets����
	// ----------------------------------------
	while( fgets( fgets_buf, MJSCORE_FGET_BUF, fp) != NULL) {

		// �l�̏�����
		fgets_buf_point = 0;
		space_flg = 0;              // �u�󔒁v�u���s�v�ȊO�̔��p������Ǎ��񂾏ꍇ�́A�uspace_flg = 1�v�Ƃ���B
		wsprintf(tmp_wk_str, "");   

		/* ---------------------------------------- */
		// fget�Ŏ擾������������s���܂Ŋm�F����
		/* ---------------------------------------- */
	    while( fgets_buf[fgets_buf_point] != '\0' ){

			// �S�p�E���p�̔���
			if(_ismbblead(fgets_buf[fgets_buf_point])){

				/* ---------------------------------------- */
				// �S�p�����̊i�[
				/* ---------------------------------------- */
				tmp_buf[0] = fgets_buf[fgets_buf_point];
				tmp_buf[1] = fgets_buf[fgets_buf_point+1];
				tmp_buf[2] = '\0';
				fgets_buf_point+=2;

				// �S�p��������
				space_flg = 1;
				wsprintf(tmp_wk_str, "%s%s", tmp_wk_str, tmp_buf);

			}else{

				/* ---------------------------------------- */
				// ���p�����̊i�[
				/* ---------------------------------------- */
				tmp_buf[0] = fgets_buf[fgets_buf_point];
				tmp_buf[1] = '\0';
				fgets_buf_point++;

				/* ---------------------------------------- */
				// �������o(��)
				/* ---------------------------------------- */
				if ( strcmp(tmp_buf, " " ) == 0 ){

					// �u�󔒋�؂�v�ŕ�����ǋL
					if(space_flg == 1){
						space_flg = 0;

						// wk�\���̂Ɉꎞ�f�[�^���i�[�A���̌�tmp_wk_str�͏�����
						Set_wk(tmp_wk_str);
						wsprintf(tmp_wk_str, "");

					}

				/* ---------------------------------------- */
				// �������o(���s)
				/* ---------------------------------------- */
				}else if(strcmp(tmp_buf, "\n") == 0){

					// �u�󔒋�؂�v�ŕ�����ǋL
					if(space_flg == 1){
						space_flg = 0;

						// wk�\���̂Ɉꎞ�f�[�^���i�[�A���̌�tmp_wk_str�͏�����
						Set_wk(tmp_wk_str);
						wsprintf(tmp_wk_str, "");

					}

					// �u���s��؂�v�����̏ꍇ�́A�ԂɁu+�v������}������
					wsprintf(tmp_wk_str, "+");
					Set_wk(tmp_wk_str);
					wsprintf(tmp_wk_str, "");

				/* ---------------------------------------- */
				// ���̑��̕������o
				/* ---------------------------------------- */
				}else{

					// �u�󔒁v�u���s�v�ȊO�̔��p��������
					space_flg = 1;
					wsprintf(tmp_wk_str, "%s%s", tmp_wk_str, tmp_buf);

				}

			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// wk�\���̂Ɉꎞ�f�[�^���i�[
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_wk(char* str){

	wsprintf(wk_str[wk_str_count], "%s", str);
	wk_str_count ++;

}

/* ---------------------------------------------------------------------------------------------- */
// �v�ԍ��m�F����
/* ---------------------------------------------------------------------------------------------- */
int MJSReadTplog::Chk_painum(char* str){

	// �v�ԍ��ݒ�
	int hainum = 0;

	// ���������p
	char tmp_str[10];
	char tmp_hai_str_init[3];
	char tmp_hai_str_post[3];

	// ��Ɨp�ϐ��ɑ��
	wsprintf(tmp_str, "%s", str);

	// �S�p�E���p�̔���
	if(_ismbblead(tmp_str[0])){

		// �������o(�S�p)
		if(      strcmp( tmp_str, "��" ) == 0){
			hainum = 31;
		}else if(strcmp( tmp_str, "��" ) == 0){
			hainum = 32;
		}else if(strcmp( tmp_str, "��" ) == 0){
			hainum = 33;
		}else if(strcmp( tmp_str, "�k" ) == 0){
			hainum = 34;
		}else if(strcmp( tmp_str, "��" ) == 0){
			hainum = 35;
		}else if(strcmp( tmp_str, "��" ) == 0){
			hainum = 36;
		}else if(strcmp( tmp_str, "��" ) == 0){
			hainum = 37;
		}else{
			hainum = 0;
		}

	}else{

		// ���p�����̏ꍇ�̑O��
		tmp_hai_str_init[0] = tmp_str[0];
		tmp_hai_str_init[1] = '\0';

		// ���p�����̏ꍇ�̌㔼
		tmp_hai_str_post[0] = tmp_str[1];
		tmp_hai_str_post[1] = '\0';

		// �������o(���p_�O����)
		if(      strcmp( tmp_hai_str_init, "1" ) == 0){
			hainum = 1;
		}else if(strcmp( tmp_hai_str_init, "2" ) == 0){
			hainum = 2;
		}else if(strcmp( tmp_hai_str_init, "3" ) == 0){
			hainum = 3;
		}else if(strcmp( tmp_hai_str_init, "4" ) == 0){
			hainum = 4;
		}else if(strcmp( tmp_hai_str_init, "5" ) == 0){
			hainum = 5;
		}else if(strcmp( tmp_hai_str_init, "6" ) == 0){
			hainum = 6;
		}else if(strcmp( tmp_hai_str_init, "7" ) == 0){
			hainum = 7;
		}else if(strcmp( tmp_hai_str_init, "8" ) == 0){
			hainum = 8;
		}else if(strcmp( tmp_hai_str_init, "9" ) == 0){
			hainum = 9;
		}else{
			hainum = 0;
		}

		// �������o(���p_�㔼��)
		if(      strcmp( tmp_hai_str_post, "m" ) == 0){

		}else if(strcmp( tmp_hai_str_post, "M" ) == 0){
			hainum = hainum + 100;
		}else if(strcmp( tmp_hai_str_post, "p" ) == 0){
			hainum = hainum + 10;
		}else if(strcmp( tmp_hai_str_post, "P" ) == 0){
			hainum = hainum + 110;
		}else if(strcmp( tmp_hai_str_post, "s" ) == 0){
			hainum = hainum + 20;
		}else if(strcmp( tmp_hai_str_post, "S" ) == 0){
			hainum = hainum + 120;
		}else{
			hainum = 0;
		}

	}

	return hainum;

}

/* ---------------------------------------------------------------------------------------------- */
// �h���\���m�F
/* ---------------------------------------------------------------------------------------------- */
int MJSReadTplog::Chk_DoraHyoji(int hai){

	return 0;

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F���C������
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo(MJSTkinfo *tk){

	bool chk_kyoku_mode = true ;   // �Ǔǂݍ��݃��[�h�̊m�F
	tk->kyoku_index = 0;           // �ǂ̃C���f�b�N�X
	wk_index = 0;                  // ��Ɨp�\���̂̃C���f�b�N�X

	// mjscore_read_mode = 1 �F ��J�n���ǂݍ���
	Set_tkinfo_tkstart(tk);

	// mjscore_read_mode = 2 �F �v���[���[���ǂݍ���
	Set_tkinfo_plyprof(tk);

	// �Ǐ��̓ǂݍ���
	while(chk_kyoku_mode) {

		// mjscore_read_mode = 3 �F �Ǐ��
		Set_tkinfo_kyoku_score(tk, tk->kyoku_index);

		// mjscore_read_mode = 4 �F �a�����
		Set_tkinfo_agariinfo(tk, tk->kyoku_index);

		// mjscore_read_mode = 5 �F �z�v���
		Set_tkinfo_haipai(tk, tk->kyoku_index);

		// mjscore_read_mode = 6 �F �h�����
		Set_tkinfo_dora(tk, tk->kyoku_index);

		// mjscore_read_mode = 7 �F �A�N�V�������
		Set_tkinfo_actinfo(tk, tk->kyoku_index);

		// mjscore_read_mode = 8 �F ��I���m�F
		chk_kyoku_mode = Set_tkinfo_checkend();

		// �ǃC���f�b�N�X��+1
		tk->kyoku_index++;

	 }

	// mjscore_read_mode = 9 �F ��I�����ǂݍ���
	Set_tkinfo_tkend(tk);

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F mjscore_read_mode = 1 �F ��J�n���ǂݍ���
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_tkstart(MJSTkinfo *tk){

	// INDEX��+1����B(��؂蕶���u===�v�����邽��)
	wk_index++;

	// �얼
	wsprintf(tk->tkname, "%s", wk_str[wk_index]);
	wk_index++;

	// ��ԍ�
	wsprintf(tk->tkno  , "%s", wk_str[wk_index]);
	wk_index++;
	wk_index++;

	// ��J�n��
	wsprintf(tk->startdate, "%s", wk_str[wk_index]);
	wk_index++;

	// ��J�n����
	wsprintf(tk->starttime, "%s:00", wk_str[wk_index]);
	wk_index++;

	// �Q�[����
	wsprintf(tk->tkgname, "%s", "������");

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F mjscore_read_mode = 2 �F �v���[���[���ǂݍ���
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_plyprof(MJSTkinfo *tk){

	// �ϐ���`
	char tmp_str[10];
	int i=0;
	int j=0;

	// ----------------------------------------
	// ���_�����J��Ԃ��ǂݍ���
	// ----------------------------------------

	// �uwk_index��+2����
	wk_index=wk_index+2;

	// ----------------------------------------
	// ���_���̓ǂݍ���
	// ----------------------------------------

	// �������_�̓ǂݍ���
	while(wk_str[wk_index][i] != '\0'){
		// �S�p����
		if(_ismbblead(wk_str[wk_index][i])){
			i+=2;
		}else{
			// ���p�����̊i�[
			tmp_str[j] = wk_str[wk_index][i];
			i++;
			j++;
		}
	}

	// �I�������̑}��
	tmp_str[j] = '\0';

	// ���_�̑}��
	tk->init_score = atoi(tmp_str);

	// wk_index��+1
	wk_index++;

	// ----------------------------------------
	// �v���[���[���̓ǂݍ���
	// ----------------------------------------

	for(int ply_i = 0; ply_i < 4; ply_i++){

		// ������
		i=3;  // �v���[���[���̑O�ɂ���[1]�͓ǂݍ��܂Ȃ�
		j=0;
		wsprintf(tk->plyname[ply_i], "" );

		// �v���[���[���̓ǂݍ��ݏ���
		while(wk_str[wk_index][i] != '\0'){

			// �S�p����
			if(_ismbblead(wk_str[wk_index][i])){

				// �S�p�����ǋL
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = wk_str[wk_index][i+1];
				tmp_str[2] = '\0';
				wsprintf(tk->plyname[ply_i], "%s%s", tk->plyname[ply_i], tmp_str);
				i+=2;

			}else{

				// ���p�����ǋL
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = '\0';
				wsprintf(tk->plyname[ply_i], "%s%s", tk->plyname[ply_i], tmp_str);
				i++;
			}
		}

		// ���[�g�m�F����
		wk_index++; 

		// wk_index��+1
		wk_index++;

	}

	// wk_index��+1
	wk_index++;

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F mjscore_read_mode = 3 �F �Ǐ��ƃv���[���[���_���
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_kyoku_score(MJSTkinfo *tk, int kyoku_index){

	// ----------------------------------------
	// ������
	// ----------------------------------------

	// �����V�[�h�̏�����
	tk->kyoku[kyoku_index].seed_num = 0;

	// �Ǖϐ��̏�����
	for(int tmp_ply_num = 0; tmp_ply_num < PLAYER_MAX; tmp_ply_num++){

		// �z�v
		for(int i = 0; i < PAI_MAX; i++){
			tk->kyoku[kyoku_index].tehai[tmp_ply_num][i] = 0;
		}

		// �z�v�̐Ԑ�
		for(int i = 0; i < AKA_TYPE_MAX_COUNT; i++){
			tk->kyoku[kyoku_index].aka_count[tmp_ply_num][i] = 0;
		}

		// �ϐ���`(����)
		tk->kyoku[kyoku_index].naki_count[tmp_ply_num] = 0;

	}

	// ----------------------------------------
	// �ǊJ�n���_�̐ݒ�
	// ----------------------------------------

	// �ǊJ�n���_�̐ݒ�
	if(kyoku_index > 0){
		for(int ply_i = 0; ply_i < 4; ply_i++){
			tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i] = tk->kyoku[kyoku_index-1].ply_kyoku_end_score[ply_i];
		}
	}

	// ----------------------------------------
	// �Ǐ��̓ǂݍ���
	// ----------------------------------------

	// �ϐ���`
	char tmp_str[10];
	int i=0;
	int j=0;
	tk->kyoku[kyoku_index].kyoku=0;

	while(wk_str[wk_index][i] != '\0'){

		// �S�p����
		if(_ismbblead(wk_str[wk_index][i])){

			// �S�p�����̊i�[
			tmp_str[0] = wk_str[wk_index][i];
			tmp_str[1] = wk_str[wk_index][i+1];
			tmp_str[2] = '\0';
			i+=2;

			// �������o(�S�p)
			if ( strcmp( tmp_str, "��" ) == 0){
				tk->kyoku[kyoku_index].kyoku=0;
			}else if(strcmp(tmp_str, "��") == 0){
				tk->kyoku[kyoku_index].kyoku=4;
			}

		}else{

			// ���p�����̊i�[
			tmp_str[0] = wk_str[wk_index][i];
			tmp_str[1] = '\0';
			i++;

			// �������o(���p)
			if (strcmp( tmp_str, "1" ) == 0){
				// �����Ȃ�
			}else if(strcmp( tmp_str, "2" ) == 0){
				tk->kyoku[kyoku_index].kyoku++;
			}else if(strcmp( tmp_str, "3" ) == 0){
				tk->kyoku[kyoku_index].kyoku+=2;
			}else if(strcmp( tmp_str, "4" ) == 0){
				tk->kyoku[kyoku_index].kyoku+=3;
			}else{
				tk->kyoku[kyoku_index].kyoku=0;
			}
		}
	}

	// wk_index��+1
	wk_index++;

	// ----------------------------------------
	// �c�~�_���̓ǂݍ���
	// ----------------------------------------

	// �c�~�_�E���[�`�_
	tk->kyoku[kyoku_index].tsumibo = 0;
	tk->kyoku[kyoku_index].riichbo = 0;

	// wk_index��+1
	wk_index++;

	// ----------------------------------------
	// �I�ǎ��̓��_���̓ǂݍ���
	// ----------------------------------------

	// ���[�h�ݒ�
	int mode=0;

	// ���_������
	for(int ply_i = 0; ply_i < 4; ply_i++){
		tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[ply_i] = 0;
	}

	// ���_���
	while(mode == 0){
		// �������o(�S�p)
		if ( strcmp( wk_str[wk_index], "+" ) == 0){
			mode=1;
		}else if(strcmp(wk_str[wk_index], tk->plyname[0]) == 0){
			tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[0]=atoi(wk_str[wk_index+1]);
			wk_index++;
		}else if(strcmp(wk_str[wk_index], tk->plyname[1]) == 0){
			tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[1]=atoi(wk_str[wk_index+1]);
			wk_index++;
		}else if(strcmp(wk_str[wk_index], tk->plyname[2]) == 0){
			tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[2]=atoi(wk_str[wk_index+1]);
			wk_index++;
		}else if(strcmp(wk_str[wk_index], tk->plyname[3]) == 0){
			tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[3]=atoi(wk_str[wk_index+1]);
			wk_index++;
		}
		// wk_index��+1
		wk_index++;
	}

	// �Ǔ��_�̐ݒ�
	for(int ply_i = 0; ply_i < 4; ply_i++){
		tk->kyoku[kyoku_index].ply_kyoku_end_score[ply_i] = tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i] + 
		                                                    tk->kyoku[kyoku_index].ply_agari_yk[0].kyoku_score[ply_i];
	}
}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F mjscore_read_mode = 4 �F �a�����ǂݍ���
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_agariinfo(MJSTkinfo *tk, int kyoku_index){

	// �ϐ���`
	int mode = 0;
	tk->kyoku[kyoku_index].ply_agari_yk[0].yakucount = 0;

	// �𖼑��
	while(mode == 0){
		// �������r
		if ( strcmp( wk_str[wk_index], "+" ) == 0){
			mode = 1;
		}else{

			// �����̓���
			wsprintf(tk->kyoku[kyoku_index].yakuname[tk->kyoku[kyoku_index].ply_agari_yk[0].yakucount], "%s", wk_str[wk_index]);
			tk->kyoku[kyoku_index].ply_agari_yk[0].yakucount++;

		}
		// wk_index��+1
		wk_index++;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F mjscore_read_mode = 5 �F �z�v���
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_haipai(MJSTkinfo *tk, int kyoku_index){

	// �z�v�ǂݍ���
	for(int ply_i = 0; ply_i < 4; ply_i++){
		Set_tkinfo_haipai_sub(tk, kyoku_index, ply_i);
		wk_index++;
		wk_index++;
	}

}


/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F mjscore_read_mode = 5a �F �z�v���(�T�u����)
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_haipai_sub(MJSTkinfo *tk, int kyoku_index, int pnum){

	// ----------------------------------------
	// ������
	// ----------------------------------------

	// ���������p
	char tmp_str[3];

	// �����ǂݍ��݃|�C���^
	int i=0;

	// ���������O�֘A�̕ϐ���`
	int ply_ie = 0;       // �Ə��
	int hai_read = 0 ;    // �v�ǂݎ�胂�[�h
	int hai_num = 0 ;     // �v�ԍ�

	// ----------------------------------------
	// �z�v�ǂݍ���
	// ----------------------------------------

	while(wk_str[wk_index][i] != '\0'){

		// ----------------------------------------
		// hai_read = 0�̏���
		// ----------------------------------------

		if(hai_read == 0){

			// �S�p����
			if(_ismbblead(wk_str[wk_index][i])){

				// �S�p�����̊i�[
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = wk_str[wk_index][i+1];
				tmp_str[2] = '\0';
				i+=2;

				// �Ȃ̊m�F(hai_read == 0)
				if ( strcmp( tmp_str, "��" ) == 0){
					tk->kyoku[kyoku_index].ie[ply_ie]=0;
				}else if(strcmp(tmp_str, "��") == 0){
					tk->kyoku[kyoku_index].ie[ply_ie]=1;
				}else if(strcmp(tmp_str, "��") == 0){
					tk->kyoku[kyoku_index].ie[ply_ie]=2;
				}else if(strcmp(tmp_str, "�k") == 0){
					tk->kyoku[kyoku_index].ie[ply_ie]=3;
				}

			}else{

				// ���p�����̊i�[
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = '\0';
				i++;

				// �Ə��̏I��
				if ( strcmp( tmp_str, "]" ) == 0){
					// ���[�h�ύX
					 hai_read = 1 ;
				}else if(strcmp(tmp_str, "1") == 0){
					// �v�ԍ��w��
					ply_ie = 0 ;
				}else if(strcmp(tmp_str, "2") == 0){
					// �v�ԍ��w��
					ply_ie = 1 ;
				}else if(strcmp(tmp_str, "3") == 0){
					// �v�ԍ��w��
					ply_ie = 2 ;
				}else if(strcmp(tmp_str, "4") == 0){
					// �v�ԍ��w��
					ply_ie = 3 ;
				}

			}

		// ----------------------------------------
		// hai_read = 1�̏���
		// ----------------------------------------

		}else if(hai_read == 1){

			// �������̊i�[
			tmp_str[0] = wk_str[wk_index][i];
			tmp_str[1] = wk_str[wk_index][i+1];
			tmp_str[2] = '\0';
			i+=2;

			// �v�ԍ��̐ݒ�
			hai_num = Chk_painum(tmp_str);

			// �Ԕv�m�F
			if(hai_num > 100){

				// �v�ԍ�������
				hai_num = hai_num - 100;

				// �Ԕv���Z
				if( (hai_num-5)/10 == 0 || (hai_num-5)/10 == 1 || (hai_num-5)/10 == 2 ){
					tk->kyoku[kyoku_index].aka_count[pnum][(hai_num-5)/10]++;
				}
			}

			// ����N���X�ɔv�ԍ���ݒ�
			tk->kyoku[kyoku_index].tehai[pnum][hai_num] ++;

			// �v�ԍ�������
			hai_num = 0 ;

		}else{

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F mjscore_read_mode = 6 �F �h�����
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_dora(MJSTkinfo *tk, int kyoku_index){

	// ----------------------------------------
	// ����ݒ� - �h���ݒ�(���u��)
	// ----------------------------------------
	tk->kyoku[kyoku_index].doracount   = 1;
	tk->kyoku[kyoku_index].dora[0]     = 21;
	tk->kyoku[kyoku_index].dora_aka[0] = false;

	// ----------------------------------------
	// �h�����ǂݍ���
	// ----------------------------------------
	wk_index++;
	wk_index++;

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F mjscore_read_mode = 7 �F �A�N�V�������
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_actinfo(MJSTkinfo *tk, int kyoku_index){

	// ----------------------------------------
	// �u+�v�u*�v�Ƒ����̂ŃX�L�b�v����
	// ----------------------------------------
	wk_index++;
	wk_index++;

	// ----------------------------------------
	// �ϐ���`
	// ----------------------------------------

	// �S�p�\����`
	char tmp_str[3];         // ���������p

	// �Ɣԍ��̊i�[
	int ply_ie = 0;          // �v���[���[���Ƃ̉Ɣԍ���`

	// �v�ǂݍ��݊J�n�ł��邩�̂��H
	int act_read_mode = 0 ;  // +����񑱂��ĂȂ����H
	int hai_read = 0 ;       // �v���[���[=1�A�A�N�V����=2�A�v���=3�A�⑫=4
	int hai_num = 0 ;        // �v�ԍ�

	// �J�J���t���O
	int kakan_flg;

	// ----------------------------------------
	// �A�N�V�������ݒ� - �z�v��
	// ----------------------------------------
	tk->kyoku[kyoku_index].act_stat[0]  = HAIPAI;
	tk->kyoku[kyoku_index].act_ply[0]   = 4;
	tk->kyoku[kyoku_index].react_ply[0] = 4;
	tk->kyoku[kyoku_index].act_hai[0]   = 0;
	tk->kyoku[kyoku_index].act_count    = 1;

	// ----------------------------------------
	// �A�N�V�����ǂݍ���
	// ----------------------------------------

	// ��A�N�V�����̓ǂݍ���
	while( act_read_mode < 2){

	// �����ǂݍ��݃|�C���^
	int i=0;
	tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]=0;

		// ----------------------------------------
		// �s�ǂݍ���
		// ----------------------------------------

		while(wk_str[wk_index][i] != '\0'){

			// ----------------------------------------
			// hai_read = 0�̏���
			// ----------------------------------------

			if(hai_read == 0){

				// ���p�����̊i�[
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = '\0';
				i++;

				// �u*�v�ł���΁A�Ǎ��ĊJ
				if ( strcmp( tmp_str, "*" ) == 0 ){

					// ���[�h�ύX
					act_read_mode = 0 ;

				// ���s��؂蕶��
				}else if(strcmp(tmp_str, "+") == 0 && act_read_mode == 0){

					// ���[�h�ύX
					act_read_mode = 1 ;

				// �u+�v����������ꍇ�ɂ͓Ǎ��I��

				}else if(strcmp(tmp_str, "+") == 0 && act_read_mode == 1){

					// �Ō�̃A�N�V�������u�a���v�ł���΁u�ǏI���v�A�u�̔v�v�ł���΁u���ǁv�Ɓu�ǏI���v
					if ( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count-1] != PLYTSUMOAGARI && tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count-1] != PLYACTRON ){

						// �A�N�V������� - ����
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]  = RYUKYOKU;
						tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]   = 4;
						tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;
						tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]   = 0;
						tk->kyoku[kyoku_index].act_count++;

					}

						// �A�N�V������� - �ǌ��ʕ\��
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]  = KYOKURESULT;
						tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]   = 4;
						tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;
						tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]   = 0;
						tk->kyoku[kyoku_index].act_count++;

					// �v�ԍ��w��F(�Ǎ��I��)
					act_read_mode = 2 ;

				}else if(strcmp(tmp_str, "1") == 0 && hai_read == 0){

					// �v���[���[�ԍ��w��
					tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]=0;
					hai_read = 1;

					// ���A�N�V�����v���[���[������`
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;

				}else if(strcmp(tmp_str, "2") == 0 && hai_read == 0){

					// �v���[���[�ԍ��w��
					tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]=1;
					hai_read = 1;

					// ���A�N�V�����v���[���[������`
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;

				}else if(strcmp(tmp_str, "3") == 0 && hai_read == 0){

					// �v���[���[�ԍ��w��
					tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]=2;
					hai_read = 1;

					// ���A�N�V�����v���[���[������`
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;

				}else if(strcmp(tmp_str, "4") == 0 && hai_read == 0){

					// �v���[���[�ԍ��w��
					tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]=3;
					hai_read = 1;

					// ���A�N�V�����v���[���[������`
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = 4;

				}

			// ----------------------------------------
			// hai_read = 1�̏����F�A�N�V�������
			// ----------------------------------------

			}else if(hai_read == 1){

				// ���p�����̊i�[
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = '\0';
				i++;

				// ----------------------------------------
				// �A�N�V������� -�uG�v�F���̏���(Get)
				// ----------------------------------------
				if(strcmp(tmp_str, "G") == 0 && hai_read == 1){

					tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTTSUMO;
					hai_read = 2;

				// ----------------------------------------
				// �A�N�V������� - �̔v
				// ----------------------------------------
				}else if(strcmp(tmp_str, "d") == 0 && hai_read == 1){

					//  tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] = PLYACTSUTE;
					// ��O�̏������A�N�V�����̏ꍇ�͖���
					if(tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count-1] == PLYACTPON ||
					   tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count-1] == PLYACTCHI ){
						// �v�A�N�V����
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] = PLYACTNAKISUTE;
					}else{
						// �̔v�A�N�V����
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] = PLYACTSUTE;
					}
					hai_read = 2;

				// ----------------------------------------
				// �A�N�V������� - ���̐؂�
				// ----------------------------------------
				}else if(strcmp(tmp_str, "D") == 0 && hai_read == 1){

					tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTTSUMOGIRI;
					hai_read = 2;

				// ----------------------------------------
				// �A�N�V������� - ���[�`
				// ----------------------------------------
				}else if(strcmp(tmp_str, "R") == 0 && hai_read == 1){

					tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTRIICH;
					hai_read = 2;

				// ----------------------------------------
				// �A�N�V������� -�uN�v�F�|������
				// ----------------------------------------
				}else if(strcmp(tmp_str, "N") == 0 && hai_read == 1){

					// �A�N�V������� - �|������
					tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]  = PLYACTPON;                                                          // �A�N�V������` - �|��
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count-1]; // ���A�N�V�����v���[���[ - ���O�̃v���[���[�Ɠ���
					tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1]; // �v�ԍ� - ���O�̔v�Ɠ���
					tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count-1]; // �Ԕv��`

					// �����ݒ� - �|������
					tk->kyoku[kyoku_index].naki_actid[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_count;
					tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = MINKO;
					tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1]; 
					tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1]; 

					// �����ݒ�(�Ԕv�m�F�E�A�N�V�����v) - �|������
					if (tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count] == true){
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]]=1;
					}else{
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]]=0;
					}

					// �����ݒ�(�Ԕv�m�F�E��v��) - �|������
					// �v���ɐԔv��񂪂Ȃ��̂Ŏ����Ő�����B
					// tk->Check_Actid_Aka_count(kyoku_index, tk->kyoku[kyoku_index].act_count, tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]);
					tk->Check_Ply_ActTehai(kyoku_index, tk->kyoku[kyoku_index].act_count);
					if ( tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count] == 5){ 
						// �Ԕv�}���Y�̐ݒ�
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] =
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] + tk->ply_act_aka_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][0];
					}else if( tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count] == 15){
						// �Ԕv�s���Y�̐ݒ�
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] =
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] + tk->ply_act_aka_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][1];
					}else if( tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count] == 25){
						// �Ԕv�\�E�Y�̐ݒ�
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] =
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] + tk->ply_act_aka_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][2];
					}else{
						// �ʏ�v�̐ݒ�
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 0;
					}

					// ������+1
					tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]] ++;

					// ���[�h�ύX
					hai_read = 2;

				// ----------------------------------------
				// �A�N�V������� -�uC�v�F�`�[����
				// ----------------------------------------
				}else if(strcmp(tmp_str, "C") == 0 && hai_read == 1){

					// �A�N�V������� - �`�[
					tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]  = PLYACTCHI;                                                          // �A�N�V������` - �`�[
					tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count-1]; // ���A�N�V�����v���[���[ - ���O�̃v���[���[�Ɠ���
					tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1]; // �v�ԍ� - ���O�̔v�Ɠ���
					tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count-1]; // �Ԕv��`

					// �����ݒ� - �`�[
					tk->kyoku[kyoku_index].naki_actid[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_count;
					tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = MINSHUN;
					tk->kyoku[kyoku_index].naki_hai [tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];

					// �����ݒ�(�Ԕv�m�F�E�A�N�V�����v) - �`�[����
					if(tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count]){
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 1;
					}else{
						tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 0;
					}

					// ������+1
					tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]] ++;

					// ���[�h�ύX
					hai_read = 2;

				// ----------------------------------------
				// �A�N�V������� -�uK�v�F�J������
				// ----------------------------------------
				}else if(strcmp(tmp_str, "K") == 0 && hai_read == 1){

					// ��O�������̎��̂ł���Ȃ�΁A�ÞȂ�����
					if (tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count-1] == PLYACTTSUMO){

						// ���ȃt���O�̐ݒ�
						kakan_flg=0;
						for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]; tmp_i++){
							// �|�������v�ł���΁A�J�J���t���O�𗧂Ă�
							if (tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tmp_i] == tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1] ){
								kakan_flg=1;
							}
						}

						// �ÞȁE���Ȃ̊m�F
						if (kakan_flg == 1){

							// �A�N�V�������ݒ� - ����
							tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTKAKAN;                                                        // �A�N�V������` - ����
							tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]=tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];  // �v�ԍ� - ���O�̔v�Ɠ���	

							// �����ݒ� - ����
							tk->kyoku[kyoku_index].naki_actid[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_count;
							tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = KAKAN;
							tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];
							tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];

							// �Ԕv�m�F - ����
							tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 0;

							// ������+1
							tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]] ++;

						}else{
							// �A�N�V�������ݒ� - �Þ�
							tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTANKAN;                                                       // �A�N�V������` - �Þ�
							tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]=tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1]; // �v�ԍ� - ���O�̔v�Ɠ���	

							// �����ݒ� - �Þ�
							tk->kyoku[kyoku_index].naki_actid[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_count;
							tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = ANKAN;
							tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];
							tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];


							// �Ԕv�m�F - �Þ�
							tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 0;

							// ������+1
							tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]] ++;

						}

					// �����̎��̂łȂ��Ȃ�΁A����
					}else{

							// �A�N�V�������ݒ� - ����
							tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]=PLYACTMINKAN;                                                       // �A�N�V������` - �Þ�
							tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]=tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];  // �v�ԍ� - ���O�̔v�Ɠ���	

							// �����ݒ� - ����
							tk->kyoku[kyoku_index].naki_actid[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = tk->kyoku[kyoku_index].act_count;
							tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]]  = MINKAN;
							tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]]   = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];
							tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]]  = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];

							// �Ԕv�m�F - ����
							tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]] = 0;

							// ������+1
							tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]] ++;

					}

					// ���[�h�ύX
					hai_read = 2;

				// ----------------------------------------
				// �A�N�V������� -�uA�v�F�a������
				// ----------------------------------------
				}else if(strcmp(tmp_str, "A") == 0 && hai_read == 1){

					// ��O�������̎��̂ł���Ȃ�΁A���̘a��
					if (tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count-1] == PLYACTTSUMO){

						// �A�N�V������� - ���̘a��
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] = PLYTSUMOAGARI;
						tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]  = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];
						tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count]  = tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count-1];

					}else{

						// �A�N�V������� - �����a��
						tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count]  = PLYACTRON;
						tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count] = tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count-1];
						tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count-1];
						tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count]   = tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count-1];

					}

					// ���[�h�ύX
					hai_read = 2;

				}

			// ----------------------------------------
			// �v�ԍ��ǂݍ���(hai_read = 2�F���́E�̂Ă̔v�A�`�[�v��1����)
			// ----------------------------------------

			}else if(hai_read == 2){

				// 2�����̊i�[
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = wk_str[wk_index][i+1];
				tmp_str[2] = '\0';
				i+=2;

				// �v�ԍ��̐ݒ�
				hai_num = Chk_painum(tmp_str);

				// �Ԕv�m�F
				if(hai_num > 100){
					hai_num = hai_num - 100;
					tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count] = true;
				}else{
					tk->kyoku[kyoku_index].act_aka[tk->kyoku[kyoku_index].act_count] = false;
				}

				// �A�N�V�����ݒ�
				tk->kyoku[kyoku_index].act_hai[tk->kyoku[kyoku_index].act_count] = hai_num;

				// �����ݒ�
				if (tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTCHI){
					// tpscore���O��p�̖vINDEX�̒l�̐ݒ�
					tk->kyoku[kyoku_index].naki_mj_idx[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]][tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].act_ply[tk->kyoku[kyoku_index].act_count]]-1] = hai_num;
				}

				// �v�ԍ�������
				hai_num = 0 ;

				// ���[�h�ύX
				hai_read = 3;

			// ----------------------------------------
			// hai_read = 3�̏���(�`�[�v��2����)
			// ----------------------------------------

			}else if(hai_read == 3){

				// 2�����̊i�[
				tmp_str[0] = wk_str[wk_index][i];
				tmp_str[1] = wk_str[wk_index][i+1];
				tmp_str[2] = '\0';
				i+=2;

			}else{

			}

		}

		// �����ǂݍ��ݏI���Ȃ玟�ɍs��
		wk_index ++;
		hai_read = 0;

		// �I������(*,+)�łȂ��Ȃ�A�A�N�V����ID�����ɍs��
		if ( strcmp( tmp_str, "*" ) != 0 && strcmp( tmp_str, "+" ) != 0 ){

			tk->kyoku[kyoku_index].act_count ++;

		}

	}

	// ----------------------------------------
	// �㏈��
	// ----------------------------------------

	// �`�[���́u���v���v�̐ݒ�
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){
		for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[tmp_pnum]; tmp_i++){
			if ( tk->kyoku[kyoku_index].naki_stat[tmp_pnum][tmp_i] == MINSHUN){
				if ( tk->kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i] - tk->kyoku[kyoku_index].naki_mj_idx[tmp_pnum][tmp_i] == -1){
					tk->kyoku[kyoku_index].naki_idx[tmp_pnum][tmp_i] = tk->kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i];
				}
				if ( tk->kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i] - tk->kyoku[kyoku_index].naki_mj_idx[tmp_pnum][tmp_i] == 1){
					tk->kyoku[kyoku_index].naki_idx[tmp_pnum][tmp_i] = tk->kyoku[kyoku_index].naki_mj_idx[tmp_pnum][tmp_i];
				}
				if ( tk->kyoku[kyoku_index].naki_hai[tmp_pnum][tmp_i] - tk->kyoku[kyoku_index].naki_mj_idx[tmp_pnum][tmp_i] == 2){
					tk->kyoku[kyoku_index].naki_idx[tmp_pnum][tmp_i] = tk->kyoku[kyoku_index].naki_mj_idx[tmp_pnum][tmp_i];
				}
			}else{
					// tk->kyoku[kyoku_index].naki_idx[tmp_pnum][tmp_i] = 0;
			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F mjscore_read_mode = 8 �F ��I���m�F
/* ---------------------------------------------------------------------------------------------- */
bool MJSReadTplog::Set_tkinfo_checkend(){

	// ���������p
	char tmp_str[3];

	// �S�p����
	if(_ismbblead(wk_str[wk_index][0])){

		// �S�p�����̊i�[
		tmp_str[0] = wk_str[wk_index][0];
		tmp_str[1] = wk_str[wk_index][1];
		tmp_str[2] = '\0';

		// �������o(�S�p)
		if ( strcmp( tmp_str, "��" ) == 0 || strcmp(tmp_str, "��") == 0 ){
			return true;
		}else{
			return false;
		}

	}else{
	
		// ���p�����̊i�[
		tmp_str[0] = wk_str[wk_index][0];
		tmp_str[1] = '\0';

		// �������o(���p)
		if ( strcmp( tmp_str, "-" ) == 0 ){
			return false;
		}else{
			return true;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// Tkinfo�ݒ菈���F mjscore_read_mode = 9 �F ��I�����ǂݍ���
/* ---------------------------------------------------------------------------------------------- */
void MJSReadTplog::Set_tkinfo_tkend(MJSTkinfo *tk){

	// �uwk_index��+5�ɂ���
	wk_index=wk_index+5;

	// ----------------------------------------
	// ���ʊi�[
	// ----------------------------------------

	for(int jun = 0; jun < PLAYER_MAX; jun++){
		// [��1]�v���[���̏��ʂ̒��o
		if(strcmp(wk_str[wk_index], tk->plyname[0]) == 0){
			tk->plyjun[jun]=0;
			tk->plyEndscore[jun]=atoi(wk_str[wk_index+1]);
			wk_index=wk_index+4;
		// [��2]�v���[���̏��ʂ̒��o
		}else if(strcmp(wk_str[wk_index], tk->plyname[1]) == 0){
			tk->plyjun[jun]=1;
			tk->plyEndscore[jun]=atoi(wk_str[wk_index+1]);
			wk_index=wk_index+4;
		// [��3]�v���[���̏��ʂ̒��o
		}else if(strcmp(wk_str[wk_index], tk->plyname[2]) == 0){
			tk->plyjun[jun]=2;
			tk->plyEndscore[jun]=atoi(wk_str[wk_index+1]);
			wk_index=wk_index+4;
		// [��4]�v���[���̏��ʂ̒��o
		}else if(strcmp(wk_str[wk_index], tk->plyname[3]) == 0){
			tk->plyjun[jun]=3;
			tk->plyEndscore[jun]=atoi(wk_str[wk_index+1]);
			wk_index=wk_index+4;
		}
	}

	// ----------------------------------------
	// ��I������
	// ----------------------------------------

	// wk_index��+2�ɂ���
	wk_index=wk_index+2;

	// ��I��������`
	wsprintf(tk->enddate, "%s", wk_str[wk_index]);
	wk_index++;

	// ��I�����t��`
	wsprintf(tk->endtime, "%s", wk_str[wk_index]);
	wk_index++;

}

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
