/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.1.229(MJAI���O�\���F�_�u�����\��)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F readmjai.cpp
 * �N���X��       �F MJSReadMjai
 * �����T�v       �F MJAI���O�ǂݍ��݃N���X
 * Ver0.1.2�쐬�� �F 2023/10/07 22:32:26
 * �ŏI�X�V��     �F 2024/11/17 16:53:23
 * 
 * Copyright (c) 2022-2023 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "readmjai.h"

/* ---------------------------------------------------------------------------------------------- */
// ����������
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::read_logfile_init(MJSGui *gui){

	// ----------------------------------------
	// �t�@�C��������
	// ----------------------------------------

	// MJAI���O�̃t�@�C������`
	// char fname[] = "mjailog.json";
	// wsprintf(gui->log_name_mjai,"mjailog.json");

	// C11�œ��� VisualC++2012�ȍ~�ł͂�����̂ݎg�p�\
	errno_t err; // errno_t�^(int�^)

	// fopen����
	// err = fopen_s(&fp, fname, "r");     // �t�@�C�����J���B���s����ƃG���[�R�[�h��Ԃ��B
	err = fopen_s(&fp, gui->log_name_mjai, "r");     // �t�@�C�����J���B���s����ƃG���[�R�[�h��Ԃ��B
	if(err != 0) {
		MessageBox(NULL, "fopen���s", "���s", MB_OK);
	} 

	// ----------------------------------------
	// �f�o�O���O
	// ----------------------------------------
/*
	// �N���C�A���g�N���X�����̃f�o�O���O
	mjaidebug = new MJSCorelog;

	// ���O�t�@�C�����ݒ�
	wsprintf(mjaidebug_name, ".\\mjai_debuglog.log" );
	mjaidebug->CorelogInit(mjaidebug_name);

	// �w�b�_�[��`
	wsprintf(mjaidebug_buf, "�w�b�_�[\n----\n" );

	// ���O�o��
	mjaidebug->CorelogPrint(mjaidebug_buf);
*/

}

/* ---------------------------------------------------------------------------------------------- */
// �㏈��
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::read_logfile_post(){

	// ----------------------------------------
	// �t�@�C���N���[�Y
	// ----------------------------------------

	// �t�@�C���N���[�Y
	fclose(fp); 

	// ----------------------------------------
	// �f�o�O���O
	// ----------------------------------------

	// delete mjaidebug;

}

