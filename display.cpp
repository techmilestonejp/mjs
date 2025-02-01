/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F �����疃��(Ver0.1.2.1�F�J����)
 * �o�[�W����     �F 0.1.2.1.234(�\���v(open_haiparts)�ꗗ�\��)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F display.cpp
 * �N���X��       �F MJSDisplay
 * �����T�v       �F ��ʕ\�������N���X
 * Ver0.0.8�쐬�� �F 2012/03/17 13:21:58
 * Ver0.1.0�쐬�� �F 2022/05/03 18:50:06
 * Ver0.1.1�쐬�� �F 2022/06/30 21:19:01
 * Ver0.1.2�쐬�� �F 2022/08/31 22:19:54
 * �ŏI�X�V��     �F 2025/02/01 09:57:37
 * 
 * Copyright (c) 2010-2025 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "display.h"

/* ---------------------------------------------------------------------------------------------- */
// �O����
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayInit(){

	// ----------------------------------------
	// �N���X��`
	// ----------------------------------------

	 // �p�[�c�\���N���X������
	dparts = new MJSDisplayParts;

	// ----------------------------------------
	// �N���X����������
	// ----------------------------------------

	// �N���X������
	dparts->DispPartsInit();

	// DX���C�u������ʏ���������
	if (dparts->DispPartsFrameInit() != 0){

	}

	// DX���C�u����������
	if (dparts->DispPartsLibInit() != 0){

	}

	// ----------------------------------------
	// ��ʕ\���ݒ�
	// ----------------------------------------

	// �f�o�O���̕\��
	if(DISP_DEBUG_INFO == 0){
		disp_debug_info_mode = false;
	}else{
		disp_debug_info_mode = true;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �㏈�� 
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayPost(){

	// ----------------------------------------
	// DX���C�u�����I��
	// ----------------------------------------
	dparts->DispPartsLibPost();

}

/* ---------------------------------------------------------------------------------------------- */
// �e�X�g�p�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplaySampleTitle(MJSTkinfo *tk, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// ----------------------------------------
	// �ϐ���`
	// ----------------------------------------
	tk->kyoku_index = 0;
	tk->kyoku[tk->kyoku_index].doracount     = 1;
	tk->kyoku[tk->kyoku_index].dora[0]       = 31;
	tk->kyoku[tk->kyoku_index].dora_aka[0]   = false;
	tk->kyoku[tk->kyoku_index].dora_actid[0] = 0;

	// ----------------------------------------
	// �����`�揈��
	// ----------------------------------------
	dparts->DispPartsClearDraw();

	// ----------------------------------------
	// �p�[�c�\��
	// ----------------------------------------
	dparts->DispBunner(ver1, ver2, ver3, ver4, ver5);                                     // �o�i�[
	dparts->DispMousepoint(5, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);   // �}�E�X�ʒu
	dparts->DispFps(670, 750, mFps, total_frame_count, 0);                                // FPS

	// �h���\��
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 0);

	// �v���[�g�\��
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// �v���[�g�L/��
	dparts->DispPltNakiAriNashi(PLT_NAKIARI_X_STAT, PLT_Y_STAT, gui->plt_nakiari_flg);

	// �Q�[�����[�h�̃{�^���\��
	// dparts->DispGameModeButton();
	dparts->DispInfoButton(THINFO_BUT_X_STAT, TKINFO_BUT_X_STAT, PLYINFO_BUT_X_STAT, QUIT_BUT_X_STAT, BUT02_Y_STAT);

	// ----------------------------------------
	// ����ʂ�\��ʂɔ��f
	// ----------------------------------------
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// �I�[�v�j���O���
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayOpening(MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// ----------------------------------------
	// �����`�揈��
	// ----------------------------------------
	dparts->DispPartsClearDraw();

	// ----------------------------------------
	// �p�[�c�\��
	// ----------------------------------------

	// �}�E�X�|�C���g
	dparts->DispMousepoint(SPACE_XSIZE, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);

	// FPS
	dparts->DispFps(670, 750, mFps, total_frame_count, gui->frame_count);

	// �^�C�g���\��
	dparts->DispOpeningTitle(ver1, ver2, ver3, ver4, ver5);

	// ----------------------------------------
	// 00:�ݒ���
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*0,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*0+8, GetColor(255,255,255),  "�ݒ�");

	// ----------------------------------------
	// 01:�v���ʓǍ�(�r���[���[���[�h�FMJAI���O)
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*1,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*1+8, GetColor(255,255,255),  "�v���Ǎ��FMJAI���O");

	// ----------------------------------------
	// 02:�v���ʓǍ�(�r���[���[���[�h�F���������O)
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*2,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*2+8, GetColor(255,255,255),  "�v���Ǎ��F���������O");

	// ----------------------------------------
	// 03:4COM�Ό��E���̃e�[�u���Ǎ�
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*3,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*3+8, GetColor(255,255,255),  "4COM�Ό��E��ǃ��[�h�F�v���Ǎ�");

	// ----------------------------------------
	// 04:4COM�Ό��E�V�[�h�l�����_��
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*4,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*4+8, GetColor(255,255,255),  "4COM�Ό��E��ǃ��[�h�F�����_������(���ԕϐ�)");

	// ----------------------------------------
	// 05:HUM�Ό��E��Ǒΐ�E���̃e�[�u���Ǎ�
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*5,   PARTS_BUT_GREEN);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*5+8, GetColor(255,255,255),  "HUM�Ό��E��ǃ��[�h�F�v���Ǎ�");

	// ----------------------------------------
	// 06:HUM�Ό��E�����탂�[�h�E�V�[�h�l�Œ�
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*6,   PARTS_BUT_GREEN);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*6+8, GetColor(255,255,255),  "HUM�Ό��E�����탂�[�h�F�����_������(�Œ�l)");

	// ----------------------------------------
	// 07:HUM�Ό��E�����탂�[�h�E�V�[�h�l�����_��
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*7,   PARTS_BUT_GREEN);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*7+8, GetColor(255,255,255),  "HUM�Ό��E�����탂�[�h�F�����_������(���ԕϐ�)");

	// ----------------------------------------
	// 08:MJAI�N���C�A���g(GUI���[�h)
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*8,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*8+8, GetColor(255,255,255), "MJAI�N���C�A���g�FGUI���[�h");

	// ----------------------------------------
	// 09:MJAI�N���C�A���g(Ply���[�h)
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*9,   PARTS_BUT_BLUE);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*9+8, GetColor(255,255,255), "MJAI�N���C�A���g�FPly���[�h");


	// ----------------------------------------
	// 10:���؃��[�h�EACTID_MAX
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*10,   PARTS_BUT_YELLOW);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*10+8, GetColor(255,255,255),  "���؃��[�h�F��ID�������[�h");

	// ----------------------------------------
	// 11:���؃��[�h�E������
	// ----------------------------------------
	dparts->DispButton(OPENING_BUT01_X_START,  OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*11,   PARTS_BUT_YELLOW);
	DrawFormatString(OPENING_BUT01_X_START+50, OPENING_BUT01_Y_START+OPENING_BUT01_Y_RANGE*11+8, GetColor(255,255,255),  "���؃��[�h�F�����탂�[�h");

	// ----------------------------------------
	// ����ʂ�\��ʂɔ��f
	// ----------------------------------------
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// ��\��(�Q�[�����[�h)�̃��C������
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTaku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// ----------------------------------------
	// �����`�揈��
	// ----------------------------------------
	dparts->DispPartsClearDraw();

	// ----------------------------------------
	// �p�[�c�\��
	// ----------------------------------------

	// �o�i�[
	dparts->DispBunner(ver1, ver2, ver3, ver4, ver5);

	// �}�E�X�|�C���g
	dparts->DispMousepoint(SPACE_XSIZE, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);

	// FPS
	dparts->DispFps(670, 750, mFps, total_frame_count, gui->frame_count);

	// ----------------------------------------
	// �X�e�[�^�X���Ƃ̃p�[�c�\��
	// ----------------------------------------

	// �X�e�[�^�X���Ƃ̃p�[�c�\��
	switch(tk->stat){

		// ��J�n
		case TAKUSTART:
			// �\�������͖���
		break;

		// �ꌈ��
		case BAGIME:
			// �ꌈ�ߏ��
			DisplayBagime(tk,gui);
		break;

		// �ǊJ�n
		case KYOKUSTART:
			// �\�������͖���
		break;

		// �ǏI��
		case KYOKUEND:
			// �\�������͖���
		break;

		// ��I��
		case TAKUEND:
			// �\�������͖���
		break;

		// �ǌ��ʕ\��
		case KYOKURESULT:

			// �Ǐ��
			DispKyokuInfo(tk,tk->kyoku_index);

			// �h��
			dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 tk->kyoku[tk->kyoku_index].act_count);

			// ����
			DispTakuStat(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT + STRING_YSIZE);

			// ��N���X���
			DispTkInfoStat(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT + STRING_YSIZE*2);

			// �ǏI���\��
			DispKyokuEnd(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		break;

		// �쌋�ʕ\��
		case TAKURESULT:

			// ��I�����
			DisplayGameResult(tk, gui);

		break;

		// �W������(���̑�����)
		default:

			// �ʏ���
			DispNormalTakuStat(tk,ply,gui);

	}

	// ----------------------------------------
	// ����ʂ�\��ʂɔ��f
	// ----------------------------------------
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// �ꌈ�ߏ��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayBagime(MJSTkinfo *tk, MJSGui *gui){

	// -----------------------------------------------------------
	// �v���[�����̕\��
	// -----------------------------------------------------------

	// �ǐ���
	dparts->DispString( BAGIME_X_START, BAGIME_Y_START, tk->tkname );

	// �ȕ\��
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

		// �v���[����
		      if(tk->kyoku[0].ie[tmp_pnum] == 0){
			DrawFormatString(BAGIME_X_START, BAGIME_Y_START + 50 + 50 * tmp_pnum, GetColor(255,255,255), "[��%d]���Ɓ@%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[0].ie[tmp_pnum] == 1){
			DrawFormatString(BAGIME_X_START, BAGIME_Y_START + 50 + 50 * tmp_pnum, GetColor(255,255,255), "[��%d]��Ɓ@%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[0].ie[tmp_pnum] == 2){
			DrawFormatString(BAGIME_X_START, BAGIME_Y_START + 50 + 50 * tmp_pnum, GetColor(255,255,255), "[��%d]���Ɓ@%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[0].ie[tmp_pnum] == 3){
			DrawFormatString(BAGIME_X_START, BAGIME_Y_START + 50 + 50 * tmp_pnum, GetColor(255,255,255), "[��%d]�k�Ɓ@%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else{
			DrawFormatString(BAGIME_X_START, BAGIME_Y_START + 50 + 50 * tmp_pnum, GetColor(255,255,255), "[��%d]�s���@%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}

	}

	// �����V�[�h(core)
	wsprintf(tmp_disp_msg,"����SEED %10d", tk->core_seed_num);
	dparts->DispString( 100, 400, tmp_disp_msg);

	// �N���b�N�ē�
	wsprintf(tmp_disp_msg, "�N���b�N���Ă�������");
	dparts->DispString( 100, 450, tmp_disp_msg);

	// �v���[�g�\��
	// dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

}

/* ---------------------------------------------------------------------------------------------- */
// �Q�[�����[�h�\���E�ʏ���
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispNormalTakuStat(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// �Ǐ��
	// -----------------------------------------------------------

	// �Ǐ��
	DispKyokuInfo(tk,tk->kyoku_index);

	// �h��
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 tk->kyoku[tk->kyoku_index].act_count);

	// �{�^���\��
	dparts->DispInfoButton(THINFO_BUT_X_STAT, TKINFO_BUT_X_STAT, PLYINFO_BUT_X_STAT, QUIT_BUT_X_STAT, BUT02_Y_STAT);

	// �ʏ탂�[�h�ŕ\������p�[�c
	if( gui->gui_taku_mode == COMMON_PLAY_MODE){
		// �v���[�g�\��
		dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);
		// �v���[�g�L/��
		dparts->DispPltNakiAriNashi(PLT_NAKIARI_X_STAT, PLT_Y_STAT, gui->plt_nakiari_flg);
		// ��v���C�����b�Z�[�W
		DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);
	}

	// -----------------------------------------------------------
	// �f�o�O���
	// -----------------------------------------------------------
	if(disp_debug_info_mode == true){
		// �ʃA�N�V�������
		DispActNumInfo(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);
		// ����
		DispTakuStat(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT + STRING_YSIZE);
		// ��N���X���
		DispTkInfoStat(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT + STRING_YSIZE*2);
		// GUI���
		DispGuiInfo(gui,SPACE_XSIZE, GUI_INFO_Y_STAT);
	}

	// -----------------------------------------------------------
	// ��GUI���[�h(gui->gui_taku_mode)���Ƃ̕\��
	// -----------------------------------------------------------
	if( gui->gui_taku_mode == COMMON_PLAY_MODE){

		// -----------------------------------------------------------
		// �u��v���C�i�[�v���[�h�\��
		// -----------------------------------------------------------
		if( gui->disp_tehai_mode == 0){

			// ���C�i�[���[�h�\��
			for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {

				// ��v
				if( tk->ply_hum_mode == 1 && tmp_pnum == HUM_PLY_SEKI_NUM){
					// ��v(HUM�\��)
					DispActTehaiHum(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}else{
					// ��v(COM�\��)
					DispActTehaiCom(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}

				// �N���\��
				DispActSarashi(tk, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// �͕\��(���C�i�[�\��)
				DispActKawa(tk, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// �v���[�����Ƃ̓��_���
				DispPlyInfo(tk, tk->kyoku_index, tmp_pnum);

			}

		// -----------------------------------------------------------
		// �u��v�͂݁v���[�h�\��
		// -----------------------------------------------------------
		}else if( gui->disp_tehai_mode == 1 ){

			// �A�N�V�����v���[�g�\��
			

			// ��v���[�g�\��
			DrawBox( TAKU_PLT_X_STAT, TAKU_PLT_Y_STAT, TAKU_PLT_X_SIZE-1, TAKU_PLT_Y_SIZE-1, GetColor( 0, 64, 0 ), TRUE ) ;

			// �Z���^�[�v���[�g
			dparts->DispCenterPlt( (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3,
			                       (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 );

			// ��v�͂݃��[�h�\��
			for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {

				// ��v
				if( tk->ply_hum_mode == 1 && tmp_pnum == HUM_PLY_SEKI_NUM){
					// ��v(HUM�\��)
					DispActTehaiHum(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}else{
					// ��v(COM�\��)
					DispActTehaiCom_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}

				// �N���\��
				DispActSarashi_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// �͕\��
				DispActKawa_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// �v���[�����Ƃ̓��_���
				DispPlyInfo(tk, tk->kyoku_index, tmp_pnum);

			}

		// -----------------------------------------------------------
		// �u�e�X�g�\���v���[�h
		// -----------------------------------------------------------
		}else if( gui->disp_tehai_mode == 2 ){

			// �͂ݎ�v�̃T���v���\��
			DispActTehai_test_square(gui);

		}

	// -----------------------------------------------------------
	// �I���\��
	// -----------------------------------------------------------
	}else if(gui->gui_taku_mode == COMMON_END_CHECK_MODE){

		// �I���{�^���̊m�F
		DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);

	// -----------------------------------------------------------
	// tkinfo�N���X���
	// -----------------------------------------------------------
	}else if(gui->gui_taku_mode == COMMON_TKINFO_MODE){

		// tkinfo�N���X�\��
		DisplayTkinfoDetail(tk);

	// -----------------------------------------------------------
	// ��v���ڍ�(ply�N���X���\��)
	// -----------------------------------------------------------
	}else if(gui->gui_taku_mode == GAME_PLY_INFO_MODE){

		// ��v���ڍ�(ply�N���X���\��)
		DisplayPlyTehaiDetail(tk, ply, tk->ply_turn);

		// �T�u��v�̕\�����[�h�ݒ�
		// sub_tehai_display_mode = SUB_TEHAI_DISP_MODE;

		// ��v���ڍ�(ply�N���X���\��)
		// if( sub_tehai_display_mode == 0){
		// 	DisplayTakuDetail(tk,ply,tk->ply_turn);
		// }else{
		//	DispYamahai(tk);
		// }

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��\��(�r���[�A�[���[�h)�̃��C������
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayViewerTaku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// -----------------------------------------------------------
	// ��ʂ̏�����
	// -----------------------------------------------------------
	dparts->DispPartsClearDraw();

	// -----------------------------------------------------------
	// �p�[�c�\��
	// -----------------------------------------------------------

	// �o�i�[
	dparts->DispBunner(ver1, ver2, ver3, ver4, ver5);

	// �}�E�X�|�C���g
	dparts->DispMousepoint(SPACE_XSIZE, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);

	// FPS
	dparts->DispFps(670, 750, mFps, total_frame_count, gui->frame_count);

	// �v���[�g�\��
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// -----------------------------------------------------------
	// ����{�^��
	// -----------------------------------------------------------

	// �{�^���\��(�폜�p)
	// dparts->DispViewerModeButton();
	dparts->DispActidButton(KYOID_X_STAT, ACTID_X_STAT, ACTID_Y_STAT);          // ACTID�{�^��
	dparts->DispBagimeButton(BAGIME_X_STAT, TKEND_X_STAT, BAGIME_Y_STAT);       // �ꌈ�߃{�^��
	dparts->DispSekiButton(VIEWER_SEKI_X_STAT, VIEWER_SEKI_Y_STAT);             // �ȕύX�{�^��

	// ��񑀍�{�^��
	dparts->DispInfoButton(THINFO_BUT_X_STAT, TKINFO_BUT_X_STAT, PLYINFO_BUT_X_STAT, QUIT_BUT_X_STAT, BUT02_Y_STAT);

	// ���O�`��
	DisplayGuiLogType(gui, KYOID_X_STAT, ACTID_Y_STAT - STRING_YSIZE*4);

	// �A�N�V�������
	DispActNumInfo(tk, KYOID_X_STAT, ACTID_Y_STAT - STRING_YSIZE, gui->gui_kyoku_index, gui->gui_actid);

	// GUI��Q�[���\�����[�h
	DisplayGuiTakuMode(gui, KYOID_X_STAT+80, ACTID_Y_STAT+48);

	// DOWN��v�̃v���[��ID
	DrawFormatString(KYOID_X_STAT+80, ACTID_Y_STAT+88, GetColor(255,255,255), "DOWN��v[��%d]", gui->disp_down_tehai_pnum+1);

	// -----------------------------------------------------------
	// ��W���\��
	// -----------------------------------------------------------

	// �Ǐ��
	DispKyokuInfo(tk, gui->gui_kyoku_index);

	// �h���\��
	/* dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	tk->kyoku[gui->gui_kyoku_index].doracount, 
	tk->kyoku[gui->gui_kyoku_index].dora, 
	tk->kyoku[gui->gui_kyoku_index].dora_aka);*/
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[gui->gui_kyoku_index].doracount, 
	                 tk->kyoku[gui->gui_kyoku_index].dora, 
	                 tk->kyoku[gui->gui_kyoku_index].dora_aka,
	                 tk->kyoku[gui->gui_kyoku_index].dora_actid,
	                 gui->gui_actid);

	// ���b�Z�[�W�\��
	if(gui->gui_taku_mode == COMMON_END_CHECK_MODE){

		// �I���{�^���̊m�F
		DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);

	}

/*
	// �f�o�O����\��
	if(gui->gui_taku_mode != COMMON_END_CHECK_MODE){
		// �ʃA�N�V�������
		DispActNumInfo(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT, gui->gui_kyoku_index, gui->gui_actid);
		// ��N���X���
		DispTkInfoStat(tk, SPACE_XSIZE, DEBUG_INFO_Y_STAT+STRING_YSIZE*2);
	}
*/

	/*-----------------------------------------------------------*/
	// ��X�e�[�^�X���Ƃ̕\��
	/*-----------------------------------------------------------*/

	// �ʏ�\��
	if(gui->gui_taku_mode == COMMON_PLAY_MODE){

		// �ǌ��ʕ\��
		if(tk->kyoku[gui->gui_kyoku_index].act_stat[gui->gui_actid] == KYOKURESULT){

				// ���O�`�����Ƃŕ\��
				if (gui->gui_logtype == GUI_LOG_MJSCORE){
					// �ǌ��ʁF���������O
					DispViewerKyokuEnd_mjscore(tk, gui->gui_kyoku_index, gui->gui_actid);
				}else if(gui->gui_logtype == GUI_LOG_MJAILOG){
					// �ǌ��ʁFMJAI���O
					DispViewerKyokuEnd_mjailog(tk, gui->gui_kyoku_index, gui->gui_actid);
				}

		}else{

			// �A�N�V�������Ƃ̑�\��
			DisplayViewerStatparts(tk, gui);

		}

	// �ꌈ�ߕ\��
	}else if(gui->gui_taku_mode == COMMON_BAGIME_MODE){

			// �ꌈ�ߕ\��
			DisplayBagime(tk, gui);

	// �쌋�ʕ\��
	}else if(gui->gui_taku_mode == COMMON_TAKURESULT_MODE){

			// �쌋�ʕ\��
			DispViewerGameResult(tk);

	}

	/*-----------------------------------------------------------*/
	// ����ʂ�\��ʂɔ��f
	/*-----------------------------------------------------------*/
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// �X�e�[�^�X���Ƃ̃p�[�c�\��(�r���[�A�[���[�h)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayViewerStatparts(MJSTkinfo *tk, MJSGui *gui){

	// -----------------------------------------------------------
	// �u��v���C�i�[�v���[�h�\��
	// -----------------------------------------------------------
	if( gui->disp_tehai_mode == 0){

		// �v���[���ꗗ�\��
		for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {

			// ��v(COM�\��)
			DispActTehaiCom(tk, gui, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum, gui->msx, gui->msy);

			// �N���\��
			DispActSarashi(tk, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum);

			// �̔v�`��
			DispActKawa(tk, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum);

			// �v���[�����Ƃ̓��_���
			DispPlyInfo(tk, gui->gui_kyoku_index, tmp_pnum);

		}

	// -----------------------------------------------------------
	// �u��v�͂݁v���[�h�\��
	// -----------------------------------------------------------
	}else if( gui->disp_tehai_mode == 1 ){

		// ��v���[�g�\��
		DrawBox( TAKU_PLT_X_STAT, TAKU_PLT_Y_STAT, TAKU_PLT_X_SIZE-1, TAKU_PLT_Y_SIZE-1, GetColor( 0, 64, 0 ), TRUE ) ;

		// �Z���^�[�v���[�g
		dparts->DispCenterPlt( (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3,
			                       (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 );

		// ��v�͂݃��[�h�\��
		for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {

			// ��v(COM�\��)
			DispActTehaiCom_square(tk, gui, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum, gui->msx, gui->msy);

			// �N���\��
			DispActSarashi_square(tk, gui, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum);

			// �͕\��
			DispActKawa_square(tk, gui, gui->gui_kyoku_index, gui->gui_actid, tmp_pnum);

			// �v���[�����Ƃ̓��_���
			DispPlyInfo(tk, gui->gui_kyoku_index, tmp_pnum);

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��v���ڍ�(tkinfo�N���X���\��)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail(MJSTkinfo *tk){

	// tkinfo���
	for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {
		// �ʕ\��
		DisplayTkinfoDetail_sub_sute(tk, SPACE_XSIZE,(PLY_YSTART-34)    + tmp_pnum*102 + 17*1, tmp_pnum, 0);                                                         // 1�i�ځF�̔v���
		DisplayTkinfoDetail_sub_sute(tk, SPACE_XSIZE,(PLY_YSTART-34)    + tmp_pnum*102 + 17*2, tmp_pnum, 1);                                                         // 2�i�ځF�̔v���
		DisplayTkinfoDetail_sub_tehai(tk, SPACE_XSIZE,(PLY_YSTART-34)   + tmp_pnum*102 + 17*3, tmp_pnum);                                                            // 3�i�ځF��v�e�[�u��
		DisplayTkinfoDetail_sub_hist(tk, SPACE_XSIZE,(PLY_YSTART-34)    + tmp_pnum*102 + 17*4, tmp_pnum);                                                            // 4�i�ځF��v�q�X�g�O�������
		DisplayTkinfoDetail_sub_naki(tk, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, SPACE_XSIZE, (PLY_YSTART-34) + tmp_pnum*102 + 17*5);       // 5�i�ځF�����
		DisplayTkinfoDetail_sub_shanten(tk, SPACE_XSIZE,(PLY_YSTART-34) + tmp_pnum*102 + 17*6, tmp_pnum);                                                            // 6�i�ځF�Ҕv���

		// DrawFormatString(SPACE_XSIZE, (PLY_YSTART-17) + tmp_pnum*95, GetColor(255,255,255), "[��%d�̔v1]",tmp_pnum+1);
		// DisplayTkinfoDetail_sub_tehai(tk, SPACE_XSIZE, (PLY_YSTART-17) + tmp_pnum*95 + 17*2, tmp_pnum);
		// DrawFormatString(SPACE_XSIZE, (PLY_YSTART-17) + tmp_pnum*95 + 17*2, GetColor(255,255,255), "[��%dHist]",tmp_pnum+1);
		// DrawFormatString(SPACE_XSIZE, (PLY_YSTART-17) + tmp_pnum*95 + 17*3, GetColor(255,255,255), "[��%d�v]",tmp_pnum+1);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo���̏ڍ�(�T�u�����F��v���)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_tehai(MJSTkinfo *tk, int x, int y, int pnum){

	// ��v�̍��v����
	DrawFormatString(x, y, GetColor(255,255,255), "[��%d]%2d��:", pnum+1,tk->ply_act_tehaicount[pnum]);

	// ��v���
	for(int tmp_i = 0; tmp_i < tk->ply_act_tehaicount[pnum]; tmp_i++){

		// �̔v�A�N�V�����Ȃ�
		if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTSUTE      || 
		    tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTTSUMOGIRI || 
		    tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTNAKISUTE  || 
			tk->ply_turn != pnum){

			// ��v���(�Ԕv�m�F)
			if(tk->ply_act_tehai_tbl_aka[pnum][tmp_i] == true){
				DrawFormatString(x+tmp_i*58+110, y, GetColor(255,255,255), "%2d��-",tk->ply_act_tehaitbl[pnum][tmp_i]);
			}else{
				DrawFormatString(x+tmp_i*58+110, y, GetColor(255,255,255), "%2d��-",tk->ply_act_tehaitbl[pnum][tmp_i]);
			}

		}else{

			// ��v���(�Ԕv�m�F)
			if(tk->ply_act_tehai_tbl_aka[pnum][tmp_i] == true){
				DrawFormatString(x+tmp_i*58+110, y, GetColor(255,255,255), "%2d��%d",tk->ply_act_tehaitbl[pnum][tmp_i],tk->ply_act_tehai_shanten_tbl[pnum][tmp_i]);
			}else{
				DrawFormatString(x+tmp_i*58+110, y, GetColor(255,255,255), "%2d��%d",tk->ply_act_tehaitbl[pnum][tmp_i],tk->ply_act_tehai_shanten_tbl[pnum][tmp_i]);
			}

		}

	}

			// ���̏��
			if(tk->ply_act_tsumo_aka[pnum] == true){
				DrawFormatString(x+13*58+110, y, GetColor(255,255,255), "%2d��%d",tk->ply_act_tsumo[pnum],tk->ply_act_tsumo_shanten[pnum]);
			}else{
				DrawFormatString(x+13*58+110, y, GetColor(255,255,255), "%2d��%d",tk->ply_act_tsumo[pnum],tk->ply_act_tsumo_shanten[pnum]);
			}

			// �̔v���
			if(tk->ply_act_sute_aka[pnum] == true){
				DrawFormatString(x+14*58+110, y, GetColor(255,255,255), "��%2d�Ԉ�%2d",tk->ply_act_sute[pnum],tk->ply_tbl_com_sutehai_statnum[pnum]);
			}else{
				DrawFormatString(x+14*58+110, y, GetColor(255,255,255), "��%2d�Ԉ�%2d",tk->ply_act_sute[pnum],tk->ply_tbl_com_sutehai_statnum[pnum]);
			}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo���̏ڍ�(�T�u�����F��v�q�X�g�O�������)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_hist(MJSTkinfo *tk, int x, int y, int pnum){

	// �q�X�g�O�������
	DrawFormatString(x, y, GetColor(255,255,255), "[��%d]", pnum+1);

	// �ݎq�A���q�A���q
	for(int tmp_syubetsu = 0; tmp_syubetsu < 3; tmp_syubetsu++){
		// 0�v
			DrawFormatString(tmp_syubetsu*95 +         + x+50, y, GetColor(255,255,255), "%d",tk->ply_act_tehai[pnum][tmp_syubetsu*10]);
		// 1-9�v
		for(int tmp_i = 0; tmp_i < 9; tmp_i++){
			DrawFormatString(tmp_syubetsu*95 + tmp_i*8 + x+65, y, GetColor(255,255,255), "%d",tk->ply_act_tehai[pnum][tmp_syubetsu*10+tmp_i+1]);
		}
	}

	// ���v
		// 0�v
			 DrawFormatString(             95*3 + x+50, y, GetColor(255,255,255), "%d",tk->ply_act_tehai[pnum][30]);
		// 1-9�v
		for(int tmp_i = 0; tmp_i < 7; tmp_i++){
			DrawFormatString(              95*3 + x+65 + (tmp_i)*8, y, GetColor(255,255,255), "%d",tk->ply_act_tehai[pnum][31+tmp_i]);
		}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo���̏ڍ�(�T�u�����F�̔v���)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_sute(MJSTkinfo *tk, int x, int y, int pnum, int line_num){

	// �̔v���1�i��
	if(line_num == 0){

		// �v���[�����
		DrawFormatString(x, y, GetColor(255,255,255), "[��%d]��%2d��:", pnum+1, tk->ply_act_kawa_count[pnum]);

		// �̔v���
		if(tk->ply_act_kawa_count[pnum] >= 15){
			for(int tmp_i = 0; tmp_i < 15; tmp_i++){
				DrawFormatString(tmp_i*58+x+110, y, GetColor(255,255,255), "%2d��%d",tk->ply_act_kawa[pnum][tmp_i],tk->ply_act_kawa_mode[pnum][tmp_i]);
			}
		}else{
			for(int tmp_i = 0; tmp_i < tk->ply_act_kawa_count[pnum]; tmp_i++){
				DrawFormatString(tmp_i*58+x+110, y, GetColor(255,255,255), "%2d��%d",tk->ply_act_kawa[pnum][tmp_i],tk->ply_act_kawa_mode[pnum][tmp_i]);
			}
		}

	// �̔v���2�i��
	}else{

		// �v���[�����
		DrawFormatString(x, y, GetColor(255,255,255), "[��%d]:�@�@�@", pnum+1);
		// �̔v���
		if(tk->ply_act_kawa_count[pnum] >= 15){
			for(int tmp_i = 15; tmp_i < tk->ply_act_kawa_count[pnum]; tmp_i++){
				DrawFormatString((tmp_i-15)*58+x+110, y, GetColor(255,255,255), "%2d��%d",tk->ply_act_kawa[pnum][tmp_i],tk->ply_act_kawa_mode[pnum][tmp_i]);
			}
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo���̏ڍ�(�T�u�����F�v���)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_naki(MJSTkinfo *tk, int kyoku_index, int actid, int pnum, int x, int y){

	// �����
	DrawFormatString(x, y, GetColor(255,255,255), "[��%d]��%d ��%d ��%d", pnum+1, tk->kyoku[kyoku_index].naki_count[pnum], tk->kyoku[kyoku_index].ankan_count[pnum] , tk->kyoku[kyoku_index].kakan_count[pnum]);

	// �����E�ڍ�
	for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[pnum]; tmp_i++){
		if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINKO){
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "�|��%2d��%d",tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i]==MINSHUN){
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "�`�[%2d,%2d��%d",tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i],tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i]==ANKAN){
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "�Þ�%2d��%d",tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i]==MINKAN){
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "����%2d��%d",tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i]==KAKAN){
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "����%2d��%d",tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}else{
			DrawFormatString(tmp_i*100+x+150, y, GetColor(255,255,255), "�s��%2d��%d",tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i],0);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo���̏ڍ�(�T�u�����F�Ԕv�A�����A�Ҕv���)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_shanten(MJSTkinfo *tk, int x, int y, int pnum){

	// DrawFormatString(x, y, GetColor(255,255,255), "[��%d�Ҕv]",pnum+1);

	// �Ԕv�����A������
	DrawFormatString(x, y, GetColor(255,255,255), "[��%d]��%d,%d,%d��%d��%2d��%2d��%2d��%2d��%2d:", 
		       pnum+1, 
		       tk->ply_act_aka_count[pnum][0],   // �Ԕv�����ݎq
		       tk->ply_act_aka_count[pnum][1],   // �Ԕv�������q
		       tk->ply_act_aka_count[pnum][2],   // �Ԕv�������q
		       tk->naki_count_none_kakan[pnum],  // �v����
		       tk->shanten_total[pnum], 
		       tk->shanten_normal[pnum], tk->shanten_chitoi[pnum],tk->shanten_kokushi[pnum], tk->ply_act_machi_count[pnum]);

	// �Ҕv
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[pnum]; tmp_i++){
		DrawFormatString(x+320+tmp_i*25, y, GetColor(255,255,255), "%2d,", tk->ply_act_machi_hai[pnum][tmp_i]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo���̏ڍ�(�T�u�����FAct�v���)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_ply_actnaki_info(MJSTkinfo *tk, int x, int y, int pnum){

	// ���v���
	DrawFormatString(x, y, GetColor(255,255,255), "[��%d]", pnum+1);

	// ���A�N�V�����\��
	DisplayTkinfoDetail_sub_plyactInfo(tk, tk->ply_act_naki[pnum], x+50, y);

	// ���ڍ�
	DrawFormatString(x+125, y, GetColor(255,255,255), "��%2d��%2d��%d",
	tk->ply_naki_hai[pnum], 
	tk->ply_naki_idx[pnum], 
	tk->ply_naki_aka_count[pnum]);

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo���̏ڍ�(�T�u�����Ftkinfo�X�e�[�^�X)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_tkstat(MJSTkinfo *tk, LBTkSt tk_stat, int x, int y){

	// -----------------------------------------------------------
	// ����
	// -----------------------------------------------------------
	if( tk_stat == PLYNOACT){
			wsprintf(tmp_disp_msg, "��`�Ȃ�");   // 00: ���Ԃ̒�`�Ȃ�
	}else if( tk_stat == TAKUSTART){
			wsprintf(tmp_disp_msg, "��J�n�@");   // 01: ��J�n
	}else if( tk_stat == BAGIME){
			wsprintf(tmp_disp_msg, "�ꌈ�߁@");   // 02: �ꌈ��
	}else if( tk_stat == KYOKUSTART){
			wsprintf(tmp_disp_msg, "�ǊJ�n�@");   // 03: �ǊJ�n
	}else if( tk_stat == HAIPAI){
			wsprintf(tmp_disp_msg, "�z�v�@�@");   // 04: �z�v
	}else if( tk_stat == PLYACTTSUMOWAIT){
			wsprintf(tmp_disp_msg, "���̑҂�");   // 05: ���̔v�҂�
	}else if( tk_stat == PLYACTTSUMO){
			wsprintf(tmp_disp_msg, "���́@�@");   // 06: ���̔v���
	}else if( tk_stat == PLYRINSHAN){
			wsprintf(tmp_disp_msg, "��㎩��");   // 07: ���v���
	}else if( tk_stat == PLYACTSUTEWAIT){
			wsprintf(tmp_disp_msg, "�̔v�҂�");   // 08: ���̌�̎̔v�҂�
	}else if( tk_stat == PLYACTNAKISUTEWAIT){
			wsprintf(tmp_disp_msg, "�̑҂�");   // 09: ��̎̔v�҂�
	}else if( tk_stat == PLYACTSUTE){
			wsprintf(tmp_disp_msg, "�̔v�@�@");   // 10: �̔v
	}else if( tk_stat == PLYACTTSUMOGIRI){
			wsprintf(tmp_disp_msg, "���̐؂�");   // 11: ���̐؂�
	}else if( tk_stat == PLYACTNAKISUTE){
			wsprintf(tmp_disp_msg, "���̔v");   // 12: ���̔v
	}else if( tk_stat == PLYACTRIICH){
			wsprintf(tmp_disp_msg, "���[�`�@");   // 13: ���[�`�錾
	}else if( tk_stat == PLYRIICHACCEPTED){
			wsprintf(tmp_disp_msg, "���[�`��");   // 14: ���[�`�錾�󂯓���
	}else if( tk_stat == PLYTSUMOAGARI){
			wsprintf(tmp_disp_msg, "���̘a��");   // 15: ���̘a��
	}else if( tk_stat == PLYACTANKAN){
			wsprintf(tmp_disp_msg, "�Þȁ@�@");   // 16: �Þ�
	}else if( tk_stat == PLYACTKAKAN){
			wsprintf(tmp_disp_msg, "���ȁ@�@");   // 17: ����
	}else if( tk_stat == PLYACTNAKIWAIT){
			wsprintf(tmp_disp_msg, "���҂�");   // 18: ���҂�
	}else if( tk_stat == PLYACTRON){
			wsprintf(tmp_disp_msg, "�����a��");   // 19: �����a��
	}else if( tk_stat == PLYACTPON){
			wsprintf(tmp_disp_msg, "�|���@�@");   // 20: �|��
	}else if( tk_stat == PLYACTCHI){
			wsprintf(tmp_disp_msg, "�`�[�@�@");   // 21: �`�[
	}else if( tk_stat == PLYACTMINKAN){
			wsprintf(tmp_disp_msg, "���ȁ@�@");   // 22: ����
	}else if( tk_stat == TSUMOKANDORAOPEN){
			wsprintf(tmp_disp_msg, "���̃h��");   // 24: ���̎��J���h���\��
	}else if( tk_stat == SUTEKANDORAOPEN){
			wsprintf(tmp_disp_msg, "�̔v�h��");   // 25: �̔v���J���h���\��
	}else if( tk_stat == RYUKYOKU){
			wsprintf(tmp_disp_msg, "���ǁ@�@");   // 26: ����
	}else if( tk_stat == KYOKURESULT){
			wsprintf(tmp_disp_msg, "�ǌ��ʁ@");   // 26: �ǌ��ʕ\��
	}else if( tk_stat == KYOKUEND){
			wsprintf(tmp_disp_msg, "�ǏI���@");   // 26: �ǏI��
	}else if( tk_stat == TAKURESULT){
			wsprintf(tmp_disp_msg, "�쌋�ʁ@");   // 27: �쌋�ʕ\��
	}else if( tk_stat == TAKUEND){
			wsprintf(tmp_disp_msg, "��I���@");   // 28: ��I��
	}else if( tk_stat == TAKUERR){
			wsprintf(tmp_disp_msg, "��G���[");   // 29: ��G���[���
	}else{
			wsprintf(tmp_disp_msg, "�s���@�@");   // 99: �s��
	}

	// �A�N�V�������\��
	DrawFormatString(x, y, GetColor(255,255,255), "%s", tmp_disp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// tkinfo���̏ڍ�(�T�u�����Fply_act�X�e�[�^�X)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_plyactInfo(MJSTkinfo *tk, LBPAct tmp_act, int x, int y){

	// -----------------------------------------------------------
	// �v���[���̃A�N�V�����X�e�[�^�X
	// -----------------------------------------------------------
	if( tmp_act == NOACT){
			wsprintf(tmp_disp_msg, "ACT�Ȃ� �@"); // 00: �A�N�V�����Ȃ�
	}else if( tmp_act == ACTHAIPAI){
			wsprintf(tmp_disp_msg, "�z�v���@�@"); // 01: �z�v��
	}else if( tmp_act == ACTTSUMO){
			wsprintf(tmp_disp_msg, "���̔v���"); // 02: ���̔v���
	}else if( tmp_act == ACTRINSHAN){
			wsprintf(tmp_disp_msg, "���v���"); // 03: ���v���
	}else if( tmp_act == ACTSUTEWAIT){
			wsprintf(tmp_disp_msg, "�̔v�҂��@"); // 04: �̔v�҂�
	}else if( tmp_act == ACNAKITSUTEWAIT){
			wsprintf(tmp_disp_msg, "���̔v��"); // 05: ���̔v�҂�
	}else if( tmp_act == ACTSUTE){
			wsprintf(tmp_disp_msg, "�̔v�@�@�@"); // 06: �̔v
	}else if( tmp_act == ACTNAKISUTE){
			wsprintf(tmp_disp_msg, "���̔v�@"); // 07: ���̔v
	}else if( tmp_act == ACTTSUMOGIRI){
			wsprintf(tmp_disp_msg, "���̐؂�@"); // 08: ���̐؂�
	}else if( tmp_act == ACTRIICH){
			wsprintf(tmp_disp_msg, "���[�`�錾"); // 09: ���[�`�錾
	}else if( tmp_act == ACTTSUMOAGARI){
			wsprintf(tmp_disp_msg, "���̘a���@"); // 10: ���̘a���錾
	}else if( tmp_act == ACTNAKIWAIT){
			wsprintf(tmp_disp_msg, "���҂��@"); // 11: ���҂�
	}else if( tmp_act == ACTNONAKI){
			wsprintf(tmp_disp_msg, "���Ȃ��@"); // 12: �������Ȃ�
	}else if( tmp_act == ACTRON){
			wsprintf(tmp_disp_msg, "�����a���@"); // 13: �����a���錾
	}else if( tmp_act == ACTPON){
			wsprintf(tmp_disp_msg, "�|�����@"); // 14: �|�����錾
	}else if( tmp_act == ACTCHI){
			wsprintf(tmp_disp_msg, "�`�[���@"); // 15: �`�[���錾
	}else if( tmp_act == ACTMINKAN){
			wsprintf(tmp_disp_msg, "���Ȗ��@"); // 16: ���Ȗ��錾
	}else if( tmp_act == ACTANKAN){
			wsprintf(tmp_disp_msg, "�ÞȖ��@"); // 17: �ÞȖ��錾
	}else if( tmp_act == ACTKAKAN){
			wsprintf(tmp_disp_msg, "���Ȗ��@"); // 18: ���Ȗ��錾
	}else{
			wsprintf(tmp_disp_msg, "�s���@�@�@"); // 99: �s��
	}

	// �A�N�V�������\��
	DrawFormatString(x, y, GetColor(255,255,255), "%s", tmp_disp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// GUI���E// tkinfo���ڍ�(�T�u�����F��v����)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayTkinfoDetail_sub_tehai_count(MJSTkinfo *tk, int x, int y, int pnum){

	// ��v�����\��
	DrawFormatString(x, y, GetColor(255,255,255), "[��%d]%d��", pnum+1, tk->ply_act_tehaicount[pnum]);

}

/* ---------------------------------------------------------------------------------------------- */
// GUI���EGUI�N���C�A���g���[�h�̃X�e�[�^�X�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGuiClientMode(MJSGui *gui, int x, int y){

	// ���b�Z�[�W�ݒ�
	if( gui->cli_mode == GUI_MJAI_CLIENT_NO_MODE){
		wsprintf(tmp_disp_msg, "��ԂȂ��@�@�@");                // 00:��ԂȂ�
	}else if( gui->cli_mode == GUI_MJAI_NOTCONNECT){
		wsprintf(tmp_disp_msg, "�ڑ��O�҂��@�@");                // 01:�ڑ��O�҂�
	}else if( gui->cli_mode == GUI_MJAI_CONNECT_ACTION){
		wsprintf(tmp_disp_msg, "�ڑ������@�@�@");                // 02:�ڑ�����
	}else if( gui->cli_mode == GUI_MJAI_DISCONNECT){
		wsprintf(tmp_disp_msg, "�ؒf�����@�@�@");                // 04:�ؒf����
	}else if( gui->cli_mode == GUI_MJAI_ERR_CONNECT){
		wsprintf(tmp_disp_msg, "�ڑ����G���[�@");                // 05:Socket�ڑ����G���[
	}else if( gui->cli_mode == GUI_MJAI_WAIT_HELO_RESMES){
		wsprintf(tmp_disp_msg, "HELO�҂��@�@�@");                // 06:HELLO���N�G�X�g�҂�
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_START_RESMES){
		wsprintf(tmp_disp_msg, "��J�n�҂��@�@");                // 07:��J�n�҂�
	}else if( gui->cli_mode == GUI_MJAI_BAGIME){
		wsprintf(tmp_disp_msg, "�ꌈ�߁@�@�@�@");                // 08:�ꌈ��
	}else if( gui->cli_mode == GUI_MJAI_WAIT_KYOKU_START_RESMES){
		wsprintf(tmp_disp_msg, "�ǊJ�n�҂��@�@");                // 09:�ǊJ�n�҂�
	}else if( gui->cli_mode == GUI_MJAI_HAIPAI){
		wsprintf(tmp_disp_msg, "�z�v�\��");                      // 10:�z�v�\��
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_RESMES){
		wsprintf(tmp_disp_msg, "�����M�҂�");                // 11:�샂�[�h�F��M���b�Z�[�W�҂�
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_PLYACT){
		wsprintf(tmp_disp_msg, "PLYACT�҂��@�@");                // 12:�샂�[�h�F�v���[���A�N�V�����҂�
	}else if( gui->cli_mode == GUI_MJAI_WAIT_SED_MES){
		wsprintf(tmp_disp_msg, "���M�҂��@�@�@");                // 13:�샂�[�h�F���b�Z�[�W���M�̏����҂�����
	}else if( gui->cli_mode == GUI_MJAI_ERR_RES_MES){
		wsprintf(tmp_disp_msg, "�G���[��M�@�@");                // 14:�샂�[�h�F�G���[���b�Z�[�W��M�����
	}else if( gui->cli_mode == GUI_MJAI_KYOKUEND){
		wsprintf(tmp_disp_msg, "�ǏI���\���@�@");                // 15:�ǌ��ʁF�ǏI������
	}else if( gui->cli_mode == GUI_MJAI_KYOKUEND_SED_MES){
		wsprintf(tmp_disp_msg, "�ǏI�����M�҂�");                // 16:�ǌ��ʁF�ǏI�����̊m�F���b�Z�[�W���M�̑҂�����
	}else if( gui->cli_mode == GUI_MJAI_TAKURESULT){
		wsprintf(tmp_disp_msg, "�쌋�ʕ\���@�@");                // 17:�쌋�ʁF�쌋�ʏ���
	}else if( gui->cli_mode == GUI_MJAI_END_MODE){
		wsprintf(tmp_disp_msg, "��I���@�@");                    // 18:�I�����[�h
	}else{
		wsprintf(tmp_disp_msg, "�s���@�@");                      // 99:��O���[�h
	}

	// GUI���\��
	DrawFormatString(x, y, GetColor(255,255,255), "[Stat]%s", tmp_disp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// ��v���ڍ�(ply�N���X���\��)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayPlyTehaiDetail(MJSTkinfo *tk, MJSPlayer *ply, int pnum){

	// -----------------------------------------------------------
	// ����\��
	// -----------------------------------------------------------

	if(ply[pnum].ie == 0){
		DrawFormatString(SPACE_XSIZE, PLY_YSTART-17, GetColor(255,255,255), "[��%d][����%d]����", 
					ply[pnum].ply_num+1, 
					ply[pnum].ply_num_shimo+1);
	}else if(ply[pnum].ie == 1){
		DrawFormatString(SPACE_XSIZE, PLY_YSTART-17, GetColor(255,255,255), "[��%d][����%d]���", 
					ply[pnum].ply_num+1, 
					ply[pnum].ply_num_shimo+1);
	}else if(ply[pnum].ie == 2){
		DrawFormatString(SPACE_XSIZE, PLY_YSTART-17, GetColor(255,255,255), "[��%d][����%d]����", 
					ply[pnum].ply_num+1, 
					ply[pnum].ply_num_shimo+1);
	}else if(ply[pnum].ie == 3){
		DrawFormatString(SPACE_XSIZE, PLY_YSTART-17, GetColor(255,255,255), "[��%d][����%d]�k��", 
					ply[pnum].ply_num+1, 
					ply[pnum].ply_num_shimo+1);
	}

	// �Ԕv���
	DrawFormatString(SPACE_XSIZE, PLY_YSTART, GetColor(255,255,255), "����%d �ԓ�%d �ԍ�%d", 
				ply[pnum].aka_count[0], 
				ply[pnum].aka_count[1], 
				ply[pnum].aka_count[2]);

	//-----------------------------------------------------------
	// �̔v���\��(���̂���p�^�[��)
	//-----------------------------------------------------------
	if (tk->stat == PLYACTTSUMO        || 
	    tk->stat == PLYACTSUTEWAIT     || 
		tk->stat == PLYACTNAKISUTEWAIT || 
		tk->stat == PLYACTRIICH        ){ 

		// ���̂���p�^�[���ڍ׏��
		DisplayPlyTehaiDetailTsumoAri(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART);

	//-----------------------------------------------------------
	// �̔v���\��(���̂Ȃ��p�^�[��)
	//-----------------------------------------------------------

	}else if( tk->stat == PLYACTSUTE      || 
	          tk->stat == PLYACTTSUMOGIRI || 
	          tk->stat == PLYACTNAKISUTE  || 
	          tk->stat == PLYACTNAKIWAIT  || 
	          tk->stat == HAIPAI          || 
	          tk->stat == PLYACTANKAN     || 
	          tk->stat == PLYACTKAKAN     ){

		// ���̂Ȃ��p�^�[���ڍ׏��
		DisplayPlyTehaiDetailTsumoNashi(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART);

	//-----------------------------------------------------------
	// �̔v���\��(�a���p�^�[��)
	//-----------------------------------------------------------

	}else if(tk->stat == PLYTSUMOAGARI || tk->stat == PLYACTRON){

		// �a�����
		DrawFormatString(SPACE_XSIZE, PLY_YSTART+ 90, GetColor(255,255,255), "�v���[���a��");

	//-----------------------------------------------------------
	// �̔v���\��(��O����)
	//-----------------------------------------------------------

	}else{

		// �f�o�O�p
		DrawFormatString(SPACE_XSIZE, PLY_YSTART+ 90, GetColor(255,255,255), "��O���");

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ply��v�̏ڍ׏��(���̗L�莞)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayPlyTehaiDetailTsumoAri(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y){

	// -----------------------------------------------------------
	// ��v�\��
	// -----------------------------------------------------------

	// ��v�e�[�u���X�V����
	ply[pnum].settehaitbl();

	// ���̂����v�\��
	dparts->DispActTehaiParts( SPACE_XSIZE, PLY_YSTART+40,
		                  ply[pnum].tehai_count,
		                  ply[pnum].tehaitbl,
		                  ply[pnum].tehaitbl_aka, 
		                  ply[pnum].ply_tsumo_hai,                         // ���̔v
	                      ply[pnum].ply_tsumo_aka,                         // ���̐�
	                      EXCEPT_VALUE,                                    // �̔v�F�Ȃ�
	                      EXCEPT_VALUE, EXCEPT_VALUE, false);              // �J�[�\���I���F�Ȃ�

	// -----------------------------------------------------------
	// �N���v�\��
	// -----------------------------------------------------------
	dparts->DispAllSarashiParts(600, PLY_YSTART+40,    // XY�ʒu
	ply[pnum].naki_count,          // �����v�ʎq��
	ply[pnum].naki_stat,           // �����
	ply[pnum].naki_hai,            // ���v
	ply[pnum].naki_idx,            // �`�[���̓��v
	ply[pnum].naki_aka             // �Ԕv�̐�
	);

	//-----------------------------------------------------------
	// �������
	//-----------------------------------------------------------
	DrawFormatString(SPACE_XSIZE+150, PLY_YSTART-17, GetColor(255,255,255), "�N���v%d�ʎq �ʏ�%d����(�ő�L���v%d��) ����%d���� ���m%d����", 
				ply[pnum].naki_count,
				ply[pnum].shanten_normal, 
				ply[pnum].yuko_max_count, 
				ply[pnum].shanten_chitoi, 
				ply[pnum].shanten_kokushi);

	// ���̂���\�L
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+19, GetColor(255,255,255), "��v���F���̗L��");

	//-----------------------------------------------------------
	// �̔v��␔
	//-----------------------------------------------------------

	// ��␔
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+80, GetColor(255,255,255), "�̔v���%d��", ply[pnum].sutekoho_count);

	// �ꗗ�\��
	if(ply[pnum].sutekoho_count > 7){

		// �̔v���(���i�\��)
		for(int tmp_i = 0; tmp_i < 7; tmp_i++){
			DisplaySutekoho(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART+100+tmp_i*40, tmp_i);
		}

		// �̔v���(�E�i�\��)
		for(int tmp_i = 7; tmp_i < ply[pnum].sutekoho_count; tmp_i++){
			DisplaySutekoho(tk, ply, pnum, SPACE_XSIZE+510, PLY_YSTART+100+(tmp_i-7)*40, tmp_i);
		}

	}else{

		// �̔v���(���i�\��)
		for(int tmp_i = 0; tmp_i < ply[pnum].sutekoho_count; tmp_i++){
			DisplaySutekoho(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART+100+tmp_i*40, tmp_i);
		}

	}

	//-----------------------------------------------------------
	// �ŏI�̔v���
	//-----------------------------------------------------------
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+400, GetColor(255,255,255), "�̔v���");
	dparts->DispHai( SPACE_XSIZE+80, PLY_YSTART+380, ply[pnum].sutekoho_hai[ply[pnum].fixed_sutekoho_num], false, false, 0, 0);

	//-----------------------------------------------------------
	// �A�N�V�����\��
	//-----------------------------------------------------------
	if( ply[pnum].ply_act == ACTSUTE){
		wsprintf(tmp_disp_msg, "�̔v�@�@");

		// �v�\��
		if(ply[pnum].ply_sute_aka == true){
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, true, false, 0, 0);
		}else{
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, false, false, 0, 0);
		}

	}else if(ply[pnum].ply_act == ACTTSUMOGIRI){

		// �A�N�V�����\��
		wsprintf(tmp_disp_msg, "���̐؂�");

		// �v�\��
		if(ply[pnum].ply_sute_aka == true){
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, true, false, 0, 0);
		}else{
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, false, false, 0, 0);
		}

	}else if(ply[pnum].ply_act == ACTNAKISUTE){

		// �A�N�V�����\��
		wsprintf(tmp_disp_msg, "���̂�");

		// �v�\��
		if(ply[pnum].ply_sute_aka == true){
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, true, false, 0, 0);
		}else{
			dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_sute_hai, false, false, 0, 0);
		}

	}else if(ply[pnum].ply_act == ACTRIICH){

		// �A�N�V�����\��
		wsprintf(tmp_disp_msg, "���[�`�@");

	}else if(ply[pnum].ply_act == ACTANKAN){

		// �A�N�V�����\��
		wsprintf(tmp_disp_msg, "�Þȁ@�@");

		// �v�\��
		dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_naki_idx, false, false, 0, 0);

	}else if(ply[pnum].ply_act == ACTKAKAN){

		// �A�N�V�����\��
		wsprintf(tmp_disp_msg, "���ȁ@�@");

		// �v�\��
		dparts->DispHai( 270, PLY_YSTART+380, ply[pnum].ply_naki_idx, false, false, 0, 0);

	}else{

		// �A�N�V�����\��
		wsprintf(tmp_disp_msg, "�s���@�@");

	}

	// �A�N�V�����\��
	DrawFormatString(150, PLY_YSTART+400, GetColor(255,255,255), "Act�F%s", tmp_disp_msg);

	//-----------------------------------------------------------
	// �\���v�ꗗ
	//-----------------------------------------------------------
	DisplayOpenhai(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART+450);

	//-----------------------------------------------------------
	// ��������
	//-----------------------------------------------------------
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+490, GetColor(255,255,255), "��������(ply) :%d�~���b",ply[pnum].action_timestamp2 - ply[pnum].action_timestamp1);    // ��������

}

/* ---------------------------------------------------------------------------------------------- */
// ply��v�̏ڍ׏��(���̖�����)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayPlyTehaiDetailTsumoNashi(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y){

	// -----------------------------------------------------------
	// ��v�\��
	// -----------------------------------------------------------

	// ��v�e�[�u���X�V����
	ply[pnum].settehaitbl();

	// ���̂Ȃ���v�\��
	dparts->DispActTehaiParts( SPACE_XSIZE, PLY_YSTART+40,
		                  ply[pnum].tehai_count,
		                  ply[pnum].tehaitbl,
		                  ply[pnum].tehaitbl_aka, 
		                  EXCEPT_VALUE,                                    // ���̔v�F�Ȃ�
	                      false,                                           // ���̐ԁE�Ȃ�
	                      EXCEPT_VALUE,                                    // �̔v�F�Ȃ�
	                      EXCEPT_VALUE, EXCEPT_VALUE, false);              // �J�[�\���I���F�Ȃ�

	// -----------------------------------------------------------
	// �N���v�\��
	// -----------------------------------------------------------
	dparts->DispAllSarashiParts(600, PLY_YSTART+40,    // XY�ʒu
	ply[pnum].naki_count,          // �����v�ʎq��
	ply[pnum].naki_stat,           // �����
	ply[pnum].naki_hai,            // ���v
	ply[pnum].naki_idx,            // �`�[���̓��v
	ply[pnum].naki_aka             // �Ԕv�̐�
	);

	// -----------------------------------------------------------
	// �������
	// -----------------------------------------------------------

	DrawFormatString(SPACE_XSIZE+150, PLY_YSTART-17, GetColor(255,255,255), "�N���v%d�ʎq �ʏ�%d���� ����%d���� ���m%d����", 
				ply[pnum].naki_count,
				ply[pnum].shanten_normal, 
				ply[pnum].shanten_chitoi, 
				ply[pnum].shanten_kokushi);

	// ���̖����\�L
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+19, GetColor(255,255,255), "��v���F���̖���");

	// �L���v
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+ 90, GetColor(255,255,255), "������%d��"  , ply[pnum].atama_count);
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+110, GetColor(255,255,255), "�����c��%d��", ply[pnum].mentsu_count);
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+130, GetColor(255,255,255), "�^�[�c��%d��", ply[pnum].taatsu_count);

	// �L���v���
	x=5;
	y=250;

	// �ݎq
	DrawFormatString(x+127, y+10, GetColor(255,255,255), "m");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai_13mai[tmp_j+1] == true){
			DrawFormatString(x+135+tmp_j*8, y+10, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// ���q
	DrawFormatString(x+227, y+10, GetColor(255,255,255), "p");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai_13mai[tmp_j+11] == true){
			DrawFormatString(x+235+tmp_j*8, y+10, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// ���q
	DrawFormatString(x+327, y+10, GetColor(255,255,255), "s");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai_13mai[tmp_j+21] == true){
			DrawFormatString(x+335+tmp_j*8, y+10, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// ���v
	DrawFormatString(x+427, y+10, GetColor(255,255,255), "z");
	for(int tmp_j = 0; tmp_j < 7; tmp_j++){
		if(ply[pnum].yuko_hai_13mai[tmp_j+31] == true){
			DrawFormatString(x+435+tmp_j*8, y+10, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// �����
	DrawFormatString(SPACE_XSIZE, 300, GetColor(255,255,255), "����▇��%d��", ply[pnum].nakikoho_tbl_count);

	// ���e�[�u�����
	for(int tmp_i = 0; tmp_i < ply[pnum].nakikoho_tbl_count; tmp_i++){

		// 1�i�ځE�v�ԍ�
		DrawFormatString(SPACE_XSIZE+tmp_i*100, 320, GetColor(255,255,255), "�v%d,IDX%d", ply[pnum].nakikoho_tbl_hai[tmp_i], ply[pnum].nakikoho_tbl_idx[tmp_i]);

		// 2�i�ځE�A�N�V����
		if( ply[pnum].nakikoho_tbl_act[tmp_i] == ACTRON){
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 340, GetColor(255,255,255), "Act:����");
		}else if( ply[pnum].nakikoho_tbl_act[tmp_i] == ACTPON){
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 340, GetColor(255,255,255), "Act:�|��");
		}else if( ply[pnum].nakikoho_tbl_act[tmp_i] == ACTCHI){
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 340, GetColor(255,255,255), "Act:�`�[");
		}else{
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 340, GetColor(255,255,255), "Act:�s��");
		}

		// 3�i�ځE���̗L��
		if( ply[pnum].nakikoho_tbl_yesno[tmp_i] == true){
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 360, GetColor(255,255,255), "�L");
		}else{
			DrawFormatString(SPACE_XSIZE+tmp_i*100, 360, GetColor(255,255,255), "��");
		}

	}

	//-----------------------------------------------------------
	// �\���v�ꗗ
	//-----------------------------------------------------------
	DisplayOpenhai(tk, ply, pnum, SPACE_XSIZE, PLY_YSTART+450);

	//-----------------------------------------------------------
	// ��������
	//-----------------------------------------------------------
	DrawFormatString(SPACE_XSIZE, PLY_YSTART+490, GetColor(255,255,255), "��������(ply) :%d�~���b",ply[pnum].action_timestamp2 - ply[pnum].action_timestamp1);    // ��������

}

/* ---------------------------------------------------------------------------------------------- */
// �̔v�����
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplaySutekoho(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y, int sutenum){

	// �p�[�c�\��(���v)
	dparts->DispHai( x, y, ply[pnum].sutekoho_hai[sutenum], false, false, 0, 0);

	// ���Ғl
	DrawFormatString(x+25, y+STRING_YSIZE+2, GetColor(255,255,0), "���Ғl%6d", 1300);

	// ��␔�\��
	DrawFormatString(x+25, y, GetColor(255,255,255), "%d��%2d��%2d��%dp", 
		ply[pnum].sutekoho_shanten[sutenum], 
		ply[pnum].yuko_haishu_count[sutenum],
		ply[pnum].yuko_hai_count[sutenum],
		ply[pnum].sutekoho_priority[sutenum]);

	// ���v - �ݎq
	DrawFormatString(x+138, y, GetColor(255,255,255), "m");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai[sutenum][tmp_j+1] == true){
			DrawFormatString(x+148+tmp_j*8, y, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// ���v - ���q
	DrawFormatString(x+238, y, GetColor(255,255,255), "p");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai[sutenum][tmp_j+11] == true){
			DrawFormatString(x+248+tmp_j*8, y, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// ���v - ���q
	DrawFormatString(x+338, y, GetColor(255,255,255), "s");
	for(int tmp_j = 0; tmp_j < 9; tmp_j++){
		if(ply[pnum].yuko_hai[sutenum][tmp_j+21] == true){
			DrawFormatString(x+348+tmp_j*8, y, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

	// ���v - ���v
	DrawFormatString(x+438, y, GetColor(255,255,255), "z");
	for(int tmp_j = 0; tmp_j < 7; tmp_j++){
		if(ply[pnum].yuko_hai[sutenum][tmp_j+31] == true){
			DrawFormatString(x+448+tmp_j*8, y, GetColor(255,255,255), "%d",tmp_j+1);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �\���v(open_haiparts)����
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayOpenhai(MJSTkinfo *tk, MJSPlayer *ply, int pnum, int x, int y){

	// ���v - �ݎq
	DrawFormatString(x, y+20, GetColor(255,255,255), "m");
	for(int tmp_i = 1; tmp_i < 10; tmp_i++){
		DrawFormatString(x+10+tmp_i*8, y, GetColor(255,255,255), "%d",tmp_i);
		DrawFormatString(x+10+tmp_i*8, y+20, GetColor(255,255,255), "%d",ply[pnum].open_haiparts_count[tmp_i]);
	}

	// ���v - ���q
	DrawFormatString(x+100, y+20, GetColor(255,255,255), "p");
	for(int tmp_i = 1; tmp_i < 10; tmp_i++){
		DrawFormatString(x+110+tmp_i*8, y, GetColor(255,255,255), "%d",tmp_i);
		DrawFormatString(x+110+tmp_i*8, y+20, GetColor(255,255,255), "%d",ply[pnum].open_haiparts_count[tmp_i+10]);
	}

	// ���v - ���q
	DrawFormatString(x+200, y+20, GetColor(255,255,255), "s");
	for(int tmp_i = 1; tmp_i < 10; tmp_i++){
		DrawFormatString(x+210+tmp_i*8, y, GetColor(255,255,255), "%d",tmp_i);
		DrawFormatString(x+210+tmp_i*8, y+20, GetColor(255,255,255), "%d",ply[pnum].open_haiparts_count[tmp_i+20]);
	}

	// ���v - ���v
	DrawFormatString(x+300, y+20, GetColor(255,255,255), "z");
	for(int tmp_i = 1; tmp_i < 8; tmp_i++){
		DrawFormatString(x+310+tmp_i*8, y, GetColor(255,255,255), "%d",tmp_i);
		DrawFormatString(x+310+tmp_i*8, y+20, GetColor(255,255,255), "%d",ply[pnum].open_haiparts_count[tmp_i+30]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �Ǐ��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuInfo(MJSTkinfo *tk, int kyoku_index){

	//-----------------------------------------------------------
	// �f�o�O�p
	//-----------------------------------------------------------
	if (tk->kyoku[kyoku_index].kyoku < 0 || tk->kyoku[kyoku_index].kyoku > 11){
		tk->kyoku[kyoku_index].kyoku = 0;
	}

	//-----------------------------------------------------------
	// �����`���̕\��
	//-----------------------------------------------------------
	if(tk->tkgame_type == TKGAME_HANCHAN){
		wsprintf(tmp_disp_msg,"������ %s %d�{��", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else if(tk->tkgame_type == TKGAME_TONPU){
		wsprintf(tmp_disp_msg,"������ %s %d�{��", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else if(tk->tkgame_type == TKGAME_1KYOKU){
		wsprintf(tmp_disp_msg,"��ǐ� %s %d�{��", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else if(tk->tkgame_type == TKGAME_MJAI){
		wsprintf(tmp_disp_msg,"Mjai�� %s %d�{��", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else if(tk->tkgame_type == TKGAME_MAXID_TEST){
		wsprintf(tmp_disp_msg,"���ؗp %s %d�{��", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else if(tk->tkgame_type == TKGAME_VIEWER){
		wsprintf(tmp_disp_msg,"�\���p %s %d�{��", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}else{
		wsprintf(tmp_disp_msg,"�s���@ %s %d�{��", dparts->kyokutbl[tk->kyoku[kyoku_index].kyoku], tk->kyoku[kyoku_index].tsumibo);
	}

	dparts->DispString( SPACE_XSIZE, 8 + STRING_YSIZE * 0, tmp_disp_msg);

	/*-----------------------------------------------------------*/
	// ���[�h�\��
	/*-----------------------------------------------------------*/
	if( tk->ply_hum_mode == 0 ){
		DrawFormatString(SPACE_XSIZE+230, 8 + STRING_YSIZE * 0, GetColor(255,255,255), "4Com��");
	}else{
		DrawFormatString(SPACE_XSIZE+230, 8 + STRING_YSIZE * 0, GetColor(255,255,255), "Hum�� ");
	}

	//-----------------------------------------------------------
	// ���[�`�_�E�c��v�\��
	//-----------------------------------------------------------
	wsprintf(tmp_disp_msg,"���[�`�_%d �c�v%d ���v%d", tk->kyoku[kyoku_index].riichbo, tk->remain_hai_count, tk->remain_rinshan_count);
	dparts->DispString( SPACE_XSIZE, 8 + STRING_YSIZE * 1, tmp_disp_msg);

	//-----------------------------------------------------------
	// �ő�Ԕv����
	//-----------------------------------------------------------
	wsprintf(tmp_disp_msg,"MAX�� ��%d ��%d ��%d", tk->aka_max[0], tk->aka_max[1], tk->aka_max[2]);
	dparts->DispString( SPACE_XSIZE+230, 8 + STRING_YSIZE * 1, tmp_disp_msg);

	//-----------------------------------------------------------
	// �J�n����
	//-----------------------------------------------------------
	wsprintf(tmp_disp_msg,"�J�n:%s %s", tk->startdate, tk->starttime);
	dparts->DispString( SPACE_XSIZE, 8 + STRING_YSIZE * 2, tmp_disp_msg);

	//-----------------------------------------------------------
	// �����V�[�h
	//-----------------------------------------------------------
//	if(tk->kyoku[kyoku_index].seed_num != 0){
		wsprintf(tmp_disp_msg,"����SEED:%10d", tk->kyoku[kyoku_index].seed_num);
		dparts->DispString( SPACE_XSIZE + 230, 8 + STRING_YSIZE * 2, tmp_disp_msg);
//	}

}

/* ---------------------------------------------------------------------------------------------- */
// �v���[�����
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispPlyInfo(MJSTkinfo *tk, int kyoku_index, int pnum){

	//-----------------------------------------------------------
	// 1�s��
	//-----------------------------------------------------------

	// �v���[����
	DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE, GetColor(255,255,255), "[��%d]%s", pnum+1, tk->plyname[pnum]);

	// �ƕ\��
	if(tk->kyoku[kyoku_index].ie[pnum] == 0){
		DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "����");
	}else if(tk->kyoku[kyoku_index].ie[pnum] == 1){
		DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "���");
	}else if(tk->kyoku[kyoku_index].ie[pnum] == 2){
		DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "����");
	}else if(tk->kyoku[kyoku_index].ie[pnum] == 3){
		DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "�k��");
	}else{
		DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "�s��");
	}

	//-----------------------------------------------------------
	// 2�s��
	//-----------------------------------------------------------

	// ���_
	DrawFormatString(840, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_start_score[pnum]);

	//-----------------------------------------------------------
	// 3�s��
	//-----------------------------------------------------------

	// �e���p�C���
	if (tk->stat == RYUKYOKU){

		// �e���p�C���ʂ�\������
		if(tk->kyoku[kyoku_index].ply_agari_yk[0].ply_tempai_flg[pnum] == true){
			DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "���v");
		}else{
			DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "�s��");
		}

			// �e���p�C�l��
			DrawFormatString(800, PLY_YSTART+4*PLY_YSIZE, GetColor(255,255,255), "���v%d�l", tk->kyoku[kyoku_index].ply_agari_yk[0].ply_tempai_count);

	// �v���[��ID
	}else{

		// Mjai���[�h�ł���Ȃ�
		if(tk->tkgame_type == TKGAME_MJAI){
			DrawFormatString(800, PLY_YSTART+pnum*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "Ply_id:%d", tk->ply_mjai_id[pnum]);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �v���[���A�N�V�������\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActNumInfo(MJSTkinfo *tk, int x, int y, int kyoku_index, int actid){

	// �Ǐ��
	DrawFormatString(x   , y-32, GetColor(255,255,255), "��ID %2d"  ,kyoku_index );

	// �A�N�V����ID
	DrawFormatString(x+80, y-32, GetColor(255,255,255), "ACTID %3d" ,actid);

	// �A�N�V�������̒l�������
	if (actid > 0){

		// TKINFO�̃X�e�[�^�X���
		DisplayTkinfoDetail_sub_tkstat(tk, tk->kyoku[kyoku_index].act_stat[actid], x, y-16);

		// �v���\���E�Ԕv
		if ( tk->kyoku[kyoku_index].act_aka[actid] == true){
			DrawFormatString(x+80, y-16, GetColor(255,255,255), "�v%2d��,IDX%2d", tk->kyoku[kyoku_index].act_hai[actid], 0);
		}else{
			DrawFormatString(x+80, y-16, GetColor(255,255,255), "�v%2d��,IDX%2d", tk->kyoku[kyoku_index].act_hai[actid], 0);
		}

/*
		if ( tk->kyoku[kyoku_index].act_aka[actid] == true){
			DrawFormatString(x+80, y-16, GetColor(255,255,255), "�v�ԍ��F%3d�@�Ԕv�@", tk->kyoku[kyoku_index].act_hai[actid]);
		}else{
			DrawFormatString(x+80, y-16, GetColor(255,255,255), "�v�ԍ��F%3d�@�ʏ�v", tk->kyoku[kyoku_index].act_hai[actid]);
		}
*/
		// �A�N�V�����v���[���\��
		       if( tk->kyoku[kyoku_index].act_ply[actid] > -1 && tk->kyoku[kyoku_index].act_ply[actid] < 4){
			DrawFormatString(x, y, GetColor(255,255,255), "Act_ply  �F[��%d]", tk->kyoku[kyoku_index].act_ply[actid]+1 );
		 }else if( tk->kyoku[kyoku_index].act_ply[actid] == 4){
			DrawFormatString(x, y, GetColor(255,255,255), "Act_ply  �F[ - ]", tk->kyoku[kyoku_index].act_ply[actid]+1 );
		 }else {
			DrawFormatString(x, y, GetColor(255,255,255), "Act_ply  �F[��O]", tk->kyoku[kyoku_index].act_ply[actid]+1 );
		 }

		// ���A�N�V�����v���[���\��
		      if( tk->kyoku[kyoku_index].react_ply[actid] > -1 && tk->kyoku[kyoku_index].react_ply[actid] < 4){
			DrawFormatString(x+150, y, GetColor(255,255,255), "ReAct_ply�F[��%d]", tk->kyoku[kyoku_index].react_ply[actid]+1 );
		}else if( tk->kyoku[kyoku_index].react_ply[actid] == 4){
			DrawFormatString(x+150, y, GetColor(255,255,255), "ReAct_ply�F[ - ]",  tk->kyoku[kyoku_index].react_ply[actid]+1 );
		}else{
			DrawFormatString(x+150, y, GetColor(255,255,255), "ReAct_ply�F[��O]", tk->kyoku[kyoku_index].react_ply[actid]+1 );
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// TKINFO���̕\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispTakuStat(MJSTkinfo *tk, int x, int y){

	// TKINFO�̃X�e�[�^�X���
	DisplayTkinfoDetail_sub_tkstat(tk, tk->stat, x, y);

	// ����
	DrawFormatString(x+90, y, GetColor(255,255,255), "���ԁF[��%d]", tk->ply_turn+1);

	// Ply�A�N�V����
	DisplayTkinfoDetail_sub_plyactInfo(tk, tk->ply_act, x+250, y);

	// Hum�̔v�ʒu�ԍ�
	DrawFormatString(x+400, y, GetColor(255,255,255), "Hum�̈ʒu�F%3d" ,tk->ply_tbl_hum_sutehai_statnum);

}

/* ---------------------------------------------------------------------------------------------- */
// ����N���X(tkinfo�N���X)���
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispTkInfoStat(MJSTkinfo *tk, int x, int y){

	// �v���[�����Ƃ̖��A�N�V����
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){
		DisplayTkinfoDetail_sub_ply_actnaki_info(tk, x+255*tmp_pnum, y, tmp_pnum);
	}

	// �v���[�����Ƃ̎�v���
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){
		DisplayTkinfoDetail_sub_tehai(tk, x, y+STRING_YSIZE*(1+tmp_pnum),tmp_pnum);
	}

	// �Ԕv�����A�������F��1
	DrawFormatString(x, y+STRING_YSIZE*5, GetColor(255,255,255), "[��1]��%d,%d,%d��%d��%2d��%2d��%2d��%2d��%2d:", 
	       tk->ply_act_aka_count[0][0], tk->ply_act_aka_count[0][1], tk->ply_act_aka_count[0][2],
	       tk->naki_count_none_kakan[0], tk->shanten_total[0], tk->shanten_normal[0], tk->shanten_chitoi[0],tk->shanten_kokushi[0], tk->ply_act_machi_count[0]);

	// �Ҕv�F��1
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[0]; tmp_i++){
		DrawFormatString(x+320+tmp_i*25,   y+STRING_YSIZE*5, GetColor(255,255,255), "%2d,", tk->ply_act_machi_hai[0][tmp_i]);
	}

	// �Ԕv�����A�������F��2
	DrawFormatString(x+500, y+STRING_YSIZE*5, GetColor(255,255,255), "[��2]��%d,%d,%d��%d��%2d��%2d��%2d��%2d��%2d:", 
	       tk->ply_act_aka_count[1][0], tk->ply_act_aka_count[1][1], tk->ply_act_aka_count[1][2],
	       tk->naki_count_none_kakan[1], tk->shanten_total[1], tk->shanten_normal[1], tk->shanten_chitoi[1],tk->shanten_kokushi[1], tk->ply_act_machi_count[1]);

	// �Ҕv�F��2
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[1]; tmp_i++){
		DrawFormatString(x+820+tmp_i*25,   y+STRING_YSIZE*5, GetColor(255,255,255), "%2d,", tk->ply_act_machi_hai[1][tmp_i]);
	}

	// �Ԕv�����A�������F��3
	DrawFormatString(x, y+STRING_YSIZE*6, GetColor(255,255,255), "[��3]��%d,%d,%d��%d��%2d��%2d��%2d��%2d��%2d:", 
	       tk->ply_act_aka_count[2][0], tk->ply_act_aka_count[2][1], tk->ply_act_aka_count[2][2],
	       tk->naki_count_none_kakan[2], tk->shanten_total[2], tk->shanten_normal[2], tk->shanten_chitoi[2],tk->shanten_kokushi[2], tk->ply_act_machi_count[2]);

	// �Ҕv�F��3
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[2]; tmp_i++){
		DrawFormatString(x+320+tmp_i*25,   y+STRING_YSIZE*6, GetColor(255,255,255), "%2d,", tk->ply_act_machi_hai[2][tmp_i]);
	}

	// �Ԕv�����A�������F��4
	DrawFormatString(x+500, y+STRING_YSIZE*6, GetColor(255,255,255), "[��4]��%d,%d,%d��%d��%2d��%2d��%2d��%2d��%2d:", 
	       tk->ply_act_aka_count[3][0], tk->ply_act_aka_count[3][1], tk->ply_act_aka_count[3][2],
	       tk->naki_count_none_kakan[3], tk->shanten_total[3], tk->shanten_normal[3], tk->shanten_chitoi[3],tk->shanten_kokushi[3], tk->ply_act_machi_count[3]);

	// �Ҕv�F��4
	for(int tmp_i = 0; tmp_i < tk->ply_act_machi_count[3]; tmp_i++){
		DrawFormatString(x+820+tmp_i*25,   y+STRING_YSIZE*6, GetColor(255,255,255), "%2d,", tk->ply_act_machi_hai[3][tmp_i]);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI�N���X���
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispGuiInfo(MJSGui *gui, int x, int y){

	//-----------------------------------------------------------
	// GUI�X�e�[�^�X(0�s��)
	//-----------------------------------------------------------

	// GUI���E���C���X�e�[�^�X
	if(gui->gui_main_stat == GUI_NO_MAIN_STAT){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]���[�h���ݒ�");
	}else if(gui->gui_main_stat == GUI_PLAYING_INIT){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]�v���C���[�h�O����");
	}else if(gui->gui_main_stat == GUI_PLAYING){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]�v���C���[�h");
	}else if(gui->gui_main_stat == GUI_PLAYING_POST){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]�v���C���[�h�㏈��");
	}else if(gui->gui_main_stat == GUI_RUNNING_INIT){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]���؃��[�h�O����");
	}else if(gui->gui_main_stat == GUI_RUNNING){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]���؃��[�h");
	}else if(gui->gui_main_stat == GUI_RUNNING_POST){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]���؃��[�h�㏈��");
	}else if(gui->gui_main_stat == GUI_CLIENT_INIT){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]�N���C�A���g�O����");
	}else if(gui->gui_main_stat == GUI_CLIENT){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]�N���C�A���g���[�h");
	}else if(gui->gui_main_stat == GUI_CLIENT_POST){
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]�N���C�A���g�㏈��");
	}else{
		DrawFormatString(x, y, GetColor(255,255,255), "[Main]��O����");
	}

	// GUI���E�샂�[�h
	DisplayGuiTakuMode(gui, x+250, y);

	// GUI���E��v���[�h
	DisplayGuiTehaiMode(gui, x+400, y);

	//-----------------------------------------------------------
	// ���v�����(1�s��)
	//-----------------------------------------------------------

	// �Þȏ��
	if(gui->gui_taku_mode == COMMON_PLAY_MODE){
		DrawFormatString( x,    y+STRING_YSIZE, GetColor(255,255,255), "[�Þ�]%2d,%2d,%2d", gui->naki_ankan_hai[0], gui->naki_ankan_hai[1], gui->naki_ankan_hai[2]);
	}

	// ���ȏ��
	if(gui->gui_taku_mode == COMMON_PLAY_MODE){
		DrawFormatString( x+130, y+STRING_YSIZE, GetColor(255,255,255), "[����]%2d,%2d,%2d", gui->naki_kakan_hai[0], gui->naki_kakan_hai[1], gui->naki_kakan_hai[2]);
	}

	// GUI���E�`�[���̏��
	DisplayGuiChiKoho(gui, x+260, y+STRING_YSIZE);

}

/* ---------------------------------------------------------------------------------------------- */
// GUI���EGUI�샂�[�h
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGuiTakuMode(MJSGui *gui, int x, int y){

	// GUI���EGUI�샂�[�h�\��
	      if(gui->gui_taku_mode == COMMON_PLAY_MODE){
		DrawFormatString(x, y, GetColor(255,255,255), "[���]��v�\���@");
	}else if( gui->gui_taku_mode == COMMON_BAGIME_MODE){
		DrawFormatString(x, y, GetColor(255,255,255), "[���]�ꌈ�߁@�@");
	}else if( gui->gui_taku_mode == COMMON_TAKURESULT_MODE){
		DrawFormatString(x, y, GetColor(255,255,255), "[���]�쌋�ʕ\��");
	}else if(gui->gui_taku_mode == COMMON_TKINFO_MODE){
		DrawFormatString(x, y, GetColor(255,255,255), "[���]TK�ڍׁ@�@");
	}else{
		DrawFormatString(x, y, GetColor(255,255,255), "[���]��O�����@");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI���EGUI��v���[�h
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGuiTehaiMode(MJSGui *gui, int x, int y){

	if(gui->gui_ply_tehai_mode == TEHAI_NORMAL){
		DrawFormatString(x, y, GetColor(255,255,255), "[��v]�ʏ��v�@");
	}else if(gui->gui_ply_tehai_mode == TEHAI_RIICHI_SUTEHAI){
		DrawFormatString(x, y, GetColor(255,255,255), "[��v]���[�`�I��");
	}else if(gui->gui_ply_tehai_mode == TEHAI_RIICHI_YUKO){
		DrawFormatString(x, y, GetColor(255,255,255), "[��v]���[�`�L��");
	}else if(gui->gui_ply_tehai_mode == TEHAI_ANKAN_KAKAN_SELECT){
		DrawFormatString(x, y, GetColor(255,255,255), "[��v]�É��ȑI��");
	}else if(gui->gui_ply_tehai_mode == TEHAI_CHI_SELECT){
		DrawFormatString(x, y, GetColor(255,255,255), "[��v]�`�[�I���@");
	}else{
		DrawFormatString(x, y, GetColor(255,255,255), "[��v]��O�����@");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI���E�`�[�����
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGuiChiKoho(MJSGui *gui, int x, int y){

	// �`�[���̌�
	DrawFormatString(x, y, GetColor(255,255,255), "[�`�v]%d��",gui->chihai_count);

	// �`�[�v���
	for(int tmp_i = 0; tmp_i < CHI_KOHO_COUNT_MAX; tmp_i++){
		// �L���ł����
//		if(gui->chihai_mode[tmp_i] == true){
			if (gui->chi_aka_count[tmp_i] > 0){
				DrawFormatString(x+tmp_i*90+80, y, GetColor(255,255,255), "%d:��:%2d��|", tmp_i, gui->chi_idx_hai[tmp_i]);
			}else{
				DrawFormatString(x+tmp_i*90+80, y, GetColor(255,255,255), "%d:��:%2d��|", tmp_i, gui->chi_idx_hai[tmp_i]);
			}
//		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// GUI���E�v�����O�`��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGuiLogType(MJSGui *gui, int x, int y){

	if( gui->gui_logtype == GUI_LOG_MJAILOG){
		DrawFormatString(x, y, GetColor(255,255,255), "[���O�`��]MJAI���O");
	}else if( gui->gui_logtype == GUI_LOG_MJSCORE){
		DrawFormatString(x, y, GetColor(255,255,255), "[���O�`��]���������O");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��v���C�����b�Z�[�W
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispTehaiLineMessage(MJSTkinfo *tk, MJSGui *gui, int x, int y){

	// gui_taku_mode���[�h���ƂɃ��b�Z�[�W�\��
	if(gui->gui_taku_mode == COMMON_PLAY_MODE){

		// gui_ply_tehai_mode���[�h���ƂɃ��b�Z�[�W�\��
		if(gui->gui_ply_tehai_mode == TEHAI_NORMAL || gui->gui_ply_tehai_mode == TEHAI_RIICHI_YUKO){

			// GUI���[�h�̏ꍇ
			if( tk->ply_hum_mode == 1 && 
			    tk->kyoku[tk->kyoku_index].act_ply[tk->kyoku[tk->kyoku_index].act_count] == HUM_PLY_SEKI_NUM ){

				// HUM���̘a��
				if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYTSUMOAGARI){
					DrawFormatString(x, y,    GetColor(255,255,255), "���߂łƂ��������܂�");
					DrawFormatString(x, y+STRING_YSIZE, GetColor(255,255,255), "���Ȃ��̎��̘a���ł�");

				// HUM�����a��
				}else if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTRON){
					DrawFormatString(x, y,    GetColor(255,255,255), "���߂łƂ��������܂�");
					DrawFormatString(x, y+STRING_YSIZE, GetColor(255,255,255), "���Ȃ��̃����a���ł�");

				// ���̃A�N�V�����̏ꍇ
				}else if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTTSUMO ||
				          tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYRINSHAN  ){

					// HUM�̎̔v���b�Z�[�W
					if(gui->gui_ply_tehai_mode == TEHAI_RIICHI_YUKO){
						DrawFormatString(x, y,    GetColor(255,255,255), "���[�`�錾���Ă܂�");
						DrawFormatString(x, y+STRING_YSIZE, GetColor(255,255,255), "�����̔v�����܂�");
					}else{
						DrawFormatString(x, y, GetColor(255,255,255), "�̔v�����Ă�������");
					}

				// ����̃A�N�V����
				// }else if( tk->stat == PLYACTSUTEWAIT || tk->stat == PLYACTNAKISUTEWAIT){
				}else if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTPON ||
				          tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTCHI ){
					DrawFormatString(x, y, GetColor(255,255,255), "����̎̔v�����Ă�������");

				// �̔v�A�N�V�����̏ꍇ
				}else if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTSUTE ||
				          tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTTSUMOGIRI ||
				          tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTNAKISUTE  ){
					DrawFormatString(x, y, GetColor(255,255,255), "�̔v���܂���");

				// ��O����
				}else{
					DrawFormatString(x, y, GetColor(255,255,255), "��O�����Fact_HUM_PLY_SEKI_NUM");
				}

			// ������Ԃ̏ꍇ
			}else{

				// COM���̘a��
				if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYTSUMOAGARI ){
					DrawFormatString(x, y, GetColor(255,255,255), "COM�v���[�������̘a���ł�");

				// COM�����a��
				}else if( tk->kyoku[tk->kyoku_index].act_stat[tk->kyoku[tk->kyoku_index].act_count] == PLYACTRON ){

					// �U��v���[����HUM
					if( tk->ply_hum_mode == 1 && tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].furikomi_ply_num == HUM_PLY_SEKI_NUM){
						DrawFormatString(x, y, GetColor(255,255,255), "�c�O�I���Ȃ����U�肱�݂܂���");
					}else{
						DrawFormatString(x, y, GetColor(255,255,255), "COM�v���[���������a���ł�");
					}

				// ���̑�����
				}else{
					DrawFormatString(x, y, GetColor(255,255,255), "COM�v���[��������");
				}

			}

		// ���[�`���[�h
		}else if(gui->gui_ply_tehai_mode == TEHAI_RIICHI_SUTEHAI){
			DrawFormatString(x, y, GetColor(255,255,255), "���[�`�錾��̎̔v��I�����Ă�������");
		// �`�[�錾���[�h
		}else if(gui->gui_ply_tehai_mode == TEHAI_CHI_SELECT){
			DrawFormatString(x, y, GetColor(255,255,255), "�`�[�v��錾���Ă�������");
		// ��O����
		}else{
			DrawFormatString(x, y, GetColor(255,255,255), "��O�����Fgui_ply_tehai_mode");
		}

	// �I���m�F���b�Z�[�W
	}else if(gui->gui_taku_mode == COMMON_END_CHECK_MODE){
		DrawFormatString(x, y, GetColor(255,255,255), "�������I�����܂�");
	// ��O����
	}else{
		DrawFormatString(x, y, GetColor(255,255,255), "��O�����Fgui_taku_mode");
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V������v�̕\��(COM�p�X�N�G�A)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActTehaiCom_square(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum, int msx, int msy){

	// �`�F�b�N�t���O
	int tmp_chi_num = 0;
	int sute_chk    = 0;

	// �v��X�ʒu�\���p
	int xstat = 0;

	// ----------------------------------------
	// �A�N�V�����v���[�g�\��
	// ----------------------------------------
	DispTakuActplt(tk, gui, kyoku_index, actid, pnum);

	// ----------------------------------------
	// �ȏ��\��
	// ----------------------------------------

	// �ȏ��ݒ�
	wsprintf(tmp_disp_msg,"[��%d]%s", pnum+1, tk->plyname[pnum]);

	// ��v�p�[�c�̕\��(Right)
	if( pnum == (gui->disp_down_tehai_pnum+1) % 4){

		// �ȏ��_RIGHT
		dparts->DispName_right( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE+10, 
	                tmp_disp_msg);

	}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){

		// �ȏ��_UP
		dparts->DispName_up( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX, 
	             gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	             tmp_disp_msg);

	}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){

		// �ȏ��_LEFT
		dparts->DispName_left( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	               gui->tehai_left_y,
	               tmp_disp_msg);

	}else if( pnum == gui->disp_down_tehai_pnum){

		// �ȏ��_DOWN
		dparts->DispString( gui->tehai_x, 
	                    gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                   tmp_disp_msg);

	}

	// -----------------------------------------------------------
	// 1.��v�\���F���̎�
	// -----------------------------------------------------------
	if ( ( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMO || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYRINSHAN  || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI ) &&
	       tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

		// ��v�p�[�c�̕\��(Right)
		if( pnum == (gui->disp_down_tehai_pnum+1) % 4){
			dparts->DispActTehaiParts_right( gui->tehai_right_x, gui->tehai_right_y,
				                        tk->ply_act_tehaicount[pnum],
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    tk->kyoku[kyoku_index].act_hai[actid],
					                    tk->kyoku[kyoku_index].act_aka[actid],
					                    EXCEPT_VALUE);
		// ��v�p�[�c�̕\��(UP)
		}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){
			dparts->DispActTehaiParts_up( gui->tehai_up_x, gui->tehai_up_y,
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   EXCEPT_VALUE);
		// ��v�p�[�c�̕\��(Left)
		}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){
				dparts->DispActTehaiParts_left( gui->tehai_left_x, gui->tehai_left_y,
				                        tk->ply_act_tehaicount[pnum],
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   EXCEPT_VALUE);
		// ��v�p�[�c�̕\��(Down)
		}else if( pnum == gui->disp_down_tehai_pnum){
				dparts->DispActTehaiParts(gui->tehai_x, gui->tehai_y,
				                       tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   false);
		}

	// ----------------------------------------
	// 2.��v�\���F���̎����[�`�錾
	// ----------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRIICH && tk->kyoku[kyoku_index].act_ply[actid] == pnum ){

		// ��v�p�[�c�̕\��(Right)
		if( pnum == (gui->disp_down_tehai_pnum+1) % 4){
			dparts->DispActTehaiParts_right( gui->tehai_right_x, gui->tehai_right_y,
				                        tk->ply_act_tehaicount[pnum],
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    tk->kyoku[kyoku_index].act_hai[actid-1],
					                    tk->kyoku[kyoku_index].act_aka[actid-1],
					                    EXCEPT_VALUE);
		// ��v�p�[�c�̕\��(UP)
		}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){
			dparts->DispActTehaiParts_up( gui->tehai_up_x, gui->tehai_up_y,
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid-1],
					                   tk->kyoku[kyoku_index].act_aka[actid-1],
					                   EXCEPT_VALUE);
		// ��v�p�[�c�̕\��(Left)
		}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){
			dparts->DispActTehaiParts_left( gui->tehai_left_x, gui->tehai_left_y,
				                        tk->ply_act_tehaicount[pnum],
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid-1],
					                   tk->kyoku[kyoku_index].act_aka[actid-1],
					                   EXCEPT_VALUE);
		// ��v�p�[�c�̕\��(Down)
		}else if( pnum == gui->disp_down_tehai_pnum){
			dparts->DispActTehaiParts(gui->tehai_x, gui->tehai_y,
				                       tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->kyoku[kyoku_index].act_hai[actid-1],
					                   tk->kyoku[kyoku_index].act_aka[actid-1],
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   false);
		}

	// ----------------------------------------
	// 3.��v�\���F���̎̔v��
	// ----------------------------------------
	}else if( tk->kyoku[kyoku_index].act_ply[actid] == pnum && tk->kyoku[kyoku_index].act_stat[actid] == PLYACTSUTE){

		// ��v�p�[�c�̕\��(Right)
		if( pnum == (gui->disp_down_tehai_pnum+1) % 4){
			dparts->DispActTehaiParts_right( gui->tehai_right_x,                // 01:X���W
				                             gui->tehai_right_y,                // 02:Y���W
				                        tk->ply_act_tehaicount[pnum],           // 03:��v��
					                    tk->ply_act_tehaitbl[pnum],             
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    tk->ply_act_tsumo[pnum],
					                    tk->ply_act_tsumo_aka[pnum],
					                    tk->ply_tbl_com_sutehai_statnum[pnum]);

		// ��v�p�[�c�̕\��(UP)
		}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){
					dparts->DispActTehaiParts_up( gui->tehai_up_x, gui->tehai_up_y,
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->ply_act_tsumo[pnum],
					                   tk->ply_act_tsumo_aka[pnum],
					                   tk->ply_tbl_com_sutehai_statnum[pnum]);

		// ��v�p�[�c�̕\��(Left)
		}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){
					dparts->DispActTehaiParts_left(  gui->tehai_left_x, gui->tehai_left_y,
				                        tk->ply_act_tehaicount[pnum],
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    tk->ply_act_tsumo[pnum],
					                    tk->ply_act_tsumo_aka[pnum],
					                    tk->ply_tbl_com_sutehai_statnum[pnum]);

		// ��v�p�[�c�̕\��(Down)
		}else if( pnum == gui->disp_down_tehai_pnum){
					dparts->DispActTehaiParts(gui->tehai_x, gui->tehai_y,
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
					                   tk->ply_act_tsumo[pnum],
					                   tk->ply_act_tsumo_aka[pnum],
					                   tk->ply_tbl_com_sutehai_statnum[pnum],
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   false);
		}

	// -----------------------------------------------------------
	// 5.��v�\���F���̔v��
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTNAKISUTE &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum       ){

		// ��v�p�[�c�̕\��(Right)
		if( pnum == (gui->disp_down_tehai_pnum+1) % 4){
					dparts->DispActTehaiParts_right( gui->tehai_right_x,        // 01:X���W
				                                     gui->tehai_right_y,        // 02:Y���W
					                    tk->ply_act_tehaicount[pnum],           // 03:��v��
					                    tk->ply_act_tehaitbl[pnum],             
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    EXCEPT_VALUE, 
					                    false,
					                    tk->ply_tbl_com_sutehai_statnum[pnum]);

		// ��v�p�[�c�̕\��(UP)
		}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){
					dparts->DispActTehaiParts_up( gui->tehai_up_x, gui->tehai_up_y,
					                    tk->ply_act_tehaicount[pnum], 
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    EXCEPT_VALUE, 
					                    false,
					                    tk->ply_tbl_com_sutehai_statnum[pnum]);

		// ��v�p�[�c�̕\��(Left)
		}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){
					dparts->DispActTehaiParts_left(  gui->tehai_left_x,         // 01:X���W
					                                 gui->tehai_left_y,         // 02:Y���W
					                    tk->ply_act_tehaicount[pnum],           // 03:��v��
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    EXCEPT_VALUE, 
					                    false,
					                    tk->ply_tbl_com_sutehai_statnum[pnum]);

		// ��v�p�[�c�̕\��(Down)
		}else if( pnum == gui->disp_down_tehai_pnum){
					dparts->DispActTehaiParts(gui->tehai_x, gui->tehai_y,
					                    tk->ply_act_tehaicount[pnum], 
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    EXCEPT_VALUE, 
					                    false,
					                    tk->ply_tbl_com_sutehai_statnum[pnum],
					                    EXCEPT_VALUE,
					                    EXCEPT_VALUE,
					                    false);
		}

	// ----------------------------------------
	// 7.��v�\���F����ȊO�̎�v�\��(���̂Ȃ��E�̔v�Ȃ�)
	// ----------------------------------------
	}else{

		// �`�[�v�I��
		if( pnum == HUM_PLY_SEKI_NUM && gui->gui_ply_tehai_mode == TEHAI_CHI_SELECT){

		// ���̑��ʏ��v�\��
		}else{

			// ��v�p�[�c�̕\��(Right)
			if( pnum == (gui->disp_down_tehai_pnum+1) % 4){
				dparts->DispActTehaiParts_right( gui->tehai_right_x, gui->tehai_right_y,
				                        tk->ply_act_tehaicount[pnum],
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
					                    EXCEPT_VALUE, false,
					                    EXCEPT_VALUE);

			// ��v�p�[�c�̕\��(UP)
			}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){
				dparts->DispActTehaiParts_up( gui->tehai_up_x, gui->tehai_up_y,
					                    tk->ply_act_tehaicount[pnum], 
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
				                        EXCEPT_VALUE, false,
					                    EXCEPT_VALUE);

			// ��v�p�[�c�̕\��(Left)
			}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){
				dparts->DispActTehaiParts_left(  gui->tehai_left_x, gui->tehai_left_y,    // 01-02:X,Y��
				                        tk->ply_act_tehaicount[pnum],
					                    tk->ply_act_tehaitbl[pnum],
					                    tk->ply_act_tehai_tbl_aka[pnum], 
				                        EXCEPT_VALUE, false,
					                    EXCEPT_VALUE);

			// ��v�p�[�c�̕\��(Down)
			}else if( pnum == gui->disp_down_tehai_pnum){
				// ���C�i�[�\���Ƌ���
				dparts->DispActTehaiParts(gui->tehai_x, gui->tehai_y,
				                       tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum], 
				                       EXCEPT_VALUE, false,
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   EXCEPT_VALUE,
					                   false);
			}
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�������̎N���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActSarashi(MJSTkinfo *tk, int kyoku_index, int actid, int pnum){

	// �ϐ���`
	int tmp_xstat_count  = 0;
	int tmp_aka_count    = 0;

	// ���炵�\��
	for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[pnum]; tmp_i++){

		// �A�N�V�������s��ꂽ���̊m�F
		if( tk->kyoku[kyoku_index].naki_actid[pnum][tmp_i] <= actid ){

			// �Ԕv�̐ݒ�
			tmp_aka_count=tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i];

			// ----------------------------------------
			// �|���v�̕\���E���Ȕv�̕\���E�ÞȔv�̕\��
			// ----------------------------------------
			if( tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINKO  || 
                tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINKAN || 
                tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == ANKAN  ){

				dparts->DispActSarashiParts( 600 - tmp_xstat_count*NAKI_MENTSU_RANGE, PLY_YSTART+pnum*PLY_YSIZE+40, 
				                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
				                     tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i], 
				                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ���ʎq�̕\���ʒu�ړ�
				tmp_xstat_count++;

			// ----------------------------------------
			// �`�[�v�̕\��
			// ----------------------------------------
			}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINSHUN){

				dparts->DispActSarashiParts( 600 - tmp_xstat_count*NAKI_MENTSU_RANGE, PLY_YSTART+pnum*PLY_YSIZE+40, 
				                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
				                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
				                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ���ʎq�̕\���ʒu�ړ�
				tmp_xstat_count++;

			// ----------------------------------------
			// ���Ȕv�̕\��
			// ----------------------------------------
			}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == KAKAN){

				// ���Ȃ̎N���v�ԍ��̊m�F
				for(int tmp_j = 0; tmp_j < tk->kyoku[kyoku_index].naki_count[pnum]; tmp_j++){

					// �����N���ʎq�Ɠ����Ȃ��
					if (tk->kyoku[kyoku_index].naki_hai[pnum][tmp_j] == tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i]){

						// �N���ʎq�p�[�c�\��
						if(tmp_aka_count > 0){
							dparts->DispActSarashiParts(600 - tmp_j*NAKI_MENTSU_RANGE, PLY_YSTART+pnum*PLY_YSIZE+40, KAKAN, tk->kyoku[kyoku_index].naki_hai[pnum][tmp_j], 1);
						}else{
							dparts->DispActSarashiParts(600 - tmp_j*NAKI_MENTSU_RANGE, PLY_YSTART+pnum*PLY_YSIZE+40, KAKAN, tk->kyoku[kyoku_index].naki_hai[pnum][tmp_j], 0);
						}

						// ���Ȃ�����̂ŁA�����Ŕ�����(�����Ȃ��Ɖ��Ȃŏd�������ɂȂ��Ă��܂�)
						break;

					}
				}

			// ----------------------------------------
			// ���̑��̕\��
			// ----------------------------------------
			}else{
				// ���̑�����
				DrawFormatString(900, PLY_YSTART+pnum*PLY_YSIZE+40, GetColor(255,255,255), "���̑�");
			}

		}
	}

	// ���炵���
	// wsprintf(tmp_disp_msg, "�N�������F%d", tk->kyoku[kyoku_index].naki_count[pnum]);
	// ShowlogPrint(tmp_disp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�������̎N���\��(�X�N�G�A)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActSarashi_square(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum){

	// �ϐ���`
	int tmp_nakimen_count  = 0;  // �ʎq��
	int tmp_naki_x         = 0;  // ���ʎq��X�\���ʒu
	int tmp_naki_y         = 0;  // ���ʎq��Y�\���ʒu

	// ���炵�\��
	for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[pnum]; tmp_i++){

		// �A�N�V�������s��ꂽ���̊m�F
		if( tk->kyoku[kyoku_index].naki_actid[pnum][tmp_i] <= actid ){

			// ----------------------------------------
			// �|���v�̕\���E���Ȕv�̕\���E�ÞȔv�̕\��
			// ----------------------------------------
			if( tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINKO   || 
			    tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINKAN  || 
			    tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == ANKAN   ){

				// ----------------------------------------
				// ��v�p�[�c�̕\��(Right)
				// ----------------------------------------
				if( pnum == (gui->disp_down_tehai_pnum+1) % 4){

					// ���ʎq�̕\���ʒu
					if( gui->disp_square_naki_mentsu == 0 ){
						// ������\��
						tmp_naki_x = gui->nakihai_line_right_x;
						tmp_naki_y = gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_nakimen_count - HAI_XSIZE*3;
					}else{
//						tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//						tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// ���ʎq�̕\��
					dparts->DispActSarashiParts_right( 
					                     tmp_naki_x, 
				                         tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// ��v�p�[�c�̕\��(UP)
				// ----------------------------------------
				}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){

					// ���ʎq�̕\���ʒu
					if( gui->disp_square_naki_mentsu == 0 ){
						// ������\��
						tmp_naki_x = gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_nakimen_count;
						tmp_naki_y = gui->nakihai_line_up_y;
					}else{
//						tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//						tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// ���ʎq�̕\��
					dparts->DispActSarashiParts_up( 
					                     tmp_naki_x,
					                     tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// ��v�p�[�c�̕\��(Left)
				// ----------------------------------------
				}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){

					// ���ʎq�̕\���ʒu
					if( gui->disp_square_naki_mentsu == 0 ){
						// ������\��
						tmp_naki_x = gui->nakihai_line_left_x;
						tmp_naki_y = gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_nakimen_count;
					}else{
//						tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//						tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// ���ʎq�̕\��
					dparts->DispActSarashiParts_left( 
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// ��v�p�[�c�̕\��(Down�F���C�i�[�Ƌ���)
				// ----------------------------------------
				}else if( pnum == gui->disp_down_tehai_pnum){

					// ���ʎq�̕\���ʒu
					if( gui->disp_square_naki_mentsu == 0 ){
						tmp_naki_x = gui->nakihai_line_down_x - NAKI_MENTSU_RANGE*tmp_nakimen_count;
						tmp_naki_y = gui->nakihai_line_down_y;
					}else{

					}

					// ���ʎq�̕\��
					dparts->DispActSarashiParts( 
					                     tmp_naki_x, 
					                     tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				}

				// ----------------------------------------
				// ���ʎq�̕\���ʒu�ړ�
				// ----------------------------------------
				tmp_nakimen_count++;

			// ----------------------------------------
			// �`�[�v�̕\��
			// ----------------------------------------
			}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == MINSHUN){

				// ----------------------------------------
				// ��v�p�[�c�̕\��(Right)
				// ----------------------------------------
				if( pnum == (gui->disp_down_tehai_pnum+1) % 4){

					// ���ʎq�̕\���ʒu
					// ������\��
					if( gui->disp_square_naki_mentsu == 0 ){
						tmp_naki_x = gui->nakihai_line_right_x;
						tmp_naki_y = gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_nakimen_count - HAI_XSIZE*3;
					}else{
						// tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
						// tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// ���ʎq�̕\��
					dparts->DispActSarashiParts_right( 
					                     tmp_naki_x, 
				                         tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// ��v�p�[�c�̕\��(UP)
				// ----------------------------------------
				}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4){

					// ���ʎq�̕\���ʒu
					if( gui->disp_square_naki_mentsu == 0 ){
						// ������\��
						tmp_naki_x = gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_nakimen_count;
						tmp_naki_y = gui->nakihai_line_up_y;
					}else{
//						tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//						tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// ���ʎq�̕\��
					dparts->DispActSarashiParts_up( 
					                     tmp_naki_x,
				                         tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// ��v�p�[�c�̕\��(Left)
				// ----------------------------------------
				}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4){

					// ���ʎq�̕\���ʒu
					if( gui->disp_square_naki_mentsu == 0 ){
						// ������\��
						tmp_naki_x = gui->nakihai_line_left_x;
						tmp_naki_y = gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_nakimen_count;
					}else{
						// �c����\��
//						tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//						tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
					}

					// ���ʎq�̕\��
					dparts->DispActSarashiParts_left(
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				// ----------------------------------------
				// ��v�p�[�c�̕\��(Down�F���C�i�[�Ƌ���)
				// ----------------------------------------
				}else if( pnum == gui->disp_down_tehai_pnum){

					// ���ʎq�̕\���ʒu
						tmp_naki_x = gui->nakihai_line_down_x - NAKI_MENTSU_RANGE*tmp_nakimen_count;
						tmp_naki_y = gui->nakihai_line_down_y;

					// ���ʎq�̕\��
					dparts->DispActSarashiParts(  
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

				}

				// ----------------------------------------
				// ���ʎq�̕\���ʒu�ړ�
				// ----------------------------------------
				tmp_nakimen_count++;

			// ----------------------------------------
			// ���Ȕv�̕\��
			// ----------------------------------------
			}else if(tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i] == KAKAN){

				// ----------------------------------------
				// ���Ȃ̎N���v�ԍ��̊m�F
				// ----------------------------------------
				for(int tmp_j = 0; tmp_j < tk->kyoku[kyoku_index].naki_count[pnum]; tmp_j++){

					// �����N���ʎq�Ɠ����Ȃ��
					if (tk->kyoku[kyoku_index].naki_hai[pnum][tmp_j] == tk->kyoku[kyoku_index].naki_hai[pnum][tmp_i]){

						// ----------------------------------------
						// ��v�p�[�c�̕\��(Right)
						// ----------------------------------------
						if( pnum == (gui->disp_down_tehai_pnum+1) % 4 ){

							// ���ʎq�̕\���ʒu
							if( gui->disp_square_naki_mentsu == 0 ){
								// ������\��
								tmp_naki_x = gui->nakihai_line_right_x;
								tmp_naki_y = gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_j - HAI_XSIZE*3;
							}else{
								// �c����\��
								// tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
								// tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
							}

							// ���ʎq�̕\��
							dparts->DispActSarashiParts_right( 
					                     tmp_naki_x, 
				                         tmp_naki_y,
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

						// ----------------------------------------
						// ��v�p�[�c�̕\��(UP)
						// ----------------------------------------
						}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4 ){

							// ���ʎq�̕\���ʒu
							if( gui->disp_square_naki_mentsu == 0 ){
								// ������\��
								tmp_naki_x = gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_j;
								tmp_naki_y = gui->nakihai_line_up_y;
							}else{
//								tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//								tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
							}

							// ���ʎq�̕\��
							dparts->DispActSarashiParts_up(
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

						// ----------------------------------------
						// ��v�p�[�c�̕\��(Left)
						// ----------------------------------------
						}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4 ){

							// ���ʎq�̕\���ʒu
							if( gui->disp_square_naki_mentsu == 0 ){
								// ������\��
								tmp_naki_x = gui->nakihai_line_left_x;
								tmp_naki_y = gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_j;
							}else{
//								tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//								tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
							}

							// ���ʎq�̕\��
							dparts->DispActSarashiParts_left( 
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

						// ----------------------------------------
						// ��v�p�[�c�̕\��(Down�F���C�i�[�Ƌ���)
						// ----------------------------------------
						}else if( pnum == gui->disp_down_tehai_pnum ){

							// ���ʎq�̕\���ʒu
							if( gui->disp_square_naki_mentsu == 0 ){
								// ������\��
								tmp_naki_x = gui->nakihai_line_down_x - NAKI_MENTSU_RANGE*tmp_j;
								tmp_naki_y = gui->nakihai_line_down_y;
							}else{
								// �c����\��
//								tmp_naki_x = TEHAI_RIGHT_NAKI_X_START + (3-tmp_nakimen_count)*LHAI_XSIZE;
//								tmp_naki_y = TEHAI_RIGHT_NAKI_Y_START;
							}

							// ���ʎq�̕\��
							dparts->DispActSarashiParts( 
					                     tmp_naki_x, 
					                     tmp_naki_y, 
					                     tk->kyoku[kyoku_index].naki_stat[pnum][tmp_i],
					                     tk->kyoku[kyoku_index].naki_idx[pnum][tmp_i], 
					                     tk->kyoku[kyoku_index].naki_aka[pnum][tmp_i]);

						}

						// ���Ȃ�����̂ŁA�����Ŕ�����(�����Ȃ��Ɖ��Ȃŏd�������ɂȂ��Ă��܂�)
						break;

					}
				}
			}
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����͏��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActKawa(MJSTkinfo *tk, int kyoku_index, int actid, int pnum){

	// �͕\��(�p�[�c�\��)
	dparts->DispActKawaParts_liner( SPACE_XSIZE, 
	                        PLY_YSTART+pnum*PLY_YSIZE, 
	                        tk->ply_act_kawa_count[pnum], 
	                        tk->ply_act_kawa[pnum], 
	                        tk->ply_act_kawa_aka[pnum], 
	                        tk->ply_act_kawa_mode[pnum]);

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����͏��(�X�N�G�A)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActKawa_square(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum){

	// RIGHT�v���[���̕\��
	if( pnum == (gui->disp_down_tehai_pnum+1) % 4 ){
		dparts->DispActKawaParts_right( gui->sutehai_right_x, 
	                                    gui->sutehai_right_y, 
	                            tk->ply_act_kawa_count[pnum], 
	                            tk->ply_act_kawa[pnum], 
	                            tk->ply_act_kawa_aka[pnum], 
	                            tk->ply_act_kawa_mode[pnum]);

	// UP�v���[���̕\��
	}else if( pnum == (gui->disp_down_tehai_pnum+2) % 4 ){

		dparts->DispActKawaParts_up( gui->sutehai_up_x, 
	                                 gui->sutehai_up_y, 
	                            tk->ply_act_kawa_count[pnum], 
	                            tk->ply_act_kawa[pnum], 
	                            tk->ply_act_kawa_aka[pnum], 
	                            tk->ply_act_kawa_mode[pnum]);

	// LEFT�v���[���̕\��
	}else if( pnum == (gui->disp_down_tehai_pnum+3) % 4 ){
		dparts->DispActKawaParts_left( gui->sutehai_left_x, 
	                                   gui->sutehai_left_y,
	                            tk->ply_act_kawa_count[pnum], 
	                            tk->ply_act_kawa[pnum], 
	                            tk->ply_act_kawa_aka[pnum], 
	                            tk->ply_act_kawa_mode[pnum]);

	// DOWN�v���[���̕\��
	}else if( pnum == gui->disp_down_tehai_pnum ){
		dparts->DispActKawaParts_down( gui->sutehai_down_x, 
	                                   gui->sutehai_down_y, 
	                            tk->ply_act_kawa_count[pnum], 
	                            tk->ply_act_kawa[pnum], 
	                            tk->ply_act_kawa_aka[pnum], 
	                            tk->ply_act_kawa_mode[pnum]);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V�����v���[�g�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispTakuActplt(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum){

	// ----------------------------------------
	// �A�N�V�����v���[�g��\������A�N�V�����m�F
	// ----------------------------------------
	if (tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRIICH   ||  // ���[�`
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTPON     ||  // �|��
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTCHI     ||  // �`�[
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTMINKAN  ||  // ���J��
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTANKAN   ||  // �ÃJ��
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTKAKAN   ||  // ���J��
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI ||  // ���̘a��
	    tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRON     ){  // �����a��

		// ----------------------------------------
		// �A�N�V�������b�Z�[�W�̒�`
		// ----------------------------------------
		if (tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRIICH){
			// ���[�`
			wsprintf(tmp_disp_msg,"���[�`");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTPON){
			// �|��
			wsprintf(tmp_disp_msg,"�|���I");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTCHI){
			// �`�[
			wsprintf(tmp_disp_msg,"�`�[�I");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTMINKAN){
			// ���J��
			wsprintf(tmp_disp_msg,"���J��");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTANKAN){
			// �ÃJ��
			wsprintf(tmp_disp_msg,"�ÃJ��");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTKAKAN){
			// ���J��
			wsprintf(tmp_disp_msg,"���J��");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI){
			// ���̘a��
			wsprintf(tmp_disp_msg,"���́I");
		}else if(tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRON){
			// �����a��
			wsprintf(tmp_disp_msg,"�����I");
		}else{
			// �s��
			wsprintf(tmp_disp_msg,"�s��");
		}

		// ----------------------------------------
		// �A�N�V�����v���[���[�̊m�F
		// ----------------------------------------
		     if( tk->kyoku[kyoku_index].act_ply[actid] == (gui->disp_down_tehai_pnum+1) % 4 ){
			// RIGHT�v���[�g�̕\��
			dparts->DispActplt_right( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                          gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 56, 
	                          tmp_disp_msg);

		}else if( tk->kyoku[kyoku_index].act_ply[actid] == (gui->disp_down_tehai_pnum+2) % 4 ){
			// UP�v���[�g�̕\��
			dparts->DispActplt_up( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 56, 
	                       gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                       tmp_disp_msg);

		}else if( tk->kyoku[kyoku_index].act_ply[actid] == (gui->disp_down_tehai_pnum+3) % 4 ){
			// LEFT�v���[�g�̕\��
			dparts->DispActplt_left( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                         gui->tehai_left_y - 56,
	                         tmp_disp_msg);

		}else if( tk->kyoku[kyoku_index].act_ply[actid] == gui->disp_down_tehai_pnum ){
			// DOWN�v���[�g�̕\��
			dparts->DispActplt_down( gui->tehai_x - 56, 
	                         gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                         tmp_disp_msg);

		}

	// ----------------------------------------
	// �A�N�V�����v���[�g��\������A�N�V�����m�F
	// ----------------------------------------
	}else if(tk->kyoku[kyoku_index].act_stat[actid] == RYUKYOKU){ // ���ǂ͑S���\��


			// ���ǒ�`
			wsprintf(tmp_disp_msg,"���ǁ@");

			// RIGHT�v���[�g�̕\��
			dparts->DispActplt_right( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                          gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 56, 
	                          tmp_disp_msg);

			// UP�v���[�g�̕\��
			dparts->DispActplt_up( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 56, 
	                       gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                       tmp_disp_msg);

			// LEFT�v���[�g�̕\��
			dparts->DispActplt_left( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                         gui->tehai_left_y - 56,
	                         tmp_disp_msg);

			// DOWN�v���[�g�̕\��
			dparts->DispActplt_down( gui->tehai_x - 56, 
	                         gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                         tmp_disp_msg);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI���\��(���_�\��)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEnd(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int tmp_actid){

	int disp_agari_num = 0;
	int tmp_disp_yaku_count = 0;

	// ----------------------------------------
	// ���ǎ�
	// ----------------------------------------
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_flg == true ){

		// ���ǌ��ʂ�\��
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_stat == HOWANPAI ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[HOWANPAI]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_stat == SUFURENDA ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[SUFURENDA]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_stat == RIICHI4PLY ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[RIICHI4PLY]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_stat == UNKNOWNRKK ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[UNKNOWNRKK]);
		}

	// ----------------------------------------
	// �𖼕\���F��L�莞
	// ----------------------------------------
	}else{

		// ��v�\��
		DispKyokuEndTehai(tk, kyoku_index, 0);

		// �|���\��
		DispKyokuEndHanInfo(tk, kyoku_index, 0);

		// �a�����̏ڍ׏��
		DispKyokuEndYakuInfo(tk, kyoku_index, tmp_actid, 0);

	}

	// ----------------------------------------
	// �v���[���̓��_��
	// ----------------------------------------
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){

		// �v���[����
		DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE, GetColor(255,255,255), "[��%d]%s", ply_i+1, tk->plyname[ply_i]);

		// �ƕ\��
		if(tk->kyoku[kyoku_index].ie[ply_i] == 0){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "����");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 1){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "���");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 2){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "����");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 3){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "�k��");
		}else{
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "�s��");
		}

		// �J�n���_
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*1, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i]);

		// �ǂ̓��_
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].kyoku_score[ply_i]);

		// �I�����_
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*3, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_end_score[ply_i]);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI���\��(��v�\��)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndTehai(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// �a����v�̕\��
	// ----------------------------------------

/*
	// ��v�p�[�c�̕\��(�l�v���[���p_���̖����F�J�[�\���I�𖳂�)
	dparts->DispActTehaiParts( SPACE_XSIZE, 
	                      PLY_YSTART,
	                      tk->ply_act_tehaicount[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],     
	                      tk->ply_act_tehaitbl[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],       
	                      tk->ply_act_tehai_tbl_aka[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],  
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai,       // ���̔v�F�a���v
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka,       // ���̐ԁF�a���v��
	                      EXCEPT_VALUE,                                                        // �̔v�F�Ȃ�
	                      EXCEPT_VALUE, EXCEPT_VALUE, false);                                  // �J�[�\���I���F�Ȃ�
*/

	// ��v�p�[�c�̕\��(�l�v���[���p_���̖����F�J�[�\���I�𖳂�)
	dparts->DispActTehaiParts( SPACE_XSIZE, 
	                      PLY_YSTART,
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_tehaicount,     // ��v��
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_tehaitbl,       // ��v�e�[�u��
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_tehai_tbl_aka,  // ��v�e�[�u����
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai,            // ���̔v�F�a���v
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka,            // ���̐ԁF�a���v��
	                      EXCEPT_VALUE,                                                             // �̔v�F�Ȃ�
	                      EXCEPT_VALUE, EXCEPT_VALUE, false);                                       // �J�[�\���I���F�Ȃ�

	// �N���v�\��
	dparts->DispAllSarashiParts(600, PLY_YSTART,
		tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],     
		tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],      
		tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],       
		tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],       
		tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num]        
	);

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI���\��(�|���\��)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndHanInfo(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// �ϐ���`
	// ----------------------------------------
	int tmp_disp_yaku_count=0;

	// �ʏ��(�𖞂Ȃ���)
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_count == 0 ){

		// �ʏ���m�F
		for(int tmp_i = 0; tmp_i < YAKU_SHUBETSU_MAX; tmp_i++){

			// ��ݒ�L��
			if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yaku_flg[tmp_i] == true){

				// �ʖ�
				wsprintf(tmp_disp_msg, "%s �c %d�|", dparts->yakuname[tmp_i], tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yaku_han[tmp_i]);
				dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, tmp_disp_msg);
				tmp_disp_yaku_count++;
			}
		}

	}else{

		// �𖞊m�F
		for(int tmp_i = 0; tmp_i < YAKUMAN_SHUBETSU_MAX; tmp_i++){

			// ��ݒ�L��
			if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_flg[tmp_i] == true){

				// ���e�[�u���ݒ�
				wsprintf(tmp_disp_msg, "%s �c �𖞁@�@", dparts->yakumanname[tmp_i]);
				dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, tmp_disp_msg);
				tmp_disp_yaku_count++;

			}

		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI���\��(���_�\��)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndYakuInfo(MJSTkinfo *tk, int kyoku_index, int tmp_actid, int disp_agari_num){

	// ----------------------------------------
	// �a�����
	// ----------------------------------------
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].tsumo_agari_flg == true){
		DrawFormatString(5, PLY_YSTART+50, GetColor(255,255,255), "���̘a���@�a��[��%d]", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num+1);
	}else{
		DrawFormatString(5, PLY_YSTART+50, GetColor(255,255,255), "�����a���@�a��[��%d]�@���e�F[��%d]", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num+1, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].furikomi_ply_num+1);
	}

	// �a���v���[����
		DrawFormatString(300, PLY_YSTART+50, GetColor(255,255,255), "�a���v���[���� %d�l", tk->kyoku[kyoku_index].agari_ply_count);

	// ----------------------------------------
	// ���h���\��
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].riichi_flg == true){
		// ���h���\��
		dparts->DispDora(DORA_XSIZE+URADORA_XSIZE_RANGE, SPACE_YSIZE, 
	                 tk->kyoku[kyoku_index].doracount, 
	                 tk->kyoku[kyoku_index].uradora, 
	                 tk->kyoku[kyoku_index].uradora_aka,
	                 tk->kyoku[kyoku_index].uradora_actid,
	                 tmp_actid);
	}

	// ----------------------------------------
	// �a�����̖ʎq���
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_NORMAL){
		DispKyokuEndMentsuInfoNormal(tk, kyoku_index, disp_agari_num);
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_CHITOI){
//		DispKyokuEndMentsuInfoChitoi(tk, kyoku_index, disp_agari_num);
	}

	// ----------------------------------------
	// �a���v
	// ----------------------------------------
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka == true ){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*0, GetColor(255,255,255), "�a���v�@�F%2d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai);
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*0, GetColor(255,255,255), "�a���v�@�F%2d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai);
	}

	// ----------------------------------------
	// �a���`��
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_NORMAL){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*1, GetColor(255,255,255), "�a���`���F�ʏ�`��");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_CHITOI){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*1, GetColor(255,255,255), "�a���`���F���Ό`��");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_KOKUSHI){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*1, GetColor(255,255,255), "�a���`���F���m�`��");
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*1, GetColor(255,255,255), "�a���`���F�`���s��");
	}

	// ----------------------------------------
	// �e�q���
	// ----------------------------------------
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_oya_flg == true){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*2, GetColor(255,255,255), "�e�q�@�@�F�e�a��");
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*2, GetColor(255,255,255), "�e�q�@�@�F�q�a��");
	}

	// ----------------------------------------
	// ���̘a���L��
	// ----------------------------------------
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].tsumo_agari_flg == true){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "���̃����F���̘a��");
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "���̃����F�����a��");
	}

	// ----------------------------------------
	// �ʑO���
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].menzen_flg==true){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*4, GetColor(255,255,255), "����ԁF�ʑO");
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*4, GetColor(255,255,255), "����ԁF�L");
	}

	// ----------------------------------------
	// �҂��`��
	// ----------------------------------------
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_machi_stat == TANKI){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "�҂��`���F�P�R�҂�");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_machi_stat == RYANMEN){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "�҂��`���F���ʑ҂�");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_machi_stat == KANCHAN){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "�҂��`���F�ƒ��҂�");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_machi_stat == PENCHAN){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "�҂��`���F�Ӓ��҂�");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_machi_stat == TOITSU){
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "�҂��`���F�o���҂�");
	}else{
		DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*5, GetColor(255,255,255), "�҂��`���F�`���s��");
	}

	// ----------------------------------------
	// ���v��
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE* 7, GetColor(255,255,255), "��{���@�@%3d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].basefu);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE* 8, GetColor(255,255,255), "�ʎq�����v%3d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].atamaFu+tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[0]+tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[1]+tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[2]+tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[3]);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE* 9, GetColor(255,255,255), "�ʑO���@�@%3d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].menzenFu);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*10, GetColor(255,255,255), "�҂����@�@%3d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].machiFu);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*11, GetColor(255,255,255), "���̕��@�@%3d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].tsumoFu);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*12, GetColor(255,255,255), "���v���@�@%3d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].totalFu);
	DrawFormatString(AGARI_INFO_X2, PLY_YSTART+70+STRING_YSIZE*13, GetColor(255,255,255), "���v���@�@%3d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].scoreFu);

	// ----------------------------------------
	// �a���v�̊܂ރ����c�ԍ�
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*0, GetColor(255,255,255), "�a���v�ʎq:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai);

	// ----------------------------------------
	// �h���E�Ԕv���
	// ----------------------------------------
	// �h��
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*1, GetColor(255,255,255), "�h��%d ���h��%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_dora_count, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_uradora_count);

	// �Ԕv
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*2, GetColor(255,255,255), "����%d �ԓ�%d �ԍ�%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka_count[0], tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka_count[1], tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka_count[2]);

	// ----------------------------------------
	// ���[�`���
	// ----------------------------------------
	// ���[�`���
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].riichi_flg == true){
		DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "R�L");
	}else{
		DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "R��");
	}

	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].double_riichi_flg == true){
		DrawFormatString(AGARI_INFO_X3+40, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "WR�L");
	}else{
		DrawFormatString(AGARI_INFO_X3+40, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "WR��");
	}

	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].riichi_ippatsu_flg == true){
		DrawFormatString(AGARI_INFO_X3+95, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "�ꔭ�L");
	}else{
		DrawFormatString(AGARI_INFO_X3+95, PLY_YSTART+70+STRING_YSIZE*3, GetColor(255,255,255), "�ꔭ��");
	}

	// ���̉�
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*4, GetColor(255,255,255), "���̏�:%d �q��:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_tsumo_count, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_riichi_count);

	// ----------------------------------------
	// ���̑��̘a�����
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_NORMAL){
		DispKyokuEndAgariInfoNormal(tk, kyoku_index, disp_agari_num);
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_stat == AGARI_CHITOI){
		DispKyokuEndAgariInfoChitoi(tk, kyoku_index, disp_agari_num);
	}

	// ----------------------------------------
	// ���v�|�E���сE���v�𖞔{
	// ----------------------------------------
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai == 0 ){

		if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 0){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d�|", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 1){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d�|�@���с@�@", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 2){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d�|�@�����@�@", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 3){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d�|�@�{���@�@", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 4){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d�|�@�O�{���@", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_mangan_count == 5){
			DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%2d�|�@������", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);
		}

	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai == 1 ){
		// �𖞕\��
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "�𖞁@�@");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai == 2 ){
		// �𖞕\��
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "��{��");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai == 3 ){
		// �𖞕\��
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "�O�{��");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai == 4 ){
		// �𖞕\��
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "�l�{��");
	}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_agari_ply_bai >  4 ){
		// �𖞕\��
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "�ܔ{��");
	}

	// ----------------------------------------
	// ���_
	// ----------------------------------------
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].tsumo_agari_flg == true){

		// �c���a���E�e
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_oya_flg == true){
			DrawFormatString(AGARI_INFO_X1,PLY_YSTART+372, GetColor(255,255,255), "%d�_�I�[��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_tsumo_oya);
		// �c���a���E�q
		}else{
			DrawFormatString(AGARI_INFO_X1,PLY_YSTART+372, GetColor(255,255,255), "%d�_ %d�_", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_tsumo_oya, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_tsumo_ko);
		}

	}else{

		// �����a��
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_oya_flg == true){
			DrawFormatString(AGARI_INFO_X1,PLY_YSTART+372, GetColor(255,255,255), "%d�_", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_ron);
		}else{
			DrawFormatString(AGARI_INFO_X1,PLY_YSTART+372, GetColor(255,255,255), "%d�_", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_ron);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI���\��(�ʏ�`���ʎq���)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndMentsuInfoNormal(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// �a�����̐������
	// ----------------------------------------
	// �v�\��
		dparts->DispActSarashiParts(
			AGARI_INFO_X1, 
			PLY_YSTART+70,
			ATAMA,
			tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai,
			tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_aka);

	// �a���v�ϐF
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == EXCEPT_VALUE){
		// �Ԕv�\��
		if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_aka>0){
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, true,  false, DISP_HAI_COLOR_NUM_PINK, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, false, false, DISP_HAI_COLOR_NUM_PINK, 0);
		}
	}

	// �����E��
	DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+70, GetColor(255,255,255), "����");
	DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+87, GetColor(255,255,255), "%2d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].atamaFu);

	// �Ԕv����
	DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+70, GetColor(255,255,255), "��%d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_aka);

	// ��㎚�E�����v�̎��
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 0){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "�����v");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 1){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "��㎚");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 2){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "��v�@");
	}

	// ----------------------------------------
	// �a�����̖ʎq���
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < 4; tmp_i++){

		// ----------------------------------------
		// �ʎq�v
		// ----------------------------------------
		dparts->DispActSarashiParts(
			AGARI_INFO_X1, 
			PLY_YSTART+70+(tmp_i+1)*40,
			tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i],
			tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i],
			tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i]);

		// ----------------------------------------
		// �a���v�ϐF
		// ----------------------------------------

		// �a���v�Ȃ�
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i){
			// �ʎq�`���E�Í��\��
			if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKO || tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKO){
					dparts->DispHai( AGARI_INFO_X1,             PLY_YSTART+70+(tmp_i+1)*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i],  tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka, false, DISP_HAI_COLOR_NUM_PINK, 0);
			// �ʎq�`���E���q�\��
			}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == SHUNTSU || tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINSHUN){
				// ���q�̏��Ԋm�F
				if(       tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]){
					// ���q��1����
					dparts->DispHai( AGARI_INFO_X1,             PLY_YSTART+70+(tmp_i+1)*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i],  tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka, false, DISP_HAI_COLOR_NUM_PINK, 0);
				}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+1){
					// ���q��2����
					dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1, PLY_YSTART+70+(tmp_i+1)*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+1,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka, false, DISP_HAI_COLOR_NUM_PINK, 0);
				}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+2){
					// ���q��3����
					dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2, PLY_YSTART+70+(tmp_i+1)*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+2,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka, false, DISP_HAI_COLOR_NUM_PINK, 0);
				}

			}
		}

		// ----------------------------------------
		// �ʎq�\��
		// ----------------------------------------
		// �����c�`��
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == SHUNTSU){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "���q");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINSHUN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "����");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKO){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "�Í�");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKO){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "����");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKAN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "�Þ�");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKAN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "����");
		}else{
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "�s��");
		}

		// �����c��
		DrawFormatString( AGARI_INFO_X1_1, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "%2d��",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[tmp_i]);

		// �Ԕv����
		DrawFormatString( AGARI_INFO_X1_2, PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "��%d��",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i]);

		// ��㎚�E�����v�̎��
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 0){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "�����v");
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 1){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "��㎚");
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 2){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "��v�@");
		}

	}

