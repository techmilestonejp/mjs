/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F �����疃��(Ver0.1.2�F�J����)
 * �o�[�W����     �F 0.1.2.0.215(MJAI���O�\���F�{�^���\���C��)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F gui.cpp
 * �N���X��       �F MJSGui
 * �����T�v       �F GUI����N���X
 * Ver0.1.0�쐬�� �F 2022/05/03 18:50:06
 * �ŏI�X�V��     �F 2024/10/26 15:15:34
 * 
 * Copyright (c) 2010-2024 Techmilestone, All rights reserved.
 *  
 * ---------------------------------------------------------------------------------------------- */

#include "gui.h"

/* ---------------------------------------------------------------------------------------------- */
// ����������
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::GuiInit(){

	// -----------------------------
	// �ϐ���`
	// -----------------------------
	char cdir[192];

	// -----------------------------
	// ��Q�[�����[�h������
	// -----------------------------

	// ���O�o�̖͂�����
	tklog_output_flg     = false;
	clientlog_output_flg = false;

	// �J�����g�f�B���N�g�����擾
	GetCurrentDirectory(192,cdir);

	// �샍�O����`
	wsprintf(tklog_name, "%s\\mjslog.log", cdir);

	// �N���C�A���g���O����`
	wsprintf(clientlog_name, "%s\\mjai_client.log", cdir);

	// MJAI�v�����O����`
	// wsprintf(log_name_mjai, "C:\\Users\\era27\\source\\repos\\mjs0120_126\\Debug\\mjailog.json");
	// wsprintf(log_name_mjai, "mjailog.json");
	wsprintf(log_name_mjai, "%s\\mjailog.json", cdir);

	// �������v�����O����`
	// wsprintf(log_name_mjsocre, "C:\\Users\\era27\\source\\repos\\mjs0120_126\\Debug\\mjscore.txt");
	// wsprintf(log_name_mjsocre, "mjscore.txt");
	wsprintf(log_name_mjsocre, "%s\\mjscore.txt", cdir);

	// GUI���C���X�e�[�^�X
	gui_main_stat = GUI_NO_MAIN_STAT;
	gui_next_stat = GUI_NO_MAIN_STAT;

	// ��X�e�[�^�X�ϐ��̏�����
	guiTakuInit();

	// -----------------------------
	// �v���[�g������`
	// -----------------------------

	wsprintf(plt_name[PLT_RIICHI], "���[�`");
	wsprintf(plt_name[PLT_PON]   , "�|�@��");
	wsprintf(plt_name[PLT_KAN]   , "�J�@��");
	wsprintf(plt_name[PLT_CHI]   , "�`�@�[");
	wsprintf(plt_name[PLT_AGARI] , "�a�@��");
	wsprintf(plt_name[PLT_NEXT]  , "���@��");

	// -----------------------------
	// ��v���[�h�ݒ�
	// -----------------------------
	disp_tehai_mode         = DISP_TEHAI_MODE_DEF;          // ��\�����[�h
	disp_square_naki_mentsu = DISP_SQUARE_NAKI_MENTSU_DEF;  // ���v�\�����[�h

	// -----------------------------
	// ��v�ʒu�̐ݒ�
	// -----------------------------

	// ���C�i�[�\��
	if(disp_tehai_mode == 0){

		// ��v�ʒu��`
		tehai_x = SPACE_XSIZE;
		tehai_y = PLY_YSTART + PLY_YSIZE*HUM_PLY_SEKI_NUM + 40;

	// �X�N�G�A�\��
	}else if( disp_tehai_mode == 1 || disp_tehai_mode == 2 ){

		// UP�v���[���[��v�ʒu
		sutehai_up_x         = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3;
		sutehai_up_y         = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 - SUTEHAI_CENTERPLT_RANGE - HAI_YSIZE*4;
		tehai_up_x           = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*6; // ���̕������E�Ɉړ�����
		tehai_up_y           = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 - SUTEHAI_CENTERPLT_RANGE - HAI_YSIZE*4 - SUTEHAI_TEHAI_RANGE;
		nakihai_line_up_x    = tehai_up_x - NAKI_RANGE + HAI_XSIZE*TEHAI_MAX - HAI_XSIZE;
		nakihai_line_up_y    = tehai_up_y;
		nakihai_up_x         = 0;
		nakihai_up_y         = 0;

		// DOWN�v���[���[��v�ʒu
		sutehai_down_x       = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3;
		sutehai_down_y       = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 + HAI_XSIZE*3 + SUTEHAI_CENTERPLT_RANGE;
		tehai_x              = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*7;
		tehai_y              = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 + HAI_XSIZE*3 + SUTEHAI_CENTERPLT_RANGE + HAI_YSIZE*4 + SUTEHAI_TEHAI_RANGE;
		nakihai_line_down_x  = tehai_x + NAKI_RANGE;
		nakihai_line_down_y  = tehai_y;
		nakihai_down_x       = 0;
		nakihai_down_y       = 0;

		// LEFT�v���[���[��v�ʒu
		sutehai_left_x       = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3 - SUTEHAI_CENTERPLT_RANGE - HAI_YSIZE;
		sutehai_left_y       = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3;
		tehai_left_x         = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3 - SUTEHAI_CENTERPLT_RANGE - HAI_YSIZE*4 - SUTEHAI_TEHAI_RANGE - HAI_YSIZE;
		tehai_left_y         = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*8;
		nakihai_line_left_x  = tehai_left_x;
		nakihai_line_left_y  = tehai_left_x + NAKI_RANGE + HAI_XSIZE*4;
		nakihai_left_x       = 0;
		nakihai_left_y       = 0;

		// RIGHT�v���[���[��v�ʒu
		sutehai_right_x      = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 + HAI_XSIZE*3 + SUTEHAI_CENTERPLT_RANGE;
		sutehai_right_y      = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3;
		tehai_right_x        = (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 + HAI_XSIZE*3 + SUTEHAI_CENTERPLT_RANGE + HAI_YSIZE*4 + SUTEHAI_TEHAI_RANGE;
		tehai_right_y        = (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*7;
		nakihai_line_right_x = tehai_right_x;
		nakihai_line_right_y = tehai_right_y - NAKI_RANGE + HAI_XSIZE*TEHAI_MAX;
		nakihai_right_x      = 0;
		nakihai_right_y      = 0;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �I������
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::GuiPost(){

	// ��X�e�[�^�X�ϐ��̏�����
	guiTakuInit();

}

/* ---------------------------------------------------------------------------------------------- */
// �}�E�X���擾
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::MouseStat(){

    GetMousePoint( &msx, &msy );         // �}�E�X�̈ʒu�擾

    int MouseInput = GetMouseInput();    // �}�E�X�̉�������Ԏ擾

    for(int i = 0; i < 8; i++){          // �}�E�X�̃L�[�͍ő�8�܂Ŋm�F�o����

		Button[i] = 0;

        if( (MouseInput & 1<<i ) != 0 ){

			Button[i]++;   //������Ă�����J�E���g�A�b�v

		}else{

			Button[i] = 0; //������ĂȂ�������0
		}
	}

	wheelrotvol = GetMouseWheelRotVol() ;    //�z�C�[����]�ʎ擾

}

/* ---------------------------------------------------------------------------------------------- */
// �I�[�v�j���O��Ԋm�F
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::chk_opening(MJSTkinfo *tk){

	// -----------------------------
	// �}�E�X���擾
	// -----------------------------
	MouseStat();

	// -----------------------------
	// �}�E�X��������Ă��Ȃ��Ȃ�A�u�}�E�X�J�����(mouse_push_flg=0)�v�Ƃ���
	// -----------------------------
	if( Button[0] == 0 && Button[1] == 0 ){
		// �}�E�X�`�F�b�N�t���O������
		mouse_push_flg=0;
	}

	// -----------------------------
	// �}�E�X�������ꂽ�Ȃ�
	// -----------------------------
	if( Button[0] > 0 && mouse_push_flg == 0){

		// ----------------------------------------
		// 00:�ݒ�
		// ----------------------------------------
		if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START && msy<OPENING_BUT01_Y_START+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// �Q�[�����[�h�̕ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_SETTING_INIT;               // �r���[���[���[�h

		// ----------------------------------------
		// 01:�r���[���[���[�h�EMJAI���O
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*1 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*1+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// �Q�[�����[�h�̕ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_VIEWING_INIT;               // �r���[���[���[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 0;                                // ��Q�[��HUM���[�h�F0(COM�ΐ�)
			tk->tkgame_type = TKGAME_VIEWER;                     // �r���[�A���[�h
			gui_logtype = GUI_LOG_MJAILOG;                       // MJAI���O

		// ----------------------------------------
		// 02:�r���[���[���[�h�E���������O
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*2 && 
		    msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*2+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// �Q�[�����[�h�̕ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_VIEWING_INIT;               // �r���[���[���[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 0;                           // ��Q�[��HUM���[�h�F0(COM�ΐ�)
			tk->tkgame_type = TKGAME_VIEWER;                // �r���[�A���[�h
			gui_logtype = GUI_LOG_MJSCORE;                  // ���������O

		// ----------------------------------------
		// 03:4COM�Ό��E��Ǒΐ�E���̃e�[�u���Ǎ�
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*3 && 
		    msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*3+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ���C���X�e�[�^�X�ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_PLAYING_INIT;               // ��v���C���[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 0;                 // ��Q�[��HUM���[�h�F0(COM�ΐ�)
			tk->tkgame_type = TKGAME_1KYOKU;      // ��Q�[����ʁF��ǐ�
			tk->yama_setting_mode = 0;            // �v�R��ԁF�v�e�[�u���ǂݍ���

		// ----------------------------------------
		// 04:4COM�Ό��E�V�[�h�l�����_��
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*4 && 
		    msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*4+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ���C���X�e�[�^�X�ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_PLAYING_INIT;               // ��v���C���[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 0;                           // ��Q�[��HUM���[�h�F0(COM�ΐ�)
			tk->tkgame_type = TKGAME_TONPU;                 // ��Q�[����ʁF������
			tk->yama_setting_mode = 1;                      // �v�R��ԁF�V�[�h�l�w��

		// ----------------------------------------
		// 05:HUM�Ό��E��Ǒΐ�E���̃e�[�u���Ǎ�
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*5 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*5+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ���C���X�e�[�^�X�ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;          // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_PLAYING_INIT;          // ��v���C���[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 1;                      // ��Q�[��HUM���[�h�F1(HUM�ΐ�)
			tk->tkgame_type = TKGAME_1KYOKU;           // ��Q�[����ʁF��ǐ�
			tk->yama_setting_mode = 0;                 // �v�R��ԁF�v�e�[�u���ǂݍ���

		// ----------------------------------------
		// 06:HUM�Ό��E�V�[�h�l�Œ�
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*6 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*6+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ���C���X�e�[�^�X�ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;          // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_PLAYING_INIT;          // ��v���C���[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 1;                           // ��Q�[��HUM���[�h�F1(HUM�ΐ�)
			tk->tkgame_type = TKGAME_TONPU;                 // ��Q�[����ʁF������
			tk->yama_setting_mode = 2;                      // �v�R��ԁF�V�[�h�l�Œ�

		// ----------------------------------------
		// 07:HUM�Ό��E�V�[�h�l�����_��
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*7 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*7+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ���C���X�e�[�^�X�ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;          // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_PLAYING_INIT;          // ��v���C���[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 1;                           // ��Q�[��HUM���[�h�F1(HUM�ΐ�)
			tk->tkgame_type = TKGAME_TONPU;                 // ��Q�[����ʁF������
			tk->yama_setting_mode = 1;                      // �v�R��ԁF�V�[�h�l�w��

		// ----------------------------------------
		// 08:MJAI�N���C�A���g���[�h(GUI���[�h)
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*8 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*8+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ���C���X�e�[�^�X�ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_CLIENT_INIT;                // �N���C�A���g���[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 1;                 // ��Q�[��HUM���[�h�F1(HUM�ΐ�)

		// ----------------------------------------
		// 09:MJAI�N���C�A���g���[�h(PLY���[�h)
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		          msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*9 && 
		          msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*9+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// ���C���X�e�[�^�X�ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_CLIENT_INIT;                // �N���C�A���g���[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 0;                      // ��Q�[��HUM���[�h�F0(COM�ΐ�)

		// ----------------------------------------
		// 10:���؃��[�h�EACTID_MAX
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*10 && 
			msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*10+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// �Q�[�����[�h�̕ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_RUNNING_INIT;               // ���؃��[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 0;                                // ��Q�[��HUM���[�h�F0(COM�ΐ�)
			tk->tkgame_type = TKGAME_MAXID_TEST;
			tk->yama_setting_mode = 1;                           // �v�R��ԁF�V�[�h�l�w��

		// ----------------------------------------
		// 11:���؃��[�h�E������
		// ----------------------------------------
		}else if( msx>OPENING_BUT01_X_START && msx<OPENING_BUT01_X_START+BUT_ICON_XSIZE && 
		    msy>OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*11 && 
		    msy<OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*11+BUT_ICON_YSIZE ){

			// ----------------------------------------
			// �Q�[�����[�h�̕ύX
			// ----------------------------------------
			gui_main_stat = GUI_OPENING_POST;               // �I�[�v�j���O�㏈��
			gui_next_stat = GUI_RUNNING_INIT;               // ���؃��[�h

			// ----------------------------------------
			// �e�N���X�̕ϐ���`
			// ----------------------------------------
			tk->ply_hum_mode = 0;                           // ��Q�[��HUM���[�h�F0(COM�ΐ�)
			tk->tkgame_type = TKGAME_TONPU;                 // ��Q�[����ʁF������
			tk->yama_setting_mode = 1;                      // �v�R��ԁF�V�[�h�l�w��

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �쏈��(�Q�[�����[�h)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTakuInit(){

	// -----------------------------
	// GUI������
	// -----------------------------

	// �}�E�X��񏉊���
	MouseStat();
	mouse_push_flg = 0;
	Button[0] = 0;
	Button[1] = 0;

	// �t���[���J�E���g
	frame_count = 0;

	// -----------------------------
	// �v���[�g������`
	// -----------------------------

	// HUM�A�N�V�����v���[�g
	plt_mode[PLT_RIICHI] = false;
	plt_mode[PLT_PON]    = false;
	plt_mode[PLT_KAN]    = false;
	plt_mode[PLT_CHI]    = false;
	plt_mode[PLT_AGARI]  = false;
	plt_mode[PLT_NEXT]   = true;
	// plt_mode[PLT_NEXT]   = false;

	// �L/���t���O
	plt_nakiari_flg = true;

	// -----------------------------
	// �{�^�������t���O������
	// -----------------------------
	act_push_flg = false;               // �}�E�X�����t���O
	but_push_flg = false;               // �{�^�������t���O

	// -----------------------------
	// ��X�e�[�^�X������
	// -----------------------------

	// GUI���[�h�ݒ�
	gui_taku_mode = COMMON_PLAY_MODE;   // �ʏ탂�[�h
	gui_ply_tehai_mode = TEHAI_NORMAL;  // ��v�\�����[�h

	// �����(�ÞȁE����)
	naki_ankan_hai_count = 0;           // �ÞȔv����
	naki_kakan_hai_count = 0;           // ���Ȕv����

	// �����
	chihai_count = 0;
	for(int tmp_i = 0; tmp_i < CHI_KOHO_COUNT_MAX; tmp_i++){
		chihai_mode[tmp_i]   = false;
		chi_idx_hai[tmp_i]   = 0; 
		chi_aka_count[tmp_i] = 0;
	}

	// �̔v�s�e�[�u��
	cannot_sutehai_count = 0;

	// �r���[�A�[���[�h
	gui_kyoku_index = 0;
	gui_actid = 0;

	// �N���C�A���g���[�h
	cli_mode = GUI_MJAI_NOTCONNECT;

	// ���i��v�\���v���[��ID
	disp_down_tehai_pnum = HUM_PLY_SEKI_NUM;

}

/* ---------------------------------------------------------------------------------------------- */
// ��I��(�Q�[�����[�h)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTakuPost(){

}

/* ---------------------------------------------------------------------------------------------- */
// �쏈��(�Q�[�����[�h)�E�ʏ���
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTaku(MJSTkinfo *tk){

	// ��X�e�[�^�X���Ƃ̏����ω�
	if(tk->stat == KYOKUSTART){
		// GUI������
		guiTakuInit();
	}

	// �l�Ȃ�A���A�N�V�����̊m�F(�v���[�g��Ԋm�F)
	if( tk->ply_hum_mode == 1){

		// �N���b�N�O����
		guiTakuChkPreClick(tk);

	}

	// �N���b�N�㏈��
	guiTakuActClick(tk);

}

/* ---------------------------------------------------------------------------------------------- */
// �N���b�N�O����(���C��)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTakuChkPreClick(MJSTkinfo *tk){

		// -----------------------------
		// �����̔Ԃł���΁A���̎��A�N�V�����m�F
		// -----------------------------
		if(tk->ply_turn == HUM_PLY_SEKI_NUM){

			// �����Ԃ̍ŏI�A�N�V����������(�����V����)�Ȃ�A���̌�A�N�V�����̊m�F
			if( ( tk->stat == PLYACTSUTEWAIT) &&
			    ( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTTSUMO  ||
			      tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYRINSHAN   )
			){

				// �v���[���[�̎��̎��A�N�V�����m�F
				guiChkPlyTsumoStat(tk);

			}

		// -----------------------------
		// ����̔Ԃł���΁A�����A�N�V�����m�F
		// -----------------------------
		}else{

			// �O�v���[���[�̃A�N�V�����v�̊m�F
			if( ( tk->stat == PLYACTNAKIWAIT) &&
				( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTSUTE      ||
			      tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTTSUMOGIRI ||
			      tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTNAKISUTE  ) 
			  ){

				// �����m�F
				guiChkPlyRonStat(tk);

				// ���v�m�F
				// ���L���t���O��true(���L)
				// �� ���[�`���[�h�̎��ɂ͖��m�F�̓X�L�b�v����
				// if( gui_ply_tehai_mode != TEHAI_RIICHI_YUKO && gui_ply_tehai_mode != TEHAI_CHI_SELECT){
				if( ( plt_nakiari_flg == true ) &&
				    ( gui_ply_tehai_mode != TEHAI_RIICHI_YUKO && gui_ply_tehai_mode != TEHAI_CHI_SELECT )
				){

					// HUM�v���[���̖v�m�F(�`�[�A�|���A����)
					guiChkPlyNakiStat(tk);

				}

			// �̔v�A�N�V�����łȂ��Ȃ�A�v���[�g�͖�����
			}else{

				// �u������v���[�g�v�̖�����
				plt_mode[PLT_CHI]   = false;
				plt_mode[PLT_PON]   = false;
				plt_mode[PLT_KAN]   = false;
				plt_mode[PLT_AGARI] = false;
				// plt_mode[PLT_NEXT]  = false;

			}

		}

}

/* ---------------------------------------------------------------------------------------------- */
// �v���[���[�̎��̏�Ԋm�F
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiChkPlyTsumoStat(MJSTkinfo *tk){

	// -----------------------------
	// �ÞȊm�F
	// -----------------------------

	// ������
	naki_ankan_hai_count = 0;

	// �ÞȊm�F
	for(int tmp_i = 0; tmp_i < PAI_MAX; tmp_i++){

		// tmp_i�����̔v�Ȃ�
		if ( ( tmp_i == tk->ply_act_tsumo[HUM_PLY_SEKI_NUM] && tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_i] == 3) ||
		     ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_i] == 4) ){

			// �J���������Z
			naki_ankan_hai[naki_ankan_hai_count] = tmp_i;
			naki_ankan_hai_count++;
		}
	}

	// �c���0����
	for(int tmp_i = naki_ankan_hai_count; tmp_i < 3; tmp_i++){
		// �c��0����
		naki_ankan_hai[tmp_i] = 0;
	}

	// -----------------------------
	// ���Ȋm�F
	// -----------------------------

	// ������
	naki_kakan_hai_count=0;

	// ���Ȋm�F
	for(int tmp_i = 0; tmp_i < tk->kyoku[tk->kyoku_index].naki_count[HUM_PLY_SEKI_NUM]; tmp_i++){

		// ���Ȕv�Ȃ��
		if( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tk->kyoku[tk->kyoku_index].naki_hai[HUM_PLY_SEKI_NUM][tmp_i]] > 0 &&
		    tk->kyoku[tk->kyoku_index].naki_stat[HUM_PLY_SEKI_NUM][tmp_i] == MINKO ){

			// ���Ȍ������Z
			naki_kakan_hai[naki_kakan_hai_count] = tk->kyoku[tk->kyoku_index].naki_hai[HUM_PLY_SEKI_NUM][tmp_i];
			naki_kakan_hai_count++;

		}
	}

	// �c���0����
	for(int tmp_i = naki_kakan_hai_count; tmp_i < 3; tmp_i++){

		// �c��0����
		naki_kakan_hai[tmp_i] = 0;

	}

	// -----------------------------
	// �ÞȖ��͉��ȂȂ�A�ȃv���[�g�L����
	// -----------------------------
	if( ( naki_ankan_hai_count > 0 || naki_kakan_hai_count > 0 ) && 
	    gui_ply_tehai_mode == TEHAI_NORMAL){
		// �v���[�g�L����
		plt_mode[PLT_KAN] = true;
	}else{
		// �v���[�g������
		plt_mode[PLT_KAN] = false;
	}

	// -----------------------------
	// �ʑO�Ńe���p�C�ȉ��̃V�����e���Ȃ�A���[�`�v���[�g�L����
	// -----------------------------
	if(tk->shanten_total[HUM_PLY_SEKI_NUM] <= 0 && 
	   tk->kyoku[tk->kyoku_index].naki_count[HUM_PLY_SEKI_NUM] - tk->kyoku[tk->kyoku_index].ankan_count[HUM_PLY_SEKI_NUM] == 0 && // �ÞȈȊO�̖��Ȃ�
	   gui_ply_tehai_mode == TEHAI_NORMAL){
		// �v���[�g�L����
		plt_mode[PLT_RIICHI] = true;
	}else{
		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
	}

	// -----------------------------
	// ���̘a���Ȃ�A�a���v���[�g�L����
	// -----------------------------
	if( (tk->shanten_total[HUM_PLY_SEKI_NUM] == -1) && (gui_ply_tehai_mode == TEHAI_NORMAL || gui_ply_tehai_mode == TEHAI_RIICHI_YUKO) ){
		// �v���[�g�L����
		plt_mode[PLT_AGARI] = true;
	}else{
		// �v���[�g������
		plt_mode[PLT_AGARI] = false;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// HUM�v���[���̃����m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiChkPlyRonStat(MJSTkinfo *tk){

	// ���O��`
	int tmp_sute_hai;
	int tmp_sute_ply;

	// -----------------------------
	// ���v���[���̎̔v��`
	// -----------------------------
	tmp_sute_hai = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
	tmp_sute_ply = tk->kyoku[tk->kyoku_index].act_ply[tk->kyoku[tk->kyoku_index].act_count];

	// -----------------------------
	// �a���v���[�g�̖�����
	// -----------------------------
	plt_mode[PLT_AGARI] = false;

	// -----------------------------
	// �Ҕv�m�F
	// -----------------------------
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[HUM_PLY_SEKI_NUM]; tmp_i++){

		// �����Ȃ�(�҂��q�X�g�O�����ƈ�v����̂��H)
		if( tk->ply_act_machi_hai[HUM_PLY_SEKI_NUM][tmp_i] == tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count]){

			// �v���[�g�L����
			plt_mode[PLT_AGARI] = true;
			plt_mode[PLT_NEXT]  = true;

			// �̔v���F
			if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) || 
			     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5)
			   ){
				tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
			}

			break;

		}else{
			// �v���[�g������
			plt_mode[PLT_AGARI] = false;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// HUM�v���[���̖v�m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiChkPlyNakiStat(MJSTkinfo *tk){

	// ���O��`
	int tmp_sute_hai;
	int tmp_sute_ply;
	chihai_count = 0;

	// -----------------------------
	// ���v���[���̎̔v��`
	// -----------------------------
	tmp_sute_hai = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
	tmp_sute_ply = tk->kyoku[tk->kyoku_index].act_ply[tk->kyoku[tk->kyoku_index].act_count];

	// -----------------------------
	// �|���m�F
	// -----------------------------
	if ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai] > 1){

		// �v���[�g�L����
		plt_mode[PLT_PON]   = true;
		plt_mode[PLT_NEXT]  = true;

		// ���v��`
		// tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = tmp_sute_hai;

		// �̔v���F
		if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) || // �ʏ�̔v�̏ꍇ
		     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5) ){ // ���[�`�錾���̎̔v�̏ꍇ
			// �̔v�𒅐F
			tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
		}

	}

	// -----------------------------
	// ���Ȋm�F
	// -----------------------------
	if ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai] > 2){

		// �v���[�g�L����
		plt_mode[PLT_KAN]   = true;
		plt_mode[PLT_NEXT]  = true;

		// ���v��`
		// tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = tmp_sute_hai;
		// tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

		// �̔v���F
		if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) ||      // �ʏ�̔v�̏ꍇ
		     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5) ){      // ���[�`�錾���̎̔v�̏ꍇ

			// �̔v�𒅐F
			tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
		}

	}

	// -----------------------------
	// �`�[�m�F(���v��1����)
	// -----------------------------
	if ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai+1] > 0 && 
         tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai+2] > 0 &&
		 tmp_sute_ply == HUM_PLY_SEKI_NUM - 1 &&
		 tmp_sute_hai > 0 &&
		 tmp_sute_hai < 30 ){

		// �v���[�g�L����
		plt_mode[PLT_CHI]   = true;
		plt_mode[PLT_NEXT]  = true;

		// ���v��`(GUI�N���X)
		chihai_count ++;    // �`�[��␔+1
		chihai_mode[0] = true;
		chi_idx_hai[0] = tmp_sute_hai;

		chi_hai_num1[0] = tmp_sute_hai+1;
		chi_hai_num2[0] = tmp_sute_hai+2;

		// �Ԕv�����m�F(�u3�v-4-5�̃p�^�[��)
		if( tmp_sute_hai == 3        && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[0] = 1;
		}else if( tmp_sute_hai == 13 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[0] = 1;
		}else if( tmp_sute_hai == 23 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[0] = 1;

		// �Ԕv�����m�F(�u4�v-5-6�̃p�^�[��)
		}else if( tmp_sute_hai ==  4 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[0] = 1;
		}else if( tmp_sute_hai == 14 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[0] = 1;
		}else if( tmp_sute_hai == 24 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[0] = 1;
		}else{
		 chi_aka_count[0] = 0;
		}

		// �̔v���F
		if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) || 
		     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5)
		   ){
			tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
		}

	}else{

		// ���v��`(GUI�N���X)
		chihai_mode[0] = false;

	}

	// -----------------------------
	// �`�[�m�F(���v��2����)
	// -----------------------------
	if ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai-1] > 0 && 
	     tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai+1] > 0 &&
		 tmp_sute_ply == HUM_PLY_SEKI_NUM - 1 &&
                 tmp_sute_hai > 1 &&
		         tmp_sute_hai < 30 ){

		// �v���[�g�L����
		plt_mode[PLT_CHI]   = true;
		plt_mode[PLT_NEXT]  = true;

		// ���v��`(GUI�N���X)
		chihai_count ++;    // �`�[��␔+1
		chihai_mode[1] = true;
		chi_idx_hai[1] = tmp_sute_hai-1;

		chi_hai_num1[1] = tmp_sute_hai-1;
		chi_hai_num2[1] = tmp_sute_hai+1;

		// �Ԕv�����m�F(3-�u4�v-5�̃p�^�[��)
		if( tmp_sute_hai == 4        && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[1] = 1;
		}else if( tmp_sute_hai == 14 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[1] = 1;
		}else if( tmp_sute_hai == 24 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[1] = 1;

		// �Ԕv�����m�F(5-�u6�v-7�̃p�^�[��)
		}else if( tmp_sute_hai ==  6 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[1] = 1;
		}else if( tmp_sute_hai == 16 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[1] = 1;
		}else if( tmp_sute_hai == 26 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[1] = 1;

		}else{
		 chi_aka_count[1] = 0;
		}

		// �̔v���F
		if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) || 
		     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5)
		   ){
			tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
		}

	}else{

		// ���v��`(GUI�N���X)
		chihai_mode[1] = false;

	}

	// -----------------------------
	// �`�[�m�F(���v��3����)
	// -----------------------------
	if ( tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai-2] > 0 && 
	     tk->ply_act_tehai[HUM_PLY_SEKI_NUM][tmp_sute_hai-1] > 0 &&
		 tmp_sute_ply == HUM_PLY_SEKI_NUM - 1 &&
	     tmp_sute_hai > 2 &&
	     tmp_sute_hai < 30 ){

		// �v���[�g�L����
		plt_mode[PLT_CHI]   = true;
		plt_mode[PLT_NEXT]  = true;

		// ���v��`(GUI�N���X)
		chihai_count ++;    // �`�[��␔+1
		chihai_mode[2] = true;
		chi_idx_hai[2] = tmp_sute_hai-2;

		chi_hai_num1[2] = tmp_sute_hai-2;
		chi_hai_num2[2] = tmp_sute_hai-1;

		// �Ԕv�����m�F(4-5-�u6�v�̃p�^�[��)
		if( tmp_sute_hai == 6        && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[2] = 1;
		}else if( tmp_sute_hai == 16 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[2] = 1;
		}else if( tmp_sute_hai == 26 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[2] = 1;

		// �Ԕv�����m�F(5-6-�u7�v�̃p�^�[��)
		}else if( tmp_sute_hai ==  7 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
		 chi_aka_count[2] = 1;
		}else if( tmp_sute_hai == 17 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
		 chi_aka_count[2] = 1;
		}else if( tmp_sute_hai == 27 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
		 chi_aka_count[2] = 1;

		}else{
		 chi_aka_count[2] = 0;
		}

		// �̔v���F
		if ( ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 0) || 
		     ( tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] == 5)
		   ){
			tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] = tk->ply_act_kawa_mode[tmp_sute_ply][tk->ply_act_kawa_count[tmp_sute_ply]-1] + HAI_COLOR_NUM_BLUE;
		}

	}else{

		// ���v��`(GUI�N���X)
		chihai_mode[2] = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �N���b�N�㏈��(���C��)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTakuActClick(MJSTkinfo *tk){

	// �}�E�X���擾
	MouseStat();

	// ----------------------------------------
	// �}�E�X�J��
	// ----------------------------------------

	// �}�E�X��������Ă��Ȃ��Ȃ�A�u�}�E�X�J�����(mouse_push_flg=0)�v�Ƃ���
	if( Button[0]==0 && Button[1]==0 ){

		// �}�E�X�`�F�b�N�t���O������
		mouse_push_flg = 0;

		// �N���b�N�m�F�t���O������
		act_push_flg = false;

	}

	// ----------------------------------------
	// �{�^���������ꂽ�ꍇ�̏���
	// ----------------------------------------

	// �}�E�X�������ꂽ���A�t���[�������߂����Ȃ�A
//	if( (Button[0] > 0 && mouse_push_flg == 0) || ( frame_count > AUTO_FRAME_COUNT_PLAYING) ){
	if(  Button[0] > 0 && mouse_push_flg == 0){

		// �t���[��������
		frame_count = 0;

		// �}�E�X�`�F�b�N�t���O�L����
		mouse_push_flg = 1;
	
		// ----------------------------------------
		// ���C�������F�X�e�[�^�X���Ƃ̃p�[�c�\��
		// ----------------------------------------

		// ----------------------------------------
		// ��J�n
		// ----------------------------------------
		if( tk->stat == TAKUSTART){

		// ----------------------------------------
		// �ꌈ��
		// ----------------------------------------
		}else if(tk->stat == BAGIME){

			// �u���ցv�v���[�g��������Ă���ꍇ�ɂ�
			// if( msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT && 
			//    msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT + PLT_ICON_XSIZE &&
			//    msy > PLT_Y_STAT && 
			//    msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

				//�v�b�V���t���O�L��
				act_push_flg = true;

			// }

		// ----------------------------------------
		// �ǌ��ʕ\��
		// ----------------------------------------
		}else if(tk->stat == KYOKURESULT){

			// ���փv���[�g�L����
			plt_mode[PLT_NEXT]  = true;

			// �\�������͖���
			guiKyokuEnd(tk);

		// ----------------------------------------
		// �쌋�ʕ\��
		// ----------------------------------------
		}else if(tk->stat == TAKURESULT){

			// ���փv���[�g�L����
			plt_mode[PLT_NEXT]  = true;

			// �\�������͖���
			guiTakuEnd(tk);

		// ----------------------------------------
		// ���̎��̃A�N�V�����҂�
		// ----------------------------------------
		}else if(tk->stat == PLYACTSUTEWAIT){

			// GUI�X�e�[�^�X���ʏ�̏ꍇ
			if( gui_taku_mode == COMMON_PLAY_MODE){

				// �{�^���m�F
				chk_but(tk);
				set_plt_naki_arinashi();

				// �{�^����������ĂȂ��Ȃ�
				if(but_push_flg == false){

					// �l�Ȃ�v���[�g��Ԋm�F
					if( tk->ply_hum_mode == 1 && tk->ply_turn == HUM_PLY_SEKI_NUM){
						// �ʏ��Ԋm�F
						guiSetPlyNormalActMain(tk);
					}else{
						// �N���b�N�t���O�L����
						act_push_flg = true;
					}

				}

			// GUI�X�e�[�^�X���ʏ�ȊO�̏ꍇ
			}else{
				// �{�^���m�F
				chk_but(tk);
				set_plt_naki_arinashi();
			}

		// ----------------------------------------
		// HUM�v���[���̖��҂�
		// ----------------------------------------
		}else if(tk->stat == PLYACTNAKIWAIT){

			// GUI�X�e�[�^�X���ʏ�̏ꍇ
			if( gui_taku_mode == COMMON_PLAY_MODE){

				// �{�^���m�F
				chk_but(tk);
				set_plt_naki_arinashi();

				// �{�^����������ĂȂ��Ȃ�
				if(but_push_flg == false){
					// HUM�v���[���̖��҂�
					guiSetPlyNakiActMain(tk);
				}

			// GUI�X�e�[�^�X���ʏ�ȊO�̏ꍇ
			}else{
				// �{�^���m�F
				chk_but(tk);
				set_plt_naki_arinashi();
			}

		// ----------------------------------------
		// ���̔v�҂�
		// ----------------------------------------
		}else if(tk->stat == PLYACTNAKISUTEWAIT){

			// GUI�X�e�[�^�X���ʏ�̏ꍇ
			if( gui_taku_mode == COMMON_PLAY_MODE){

				// �{�^���m�F
				chk_but(tk);
				set_plt_naki_arinashi();

				// �{�^����������ĂȂ��Ȃ�
				if(but_push_flg == false){

					// �l�Ȃ�v���[�g��Ԋm�F
					if( tk->ply_hum_mode == 1 && tk->ply_turn == HUM_PLY_SEKI_NUM){
						// ���̔v�҂�
						guiSetPlyNakiSuteAct(tk);
					}else{
						// �N���b�N�t���O�L����
						act_push_flg = true;
					}

				}

			// GUI�X�e�[�^�X���ʏ�ȊO�̏ꍇ
			}else{
				// �{�^���m�F
				chk_but(tk);
				set_plt_naki_arinashi();
			}

		// ----------------------------------------
		// �W������(���̑�����)
		// ----------------------------------------
		}else{

			// GUI�X�e�[�^�X���ʏ�̏ꍇ
			if( gui_taku_mode == COMMON_PLAY_MODE){

				// �{�^���m�F
				chk_but(tk);
				set_plt_naki_arinashi();

				// �{�^����������ĂȂ��Ȃ�
				if(but_push_flg == false){
					// �N���b�N�t���O�L����
					act_push_flg = true;
				}

			// GUI�X�e�[�^�X���ʏ�ȊO�̏ꍇ
			}else{
				// �{�^���m�F
				chk_but(tk);
				set_plt_naki_arinashi();
			}

		} // tk->stat�̏�������

	// ----------------------------------------
	// �}�E�X��������Ă��Ȃ��Ȃ�A�t���[�����J�E���g�A�b�v
	// ----------------------------------------
	}else{

			//�t���[���J�E���g
			frame_count++;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 1.GUI����ʏ폈���i���C���j
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyNormalActMain(MJSTkinfo *tk){

	// �v���[���[�ʏ�A�N�V������`(mode:TEHAI_NORMAL)
	if( gui_ply_tehai_mode == TEHAI_NORMAL ){
		guiSetPlyNormalAct(tk);
	// ���[�`�錾��̎̔v�I��(mode:TEHAI_RIICHI_SUTEHAI)
	}else if( gui_ply_tehai_mode == TEHAI_RIICHI_SUTEHAI ){
		guiSetPlyRiichiSutehaiAct(tk);
	// ���[�`�L����̃A�N�V����(���̐؂�A���̘a���A�Þ�)(mode:TEHAI_RIICHI_YUKO)
	}else if( gui_ply_tehai_mode == TEHAI_RIICHI_YUKO ){
		guiSetPlyRiichiYukoAct(tk);
	// �v���[���[�ÞȃA�N�V������`(mode:TEHAI_ANKAN_KAKAN_SELECT)
	}else if( gui_ply_tehai_mode == TEHAI_ANKAN_KAKAN_SELECT ){
		guiSetPlyAnkanKakanAct(tk);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// 1-1.GUI����ʏ폈���E�v���[���[�ʏ�A�N�V������`(mode:TEHAI_NORMAL)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyNormalAct(MJSTkinfo *tk){

	// ----------------------------------------
	// ��v���̎̔v����
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE+HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// ��v�e�[�u���N���b�N�t���O�L�����ƃA�N�V������`
		tk->ply_act = ACTSUTE;

		// �̔v�ԍ��ݒ�(�}�E�X�I���ʒu)
		tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ���̔v�̎̔v����
	// ----------------------------------------
	}else if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
			  msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE && 
			  msy > tehai_y && 
			  msy < tehai_y + HAI_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// �e�[�u���N���b�N�t���O�L����
		tk->ply_act = ACTTSUMOGIRI;

		// �̔v�ԍ��ݒ�
		tk->ply_tbl_hum_sutehai_statnum = tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; // ���̔v

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �ȃv���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �ÞȔv�Ȃ��
		if ( naki_ankan_hai_count == 1 && naki_kakan_hai_count == 0 ){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];

		// ���Ȕv�Ȃ��
		}else if( naki_ankan_hai_count == 0 && naki_kakan_hai_count == 1 ){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTKAKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[0];

			// ���Ȕv���Ԕv�Ȃ��
			if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
			}

		// ���v����������ꍇ�ɂ�
		}else{

			// ----------------------------------------
			// GUI��v���[�h�̕ύX
			// ----------------------------------------
			gui_ply_tehai_mode = TEHAI_ANKAN_KAKAN_SELECT;

/*
			// ----------------------------------------
			// �ÞȔv�Ȃ��
			// ----------------------------------------
			if ( naki_ankan_hai_count > 0){
				// HUM�v���[���[�̃A�N�V������`
				tk->ply_act = ACTANKAN;
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];
			}

			// ----------------------------------------
			// ���Ȕv�Ȃ��
			// ----------------------------------------
			if ( naki_kakan_hai_count > 0){

				// HUM�v���[���[�̃A�N�V������`
				tk->ply_act = ACTKAKAN;
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[0];

				// ���Ȕv���Ԕv�Ȃ��
				if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
					tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
				}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
					tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
				}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
					tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
				}else{
					tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
				}
			}
*/

		}

		// ----------------------------------------
		// �v���[�g������
		// ----------------------------------------
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ���[�`�v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_RIICHI] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_RIICHI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_RIICHI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̃A�N�V������`
		tk->ply_act = ACTRIICH;

		// GUI��v���[�h�̕ύX
		gui_ply_tehai_mode = TEHAI_RIICHI_SUTEHAI;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �a���v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̃A�N�V������`
		tk->ply_act = ACTTSUMOAGARI;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ���̏ꏊ�������ꂽ�ꍇ�́A�N���b�N�t���O�𖳌�������
	// ----------------------------------------
	}else{

		// �N���b�N�t���O������
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 1-2.GUI����ʏ폈���E���[�`�錾��̎̔v�I��(mode:TEHAI_RIICHI_SUTEHAI)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyRiichiSutehaiAct(MJSTkinfo *tk){

	// ----------------------------------------
	// ��v���̎̔v����
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// ���[�`���̑I���̔v�̃V�����e����0�ł���Ȃ�
		if(tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == true){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// ��v�e�[�u���N���b�N�t���O�L�����ƃA�N�V������`
			tk->ply_act = ACTSUTE;

			// �̔v�ԍ��ݒ�(�}�E�X�I���ʒu)
			tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;

			// GUI��v���[�h�̕ύX
			gui_ply_tehai_mode = TEHAI_RIICHI_YUKO;

		}

	// ----------------------------------------
	// ���̔v�ŃN���b�N�����Ȃ�̔v���`����
	// ----------------------------------------
	}else if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
			  msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE &&
			  msy > tehai_y && 
			  msy < tehai_y + HAI_YSIZE ){

		// ���[�`���̑I���̔v�̃V�����e����0�ł���Ȃ�
		if( tk->ply_act_tsumo_can_sute[HUM_PLY_SEKI_NUM] == true ){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// �e�[�u���N���b�N�t���O�L����
			tk->ply_act = ACTTSUMOGIRI;

			// �̔v�ԍ��ݒ�
			tk->ply_tbl_hum_sutehai_statnum = (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]); // ���̔v

			// GUI��v���[�h�̕ύX
			gui_ply_tehai_mode = TEHAI_RIICHI_YUKO;

		}
	}
}