/* ---------------------------------------------------------------------------------------------- */
// �ǂݍ��ݎ��s����
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::read_logfile_exec(MJSTkinfo *tk, MJSGui *gui){

	// ----------------------------------------
	// fgets����
	// ----------------------------------------
	while( fgets( line_buf, MJAI_LINE_BUF, fp) != NULL) {

		// ----------------------
		// ���C�����
		// ----------------------
		// wsprintf(line_buf, line_buf);         // ���C���o�b�t�@�ւ̃R�s�[
		Read_logline(gui);                       // ���C�����

		// ----------------------
		// (�f�o�O)���O�o��
		// ----------------------
/*
		// Gui_wk�N���X�̏o��
		for(int tmp_i = 0; tmp_i < gui->wk_str_count; tmp_i++){
			wsprintf(mjaidebug_buf, "%d:%s\n", tmp_i, gui->wk_str[tmp_i]);
			mjaidebug->CorelogPrint(mjaidebug_buf);
		}
		wsprintf(mjaidebug_buf, "----\n" );
		mjaidebug->CorelogPrint(mjaidebug_buf);
*/

		// ----------------------
		// ����N���X�̐ݒ�
		// ----------------------
		set_tkinfo(tk, gui);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// MJAI���O�̓ǂݍ���
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::Read_logline(MJSGui *gui){

	// ----------------------------------------
	// ������
	// ----------------------------------------

	// wk�C���f�b�N�X�̏�����
	gui->wk_str_count = 0;

	// �ǂݍ��ݕ�����`�p
	int  line_buf_point;                //  fget�̃o�b�t�@�̈ʒu���
	char tmp_wk_str[1024];              //  1���[�h�̃o�b�t�@�p
	char tmp_buf[3];                    //  ���������p

	// �󔒊m�F�t���O
	int space_flg;                      // 0�F�����Ȃ�(�󔒃X�y�[�X�̂�) 1�F�󔒈ȊO�̕�����

	// �l�̏�����
	line_buf_point = 0;
	space_flg = 0;                      // �u�󔒁v�u���s�v�ȊO�̔��p������Ǎ��񂾏ꍇ�́A�uspace_flg = 1�v�Ƃ���B
	wsprintf(tmp_wk_str, "");

	/* ---------------------------------------- */
	// fget�Ŏ擾������������s���܂Ŋm�F����
	/* ---------------------------------------- */
    while( line_buf[line_buf_point] != '\0' ){

		// �S�p�E���p�̔���
		if(_ismbblead(line_buf[line_buf_point])){

			/* ---------------------------------------- */
			// �S�p�����̊i�[
			/* ---------------------------------------- */
			tmp_buf[0] = line_buf[line_buf_point];
			tmp_buf[1] = line_buf[line_buf_point+1];
			tmp_buf[2] = '\0';
			line_buf_point+=2;

			// �S�p��������
			space_flg = 1;
			wsprintf(tmp_wk_str, "%s%s", tmp_wk_str, tmp_buf);

		}else{

			/* ---------------------------------------- */
			// ���p�����̊i�[
			/* ---------------------------------------- */
			tmp_buf[0] = line_buf[line_buf_point];
			tmp_buf[1] = '\0';
			line_buf_point++;

			/* ---------------------------------------- */
			// �������o(��)
			/* ---------------------------------------- */
			if ( strcmp(tmp_buf, ":" ) == 0 || strcmp(tmp_buf, "," ) == 0 ){

				// �u�󔒋�؂�v�ŕ�����ǋL
				if(space_flg == 1){
					space_flg = 0;

					// wk�\���̂Ɉꎞ�f�[�^���i�[�A���̌�tmp_wk_str�͏�����
					set_wkinfo(gui, tmp_wk_str);
					wsprintf(tmp_wk_str, "");

				}

			/* ---------------------------------------- */
			// ��������
			/* ---------------------------------------- */
			}else if( strcmp(tmp_buf, "{") == 0  || 
			          strcmp(tmp_buf, "}") == 0  || 
			          strcmp(tmp_buf, "\"") == 0 || 
			          strcmp(tmp_buf, "[") == 0  || 
			          strcmp(tmp_buf, "]") == 0  ){

			/* ---------------------------------------- */
			// �������o(���s)
			/* ---------------------------------------- */
			}else if(strcmp(tmp_buf, "\n") == 0){

				// �u�󔒋�؂�v�ŕ�����ǋL
				if(space_flg == 1){
					space_flg = 0;

					// wk�\���̂Ɉꎞ�f�[�^���i�[�A���̌�tmp_wk_str�͏�����
					set_wkinfo(gui, tmp_wk_str);
					wsprintf(tmp_wk_str, "");

				}

				// �u���s��؂�v�����̏ꍇ�́A�ԂɁu+�v������}������
				wsprintf(tmp_wk_str, "+");
				set_wkinfo(gui, tmp_wk_str);

				// �l�̏�����
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

/* ---------------------------------------------------------------------------------------------- */
// Gui�N���X�Ɉꎞ�f�[�^���i�[
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_wkinfo(MJSGui *gui, char* str){

	wsprintf(gui->wk_str[gui->wk_str_count], "%s", str);
	gui->wk_str_count++;

}

/* ---------------------------------------------------------------------------------------------- */
// ����N���X�̐ݒ菈��
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_tkinfo(MJSTkinfo *tk, MJSGui *gui){

	// ----------------------------------------
	// ��M���b�Z�[�W�̉��
	// ----------------------------------------
	for( int tmp_i = 0; tmp_i < gui->wk_str_count; tmp_i++ ) {

		// -----------------------
		// ���s
		// -----------------------
		if(strcmp(gui->wk_str[tmp_i], "+" ) == 0 ){

			// ���s�̏ꍇ�͉������Ȃ�

		// -----------------------
		// ��J�n(01:start_game)
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type" ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "start_game" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_startgame(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// �ǊJ�n(02:start_kyoku)
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type" ) == 0 && 
		         strcmp(gui->wk_str[tmp_i+1], "start_kyoku" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_startkyoku(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// ���̃A�N�V����(03:type_tsumo)
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "tsumo" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_tsumo(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// �̔v����(04:type_dahai)
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "dahai" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_dahai(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// �ÞȃA�N�V����
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "ankan" ) == 0 ){

			// �A�N�V�����ݒ�F�ÞȃA�N�V����
			set_type_ankan(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// ���ȃA�N�V����
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
		         strcmp(gui->wk_str[tmp_i+1], "kakan" ) == 0 ){

			// �A�N�V�����ݒ�F���ȃA�N�V����
			set_type_kakan(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// ���[�`�錾�A�N�V����
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "reach" ) == 0 ){

			// �A�N�V�����ݒ�F���[�`�錾�A�N�V����
			set_type_riichi(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// ���[�`�錾�󂯓���
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
		         strcmp(gui->wk_str[tmp_i+1], "reach_accepted" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_reach_accepted(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// �|������
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "pon" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_pon(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// �`�[����
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "chi" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_chi(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// �~���J������
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "daiminkan" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_minkan(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// �J���h���\��
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
		         strcmp(gui->wk_str[tmp_i+1], "dora" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_dora_open(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// �a���m�F
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "hora" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_hora(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// ����
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "ryukyoku" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_ryukyoku(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// �ǏI��
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
		         strcmp(gui->wk_str[tmp_i+1], "end_kyoku" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_endkyoku(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// ��Q�[���I��
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "end_game" ) == 0 ){

			// �A�N�V�����ݒ�
			set_type_endgame(tk, gui, tmp_i);

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// �G���[����
		// -----------------------
		}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "error" ) == 0 ){

			// �G���[����
			tk->stat = TAKUERR;

			// ���b�Z�[�W�m��̂��߂ɏ�������
			break;

		// -----------------------
		// ���̑��̃A�N�V����
		// -----------------------
		}else{

			// wk_str_count��for���[�v�ŉ񂵂Ă���Ԃ͉������Ȃ�

		}

		// -----------------------
		// �A�N�V�����m�F�͂����܂�
		// -----------------------

	} // gui->wk_count�̃��[�v


}

/* ---------------------------------------------------------------------------------------------- */
// 01:type_startgame
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_startgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// �Ǐ��ݒ�
	// ----------------------------------------

	// �Ǐ��
	tk->kyoku[tk->kyoku_index].kyoku = 0;

	// �c�~�_
	tk->kyoku[tk->kyoku_index].tsumibo = 0;

	// ���[�`�_
	tk->kyoku[tk->kyoku_index].riichbo = 0;

	// ----------------------------------------
	// �v���[���[���̐ݒ�
	// ----------------------------------------

	for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++ ) {
		// �v���[�����w��
		wsprintf(tk->plyname[tmp_pnum], gui->wk_str[tmp_pnum+3]);
	}

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = TAKUSTART;

}

/* ---------------------------------------------------------------------------------------------- */
// 02:type_startkyoku
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_startkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// �O����
	// ----------------------------------------

	// ������
	int  haipai_point=0;
	int  now_tsumo_hai=0;
	bool now_tsumo_aka = false;
	int  tmp_ie_id;
	int  tmp_dora_hai;
	bool tmp_dora_aka;

	// ----------------------------------------
	// GUI���[�h������
	// ----------------------------------------
	gui->guiTakuInit();

	// ----------------------------------------
	// ��ID�̃J�E���g
	// ----------------------------------------

	// ��J�n�ł���Ȃ��
	if (tk->stat == TAKUSTART){
		tk->kyoku_index = 0;
	}else{

	}

	// ----------------------------------------
	// �Ǐ�񏉊���
	// ----------------------------------------
	tk->KyokuInit();

	// ----------------------------------------
	// �ǂ̎Z�o
	// ----------------------------------------
	// ��
	tk->kyoku[tk->kyoku_index].kyoku = ( Get_hainum(gui->wk_str[tmp_wk_num+3] ) - 31 )*4 + // E(����)��S(���)�̕�����m�F
	                                  atoi(gui->wk_str[tmp_wk_num+7]) - 1;                 // �Ǐ��擾

	// ----------------------------------------
	// �Ǐ���`
	// ----------------------------------------

	// �{��
	tk->kyoku[tk->kyoku_index].tsumibo = atoi(gui->wk_str[tmp_wk_num+9]);

	// ���[�`�_
	tk->kyoku[tk->kyoku_index].riichbo = atoi(gui->wk_str[tmp_wk_num+11]);

	// �V�[�h�ԍ�
	tk->kyoku[tk->kyoku_index].seed_num = 0;

	// ----------------------------------------
	// ���_��`
	// ----------------------------------------
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){
		tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[tmp_pnum] = atoi(gui->wk_str[tmp_wk_num+15+tmp_pnum]);
	}

	// ----------------------------------------
	// �h����`
	// ----------------------------------------

	// �h���\���v
	tmp_dora_hai = Get_hainum(gui->wk_str[tmp_wk_num+5]);

	// �Ԕv�m�F
	if (tmp_dora_hai > 100){
		tmp_dora_hai = tmp_dora_hai - 100;
		tmp_dora_aka = true;
	}else{
		tmp_dora_aka = false;
	}

	// �h���\���v��`
	tk->kyoku[tk->kyoku_index].doracount     = 1;
	tk->kyoku[tk->kyoku_index].dora_actid[0] = 0;
	tk->kyoku[tk->kyoku_index].dora[0]       = tmp_dora_hai;
	tk->kyoku[tk->kyoku_index].dora_aka[0]   = tmp_dora_aka;

	// ----------------------------------------
	// �Ə��
	// ----------------------------------------
	tk->kyoku[tk->kyoku_index].kyoku_oya = atoi(gui->wk_str[tmp_wk_num+13]);
	tmp_ie_id                            = atoi(gui->wk_str[tmp_wk_num+13]);
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		tk->kyoku[tk->kyoku_index].ie[tmp_ie_id] = tmp_i;
		tmp_ie_id = (tmp_ie_id+1) % 4;
	}

	// ----------------------------------------
	// �z�v�ݒ�
	// ----------------------------------------

	// �z�v�ݒ�
	for(int tmp_pnum=0; tmp_pnum < 4; tmp_pnum++){

		// �z�v�|�C���^�[�ݒ�
		haipai_point=tmp_wk_num + 20 + TEHAI_MAX * tmp_pnum;

		for(int tmp_i=0; tmp_i < TEHAI_MAX; tmp_i++){

			// ----------------------------------------
			// �v���ݒ�
			// ----------------------------------------

			// �z�v�m�F
			now_tsumo_hai=Get_hainum(gui->wk_str[haipai_point+tmp_i]);

			// �Ԕv�m�F
			if (now_tsumo_hai > 100){
				now_tsumo_hai = now_tsumo_hai - 100;
				now_tsumo_aka = true;
			}else{
				now_tsumo_aka = false;
			}

			// ----------------------------------------
			// Tkinfo�N���X�z�v�ݒ�
			// ----------------------------------------

			// ��v�ǉ�
			tk->kyoku[tk->kyoku_index].tehai[tmp_pnum][now_tsumo_hai]++;

			// �Ԕv�ǉ�
			if(now_tsumo_aka == true){
				tk->kyoku[tk->kyoku_index].aka_count[tmp_pnum][(now_tsumo_hai-5)/10]++;
			}
		}
	}

	// ----------------------------------------
	// �A�N�V�������ݒ� - �z�v��
	// ----------------------------------------

	// ACT_ID�̐ݒ�
	tk->kyoku[tk->kyoku_index].act_count = 0;

	// ��`�ݒ�
	tk->kyoku[tk->kyoku_index].act_stat[0]  = HAIPAI;
	tk->kyoku[tk->kyoku_index].act_ply[0]   = 4;
	tk->kyoku[tk->kyoku_index].react_ply[0] = 4;
	tk->kyoku[tk->kyoku_index].act_hai[0]   = 0;

	// ----------------------------------------
	// �v���[���[��v���ݒ�
	// ----------------------------------------
	// ��v����
	for(int tmp_i=0; tmp_i < PLAYER_MAX; tmp_i++){
		tk->ply_act_tehaicount[tmp_i] = TEHAI_MAX;
	}

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = HAIPAI;

}

/* ---------------------------------------------------------------------------------------------- */
// 03:type_tsumo
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_tsumo(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// �A�N�V������`
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// ������
	int tmp_ply_id;

	// ��X�e�[�^�X�ݒ�
	tk->stat = PLYACTTSUMO;

	// ��Ԑݒ�
	tmp_ply_id = atoi(gui->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// �v���ݒ�
	// ----------------------------------------

	// ���̔v�m�F
	tk->ply_act_tsumo[tmp_ply_id] = Get_hainum(gui->wk_str[tmp_wk_num+5]);

	// �Ԕv�m�F
	if (tk->ply_act_tsumo[tmp_ply_id]  > 100){
		tk->ply_act_tsumo[tmp_ply_id]  = tk->ply_act_tsumo[tmp_ply_id]  - 100;
		tk->ply_act_tsumo_aka[tmp_ply_id] = true;
	}else{
		tk->ply_act_tsumo_aka[tmp_ply_id] = false;
	}

	// -----------------------------------------------------------
	// �A�N�V�����ݒ� - ���̏���
	// -----------------------------------------------------------
	tk->SetActInfo(tk->kyoku_index,
			PLYACTTSUMO,
			tmp_ply_id,
			4,
			tk->ply_act_tsumo[tmp_ply_id],
			tk->ply_act_tsumo_aka[tmp_ply_id]
	);

}

/* ---------------------------------------------------------------------------------------------- */
// 04:type_dahai
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_dahai(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// �A�N�V������`
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// ----------------------------------------
	// ������
	// ----------------------------------------
	int tmp_ply_id;

	// ��Ԑݒ�
	tmp_ply_id = atoi(gui->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�(dahai����)
	// ----------------------------------------
	if(strcmp(gui->wk_str[tmp_wk_num+7], "true") == 0 ){
			// ���̐؂�A�N�V����
			tk->stat = PLYACTTSUMOGIRI;
	// �̔v����
	}else{
		// ��O�̏������A�N�V�����̏ꍇ��
		if(tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTPON ||
		   tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTCHI ){
			// �v�A�N�V����
			tk->stat = PLYACTNAKISUTE;
		}else{
			// �̔v�A�N�V����
			tk->stat = PLYACTSUTE;
		}
	}

	// ----------------------------------------
	// �̔v��`
	// ----------------------------------------

	// �̔v�ݒ�
	tk->ply_act_sute[tmp_ply_id] = Get_hainum(gui->wk_str[tmp_wk_num+5]);

	// �Ԕv�m�F
	if ( tk->ply_act_sute[tmp_ply_id] > 100){
		 tk->ply_act_sute[tmp_ply_id] = tk->ply_act_sute[tmp_ply_id] - 100;
		 tk->ply_act_sute_aka[tmp_ply_id] = true;
	}else{
		 tk->ply_act_sute_aka[tmp_ply_id] = false;
	}

	// �f�o�O�p
	if ( tk->ply_act_sute[tmp_ply_id] > 37 || tk->ply_act_sute[tmp_ply_id] < 0){
		 tk->ply_act_sute[tmp_ply_id] = 0;
	}

	// -----------------------------------------------------------
	// �A�N�V�����ݒ�
	// -----------------------------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		tk->stat,
		tmp_ply_id,
		4,
		tk->ply_act_sute[tmp_ply_id],
		tk->ply_act_sute_aka[tmp_ply_id]
	);

}

/* ---------------------------------------------------------------------------------------------- */
// 05:type_ankan
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_ankan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_naki_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACT�v���[���[(target�v���[���[)�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_naki_seki  = atoi(gui->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// �J�J���v�m�F
	// ----------------------------------------

	// ��v�Ǎ�
	tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+5]);

	// �Ԕv�m�F
	if (tmp_naki_hai > 100){
		tmp_naki_hai = tmp_naki_hai - 100;
		tmp_naki_aka = true;
		// �Ԕv���Z
		tmp_aka_count++;
	}else{
		tmp_naki_aka = false;
	}

	// ----------------------------------------
	// �A�N�V�����ݒ� - �A���J��
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		PLYACTANKAN,
		tmp_naki_seki,
		4,
		tmp_naki_hai,
		tmp_naki_aka
	);

	// ----------------------------------------
	// �N�����ݒ� - �A���J��
	// ----------------------------------------
	tk->SetNakiInfo(tk->kyoku_index,                                                // ��INDEX
		ANKAN,                                                                      // �v���[���A�N�V����
		tmp_naki_seki,                                                              // ���v���[���[
		tk->kyoku[tk->kyoku_index].act_count,                                       // ACTID
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],   // ���v��`
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],   // ��INDEX�v��`
		tmp_aka_count);                                                             // �Ԕv����

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTANKAN;

}

/* ---------------------------------------------------------------------------------------------- */
// 06:type_kakan
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_kakan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_naki_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACT�v���[���[(target�v���[���[)�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_naki_seki  = atoi(gui->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// �J�J���v�m�F
	// ----------------------------------------

	// ��v�Ǎ�
	tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+5]);

	// �Ԕv�m�F
	if (tmp_naki_hai > 100){
		tmp_naki_hai = tmp_naki_hai - 100;
		tmp_naki_aka = true;
		// �Ԕv���Z
		tmp_aka_count++;
	}else{
		tmp_naki_aka = false;
	}

	// ----------------------------------------
	// �A�N�V�����ݒ� - �J�J��
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		PLYACTKAKAN,
		tmp_naki_seki,
		4,
		tmp_naki_hai,
		tmp_naki_aka
	);

	// ----------------------------------------
	// �N�����ݒ� - �J�J��
	// ----------------------------------------
	tk->SetNakiInfo(tk->kyoku_index, 
		KAKAN, 
		tmp_naki_seki,                                                              // ���v���[���[
		tk->kyoku[tk->kyoku_index].act_count,                                       // ACTID
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],   // ���v��`
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],   // ��INDEX�v��`
		tmp_aka_count);

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTKAKAN;

}

/* ---------------------------------------------------------------------------------------------- */
// 07:type_riichi
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_riichi(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// ������
	// ----------------------------------------
	int tmp_ply_id;

	// ----------------------------------------
	// REACT�v���[���[(target�v���[���[)�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);

	// -----------------------------------------------------------
	// �A�N�V�����ݒ� - ���[�`�錾
	// -----------------------------------------------------------
	tk->SetActInfo(tk->kyoku_index, // ��INDEX
		PLYACTRIICH,                // �A�N�V������� / ���[�`
		tmp_ply_id,                 // �A�N�V�����v���[��
		4,                          // ���A�N�V�����v���[��
		0,                          // �v�ԍ�
		false                       // �Ԕv
	);

}

/* ---------------------------------------------------------------------------------------------- */
// 08:set_type_reach_accepted
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_reach_accepted(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// ������
	// ----------------------------------------
	int tmp_ply_id;

	// ----------------------------------------
	// REACT�v���[���[(target�v���[���[)�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);

	// -----------------------------------------------------------
	// �A�N�V�����ݒ� - ���[�`�錾���
	// -----------------------------------------------------------
	tk->SetActInfo(tk->kyoku_index, // ��INDEX
		PLYRIICHACCEPTED,           // �A�N�V������� / ���[�`���
		4,                          // �A�N�V�����v���[��
		4,                          // ���A�N�V�����v���[��
		0,                          // �v�ԍ�
		false                       // �Ԕv
	);

}

/* ---------------------------------------------------------------------------------------------- */
// 08:set_type_pon
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_pon(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_naki_seki;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACT�v���[���[(target�v���[���[)�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_naki_seki  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_react_seki = atoi(gui->wk_str[tmp_wk_num+5]);

	// ----------------------------------------
	// �|���v�m�F(�̔v)
	// ----------------------------------------

	// ��v�Ǎ�
	tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+7]);

	// �Ԕv�m�F
	if (tmp_naki_hai > 100){
		tmp_naki_hai = tmp_naki_hai - 100;
		tmp_naki_aka = true;
		// �Ԕv���Z
		tmp_aka_count++;
	}else{
		tmp_naki_aka = false;
	}

	// ----------------------------------------
	// �|���v�m�F(1����)
	// ----------------------------------------


	// ----------------------------------------
	// �|���v�m�F(2����)
	// ----------------------------------------


	// ----------------------------------------
	// �A�N�V�����ݒ� - �|��
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		PLYACTPON,
		tmp_naki_seki,
		tmp_react_seki,
		tmp_naki_hai,
		tmp_naki_aka
	);

	// ----------------------------------------
	// �N�����ݒ� - �|��
	// ----------------------------------------
	tk->SetNakiInfo(tk->kyoku_index, 
		MINKO, 
		tmp_naki_seki,                            // ���v���[���[
		tk->kyoku[tk->kyoku_index].act_count,     // ACTID
		// tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // ���v��`
		// tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // ��INDEX�v��`
		tmp_naki_hai,                             // ���v��`
		tmp_naki_hai,                             // ��INDEX�v��`
		tmp_aka_count);

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTPON;

}

/* ---------------------------------------------------------------------------------------------- */
// 09:set_type_chi
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_chi(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_naki_seki;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	int tmp_naki_tehai_hai1 = 0;
	int tmp_naki_tehai_hai2 = 0;
	int tmp_hai = 0;
	int tmp_chi_idx = 0;

	// ----------------------------------------
	// REACT�v���[���[(target�v���[���[)�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_naki_seki  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_react_seki = atoi(gui->wk_str[tmp_wk_num+5]);

	// ----------------------------------------
	// �`�[�v�m�F(�̔v)
	// ----------------------------------------
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+7]);
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			tmp_naki_aka = true ;
			tmp_aka_count++;
		}

	// ----------------------------------------
	// �`�[�\���v(1����)
	// ----------------------------------------
		tmp_naki_tehai_hai1 = Get_hainum(gui->wk_str[tmp_wk_num+9]);
		if (tmp_naki_tehai_hai1 > 100){
			tmp_naki_tehai_hai1 = tmp_naki_tehai_hai1 - 100;
			tmp_aka_count++;
		}

	// ----------------------------------------
	// �`�[�\���v(2����)
	// ----------------------------------------
		tmp_naki_tehai_hai2 = Get_hainum(gui->wk_str[tmp_wk_num+10]);
		if (tmp_naki_tehai_hai2 > 100){
			tmp_naki_tehai_hai2 = tmp_naki_tehai_hai2 - 100;
			tmp_aka_count++;
		}

	// ----------------------------------------
	// �`�[INDEX�v�Z�o
	// ----------------------------------------

		// 1����2���ڂ̑召��r�E����
		if(tmp_naki_tehai_hai1 > tmp_naki_tehai_hai2){
			tmp_hai = tmp_naki_tehai_hai1;
			tmp_naki_tehai_hai1 = tmp_naki_tehai_hai2;
			tmp_naki_tehai_hai2 = tmp_hai;
		}

		// �`�[INDEX�v���Z�o
		if (tmp_naki_tehai_hai1 == tmp_naki_hai - 2 ){
			tmp_chi_idx = tmp_naki_tehai_hai1;
		}else if (tmp_naki_tehai_hai1 == tmp_naki_hai - 1 ){
			tmp_chi_idx = tmp_naki_tehai_hai1;
		}else if (tmp_naki_tehai_hai1 == tmp_naki_hai + 1 ){
			tmp_chi_idx = tmp_naki_hai;
		}else {
			tmp_chi_idx = 0;
		}

	// ----------------------------------------
	// �A�N�V�����ݒ� - �`�[
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		PLYACTCHI,
		tmp_naki_seki,
		tmp_react_seki,
		tmp_naki_hai,
		tmp_naki_aka
	);

	// ----------------------------------------
	// �N�����ݒ� - �`�[
	// ----------------------------------------
	tk->SetNakiInfo(tk->kyoku_index, 
		MINSHUN, 
		tmp_naki_seki,                            // ���v���[���[
		tk->kyoku[tk->kyoku_index].act_count,     // ACTID
		tmp_naki_hai,                             // ���v
		tmp_chi_idx,                              // ���vINDEX
		tmp_aka_count                             // �Ԕv���� 
	);

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTCHI;

}

/* ---------------------------------------------------------------------------------------------- */
// 10:set_type_minkan
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_minkan(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_naki_seki;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACT�v���[���[(target�v���[���[)�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_naki_seki  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_react_seki = atoi(gui->wk_str[tmp_wk_num+5]);

	// ----------------------------------------
	// �~���J���v�m�F(�̔v)
	// ----------------------------------------

	// ��v�Ǎ�
	tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+7]);

	// �Ԕv�m�F
	if (tmp_naki_hai > 100){
		tmp_naki_hai = tmp_naki_hai - 100;
		tmp_naki_aka = true;
		// �Ԕv���Z
		tmp_aka_count++;
	}else{
		tmp_naki_aka = false;
	}

	// ----------------------------------------
	// �~���J���v�m�F(1����)
	// ----------------------------------------

	// ----------------------------------------
	// �~���J���v�m�F(2����)
	// ----------------------------------------

	// ----------------------------------------
	// �~���J���v�m�F(3����)
	// ----------------------------------------


	// ----------------------------------------
	// �A�N�V�����ݒ� - �~���J��
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		PLYACTMINKAN,
		tmp_naki_seki,
		tmp_react_seki,
		tmp_naki_hai,
		tmp_naki_aka
	);

	// ----------------------------------------
	// �N�����ݒ� - �~���J��
	// ----------------------------------------
	tk->SetNakiInfo(tk->kyoku_index, 
		MINKAN, 
		tmp_naki_seki,                                                              // ���v���[���[
		tk->kyoku[tk->kyoku_index].act_count,                                       // ACTID
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // ���v��`
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // ��INDEX�v��`
		tmp_aka_count);

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTMINKAN;


}

/* ---------------------------------------------------------------------------------------------- */
// 95:type_dora
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_dora_open(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	int tmp_dora_hai;
	int tmp_dora_aka;

	// ----------------------------------------
	// �h����`
	// ----------------------------------------

	// �h���\���v
	tmp_dora_hai = Get_hainum(gui->wk_str[tmp_wk_num+3]);

	// �Ԕv�m�F
	if (tmp_dora_hai > 100){
		tmp_dora_hai = tmp_dora_hai - 100;
		tmp_dora_aka = true;
	}else{
		tmp_dora_aka = false;
	}

/*
	// ----------------------------------------
	// �A�N�V�����ݒ� - ���̎��h���\��
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		TSUMOKANDORAOPEN,
		4,
		4,
		tmp_dora_hai,
		tmp_dora_aka
	);
*/

	// �h���\���v��`
	tk->kyoku[tk->kyoku_index].dora_actid[tk->kyoku[tk->kyoku_index].doracount] = tk->kyoku[tk->kyoku_index].act_count;
	tk->kyoku[tk->kyoku_index].dora[tk->kyoku[tk->kyoku_index].doracount]       = tmp_dora_hai;
	tk->kyoku[tk->kyoku_index].dora_aka[tk->kyoku[tk->kyoku_index].doracount]   = tmp_dora_aka;
	tk->kyoku[tk->kyoku_index].doracount++;

}

/* ---------------------------------------------------------------------------------------------- */
// 96:type_hora
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_hora(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ������
	int tmp_agari_ply_id;
	int tmp_target_ply_id;
	int tmp_hai;
	int tmp_hai_aka;
	int tmp_tsumo_agari_flg;
	int tmp_dora_hai;
	int tmp_dora_aka;

	// ----------------------------------------
	// ���h���ݒ�
	// ----------------------------------------
	// ���h�����u+�v�łȂ��Ȃ�A�h�����擾
	if( strcmp(gui->wk_str[tmp_wk_num+12], "+"  ) != 0 ){
		// �h�����������擾
		for(int tmp_i = 0; tmp_i < tk->kyoku[tk->kyoku_index].doracount; tmp_i++){
			// ���h���Ǎ�
			tmp_dora_hai = Get_hainum(gui->wk_str[tmp_wk_num+12+tmp_i]);
			// �Ԕv�m�F
			if (tmp_dora_hai > 100){
				tmp_dora_hai = tmp_dora_hai - 100;
				tmp_dora_aka = true;
			}else{
				tmp_dora_aka = false;
			}
			// ���h���ݒ�
			tk->kyoku[tk->kyoku_index].uradora[tmp_i]       = tmp_dora_hai;
			tk->kyoku[tk->kyoku_index].uradora_aka[tmp_i]   = tmp_dora_aka;
			tk->kyoku[tk->kyoku_index].uradora_actid[tmp_i] = 0;
		}
	}

	// ----------------------------------------
	// �a�����擾
	// ----------------------------------------
	// �v���[���[ID�m�F
	tmp_agari_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_target_ply_id = atoi(gui->wk_str[tmp_wk_num+5]);

	// �A�N�V�����v�ݒ�
	tmp_hai     = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
	tmp_hai_aka = tk->kyoku[tk->kyoku_index].act_aka[tk->kyoku[tk->kyoku_index].act_count];

	// ----------------------------------------
	// �a�����ݒ�
	// ----------------------------------------

	// �a���t���O
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_flg  = false;

	// ��X�e�[�^�X�ݒ�(�a���v���[���[�ƃ^�[�Q�b�g�������Ȃ�Ύ��̘a���̐ݒ�)
	if ( tmp_agari_ply_id == tmp_target_ply_id ){
		// ���̘a���ݒ�
		tmp_target_ply_id = 4;
		tk->stat = PLYTSUMOAGARI;
		tmp_tsumo_agari_flg = true;
	}else{
		// �����a���ݒ�
		tk->stat = PLYACTRON;
		tmp_tsumo_agari_flg = false;
	}

	// �a���v���[���ݒ�
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_num    = tmp_agari_ply_id;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].furikomi_ply_num = tmp_target_ply_id;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_hai        = tmp_hai;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_aka        = tmp_hai_aka;

	// ----------------------------------------
	// �A�N�V�����ݒ� - �a���錾
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index, // ��INDEX
		tk->stat,                   // �A�N�V������� / �a���錾
		tmp_agari_ply_id,           // �A�N�V�����v���[��
		tmp_target_ply_id,          // ���A�N�V�����v���[��
		tmp_hai,                    // �v�ԍ�
		tmp_hai_aka                 // �Ԕv
	);

	// -----------------------------------------------------------
	// tk�N���X�̃A�N�V�������̍ŐV��
	// -----------------------------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// -----------------------------------------------------------
	// �a�����ݒ�
	// -----------------------------------------------------------

	// �a���`���m�F
	if( tk->shanten_normal[tmp_agari_ply_id] == -1 ){

		// �ʏ�`���̘a��
		tk->SetAgariInfo(tk->kyoku_index,
			AGARI_NORMAL,
			tmp_agari_ply_id,
			tmp_target_ply_id,
			tmp_tsumo_agari_flg,
			tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],
			tk->kyoku[tk->kyoku_index].act_aka[tk->kyoku[tk->kyoku_index].act_count]
		);

	}else if( tk->shanten_chitoi[tmp_agari_ply_id] == -1){

		// ���Ύq�`���̘a��
		tk->SetAgariInfo(tk->kyoku_index,
			AGARI_CHITOI,
			tmp_agari_ply_id,
			tmp_target_ply_id,
			tmp_tsumo_agari_flg,
			tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],
			tk->kyoku[tk->kyoku_index].act_aka[tk->kyoku[tk->kyoku_index].act_count]
		);

	}else if( tk->shanten_kokushi[tmp_agari_ply_id] == -1){

		// ���m�`���̘a��
		tk->SetAgariInfo(tk->kyoku_index,
			AGARI_KOKUSHI,
			tmp_agari_ply_id,
			tmp_target_ply_id,
			tmp_tsumo_agari_flg,
			tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count],
			tk->kyoku[tk->kyoku_index].act_aka[tk->kyoku[tk->kyoku_index].act_count]
		);

	}

	// ----------------------------------------
	// �Ǔ��_�̐ݒ�
	// ----------------------------------------
	for(int ply_i = 0; ply_i < 4; ply_i++){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[ply_i] = atoi(gui->wk_str[tmp_wk_num+7+ply_i]);
		tk->kyoku[tk->kyoku_index].ply_kyoku_end_score[ply_i] = tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[ply_i] + 
		                                                        tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[ply_i];
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 97:type_ryukyoku
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_ryukyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// �A�N�V�����ݒ� - �r��
	// ----------------------------------------
	tk->SetActInfo(tk->kyoku_index,
		RYUKYOKU,
		4,
		4,
		0,
		false
	);

	// -----------------------------------------------------------
	// tk�N���X�̃A�N�V�������̍ŐV��
	// -----------------------------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// -----------------------------------------------------------
	// �ǏI���ݒ�(�r�v)
	// -----------------------------------------------------------
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_flg  = true;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_stat = HOWANPAI;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount     = 0;

	// �Ǔ��_�̐ݒ�
	for(int ply_i = 0; ply_i < 4; ply_i++){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[ply_i] = atoi(gui->wk_str[tmp_wk_num+3+ply_i]);
		tk->kyoku[tk->kyoku_index].ply_kyoku_end_score[ply_i] = tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[ply_i] + 
		                                                        tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[ply_i];
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 98:type_endkyoku
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_endkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// �A�N�V�����ݒ� - �ǌ���(����)
	// ----------------------------------------
	if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == RYUKYOKU){

		// �A�N�V�����w��(�ǌ��� - ����)
		tk->SetActInfo(tk->kyoku_index,
			KYOKURESULT,
			4,
			4,
			0,
			false
		);

	// ----------------------------------------
	// �A�N�V�����ݒ� - �ǌ���(�_�u�������܂ޘa�����)
	// ----------------------------------------
	}else{

		// �A�N�V�����w��(�ǌ��� - �_�u�������܂ޘa�����)
		for(int tmp_disp_num = 0; tmp_disp_num < tk->kyoku[tk->kyoku_index].agari_ply_count; tmp_disp_num++){
			tk->SetActInfo(tk->kyoku_index,
				KYOKURESULT,
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tmp_disp_num].agari_ply_num,  // ���ʕ\������a���v���[����ݒ肷��
				4,
				0,
				false
			);
		}
	}

	// �A�N�V�����ԍ��̉��Z(�ŏI�l)
	tk->kyoku[tk->kyoku_index].act_count++;

	// ��ID�����Z
	tk->kyoku_index++;

}

/* ---------------------------------------------------------------------------------------------- */
// 99:type_endgame
/* ---------------------------------------------------------------------------------------------- */
void MJSReadMjai::set_type_endgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// �ŏI���_
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
		tk->plyEndscore[ply_i] = tk->kyoku[tk->kyoku_index-1].ply_kyoku_end_score[ply_i];
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �v�ԍ��擾
/* ---------------------------------------------------------------------------------------------- */
int MJSReadMjai::Get_hainum(char hai_str[]){

	char tmp_str[8];
	int  hainum;

	// ----------------------------------------
	// 1������
	// ----------------------------------------

	tmp_str[0] = hai_str[0];
	tmp_str[1] = '\0';

	// �������o(���p_�O����)
	if(      strcmp( tmp_str, "1" ) == 0){
		hainum = 1;
	}else if(strcmp( tmp_str, "2" ) == 0){
		hainum = 2;
	}else if(strcmp( tmp_str, "3" ) == 0){
		hainum = 3;
	}else if(strcmp( tmp_str, "4" ) == 0){
		hainum = 4;
	}else if(strcmp( tmp_str, "5" ) == 0){
		hainum = 5;
	}else if(strcmp( tmp_str, "6" ) == 0){
		hainum = 6;
	}else if(strcmp( tmp_str, "7" ) == 0){
		hainum = 7;
	}else if(strcmp( tmp_str, "8" ) == 0){
		hainum = 8;
	}else if(strcmp( tmp_str, "9" ) == 0){
		hainum = 9;
	}else if(strcmp( tmp_str, "E" ) == 0){
		hainum = 31;
	}else if(strcmp( tmp_str, "S" ) == 0){
		hainum = 32;
	}else if(strcmp( tmp_str, "W" ) == 0){
		hainum = 33;
	}else if(strcmp( tmp_str, "N" ) == 0){
		hainum = 34;
	}else if(strcmp( tmp_str, "P" ) == 0){
		hainum = 35;
	}else if(strcmp( tmp_str, "F" ) == 0){
		hainum = 36;
	}else if(strcmp( tmp_str, "C" ) == 0){
		hainum = 37;
	}else if(strcmp( tmp_str, "?" ) == 0){
		hainum = 0;
	}else{
		hainum = 0;
	}

	// ----------------------------------------
	// 2������
	// ----------------------------------------

	if( hai_str[1] != '\0'){	

		tmp_str[0] = hai_str[1];
		tmp_str[1] = '\0';

		if(      strcmp( tmp_str, "m" ) == 0){

		}else if(strcmp( tmp_str, "p" ) == 0){
			hainum = hainum + 10;
		}else if(strcmp( tmp_str, "s" ) == 0){
			hainum = hainum + 20;
		}else{

		}

	}

	// ----------------------------------------
	// 3������
	// ----------------------------------------

	if(( hai_str[1] != '\0' ) && ( hai_str[2] != '\0' )){

		tmp_str[0] = hai_str[2];
		tmp_str[1] = '\0';

		if( strcmp( tmp_str, "r" ) == 0){
			hainum = hainum + 100;
		}else{

		}

	}

	// ----------------------------------------
	// �Ԃ�l
	// ----------------------------------------
	return hainum;

}

/* ---------------------------------------------------------------------------------------------- 
 * �\�[�X�I��
 * ---------------------------------------------------------------------------------------------- */