/*
	// �Ԕv�����̉��ݒ�
	tmp_aka_count=tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_aka;

	// ����1����
	if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == EXCEPT_VALUE){

		// �Ԕv�\��
		if(tmp_aka_count>0){
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, true, false,DISP_HAI_COLOR_NUM_PINK, 0);
			tmp_aka_count--;
		}else{
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, false, false,DISP_HAI_COLOR_NUM_PINK, 0);
		}

	}else{

		// �Ԕv�\��
		if(tmp_aka_count>0){
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, true, false , 0, 0);
			tmp_aka_count--;
		}else{
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, false, false, 0, 0);
		}
	}

	// ����2����

		// �Ԕv�\��
		if(tmp_aka_count>0){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, true, false , 0, 0);
			tmp_aka_count--;
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+70, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_hai, false, false, 0, 0);
		}

	// �����E��
	DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+70, GetColor(255,255,255), "����");
	DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+87, GetColor(255,255,255), "%2d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].atamaFu);

	// �Ԕv����
	DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+70, GetColor(255,255,255), "��%d��", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_aka);

	// ��㎚
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 0){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "�����v");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 1){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "��㎚");
	}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ata_19zi == 2){
		DrawFormatString(AGARI_INFO_X1_2,PLY_YSTART+87, GetColor(255,255,255), "��v�@");
	}
*/