/* ---------------------------------------------------------------------------------------------- */
// 1-3.GUI����ʏ폈���E���[�`�L����̃A�N�V����(���̐؂�A���̘a���A�Þ�)(mode:TEHAI_RIICHI_YUKO)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyRiichiYukoAct(MJSTkinfo *tk){

	// ----------------------------------------
	// ���̔v�ŃN���b�N�����Ȃ�̔v���`����
	// ----------------------------------------
	if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
		msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE &&
		msy > tehai_y && 
		msy < tehai_y + HAI_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// �e�[�u���N���b�N�t���O�L����
		tk->ply_act = ACTTSUMOGIRI;

		// �̔v�ԍ��ݒ�
		tk->ply_tbl_hum_sutehai_statnum = tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; // ���̔v

	// ----------------------------------------
	// �ȃv���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// �ÞȔv�Ȃ��
		if ( naki_ankan_hai_count > 0){
			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];
		}

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

		// GUI��v���[�h�̕ύX
		// gui_ply_tehai_mode = TEHAI_ANKAN_KAKAN_SELECT;

	// ----------------------------------------
	// �a���v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// ��v�e�[�u���N���b�N�t���O�L�����ƃA�N�V������`
		tk->ply_act = ACTTSUMOAGARI;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ���̏ꏊ�������ꂽ�ꍇ�́A�N���b�N�t���O�𖳌�������
	// ----------------------------------------
	}else{

		// �N���b�N�t���O������
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 1-4.GUI����ʏ폈���E�v���[���[�ÞȃA�N�V������`(mode:TEHAI_ANKAN_KAKAN_SELECT)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyAnkanKakanAct(MJSTkinfo *tk){

	// ----------------------------------------
	// �Ȕv�̑I��
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// �ÞȔv0�Ȃ�
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_ankan_hai[0]){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];

			// GUI��v���[�h�̕ύX
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

		// �ÞȔv1�Ȃ�
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_ankan_hai[1]){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[1];

			// GUI��v���[�h�̕ύX
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

		// �ÞȔv2�Ȃ�
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_ankan_hai[2]){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[2];

			// GUI��v���[�h�̕ύX
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

		// ���Ȕv0�Ȃ�
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_kakan_hai[0]){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTKAKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[0];

			// ���Ȕv���Ԕv�Ȃ��
			if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
			}

			// GUI��v���[�h�̕ύX
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

		// ���Ȕv1�Ȃ�
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_kakan_hai[1]){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTKAKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[1];

			// ���Ȕv���Ԕv�Ȃ��
			if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
			}

			// GUI��v���[�h�̕ύX
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

		// ���Ȕv2�Ȃ�
		if( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == naki_kakan_hai[2]){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTKAKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[2];

			// ���Ȕv���Ԕv�Ȃ��
			if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
			}

			// GUI��v���[�h�̕ύX
			gui_ply_tehai_mode = TEHAI_NORMAL;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 2.GUI����ʏ폈���E�v���[���[�ʖ��m�F(���C��)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyNakiActMain(MJSTkinfo *tk){

	// ----------------------------------------
	// ��Ԃ������ł���Ȃ�A�u���Ȃ��v�A�N�V����
	// ----------------------------------------
	if( tk->ply_turn == HUM_PLY_SEKI_NUM){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// �A�N�V������`�F���Ȃ�
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

	// ----------------------------------------
	// ��Ԃ����v���[���̏ꍇ
	// ----------------------------------------
	}else{

		// -----------------------
		// �u�ʏ탂�[�h�v�u���[�`�ヂ�[�h�v�̃A�N�V��������
		// -----------------------
		if( gui_ply_tehai_mode == TEHAI_NORMAL || gui_ply_tehai_mode == TEHAI_RIICHI_YUKO){

			// HUM�Ŗ��A�N�V�����ł��Ȃ��ꍇ(NONAKI�̐ݒ�)
			if( plt_mode[PLT_PON]   == false && 
		        plt_mode[PLT_KAN]   == false && 
		        plt_mode[PLT_CHI]   == false && 
		        plt_mode[PLT_AGARI] == false){

				// �N���b�N�t���O�L����
				act_push_flg = true;

				// �A�N�V������`�F���Ȃ�
				tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

			// HUM�Ŗ��A�N�V�����\�ȏꍇ
			}else{
				guiSetPlyNakiAct(tk);
			}

		// -----------------------
		// �u�`�[�v�I�����[�h�v�̃A�N�V������`
		// -----------------------
		}else if( gui_ply_tehai_mode == TEHAI_CHI_SELECT){
			guiSetPlyChiPaiAct(tk);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 2-1.GUI����ʏ폈���E�v���[���[�ʖ��A�N�V������`(mode:TEHAI_NORMAL || mode:TEHAI_RIICHI_YUKO)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyNakiAct(MJSTkinfo *tk){

	// ----------------------------------------
	// ���փv���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	if( msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT && 
	          msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT + PLT_ICON_XSIZE &&
	          msy > PLT_Y_STAT && 
	          msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̖��A�N�V������`
		tk->ply_act_naki[HUM_PLY_SEKI_NUM]       = ACTNONAKI;
		tk->ply_naki_hai[HUM_PLY_SEKI_NUM]       = 0;
		tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = 0;
		tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �a���v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
	      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
	      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
	      msy > PLT_Y_STAT && 
	      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̖��A�N�V������`
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTRON;
		tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
		tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];

		// �Ԕv��`
		tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �|���v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_PON] == true &&
	      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_PON && 
	      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_PON + PLT_ICON_XSIZE &&
	      msy > PLT_Y_STAT && 
	      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̖��A�N�V������`
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTPON;
		tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
		tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];

		// �Ԕv��`
		if( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] ==  5 || 
		    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 || 
		    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 ){

			if ( tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tk->ply_naki_idx[HUM_PLY_SEKI_NUM]-5)/10] > 2){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 2;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tk->ply_naki_idx[HUM_PLY_SEKI_NUM]-5)/10];
			}

		}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
		}

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �ȃv���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
	      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
	      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
	      msy > PLT_Y_STAT && 
	      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̖��A�N�V������`
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTMINKAN;
		tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
		tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
		tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �`�[�v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_CHI] == true &&
	      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_CHI && 
	      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_CHI + PLT_ICON_XSIZE &&
	      msy > PLT_Y_STAT && 
	      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �`�[���v��2���ȏ�ł���΁A�v�I���������s��
		if (chihai_count > 1){

			// ���[�h�ύX
			gui_ply_tehai_mode = TEHAI_CHI_SELECT;

		// �`�[���v��1���ł���΁A�����`�[����
		}else{

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̖��A�N�V������`
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTCHI;

			// �`�[INDEX�v��`(0)
			if (chihai_mode[0]== true){

				// �`�[�v��`(0)
				tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = chi_idx_hai[0];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[0];

			// �`�[INDEX�v��`(1)
			}else if (chihai_mode[1]== true){

				// �`�[�v��`(1)
				tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = chi_idx_hai[1];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[1];

			// �`�[INDEX�v��`(2)
			}else if (chihai_mode[2]== true){

				// �`�[�v��`(2)
				tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count];
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = chi_idx_hai[2];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[2];

			// �`�[INDEX�v��`(��O����)
			}else{

			}

		}

		// �`�[����������
		chihai_count = 0;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ����ȊO�̏����͖�����
	// ----------------------------------------
	}else{

		// �N���b�N�t���O������
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 2-2.GUI����ʏ폈���E�v���[���[�`�[�v�A�N�V������`(mode:TEHAI_CHI_SELECT)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyChiPaiAct(MJSTkinfo *tk){

	// �ϐ���`
	int tmp_chi_idx;

	// ----------------------------------------
	// �`�[�v�̑I��
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// �v�ԍ��ݒ�
		tmp_chi_idx = (msx-tehai_x) / HAI_XSIZE;

		// �`�[�A�N�V�����ݒ�
		if ( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[0] || 
		     tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[1] || 
		     tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[2] ){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̖��A�N�V������`
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTCHI;

			// ��v���[�h�ύX
			gui_ply_tehai_mode = TEHAI_NORMAL;

			// �`�[INDEX�v��`
			if ( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[0]){
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = chi_idx_hai[0];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[0];
			}

			// �`�[INDEX�v��`
			if ( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[1]){
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = chi_idx_hai[1];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[1];
			}

			// �`�[INDEX�v��`
			if ( tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_chi_idx] == chi_hai_num1[2]){
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = chi_idx_hai[2];
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[2];
			}

			// �`�[����������
			chihai_count = 0;

			// �Ԕv����
			// tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

			// �v���[�g������
			plt_mode[PLT_PON]    = false;
			plt_mode[PLT_KAN]    = false;
			plt_mode[PLT_CHI]    = false;
			plt_mode[PLT_AGARI]  = false;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 3.GUI����ʏ폈���E�v���[���[����̎̔v����
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetPlyNakiSuteAct(MJSTkinfo *tk){

	// ----------------------------------------
	// ��v���̎̔v����
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̃A�N�V������`
		tk->ply_act = ACTNAKISUTE;

		// �̔v�ԍ��ݒ�(�}�E�X�I���ʒu)
		tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;

		// HUM�v���[���[�̖��A�N�V������`
		tk->ply_act_naki[HUM_PLY_SEKI_NUM]       = ACTNONAKI;
		tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = 0;
		tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// (�f�o�O�p)ply����ʑ���
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiPlyDetailInfo(MJSTkinfo *tk){

	// ----------------------------------------
	// BUT04�������ꂽ�Ȃ�
	// ----------------------------------------

	if( msx > THINFO_BUT_X_STAT && 
		msx < THINFO_BUT_X_STAT + 32 &&
		msy > BUT02_Y_STAT && 
		msy < BUT02_Y_STAT + 32 ){

		// (�f�o�O�p)�N���b�N�t���O������(�v���[�g�������ꂽ�ꍇ�͏��false)
		act_push_flg = false;

	}
}

/* ---------------------------------------------------------------------------------------------- */
// �쏈��(�Q�[���[���[�h)�E�ǏI��
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiKyokuEnd(MJSTkinfo *tk){

	// ----------------------------------------
	// ���փv���[�g�������ꂽ��
	// ----------------------------------------

/*	if( ( msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLTSTATNUM_NEXT && 
		msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLTSTATNUM_NEXT + PLT_ICON_XSIZE &&
		msy > PLT_Y_STAT && 
		msy < PLT_Y_STAT + PLT_ICON_YSIZE ) || ( frame_count > AUTO_PUSH_FRAME_COUNT ) ){*/

		// �N���b�N�t���O�L����
		act_push_flg = true;

//	}

}

/* ---------------------------------------------------------------------------------------------- */
// �쏈��(�Q�[���[���[�h)�E��I��
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiTakuEnd(MJSTkinfo *tk){

	// ----------------------------------------
	// ���փv���[�g�������ꂽ��
	// ----------------------------------------

/*	if( ( msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLTSTATNUM_NEXT && 
		msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLTSTATNUM_NEXT + PLT_ICON_XSIZE &&
		msy > PLT_Y_STAT && 
		msy < PLT_Y_STAT + PLT_ICON_YSIZE ) || ( frame_count > AUTO_PUSH_FRAME_COUNT) ){*/

		// �N���b�N�t���O�L����
		act_push_flg = true;

//	}

}

/* ---------------------------------------------------------------------------------------------- */
// �r���[���[���[�h�̏�����
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiViewerInitTaku(MJSTkinfo *tk){

	// �Ǐ�񏉊���
	tk->KyokuInit();

	// ������
	gui_kyoku_index = 0;
	gui_actid = 0;

	// ���i��v�\���v���[��ID
	disp_down_tehai_pnum = 0;

	// tk�N���X�̃A�N�V�������̍ŐV��
	tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	// GUI���[�h�ݒ�
	gui_taku_mode = COMMON_PLAY_MODE;                   // ��X�e�[�^�X���[�h�F�ʏ탂�[�h

	// �얼��`
	wsprintf(tk->tkname, "%s", "�r���[�A���[�h�v��");

}

/* ---------------------------------------------------------------------------------------------- */
// �쏈��(�r���[�A�[���[�h)�E���C��
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiViewerTaku(MJSTkinfo *tk){

	// �}�E�X���擾
	MouseStat();

	// ----------------------------------------
	// �}�E�X�J��
	// ----------------------------------------

	// �}�E�X��������Ă��Ȃ��Ȃ�A�u�}�E�X�J�����(mouse_push_flg=0)�v�Ƃ���
	if( Button[0] == 0 && Button[1] == 0 ){
		mouse_push_flg = 0;
	}

	// ----------------------------------------
	// �{�^���������ꂽ�ꍇ�̏���
	// ----------------------------------------

	// �}�E�X�������ꂽ�Ȃ�
	if( Button[0] > 0 && mouse_push_flg == 0){

		// �}�E�X�`�F�b�N�t���O�L����
		mouse_push_flg=1;

		// �I���{�^���m�F
		chk_but(tk);

		// �I���{�^���ȊO�̏���
		if(gui_taku_mode != COMMON_END_CHECK_MODE){
			count_plyact(tk);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �쏈��(�r���[�A�[���[�h)�F�ǁEACTID�̃J�E���g
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::count_plyact(MJSTkinfo *tk){

	// ----------------------------------------
	// ��INDEX
	// ----------------------------------------

	// ��ID�E�J�E���g�_�E��
	if( msx > KYOID_X_STAT && msx < KYOID_X_STAT + BUT_ICON_XSIZE && 
		msy > ACTID_Y_STAT && msy < ACTID_Y_STAT + BUT_ICON_YSIZE && gui_kyoku_index > 0){

		// �\�����[�h�ύX
		gui_taku_mode = COMMON_PLAY_MODE;

		// ��ID�ύX
		gui_kyoku_index--;
		gui_actid = 0;

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	// ��ID�E�J�E���g�A�b�v
	}else if( msx>KYOID_X_STAT+BUT_ICON_XSIZE && msx<KYOID_X_STAT+BUT_ICON_XSIZE*2 && 
		      msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && gui_kyoku_index < tk->kyoku_index-1){

		// �\�����[�h�ύX
		gui_taku_mode = COMMON_PLAY_MODE;

		// ��ID�ύX
		gui_kyoku_index++;
		gui_actid = 0;

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ----------------------------------------
	// �A�N�V�����ԍ�
	// ----------------------------------------

	// ActID�E�J�E���g�_�E��MIN
	if( msx>ACTID_X_STAT && msx<ACTID_X_STAT+BUT_ICON_XSIZE && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE){

		// �\�����[�h�ύX
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID�ύX
		gui_actid = 0;

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ActID�E�J�E���g�_�E��-4
	if( msx>ACTID_X_STAT+BUT_ICON_XSIZE*1 && msx<ACTID_X_STAT+BUT_ICON_XSIZE*2 && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && gui_actid >= 4){

		// �\�����[�h�ύX
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID�ύX
		gui_actid=gui_actid-4;

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ActID�E�J�E���g�_�E��-1
	if( msx>ACTID_X_STAT+BUT_ICON_XSIZE*2 && msx<ACTID_X_STAT+BUT_ICON_XSIZE*3 && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && gui_actid > 0){

		// �\�����[�h�ύX
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID�ύX
		gui_actid--;

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ActID�E�J�E���g�A�b�v+1
	if( msx>ACTID_X_STAT+BUT_ICON_XSIZE*3 && msx<ACTID_X_STAT+BUT_ICON_XSIZE*4 && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && gui_actid < tk->kyoku[gui_kyoku_index].act_count-1){

		// �\�����[�h�ύX
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID�ύX
		gui_actid++;

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ActID�E�J�E���g�A�b�v+4
	if( msx>ACTID_X_STAT+BUT_ICON_XSIZE*4 && msx<ACTID_X_STAT+BUT_ICON_XSIZE*5 && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && Button[0]>0 && gui_actid < tk->kyoku[gui_kyoku_index].act_count-1-4){

		// �\�����[�h�ύX
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID�ύX
		gui_actid=gui_actid+4;

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ActID�E�J�E���g�A�b�vMAX
	if( msx>ACTID_X_STAT+BUT_ICON_XSIZE*5 && msx<ACTID_X_STAT+BUT_ICON_XSIZE*6 && 
		msy>ACTID_Y_STAT && msy<ACTID_Y_STAT+BUT_ICON_YSIZE && Button[0]>0){

		// �\�����[�h�ύX
		gui_taku_mode = COMMON_PLAY_MODE;

		// ActID�ύX
		gui_actid=tk->kyoku[gui_kyoku_index].act_count-1;

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(gui_kyoku_index, gui_actid);

	}

	// ----------------------------------------
	// �ꌈ�߃{�^��
	// ----------------------------------------
	if( msx>BAGIME_X_STAT && msx<BAGIME_X_STAT+BUT_ICON_XSIZE && 
		msy>BAGIME_Y_STAT && msy<BAGIME_Y_STAT+BUT_ICON_YSIZE && Button[0]>0){

		// �r���[�\�����[�h�ύX
		if( gui_taku_mode != COMMON_BAGIME_MODE){
			gui_taku_mode = COMMON_BAGIME_MODE;
		}else{
			gui_taku_mode = COMMON_PLAY_MODE;
		}

	}

	// ----------------------------------------
	// �쌋�ʃ{�^��
	// ----------------------------------------
	if( msx>TKEND_X_STAT && msx<TKEND_X_STAT+BUT_ICON_XSIZE && 
		msy>BAGIME_Y_STAT && msy<BAGIME_Y_STAT+BUT_ICON_YSIZE && Button[0]>0){

		// �r���[�\�����[�h�ύX
		if( gui_taku_mode != COMMON_TAKURESULT_MODE){
			gui_taku_mode = COMMON_TAKURESULT_MODE;
		}else{
			gui_taku_mode = COMMON_PLAY_MODE;
		}

	}

	// ----------------------------------------
	// �ȕύX�ԍ�
	// ----------------------------------------
	// �Ȕԍ�-1
	if( msx>VIEWER_SEKI_X_STAT && msx<VIEWER_SEKI_X_STAT+BUT_ICON_XSIZE*1 && 
		msy>VIEWER_SEKI_Y_STAT && msy<VIEWER_SEKI_Y_STAT+BUT_ICON_YSIZE && Button[0]>0){

		// �\���Ȕԍ��̕ύX
		disp_down_tehai_pnum = (disp_down_tehai_pnum + 3) % 4;

	// �Ȕԍ�+1
	}else if( msx>VIEWER_SEKI_X_STAT + BUT_ICON_XSIZE*1 && msx<VIEWER_SEKI_X_STAT+BUT_ICON_XSIZE*2 && 
		msy>VIEWER_SEKI_Y_STAT                    && msy<VIEWER_SEKI_Y_STAT+BUT_ICON_YSIZE && Button[0]>0){

		// �\���Ȕԍ��̕ύX
		disp_down_tehai_pnum = (disp_down_tehai_pnum + 1) % 4;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���؃��[�h�E������
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiRunningInit(){

	// GUI���[�h������
	guiTakuInit();

}

/* ---------------------------------------------------------------------------------------------- */
// ���؃��[�h�E���C��
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiRunningMain(MJSTkinfo *tk){

	// �}�E�X���擾
	MouseStat();

	// ----------------------------------------
	// �}�E�X�J��
	// ----------------------------------------

	// �}�E�X��������Ă��Ȃ��Ȃ�A�u�}�E�X�J�����(mouse_push_flg=0)�v�Ƃ���
	if( Button[0]==0 && Button[1]==0 ){

		// �}�E�X�`�F�b�N�t���O������
		mouse_push_flg = 0;

		// �N���b�N�m�F�t���O������
		act_push_flg = false;

	}

	// �N���b�N����Ă���Ȃ�
	if(  Button[0] > 0 && mouse_push_flg == 0){

		// �{�^���m�F
		chk_but(tk);

		// �}�E�X�`�F�b�N�t���O�L����
		mouse_push_flg = 1;

	}

	// ----------------------------------------
	// ���C������
	// ----------------------------------------

	// �t���[�������ߐ��m�F
	if( frame_count > AUTO_FRAME_COUNT_RUNNING ){

		// �I���{�^���łȂ��Ȃ�
		if( gui_taku_mode != COMMON_END_CHECK_MODE && gui_taku_mode != COMMON_END_MODE){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// �t���[��������
			frame_count = 0;

		}else{

			// �N���b�N�m�F�t���O������
			act_push_flg = false;

		}

	}else{

		// �t���[���J�E���g
		frame_count++;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �N���C�A���g���[�h�E������
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientInit(MJSTkinfo *tk){

	// GUI���[�h������
	guiTakuInit();

}

/* ---------------------------------------------------------------------------------------------- */
// �N���C�A���g���[�h�E���C������
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientMain(MJSTkinfo *tk){

	// �}�E�X���擾
	MouseStat();

	// ----------------------------------------
	// �}�E�X�̃{�^�����J������Ă���Ȃ��
	// ----------------------------------------

	// �}�E�X��������Ă��Ȃ��Ȃ�A�u�}�E�X�J�����(mouse_push_flg=0)�v�Ƃ���
	if( Button[0]==0 && Button[1]==0 ){

		// �}�E�X�`�F�b�N�t���O������
		mouse_push_flg = 0;

		// �N���b�N�m�F�t���O������
		act_push_flg = false;

	}

	// ----------------------------------------
	// �N���C�A���g���[�h���Ƃ̏����F�ʏ�샂�[�h
	// ----------------------------------------
	if( cli_mode == GUI_MJAI_WAIT_TAKU_PLYACT){

		// -------------------------------
		// ���̃A�N�V�����҂���Ԃł����
		// -------------------------------
		if( tk->stat == PLYACTTSUMO   || 
		    tk->stat == PLYRINSHAN    || 
		    tk->stat == PLYACTRIICH   ){ 

			// GUI���[�h�̏ꍇ
			if( tk->ply_hum_mode == 1 && tk->ply_turn == HUM_PLY_SEKI_NUM ){

				// ���[�`�ヂ�[�h�Ńv���[�g���L�����łȂ��Ȃ�A�I�[�g���̏���
				if( ( gui_ply_tehai_mode == TEHAI_RIICHI_YUKO ) &&
				    ( plt_mode[PLT_KAN] == false && plt_mode[PLT_AGARI] == false ) ){

						// �t���[�������N���b�N����(AUTO_FRAME_COUNT_RESULT�����҂�����)
						auto_frame_click_riichi(tk, 30);

				// ����ȊO�̓N���b�N�m�F
				}else{

					// �{�^���̉����m�F
					if(  Button[0] > 0 && mouse_push_flg == 0){

						// �}�E�X�`�F�b�N�t���O�L����
						mouse_push_flg = 1;

						// �{�^���m�F
						chk_but(tk);
						set_plt_naki_arinashi();

						// ���̎�����
						guiClientSetPlyNormalActMain(tk);

					}

				}

			// PLY�A�N�V��������COM����̏ꍇ
			}else{

				// �{�^���̉����m�F
				if( Button[0] > 0 && mouse_push_flg == 0){

					// �}�E�X�`�F�b�N�t���O�L����
					mouse_push_flg = 1;

					// �{�^���m�F
					chk_but(tk);
					// set_plt_naki_arinashi();

				}

				// �t���[�������N���b�N����
				auto_frame_click(AUTO_FRAME_COUNT_CLIENT);
			}

		// -------------------------------
		// �̔v�A�N�V���������m�F
		// -------------------------------
		}else if( ( tk->stat == PLYACTSUTE      || 
		            tk->stat == PLYACTTSUMOGIRI ||
		            tk->stat == PLYACTNAKISUTE  ) && 
		          ( tk->ply_turn != HUM_PLY_SEKI_NUM) ){

			// GUI���[�h�̏ꍇ
			if( tk->ply_hum_mode == 1){

				// �����\�Ȃ��
				if ( plt_mode[PLT_PON]   == true ||
				     plt_mode[PLT_KAN]   == true ||
				     plt_mode[PLT_CHI]   == true ||
				     plt_mode[PLT_AGARI] == true ){

					// �{�^���̉����m�F
					if(  Button[0] > 0 && mouse_push_flg == 0){

						// �}�E�X�`�F�b�N�t���O�L����
						mouse_push_flg = 1;

						// �{�^���m�F
						chk_but(tk);
						set_plt_naki_arinashi();

						// ���m�F
						guiClientSetPlyNakiAct(tk);

					}

				// �����s�Ȃ��
				}else{

					// �{�^���̉����m�F
					if( Button[0] > 0 && mouse_push_flg == 0){

						// �}�E�X�`�F�b�N�t���O�L����
						mouse_push_flg = 1;

						// �{�^���m�F
						chk_but(tk);
						set_plt_naki_arinashi();

					}

					// �t���[�������N���b�N����
					auto_frame_click(AUTO_FRAME_COUNT_CLIENT);
				}

			// PLY�A�N�V��������COM����̏ꍇ
			}else{

				// �{�^���̉����m�F
				if( Button[0] > 0 && mouse_push_flg == 0){

					// �}�E�X�`�F�b�N�t���O�L����
					mouse_push_flg = 1;

					// �{�^���m�F
					chk_but(tk);
					// set_plt_naki_arinashi();

				}

				// �t���[�������N���b�N����
				auto_frame_click(AUTO_FRAME_COUNT_CLIENT);

			}

		// -------------------------------
		// ���̔v����(���v���[��)
		// -------------------------------
		}else if( tk->stat == PLYACTPON  || 
		          tk->stat == PLYACTCHI  ){

			// GUI����̏ꍇ
			if( tk->ply_hum_mode == 1 && tk->ply_turn == HUM_PLY_SEKI_NUM ){

				// �{�^���̉����m�F
				if( Button[0] > 0 && mouse_push_flg == 0 ){

					// �}�E�X�`�F�b�N�t���O�L����
					mouse_push_flg = 1;

					// �{�^���m�F
					chk_but(tk);
					set_plt_naki_arinashi();

					// ���̔v������
					guiClienSetPlyNakiSuteAct(tk);
				}

			// PLY�A�N�V��������COM����̏ꍇ
			}else{
				// �t���[�������N���b�N����
				auto_frame_click(AUTO_FRAME_COUNT_CLIENT);
			}

		// -------------------------------
		// �a���E���ꏈ���̏ꍇ
		// -------------------------------
		}else if( tk->stat == PLYACTRON  || 
		          tk->stat == PLYTSUMOAGARI ||
		          tk->stat == RYUKYOKU  ){

			// GUI���[�h�̏ꍇ
			if ( tk->ply_hum_mode == 1){

				// �{�^���̉����m�F
				if(  Button[0] > 0 && mouse_push_flg == 0){

					// �}�E�X�`�F�b�N�t���O�L����
					mouse_push_flg = 1;

					// �{�^���m�F
					chk_but(tk);
					set_plt_naki_arinashi();

					// ���փ{�^���̊m�F
					set_plt_next();  

				}

			// PLY���[�h�̏ꍇ
			}else{
				// �t���[�������N���b�N����(AUTO_FRAME_COUNT_RESULT�����҂�����)
				auto_frame_click(AUTO_FRAME_COUNT_RESULT);
			}

		// -------------------------------
		// ����ȊO�ł����
		// -------------------------------
		}else{

			// �{�^���̉����m�F
			if( Button[0] > 0 && mouse_push_flg == 0){

				// �}�E�X�`�F�b�N�t���O�L����
				mouse_push_flg = 1;

				// �{�^���m�F
				chk_but(tk);
				set_plt_naki_arinashi();

			}

			// �t���[�������N���b�N����
			auto_frame_click(AUTO_FRAME_COUNT_CLIENT);
		}

	// ----------------------------------------
	// ��ʑJ�ڑ҂��̏ꍇ
	// ----------------------------------------
	}else if( cli_mode == GUI_MJAI_BAGIME       || 
	          cli_mode == GUI_MJAI_KYOKUEND     ||
	          cli_mode == GUI_MJAI_TAKURESULT   ||
	          cli_mode == GUI_MJAI_ERR_CONNECT  ||
	          cli_mode == GUI_MJAI_ERR_RES_MES  ){

		// GUI���[�h�̏ꍇ
		if ( tk->ply_hum_mode == 1){

			// �{�^���̉����m�F
			if(  Button[0] > 0 && mouse_push_flg == 0){

				// �}�E�X�`�F�b�N�t���O�L����
				mouse_push_flg = 1;

				// �{�^���m�F
				chk_but(tk);
				// set_plt_naki_arinashi();

				// ���փ{�^���̊m�F
				set_plt_next();  

			}

		// PLY���[�h�̏ꍇ
		}else{

			// �{�^���̉����m�F
			if(  Button[0] > 0 && mouse_push_flg == 0){

				// �}�E�X�`�F�b�N�t���O�L����
				mouse_push_flg = 1;

				// �{�^���m�F
				chk_but(tk);
				// set_plt_naki_arinashi();

			}

			// �t���[�������N���b�N����(AUTO_FRAME_COUNT_RESULT�����҂�����)
			auto_frame_click(AUTO_FRAME_COUNT_RESULT);

		}

	// ----------------------------------------
	// ����ȊO
	// ----------------------------------------
	}else{

		// �{�^���̉����m�F
		if(  Button[0] > 0 && mouse_push_flg == 0){

			// �}�E�X�`�F�b�N�t���O�L����
			mouse_push_flg = 1;

			// �{�^���m�F
			chk_but(tk);
			set_plt_naki_arinashi();

		}

		// �t���[�������N���b�N����
		auto_frame_click(AUTO_FRAME_COUNT_CLIENT);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI����ʏ폈���i���C���j
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientSetPlyNormalActMain(MJSTkinfo *tk){

	// �v���[���[�ʏ�A�N�V������`(mode:TEHAI_NORMAL)
	if( gui_ply_tehai_mode == TEHAI_NORMAL ){
		guiClientSetPlyNormalAct(tk);
	// ���[�`�錾��̎̔v�I��(mode:TEHAI_RIICHI_SUTEHAI)
	}else if( gui_ply_tehai_mode == TEHAI_RIICHI_SUTEHAI ){
		guiClientSetPlyRiichiSutehaiAct(tk);
	// ���[�`�L����̃A�N�V����(���̐؂�A���̘a���A�Þ�)(mode:TEHAI_RIICHI_YUKO)
	}else if( gui_ply_tehai_mode == TEHAI_RIICHI_YUKO ){
		guiClientSetPlyRiichiYukoAct(tk);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI����ʏ폈���E�v���[���[�ʏ�A�N�V������`(mode:TEHAI_NORMAL)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientSetPlyNormalAct(MJSTkinfo *tk){

	// ----------------------------------------
	// ��v���̎̔v����
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// ��v�e�[�u���N���b�N�t���O�L�����ƃA�N�V������`
		tk->ply_act = ACTSUTE;

		// �̔v�ԍ��ݒ�(�}�E�X�I���ʒu)
		tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ���̔v�̎̔v����
	// ----------------------------------------
	}else if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
			  msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE &&
			  msy > tehai_y && 
			  msy < tehai_y + HAI_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// �e�[�u���N���b�N�t���O�L����
		tk->ply_act = ACTTSUMOGIRI;

		// �̔v�ԍ��ݒ�
		tk->ply_tbl_hum_sutehai_statnum = tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; // ���̔v

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �ȃv���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �ÞȔv��1���Ȃ��
		if ( naki_ankan_hai_count == 1 && naki_kakan_hai_count == 0 ){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];

		// ���Ȕv��1���Ȃ��
		}else if( naki_ankan_hai_count == 0 && naki_kakan_hai_count == 1 ){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTKAKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_kakan_hai[0];

			// ���Ȕv���Ԕv�Ȃ��
			if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 5 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else if ( tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 && tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2] > 0){
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 1;
			}else{
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
			}

		// ���v����������ꍇ�ɂ�
		}else{

			// ----------------------------------------
			// GUI��v���[�h�̕ύX
			// ----------------------------------------
			gui_ply_tehai_mode = TEHAI_ANKAN_KAKAN_SELECT;

		}

		// ----------------------------------------
		// �v���[�g������
		// ----------------------------------------
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ���[�`�v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_RIICHI] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_RIICHI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_RIICHI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̃A�N�V������`
		tk->ply_act = ACTRIICH;

		// GUI��v���[�h�̕ύX
		gui_ply_tehai_mode = TEHAI_RIICHI_SUTEHAI;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �a���v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̃A�N�V������`
		tk->ply_act = ACTTSUMOAGARI;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ���̏ꏊ�������ꂽ�ꍇ�́A�N���b�N�t���O�𖳌�������
	// ----------------------------------------
	}else{

		// �N���b�N�t���O������
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI����ʏ폈���E���[�`�錾��̎̔v�I��(mode:TEHAI_RIICHI_SUTEHAI)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientSetPlyRiichiSutehaiAct(MJSTkinfo *tk){

	// ----------------------------------------
	// ��v���̎̔v����
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// ���[�`���̑I���̔v�̃V�����e����0�ł���Ȃ�
		if(tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][(msx-tehai_x)/HAI_XSIZE] == true){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// ��v�e�[�u���N���b�N�t���O�L�����ƃA�N�V������`
			tk->ply_act = ACTSUTE;

			// �̔v�ԍ��ݒ�(�}�E�X�I���ʒu)
			tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;        // ��v�I��v

			// GUI��v���[�h�̕ύX
			gui_ply_tehai_mode = TEHAI_RIICHI_YUKO;

		}

	// ----------------------------------------
	// ���̔v�ŃN���b�N�����Ȃ�̔v���`����
	// ----------------------------------------
	}else if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
			  msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE &&
			  msy > tehai_y && 
			  msy < tehai_y + HAI_YSIZE ){

		// ���[�`���̑I���̔v�̃V�����e����0�ł���Ȃ�
		if( tk->ply_act_tsumo_can_sute[HUM_PLY_SEKI_NUM] == true ){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// �e�[�u���N���b�N�t���O�L����
			tk->ply_act = ACTTSUMOGIRI;

			// �̔v�ԍ��ݒ�
			tk->ply_tbl_hum_sutehai_statnum = (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]); // ���̔v

			// GUI��v���[�h�̕ύX
			gui_ply_tehai_mode = TEHAI_RIICHI_YUKO;

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI����ʏ폈���E���[�`�L����̃A�N�V����(���̐؂�A���̘a���A�Þ�)(mode:TEHAI_RIICHI_YUKO)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientSetPlyRiichiYukoAct(MJSTkinfo *tk){

	// ----------------------------------------
	// ���̔v�̎̔v����
	// ----------------------------------------
	if( msx > tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE && 
		msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE) + SPACE_XSIZE + HAI_XSIZE &&
		msy > tehai_y && 
		msy < tehai_y + HAI_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// �e�[�u���N���b�N�t���O�L����
		tk->ply_act = ACTTSUMOGIRI;

		// �̔v�ԍ��ݒ�
		tk->ply_tbl_hum_sutehai_statnum = tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; // ���̔v

	// ----------------------------------------
	// �ȃv���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
	          msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// �ÞȔv�Ȃ��
		if ( naki_ankan_hai_count > 0){
			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act = ACTANKAN;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = naki_ankan_hai[0];
		}

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

		// GUI��v���[�h�̕ύX
		// gui_ply_tehai_mode = TEHAI_ANKAN_KAKAN_SELECT;

	// ----------------------------------------
	// �a���v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// ��v�e�[�u���N���b�N�t���O�L�����ƃA�N�V������`
		tk->ply_act = ACTTSUMOAGARI;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ���̏ꏊ�������ꂽ�ꍇ�́A�N���b�N�t���O�𖳌�������
	// ----------------------------------------
	}else{

		// �N���b�N�t���O������
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI����ʏ폈���E�v���[���[�ÞȃA�N�V������`(mode:TEHAI_ANKAN_KAKAN_SELECT)
/* ---------------------------------------------------------------------------------------------- */




/* ---------------------------------------------------------------------------------------------- */
// GUI����ʏ폈���E�v���[���[�ʖ��m�F(���C��)
/* ---------------------------------------------------------------------------------------------- */




/* ---------------------------------------------------------------------------------------------- */
// GUI����ʏ폈���E�v���[���[�ʖ��A�N�V������`(mode:TEHAI_NORMAL || mode:TEHAI_RIICHI_YUKO)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClientSetPlyNakiAct(MJSTkinfo *tk){

	// ----------------------------------------
	// �u���ցv�v���[�g��������Ă���ꍇ�ɂ�
	// ----------------------------------------
	if( msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT && 
	    msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_NEXT + PLT_ICON_XSIZE &&
	    msy > PLT_Y_STAT && 
	    msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̃A�N�V������`
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �a���v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_AGARI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_AGARI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̃A�N�V������`
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTRON;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �|���v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_PON] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_PON && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_PON + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̃A�N�V������`
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTPON;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �ȃv���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_KAN] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_KAN + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �N���b�N�t���O�L����
		act_push_flg = true;

		// HUM�v���[���[�̃A�N�V������`
		tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTMINKAN;

		// �v���[�g������
		plt_mode[PLT_RIICHI] = false;
		plt_mode[PLT_PON]    = false;
		plt_mode[PLT_KAN]    = false;
		plt_mode[PLT_CHI]    = false;
		plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// �`�[�v���[�g�������ꂽ�Ȃ�
	// ----------------------------------------
	}else if( plt_mode[PLT_CHI] == true &&
		      msx > SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_CHI && 
		      msx < SPACE_XSIZE+(PLT_ICON_XSIZE+SPACE_XSIZE)*PLT_CHI + PLT_ICON_XSIZE &&
		      msy > PLT_Y_STAT && 
		      msy < PLT_Y_STAT + PLT_ICON_YSIZE ){
/*
		// �`�[���v��2���ȏ�ł���΁A�v�I���������s��
		if (chihai_count > 1){

			// ���[�h�ύX
			gui_ply_tehai_mode = TEHAI_CHI_SELECT;

		// �`�[���v��1���ł���΁A�����`�[����
		}else{
*/
			// �N���b�N�t���O�L����
			act_push_flg = true;

			// HUM�v���[���[�̃A�N�V������`
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTCHI;

			// �v�ݒ�
			// tk->ply_naki_hai[HUM_PLY_SEKI_NUM] = ;

			// �Ԗ�����`

			// �`�[INDEX�v��`
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = chi_idx_hai[0];

			// �Ԗ�����`
			tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = chi_aka_count[0];

			// �v���[�g������
			plt_mode[PLT_RIICHI] = false;
			plt_mode[PLT_PON]    = false;
			plt_mode[PLT_KAN]    = false;
			plt_mode[PLT_CHI]    = false;
			plt_mode[PLT_AGARI]  = false;

	// ----------------------------------------
	// ����ȊO�̏����͖�����
	// ----------------------------------------
	}else{

		// �N���b�N�t���O������
		act_push_flg = false;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI����ʏ폈���E�v���[���[�`�[�v�A�N�V������`(mode:TEHAI_CHI_SELECT)
/* ---------------------------------------------------------------------------------------------- */




/* ---------------------------------------------------------------------------------------------- */
// GUI����ʏ폈���E�v���[���[����̎̔v����
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiClienSetPlyNakiSuteAct(MJSTkinfo *tk){

	// ----------------------------------------
	// ��v���̎̔v����
	// ----------------------------------------
	if( msx > tehai_x && 
	    msx < tehai_x + (tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]-1)*HAI_XSIZE + HAI_XSIZE &&
	    msy > tehai_y && 
	    msy < tehai_y + HAI_YSIZE ){

		// �̔v�ԍ��ݒ�(�}�E�X�I���ʒu)
		tk->ply_tbl_hum_sutehai_statnum = (msx-tehai_x) / HAI_XSIZE;

		// ���̂ĉ\�Ȃ�
		if(tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tk->ply_tbl_hum_sutehai_statnum] == true){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// ��v�e�[�u���N���b�N�t���O�L�����ƃA�N�V������`
			tk->ply_act = ACTNAKISUTE;

			// HUM�v���[���[�̖��A�N�V������`
			tk->ply_act_naki[HUM_PLY_SEKI_NUM]       = ACTNONAKI;
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = 0;
			tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = 0;
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �N���C�A���g���[�h�E�t���[�������J�E���g
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::auto_frame_click(int tmp_coint_max){

	// �t���[�������ߐ��m�F
	if( frame_count > tmp_coint_max ){

		// �I���{�^���łȂ��Ȃ�
		if( gui_taku_mode != COMMON_END_CHECK_MODE && gui_taku_mode != COMMON_END_MODE){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// �t���[��������
			frame_count = 0;

		}else{

			// �N���b�N�m�F�t���O������
			act_push_flg = false;

		}

	}else{

		// �t���[���J�E���g
		frame_count++;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �N���C�A���g���[�h�E�t���[�������J�E���g(���[�`�p)
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::auto_frame_click_riichi(MJSTkinfo *tk, int tmp_coint_max){

	// �t���[�������ߐ��m�F
	if( frame_count > tmp_coint_max ){

		// �I���{�^���łȂ��Ȃ�
		if( gui_taku_mode != COMMON_END_CHECK_MODE && gui_taku_mode != COMMON_END_MODE){

			// �N���b�N�t���O�L����
			act_push_flg = true;

			// �e�[�u���N���b�N�t���O�L����
			tk->ply_act = ACTTSUMOGIRI;

			// �̔v�ԍ��ݒ�
			tk->ply_tbl_hum_sutehai_statnum = tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; // ���̔v

			// �t���[��������
			frame_count = 0;

		}else{

			// �N���b�N�m�F�t���O������
			act_push_flg = false;

		}

	}else{

		// �t���[���J�E���g
		frame_count++;

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �e�{�^���̏�Ԋm�F
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::chk_but(MJSTkinfo *tk){

	// ----------------------------------------
	// �N���C�A���g���[�h
	// ----------------------------------------
	if ( gui_main_stat == GUI_CLIENT ){

		// �I���{�^���������ꂽ��
		if( msx > QUIT_BUT_X_STAT && 
		    msx < QUIT_BUT_X_STAT + BUT_ICON_XSIZE && 
		    msy > BUT02_Y_STAT && 
		    msy < BUT02_Y_STAT + BUT_ICON_YSIZE){

			// GUI�{�^���̗L����
			but_push_flg = true;

			// �N���b�N�t���O������(�{�^���������ꂽ�ꍇ�͏��false)
			act_push_flg = false;

			// ���[�h�ύX
			if(gui_taku_mode != COMMON_END_CHECK_MODE){

				// �I���m�F�X�e�[�^�X
				gui_taku_mode = COMMON_END_CHECK_MODE;

			}else if(gui_taku_mode == COMMON_END_CHECK_MODE){

				// �I������
				cli_mode = GUI_MJAI_DISCONNECT;

			}

		// �{�^����������Ă��Ȃ��Ȃ�
		}else{

			// GUI�{�^��������
			but_push_flg = false;

		}

	// ----------------------------------------
	// �샂�[�h��p����
	// ----------------------------------------
	}else{

		// �I���{�^���������ꂽ��
		if( msx > QUIT_BUT_X_STAT && 
		    msx < QUIT_BUT_X_STAT + BUT_ICON_XSIZE && 
		    msy > BUT02_Y_STAT && 
		    msy < BUT02_Y_STAT + BUT_ICON_YSIZE){

			// GUI�{�^���̗L����
			but_push_flg = true;

			// �N���b�N�t���O������(�{�^���������ꂽ�ꍇ�͏��false)
			act_push_flg = false;

			// ���[�h�ύX
			if(gui_taku_mode != COMMON_END_CHECK_MODE){
				// �I���m�F�X�e�[�^�X
				gui_taku_mode = COMMON_END_CHECK_MODE;
			}else if(gui_taku_mode == COMMON_END_CHECK_MODE){
				// �I������
				gui_taku_mode = COMMON_END_MODE;
			}

		// TKINFO���{�^���������ꂽ��
		} else if( msx > TKINFO_BUT_X_STAT && 
		    msx < TKINFO_BUT_X_STAT + BUT_ICON_XSIZE && 
		    msy > BUT02_Y_STAT && 
		    msy < BUT02_Y_STAT + BUT_ICON_YSIZE){

			// GUI�{�^���̗L����
			but_push_flg = true;

			// �N���b�N�t���O������(�{�^���������ꂽ�ꍇ�͏��false)
			act_push_flg = false;

			// ���[�h�ύX
			if(gui_taku_mode == COMMON_TKINFO_MODE){
				// �ʏ탂�[�h�ɖ߂�
				gui_taku_mode = COMMON_PLAY_MODE;
			}else{
				// ACT��v���\�����[�h
				gui_taku_mode = COMMON_TKINFO_MODE;
			}

		// PLYINFO_BUT�������ꂽ��
		}else if( msx > PLYINFO_BUT_X_STAT && 
			      msx < PLYINFO_BUT_X_STAT + BUT_ICON_XSIZE && 
			      msy > BUT02_Y_STAT && 
			      msy < BUT02_Y_STAT + BUT_ICON_YSIZE){

			// GUI�{�^���̗L����
			but_push_flg = true;

			// �N���b�N�t���O������(�{�^���������ꂽ�ꍇ�͏��false)
			act_push_flg = false;

			// ���[�h�ύX
			if(gui_taku_mode == GAME_PLY_INFO_MODE){
				// �ʏ탂�[�h�ɖ߂�
				gui_taku_mode = COMMON_PLAY_MODE;
			}else{
				// ACT��v���\�����[�h
				gui_taku_mode = GAME_PLY_INFO_MODE;
			}

		// �{�^����������Ă��Ȃ��Ȃ�
		}else{

			// GUI�{�^��������
			but_push_flg = false;

		}

	}
}

/* ---------------------------------------------------------------------------------------------- */
// ���փv���[�g�����m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::set_plt_next(){

	// ----------------------------------------
	// ���փv���[�g�������ꂽ��
	// ----------------------------------------

	// �N���b�N�t���O�L����
	act_push_flg = true;

}

/* ---------------------------------------------------------------------------------------------- */
// �u�L/���v�v���[�g�̕\���ύX
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::set_plt_naki_arinashi(){

	// ----------------------------------------
	// �u�L/���v�v���[�g�������ꂽ��
	// ----------------------------------------
	if( msx > PLT_NAKIARI_X_STAT && 
		msx < PLT_NAKIARI_X_STAT + PLT_ICON_XSIZE &&
		msy > PLT_Y_STAT && 
		msy < PLT_Y_STAT + PLT_ICON_YSIZE ){

		// �l�ύX
		if (plt_nakiari_flg == true){
			plt_nakiari_flg = false;
		}else{
			plt_nakiari_flg = true;
		}

	}

	// �N���b�N�t���O������(�{�^���������ꂽ�ꍇ�͏��false)
	act_push_flg = false;
}

/* ---------------------------------------------------------------------------------------------- */
// �ݒ胂�[�h�F����������
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSettingInit(){

	// ���[�h������
	set_mode = SETTING_INFO_MODE;

}

/* ---------------------------------------------------------------------------------------------- */
// �ݒ胂�[�h�F���C������
/* ---------------------------------------------------------------------------------------------- */
void MJSGui::guiSetting(){

	// �}�E�X���擾
	MouseStat();

	// ----------------------------------------
	// �}�E�X�J��
	// ----------------------------------------

	// �}�E�X��������Ă��Ȃ��Ȃ�A�u�}�E�X�J�����(mouse_push_flg=0)�v�Ƃ���
	if( Button[0] == 0 && Button[1] == 0 ){
		mouse_push_flg = 0;
	}

	// ----------------------------------------
	// �{�^���������ꂽ�ꍇ�̏���
	// ----------------------------------------

	// �}�E�X�������ꂽ�Ȃ�
	if( Button[0] > 0 && mouse_push_flg == 0){

		// �}�E�X�`�F�b�N�t���O�L����
		mouse_push_flg=1;

		// �{�^��1�������ꂽ��
		if( msx > SETTING_X_START && 
			msx < SETTING_X_START + BUT_ICON_XSIZE &&
			msy > SETTING_Y_START && 
			msy < SETTING_Y_START + BUT_ICON_YSIZE ){

			// ���[�h�ύX
			set_mode = SETTING_FILENAME_MJAI_MODE;

		// �{�^��2�������ꂽ��
		}else if( msx > SETTING_X_START && 
			      msx < SETTING_X_START + BUT_ICON_XSIZE  &&
			      msy > SETTING_Y_START+1*SETTING_Y_RANGE && 
			      msy < SETTING_Y_START+1*SETTING_Y_RANGE + BUT_ICON_YSIZE ){

			// ���[�h�ύX
			set_mode = SETTING_FILENAME_MJSCORE_MODE;

		// �I���{�^���������ꂽ��
		}else if( msx > SETTING_X_START && 
			      msx < SETTING_X_START + BUT_ICON_XSIZE &&
			      msy > SETTING_ENDBUT_Y_START && 
			      msy < SETTING_ENDBUT_Y_START + BUT_ICON_YSIZE ){

			// ���C���X�e�[�^�X�ύX
			gui_main_stat = GUI_SETTING_POST;

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