/*
		// ----------------------------------------
		// �����c�\�� - �Í��\��
		// ----------------------------------------
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKO || tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKO){

			// ����1����
			if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i){
				dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, DISP_HAI_COLOR_NUM_PINK, 0);
			}else{
				dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
			}

			// �Í��̔v�\��(2���ڈȍ~)
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);

		// ----------------------------------------
		// �����c�\�� - ���q�\��
		// ----------------------------------------
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == SHUNTSU || tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINSHUN){

			// ���q��1����
			if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i && tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]){
				dparts->DispHai( AGARI_INFO_X1             ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]  ,false, false, DISP_HAI_COLOR_NUM_PINK, 0);
			}else{
				dparts->DispHai( AGARI_INFO_X1             ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]  ,false, false,  0, 0);
			}

			// ���q��2����
			if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i && tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+1){
				dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+1, false, false, DISP_HAI_COLOR_NUM_PINK, 0);
			}else{
				dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+1, false, false, 0, 0);
			}

			// ���q��3����
			if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i && tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai == tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+2){
				dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+2, false, false, DISP_HAI_COLOR_NUM_PINK, 0);
			}else{
				dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i]+2, false, false, 0, 0);
			}

		// ----------------------------------------
		// �����c�\�� - �Þȕ\��
		// ----------------------------------------
		}else if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKAN || tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKAN ){

		// �N���v�̕\��(�I�[�v��1����)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 0 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��2����)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 1 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

			// �������v
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*0 ,PLY_YSTART+110+tmp_i*40, 0, false, false, 0, 0);
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*3 ,PLY_YSTART+110+tmp_i*40, 0, false, false, 0, 0);

		// ----------------------------------------
		// �����c�\�� - ���ȕ\��
		// ----------------------------------------

		// �N���v�̕\��(�I�[�v��1����)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 0 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*0 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*0 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��2����)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 1 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��3����)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 2 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*2 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

		// �N���v�̕\��(�I�[�v��4����)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i] > 3 ){
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*3 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], true, false, 0, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*3 ,PLY_YSTART+110+tmp_i*40,tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_hai[tmp_i], false, false, 0, 0);
		}

		// ----------------------------------------
		// (�f�o�O�p)�s���̖ʎq
		// ----------------------------------------
		}else{
				DrawFormatString( AGARI_INFO_X1, PLY_YSTART+140+tmp_i*40, GetColor(255,255,255), "�`���s��");
		}

		// ----------------------------------------
		// �ʎq�\��
		// ----------------------------------------

		// �����c�`��
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == SHUNTSU){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "���q");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINSHUN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "����");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKO){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "�Í�");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKO){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "����");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == ANKAN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "�Þ�");
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_stat[tmp_i] == MINKAN){
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "����");
		}else{
			DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "�s��");
		}

		// �����c��
		DrawFormatString( AGARI_INFO_X1_1, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "%2d��",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_Fu[tmp_i]);

		// �Ԕv����
		DrawFormatString( AGARI_INFO_X1_2, PLY_YSTART+110+tmp_i*40, GetColor(255,255,255), "��%d��",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_aka_count[tmp_i]);

		// ���I�`���E
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 0){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "�����v");
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 1){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "��㎚");
		}else if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_19zi[tmp_i] == 2){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+127+tmp_i*40, GetColor(255,255,255), "��v�@");
		}

	}
*/

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI���\��(�ʏ�`���a�����)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndAgariInfoNormal(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// �ꕗ�����̔v�ԍ�
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 5, GetColor(255,255,255), "�ꕗ:%d ����:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_bakaze, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_zikaze);

	// ----------------------------------------
	// �ʎq����(�ʏ�a��)
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 6, GetColor(255,255,255), "��㎚:%d �����v:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_19zi, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_chunchan);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 7, GetColor(255,255,255), "�ݎq:%d ���q:%d",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_manzu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_pinzu);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 8, GetColor(255,255,255), "���q:%d ���v:%d",tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_souzu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_zihai);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 9, GetColor(255,255,255), "�Δv:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_green);

	// ----------------------------------------
	// �ʎq�`������(�ʏ�a��)
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*10, GetColor(255,255,255), "���q:%d ����:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_shuntsu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_minshun);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*11, GetColor(255,255,255), "�Í�:%d ����:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_anko,    tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_minko);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*12, GetColor(255,255,255), "�Þ�:%d ����:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_ankan,   tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_minkan);

	// ----------------------------------------
	// ��v�q�X�g�O����(���q)
	// ----------------------------------------

	// �q�X�g�O�����p
	int tmp_hist;
	tmp_hist=0;

	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*13, GetColor(255,255,255), "���q:");
	for(int tmp_i = 1; tmp_i < PAI_MAX; tmp_i++){
		for(int tmp_j = 0; tmp_j < tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].anko_hist[tmp_i]; tmp_j++){
			// �q�X�g�O����
			DrawFormatString(AGARI_INFO_X3+45+tmp_hist*24, PLY_YSTART+70+STRING_YSIZE*13, GetColor(255,255,255), "%2d,", tmp_i);
			tmp_hist++;
		}
	}
	// ----------------------------------------
	// ��v�q�X�g�O����(���q)
	// ----------------------------------------
	tmp_hist=0;

	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE*14, GetColor(255,255,255), "���q:");
	for(int tmp_i = 1; tmp_i < PAI_MAX; tmp_i++){
		for(int tmp_j = 0; tmp_j < tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].shuntsu_hist[tmp_i]; tmp_j++){
			// �q�X�g�O����
			DrawFormatString(AGARI_INFO_X3+45+tmp_hist*24, PLY_YSTART+70+STRING_YSIZE*14, GetColor(255,255,255), "%2d,", tmp_i);
			tmp_hist++;
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI���\��(���Ύq�`���ʎq���)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndMentsuInfoChitoi(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// �a�����̖ʎq���
	// ----------------------------------------
	for(int tmp_i = 0; tmp_i < 7; tmp_i++){

		// �Ύq1����
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_men_num_agari_hai == tmp_i){
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_chitoi_men_hai[tmp_i], false, false, DISP_HAI_COLOR_NUM_PINK, 0);
		}else{
			dparts->DispHai( AGARI_INFO_X1, PLY_YSTART+70+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_chitoi_men_hai[tmp_i], false, false, 0, 0);
		}

		// �Ύq2����
		dparts->DispHai( AGARI_INFO_X1+HAI_XSIZE*1 ,PLY_YSTART+70+tmp_i*40, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_chitoi_men_hai[tmp_i], false, false, 0, 0);

		// �����c�`��
		DrawFormatString( AGARI_INFO_X1_1,PLY_YSTART+70+tmp_i*40, GetColor(255,255,255), "�Ύq");

		// �Ԕv����
		// DrawFormatString( AGARI_INFO_X1_2, PLY_YSTART+70+tmp_i*40, GetColor(255,255,255), "��%d��",tk->kyoku[kyoku_index].agari_men_aka_count[tmp_i]);
		DrawFormatString( AGARI_INFO_X1_2, PLY_YSTART+70+tmp_i*40, GetColor(255,255,255), "��%d��",0);

		// �����c��
		DrawFormatString( AGARI_INFO_X1_1, PLY_YSTART+87+tmp_i*40, GetColor(255,255,255), "%2d��",0);

		// ��㎚�v
		DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+87+tmp_i*40, GetColor(255,255,255), "��㎚");
/*		if( tk->kyoku[kyoku_index].agari_men_19zi[tmp_i] == 0){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+87+tmp_i*40, GetColor(255,255,255), "�����v");
		}else if(tk->kyoku[kyoku_index].agari_men_19zi[tmp_i] == 1){
			DrawFormatString(AGARI_INFO_X1_2, PLY_YSTART+87+tmp_i*40, GetColor(255,255,255), "��㎚");
		}*/

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI���\��(���Ύq�`���a�����)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispKyokuEndAgariInfoChitoi(MJSTkinfo *tk, int kyoku_index, int disp_agari_num){

	// ----------------------------------------
	// �ʎq����(�ʏ�a��)
	// ----------------------------------------
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 6, GetColor(255,255,255), "��㎚:%d �����v:%d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_19zi,  tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_chunchan);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 7, GetColor(255,255,255), "�ݎq:%d ���q:%d",     tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_manzu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_pinzu);
	DrawFormatString(AGARI_INFO_X3, PLY_YSTART+70+STRING_YSIZE* 8, GetColor(255,255,255), "���q:%d ���v:%d",     tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_souzu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].mentsu_count_zihai);

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI���\��(�r���[�A���[�h�F���������O)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispViewerKyokuEnd_mjscore(MJSTkinfo *tk, int kyoku_index, int tmp_actid){

	int disp_agari_num = 0;

	// ----------------------------------------
	// �𖼕\��
	// ----------------------------------------

	// �𖼕\��
	for(int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakucount; tmp_i++){

		// �ʖ�
		wsprintf(tmp_disp_msg, "%s", tk->kyoku[kyoku_index].yakuname[tmp_i]);
		dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_i, tmp_disp_msg);

	}

	// ----------------------------------------
	// �v���[���̓��_��
	// ----------------------------------------
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){

		// �v���[����
		DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE, GetColor(255,255,255), "[��%d]%s", ply_i+1, tk->plyname[ply_i]);

		// �ƕ\��
		if(tk->kyoku[kyoku_index].ie[ply_i] == 0){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "����");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 1){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "���");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 2){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "����");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 3){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "�k��");
		}else{
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "�s��");
		}

		// ���_
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*1, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i]);
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].kyoku_score[ply_i]);
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*3, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_end_score[ply_i]);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ǏI���\��(�r���[�A���[�h�FMJAI���O)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispViewerKyokuEnd_mjailog(MJSTkinfo *tk, int kyoku_index, int tmp_actid){

	// ----------------------------------------
	// ������
	// ----------------------------------------
	int tmp_disp_yaku_count = 0;  
	int disp_agari_num = 0;

	// ----------------------------------------
	// ��ʔԍ��Z�o
	// ----------------------------------------

	// �a����ʔԍ��̊m�F
	for(int tmp_disp_num = 0; tmp_disp_num < tk->kyoku[kyoku_index].agari_ply_count; tmp_disp_num++){
		if( tk->kyoku[kyoku_index].ply_agari_yk[tmp_disp_num].agari_ply_num == tk->kyoku[kyoku_index].act_ply[tmp_actid]){
			disp_agari_num = tmp_disp_num;
		}
	}

	// ----------------------------------------
	// ���Ǐ��
	// ----------------------------------------
	if(tk->kyoku[kyoku_index].ply_agari_yk[0].ryukyoku_flg == true){

		// ���ǌ��ʂ�\��
		if(       tk->kyoku[kyoku_index].ply_agari_yk[0].ryukyoku_stat == HOWANPAI ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[HOWANPAI]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[0].ryukyoku_stat == SUFURENDA ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[SUFURENDA]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[0].ryukyoku_stat == RIICHI4PLY ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[RIICHI4PLY]);
		}else if( tk->kyoku[kyoku_index].ply_agari_yk[0].ryukyoku_stat == UNKNOWNRKK ){
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[UNKNOWNRKK]);
		}

	// ----------------------------------------
	// �a�����ʕ\��
	// ----------------------------------------
	}else{

		// ��v�\��
		DispKyokuEndTehai(tk, kyoku_index, disp_agari_num);

		// �|���\��
		DispKyokuEndHanInfo(tk, kyoku_index, disp_agari_num);

		// �a�����̏ڍ׏��
		DispKyokuEndYakuInfo(tk, kyoku_index, tmp_actid, disp_agari_num);

	}

	// ----------------------------------------
	// �v���[���̓��_��
	// ----------------------------------------
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){

		// �v���[����
		DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE, GetColor(255,255,255), "[��%d]%s", ply_i+1, tk->plyname[ply_i]);

		// �ƕ\��
		if(tk->kyoku[kyoku_index].ie[ply_i] == 0){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "����");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 1){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "���");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 2){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "����");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 3){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "�k��");
		}else{
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "�s��");
		}

		// ���_
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*1, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i]);
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].kyoku_score[ply_i]);
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*3, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_end_score[ply_i]);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��I���\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayGameResult(MJSTkinfo *tk, MJSGui *gui){

	// ----------------------------------------
	// �p�[�c�\��
	// ----------------------------------------

	// �v���[�g�\��
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// ----------------------------------------
	// ���_�ꗗ
	// ----------------------------------------

	// �\��
	wsprintf(tmp_disp_msg, "���с@�F");
	dparts->DispString(GAMERESULT_X_START, GAMERESULT_Y_START, tmp_disp_msg);

	// ���ʕ\��
	for(int rank = 0; rank < PLAYER_MAX; rank++){

		// ���ʈꗗ
		wsprintf(tmp_disp_msg, "%d�ʁ@�F�@%s", rank+1, tk->plyname[tk->plyjun[rank]] );
		dparts->DispString(  GAMERESULT_X_START, GAMERESULT_Y_START+50 + 50 * rank, tmp_disp_msg);

		// ���_�\��
		wsprintf(tmp_disp_msg, "�@%4d", tk->plyEndscore[rank] );
		dparts->DispString( GAMERESULT_X_START+300, GAMERESULT_Y_START+50 + 50 * rank, tmp_disp_msg);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��Q�[���I���\��(�r���[�A���[�h)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispViewerGameResult(MJSTkinfo *tk){

	// �\��
	wsprintf(tmp_disp_msg, "���с@�F");
	dparts->DispString(GAMERESULT_X_START, GAMERESULT_Y_START, tmp_disp_msg);

	// ���ʕ\��
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){

		// ���ʈꗗ
		wsprintf(tmp_disp_msg, "[��%d]%s", tmp_pnum+1, tk->plyname[tmp_pnum] );
		dparts->DispString(  GAMERESULT_X_START, GAMERESULT_Y_START+50 + 50 * tmp_pnum, tmp_disp_msg);

		// ���_�\��
		wsprintf(tmp_disp_msg, "�@%8d", tk->plyEndscore[tmp_pnum] );
		dparts->DispString( GAMERESULT_X_START+300, GAMERESULT_Y_START+50 + 50 * tmp_pnum, tmp_disp_msg);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �v�R�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispYamahai(MJSTkinfo *tk){

	// �v�R�E�v�RINDEX�\��
	for(int ply_i = 0; ply_i < 8; ply_i++){
		for(int ply_j = 0; ply_j < 17; ply_j++){
			DrawFormatString(SPACE_XSIZE+42*ply_j, PLY_YSTART+20*ply_i, GetColor(255,255,255), "%2d-%d ", tk->hai_yama[ply_i*17+ply_j], tk->yamahai_index[ply_i*17+ply_j]);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// MJAI�N���C�A���g���[�h�F���C������
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayMjaiClientTaku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// ----------------------------------------
	// �����`�揈��
	// ----------------------------------------
	dparts->DispPartsClearDraw();

	// ----------------------------------------
	// �p�[�c�\��
	// ----------------------------------------

	// �o�i�[
	dparts->DispBunner(ver1, ver2, ver3, ver4, ver5);

	// �}�E�X�|�C���g
	dparts->DispMousepoint(SPACE_XSIZE, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);

	// FPS
	dparts->DispFps(670, 750, mFps, total_frame_count, gui->frame_count);

	// �f�o�O���
	if(disp_debug_info_mode == TRUE){
		// �N���C�A���g���[�h���̕\��
		DisplayClientModeInfo(tk, gui, SPACE_XSIZE, DEBUG_INFO_Y_STAT + STRING_YSIZE);
	}

	/*-----------------------------------------------------------*/
	// �X�e�[�^�X���Ƃ̃p�[�c�\��(�ڑ����)
	/*-----------------------------------------------------------*/
	if( gui->cli_mode == GUI_MJAI_NOTCONNECT              ||
	    gui->cli_mode == GUI_MJAI_CONNECT_ACTION          ||
	    gui->cli_mode == GUI_MJAI_ERR_CONNECT             ||
	    gui->cli_mode == GUI_MJAI_WAIT_HELO_RESMES        ||
	    gui->cli_mode == GUI_MJAI_WAIT_TAKU_START_RESMES  ||
	    gui->cli_mode == GUI_MJAI_WAIT_KYOKU_START_RESMES ||
	    gui->cli_mode == GUI_MJAI_DISCONNECT              ){

		// �ڑ��m�F
		DisplayMjaiConnect(tk,gui);

	/*-----------------------------------------------------------*/
	// �X�e�[�^�X���Ƃ̃p�[�c�\��(�ꌈ�ߕ\��)
	/*-----------------------------------------------------------*/
	}else if( gui->cli_mode == GUI_MJAI_BAGIME                  || 
	          gui->cli_mode == GUI_MJAI_WAIT_KYOKU_START_RESMES ){

		// �ꌈ�ߕ\��
		DisplayClientModeBagime(tk, gui, tk->kyoku_index);

	/*-----------------------------------------------------------*/
	// �X�e�[�^�X���Ƃ̃p�[�c�\��(�샂�[�h�\��)
	/*-----------------------------------------------------------*/
	}else if(gui->cli_mode == GUI_MJAI_HAIPAI                ||
	         gui->cli_mode == GUI_MJAI_WAIT_TAKU_RESMES      ||
	         gui->cli_mode == GUI_MJAI_WAIT_TAKU_PLYACT      ||
	         gui->cli_mode == GUI_MJAI_WAIT_SED_MES          ||
	         gui->cli_mode == GUI_MJAI_CHECK_DISCONNECT      ){

		// �ǏI���\���Ȃ�
		if(tk->stat == KYOKURESULT || tk->stat == KYOKUEND){
			// �a�����
			DisplayMjaiClientKyokuEnd(tk, gui, tk->kyoku_index);
		// �ǏI���\���Ȃ�
		}else if(tk->stat == TAKURESULT || tk->stat == TAKUEND){
			// ��I��
			DisplayMjaiClientGameResult(tk, gui);
		// ����ȊO�Ȃ�
		}else{
			// ��\�����[�h
			DispyMjaiClientNormalTakuStat(tk, ply, gui);
		}

	/*-----------------------------------------------------------*/
	// �X�e�[�^�X���Ƃ̃p�[�c�\��(�ǏI��)
	/*-----------------------------------------------------------*/
	}else if(gui->cli_mode == GUI_MJAI_KYOKUEND){

		// �a�����
		DisplayMjaiClientKyokuEnd(tk, gui, tk->kyoku_index);

	/*-----------------------------------------------------------*/
	// �X�e�[�^�X���Ƃ̃p�[�c�\��(��I��)
	/*-----------------------------------------------------------*/
	}else if(gui->cli_mode == GUI_MJAI_TAKURESULT){

		// ��I��
		DisplayMjaiClientGameResult(tk, gui);

	/*-----------------------------------------------------------*/
	// �X�e�[�^�X���Ƃ̃p�[�c�\��(�G���[�\��)
	/*-----------------------------------------------------------*/
	}else if(gui->cli_mode == GUI_MJAI_ERR_RES_MES){

		// �G���[�\��
		DisplayMjaiClientErrMes(tk, gui);

	}

	/*-----------------------------------------------------------*/
	// ����ʂ�\��ʂɔ��f
	/*-----------------------------------------------------------*/
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// MJAI�N���C�A���g���[�h�F�ڑ��m�F
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayMjaiConnect(MJSTkinfo *tk, MJSGui *gui){

	// �ڑ�����
	DrawFormatString(50, 250, GetColor(255,255,255), "�ڑ���IP�A�h���X�F%d.%d.%d.%d", 127,0,0,1);

	// �X�e�[�^�X���b�Z�[�W�̕\��
	DrawFormatString(50, 300, GetColor(255,255,255), gui->stat_mes);

	// Socket��M���b�Z�[�W�̕\��
	if( gui->cli_mode == GUI_MJAI_WAIT_HELO_RESMES        || 
	    gui->cli_mode == GUI_MJAI_WAIT_TAKU_START_RESMES  ||
	    gui->cli_mode == GUI_MJAI_WAIT_KYOKU_START_RESMES ){

		// ��M���b�Z�[�W��\��
		DrawFormatString(50, 320, GetColor(255,255,255), gui->res_mes);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ꌈ�ߏ��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayClientModeBagime(MJSTkinfo *tk, MJSGui *gui, int kyoku_index){

	/*-----------------------------------------------------------*/
	// �v���[�����̕\��
	/*-----------------------------------------------------------*/

	// �X�e�[�^�X���b�Z�[�W
	DrawFormatString(BAGIME_X_START, BAGIME_Y_START, GetColor(255,255,255), gui->stat_mes);

	// �v���[�����(Ply_id��)
	DrawFormatString(BAGIME_X_START, 70, GetColor(255,255,255), "Hum_Ply_id %d", tk->ply_mjai_hum_id);
	for(int tmp_ply_id = 0; tmp_ply_id < PLAYER_MAX; tmp_ply_id++){
		for(int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++){
			if(tk->ply_mjai_id[tmp_i] == tmp_ply_id){
				DrawFormatString(BAGIME_X_START , BAGIME_Y_START + 40 + tmp_ply_id * 20, GetColor(255,255,255), "Ply_id:%d [��%d] %s", tmp_ply_id, tmp_i+1, tk->plyname[tmp_i]);
			}
		}
	}

	/*-----------------------------------------------------------*/
	// �N���b�N�ē�
	/*-----------------------------------------------------------*/
	wsprintf(tmp_disp_msg, "�N���b�N���Ă�������");
	dparts->DispString( 100, 450, tmp_disp_msg);

	// �v���[�g�\��
	// dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

/*
	// �v���[�����(�ȏ�)
	DrawFormatString(50, 70, GetColor(255,255,255), "Hum_Ply_id %d", tk->ply_mjai_hum_id);
	for(int tmp_i = 0; tmp_i < 4; tmp_i++){
		DrawFormatString(50 , 90 + tmp_i * 20, GetColor(255,255,255), "[��%d]:Ply_id %d:%s�F", tmp_i+1, tk->ply_mjai_id[tmp_i], tk->plyname[tmp_i]);
	}
*/

/*
	// �\��
	dparts->DispString( 50, 50, tk->tkname );

	// �ȕ\��
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){

		// �v���[����
		if(tk->kyoku[kyoku_index].ie[tmp_pnum] == 0){
			DrawFormatString(50, 100 + 50 * tmp_pnum, GetColor(255,255,255), "[��%d]���Ɓ@%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[kyoku_index].ie[tmp_pnum] == 1){
			DrawFormatString(50, 100 + 50 * tmp_pnum, GetColor(255,255,255), "[��%d]��Ɓ@%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[kyoku_index].ie[tmp_pnum] == 2){
			DrawFormatString(50, 100 + 50 * tmp_pnum, GetColor(255,255,255), "[��%d]���Ɓ@%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else if(tk->kyoku[kyoku_index].ie[tmp_pnum] == 3){
			DrawFormatString(50, 100 + 50 * tmp_pnum, GetColor(255,255,255), "[��%d]�k�Ɓ@%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}else{
			DrawFormatString(50, 100 + 50 * tmp_pnum, GetColor(255,255,255), "[��%d]�s���@%s", tmp_pnum+1, tk->plyname[tmp_pnum]);
		}

	}
*/

}

/* ---------------------------------------------------------------------------------------------- */
// �ʏ�̑�\��(�N���C�A���g���[�h)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispyMjaiClientNormalTakuStat(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// �Ǐ��
	// -----------------------------------------------------------

	// �Ǐ��
	DispKyokuInfo(tk,tk->kyoku_index);

	// �h��
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 tk->kyoku[tk->kyoku_index].act_count);

	// �{�^���\��
	// dparts->DispGameModeButton();
	dparts->DispInfoButton(THINFO_BUT_X_STAT, TKINFO_BUT_X_STAT, PLYINFO_BUT_X_STAT, QUIT_BUT_X_STAT, BUT02_Y_STAT);

	// �v���[�g�\��
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// �v���[�g�L/��
	dparts->DispPltNakiAriNashi(PLT_NAKIARI_X_STAT, PLT_Y_STAT, gui->plt_nakiari_flg);

	// ��v���C�����b�Z�[�W
	DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);

	// -----------------------------------------------------------
	// ��GUI���[�h(gui->gui_taku_mode)���Ƃ̕\��
	// -----------------------------------------------------------

		// -----------------------------------------------------------
		// �u��v���C�i�[�v���[�h�\��
		// -----------------------------------------------------------
		if( gui->disp_tehai_mode == 0 ){

			// ���C�i�[���[�h�\��(COM)
			for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++ ) {

				// ��v
				if( tmp_pnum == HUM_PLY_SEKI_NUM){
					// ��v(HUM�\��)
					DispActTehaiHum(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}else{
					// ��v(COM�\��)
					DispActTehaiCom(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}

				// �N���\��
				DispActSarashi(tk, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// �͕\��(���C�i�[�\��)
				DispActKawa(tk, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// �v���[�����Ƃ̓��_���
				DispPlyInfo(tk, tk->kyoku_index, tmp_pnum);

			}

		// -----------------------------------------------------------
		// �u��v�͂݁v���[�h�\��
		// -----------------------------------------------------------
		}else if( gui->disp_tehai_mode == 1 ){

			// �Z���^�[�v���[�g
			dparts->DispCenterPlt( (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3,
			                       (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 );

			// ��v�͂݃��[�h�\��
			for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX ; tmp_pnum++ ) {

				// ��v
				if( tk->ply_hum_mode == 1 && tmp_pnum == HUM_PLY_SEKI_NUM){
					// ��v(HUM�\��)
					DispActTehaiHum(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}else{
					// ��v(COM�\��)
					DispActTehaiCom_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum, gui->msx, gui->msy);
				}

				// �N���\��
				DispActSarashi_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// �͕\��
				DispActKawa_square(tk, gui, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count, tmp_pnum);

				// �v���[�����Ƃ̓��_���
				DispPlyInfo(tk, tk->kyoku_index, tmp_pnum);

			}

		// -----------------------------------------------------------
		// �u�e�X�g�\���v���[�h
		// -----------------------------------------------------------
		}else if( gui->disp_tehai_mode == 2 ){

			// �͂ݎ�v�̃T���v���\��
			DispActTehai_test_square(gui);

		}

	// -----------------------------------------------------------
	// �I���\��
	// -----------------------------------------------------------
	// }else if(gui->gui_taku_mode == COMMON_END_CHECK_MODE){

		// �I���{�^���̊m�F
		// DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);

	// -----------------------------------------------------------
	// tkinfo�N���X���
	// -----------------------------------------------------------
	// }else if(gui->gui_taku_mode == COMMON_TKINFO_MODE){

		// tkinfo�N���X�\��
		// DisplayTkinfoDetail(tk);

}

/* ---------------------------------------------------------------------------------------------- */
// �a�����ʕ\��(�N���C�A���g���[�h)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayMjaiClientKyokuEnd(MJSTkinfo *tk, MJSGui *gui, int kyoku_index){

	// �f�o�O�p
	int disp_agari_num=0;

	// -----------------------------------------------------------
	// �Ǐ��
	// -----------------------------------------------------------

	// �Ǐ��
	DispKyokuInfo(tk,tk->kyoku_index);

	// �h��
	// dparts->DispDora(DORA_XSIZE, 5, tk->kyoku[tk->kyoku_index].doracount, tk->kyoku[tk->kyoku_index].dora, tk->kyoku[tk->kyoku_index].dora_aka);
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// �a�����F��L�莞
	// ----------------------------------------

	// �ϐ���`
	int tmp_disp_yaku_count = 0;

	// �a���t���O�m�F
	if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_flg == false ){

		// �a�����̏ڍו\��
		// DispClientKyokuEndYakuari(tk, gui, kyoku_index);

		// �a���v���[��
		if (tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].tsumo_agari_flg == true){
			DrawFormatString(5, PLY_YSTART+50, GetColor(255,255,255), "���̘a���@�a��[��%d]", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num+1);
		}else{
			DrawFormatString(5, PLY_YSTART+50, GetColor(255,255,255), "�����a���@�a��[��%d]�@���e�F[��%d]", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num+1, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].furikomi_ply_num+1);
		}

		// ��v�p�[�c�̕\��(�l�v���[���p_���̖����F�J�[�\���I�𖳂�)
		dparts->DispActTehaiParts( SPACE_XSIZE, PLY_YSTART,
	                      tk->kyoku[kyoku_index].agari_tehaicount,    
	                      tk->kyoku[kyoku_index].agari_tehaitbl,      
	                      tk->kyoku[kyoku_index].agari_tehaitbl_aka,  
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_hai,        // ���̔v�F�a���v
	                      tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_aka,        // ���̐ԁF�a���v��
	                      EXCEPT_VALUE,                               // �̔v�F�Ȃ�
	                      EXCEPT_VALUE, EXCEPT_VALUE, false);         // �J�[�\���I���F�Ȃ�

		// �N���v�\��
		dparts->DispAllSarashiParts(600, PLY_YSTART,
		tk->kyoku[kyoku_index].naki_count[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num], 
		tk->kyoku[kyoku_index].naki_stat[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],
		tk->kyoku[kyoku_index].naki_hai[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],
		tk->kyoku[kyoku_index].naki_idx[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num],
		tk->kyoku[kyoku_index].naki_aka[tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_num]);

		// �ʏ��(�𖞂Ȃ���)
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_count == 0 ){

			// �ʏ���m�F
			for(int tmp_i = 0; tmp_i < YAKU_SHUBETSU_MAX; tmp_i++){

				// ��ݒ�L��
				if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yaku_flg[tmp_i] == true){

					// �ʖ�
					// wsprintf(tmp_disp_msg, "%s", tk->kyoku[kyoku_index].yakuname[tmp_i]);
					wsprintf(tmp_disp_msg, "%s �c %d�|", dparts->yakuname[tmp_i], tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yaku_han[tmp_i]);
					dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, tmp_disp_msg);
					tmp_disp_yaku_count++;
				}
			}

		// ���v�|�̕\��
		DrawFormatString(AGARI_INFO_X1, PLY_YSTART+355, GetColor(255,255,255), "%3d���@%2d�|", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].scoreFu, tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].agari_ply_han);

		// ----------------------------------------
		// �𖞎�
		// ----------------------------------------
		}else{

			// �𖞊m�F
			for(int tmp_i = 0; tmp_i < YAKUMAN_SHUBETSU_MAX; tmp_i++){

				// ��ݒ�L��
				if(tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].yakuman_flg[tmp_i] == true){

					// ���e�[�u���ݒ�
					// wsprintf(tk->kyoku[kyoku_index].yakuname[tk->kyoku[kyoku_index].yakuman_count], "%s �c �𖞁@�@", dparts->yakumanname[tmp_i], 1);
					wsprintf(tmp_disp_msg, "%s �c �𖞁@�@", dparts->yakumanname[tmp_i]);
					dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, tmp_disp_msg);
					tmp_disp_yaku_count++;

				}

			}
		}

	// ----------------------------------------
	// ���ǎ�
	// ----------------------------------------
	}else{

		// �r�v
		if( tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].ryukyoku_stat == HOWANPAI ){
			// ������\��
			dparts->DispString( 10, PLY_YSTART + 100 + STRING_YSIZE * tmp_disp_yaku_count, dparts->ryukyokuname[HOWANPAI]);
		}
	}

	// ----------------------------------------
	// �v���[���̓��_��
	// ----------------------------------------
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){

		// �v���[����
		DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE, GetColor(255,255,255), "[��%d]%s", ply_i+1, tk->plyname[ply_i]);

		// �ƕ\��
		if(tk->kyoku[kyoku_index].ie[ply_i] == 0){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "����");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 1){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "���");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 2){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "����");
		}else if(tk->kyoku[kyoku_index].ie[ply_i] == 3){
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "�k��");
		}else{
			DrawFormatString(800, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE, GetColor(255,255,255), "�s��");
		}

		// �J�n���_
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*1, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_start_score[ply_i]);

		// �ǂ̓��_
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*2, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_agari_yk[disp_agari_num].kyoku_score[ply_i]);

		// �I�����_
		DrawFormatString(840, PLY_YSTART+ply_i*PLY_YSIZE + STRING_YSIZE*3, GetColor(255,255,255), "%6d", tk->kyoku[kyoku_index].ply_kyoku_end_score[ply_i]);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��I���\��(�N���C�A���g���[�h)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayMjaiClientGameResult(MJSTkinfo *tk, MJSGui *gui){

	// ----------------------------------------
	// �p�[�c�\��
	// ----------------------------------------

	// �v���[�g�\��
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// ----------------------------------------
	// ���_�ꗗ
	// ----------------------------------------

	// �\��
	wsprintf(tmp_disp_msg, "���с@�F");
	dparts->DispString(GAMERESULT_X_START, GAMERESULT_Y_START, tmp_disp_msg);

	// �v���[�����
	for(int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++){
		// �v���[����
		wsprintf(tmp_disp_msg, "[��%d] Ply_id:%d�@%s", tmp_pnum+1, tk->ply_mjai_id[tmp_pnum], tk->plyname[tmp_pnum]);
		dparts->DispString(  GAMERESULT_X_START, GAMERESULT_Y_START+50 + 50 * tmp_pnum, tmp_disp_msg);
		// ���_�\��
		wsprintf(tmp_disp_msg, "%10d", tk->plyEndscore[tmp_pnum] );
		dparts->DispString( GAMERESULT_X_START+300, GAMERESULT_Y_START+50 + 50 * tmp_pnum, tmp_disp_msg);

	}

/*
	// ���ʕ\��
	for(int rank = 0; rank < 4; rank++){

		// ���ʈꗗ
		wsprintf(tmp_disp_msg, "%d�ʁ@�F�@%10s", rank+1, tk->plyname[tk->plyjun[rank]] );
		dparts->DispString(  50, 100 + 50 * rank, tmp_disp_msg);

		// ���_�\��
		wsprintf(tmp_disp_msg, "�@%4d", tk->plyEndscore[rank] );
		dparts->DispString( 250, 100 + 50 * rank, tmp_disp_msg);

	}
*/
}

/* ---------------------------------------------------------------------------------------------- */
// �G���[�\��(�N���C�A���g���[�h)
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayMjaiClientErrMes(MJSTkinfo *tk, MJSGui *gui){

	// -----------------------------------------------------------
	// �Ǐ��
	// -----------------------------------------------------------

	// �Ǐ��
	DispKyokuInfo(tk,tk->kyoku_index);

	// �h��
	// dparts->DispDora(DORA_XSIZE, 5, tk->kyoku[tk->kyoku_index].doracount, tk->kyoku[tk->kyoku_index].dora, tk->kyoku[tk->kyoku_index].dora_aka);
	dparts->DispDora(DORA_XSIZE, SPACE_YSIZE, 
	                 tk->kyoku[tk->kyoku_index].doracount, 
	                 tk->kyoku[tk->kyoku_index].dora, 
	                 tk->kyoku[tk->kyoku_index].dora_aka,
	                 tk->kyoku[tk->kyoku_index].dora_actid,
	                 tk->kyoku[tk->kyoku_index].act_count);

	// �{�^���\��
	// dparts->DispGameModeButton();
	dparts->DispInfoButton(THINFO_BUT_X_STAT, TKINFO_BUT_X_STAT, PLYINFO_BUT_X_STAT, QUIT_BUT_X_STAT, BUT02_Y_STAT);

	// �v���[�g�\��
	dparts->DispPltline(SPACE_XSIZE, PLT_Y_STAT, PLT_ICON_XSIZE+SPACE_XSIZE, gui->plt_mode);

	// ��v���C�����b�Z�[�W
	// DispTehaiLineMessage(tk, gui, PLY_MES_X_STAT, PLY_MES_Y_STAT);

}

/* ---------------------------------------------------------------------------------------------- */
// �N���C�A���g���[�h�F����
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayClientModeInfo(MJSTkinfo *tk, MJSGui *gui, int x, int y){

	// -----------------------------------------------------------
	// GUI�X�e�[�^�X���(0�i�ځE1�Ԗ�)
	// -----------------------------------------------------------

	// �N���C�A���g���[�hGUI�X�e�[�^�X
	DisplayGuiClientMode(gui, x, y);

	// ��v����
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){
		DisplayTkinfoDetail_sub_tehai_count(tk, x+300+tmp_pnum*150, y, tmp_pnum);
	}

	// -----------------------------------------------------------
	// GUI���(1-2�i��)
	// -----------------------------------------------------------

	// GUI���
	DispGuiInfo(gui, x, y+STRING_YSIZE);

	// -----------------------------------------------------------
	// TkInfo���(3-4�i��)
	// -----------------------------------------------------------

	// �ʃA�N�V�������
	DispActNumInfo(tk, x, y+STRING_YSIZE*3, tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ����
	DispTakuStat(tk, x, y+STRING_YSIZE*4);

	// -----------------------------------------------------------
	// HUM���̔v(5�i�ځE1�Ԗ�)
	// -----------------------------------------------------------
	if( tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM] == true){
		DrawFormatString(x, y+STRING_YSIZE*5, GetColor(255,255,255), "Ply����%2d��", tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]);
	}else{
		DrawFormatString(x, y+STRING_YSIZE*5, GetColor(255,255,255), "Ply����%2d��", tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]);
	}

	// -----------------------------------------------------------
	// HUM���v���(5�i�ځE2�Ԗ�)
	// -----------------------------------------------------------
	// �v���C���[�̖����ڍ�
	DisplayTkinfoDetail_sub_ply_actnaki_info(tk, x+120, y+STRING_YSIZE*5, HUM_PLY_SEKI_NUM);

	// -----------------------------------------------------------
	// HUM�Ԕv����(5�i�ځE3�Ԗ�)
	// -----------------------------------------------------------
	DrawFormatString(x+500, y+STRING_YSIZE*5, GetColor(255,255,255), "[��%d]����%d,�ԓ�%d,�ԍ�%d", 
		       HUM_PLY_SEKI_NUM+1, 
		       tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][0],    // �Ԕv�����ݎq
		       tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][1],    // �Ԕv�������q
		       tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][2]);   // �Ԕv�������q

	// -----------------------------------------------------------
	// �S�v���[���̎̔v(6�i��)
	// -----------------------------------------------------------
	for(int tmp_pnum = 0; tmp_pnum < 4; tmp_pnum++){
		if(tk->ply_act_sute_aka[tmp_pnum] == true){
			DrawFormatString(x+tmp_pnum*120, y+STRING_YSIZE*6, GetColor(255,255,255), "[��%d]��%2d��",tmp_pnum+1, tk->ply_act_sute[tmp_pnum]);
		}else{
			DrawFormatString(x+tmp_pnum*120, y+STRING_YSIZE*6, GetColor(255,255,255), "[��%d]��%2d��",tmp_pnum+1, tk->ply_act_sute[tmp_pnum]);
		}
	}

	// -----------------------------------------------------------
	// Socket���(7-8�i��)
	// -----------------------------------------------------------
	DrawFormatString(x, y+STRING_YSIZE*7, GetColor(255,255,255), gui->res_mes);  // ��M���b�Z�[�W
	DrawFormatString(x, y+STRING_YSIZE*8, GetColor(255,255,255), gui->snd_mes);  // ���M���b�Z�[�W

	// -----------------------------------------------------------
	// ���[�`���(7-8�i��)
	// -----------------------------------------------------------
/*
	// �̔v�s�e�[�u�����
	DrawFormatString(x, y+STRING_YSIZE*7, GetColor(255,255,255), "����%2d",gui->cannot_sutehai_count);
	for(int tmp_i = 0; tmp_i < gui->cannot_sutehai_count; tmp_i++){
		DrawFormatString(x+100+tmp_i*50, y+STRING_YSIZE*7, GetColor(255,255,255), "%2d ",gui->cannot_sutehai[tmp_i] );
	}

	// �V�����e�����
	for(int tmp_i = 0; tmp_i < TEHAI_MAX; tmp_i++){
		DrawFormatString(x+80+tmp_i*50, y+STRING_YSIZE*8, GetColor(255,255,255), "%2d:%2d ",tmp_i, tk->ply_act_tehai_shanten_tbl[HUM_PLY_SEKI_NUM][tmp_i]);
	} */

	// -----------------------------------------------------------
	// wk_str���
	// -----------------------------------------------------------
/*
	// ��؂�s�̒l
	const int row_num = 7;

	// work������\��(X�i��)
	for(int tmp_rank = 0; tmp_rank < 10; tmp_rank++){
		if( gui->wk_str_count > row_num*tmp_rank && gui->wk_str_count <= row_num*(tmp_rank+1) ){
			// �ꕔ�\��
			for(int tmp_i = row_num*tmp_rank; tmp_i < gui->wk_str_count; tmp_i++){
				// DrawFormatString(x + 150 * (tmp_i-row_num*tmp_rank), y+50+20*tmp_rank, GetColor(255,255,255), gui->wk_str[tmp_i]);
				wsprintf(tmp_disp_msg, "%2d:%s", tmp_i, gui->wk_str[tmp_i]);
				DrawFormatString(x + 150 * (tmp_i-row_num*tmp_rank), y+64+16*tmp_rank, GetColor(255,255,255), tmp_disp_msg);
			}
		}else{
			// �t���\��
			for(int tmp_i = row_num*tmp_rank; tmp_i < row_num*(tmp_rank+1); tmp_i++){
				// DrawFormatString(x + 150 *  (tmp_i-row_num*tmp_rank), y+50+20*tmp_rank, GetColor(255,255,255), gui->wk_str[tmp_i]);
				wsprintf(tmp_disp_msg, "%2d:%s", tmp_i, gui->wk_str[tmp_i]);
				DrawFormatString(x + 150 * (tmp_i-row_num*tmp_rank), y+64+16*tmp_rank, GetColor(255,255,255), tmp_disp_msg);
			}
		}
	}
*/


/*

	// work������\��(1�i��)
	if(gui->wk_str_count <= 8){
		for(int tmp_i = 0; tmp_i < gui->wk_str_count; tmp_i++){
			DrawFormatString(x + 150 * tmp_i, y+50, GetColor(255,255,255), gui->wk_str[tmp_i]);
		}
	}else{
		for(int tmp_i = 0; tmp_i < 8; tmp_i++){
			DrawFormatString(x + 150 * tmp_i, y+50, GetColor(255,255,255), gui->wk_str[tmp_i]);
		}
	}

	// work������\��(2�i��)
	if(gui->wk_str_count > 8 && gui->wk_str_count <= 8*2){
		for(int tmp_i = 8*1; tmp_i < gui->wk_str_count; tmp_i++){
			DrawFormatString(x + 150 * tmp_i, y+50, GetColor(255,255,255), gui->wk_str[tmp_i]);
		}
	}else{
		for(int tmp_i = 8*1; tmp_i < 8*2; tmp_i++){
			DrawFormatString(x + 150 * tmp_i, y+50, GetColor(255,255,255), gui->wk_str[tmp_i]);
		}
	}*/


}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V������v�\���E���C�i�[HUM�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActTehaiHum(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum, int msx, int msy){

	// ������
	int tmp_sute_stat=0;                // ���p�̎̔v�̈ʒu�ԍ�

	// -----------------------------------------------------------
	// �ȏ��
	// -----------------------------------------------------------

	// �ȏ��ݒ�
	wsprintf(tmp_disp_msg,"[��%d]%s", pnum+1, tk->plyname[pnum]);

	// ���v���[���[�̐ȏ���`
	dparts->DispString( gui->tehai_x, 
	                    gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                   tmp_disp_msg);

	// -----------------------------------------------------------
	// 1.��v�\���F���̎�
	// -----------------------------------------------------------

	if ( ( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMO || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYRINSHAN  || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI ) &&
	       tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

			// �J���I�����[�h�Ȃ�
			if( gui->gui_ply_tehai_mode == TEHAI_ANKAN_KAKAN_SELECT ){

				// �}�E�X�ʒu�̊m�F(�ʏ탂�[�h)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

						// ��v�p�[�c�̕\��(�l�v���[���p�F�J�[�\���I������)
						dparts->DispActHumKanSelectTehaiParts( SPACE_XSIZE, 
					                   PLY_YSTART+pnum*PLY_YSIZE+40, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   gui->naki_ankan_hai[0],
					                   gui->naki_ankan_hai[1],
					                   gui->naki_ankan_hai[2],
					                   gui->naki_kakan_hai[0],
					                   gui->naki_kakan_hai[1],
					                   gui->naki_kakan_hai[2],
					                   (msx-gui->tehai_x)/HAI_XSIZE);

				// �}�E�X�ʒu�̊m�F(���̔v)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE){

						dparts->DispActHumKanSelectTehaiParts( SPACE_XSIZE, 
					                   PLY_YSTART+pnum*PLY_YSIZE+40, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   gui->naki_ankan_hai[0],
					                   gui->naki_ankan_hai[1],
					                   gui->naki_ankan_hai[2],
					                   gui->naki_kakan_hai[0],
					                   gui->naki_kakan_hai[1],
					                   gui->naki_kakan_hai[2],
					                   tk->ply_act_tehaicount[pnum]);

				// ��v�I�����Ă��Ȃ��Ȃ�
				}else{

						dparts->DispActHumKanSelectTehaiParts( SPACE_XSIZE, 
					                   PLY_YSTART+pnum*PLY_YSIZE+40, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum],
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->kyoku[kyoku_index].act_hai[actid],
					                   tk->kyoku[kyoku_index].act_aka[actid],
					                   gui->naki_ankan_hai[0],
					                   gui->naki_ankan_hai[1],
					                   gui->naki_ankan_hai[2],
					                   gui->naki_kakan_hai[0],
					                   gui->naki_kakan_hai[1],
					                   gui->naki_kakan_hai[2],
			                           EXCEPT_VALUE);

				} // �}�E�X�ʒu�̊m�F(�J���I�����[�h)�I���

			// �ʏ탂�[�h�Ȃ�
			}else{

				// �}�E�X�ʒu(��v��)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts(gui->tehai_x,                                         // ��vX�ʒu
					                      gui->tehai_y,                                             // ��vY�ʒu
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM],                 // ��v����
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],                   // ��v�e�[�u��
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],              // ��v�e�[�u���E�Ԕv
					                      tk->kyoku[kyoku_index].act_hai[actid],                    // ���̔v�F�A�N�V����ID
					                      tk->kyoku[kyoku_index].act_aka[actid],                    // ���̐ԁF�A�N�V����ID
						                  EXCEPT_VALUE,                                             // �̔v�F�Ȃ�
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // �J�[�\���I���F��v


				// �}�E�X�ʒu(���̔v)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE ){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I�����̔v)
					dparts->DispActTehaiParts( gui->tehai_x,                                        // ��vX�ʒu
					                      gui->tehai_y,                                             // ��vY�ʒu
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM],                 // ��v����
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],                   // ��v�e�[�u��
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],              // ��v�e�[�u���E�Ԕv
					                      tk->kyoku[kyoku_index].act_hai[actid],                    // ���̔v�F�A�N�V����ID
					                      tk->kyoku[kyoku_index].act_aka[actid],                    // ���̐ԁF�A�N�V����ID
					                      EXCEPT_VALUE,                                             // �̔v�F�Ȃ�
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], EXCEPT_VALUE,false);  // �J�[�\���I���F���̔v

				// �}�E�X�ʒu(��v�O)
				}else{

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I���Ȃ�)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid],                    // ���̔v�F�A�N�V����ID
					                      tk->kyoku[kyoku_index].act_aka[actid],                    // ���̐ԁF�A�N�V����ID
					                      EXCEPT_VALUE,
					                      EXCEPT_VALUE, EXCEPT_VALUE,false);

				} // �}�E�X�ʒu

			} // �J���I�����[�h�Ȃ�

	// -----------------------------------------------------------
	// 2.��v�\���F���̎����[�`�錾
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRIICH &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum        ){

			// �}�E�X�ʒu�̊m�F
			if( msx > gui->tehai_x && 
			    msx < gui->tehai_x + 13*HAI_XSIZE && 
			    msy > gui->tehai_y && 
				msy < gui->tehai_y+HAI_YSIZE){

					// ��v�p�[�c�̕\��(�l�v���[���p�F���[�`�錾�̔v�I��)
					dparts->DispActHumCanSuteParts( gui->tehai_x, 
					                   gui->tehai_y, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum], 
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->ply_act_tehai_can_sute_tbl[pnum],                        // ��v�e�[�u���F�̔v��
					                   tk->kyoku[kyoku_index].act_hai[actid-1],                     // ���̔v�F�A�N�V����ID
					                   tk->kyoku[kyoku_index].act_aka[actid-1],                     // ���̐ԁF�A�N�V����ID
					                   tk->ply_act_tsumo_can_sute[pnum],                            // ���̔v�F�̔v��
					                   (msx-gui->tehai_x)/HAI_XSIZE                                 // HUM�p�̎̔v�ʒu
					                   );

			// �}�E�X�ʒu(���̔v)
			}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
					  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
					  msy > gui->tehai_y && 
					  msy < gui->tehai_y+HAI_YSIZE ){

					// ��v�p�[�c�̕\��(�l�v���[���p�F���[�`�錾�̔v�I��)
					dparts->DispActHumCanSuteParts( gui->tehai_x, 
					                   gui->tehai_y, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum], 
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->ply_act_tehai_can_sute_tbl[pnum],                        // ��v�e�[�u���F�̔v��
					                   tk->kyoku[kyoku_index].act_hai[actid-1],                     // ���̔v�F�A�N�V����ID
					                   tk->kyoku[kyoku_index].act_aka[actid-1],                     // ���̐ԁF�A�N�V����ID
					                   tk->ply_act_tsumo_can_sute[pnum],                            // ���̔v�F�̔v��
					                   tk->ply_act_tehaicount[pnum]                                 // HUM�p�̎̔v�ʒu
					                   );

			}else{

					// ��v�p�[�c�̕\��(�l�v���[���p�F���[�`�錾�̔v�I��)
					dparts->DispActHumCanSuteParts( gui->tehai_x, 
					                   gui->tehai_y, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum], 
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->ply_act_tehai_can_sute_tbl[pnum],                        // ��v�e�[�u���F�̔v��
					                   tk->kyoku[kyoku_index].act_hai[actid-1],                     // ���̔v�F�A�N�V����ID
					                   tk->kyoku[kyoku_index].act_aka[actid-1],                     // ���̐ԁF�A�N�V����ID
					                   tk->ply_act_tsumo_can_sute[pnum],                            // ���̔v�F�̔v��
					                   999                                                          // HUM�p�̎̔v�ʒu�F��O
					                   );

			}

	// -----------------------------------------------------------
	// 3.��v�\���F���̎̔v��
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTSUTE &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum       ){

		// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
		// if (gui->cli_game_mode == GUI_MJAI_GAMEMODE_PLY_MODE){
		if ( tk->ply_hum_mode == 0 ){
			tmp_sute_stat = tk->ply_tbl_com_sutehai_statnum[HUM_PLY_SEKI_NUM];
		}else{
			tmp_sute_stat = tk->ply_tbl_hum_sutehai_statnum;
		}

		// ----------------------------------------
		// ���̂���̔v
		// ----------------------------------------
		if ( tk->kyoku[kyoku_index].act_stat[actid-1] == PLYACTTSUMO || tk->kyoku[kyoku_index].act_stat[actid-1] == PLYRINSHAN ){

				// �}�E�X�ʒu(��v��)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-1],                  // ���̔v�F�A�N�V����ID
					                      tk->kyoku[kyoku_index].act_aka[actid-1],                  // ���̐ԁF�A�N�V����ID
					                      tmp_sute_stat,                                            // �̔v�ʒu
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // �J�[�\���I���F��v

				// �}�E�X�ʒu(���̔v)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE ){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-1],                    // ���̔v�F�A�N�V����ID
					                      tk->kyoku[kyoku_index].act_aka[actid-1],                    // ���̐ԁF�A�N�V����ID
					                      tmp_sute_stat,                                                  // �̔v�ʒu
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], EXCEPT_VALUE,false);  // �J�[�\���I���F���̔v

				// �}�E�X�ʒu(��v�O)
				}else{

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-1],                  // ���̔v�F�A�N�V����ID
					                      tk->kyoku[kyoku_index].act_aka[actid-1],                  // ���̐ԁF�A�N�V����ID
					                      tmp_sute_stat,                                            // �̔v�ʒu
					                      EXCEPT_VALUE, EXCEPT_VALUE,false);                        // �J�[�\���I���F�Ȃ�

				} // �}�E�X�ʒu

		// ----------------------------------------
		// ���̂���̔v�i���[�`�j
		// ----------------------------------------
		}else if(tk->kyoku[kyoku_index].act_stat[actid-1] == PLYACTRIICH){

				// �}�E�X�ʒu(��v��)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-2],                  // ���̔v�F�A�N�V����ID
					                      tk->kyoku[kyoku_index].act_aka[actid-2],                  // ���̐ԁF�A�N�V����ID
					                      tmp_sute_stat,                                            // �̔v�ʒu
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // �J�[�\���I���F��v

				// �}�E�X�ʒu(���̔v)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE ){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-2],                    // ���̔v�F�A�N�V����ID
					                      tk->kyoku[kyoku_index].act_aka[actid-2],                    // ���̐ԁF�A�N�V����ID
					                      tmp_sute_stat,                                                  // �̔v�ʒu
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], EXCEPT_VALUE,false);  // �J�[�\���I���F���̔v

				// �}�E�X�ʒu(��v�O)
				}else{

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      tk->kyoku[kyoku_index].act_hai[actid-2],                  // ���̔v�F�A�N�V����ID
					                      tk->kyoku[kyoku_index].act_aka[actid-2],                  // ���̐ԁF�A�N�V����ID
					                      tmp_sute_stat,                                            // �̔v�ʒu
					                      EXCEPT_VALUE, EXCEPT_VALUE,false);                        // �J�[�\���I���F�Ȃ�

				} // �}�E�X�ʒu
		}

	// -----------------------------------------------------------
	// 4.��v�\���F���̐؂莞
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMOGIRI &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

				// �}�E�X�ʒu(��v��)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                             // ���̔v�F����
					                      false,                                                    // ���̐ԁFfalse
						                  EXCEPT_VALUE,                                             // �̔v�F�Ȃ�
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // �J�[�\���I���F��v

				// �}�E�X�ʒu(���̔v)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE ){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                                   // ���̔v�F����
					                      false,                                                          // ���̐ԁFfalse
					                      EXCEPT_VALUE,                                                   // �̔v�F�Ȃ�
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], EXCEPT_VALUE,false);  // �J�[�\���I���F���̔v

				// �}�E�X�ʒu(��v�O)
				}else{

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                               // ���̔v�F����
					                      false,                                      // ���̐ԁFfalse
					                      EXCEPT_VALUE,
					                      EXCEPT_VALUE, EXCEPT_VALUE,false);

				} // �}�E�X�ʒu

	// -----------------------------------------------------------
	// 5.��v�\���F���̔v��
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTNAKISUTE &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

				// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
				// if (gui->cli_game_mode == GUI_MJAI_GAMEMODE_PLY_MODE){
				if ( tk->ply_hum_mode == 0 ){
					tmp_sute_stat = tk->ply_tbl_hum_sutehai_statnum;
				}else{
					tmp_sute_stat = tk->ply_tbl_com_sutehai_statnum[HUM_PLY_SEKI_NUM];
				}

				// �}�E�X�ʒu(��v��)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                             // ���̔v�F����
					                      false,                                                    // ���̐ԁFfalse
					                      tmp_sute_stat,                                            // �̔v�ʒu
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // �J�[�\���I���F��v

				// �}�E�X�ʒu(��v�O)
				}else{

					// ��v�p�[�c�̕\��(�l�v���[���p_���̗L��F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                                   // ���̔v�F����
					                      false,                                                          // ���̐ԁFfalse
					                      tmp_sute_stat,                                                  // �̔v�ʒu
					                      EXCEPT_VALUE, EXCEPT_VALUE,false);                              // �J�[�\���I���F�Ȃ�

				} // �}�E�X�ʒu

	// -----------------------------------------------------------
	// 6.��v�\���F������
	// -----------------------------------------------------------

	}else if( ( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTPON || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYACTCHI ) &&
	       tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

			// �}�E�X�ʒu�̊m�F
			if( msx > gui->tehai_x && 
			    msx < gui->tehai_x + tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]*HAI_XSIZE && 
			    msy > gui->tehai_y && 
				msy < gui->tehai_y+HAI_YSIZE){

					// ��v�p�[�c�̕\��(�l�v���[���p�F���[�`�錾�̔v�I��)
					dparts->DispActHumCanSuteParts( gui->tehai_x, 
					                   gui->tehai_y, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum], 
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->ply_act_tehai_can_sute_tbl[pnum],                      // ��v�e�[�u���F�̔v��
					                   999,                                                        // ���̔v�F�A�N�V����ID
					                   false,                                                      // ���̐ԁF�A�N�V����ID
					                   false,                                                      // ���̔v�F�̔v��
					                   (msx-gui->tehai_x)/HAI_XSIZE                                // HUM�p�̎̔v�ʒu
					                   );

			}else{

					// ��v�p�[�c�̕\��(�l�v���[���p�F���[�`�錾�̔v�I��)
					dparts->DispActHumCanSuteParts( gui->tehai_x, 
					                   gui->tehai_y, 
					                   tk->ply_act_tehaicount[pnum], 
					                   tk->ply_act_tehaitbl[pnum], 
					                   tk->ply_act_tehai_tbl_aka[pnum],
					                   tk->ply_act_tehai_can_sute_tbl[pnum],                       // ��v�e�[�u���F�̔v��
					                   999,                                                         // ���̔v�F�A�N�V����ID
					                   false,                                                       // ���̐ԁF�A�N�V����ID
					                   false,                                                       // ���̔v�F�̔v��
					                   999                                                          // HUM�p�̎̔v�ʒu�F��O
					                   );
			}

	// -----------------------------------------------------------
	// 7.��v�\���F����ȊO�̎�v�\��(���̂Ȃ��E�̔v�Ȃ�)
	// -----------------------------------------------------------
	}else{

				// �}�E�X�ʒu(��v��)
				if( msx > gui->tehai_x && 
				    msx < gui->tehai_x + (tk->ply_act_tehaicount[pnum])*HAI_XSIZE && 
				    msy > gui->tehai_y && 
					msy < gui->tehai_y+HAI_YSIZE){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̖����F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                             // ���̔v�F����
					                      false,                                                    // ���̐ԁFfalse
						                  EXCEPT_VALUE,                                             // �̔v�F�Ȃ�
					                      (msx-gui->tehai_x)/HAI_XSIZE, EXCEPT_VALUE,false);        // �J�[�\���I���F��v

				// �}�E�X�ʒu(���̔v)
				}else if( msx > gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE && 
						  msx < gui->tehai_x+(tk->ply_act_tehaicount[pnum])*HAI_XSIZE+SPACE_XSIZE+HAI_XSIZE &&
						  msy > gui->tehai_y && 
						  msy < gui->tehai_y+HAI_YSIZE ){

					// ��v�p�[�c�̕\��(�l�v���[���p_���̖����F�J�[�\���I����v)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                                                   // ���̔v�F����
					                      false,                                                          // ���̐ԁFfalse
					                      EXCEPT_VALUE,                                                   // �̔v�F�Ȃ�
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], EXCEPT_VALUE,false);  // �J�[�\���I���F���̔v

				// �}�E�X�ʒu(��v�O)
				}else{

					// ��v�p�[�c�̕\��(�l�v���[���p_���̖����F�J�[�\���I�𖳂�)
					dparts->DispActTehaiParts( gui->tehai_x, 
					                      gui->tehai_y, 
					                      tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM], 
					                      tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM],
					                      tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM],
					                      EXCEPT_VALUE,                               // ���̔v�F����
					                      false,                                      // ���̐ԁFfalse
					                      EXCEPT_VALUE,                               // �̔v�F�Ȃ�
					                      EXCEPT_VALUE, EXCEPT_VALUE, false);         // �J�[�\���I���F�Ȃ�

				} // �}�E�X�ʒu(�����I��)

	// -----------------------------------------------------------
	// 8.�����I��
	// -----------------------------------------------------------

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �A�N�V������v�\���E���C�i�[COM�\��
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActTehaiCom(MJSTkinfo *tk, MJSGui *gui, int kyoku_index, int actid, int pnum, int msx, int msy){

	// -----------------------------------------------------------
	// �ȏ��
	// -----------------------------------------------------------

	// �ȏ��ݒ�
	wsprintf(tmp_disp_msg,"[��%d]%s", pnum+1, tk->plyname[pnum]);

	// ���v���[���[�̐ȏ���`
	dparts->DispString( gui->tehai_x, 
	                    gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                   tmp_disp_msg);

	// -----------------------------------------------------------
	// 1.��v�\���F���̎�
	// -----------------------------------------------------------
	if ( ( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTTSUMO || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYRINSHAN  || 
	       tk->kyoku[kyoku_index].act_stat[actid] == PLYTSUMOAGARI ) &&
	       tk->kyoku[kyoku_index].act_ply[actid]  == pnum ){

		// ���\���ł��邩�ǂ���
		if ( tk->com_no_chk_tehai_flg == true ){

			// ������ꂽ��v�\��(���̗L)
			dparts->DisplayUnkownTehai(0, PLY_YSTART+pnum*PLY_YSIZE+40, tk->ply_act_tehaicount[pnum], true, EXCEPT_VALUE);

		}else{

			// ��v�p�[�c�̕\��(COM��v)
			dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum], 
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum],
			                   tk->kyoku[kyoku_index].act_hai[actid],
			                   tk->kyoku[kyoku_index].act_aka[actid],
			                   EXCEPT_VALUE,
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

		}

	// -----------------------------------------------------------
	// 2.��v�\���F���̎����[�`�錾
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTRIICH &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum        ){

		// ���\���ł��邩�ǂ���
		if ( tk->com_no_chk_tehai_flg == true ){

			// ������ꂽ��v�\��(���̗L)
			dparts->DisplayUnkownTehai(0, PLY_YSTART+pnum*PLY_YSIZE+40, tk->ply_act_tehaicount[pnum], true, EXCEPT_VALUE);

		}else{

			// ��v�p�[�c�̕\��(COM��v)
			dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum], 
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum],
			                   tk->kyoku[kyoku_index].act_hai[actid-1],
			                   tk->kyoku[kyoku_index].act_aka[actid-1],
			                   EXCEPT_VALUE,
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

		}

	// -----------------------------------------------------------
	// 3.��v�\���F���̎̔v��
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTSUTE &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum       ){

		// ���\���ł��邩�ǂ���
		if ( tk->com_no_chk_tehai_flg == true ){

			// ������ꂽ��v�\��(���̎̂�)
			dparts->DisplayUnkownTehai(0, PLY_YSTART+pnum*PLY_YSIZE+40, tk->ply_act_tehaicount[pnum], true, tk->ply_tbl_com_sutehai_statnum[pnum]);

		}else{

			// 3-1.���̂���̔v�i���[�`�j
			if(tk->kyoku[kyoku_index].act_stat[actid-1] == PLYACTRIICH){

				// ��v�p�[�c�̕\��(���̂���̔v�F���[�`�錾)
				dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum], 
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum],
			                   tk->kyoku[kyoku_index].act_hai[actid-2],
			                   tk->kyoku[kyoku_index].act_aka[actid-2],
			                   tk->ply_tbl_com_sutehai_statnum[pnum],        // COM��v�̎̔v�ʒu
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

			// 3-2.�ʏ펞(���[�`�ȊO)
			}else{

				// ��v�p�[�c�̕\��(���̂���̔v)
				dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum], 
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum],
			                   tk->kyoku[kyoku_index].act_hai[actid-1],
			                   tk->kyoku[kyoku_index].act_aka[actid-1],
			                   tk->ply_tbl_com_sutehai_statnum[pnum],
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

			}

		}

	// -----------------------------------------------------------
	// 4.��v�\���F���̐؂莞������ȊO�ɏW��
	// -----------------------------------------------------------

	// -----------------------------------------------------------
	// 5.��v�\���F���̔v��
	// -----------------------------------------------------------
	}else if( tk->kyoku[kyoku_index].act_stat[actid] == PLYACTNAKISUTE &&
	          tk->kyoku[kyoku_index].act_ply[actid]  == pnum       ){

		// ���\���ł��邩�ǂ���
		if ( tk->com_no_chk_tehai_flg == true ){

			// ������ꂽ��v�\��(���̖�)
			dparts->DisplayUnkownTehai(0, 
			        PLY_YSTART+pnum*PLY_YSIZE+40, 
			        tk->ply_act_tehaicount[pnum],
			        false, 
			        tk->ply_tbl_com_sutehai_statnum[pnum]
			        );

		}else{
				// ��v�p�[�c�̕\��(COM��v�F���̂���̔v����)
				dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum],
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum], 
		                       EXCEPT_VALUE, false,
			                   tk->ply_tbl_com_sutehai_statnum[pnum],        // COM�p�̎̔v�ʒu
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

		}


	// -----------------------------------------------------------
	// 6.��v�\���F�����とCOM�����Ȃ�
	// -----------------------------------------------------------


	// -----------------------------------------------------------
	// 7.��v�\���F����ȊO�̎�v�\��(���̂Ȃ��E�̔v�Ȃ�)
	// -----------------------------------------------------------
	}else{

		// ���\���ł��邩�ǂ���
		if ( tk->com_no_chk_tehai_flg == true ){

			// ������ꂽ��v�\��(���̖�)
			dparts->DisplayUnkownTehai(0, PLY_YSTART+pnum*PLY_YSIZE+40, tk->ply_act_tehaicount[pnum], false, EXCEPT_VALUE);

		}else{
			// ��v�p�[�c�̕\��(COM��v)
			dparts->DispActTehaiParts( SPACE_XSIZE, 
			                   PLY_YSTART+pnum*PLY_YSIZE+40, 
			                   tk->ply_act_tehaicount[pnum],
			                   tk->ply_act_tehaitbl[pnum],
			                   tk->ply_act_tehai_tbl_aka[pnum], 
		                       EXCEPT_VALUE, false,
			                   EXCEPT_VALUE,
			                   EXCEPT_VALUE, EXCEPT_VALUE,false);

		}

	// -----------------------------------------------------------
	// 8.�����I��
	// -----------------------------------------------------------

	}
}

/* ---------------------------------------------------------------------------------------------- */
// �͂ݑ�\���̃e�X�g�\���p
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DispActTehai_test_square(MJSGui *gui){

	// ----------------------------------------
	// ��v���ݒ�
	// ----------------------------------------
	int tmp_tehai_tbl_count_up    =  1;
	int tmp_tehai_tbl_count_down  =  1;
	int tmp_tehai_tbl_count_left  =  1;
	int tmp_tehai_tbl_count_right =  1;

	// ��x�[�X�\��
	DrawBox( TAKU_PLT_X_STAT, TAKU_PLT_Y_STAT, TAKU_PLT_X_SIZE-1, TAKU_PLT_Y_SIZE-1, GetColor( 0, 64, 0 ), TRUE ) ;

	// �Z���^�[�v���[�g
	dparts->DispCenterPlt( (TAKU_PLT_X_SIZE + TAKU_PLT_X_STAT)/2 - HAI_XSIZE*3,
	               (TAKU_PLT_Y_SIZE + TAKU_PLT_Y_STAT)/2 - HAI_XSIZE*3 );

	// ----------------------------------------
	// �A�N�V�����v���[�g
	// ----------------------------------------

	// �A�N�V�����v���[�g_UP
	wsprintf(tmp_disp_msg,"���[�`");
	dparts->DispActplt_up( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 56, 
	                       gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                       tmp_disp_msg);

/*
	DrawBox( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 60 - 56, 
	         gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE + 4 - 23, 
	         gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 60, 
	         gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE + 4, 
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// �A�N�V�����v���[�g(����)_UP
	wsprintf(tmp_disp_msg,"���[�`");
	DrawRotaString( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX + 60 - 4, 
	                gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                1.0, 1.0, 0, 0, PI, GetColor( 255, 255, 255 ), 0, FALSE, tmp_disp_msg);
*/

	// �A�N�V�����v���[�g_DOWN
	wsprintf(tmp_disp_msg,"���[�`");
	dparts->DispActplt_down( gui->tehai_x - 56, 
	                         gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                         tmp_disp_msg);

/*
	DrawBox( gui->tehai_x - 56 - 4, 
	         gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE-4,
	         gui->tehai_x - 56 + 56,
	         gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE-4+23,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// �A�N�V�����v���[�g(����)_DOWN
	dparts->DispString( gui->tehai_x - 56, gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, tmp_disp_msg);
*/

	// �A�N�V�����v���[�g_LEFT
	wsprintf(tmp_disp_msg,"���[�`");
	dparts->DispActplt_left( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                         gui->tehai_left_y - 56,
	                         tmp_disp_msg);

/*
	DrawBox( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE - 23 + 4 , 
	         gui->tehai_left_y - 60,
             gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE + 4 , 
	         gui->tehai_left_y - 60 + 56,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// �A�N�V�����v���[�g(����)_LEFT
	DrawRotaString( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                gui->tehai_left_y - 60 + 4,
	                1.0, 1.0, 0, 0, PI / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, tmp_disp_msg);
*/

	// �A�N�V�����v���[�g_RIGHT
	wsprintf(tmp_disp_msg,"���[�`");
	dparts->DispActplt_right( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                          gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 56, 
	                          tmp_disp_msg);

/*
	DrawBox( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE - 4 , 
	         gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 60 - 56,
             gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE - 4 + 23, 
	         gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 60 + 4,
	         GetColor( 128, 0, 0 ), TRUE ) ;

	// �A�N�V�����v���[�g(����)_RIGHT
	wsprintf(tmp_disp_msg,"���[�`");
	DrawRotaString( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10 + 60, 
	                1.0, 1.0, 0, 0, PI*3.0 / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, tmp_disp_msg);
*/

	// ----------------------------------------
	// �ȏ��̕\��
	// ----------------------------------------

	// �ȏ��UP
	DrawRotaString( gui->tehai_up_x + HAI_XSIZE * TEHAI_MAX, 
	                gui->tehai_up_y + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                1.0, 1.0, 0, 0, PI, GetColor( 255, 255, 255 ), 0, FALSE, "[��2]�Ђ܂���");

	// �ȏ��DONW
	wsprintf(tmp_disp_msg,"[��4]�Ђ܂���");
	dparts->DispString( gui->tehai_x, 
	                    gui->tehai_y - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                    tmp_disp_msg);

	// �ȏ��LEFT
	DrawRotaString( gui->tehai_left_x + HAI_YSIZE + STRING_YSIZE + NAME_TEHAI_RANGE, 
	                gui->tehai_left_y,                                           
	                1.0, 1.0, 0, 0, PI / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, "[��3]�Ђ܂���");

	// �ȏ��RIGHT
	DrawRotaString( gui->tehai_right_x - STRING_YSIZE - NAME_TEHAI_RANGE, 
	                gui->tehai_right_y + HAI_XSIZE * TEHAI_MAX + HAI_XSIZE + 10, 
	                1.0, 1.0, 0, 0, PI*3.0 / 2.0, GetColor( 255, 255, 255 ), 0, FALSE, "[��1]�Ђ܂���");

	// ----------------------------------------
	// ��v�̕\��
	// ----------------------------------------

	// ��v�\��(Right�v���[��)
		dparts->DispLHai( gui->tehai_right_x, (TEHAI_MAX - tmp_tehai_tbl_count_right) * HAI_XSIZE + gui->tehai_right_y               , 31, false, false, 0, 0);         // �E����

	for(int tmp_i = 0; tmp_i < tmp_tehai_tbl_count_right; tmp_i++){
		dparts->DispLHai( gui->tehai_right_x, (TEHAI_MAX - tmp_tehai_tbl_count_right) * HAI_XSIZE + gui->tehai_right_y + HAI_XSIZE+10+tmp_i*24, 31, false, false, 0, 0);       // �E��v
	}

	// ��v�\��(UP�v���[��)
	for(int tmp_i = 0; tmp_i < tmp_tehai_tbl_count_up; tmp_i++){
		dparts->DispHai( gui->tehai_up_x + (TEHAI_MAX - tmp_tehai_tbl_count_up) * HAI_XSIZE + HAI_XSIZE * tmp_i,       gui->tehai_up_y, 32, false, true, 0, 0);         // UP�v���[����v
	}
		dparts->DispHai( gui->tehai_up_x + (TEHAI_MAX - tmp_tehai_tbl_count_up) * HAI_XSIZE - HAI_XSIZE - SPACE_XSIZE, gui->tehai_up_y, 32, false, true, 0, 0);         // UP�v���[������

	// ��v�\��(Left�v���[��)
	for(int tmp_i = 0; tmp_i < tmp_tehai_tbl_count_left; tmp_i++){
		dparts->DispLHai( gui->tehai_left_x, gui->tehai_left_y + tmp_i * LHAI_YSIZE, 33, false, true, 0, 0);                                                            // ����v
	}
		dparts->DispLHai( gui->tehai_left_x, gui->tehai_left_y + tmp_tehai_tbl_count_left * LHAI_YSIZE + 10, 33, false, true, 0, 0);                                    // ������(13*24)

	// ��v�\��(DOWN�v���[��)
	for(int tmp_i = 0; tmp_i < tmp_tehai_tbl_count_down; tmp_i++){
		dparts->DispHai( gui->tehai_x + HAI_XSIZE * tmp_i,                                  gui->tehai_y, 34, false, false, 0, 0);                                      // DOWN�v���[����v
	}
		dparts->DispHai( gui->tehai_x + HAI_XSIZE * tmp_tehai_tbl_count_down + SPACE_XSIZE, gui->tehai_y, 34, false, false, 0, 0);                                      // DOWN�v���[������

	// ----------------------------------------
	// �v�̕\��
	// ----------------------------------------

	// ������\��
	if( gui->disp_square_naki_mentsu == 0 ){

		// �v�\��(UP�v���[��)
		for(int tmp_i = 0; tmp_i < 4 ; tmp_i++){
			dparts->DispHai( gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*0, gui->nakihai_line_up_y,  0, false, true, 0, 0);
			dparts->DispHai( gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*1, gui->nakihai_line_up_y, 32, false, true, 0, 0);
			dparts->DispHai( gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*2, gui->nakihai_line_up_y, 32, false, true, 0, 0);
			dparts->DispHai( gui->nakihai_line_up_x + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*3, gui->nakihai_line_up_y,  0, false, true, 0, 0);
		}

		// �v�\��(DOWN�v���[��)
		for(int tmp_i = 0; tmp_i < 4; tmp_i++){
			dparts->DispActSarashiParts( gui->nakihai_line_down_x - NAKI_MENTSU_RANGE*tmp_i, gui->nakihai_line_down_y, ANKAN, 34, false);
		}

		// �v�\��(RIGHT�v���[��)
		for(int tmp_i = 0; tmp_i < 4; tmp_i++){
			dparts->DispLHai( gui->nakihai_line_right_x, gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*3,  0, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_line_right_x, gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*2, 31, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_line_right_x, gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*1, 31, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_line_right_x, gui->nakihai_line_right_y + NAKI_MENTSU_RANGE*tmp_i - HAI_XSIZE*0,  0, false, false, 0, 0);
		}

		// �v�\��(LEFT�v���[��)
		for(int tmp_i = 0; tmp_i < 4; tmp_i++){
			dparts->DispLHai( gui->nakihai_line_left_x, gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_i + HAI_XSIZE*0,  0, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_line_left_x, gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_i + HAI_XSIZE*1, 33, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_line_left_x, gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_i + HAI_XSIZE*2, 33, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_line_left_x, gui->nakihai_line_left_y - NAKI_MENTSU_RANGE*tmp_i + HAI_XSIZE*3,  0, false, true, 0, 0);
		}

	// �c����\��
	}else{

		// �c��v�\��(LEFT�v���[��)
		for(int tmp_i = 0; tmp_i < 4; tmp_i++){
			dparts->DispLHai( gui->nakihai_left_x + tmp_i*LHAI_XSIZE, gui->nakihai_left_y + LHAI_YSIZE*0,  0, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_left_x + tmp_i*LHAI_XSIZE, gui->nakihai_left_y + LHAI_YSIZE*1, 33, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_left_x + tmp_i*LHAI_XSIZE, gui->nakihai_left_y + LHAI_YSIZE*2, 33, false, true, 0, 0);
			dparts->DispLHai( gui->nakihai_left_x + tmp_i*LHAI_XSIZE, gui->nakihai_left_y + LHAI_YSIZE*3,  0, false, true, 0, 0);
		}

		// �c��v�\��(RIGHT�v���[��)
		for(int tmp_i = 0; tmp_i < 4; tmp_i++){
			dparts->DispLHai( gui->nakihai_right_x + LHAI_XSIZE*(3-tmp_i), gui->nakihai_right_y + LHAI_YSIZE*0,  0, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_right_x + LHAI_XSIZE*(3-tmp_i), gui->nakihai_right_y + LHAI_YSIZE*1, 31, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_right_x + LHAI_XSIZE*(3-tmp_i), gui->nakihai_right_y + LHAI_YSIZE*2, 31, false, false, 0, 0);
			dparts->DispLHai( gui->nakihai_right_x + LHAI_XSIZE*(3-tmp_i), gui->nakihai_right_y + LHAI_YSIZE*3,  0, false, false, 0, 0);
		}

	}

	// ----------------------------------------
	// �̔v�̕\��
	// ----------------------------------------

	// �̔v�\��(RIGHT�v���[��)
	for(int tmp_i = 0; tmp_i < LINE_SUTEHAI_COUNT_MAX; tmp_i++){
		dparts->DispLHai( gui->sutehai_right_x + LHAI_XSIZE*0, gui->sutehai_right_y + tmp_i*LHAI_YSIZE, 31, false, false, 0, 0);      // �E��i��
		dparts->DispLHai( gui->sutehai_right_x + LHAI_XSIZE*1, gui->sutehai_right_y + tmp_i*LHAI_YSIZE, 31, false, false, 0, 0);      // �E��i��
		dparts->DispLHai( gui->sutehai_right_x + LHAI_XSIZE*2, gui->sutehai_right_y + tmp_i*LHAI_YSIZE, 31, false, false, 0, 0);      // �E�O�i��
		dparts->DispLHai( gui->sutehai_right_x + LHAI_XSIZE*3, gui->sutehai_right_y + tmp_i*LHAI_YSIZE, 31, false, false, 0, 0);      // �E�l�i��
	}

	// �̔v�\��(UP�v���[��)
	for(int tmp_i = 0; tmp_i < LINE_SUTEHAI_COUNT_MAX; tmp_i++){
		dparts->DispHai( gui->sutehai_up_x + HAI_XSIZE*tmp_i, gui->sutehai_up_y              ,32, false, true, 0, 0);             // ��l�i��
		dparts->DispHai( gui->sutehai_up_x + HAI_XSIZE*tmp_i, gui->sutehai_up_y + HAI_YSIZE*1,32, false, true, 0, 0);             // ��O�i��
		dparts->DispHai( gui->sutehai_up_x + HAI_XSIZE*tmp_i, gui->sutehai_up_y + HAI_YSIZE*2,32, false, true, 0, 0);             // ���i��
		dparts->DispHai( gui->sutehai_up_x + HAI_XSIZE*tmp_i, gui->sutehai_up_y + HAI_YSIZE*3,32, false, true, 0, 0);             // ���i��
	}

	// �̔v�\��(LEFT�v���[��)
	for(int tmp_i = 0; tmp_i < LINE_SUTEHAI_COUNT_MAX; tmp_i++){
		dparts->DispLHai( gui->sutehai_left_x - LHAI_XSIZE*0, gui->sutehai_left_y + tmp_i*LHAI_YSIZE, 33, false, true, 0, 0);       // ���l�i��
		dparts->DispLHai( gui->sutehai_left_x - LHAI_XSIZE*1, gui->sutehai_left_y + tmp_i*LHAI_YSIZE, 33, false, true, 0, 0);       // ���O�i��
		dparts->DispLHai( gui->sutehai_left_x - LHAI_XSIZE*2, gui->sutehai_left_y + tmp_i*LHAI_YSIZE, 33, false, true, 0, 0);       // ����i��
		dparts->DispLHai( gui->sutehai_left_x - LHAI_XSIZE*3, gui->sutehai_left_y + tmp_i*LHAI_YSIZE, 33, false, true, 0, 0);       // ����i��
	}

	// �̔v�\��(DOWN�v���[��)
	for(int tmp_i = 0; tmp_i < LINE_SUTEHAI_COUNT_MAX; tmp_i++){
		dparts->DispHai( gui->sutehai_down_x+HAI_XSIZE*tmp_i, gui->sutehai_down_y,             34, false, false, 0, 0);       // ����i��
		dparts->DispHai( gui->sutehai_down_x+HAI_XSIZE*tmp_i, gui->sutehai_down_y+HAI_YSIZE*1, 34, false, false, 0, 0);       // ����i��
		dparts->DispHai( gui->sutehai_down_x+HAI_XSIZE*tmp_i, gui->sutehai_down_y+HAI_YSIZE*2, 34, false, false, 0, 0);       // ���O�i��
		dparts->DispHai( gui->sutehai_down_x+HAI_XSIZE*tmp_i, gui->sutehai_down_y+HAI_YSIZE*3, 34, false, false, 0, 0);       // ���l�i��
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ݒ��ʁF���C�����
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplaySetting(MJSGui *gui, float mFps, int total_frame_count, int ver1, int ver2, int ver3, int ver4, int ver5){

	// ----------------------------------------
	// �����`�揈��
	// ----------------------------------------
	dparts->DispPartsClearDraw();

	// ----------------------------------------
	// �p�[�c�\��
	// ----------------------------------------
	dparts->DispBunner(ver1, ver2, ver3, ver4, ver5);                                     // �o�i�[
	dparts->DispMousepoint(5, 750, gui->msx, gui->msy, gui->Button[0], gui->Button[1]);   // �}�E�X�ʒu
	dparts->DispFps(670, 750, mFps, total_frame_count, 0);                                // FPS

	// �ݒ���\��
	DrawFormatString(4, 4, GetColor(255,255,255), "�ݒ���");

	// ----------------------------------------
	// �ݒ��ʕ\��
	// ----------------------------------------
	if(gui->set_mode == SETTING_FILENAME_MJAI_MODE){

		// �t�@�C�����擾
		DisplayFileNameDiag(gui,GUI_LOG_MJAILOG);

		// ���[�h�ύX
		gui->set_mode = SETTING_INFO_MODE;

	}else if(gui->set_mode == SETTING_FILENAME_MJSCORE_MODE){

		// �t�@�C�����擾
		DisplayFileNameDiag(gui,GUI_LOG_MJSCORE);

		// ���[�h�ύX
		gui->set_mode = SETTING_INFO_MODE;

	}else{

		// ��ʕ\��
		DisplaySettingInfo(gui);

	}

	// ----------------------------------------
	// ����ʂ�\��ʂɔ��f
	// ----------------------------------------
	dparts->DispPartsFlip();

}

/* ---------------------------------------------------------------------------------------------- */
// �ݒ��ʁF�t�@�C���I���_�C�A�O
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplaySettingInfo(MJSGui *gui){

	// �����ݒ�
	char cdir[192];
	GetCurrentDirectory(192,cdir);

	// �ݒ�{�^���\��
	for(int tmp_i = 0; tmp_i < 5; tmp_i++){
		dparts->DispButton(SETTING_X_START, SETTING_Y_START+tmp_i*SETTING_Y_RANGE, PARTS_BUT_BLUE);
	}

	// ���O���\��(���͗p)
	DrawFormatString(SETTING_X_START+40, SETTING_Y_START+0*SETTING_Y_RANGE+8, GetColor(255,255,255), "mjai      PATH:%s", gui->log_name_mjai);
	DrawFormatString(SETTING_X_START+40, SETTING_Y_START+1*SETTING_Y_RANGE+8, GetColor(255,255,255), "mjsocre   PATH:%s", gui->log_name_mjsocre);

	// ���O���\��(�o�͗p)
	DrawFormatString(SETTING_X_START+40, SETTING_Y_START+2*SETTING_Y_RANGE+8, GetColor(255,255,255), "tklog     PATH:%s", gui->tklog_name);
	DrawFormatString(SETTING_X_START+40, SETTING_Y_START+3*SETTING_Y_RANGE+8, GetColor(255,255,255), "clientlog PATH:%s", gui->clientlog_name);

	// (�f�o�O�p)�J�����g�f�B���N�g�����\��
	DrawFormatString(SETTING_X_START+40, SETTING_Y_START+4*SETTING_Y_RANGE+8, GetColor(255,255,255), "cdir      PATH:%s", cdir);

	// �I���{�^���\��
	dparts->DispButton(SETTING_X_START,    SETTING_ENDBUT_Y_START  , PARTS_BUT_RED);
	DrawFormatString(  SETTING_X_START+40, SETTING_ENDBUT_Y_START+8, GetColor(255,255,255), "�ݒ�I��");

}

/* ---------------------------------------------------------------------------------------------- */
// �ݒ��ʁF�t�@�C���I���_�C�A�O
/* ---------------------------------------------------------------------------------------------- */
void MJSDisplay::DisplayFileNameDiag(MJSGui *gui, LBGuiLogType log_type){

	// �ϐ���`
	OPENFILENAME ofn ;
	char tmp_log_name[FULLPATH_LOGNAME_SIZE];               // �t�@�C�����̈ꎞ�u��

	// ���O��`
	tmp_log_name[0] = '\0' ;
	memset( &ofn, 0, sizeof( OPENFILENAME ) ) ;
	ofn.lStructSize  = sizeof( OPENFILENAME ) ;
	ofn.hwndOwner    = GetMainWindowHandle()  ;             // �e�E�C���h�E�� GetMainWindowHandle �Ŏ擾�ł���E�C���h�E�n���h���ɂ���
	ofn.nFilterIndex = 1 ;
	ofn.nMaxFile     = 256 ;
	ofn.lpstrTitle   = "�v�����O�̑I��" ;
	ofn.Flags        = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ;
	ofn.lpstrFile    = tmp_log_name ;                       // �t�@�C��������

	// ���O��ʐݒ�
	      if(log_type == GUI_LOG_MJAILOG){
		ofn.lpstrFilter  = "mjai(*.json)\0*.json"  ;        // �g���q�w��
		ofn.lpstrDefExt  = "json";
	}else if(log_type == GUI_LOG_MJSCORE){
		ofn.lpstrFilter  = "mjscore(*.txt)\0*.txt"  ;       // �g���q�w��
		ofn.lpstrDefExt  = "txt";
	}

	// �t�@�C�����擾
	GetOpenFileName( &ofn ) ;

	// �t�@�C������`
	if (tmp_log_name[0] != '\0'){

		// ���O��ʂ��Ƃ̃t�@�C������`
		      if(log_type == GUI_LOG_MJAILOG){
			wsprintf(gui->log_name_mjai, tmp_log_name);
		}else if(log_type == GUI_LOG_MJSCORE){
			wsprintf(gui->log_name_mjsocre, tmp_log_name);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
