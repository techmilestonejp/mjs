/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.1.232(�֐���mentsu,taatsu�̖��̋��ʉ�)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F client.cpp
 * �N���X��       �F MJSMjaiClient
 * �����T�v       �F Mjai�N���C�A���g�����N���X
 * Ver0.1.2�쐬�� �F 2023/11/19 21:38:17
 * �ŏI�X�V��     �F 2025/01/04 11:21:26
 * 
 * Copyright (c) 2010-2025 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "client.h"

/* ---------------------------------------------------------------------------------------------- */
// �O����
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ClientInit(MJSTkinfo *tk, MJSGui *gui, MJSReadMjai *tmp_mjai){

	// ----------------------------------------
	// �N���X��`
	// ----------------------------------------
	mjai = new MJSReadMjai;             // MJAI�֘A���b�Z�[�W�����N���X
	clientlog = new MJSCorelog;         // �N���C�A���g�N���X�����̃f�o�O���O

	// ----------------------------------------
	// ���b�Z�[�W�����N���X�̏�����
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){

		// ���O�t�@�C�����ݒ�
		// wsprintf(clientlog_name, "mjai_client.log" );
		// clientlog->CorelogInit(clientlog_name);
		clientlog->CorelogInit(gui->clientlog_name);

	}

	// ----------------------------------------
	// �f�o�O���O�w�b�_�[�o��
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){

		// ���O�t�@�C�����ݒ�
		wsprintf(clientlog_buf, "�w�b�_�[\n----\n" );

		// ���O�o��
		clientlog->CorelogPrint(clientlog_buf);

	}

	// �����ݒ�
	SetNowTime(tk);

}

/* ---------------------------------------------------------------------------------------------- */
// �I������
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ClientPost(MJSGui *gui){

	// ----------------------------------------
	// �N���X�̏I��
	// ----------------------------------------

	// ���O�㏈��
	if( gui->clientlog_output_flg == true){
		clientlog->CorelogPost();
	}

	// ----------------------------------------
	// �N���X�폜
	// ----------------------------------------
	delete mjai;                        // MJAI�N���X
	delete clientlog;                   // �N���C�A���g�f�o�O���O

}

/* ---------------------------------------------------------------------------------------------- */
// ���b�Z�[�W���M����
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ClientSendMes(MJSGui *gui){

	// ���b�Z�[�W���M
	sock.SendMes(gui);

	// ���O�o��
	if( gui->clientlog_output_flg == true){
		wsprintf(clientlog_buf, "SND:");
		clientlog->CorelogPrint(clientlog_buf);
		clientlog->CorelogPrint(gui->snd_mes);
		wsprintf(clientlog_buf, "----\n");
		clientlog->CorelogPrint(clientlog_buf);
	}

	// ���M�o�b�t�@�̃N���A
	memset(gui->snd_mes, 0, sizeof(gui->snd_mes));

}

/* ---------------------------------------------------------------------------------------------- */
// ���ݎ����̎擾
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetNowTime(MJSTkinfo *tk){

	// �V�X�e���֐���` 
    time_t jikan = time(NULL);
    struct tm imanojikan;
	errno_t error;

	// ���ԕϐ��̒�`
	int year, mon, day;
	int hour, min, sec;

	// ���݂̓������擾 
	error = localtime_s(&imanojikan, &jikan);

	// ���ԕϐ��̑��
	year = imanojikan.tm_year + 1900;
	mon  = imanojikan.tm_mon  + 1;
	day  = imanojikan.tm_mday ;

	hour = imanojikan.tm_hour;
	min  = imanojikan.tm_min;
	sec  = imanojikan.tm_sec;

	wsprintf(tk->startdate, "%04d/%02d/%02d", year, mon, day);     // ��J�n��
	wsprintf(tk->starttime, "%02d:%02d:%02d", hour, min, sec);     // ��J�n����

}

/* ---------------------------------------------------------------------------------------------- */
// ���C������
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::CheckTakuStatus(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, bool tmp_push_flg){

	// HUM��v�m�F�t���O
	tk->com_no_chk_tehai_flg = true;

	// �ő�Ԕv��
	tk->aka_max[0] = 1;
	tk->aka_max[1] = 1;
	tk->aka_max[2] = 1;

	//-----------------------------------------------------------
	// �ڑ��O���
	//-----------------------------------------------------------
	if( gui->cli_mode == GUI_MJAI_NOTCONNECT){

		// ���b�Z�[�W�\��
		wsprintf(gui->stat_mes, "�ڑ����ă��[�U�f�[�^�𑗐M���܂����H");

		// ���[�h�ύX
		gui->cli_mode = GUI_MJAI_CONNECT_ACTION;

	//-----------------------------------------------------------
	// �ڑ�����
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_CONNECT_ACTION){

		// �N���b�N����Ă����
		if( tmp_push_flg == true){

			// �ڑ�����
			if ( sock.SocketConect() == 0 ){

				// ���b�Z�[�W�\��
				wsprintf(gui->stat_mes, "�ڑ��ɐ������܂���");

				// send���b�Z�[�W�ݒ�
				wsprintf(gui->snd_mes, res_join);

				// ���b�Z�[�W���M(join���b�Z�[�W)
				ClientSendMes(gui);

				// ���[�h�ύX
				gui->cli_mode = GUI_MJAI_WAIT_HELO_RESMES;

			}else{

				// ��M���b�Z�[�W�̐ݒ�
				wsprintf(gui->stat_mes, "�ڑ��G���[");

				// ���[�h�ύX
				gui->cli_mode = GUI_MJAI_ERR_CONNECT;

			}
		}

	//-----------------------------------------------------------
	// �ڑ��G���[��
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_ERR_CONNECT){

		// �N���b�N����Ă����
		if( tmp_push_flg == true){

			// ���[�h�ύX�F�N���C�A���g���[�h�I��
			gui->cli_mode = GUI_MJAI_DISCONNECT;

		}

	//-----------------------------------------------------------
	// HELLO���b�Z�[�W��M�҂�
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_HELO_RESMES){

		// ���b�Z�[�W��M
		sock.ResponseMes(gui);

		// �f�[�^��M�������
		if (sock.data_size > 0){

			// ���b�Z�[�W�\��
			wsprintf(gui->stat_mes, "HELLO���b�Z�[�W����M���܂���");

			// ���O�o��(HELLO���b�Z�[�W)
			if( gui->clientlog_output_flg == true){
				clientlog->CorelogPrint(gui->res_mes);
				clientlog->CorelogPrint(clientlog_buf);
				// ���O�o��(��؂��)
				wsprintf(clientlog_buf, "----\n");
				clientlog->CorelogPrint(clientlog_buf);
			}

			// ���[�h�ύX
			gui->cli_mode = GUI_MJAI_WAIT_TAKU_START_RESMES;

		}else{

			// ���b�Z�[�W�\��
			wsprintf(gui->stat_mes, "HELLO���b�Z�[�W�̎�M�҂��ł�");

		}

	//-----------------------------------------------------------
	// taku_start���b�Z�[�W��M�҂�
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_START_RESMES){

		// ���b�Z�[�W��M
		sock.ResponseMes(gui);

		// �f�[�^��M�������
		if (sock.data_size > 0){

			// ���b�Z�[�W�\��
			wsprintf(gui->stat_mes, "�Q�[���J�n���b�Z�[�W����M���܂���");

			// ���O�o��(gui->res_mes�o��)
			if( gui->clientlog_output_flg == true){
				clientlog->CorelogPrint(gui->res_mes);
				wsprintf(clientlog_buf, "----\n");
				clientlog->CorelogPrint(clientlog_buf);
			}

			// ���C�����
			wsprintf(mjai->line_buf, gui->res_mes);    // ���C���o�b�t�@�ւ̃R�s�[
			mjai->Read_logline(gui);                   // ���C�����

			// ���b�Z�[�W�m�F(���C������)
			ChkResMesMain(tk, ply, gui);

			// ���[�h�ύX
			gui->cli_mode = GUI_MJAI_BAGIME;

		}else{

			// ���b�Z�[�W�\��
			wsprintf(gui->stat_mes, "�Q�[���J�n���b�Z�[�W�̎�M�҂��ł�");

		}

	//-----------------------------------------------------------
	// �ꌈ�ߕ\��
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_BAGIME){

		// �N���b�N����Ă����
		if( tmp_push_flg == true){

			// ��M�o�b�t�@�̃N���A
			sock.data_size = 0;
			memset(gui->res_mes, 0, sizeof(gui->res_mes));

			// None���N�G�X�g�̑��M����
			ActSndNoneMes(gui);

			// ���b�Z�[�W���M
			ClientSendMes(gui);

			// ���[�h�ύX
			gui->cli_mode = GUI_MJAI_WAIT_KYOKU_START_RESMES;

		}

	//-----------------------------------------------------------
	// �ǊJ�n���b�Z�[�W�҂�
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_KYOKU_START_RESMES){

		// ���b�Z�[�W�\��
		wsprintf(gui->stat_mes, "�Ǐ��̃��b�Z�[�W�̎�M�҂��ł�");

		// ���b�Z�[�W��M
		sock.ResponseMes(gui);

		// �f�[�^��M�������
		if (sock.data_size > 0){

			// ���O�o��
			if( gui->clientlog_output_flg == true){
				clientlog->CorelogPrint(gui->res_mes);
				wsprintf(clientlog_buf, "----\n");
				clientlog->CorelogPrint(clientlog_buf);
			}

			// ���C�����
			wsprintf(mjai->line_buf, gui->res_mes);  // ���C���ݒ�
			mjai->Read_logline(gui);                  // ���C�����

			// ���b�Z�[�W�m�F(���C������)
			ChkResMesMain(tk, ply, gui);

			// ���[�h�ύX
			gui->cli_mode = GUI_MJAI_HAIPAI;

		}

	//-----------------------------------------------------------
	// �z�v���
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_HAIPAI){

		// �N���b�N����Ă����
		if( tmp_push_flg == true){

			// �o�b�t�@�N���A
			sock.data_size = 0;
			memset(gui->res_mes, 0, sizeof(gui->res_mes));

			// None���N�G�X�g�̑��M����
			ActSndNoneMes(gui);

			// ���b�Z�[�W���M
			ClientSendMes(gui);

			// ���[�h�ύX
			gui->cli_mode = GUI_MJAI_WAIT_TAKU_RESMES;

		}

	//-----------------------------------------------------------
	// �상�C���̎�M���b�Z�[�W�҂�
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_RESMES){

		// �o�b�t�@�N���A
		sock.data_size = 0;
		memset(gui->res_mes, 0, sizeof(gui->res_mes));

		// ���b�Z�[�W��M
		sock.ResponseMes(gui);

		// �f�[�^��M�������
		if (sock.data_size > 0){

			// ���O�o��
			if( gui->clientlog_output_flg == true){
				wsprintf(clientlog_buf, "RES:");
				clientlog->CorelogPrint(clientlog_buf);
				clientlog->CorelogPrint(gui->res_mes);
				wsprintf(clientlog_buf, "----\n");
				clientlog->CorelogPrint(clientlog_buf);
			}

			// ���C�����
			wsprintf(mjai->line_buf, gui->res_mes);  // ���C���̒l�ݒ�
			mjai->Read_logline(gui);                  // ���C�����(wk�z��ɒl����)

			// ���O�o��(wk�\����)
			if( gui->clientlog_output_flg == true){
				for(int tmp_i = 0; tmp_i < gui->wk_str_count; tmp_i++){
					wsprintf(clientlog_buf, "%d:%s\n", tmp_i, gui->wk_str[tmp_i]);
					clientlog->CorelogPrint(clientlog_buf);
				}
				wsprintf(clientlog_buf, "----\n");
				clientlog->CorelogPrint(clientlog_buf);
			}

			// ���b�Z�[�W�m�F(���C������)
			ChkResMesMain(tk, ply, gui);

			// ���[�h�ύX
			gui->cli_mode = GUI_MJAI_WAIT_TAKU_PLYACT;

		}

	//-----------------------------------------------------------
	// �상�C���F�����v���[���[�̃A�N�V��������҂�
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_TAKU_PLYACT){

		// �N���b�N����Ă����
		if( tmp_push_flg == true){

			// ----------------------------------------
			// ��X�e�[�^�X���Ƃɏ���(���̂̏ꍇ)
			// ----------------------------------------
			if( tk->stat == PLYACTTSUMO ){

				// ���̎��̃��b�Z�[�W���M
				SetActTsumo(tk, ply, gui);

				// SND�҂��J�E���g��������
				gui->send_wait_frame_count = 0;

				// ���[�h�ύX
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			// ----------------------------------------
			// ��X�e�[�^�X���Ƃɏ���(���[�`�̏ꍇ)
			// ----------------------------------------
			}else if(tk->stat == PLYACTRIICH){

				// ���[�`���̃��b�Z�[�W���M
				SetActRiichi(tk, ply, gui);

				// SND�҂��J�E���g��������
				gui->send_wait_frame_count = 0;

				// ���[�h�ύX
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			// ----------------------------------------
			// ��X�e�[�^�X���Ƃɏ���(�̔v�̏ꍇ���̔v��̖��m�F)
			// ---------------------------------------
			}else if( tk->stat == PLYACTSUTE       || 
			          tk->stat == PLYACTTSUMOGIRI  ||
			          tk->stat == PLYACTNAKISUTE   ){

				// ������
				SetActNaki(tk, ply, gui);

				// SND�҂��J�E���g��������
				gui->send_wait_frame_count = 0;

				// ���[�h�ύX
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			// ----------------------------------------
			// ��X�e�[�^�X���Ƃɏ���(�|���`�[�̏ꍇ���̔v��̖��m�F)
			// ----------------------------------------
			}else if( tk->stat == PLYACTPON  || 
			          tk->stat == PLYACTCHI  ){ 

				// ���̔v���̃��b�Z�[�W���M
				SetActNakiSute(tk, ply, gui);

				// SND�҂��J�E���g��������
				gui->send_wait_frame_count = 0;

				// ���[�h�ύX
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			// ----------------------------------------
			// ��X�e�[�^�X���Ƃɏ���(�J���̏ꍇ���������Ȃ�)
			// ----------------------------------------
			}else if( tk->stat == PLYACTANKAN  ||
			          tk->stat == PLYACTKAKAN  || 
			          tk->stat == PLYACTMINKAN ){ 

				// �J�����̃��b�Z�[�W���M
				SetActkan(tk, ply, gui);

				// SND�҂��J�E���g��������
				gui->send_wait_frame_count = 0;

				// ���[�h�ύX
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			// ----------------------------------------
			// �ǏI��
			// ----------------------------------------
			}else if(tk->stat == KYOKURESULT){

				// ���[�h�ύX
				gui->cli_mode = GUI_MJAI_KYOKUEND;

			// ----------------------------------------
			// �G���[���
			// ----------------------------------------
			}else if(tk->stat == TAKUERR){

				// ���[�h�ύX
				gui->cli_mode = GUI_MJAI_ERR_RES_MES;

			// ----------------------------------------
			// ����ȊO�̏ꍇ
			// ----------------------------------------
			}else{

				// None���N�G�X�g�̑��M����
				ActSndNoneMes(gui);

				// SND�҂��J�E���g��������
				gui->send_wait_frame_count = 0;

				// ���[�h�ύX
				gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

			}

		}

	//-----------------------------------------------------------
	// �상�C���F�ǏI�����[�h
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_KYOKUEND){

		// �N���b�N����Ă����
		if( tmp_push_flg == true){

			// None���N�G�X�g�̑��M����
			ActSndNoneMes(gui);

			// ���[�h�ύX
			gui->cli_mode = GUI_MJAI_WAIT_SED_MES;

		}

	//-----------------------------------------------------------
	// �상�C���F���b�Z�[�W���M�̃E�G�C�g����
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_WAIT_SED_MES){

		// �J�E���g�l�𒴉߂���܂ŃE�F�C�g
		if( gui->send_wait_frame_count > AUTO_FRAME_COUNT_CLIENT_SND){

			// ���b�Z�[�W���M
			ClientSendMes(gui);

			// �E�F�C�g�������I�����āA���[�h�ύX
			if(tk->stat == TAKURESULT){
				// ��I�����[�h
				gui->cli_mode = GUI_MJAI_TAKURESULT;
			}else{
				// ���b�Z�[�W��M
				gui->cli_mode = GUI_MJAI_WAIT_TAKU_RESMES;
			}

		}else{
			// SND�҂��J�E���g��+1
			gui->send_wait_frame_count++;
		}

	//-----------------------------------------------------------
	// �상�C���F��I�����[�h
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_TAKURESULT){

		// �N���b�N����Ă����
		if( tmp_push_flg == true){

			// ���[�h�ύX�F�N���C�A���g���[�h�I��
			gui->cli_mode = GUI_MJAI_DISCONNECT;

		}

	//-----------------------------------------------------------
	// �상�C���F�G���[����
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_ERR_RES_MES){

		// �N���b�N����Ă����
		if( tmp_push_flg == true){

			// ���[�h�ύX�F�N���C�A���g���[�h�I��
			gui->cli_mode = GUI_MJAI_DISCONNECT;

		}

	//-----------------------------------------------------------
	// �ؒf�������N���C�A���g���[�h�I��
	//-----------------------------------------------------------
	}else if( gui->cli_mode == GUI_MJAI_DISCONNECT){

		// �N���b�N����Ă����
	//	if( tmp_push_flg == true){

			// �ؒf
			sock.SocketDisconect();

			// ���[�h�ύX
			gui->cli_mode = GUI_MJAI_END_MODE;

	//	}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���̎��̃A�N�V�����ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActTsumo(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// �ϐ�
	int tmp_aka_count = 0;

	// �v���[���������Ȃ�
	if( tk->ply_turn == HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// ply�N���X�̔v�ݒ�
		// ----------------------------------------

		// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
		if ( tk->ply_hum_mode == 0 ){

			// �A�N�V������`
			tk->ply_act = ply[HUM_PLY_SEKI_NUM].ply_act;

		}

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V������`(�̔v��)
		// -----------------------------------------------------------
		if(tk->ply_act == ACTSUTE){

			// �̔v�A�N�V����
			SetActSute(tk, ply, gui);

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V������`(���[�`��)
		// -----------------------------------------------------------
		}else if(tk->ply_act == ACTRIICH){

			// ----------------------------------------
			// ��X�e�[�^�X�ݒ�
			// ----------------------------------------
			tk->stat = PLYACTRIICH;

			// ----------------------------------------
			// ���b�Z�[�W��`(���[�`�錾)
			// ----------------------------------------
			ActSndRiichiMes(gui, tk->ply_mjai_hum_id);

			// ----------------------------------------
			// �A�N�V�����ݒ� - ���[�`�錾
			// ----------------------------------------
			tk->SetActInfo(tk->kyoku_index,
				PLYACTRIICH,
				tk->ply_turn,
				4,
				0,
				false
			);

			// ----------------------------------------
			// tk�N���X�̃A�N�V�������̍ŐV��
			// ----------------------------------------
			tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

			// ----------------------------------------
			// �A�N�V�����ݒ�/���O�o��
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

			// ----------------------------------------
			// ��v�e�[�u���̍X�V(��v�̂Ă̖�����)
			// ----------------------------------------

			// ��v�̃V�����e��������
			for( int tmp_i = 0; tmp_i < TEHAI_MAX; tmp_i++ ) {
				tk->ply_act_tehai_shanten_tbl[HUM_PLY_SEKI_NUM][tmp_i] = 9;
			}

			// ���̔v�̃V�����e��������
			tk->ply_act_tsumo_shanten[HUM_PLY_SEKI_NUM] = 9;

		// -----------------------------------------------------------
		// ���v���[���[�̃A�N�V����(�ÞȐ錾)
		// -----------------------------------------------------------
		}else if(tk->ply_act == ACTANKAN){

			// -----------------------------------------------------------
			// ���v�擾
			// -----------------------------------------------------------
			// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
			if ( tk->ply_hum_mode == 0 ){

				// �ÞȔv��`
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM] = ply[HUM_PLY_SEKI_NUM].ply_naki_idx;

			}

			// -----------------------------------------------------------
			// ��X�e�[�^�X�ݒ�
			// -----------------------------------------------------------
			tk->stat = PLYACTANKAN;

			// -----------------------------------------------------------
			// ���b�Z�[�W��`(�Þ�)
			// -----------------------------------------------------------

			// �Ԗ����m�F
			if (tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == MAN5NUM || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == PIN5NUM || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == SOU5NUM ){

				// ���b�Z�[�W��`
				ActSndAnkanMes(gui, tk->ply_mjai_hum_id,                                            // �v���[���[ID
				                    tk->ply_naki_idx[HUM_PLY_SEKI_NUM],                             // ���̔v
				                    tk->aka_max[(tk->ply_naki_idx[HUM_PLY_SEKI_NUM]-5)/10]);        // �Ԕv���v����
			}else{

				// ���b�Z�[�W��`
				ActSndAnkanMes(gui, tk->ply_mjai_hum_id,                        // �v���[���[ID
				                    tk->ply_naki_idx[HUM_PLY_SEKI_NUM],         // ���̔v
				                    0);                                         // �Ԕv���v����
			}

			// -----------------------------------------------------------
			// �A�N�V�����ݒ� - �Þ�
			// -----------------------------------------------------------
			tk->SetActInfo(tk->kyoku_index,
				PLYACTANKAN,
				tk->ply_turn,
				4,
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM],  
				false                                // �ÞȎ��̐Ԕv�L���͏��false
			);

			// ----------------------------------------
			// �A�N�V�����ݒ�/���O�o��
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

			// ----------------------------------------
			// tk�N���X�̃A�N�V�������̍ŐV��
			// ----------------------------------------
			tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

			// ----------------------------------------
			// �N�����ݒ� - �Þ�
			// ----------------------------------------

			// �Ԗ����m�F
			if (tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == MAN5NUM || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == PIN5NUM || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == SOU5NUM ){

				// �v�ݒ�
				tk->SetNakiInfo(tk->kyoku_index, 
					ANKAN, 
					tk->ply_turn,                                                                  // ���v���[���[
					tk->kyoku[tk->kyoku_index].act_count,                                          // ACTID
					tk->ply_naki_idx[HUM_PLY_SEKI_NUM],    // ���v��`
					tk->ply_naki_idx[HUM_PLY_SEKI_NUM],    // ��INDEX�v��`
					tk->aka_max[(tk->ply_naki_idx[HUM_PLY_SEKI_NUM]-5)/10]);                       // ���ʎq�̍��v�Ԗ���

			}else{

				// �v�ݒ�(�ʏ�v)
				tk->SetNakiInfo(tk->kyoku_index, 
					ANKAN, 
					tk->ply_turn,                                                                  // ���v���[���[
					tk->kyoku[tk->kyoku_index].act_count,                                          // ACTID
					tk->ply_naki_idx[HUM_PLY_SEKI_NUM],    // ���v��`
					tk->ply_naki_idx[HUM_PLY_SEKI_NUM],    // ��INDEX�v��`
					0);                                                                            // ���ʎq�̍��v�Ԗ���

			}

			// ----------------------------------------
			// ply�N���X�̔v��̏���
			// ----------------------------------------

			// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
			if ( tk->ply_hum_mode == 0 ){

				// �v���[���[�A�N�V���� - �Þ�
				ply[HUM_PLY_SEKI_NUM].PlyActAnkan(ply[HUM_PLY_SEKI_NUM].ply_naki_idx);

			}

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V����(���Ȑ錾)
		// -----------------------------------------------------------
		}else if(tk->ply_act == ACTKAKAN){

			// -----------------------------------------------------------
			// ���v�擾
			// -----------------------------------------------------------
			// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
			if ( tk->ply_hum_mode == 0 ){

				// �ÞȔv��`
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = ply[HUM_PLY_SEKI_NUM].ply_naki_idx;
				tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = ply[HUM_PLY_SEKI_NUM].ply_naki_aka_count;

			}

			// -----------------------------------------------------------
			// ��X�e�[�^�X�ݒ�
			// -----------------------------------------------------------
			tk->stat = PLYACTKAKAN;

			// -----------------------------------------------------------
			// ���b�Z�[�W��`(����)
			// -----------------------------------------------------------

			// ���Ȃ���Ώۂ̃|���ʎq�̐Ԗ����m�F
			for( int tmp_i = 0; tmp_i < tk->kyoku[tk->kyoku_index].naki_count[HUM_PLY_SEKI_NUM]; tmp_i++ ) { 

				// �v�ԍ��̊m�F
				if( ( tk->kyoku[tk->kyoku_index].naki_stat[HUM_PLY_SEKI_NUM][tmp_i] == MINKO) &&   // �|���ł��邱��
				    ( tk->kyoku[tk->kyoku_index].naki_hai[HUM_PLY_SEKI_NUM][tmp_i]  == tk->ply_naki_idx[HUM_PLY_SEKI_NUM]) ){  // �v�ԍ�����v���Ă��邱��

					// �Ԕv�����̐ݒ�
					tmp_aka_count = tk->kyoku[tk->kyoku_index].naki_aka[HUM_PLY_SEKI_NUM][tmp_i];

				}

			}

			// �Ԗ����m�F
			if (tk->ply_naki_idx[HUM_PLY_SEKI_NUM] ==  5 || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 ){

				// ���b�Z�[�W��`
				ActSndkakanMes(gui, tk->ply_mjai_hum_id,                        // �v���[���[ID
				                    tk->ply_naki_idx[HUM_PLY_SEKI_NUM],         // ���Ȕv
				                    tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM],   // ���Ȕv�̐Ԕv����
				                    tmp_aka_count);                             // �|���̐Ԕv����
			}else{

				// ���b�Z�[�W��`
				ActSndkakanMes(gui, tk->ply_mjai_hum_id,                        // �v���[���[ID
				                    tk->ply_naki_idx[HUM_PLY_SEKI_NUM],         // ���Ȕv
				                    tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM],   // ���Ȕv�̐Ԕv����
				                    0);                                         // �|���̐Ԕv����
			}

			// -----------------------------------------------------------
			// �A�N�V�����ݒ� - ����
			// -----------------------------------------------------------
			tk->SetActInfo(tk->kyoku_index,
				PLYACTKAKAN,
				tk->ply_turn,
				4,
				tk->ply_naki_idx[HUM_PLY_SEKI_NUM],
				false                                // ���Ȕv�̐Ԕv���
			);

			// ----------------------------------------
			// �A�N�V�����ݒ�/���O�o��
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

			// ----------------------------------------
			// �N�����ݒ� - ����
			// ----------------------------------------

			// �Ԗ����m�F
			if (tk->ply_naki_idx[HUM_PLY_SEKI_NUM] ==  5 || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 15 || 
			    tk->ply_naki_idx[HUM_PLY_SEKI_NUM] == 25 ){

				// �v�ݒ�(�Ԕv)
				tk->SetNakiInfo(tk->kyoku_index, 
					KAKAN, 
					tk->ply_turn,                                                                  // ���v���[���[
					tk->kyoku[tk->kyoku_index].act_count,                                          // ACTID
					tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],    // ���v��`
					tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],    // ��INDEX�v��`
					tmp_aka_count);                                                                // ���ʎq�̍��v�Ԗ���

			}else{

				// �v�ݒ�(�ʏ�v)
				tk->SetNakiInfo(tk->kyoku_index, 
					KAKAN, 
					tk->ply_turn,                                                                  // ���v���[���[
					tk->kyoku[tk->kyoku_index].act_count,                                          // ACTID
					tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],    // ���v��`
					tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],    // ��INDEX�v��`
					0);                                                                            // ���ʎq�̍��v�Ԗ���

			}

			// ----------------------------------------
			// ply�N���X�̔v��̏���
			// ----------------------------------------

			// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
			if ( tk->ply_hum_mode == 0 ){

				// �v���[���[�A�N�V���� - ����
				ply[HUM_PLY_SEKI_NUM].PlyActKakan(ply[HUM_PLY_SEKI_NUM].ply_naki_idx, ply[HUM_PLY_SEKI_NUM].ply_naki_aka_count);

			}

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V����(���̘a��)
		// -----------------------------------------------------------
		}else if(tk->ply_act == ACTTSUMOAGARI){

			// -----------------------------------------------------------
			// ��X�e�[�^�X�ݒ�
			// -----------------------------------------------------------
			tk->stat = PLYTSUMOAGARI;

			// -----------------------------------------------------------
			// ���b�Z�[�W��`(���̘a��)
			// -----------------------------------------------------------
			ActSndHoraMes(gui, tk->ply_mjai_hum_id,                        // �a���v���[���[
			                   tk->ply_mjai_hum_id,                        // ���A�N�V�����v���[���[(���v���[���Ɠ���)
			                   tk->ply_act_tsumo[HUM_PLY_SEKI_NUM],        // ���̔v
			                   tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]);   // ���̐�

			// -----------------------------------------------------------
			// �A�N�V�����ݒ� - ���̘a��
			// -----------------------------------------------------------
			tk->SetActInfo(tk->kyoku_index,
				PLYTSUMOAGARI,
				tk->ply_turn,
				4,
				tk->ply_act_tsumo[HUM_PLY_SEKI_NUM],
				tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]
			);

			// ----------------------------------------
			// tk�N���X�̃A�N�V�������̍ŐV��
			// ----------------------------------------
			tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

			// ----------------------------------------
			// �A�N�V�����ݒ�/���O�o��
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V����(���̐؂�)
		// -----------------------------------------------------------
		}else{

			// -----------------------------------------------------------
			// ��X�e�[�^�X�ݒ�
			// -----------------------------------------------------------
			tk->stat = PLYACTTSUMOGIRI;

			// -----------------------------------------------------------
			// ���b�Z�[�W��`(���̐؂�)
			// -----------------------------------------------------------
			ActSndDahaiMes(gui, tk->ply_mjai_hum_id, tk->ply_act_tsumo[HUM_PLY_SEKI_NUM], tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM], true);   // �̔v���b�Z�[�W

			// -----------------------------------------------------------
			// �A�N�V������`(���̐؂�)
			// -----------------------------------------------------------
			// �A�N�V�����ݒ� - ���̐؂菈��
			tk->SetActInfo(tk->kyoku_index,
				PLYACTTSUMOGIRI,
				tk->ply_turn,
				4,
				tk->ply_act_tsumo[HUM_PLY_SEKI_NUM],
				tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]
			);

			// -----------------------------------------------------------
			// tk�N���X�̃A�N�V�������̍ŐV��
			// -----------------------------------------------------------
			tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

			// ----------------------------------------
			// �A�N�V�����ݒ�/���O�o��
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

			// ----------------------------------------
			// ply�N���X�̔v��̏���
			// ----------------------------------------

			// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
			if ( tk->ply_hum_mode == 0 ){

				// ���̎̔v����
				ply[HUM_PLY_SEKI_NUM].PlyActTsumoSute();

			}

		}

	// -----------------------------------------------------------
	// ����ȊO�̃v���[���[�̏ꍇ
	// -----------------------------------------------------------
	}else{
		// None���N�G�X�g�̑��M����
		ActSndNoneMes(gui);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �ÞȎ��̃A�N�V�����ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActkan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// �v���[���������Ȃ�
	// -----------------------------------------------------------
	if( tk->ply_turn == HUM_PLY_SEKI_NUM ){

		// None���N�G�X�g�̑��M����
		ActSndNoneMes(gui);

	// -----------------------------------------------------------
	// ����ȊO�̃v���[���[�̏ꍇ
	// -----------------------------------------------------------
	}else{
		// None���N�G�X�g�̑��M����
		ActSndNoneMes(gui);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���[�`���̃A�N�V�����ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActRiichi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// �v���[���������Ȃ�
	// -----------------------------------------------------------
	if( tk->ply_turn == HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// ply�N���X�z�v�ݒ�
		// ----------------------------------------

		// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
		if ( tk->ply_hum_mode == 0 ){

			// �A�N�V������`
			tk->ply_act = ply[HUM_PLY_SEKI_NUM].ply_act;

		}

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V������`(�̔v��)
		// -----------------------------------------------------------
		if(tk->ply_act == ACTSUTE){

			// �̔v�A�N�V����
			SetActSute(tk, ply, gui);

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V����(��O���������̐؂�)
		// -----------------------------------------------------------
		}else{

			// -----------------------------------------------------------
			// ��X�e�[�^�X�ݒ�
			// -----------------------------------------------------------
			tk->stat = PLYACTTSUMOGIRI;

			// -----------------------------------------------------------
			// ���b�Z�[�W��`(���̐؂�)
			// -----------------------------------------------------------
			ActSndDahaiMes(gui, tk->ply_mjai_hum_id, 
			                    tk->ply_act_tsumo[HUM_PLY_SEKI_NUM], 
			                    tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM], 
			                    true);   // �̔v���b�Z�[�W

			// -----------------------------------------------------------
			// �A�N�V������`(���̐؂�)
			// -----------------------------------------------------------
			// �A�N�V�����ݒ� - ���̐؂菈��
			tk->SetActInfo(tk->kyoku_index,
				PLYACTTSUMOGIRI,
				tk->ply_turn,
				4,
				tk->ply_act_tsumo[HUM_PLY_SEKI_NUM],
				tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]
			);

			// -----------------------------------------------------------
			// tk�N���X�̃A�N�V�������̍ŐV��
			// -----------------------------------------------------------
			tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

			// ----------------------------------------
			// �A�N�V�����ݒ�/���O�o��
			// ----------------------------------------
			if( gui->clientlog_output_flg == true){
				Output_Actionlog(tk, tk->kyoku_index);
			}

			// ----------------------------------------
			// ply�N���X�̔v��̏���
			// ----------------------------------------

			// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
			if ( tk->ply_hum_mode == 0 ){

				// ���̎̔v����
				ply[HUM_PLY_SEKI_NUM].PlyActTsumoSute();

			}

		}

	// -----------------------------------------------------------
	// ����ȊO�̃v���[���[�̏ꍇ
	// -----------------------------------------------------------
	}else{

		// None���N�G�X�g�̑��M����
		ActSndNoneMes(gui);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �̔v�A�N�V�����ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActSute(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// �̔v��`
	// -----------------------------------------------------------

	// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
	if ( tk->ply_hum_mode == 0 ){
		// �̔v��`
		tk->ply_act_sute[HUM_PLY_SEKI_NUM]     = ply[HUM_PLY_SEKI_NUM].ply_sute_hai;
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM] = ply[HUM_PLY_SEKI_NUM].ply_sute_aka;
	}else{
		// �̔v��`
		tk->ply_act_sute[HUM_PLY_SEKI_NUM]     = tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tk->ply_tbl_hum_sutehai_statnum];       // �̔v
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM] = tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM][tk->ply_tbl_hum_sutehai_statnum];  // �̔v��
	}

	// -----------------------------------------------------------
	// ���b�Z�[�W��`(�̔v)
	// -----------------------------------------------------------
	ActSndDahaiMes(gui, tk->ply_mjai_hum_id, 
	                    tk->ply_act_sute[HUM_PLY_SEKI_NUM],           // �̔v
	                    tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM],       // �̔v��
	                    false);                                       // ���̐؂�flg

	// -----------------------------------------------------------
	// �A�N�V������`(�̔v)
	// -----------------------------------------------------------
	// �A�N�V�����ݒ� - �̔v
	tk->SetActInfo(tk->kyoku_index,
		PLYACTSUTE,
		tk->ply_turn,
		4,
		tk->ply_act_sute[HUM_PLY_SEKI_NUM],
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM]
	);

	// -----------------------------------------------------------
	// tk�N���X�̃A�N�V�������̍ŐV��
	// -----------------------------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// �A�N�V�����ݒ�/���O�o��
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// ply�N���X�̔v��̏���
	// ----------------------------------------

	// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
	if ( tk->ply_hum_mode == 0 ){

		// ���̎̔v����
		ply[HUM_PLY_SEKI_NUM].PlyActTsumoSute();

	}

	// -----------------------------------------------------------
	// ��X�e�[�^�X�ݒ�
	// -----------------------------------------------------------
	tk->stat = PLYACTSUTE;

}

/* ---------------------------------------------------------------------------------------------- */
// �̃A�N�V�����ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActNakiSuteSub(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// -----------------------------------------------------------
	// �̔v��`
	// -----------------------------------------------------------

	// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
	if ( tk->ply_hum_mode == 0 ){
		// �̔v��`
		tk->ply_act_sute[HUM_PLY_SEKI_NUM]     = ply[HUM_PLY_SEKI_NUM].ply_sute_hai;
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM] = ply[HUM_PLY_SEKI_NUM].ply_sute_aka;
	}else{
		// �̔v��`
		tk->ply_act_sute[HUM_PLY_SEKI_NUM]     = tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tk->ply_tbl_hum_sutehai_statnum];       // �̔v
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM] = tk->ply_act_tehai_tbl_aka[HUM_PLY_SEKI_NUM][tk->ply_tbl_hum_sutehai_statnum];  // �̔v��
	}

	// -----------------------------------------------------------
	// ���b�Z�[�W��`(�̔v)
	// -----------------------------------------------------------
	ActSndDahaiMes(gui, tk->ply_mjai_hum_id, 
	                    tk->ply_act_sute[HUM_PLY_SEKI_NUM],           // �̔v
	                    tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM],       // �̔v��
	                    false);                                       // ���̐؂�flg

	// -----------------------------------------------------------
	// �A�N�V������`(�̔v)
	// -----------------------------------------------------------
	// �A�N�V�����ݒ� - �̔v
	tk->SetActInfo(tk->kyoku_index,
		PLYACTNAKISUTE,
		tk->ply_turn,
		4,
		tk->ply_act_sute[HUM_PLY_SEKI_NUM],
		tk->ply_act_sute_aka[HUM_PLY_SEKI_NUM]
	);

	// -----------------------------------------------------------
	// tk�N���X�̃A�N�V�������̍ŐV��
	// -----------------------------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// �A�N�V�����ݒ�/���O�o��
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// ply�N���X�̔v��̏���
	// ----------------------------------------

	// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
	if ( tk->ply_hum_mode == 0 ){

		// ���̎̔v����
		ply[HUM_PLY_SEKI_NUM].PlyActTsumoSute();

	}

	// -----------------------------------------------------------
	// ��X�e�[�^�X�ݒ�
	// -----------------------------------------------------------
	tk->stat = PLYACTNAKISUTE;

}

/* ---------------------------------------------------------------------------------------------- */
// �����̃A�N�V�����ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActNaki(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// ������
	int tmp_sute_hai  = 0;
	int tmp_aka_count = 0;

	// -----------------------------------------------------------
	// �v���[��������Ȃ�
	// -----------------------------------------------------------
	if( tk->ply_turn != HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// ply�N���X�z�v�ݒ�
		// ----------------------------------------

		// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
		if ( tk->ply_hum_mode == 0 ){

			// �A�N�V������`
			tk->ply_act_naki[HUM_PLY_SEKI_NUM]       = ply[HUM_PLY_SEKI_NUM].ply_act;               // ���A�N�V����
			tk->ply_naki_idx[HUM_PLY_SEKI_NUM]       = ply[HUM_PLY_SEKI_NUM].ply_naki_idx;          // ���vINDEX
			tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM] = ply[HUM_PLY_SEKI_NUM].ply_naki_aka_count;    // ��v�Ԃ̍��v��

		}

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V������`(������)
		// -----------------------------------------------------------
		if( tk->ply_act_naki[HUM_PLY_SEKI_NUM] == ACTRON){

			// �����a�����N�G�X�g�̑��M����
			ActSndHoraMes(gui, tk->ply_mjai_hum_id,                        // �a���v���[���[
			                   tk->ply_mjai_id[tk->ply_turn],              // ���A�N�V�����v���[���[(��ԃv���[���[)
			                   tk->ply_act_sute[tk->ply_turn],             // �̔v
			                   tk->ply_act_sute_aka[tk->ply_turn]);        // �̔v��

			// �A�N�V������`�F���Ȃ�
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V������`(�|����)
		// -----------------------------------------------------------
		}else if( tk->ply_act_naki[HUM_PLY_SEKI_NUM] == ACTPON){

			// �̔v�����u��
			tmp_sute_hai = tk->ply_act_sute[tk->ply_turn];

			// ��v�̐Ԕv�����m�F
			if ( ( tmp_sute_hai  ==  5 ) ||
			     ( tmp_sute_hai  == 15 ) ||
			     ( tmp_sute_hai  == 25 ) ){

				// �Ԕv�������J�E���g
				if ( tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10] > 2){
					// 3���ȏ�Ȃ�2
					tmp_aka_count = 2;
					tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10] = tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10] - 2;
					// 2���ȉ��Ȃ��v�̐Ԕv����
				}else{
					tmp_aka_count = tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10];
					tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10] = 0;
				}

			// �Ԕv�łȂ��Ȃ�
			}else{
					tmp_aka_count = 0;
			}

			// �|�����b�Z�[�W���`
			ActSndPonMes(gui, tk->ply_mjai_hum_id,                           // ���v���[���[
			                     tk->ply_mjai_id[tk->ply_turn],              // ���A�N�V�����v���[���[(��ԃv���[���[)
			                     tk->ply_act_sute[tk->ply_turn],             // ���v(�̔v)
			                     tk->ply_act_sute_aka[tk->ply_turn],         // �̔v��(�̔v��)
			                     tmp_aka_count);                             // ��v�Ԃ̍��v��

			// �A�N�V������`�F���Ȃ�
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V������`(�`�[��)
		// -----------------------------------------------------------
		}else if( tk->ply_act_naki[HUM_PLY_SEKI_NUM] == ACTCHI){

			// �`�[���b�Z�[�W���`
			ActSndChiMes(gui, tk->ply_mjai_hum_id,                           // ���v���[���[
			                     tk->ply_mjai_id[tk->ply_turn],              // ���A�N�V�����v���[���[(��ԃv���[���[)
			                     tk->ply_act_sute[tk->ply_turn],             // ���v(�̔v)
			                     tk->ply_act_sute_aka[tk->ply_turn],         // �̔v��(�̔v��)
			                     tk->ply_naki_idx[HUM_PLY_SEKI_NUM],         // �`�[INDEX�v
			                     tk->ply_naki_aka_count[HUM_PLY_SEKI_NUM]);  // ��v�Ԃ̍��v��

			// �A�N�V������`�F���Ȃ�
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V������`(�~���J����)
		// -----------------------------------------------------------
		}else if( tk->ply_act_naki[HUM_PLY_SEKI_NUM] == ACTMINKAN){

			// �̔v�����u��
			tmp_sute_hai = tk->ply_act_sute[tk->ply_turn];

			// ��v�̐Ԕv�����m�F
			if ( ( tmp_sute_hai  ==  5 ) ||
			     ( tmp_sute_hai  == 15 ) ||
			     ( tmp_sute_hai  == 25 ) ){

					// �Ԕv��`
					tmp_aka_count = tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10];
					tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_sute_hai-5)/10] = 0;

			// �Ԕv�łȂ��Ȃ�
			}else{
					tmp_aka_count = 0;
			}

			// �~���J�����b�Z�[�W���`
			ActSndMinkanMes(gui, tk->ply_mjai_hum_id,                        // ���v���[���[
			                     tk->ply_mjai_id[tk->ply_turn],              // ���A�N�V�����v���[���[(��ԃv���[���[)
			                     tk->ply_act_sute[tk->ply_turn],             // ���v(�̔v)
			                     tk->ply_act_sute_aka[tk->ply_turn],         // �̔v��(�̔v��)
			                     tmp_aka_count);                             // ��v�Ԃ̍��v��

			// �A�N�V������`�F���Ȃ�
			tk->ply_act_naki[HUM_PLY_SEKI_NUM] = ACTNONAKI;

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V����(��O�������������Ȃ�)
		// -----------------------------------------------------------
		}else{

			// None���N�G�X�g�̑��M����
			ActSndNoneMes(gui);

		}

	// -----------------------------------------------------------
	// �v���[���[�������̏ꍇ
	// -----------------------------------------------------------
	}else{

		// None���N�G�X�g�̑��M����
		ActSndNoneMes(gui);

	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���̔v���̃A�N�V�����ݒ�
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::SetActNakiSute(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// �v���[���������Ȃ�
	if( tk->ply_turn == HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// ply�N���X�̔v�ݒ�
		// ----------------------------------------

		// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
		if ( tk->ply_hum_mode == 0 ){

			// �A�N�V������`
			tk->ply_act = ply[HUM_PLY_SEKI_NUM].ply_act;

		}

		// -----------------------------------------------------------
		// �v���[���[�̃A�N�V������`(�̔v��)
		// -----------------------------------------------------------
		if(tk->ply_act == ACTNAKISUTE){

			// �̔v�A�N�V����
			SetActNakiSuteSub(tk, ply, gui);

		}

	// -----------------------------------------------------------
	// ����ȊO�̃v���[���[�̏ꍇ
	// -----------------------------------------------------------
	}else{
		// None���N�G�X�g�̑��M����
		ActSndNoneMes(gui);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// type���ƃ��b�Z�[�W�m�F(���C������)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ChkResMesMain(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui){

	// �A�N�V������`
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// ������
	bool possible_mode = false;

	// �v���[�g������
	gui->plt_mode[PLT_RIICHI] = false;
	gui->plt_mode[PLT_PON]    = false;
	gui->plt_mode[PLT_KAN]    = false;
	gui->plt_mode[PLT_CHI]    = false;
	gui->plt_mode[PLT_AGARI]  = false;

	// ���֘A�ϐ��̏�����
	gui->chihai_count = 0;              // �`�[���v�̏�����
	gui->naki_ankan_hai_count = 0;      // �ÞȔv����
	gui->naki_kakan_hai_count = 0;      // ���Ȕv����

	// ----------------------------------------
	// ��M���b�Z�[�W�̉��
	// ----------------------------------------
	for( int tmp_i = 0; tmp_i < gui->wk_str_count; tmp_i++ ) {

		// ----------------------------------------
		// possible_actions���[�h
		// ----------------------------------------

		if( possible_mode == true ){

			// ���s
			if(strcmp(gui->wk_str[tmp_i], "+" ) == 0 ){

				// possible_mode�̗L����
				possible_mode = false;

			// possible_actions�ǂݍ���
			}else if(strcmp(gui->wk_str[tmp_i], "type" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_possible_actions(tk, gui, tmp_i);

				// possible_actions�̒l���m�F���邽�߂�break�Ŕ����Ȃ�
				// break;

			}

		// ----------------------------------------
		// �ʏ탂�[�h
		// ----------------------------------------
		}else{

			// -----------------------
			// ���s
			// -----------------------
			if(strcmp(gui->wk_str[tmp_i], "+" ) == 0 ){

				// ���s�̏ꍇ�͉������Ȃ�

			// -----------------------
			// possible_actions�̗L����
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "possible_actions" ) == 0 ){

				// ������
				possible_mode = true;

			// -----------------------
			// ��J�n
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type" ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "start_game" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_startgame(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// �ǊJ�n
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type" ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "start_kyoku" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_startkyoku(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// ���̃A�N�V����
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "tsumo" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_tsumo(tk, ply, gui, tmp_i);

				// possible_actions�̒l���m�F���邽�߂�break�Ŕ����Ȃ�
				// break;

			// -----------------------
			// �ÞȃA�N�V����
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "ankan" ) == 0 ){

				// �A�N�V�����ݒ�F���[�`��̎̔v����
				Set_type_ankan(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// ���ȃA�N�V����
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "kakan" ) == 0 ){

				// �A�N�V�����ݒ�F���[�`��̎̔v����
				Set_type_kakan(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// ���[�`�A�N�V����
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "reach" ) == 0 ){

				// �A�N�V�����ݒ�F���[�`��̎̔v����
				Set_type_riichi(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// �̔v����
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "dahai" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_dahai(tk, ply, gui, tmp_i);

				// possible_actions�̒l���m�F���邽�߂�break�Ŕ����Ȃ�
				// break;

			// -----------------------
			// �|������
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "pon" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_pon(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// �`�[����
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "chi" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_chi(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// �~���J������
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "daiminkan" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_minkan(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// ���[�`�錾�󂯓���
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "reach_accepted" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_reach_accepted(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// �a���m�F
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "hora" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_hora(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// ����
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "ryukyoku" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_ryukyoku(tk, ply, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// �I��
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "end_kyoku" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_endkyoku(tk, gui, tmp_i);

				// ���b�Z�[�W�m��̂��߂ɏ�������
				break;

			// -----------------------
			// ��I��
			// -----------------------
			}else if(strcmp(gui->wk_str[tmp_i], "type"  ) == 0 && 
			         strcmp(gui->wk_str[tmp_i+1], "end_game" ) == 0 ){

				// �A�N�V�����ݒ�
				Set_type_endgame(tk, gui, tmp_i);

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

		}
	}

	// ----------------------------------------
	// �L���ȃA�N�V������񂪓����Ȃ��ꍇ
	// ----------------------------------------

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(start_game)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_startgame(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// �Ǐ��ݒ�
	// ----------------------------------------

	// ��Q�[�����
	tk->tkgame_type = TKGAME_MJAI;

	// �Ǐ��
	tk->kyoku[tk->kyoku_index].kyoku = 0;

	// �c�~�_
	tk->kyoku[tk->kyoku_index].tsumibo = 0;

	// ���[�`�_
	tk->kyoku[tk->kyoku_index].riichbo = 0;

	// ----------------------------------------
	// �O����
	// ----------------------------------------

	// HUM�v���[���[��Ply_id�ݒ�
	tk->ply_mjai_hum_id = atoi(gui->wk_str[tmp_wk_num+3]);

	// ----------------------------------------
	// ply_id�ƃv���[���[���̐ݒ�
	// ----------------------------------------

	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		// ply_id�ݒ�
		tk->ply_mjai_id[tmp_i] = ( tmp_i + 1 + tk->ply_mjai_hum_id ) % 4;
		// �v���[�����w��
		wsprintf(tk->plyname[tmp_i], gui->wk_str[ tk->ply_mjai_id[tmp_i] + tmp_wk_num+5 ]);
	}

	// ----------------------------------------
	// ply�ݒ�(��J�n)
	// ----------------------------------------
	// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
	if ( tk->ply_hum_mode == 0 ){
		ply[HUM_PLY_SEKI_NUM].PlyActTakuStart(HUM_PLY_SEKI_NUM);
	}

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = TAKUSTART;

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(start_kyoku)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_startkyoku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// �O����
	// ----------------------------------------

	// ������
	int  tmp_ply_id;
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
		tk->kyoku_index=0;
	}else{
		tk->kyoku_index++;
	}

	// ----------------------------------------
	// �Ǐ�񏉊���
	// ----------------------------------------
	tk->KyokuInit();

	// ----------------------------------------
	// �ǂ̎Z�o
	// ----------------------------------------

	// ��
	tk->kyoku[tk->kyoku_index].kyoku = Get_hainum(gui->wk_str[tmp_wk_num+3] ) - 31 + // E(����)��S(���)�̕�����m�F
	                                  atoi(gui->wk_str[tmp_wk_num+5]) - 1;          // �Ǐ��擾

	// ----------------------------------------
	// �Ǐ���`
	// ----------------------------------------

	// �{��
	tk->kyoku[tk->kyoku_index].tsumibo = atoi(gui->wk_str[tmp_wk_num+7]);

	// ���[�`�_
	tk->kyoku[tk->kyoku_index].riichbo = atoi(gui->wk_str[tmp_wk_num+9]);

	// �V�[�h�ԍ�
	tk->kyoku[tk->kyoku_index].seed_num = 0;

	// ----------------------------------------
	// ���_��`
	// ----------------------------------------
	if(tk->kyoku_index > 0){
		tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[0] = tk->kyoku[tk->kyoku_index-1].ply_kyoku_end_score[0];
		tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[1] = tk->kyoku[tk->kyoku_index-1].ply_kyoku_end_score[1];
		tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[2] = tk->kyoku[tk->kyoku_index-1].ply_kyoku_end_score[2];
		tk->kyoku[tk->kyoku_index].ply_kyoku_start_score[3] = tk->kyoku[tk->kyoku_index-1].ply_kyoku_end_score[3];
	}

	// ----------------------------------------
	// �h����`
	// ----------------------------------------

	// �h���\���v
	tmp_dora_hai = Get_hainum(gui->wk_str[tmp_wk_num+13]);

	// �Ԕv�m�F
	if (tmp_dora_hai > 100){
		tmp_dora_hai = tmp_dora_hai - 100;
		tmp_dora_aka = true;
	}else{
		tmp_dora_aka = false;
	}

	// �h���\���v��`
	tk->kyoku[tk->kyoku_index].dora[0]     = tmp_dora_hai;
	tk->kyoku[tk->kyoku_index].dora_aka[0] = tmp_dora_aka;

	// ----------------------------------------
	// ��Ԑݒ�(�e�̐Ȕԍ��w��)
	// ----------------------------------------
	tmp_ply_id = atoi(gui->wk_str[tmp_wk_num+11]);

	// ���Ԑݒ�
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		if (tmp_ply_id == tk->ply_mjai_id[tmp_i]){
			tk->ply_turn = tmp_i;
			break;
		}
	}

	// ----------------------------------------
	// �Ə��
	// ----------------------------------------
	tmp_ie_id = tk->ply_turn;
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		tk->kyoku[tk->kyoku_index].ie[tmp_ie_id] = tmp_i;
		tmp_ie_id = (tmp_ie_id+1) % 4;
	}

	// ----------------------------------------
	// pinfo�ݒ�(�ǊJ�n)
	// ----------------------------------------
	// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
	if ( tk->ply_hum_mode == 0 ){
		// ply[HUM_PLY_SEKI_NUM].PlyActKyokuStart(tk->kyoku[tk->kyoku_index].ie[HUM_PLY_SEKI_NUM]);
		ply[HUM_PLY_SEKI_NUM].PlyActKyokuStart(0,0,0,0, tk->kyoku[tk->kyoku_index].ie[HUM_PLY_SEKI_NUM], tk->kyoku[tk->kyoku_index].dora[0]);
	}

	// ----------------------------------------
	// �z�v�ݒ�
	// ----------------------------------------

	// �z�v�|�C���^�[�ݒ�
	haipai_point=tmp_wk_num + 15 + TEHAI_MAX * tk->ply_mjai_hum_id;

	// �z�v�ݒ�
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
		tk->kyoku[tk->kyoku_index].tehai[HUM_PLY_SEKI_NUM][now_tsumo_hai]++;

		// �Ԕv�ǉ�
		if(now_tsumo_aka == true){
			tk->kyoku[tk->kyoku_index].aka_count[HUM_PLY_SEKI_NUM][(now_tsumo_hai-5)/10]++;
		}

		// ----------------------------------------
		// ply�N���X�z�v�ݒ�
		// ----------------------------------------

		// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
		if ( tk->ply_hum_mode == 0 ){

			// ply�N���X�z�v
			ply[HUM_PLY_SEKI_NUM].PlyActHaipai(now_tsumo_hai, now_tsumo_aka);

			// �Ԕv�ݒ�
			for(int tmp_aka_grp = 0; tmp_aka_grp < AKA_TYPE_MAX_COUNT; tmp_aka_grp++){;
				ply[HUM_PLY_SEKI_NUM].aka_count[tmp_aka_grp] = tk->kyoku[tk->kyoku_index].aka_count[HUM_PLY_SEKI_NUM][tmp_aka_grp];
			}

			// �z�v��̊m�F����
			ply[HUM_PLY_SEKI_NUM].PlyActPostHaipai();

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

	// -----------------------------------------------------------
	// tk�N���X�̃A�N�V�������̍ŐV��
	// -----------------------------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

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
// type���Ƃł̒l�ݒ�(tsumo)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_tsumo(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// �A�N�V������`
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// ������
	int tmp_ply_id;

	// ��X�e�[�^�X�ݒ�
	tk->stat = PLYACTTSUMO;

	// ��Ԑݒ�
	tmp_ply_id = atoi(gui->wk_str[tmp_wk_num+3]);
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		if (tmp_ply_id == tk->ply_mjai_id[tmp_i]){
			tk->ply_turn = tmp_i;
			break;
		}
	}

	// ----------------------------------------
	// ���̃v���[���������Ȃ��
	// ----------------------------------------
	if( tk->ply_turn == HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// �v���ݒ�
		// ----------------------------------------

		// ���̔v�m�F
		tk->ply_act_tsumo[HUM_PLY_SEKI_NUM] = Get_hainum(gui->wk_str[tmp_wk_num+5]);

		// �Ԕv�m�F
		if (tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]  > 100){
			tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]  = tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]  - 100;
			tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM] = true;
		}else{
			tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM] = false;
		}

		// -----------------------------------------------------------
		// �A�N�V�����ݒ� - ���̏���
		// -----------------------------------------------------------
		tk->SetActInfo(tk->kyoku_index,
			PLYACTTSUMO,
			tk->ply_turn,
			4,
			tk->ply_act_tsumo[HUM_PLY_SEKI_NUM],
			tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]
		);

		// -----------------------------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// -----------------------------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// -----------------------------------------------------------
		// �A�N�V�����ݒ�/���O�o��
		// -----------------------------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

		// ----------------------------------------
		// pinfo�ݒ�(���̏���)
		// ----------------------------------------
		// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
		if ( tk->ply_hum_mode == 0 ){
			ply[HUM_PLY_SEKI_NUM].PlyActTsumo(tk->ply_act_tsumo[HUM_PLY_SEKI_NUM], tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]);
		}

	// ----------------------------------------
	// ���̃v���[����COM�Ȃ��
	// ----------------------------------------
	}else{

		// -----------------------------------------------------------
		// �A�N�V�����ݒ� - ���̏���(COM)
		// -----------------------------------------------------------

		// �A�N�V�����ݒ� - ���̏���(COM)
		tk->SetActInfo(tk->kyoku_index,
			PLYACTTSUMO,
			tk->ply_turn,
			4,
			0,                              // ���̔v���s���ȏꍇ�́u0�v�Ƃ���
			false
		);

		// -----------------------------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// -----------------------------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// -----------------------------------------------------------
		// �A�N�V�����ݒ�/���O�o��
		// -----------------------------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

	}
}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(ankan)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_ankan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// ������
	// ----------------------------------------

	int tmp_act_ply_id;
	int tmp_act_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka =false;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTANKAN;

	// ----------------------------------------
	// ACT�v���[���[�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_act_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);

	// ��ID�m�F
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// ���v���[���ԍ��̐ݒ�
		if (tmp_act_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_act_seki = tmp_i;
		}

	}

	// ----------------------------------------
	// �̔v�ݒ�(�v�e�[�u�������F����v���[���[)
	// ----------------------------------------
	if( tk->ply_turn != HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// �ÞȔv�m�F(1����)
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
		// �ÞȔv�m�F(2����)
		// ----------------------------------------

		// ��v�Ǎ�
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+6]);
		// �Ԕv�m�F
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			// �Ԕv���Z
			tmp_aka_count++;
		}

		// ----------------------------------------
		// �ÞȔv�m�F(3����)
		// ----------------------------------------

		// ��v�Ǎ�
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+7]);
		// �Ԕv�m�F
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			// �Ԕv���Z
			tmp_aka_count++;
		}

		// ----------------------------------------
		// �ÞȔv�m�F(4����)
		// ----------------------------------------

		// ��v�Ǎ�
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+8]);
		// �Ԕv�m�F
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
			// �Ԕv���Z
			tmp_aka_count++;
		}

		// ----------------------------------------
		// �A�N�V�����ݒ� - �Þ�
		// ----------------------------------------
		tk->SetActInfo(tk->kyoku_index,
			PLYACTANKAN,
			tmp_act_seki,
			4,
			tmp_naki_hai,
			tmp_naki_aka
		);

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// ----------------------------------------
		// �A�N�V�����ݒ�/���O�o��
		// ----------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

		// ----------------------------------------
		// �N�����ݒ� - �Þ�
		// ----------------------------------------
		tk->SetNakiInfo(tk->kyoku_index, 
			ANKAN, 
			tmp_act_seki,                                                            // ���v���[���[
			tk->kyoku[tk->kyoku_index].act_count,                                    // ACTID
			tmp_naki_hai,                                                            // ���v��`
			tmp_naki_hai,                                                            // ��INDEX�v��`
			tmp_aka_count);                                                          // �Ԕv�̖���

	// ----------------------------------------
	// �̔v�ݒ�(�v�e�[�u�������F�����v���[���[)
	// ----------------------------------------
	}else{

		// �����A�N�V�������Ȃ�

	}

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(kakan)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_kakan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// ������
	// ----------------------------------------

	int tmp_act_ply_id;
	int tmp_act_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka =false;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTKAKAN;

	// ----------------------------------------
	// ACT�v���[���[�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_act_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);

	// ��ID�m�F
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// ���v���[���ԍ��̐ݒ�
		if (tmp_act_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_act_seki = tmp_i;
		}

	}

	// ----------------------------------------
	// �̔v�ݒ�(�v�e�[�u�������F����v���[���[)
	// ----------------------------------------
	if( tk->ply_turn != HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// �ÞȔv�m�F(1����)
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
		// �A�N�V�����ݒ� - �Þ�
		// ----------------------------------------
		tk->SetActInfo(tk->kyoku_index,
			PLYACTKAKAN,
			tmp_act_seki,
			4,
			tmp_naki_hai,
			tmp_naki_aka
		);

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// ----------------------------------------
		// �A�N�V�����ݒ�/���O�o��
		// ----------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

		// ----------------------------------------
		// �N�����ݒ� - �Þ�
		// ----------------------------------------
		tk->SetNakiInfo(tk->kyoku_index, 
			KAKAN, 
			tmp_act_seki,                                                            // ���v���[���[
			tk->kyoku[tk->kyoku_index].act_count,                                    // ACTID
			tmp_naki_hai,                                                            // ���v��`
			tmp_naki_hai,                                                            // ��INDEX�v��`
			tmp_aka_count);                                                          // �Ԕv�̖���

	// ----------------------------------------
	// �̔v�ݒ�(�v�e�[�u�������F�����v���[���[)
	// ----------------------------------------
	}else{

		// �����A�N�V�������Ȃ�

	}
}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(reach�F���[�`��̎̔v����)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_riichi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// �ϐ���`
	int tmp_hai = 0;

	// ----------------------------------------
	// ���̃v���[����COM�Ȃ��
	// ----------------------------------------
	if( tk->ply_turn != HUM_PLY_SEKI_NUM ){

		// ----------------------------------------
		// �A�N�V�����ݒ� - ���[�`�錾
		// ----------------------------------------
		tk->SetActInfo(tk->kyoku_index,
			PLYACTRIICH,
			tk->ply_turn,
			4,
			0,
			false
		);

		// ----------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// ----------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// ----------------------------------------
		// �A�N�V�����ݒ�/���O�o��
		// ----------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

	// ----------------------------------------
	// ���̃v���[���������Ȃ��
	// ----------------------------------------
	}else{

		// ----------------------------------------
		// �̔v�s�L���̊m�F
		// ----------------------------------------
		if( (strcmp(gui->wk_str[tmp_wk_num+4], "cannot_dahai") == 0 ) && 
		    (strcmp(gui->wk_str[tmp_wk_num+5], "+") != 0 )            ){

			// ������
			gui->cannot_sutehai_count = 0;

			// GUI���[�h�ύX
			// gui->gui_ply_tehai_mode = TEHAI_RIICHI_SUTEHAI;

			// �̔v�s�e�[�u����`
			for(int tmp_i = tmp_wk_num+5; tmp_i < gui->wk_str_count; tmp_i++){

				// ���s�łȂ��Ȃ�
				if(strcmp(gui->wk_str[tmp_i], "+") != 0 ){

					// �̔v�s�̎Z�o
					tmp_hai = Get_hainum(gui->wk_str[tmp_i]);
					if ( tmp_hai > 100){
						tmp_hai = tmp_hai - 100;
					}

					// �̔v�s�e�[�u����`
					gui->cannot_sutehai[gui->cannot_sutehai_count] = tmp_hai;
					gui->cannot_sutehai_count++;

				}
			}

			// �V�����e�����e�[�u����`
			for(int tmp_i = 0; tmp_i < TEHAI_MAX; tmp_i++){

				// ������
				tk->ply_act_tehai_shanten_tbl[HUM_PLY_SEKI_NUM][tmp_i] = 0;
				tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = true;

				// ��r
				for(int tmp_j = 0; tmp_j < gui->cannot_sutehai_count; tmp_j++){
					 if(gui->cannot_sutehai[tmp_j] == tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_i]){
						// �s�e�[�u���ɔv�������
						tk->ply_act_tehai_shanten_tbl[HUM_PLY_SEKI_NUM][tmp_i] = 1;
						tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = false;
						break;
					 }
				}
			}

			// �V�����e�����E���̔v

				// ������
				tk->ply_act_tsumo_shanten[HUM_PLY_SEKI_NUM] = 0;
				tk->ply_act_tsumo_can_sute[HUM_PLY_SEKI_NUM] = true;

				// ��r
				for(int tmp_j = 0; tmp_j < gui->cannot_sutehai_count; tmp_j++){
					 if(gui->cannot_sutehai[tmp_j] == tk->ply_act_tsumo[HUM_PLY_SEKI_NUM]){
						// �s�e�[�u���ɔv�������
						tk->ply_act_tsumo_shanten[HUM_PLY_SEKI_NUM] = 1;
						tk->ply_act_tsumo_can_sute[HUM_PLY_SEKI_NUM] = false;
						break;
					 }
				}

		}

		// ----------------------------------------
		// pinfo�ݒ�(���[�`�㏈��)
		// ----------------------------------------
		// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
		if ( tk->ply_hum_mode == 0 ){
			ply[HUM_PLY_SEKI_NUM].PlyActTsumo(tk->ply_act_tsumo[HUM_PLY_SEKI_NUM], tk->ply_act_tsumo_aka[HUM_PLY_SEKI_NUM]);
		};

	}

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTRIICH;


}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(dahai)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_dahai(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// �A�N�V������`
	// https://gimite.net/pukiwiki/index.php?Mjai%20%E9%BA%BB%E9%9B%80AI%E5%AF%BE%E6%88%A6%E3%82%B5%E3%83%BC%E3%83%90

	// ----------------------------------------
	// ������
	// ----------------------------------------
	int tmp_ply_id;

	// ��Ԑݒ�
	tmp_ply_id = atoi(gui->wk_str[tmp_wk_num+3]);
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {
		if (tmp_ply_id == tk->ply_mjai_id[tmp_i]){
			tk->ply_turn = tmp_i;
			break;
		}
	}

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
	// �̔v�ݒ�(�v�e�[�u�������F����v���[���[)
	// ----------------------------------------
	if( tk->ply_turn != HUM_PLY_SEKI_NUM ){

		// �̔v�ݒ�
		tk->ply_act_sute[tk->ply_turn] = Get_hainum(gui->wk_str[tmp_wk_num+5]);

		// �Ԕv�m�F
		if ( tk->ply_act_sute[tk->ply_turn] > 100){
			 tk->ply_act_sute[tk->ply_turn] = tk->ply_act_sute[tk->ply_turn] - 100;
			 tk->ply_act_sute_aka[tk->ply_turn] = true;
		}else{
			 tk->ply_act_sute_aka[tk->ply_turn] = false;
		}

		// �f�o�O�p
		if ( tk->ply_act_sute[tk->ply_turn] > 37 || tk->ply_act_sute[tk->ply_turn] < 0){
			 tk->ply_act_sute[tk->ply_turn] = 0;
		}

		// -----------------------------------------------------------
		// �A�N�V�����ݒ�
		// -----------------------------------------------------------
		tk->SetActInfo(tk->kyoku_index,
			tk->stat,
			tk->ply_turn,
			4,
			tk->ply_act_sute[tk->ply_turn],
			tk->ply_act_sute_aka[tk->ply_turn]
		);

		// -----------------------------------------------------------
		// tk�N���X�̃A�N�V�������̍ŐV��
		// -----------------------------------------------------------
		tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

		// ----------------------------------------
		// �A�N�V�����ݒ�/���O�o��
		// ----------------------------------------
		if( gui->clientlog_output_flg == true){
			Output_Actionlog(tk, tk->kyoku_index);
		}

		// -----------------------------------------------------------
		// �����v���[���[���A�N�V������`
		// -----------------------------------------------------------

		// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
		if ( tk->ply_hum_mode == 0 ){
			// ply[HUM_PLY_SEKI_NUM].PlyChkNaki(tk->ply_turn, tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count]);
			ply[HUM_PLY_SEKI_NUM].PlyChkNaki(tk->ply_turn, tk->ply_act_sute[tk->ply_turn]);
		}

		// -----------------------------------------------------------
		// �̔v�ʒu�ݒ�
		// -----------------------------------------------------------
		tk->ply_tbl_com_sutehai_statnum[tk->ply_turn] = rand() % tk->ply_act_tehaicount[tk->ply_turn];

	// ----------------------------------------
	// �̔v�ݒ�(�v�e�[�u�������F�����v���[���[)
	// ----------------------------------------
	}else{

		// �����A�N�V�������Ȃ�

	}

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(pon)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_pon(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// ������
	// ----------------------------------------

	int tmp_naki_ply_id;
	int tmp_naki_seki;

	int tmp_target_ply_id;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACT�v���[���[(target�v���[���[)�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_naki_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_target_ply_id = atoi(gui->wk_str[tmp_wk_num+5]);

	// ��ID�m�F
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// ���v���[���ԍ��̐ݒ�
		if (tmp_naki_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_naki_seki = tmp_i;
		}

		// REACT�v���[���ԍ��̐ݒ�
		if (tmp_target_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_react_seki = tmp_i;
		}

	}

	// ���ԕύX
	tk->ply_turn = tmp_naki_seki;

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
		tmp_naki_seki,                                                            // ���v���[���[
		tk->kyoku[tk->kyoku_index].act_count,                                      // ACTID
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // ���v��`
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1], // ��INDEX�v��`
		tmp_aka_count);                                                           // �Ԕv�̖���

	// ----------------------------------------
	// tk�N���X�̃A�N�V�������̍ŐV��
	// ----------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// �A�N�V�����ݒ�/���O�o��
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// �̔v�s�e�[�u����`
	// ----------------------------------------

	// �̔v�s�e�[�u����`(�S�Ď̔v�\)
	for(int tmp_i = 0; tmp_i < tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; tmp_i++){
		// ������
		tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = true;
	}

	// ----------------------------------------
	// ply�N���X�ɃA�N�V�������������n��
	// ----------------------------------------

	// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
	if ( tk->ply_hum_mode == 0 ){

		// ���������n��
		ply[HUM_PLY_SEKI_NUM].PlyActNaki( tmp_naki_seki,   // �����F���v���[���[�ԍ�
		                      ACTPON,                  // ���A�N�V����
		                      tmp_naki_hai,            // ���v
		                      tmp_naki_hai,            // ��INDEX
		                      tmp_naki_aka             // �Ԕv����
		); 

	}

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTPON;

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(chi)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_chi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// ������
	// ----------------------------------------

	int tmp_naki_ply_id;
	int tmp_naki_seki;

	int tmp_target_ply_id;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	int tmp_naki_tehai_hai1 = 0;
	int tmp_naki_tehai_hai2 = 0;
	int tmp_hai = 0;
	int tmp_chi_idx = 0;

	// cannot_dahai��`�p
	int cannot_hai_count=0;
	int tmp_cannot_hai = 0;

	// ----------------------------------------
	// REACT�v���[���[(target�v���[���[)�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_naki_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_target_ply_id = atoi(gui->wk_str[tmp_wk_num+5]);

	// ��ID�m�F
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id )
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// ���v���[���ԍ��̐ݒ�
		if (tmp_naki_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_naki_seki = tmp_i;
		}

		// REACT�v���[���ԍ��̐ݒ�
		if (tmp_target_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_react_seki = tmp_i;
		}

	}

	// ���ԕύX
	tk->ply_turn = tmp_naki_seki;

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
		tmp_naki_seki,                       // ���v���[���[
		tk->kyoku[tk->kyoku_index].act_count, // ACTID
		tmp_naki_hai,                        // ���v
		tmp_chi_idx,                         // ���vINDEX
		tmp_aka_count                        // �Ԕv���� 
	);

	// ----------------------------------------
	// tk�N���X�̃A�N�V�������̍ŐV��
	// ----------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// �A�N�V�����ݒ�/���O�o��
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// �̔v�s�L���̊m�F(���̔v��)
	// ----------------------------------------

	// �̔v�s�e�[�u����`
	for(int tmp_i = 0; tmp_i < tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; tmp_i++){
		tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = true;
	}

	// cannot_dahai�v�̊m�F
	if( (strcmp(gui->wk_str[tmp_wk_num+11], "cannot_dahai") == 0 ) && 
	    (strcmp(gui->wk_str[tmp_wk_num+12], "+") != 0 )            ){

		// ������
		gui->cannot_sutehai_count = 0;

		// �e�[�u����`
		for(int tmp_i = tmp_wk_num+12; tmp_i < gui->wk_str_count; tmp_i++){

			// ���s�łȂ��Ȃ�
			if(strcmp(gui->wk_str[tmp_i], "+") != 0 ){

				// �̔v�s�̎Z�o
				tmp_hai = Get_hainum(gui->wk_str[tmp_i]);
				if ( tmp_hai > 100){
					tmp_hai = tmp_hai - 100;
				}

				// �̔v�s�e�[�u����`
				gui->cannot_sutehai[gui->cannot_sutehai_count] = tmp_hai;
				gui->cannot_sutehai_count++;

			}
		}

		// �̔v�s�e�[�u����`
		for(int tmp_i = 0; tmp_i < tk->ply_act_tehaicount[HUM_PLY_SEKI_NUM]; tmp_i++){
			// ������
			tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = true;

			// ��r
			for(int tmp_j = 0; tmp_j < gui->cannot_sutehai_count; tmp_j++){
				 if(gui->cannot_sutehai[tmp_j] == tk->ply_act_tehaitbl[HUM_PLY_SEKI_NUM][tmp_i]){
					// �s�e�[�u���ɔv�������
					tk->ply_act_tehai_can_sute_tbl[HUM_PLY_SEKI_NUM][tmp_i] = false;
					break;
				 }
			}

		}

	}

	// ----------------------------------------
	// ply�N���X�ɃA�N�V�������������n��
	// ----------------------------------------

	// �N���C�A���g�Q�[�����[�h��PLY���[�h�ł��邩
	if ( tk->ply_hum_mode == 0 ){

		// ���������n��
		ply[HUM_PLY_SEKI_NUM].PlyActNaki( tmp_naki_seki,   // �����F���v���[���[�ԍ�
		                      ACTCHI,                  // ���A�N�V����
		                      tmp_naki_hai,            // ���v
		                      tmp_chi_idx,             // ��INDEX
		                      tmp_aka_count            // �Ԕv����
		);
	}

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTCHI;

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(minkan)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_minkan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// ������
	// ----------------------------------------

	int tmp_naki_ply_id;
	int tmp_naki_seki;

	int tmp_target_ply_id;
	int tmp_react_seki;

	int  tmp_naki_hai = 0;
	bool tmp_naki_aka = false ;
	int  tmp_aka_count = 0;

	// ----------------------------------------
	// REACT�v���[���[(target�v���[���[)�̓���
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_naki_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_target_ply_id = atoi(gui->wk_str[tmp_wk_num+5]);

	// ��ID�m�F
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// ���v���[���ԍ��̐ݒ�
		if (tmp_naki_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_naki_seki = tmp_i;
		}

		// REACT�v���[���ԍ��̐ݒ�
		if (tmp_target_ply_id == tk->ply_mjai_id[tmp_i]){
			tmp_react_seki = tmp_i;
		}

	}

	// ���ԕύX
	tk->ply_turn = tmp_naki_seki;

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

	// ��v�̐Ԕv�����m�F
	if ( ( tmp_naki_hai  == MAN5NUM ) ||
	     ( tmp_naki_hai  == PIN5NUM ) ||
	     ( tmp_naki_hai  == SOU5NUM ) ){
			// �Ԕv��`
			tmp_aka_count = tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_naki_hai-5)/10];
			tk->ply_act_aka_count[HUM_PLY_SEKI_NUM][(tmp_naki_hai-5)/10] = 0;
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
		tmp_naki_seki,                                                                    // ���v���[���[
		tk->kyoku[tk->kyoku_index].act_count,                                             // ACTID
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],       // ���v��`
		tk->kyoku[tk->kyoku_index].act_hai[tk->kyoku[tk->kyoku_index].act_count-1],       // ��INDEX�v��`
		tmp_aka_count);                                                                   // �Ԕv�̖���

	// ----------------------------------------
	// tk�N���X�̃A�N�V�������̍ŐV��
	// ----------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// �A�N�V�����ݒ�/���O�o��
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYACTMINKAN;

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(reach_accepted)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_reach_accepted(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// ���ݓ��_��ݒ�
	// ----------------------------------------

	// ply_id�֘A
	int tmp_ply_id_0_seki;

	// ��ID�m�F
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// ply_mjai_id = 0�̃v���[���ԍ��̐ݒ�
		if (tk->ply_mjai_id[tmp_i] == 0){
			tmp_ply_id_0_seki = tmp_i;
		}

	}

	// ���_����

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = PLYRIICHACCEPTED;

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(hora)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_hora(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// ������
	// ----------------------------------------

	// �ǂݍ��݃��[�h
	int yakus_read_mode = 0; // (0:�Ǎ��J�n�O�A1:���h���Ǎ����A2:�a����v�Ǎ����A3:�����Ǎ����A4:�Ǎ��I��)

	// ply_id�֘A
	int tmp_agari_ply_id;
	int tmp_target_ply_id;
	int tmp_ply_id_0_seki;

	// �v�֘A
	int tmp_hai = 0;
	int tmp_aka = false;

	// ��v����������
	tk->kyoku[tk->kyoku_index].agari_tehaicount = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount = 0;

	// -----------------------------
	// �l��`
	// -----------------------------
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount     = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_mangan_count = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai=0;

	// ----------------------------------------
	// ���ǃt���O
	// ----------------------------------------
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_flg = false;

	// ----------------------------------------
	// �a���v���[���[�̎w��
	// ----------------------------------------

	// �v���[���[ID�m�F
	tmp_agari_ply_id  = atoi(gui->wk_str[tmp_wk_num+3]);
	tmp_target_ply_id = atoi(gui->wk_str[tmp_wk_num+5]);

	// ��ID�m�F
	// tk->ply_turn = ( tmp_ply_id + 1 + tk->ply_mjai_hum_id ) % 4; // tmp_i = tmp_ply_id - ( 3 - tk->ply_mjai_hum_id)
	for( int tmp_i = 0; tmp_i < PLAYER_MAX; tmp_i++ ) {

		// �a���v���[���ԍ��̐ݒ�
		if (tmp_agari_ply_id == tk->ply_mjai_id[tmp_i]){
			tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_num = tmp_i;
		}

		// �U���v���[���ԍ��̐ݒ�
		if (tmp_target_ply_id == tk->ply_mjai_id[tmp_i]){
			tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].furikomi_ply_num = tmp_i;
		}

		// ply_mjai_id = 0�̃v���[���ԍ��̐ݒ�
		if (tk->ply_mjai_id[tmp_i] == 0){
			tmp_ply_id_0_seki = tmp_i;
		}

	}

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�(�a���v���[���[�ƃ^�[�Q�b�g�������Ȃ�Ύ��̘a���̐ݒ�)
	// ----------------------------------------
	if ( tmp_agari_ply_id == tmp_target_ply_id ){
		tk->stat = PLYTSUMOAGARI;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].tsumo_agari_flg = true;
	}else{
		tk->stat = PLYACTRON;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].tsumo_agari_flg = false;
	}

	// ----------------------------------------
	// �����
	// ----------------------------------------
	// wk�\���̓Ǎ�
	for(int tmp_i = 0; tmp_i < gui->wk_str_count-tmp_wk_num; tmp_i++){

		// -----------------------------
		// 0:�Ǎ��J�n�O
		// -----------------------------
		if( yakus_read_mode == 0){

			// �a���v���[��
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "actor") == 0 ){
				// �������Ȃ�
			}

			// �U���v���[��
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "target") == 0 ){
				// �������Ȃ�
			}

			// �a���v
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "pai") == 0 ){

				// �v�ǂݍ���
				tmp_hai = Get_hainum(gui->wk_str[tmp_wk_num+tmp_i+1]);
				// �Ԕv�m�F
				if (tmp_hai > 100){
					tmp_hai = tmp_hai - 100;
					tmp_aka = true;
				}else{
					tmp_aka = false;
				}

				// �a���v�o�^
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_hai = tmp_hai;
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_aka = tmp_aka;

				// ���ɃJ�E���g����
				tmp_i++;

			}

			// ��Ǎ��J�n�Ȃ�
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "uradora_markers") == 0 ){
				yakus_read_mode = 1;
			}

		// -----------------------------
		// 1:���h���Ǎ���
		// -----------------------------
		}else if( yakus_read_mode == 1){

			// ��v�m�F
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "hora_tehais") == 0 ){
				yakus_read_mode = 2;
			}else{
				// ��v�Ǎ�
				tmp_hai = Get_hainum(gui->wk_str[tmp_wk_num+tmp_i]);
				// �Ԕv�m�F
				if (tmp_hai > 100){
					tmp_hai = tmp_hai - 100;
					tmp_aka = true;
				}else{
					tmp_aka = false;
				}
				// ���h���o�^
			}

		// -----------------------------
		// 2:�a����v���Ǎ���
		// -----------------------------
		}else if( yakus_read_mode == 2){

			// ��Ǎ��J�n�Ȃ�
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "yakus") == 0 ){
				yakus_read_mode = 3;
			}else{
				// �a���v�ȊO����v�Ǎ�
				// if (tk->kyoku[tk->kyoku_index].agari_tehaicount < TEHAI_MAX){
				if ( tk->kyoku[tk->kyoku_index].agari_tehaicount < tk->ply_act_tehaicount[tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_num] ){
					// �v�ԍ��擾
					tmp_hai = Get_hainum(gui->wk_str[tmp_wk_num+tmp_i]);
					// �Ԕv�m�F
					if (tmp_hai > 100){
						tmp_hai = tmp_hai - 100;
						tmp_aka = true;
					}else{
						tmp_aka = false;
					}
					// �a���e�[�u���ɓo�^
					tk->kyoku[tk->kyoku_index].agari_tehaitbl[tk->kyoku[tk->kyoku_index].agari_tehaicount]     = tmp_hai;
					tk->kyoku[tk->kyoku_index].agari_tehaitbl_aka[tk->kyoku[tk->kyoku_index].agari_tehaicount] = tmp_aka;
					tk->kyoku[tk->kyoku_index].agari_tehaicount++;
				}

			}

		// -----------------------------
		// 3:�����Ǎ���
		// -----------------------------
		}else if( yakus_read_mode == 3){

			// ���ł���Ȃ�
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "fu") == 0 ){

				// ���ǂݍ���
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].scoreFu = atoi(gui->wk_str[tmp_wk_num+tmp_i+1]);

				// ���ɃJ�E���g����
				tmp_i++;

				// ���[�h�ύX
				yakus_read_mode = 4;

			// �����ǂݍ���
			}else{

				// ��ǂݍ���
				Set_type_hora_yaku_check(tk, ply, gui, tmp_wk_num+tmp_i);

				// +1�J�E���g����
				tmp_i++;

			}

		// -----------------------------
		// 4:�Ǎ��I��
		// -----------------------------
		}else if( yakus_read_mode == 4){

			// �|���
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "fan") == 0 ){
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han = atoi(gui->wk_str[tmp_wk_num+tmp_i+1]);
			}

			// �a�����_(delta)
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "deltas") == 0 ){

				// ���_�ݒ�
				for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
					tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[(tmp_ply_id_0_seki + ply_i)%4] = atoi(gui->wk_str[tmp_wk_num+tmp_i+ply_i+1]);
				}

				// ���ɃJ�E���g����
				tmp_i = tmp_i + 4;

			}

			// �ǏI�����_
			if(strcmp(gui->wk_str[tmp_wk_num+tmp_i], "scores") == 0 ){

				// ���_�ݒ�
				for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
					tk->kyoku[tk->kyoku_index].ply_kyoku_end_score[(tmp_ply_id_0_seki + ply_i)%4] = atoi(gui->wk_str[tmp_wk_num+tmp_i+ply_i+1]);
				}

				// ���ɃJ�E���g����
				tmp_i = tmp_i + 4;

			}

		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(hora�F���m�F)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_hora_yaku_check(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_yaku_num){

	// -----------------------------
	// �ʏ��
	// -----------------------------

	// 01: ���[�`
	if(strcmp(gui->wk_str[tmp_yaku_num], "reach") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[RIICH] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RIICH] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RIICH];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 02: �_�u�����[�`
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "double_reach") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[WRIICH] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[WRIICH] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[WRIICH];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 03: �ꔭ
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "ippatsu") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[IPPATSU] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[IPPATSU] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[IPPATSU];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 04: ����F
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "chiniso") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[CHINISO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHINISO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHINISO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 05: ����F
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "honiso") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[HONISO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HONISO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HONISO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 06: ���S��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "junchantaiyao") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[JUNCHAN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[JUNCHAN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[JUNCHAN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 07: ��u��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "ryanpeko") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[RYANPEKO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RYANPEKO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RYANPEKO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 08: ���V��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "honroto") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[HONROTO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HONROTO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HONROTO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 09: ���O��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "shosangen") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[SHOSANGEN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SHOSANGEN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SHOSANGEN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 10: ��C�ʊ�
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "ikkitsukan") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[ITSU] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[ITSU] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[ITSU];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 11: �O�F����
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sanshokudoko") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[SANDOKOU] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANDOKOU] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANDOKOU];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 12: �O�F����
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sanshokudojun") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[SANDOJUN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANDOJUN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANDOJUN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 13: �O�Ȏq
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sankantsu") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[SANKANTSU] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANKANTSU] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANKANTSU];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 14: �O�Í�
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sananko") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[SANANKO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANANKO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[SANANKO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 15: �΁X�a
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "toitoiho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[TOITOI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TOITOI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TOITOI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 16: ���S��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "honchantaiyao") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[CHANTA] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHANTA] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHANTA];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 17: ���Ύq
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "chitoitsu") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[CHITOI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHITOI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[CHITOI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 18: ���a
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "pinfu") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[PINFU] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[PINFU] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[PINFU];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 19: �f����
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "tanyaochu") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[TANYAO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TANYAO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TANYAO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 20: ��u��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "ipeko") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[IPEKO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[IPEKO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[IPEKO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 21: �ꕗ�v
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "bakaze") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[BAKAZE] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[BAKAZE] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[BAKAZE];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 22: �����v
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "jikaze") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[ZIKAZE] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[ZIKAZE] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[ZIKAZE];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 23: �O���v
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sangenpai") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[YAKUHAI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[YAKUHAI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[YAKUHAI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 27: �C��̌�
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "haiteiraoyue") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[HAITEI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HAITEI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HAITEI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 28: �͒ꝝ��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "hoteiraoyui") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[HOUTEI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HOUTEI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[HOUTEI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 29: ���J��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "rinshankaiho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[RINSHAN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RINSHAN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[RINSHAN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 30: ����
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "chankan") == 0 ){

	// 31: ��O�����̘a
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "menzenchin_tsumoho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[TSUMO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TSUMO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[TSUMO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 32: �h��(�\�h��)
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "dora") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[DORA] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[DORA] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han  = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[DORA];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 33: ���h��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "uradora") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[URADORA] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[URADORA] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han     = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[URADORA];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// 34: �Ԕv
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "akadora") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_flg[AKAHAI] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[AKAHAI] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han   = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].agari_ply_han + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yaku_han[AKAHAI];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount++;

	// -----------------------------
	// ��
	// -----------------------------

	// ��01: �V�a
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "tenho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_flg[TENHO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[TENHO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[TENHO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count++;

	// ��02: �n�a
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "chiho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_flg[CHIHO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[CHIHO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[CHIHO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count++;

	// ��03: ��A��ʑ҂�
	// ��04: ��A��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "churenpoton") == 0 ){

	// ��05: ���m13��
	// ��06: ���m���o
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "kokushimuso") == 0 ){

	// ��07: ��O��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "daisangen") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_flg[DAISANGEN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[DAISANGEN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[DAISANGEN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count++;

	// ��08: ��l��a
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "daisushi") == 0 ){

	// ��09: ���l��a
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "shosushi") == 0 ){

	// ��10: ����F
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "tsuiso") == 0 ){

	// ��11: ���V��
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "chinroto") == 0 ){

	// ��12: �Έ�F
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "ryuiso") == 0 ){

	// ��13: �l�Ȏq
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "sukantsu") == 0 ){

	// ��15: �l�Í�
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "suanko") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_flg[SUANKO] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[SUANKO] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[SUANKO];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count++;

	// ��16: �l�a(��)
	}else if(strcmp(gui->wk_str[tmp_yaku_num], "renho") == 0 ){
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_flg[RENHOYAKUMAN] = true;
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[RENHOYAKUMAN] = atoi(gui->wk_str[tmp_yaku_num+1]);
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai = tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_agari_ply_bai + tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_bai[RENHOYAKUMAN];
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count++;
	}

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(ryukyoku)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_ryukyoku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// �ϐ���`
	// ----------------------------------------
	int tmp_ply_id_0_seki;

	// ----------------------------------------
	// ��ID�m�F
	// ----------------------------------------
	for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++ ) {
		// ply_mjai_id = 0�̃v���[���ԍ��̐ݒ�
		if (tk->ply_mjai_id[tmp_pnum] == 0){
			tmp_ply_id_0_seki = tmp_pnum;
		}
	}

	// ----------------------------------------
	// ���ǃt���O
	// ----------------------------------------
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_flg  = true;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakuman_count = 0;
	tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].yakucount     = 0;

	// ----------------------------------------
	// ���ǃX�e�[�^�X�ݒ�
	// ----------------------------------------
	if(strcmp(gui->wk_str[tmp_wk_num+3], "fanpai") == 0 ){
		// ���ǁF�r�v
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_stat = HOWANPAI;
	}else if(strcmp(gui->wk_str[tmp_wk_num+3], "sufonrenta") == 0 ){
		// ���ǁF�l���A��
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_stat = SUFURENDA;
	}else if(strcmp(gui->wk_str[tmp_wk_num+3], "suchareach") == 0 ){
		// ���ǁF�l�l���[�`
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_stat = RIICHI4PLY;
	}else{
		// ���ǁF�s��
		tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ryukyoku_stat = UNKNOWNRKK;
	}

	// -----------------------------
	// wk�\���̓Ǎ�
	// -----------------------------
	for(int tmp_ryukyoku_num = tmp_wk_num+4; tmp_ryukyoku_num < gui->wk_str_count; tmp_ryukyoku_num++){

		// �e���p�C�m�F(tenpais)
		if(strcmp(gui->wk_str[tmp_ryukyoku_num], "tenpais") == 0 ){

			// �e���p�C�l���̏�����
			tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ply_tempai_count = 0;

			// �v���[�����Ƃ̃e���p�C�m�F
			for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
				if(strcmp(gui->wk_str[tmp_ryukyoku_num+1+ply_i], "true") == 0 ){
					tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ply_tempai_flg[(tmp_ply_id_0_seki + ply_i)%4] = true;
					tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ply_tempai_count++;
				}else{
					tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].ply_tempai_flg[(tmp_ply_id_0_seki + ply_i)%4] = false;
				}
			}
		}

		// �Ǔ��_(delta)
		if(strcmp(gui->wk_str[tmp_ryukyoku_num], "deltas") == 0 ){
			for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
				tk->kyoku[tk->kyoku_index].ply_agari_yk[tk->kyoku[tk->kyoku_index].agari_ply_count].kyoku_score[(tmp_ply_id_0_seki + ply_i)%4] = atoi(gui->wk_str[tmp_ryukyoku_num+1+ply_i]);
			}
		}

		// �ǏI�������_(score)
		if(strcmp(gui->wk_str[tmp_ryukyoku_num], "scores") == 0 ){
			for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
				tk->kyoku[tk->kyoku_index].ply_kyoku_end_score[(tmp_ply_id_0_seki + ply_i)%4] = atoi(gui->wk_str[tmp_ryukyoku_num+1+ply_i]);
			}
		}

	}

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

	// ----------------------------------------
	// tk�N���X�̃A�N�V�������̍ŐV��
	// ----------------------------------------
	tk->Check_Ply_ActTehai(tk->kyoku_index, tk->kyoku[tk->kyoku_index].act_count);

	// ----------------------------------------
	// �A�N�V�����ݒ�/���O�o��
	// ----------------------------------------
	if( gui->clientlog_output_flg == true){
		Output_Actionlog(tk, tk->kyoku_index);
	}

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = RYUKYOKU;

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(endkyoku)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_endkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = KYOKURESULT;

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(endgame)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_type_endgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// �ϐ���`
	// ----------------------------------------
	int tmp_ply_id_0_seki;

	// ----------------------------------------
	// ��ID�m�F
	// ----------------------------------------
	for( int tmp_pnum = 0; tmp_pnum < PLAYER_MAX; tmp_pnum++ ) {
		// ply_mjai_id = 0�̃v���[���ԍ��̐ݒ�
		if (tk->ply_mjai_id[tmp_pnum] == 0){
			tmp_ply_id_0_seki = tmp_pnum;
		}
	}

	// ----------------------------------------
	// �ŏI���_���_�ݒ�
	// ----------------------------------------
	for(int ply_i = 0; ply_i < PLAYER_MAX; ply_i++){
		tk->plyEndscore[(tmp_ply_id_0_seki + ply_i)%4] = atoi(gui->wk_str[tmp_wk_num+3+ply_i]);
	}

	// ----------------------------------------
	// ��X�e�[�^�X�ݒ�
	// ----------------------------------------
	tk->stat = TAKURESULT;

}

/* ---------------------------------------------------------------------------------------------- */
// type���Ƃł̒l�ݒ�(possible_actions)
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Set_possible_actions(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num){

	// ----------------------------------------
	// �ϐ���`
	// ----------------------------------------
	int tmp_naki_hai = 0;
	int tmp_naki_tehai_hai1 = 0;   // �v1����
	int tmp_naki_tehai_hai2 = 0;   // �v2����
	int tmp_num = 0;               // �����p�ϐ�
	int tmp_chi_idx = 0;           // �`�[�vINDEX

	// �Ԕv�J�E���g
	int tmp_aka_count = 0;

	// ----------------------------------------
	// �a���A�N�V����
	// ----------------------------------------
	if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	   strcmp(gui->wk_str[tmp_wk_num+1], "hora" ) == 0 ){

		// �v���[�g�L����
		gui->plt_mode[PLT_AGARI]  = true;

		// �����a���ł���Ȃ灨�����ȊO�̎�ԂȂ�
		if ( tk->ply_turn != HUM_PLY_SEKI_NUM){

			// ���m�F���̎̔v���F
			if ( ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 0) || 
			     ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 5)
			   ){
				// �F���F
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] = 
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] + HAI_COLOR_NUM_BLUE;
			}
		}

	// ----------------------------------------
	// ���[�`�A�N�V����
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "reach" ) == 0 ){

		// �v���[�g�L����
		gui->plt_mode[PLT_RIICHI] = true;

	// ----------------------------------------
	// �ÞȃA�N�V����
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "ankan" ) == 0 ){

		// �v���[�g�L����
		gui->plt_mode[PLT_KAN]    = true;

		// ���v�̎Z�o
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+5]);
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
		}

		// �ÞȌ��v�̐ݒ�
		gui->naki_ankan_hai[gui->naki_ankan_hai_count] = tmp_naki_hai;
		gui->naki_ankan_hai_count++;

	// ----------------------------------------
	// ���ȃA�N�V����
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "kakan" ) == 0 ){

		// �v���[�g�L����
		gui->plt_mode[PLT_KAN]    = true;

		// ���v�̎Z�o
		tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+5]);
		if (tmp_naki_hai > 100){
			tmp_naki_hai = tmp_naki_hai - 100;
		}

		// ���Ȍ��v�̐ݒ�
		gui->naki_kakan_hai[gui->naki_kakan_hai_count] = tmp_naki_hai;
		gui->naki_kakan_hai_count++;

	// ----------------------------------------
	// ���ȃA�N�V����
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "daiminkan" ) == 0 ){

		// �L�t���O���L���ł���Ȃ�
		if( gui->plt_nakiari_flg == true ){

			// �v���[�g�L����
			gui->plt_mode[PLT_KAN]    = true;

			// ���m�F���̎̔v���F
			if ( ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 0) || 
			     ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 5)
			   ){
				// �F���F
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] = 
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] + HAI_COLOR_NUM_BLUE;
			}

		}

	// ----------------------------------------
	// �|���A�N�V����
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "pon" ) == 0 ){

		// �L�t���O���L���ł���Ȃ�
		if( gui->plt_nakiari_flg == true ){

			// �v���[�g�L����
			gui->plt_mode[PLT_PON]    = true;

			// ���m�F���̎̔v���F
			if ( ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 0) || 
			     ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 5)
			   ){
				// �F���F
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] = 
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] + HAI_COLOR_NUM_BLUE;
			}
		}

	// ----------------------------------------
	// �`�[�A�N�V����
	// ----------------------------------------
	}else if(strcmp(gui->wk_str[tmp_wk_num], "type"  ) == 0 && 
	         strcmp(gui->wk_str[tmp_wk_num+1], "chi" ) == 0 ){

		// �L�t���O���L���ł���Ȃ�
		if( gui->plt_nakiari_flg == true ){

			// �v���[�g�L����
			gui->plt_mode[PLT_CHI]    = true;

			// ���m�F���̎̔v���F
			if ( ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 0) || 
			     ( tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] == 5)
			   ){
				// �F���F
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] = 
				tk->ply_act_kawa_mode[tk->ply_turn][tk->ply_act_kawa_count[tk->ply_turn]-1] + HAI_COLOR_NUM_BLUE;
			}

			// ���v�̎Z�o
			tmp_naki_hai = Get_hainum(gui->wk_str[tmp_wk_num+7]);
			if (tmp_naki_hai > 100){
				tmp_naki_hai = tmp_naki_hai - 100;
			}

			// �\���v1���ڊm�F
			tmp_naki_tehai_hai1 = Get_hainum(gui->wk_str[tmp_wk_num+9]);
			if (tmp_naki_tehai_hai1 > 100){
				tmp_naki_tehai_hai1 = tmp_naki_tehai_hai1 - 100;
				tmp_aka_count++;
			}

			// �\���v2���ڊm�F
			tmp_naki_tehai_hai2 = Get_hainum(gui->wk_str[tmp_wk_num+10]);
			if (tmp_naki_tehai_hai2 > 100){
				tmp_naki_tehai_hai2 = tmp_naki_tehai_hai2 - 100;
				tmp_aka_count++;
			}

			// 1����2���ڂ̑召��r�E����
			if(tmp_naki_tehai_hai1 > tmp_naki_tehai_hai2){
				tmp_num = tmp_naki_tehai_hai1;
				tmp_naki_tehai_hai1 = tmp_naki_tehai_hai2;
				tmp_naki_tehai_hai2 = tmp_num;
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

			// �`�[�v�ݒ�
			gui->chi_idx_hai[gui->chihai_count]   = tmp_chi_idx;
			gui->chi_aka_count[gui->chihai_count] = tmp_aka_count;
			gui->chihai_count++;
		}

	} // "type"�m�F�I��

}

/* ---------------------------------------------------------------------------------------------- */
// �̔v�̃��b�Z�[�W��`
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndDahaiMes(MJSGui *gui, int ply_mjai_id, int hai, bool aka_flg, bool tsumogiri_flg){

	// �ϐ���`
	char tmp_hai_chr[5];

	// Mes�擾�����F�����擾
	Get_haichr(hai, aka_flg, tmp_hai_chr);

	// �o�b�t�@�N���A
	memset(gui->snd_mes, 0, sizeof(gui->snd_mes));

	// send���b�Z�[�W�ݒ�
	if( tsumogiri_flg == true ){
		// �A�N�V�����F���̐؂�
		wsprintf(gui->snd_mes, "{\"type\":\"dahai\",\"actor\":%d,\"pai\":\"%s\",\"tsumogiri\":true}\n", ply_mjai_id, tmp_hai_chr);
	}else{
		// �A�N�V�����F�̔v����
		wsprintf(gui->snd_mes, "{\"type\":\"dahai\",\"actor\":%d,\"pai\":\"%s\",\"tsumogiri\":false}\n", ply_mjai_id, tmp_hai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���[�`�̃��b�Z�[�W��`
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndRiichiMes(MJSGui *gui, int ply_mjai_id){

	// �o�b�t�@�N���A
	memset(gui->snd_mes, 0, sizeof(gui->snd_mes));

	// send���b�Z�[�W�ݒ�@�A�N�V�����F���[�`
	wsprintf(gui->snd_mes, "{\"type\":\"reach\",\"actor\":%d}\n", ply_mjai_id);

}

/* ---------------------------------------------------------------------------------------------- */
// �Þȃ��b�Z�[�W��`
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndAnkanMes(MJSGui *gui, int ply_mjai_id, int ankan_hai, int tehai_aka_count){

	// �ϐ���`
	char tmp_ankan_hai_chr[5];

	// Mes�擾�����F�����擾(���v)
	Get_haichr(ankan_hai, false, tmp_ankan_hai_chr);

	// send���b�Z�[�W�ݒ�
	if( tehai_aka_count == 0 ){
		// �Ԕv�Ȃ�
		wsprintf(gui->snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%s\",\"%s\",\"%s\"]}\n",     ply_mjai_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 1 ){
		// �Ԕv1��
		wsprintf(gui->snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%s\",\"%s\",\"%sr\"]}\n",    ply_mjai_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 2 ){
		// �Ԕv2��
		wsprintf(gui->snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%s\",\"%sr\",\"%sr\"]}\n",   ply_mjai_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 3 ){
		// �Ԕv3��
		wsprintf(gui->snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%s\",\"%sr\",\"%sr\",\"%sr\"]}\n",  ply_mjai_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}else if( tehai_aka_count == 4 ){
		// �Ԕv4��
		wsprintf(gui->snd_mes, "{\"type\":\"ankan\",\"actor\":%d,\"consumed\":[\"%sr\",\"%sr\",\"%sr\",\"%sr\"]}\n", ply_mjai_id, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr, tmp_ankan_hai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ���ȃ��b�Z�[�W��`
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndkakanMes(MJSGui *gui, int ply_mjai_id, int naki_hai, bool naki_aka, int tehai_aka_count){

	// �ϐ���`
	char tmp_kakan_hai_chr[5];

	// Mes�擾�����F�����擾(���v)
	Get_haichr(naki_hai, false, tmp_kakan_hai_chr);

	// send���b�Z�[�W�ݒ�
	if( naki_aka == true ){

		// Act�v���Ԕv
		if( tehai_aka_count == 0 ){
			// �Ԕv�Ȃ�
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%s\",\"%s\",\"%s\"]}\n",    ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 1 ){
			// �Ԕv3��
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%s\",\"%s\",\"%sr\"]}\n",   ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 2 ){
			// �Ԕv3��
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%s\",\"%sr\",\"%sr\"]}\n",  ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 3 ){
			// �Ԕv3��
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%sr\",\"consumed\":[\"%sr\",\"%sr\",\"%sr\"]}\n", ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}

	}else{

		// Act�v�����v
		if( tehai_aka_count == 0 ){
			// �Ԕv�Ȃ�
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\",\"%s\"]}\n",     ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 1 ){
			// �Ԕv3��
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\",\"%sr\"]}\n",    ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 2 ){
			// �Ԕv3��
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%sr\",\"%sr\"]}\n",   ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}else if( tehai_aka_count == 3 ){
			// �Ԕv3��
			wsprintf(gui->snd_mes, "{\"type\":\"kakan\",\"actor\":%d,\"pai\":\"%s\",\"consumed\":[\"%sr\",\"%sr\",\"%sr\"]}\n",  ply_mjai_id, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr, tmp_kakan_hai_chr);
		}

	}

}

/* ---------------------------------------------------------------------------------------------- */
// �a��(�����E�c��)���b�Z�[�W��`
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndHoraMes(MJSGui *gui, int ply_mjai_id, int ply_target, int agari_hai, bool agari_aka){

	// �ϐ���`
	char tmp_hai_chr[5];

	// Mes�擾�����F�����擾
	Get_haichr(agari_hai, agari_aka, tmp_hai_chr);

	// �o�b�t�@�N���A
	memset(gui->snd_mes, 0, sizeof(gui->snd_mes));

	// send���b�Z�[�W�ݒ�
	wsprintf(gui->snd_mes, "{\"type\":\"hora\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\"}\n", ply_mjai_id, ply_target, tmp_hai_chr);

}

/* ---------------------------------------------------------------------------------------------- */
// �|�����b�Z�[�W��`
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndPonMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count){

	// �ϐ���`
	char tmp_naki_hai_chr[5];
	char tmp_tehai_chr[5];

	// Mes�擾�����F�����擾(���v)
	Get_haichr(nakl_hai, nakl_aka, tmp_naki_hai_chr);

	// Mes�擾�����F�����擾(��v)
	Get_haichr(nakl_hai, false, tmp_tehai_chr);

	// send���b�Z�[�W�ݒ�
	if( tehai_aka_count == 0 ){
		// �Ԕv�Ȃ�
		wsprintf(gui->snd_mes, "{\"type\":\"pon\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\"]}\n",   ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 1 ){
		// �Ԕv1��
		wsprintf(gui->snd_mes, "{\"type\":\"pon\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%sr\"]}\n",  ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 2 ){
		// �Ԕv2��
		wsprintf(gui->snd_mes, "{\"type\":\"pon\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%sr\",\"%sr\"]}\n", ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �`�[���b�Z�[�W��`
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndChiMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int naki_idx, int tehai_aka_count){

	// �ϐ���`
	char tmp_hai_chr[5];
	int tmp_chi_count = 0;

	// �o�b�t�@�N���A
	// memset(gui->snd_mes, 0, sizeof(gui->snd_mes));

	// send���b�Z�[�W�ݒ�(�f�o�O�p)
	// wsprintf(gui->snd_mes, "{\"type\":\"chi\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\"}\n", ply_mjai_id, ply_target, tmp_hai_chr);

	// Mes�擾�����F�����擾(���v)
	Get_haichr(nakl_hai, nakl_aka, tmp_hai_chr);

	// ���b�Z�[�W�ݒ�(�w�b�_�[)
	wsprintf(gui->snd_mes, "{\"type\":\"chi\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[", ply_mjai_id, ply_target, tmp_hai_chr);

	// �`�[�v�ݒ�
	for(int tmp_i=0; tmp_i < 3; tmp_i++){

		// ���v�łȂ��Ȃ�
		if( nakl_hai != naki_idx + tmp_i ){
			// �`�[�̉�����
			tmp_chi_count++;
			// Mes�擾�����F�����擾(�Ԕv�m�F)
			if(( naki_idx + tmp_i == MAN5NUM || 
		         naki_idx + tmp_i == PIN5NUM || 
		         naki_idx + tmp_i == SOU5NUM )&& (tehai_aka_count > 0)){
				Get_haichr(naki_idx + tmp_i, true, tmp_hai_chr);
			}else{
				Get_haichr(naki_idx + tmp_i, false, tmp_hai_chr);
			}
			// �����b�Z�[�W�쐬
			wsprintf(gui->snd_mes, "%s\"%s\"", gui->snd_mes, tmp_hai_chr);
			// �Ō�łȂ��Ȃ�A�J���}�ǉ�
			if(tmp_chi_count != 2){
				wsprintf(gui->snd_mes, "%s,", gui->snd_mes);
			}
		}
	}

	// ���b�Z�[�W�ݒ�(�t�b�^�[)
	wsprintf(gui->snd_mes, "%s]}\n", gui->snd_mes);

}

/* ---------------------------------------------------------------------------------------------- */
// �~���J�����b�Z�[�W��`
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndMinkanMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count){

	// �ϐ���`
	char tmp_naki_hai_chr[5];
	char tmp_tehai_chr[5];

	// Mes�擾�����F�����擾(���v)
	Get_haichr(nakl_hai, nakl_aka, tmp_naki_hai_chr);

	// Mes�擾�����F�����擾(��v)
	Get_haichr(nakl_hai, false, tmp_tehai_chr);

	// send���b�Z�[�W�ݒ�
	if( tehai_aka_count == 0 ){
		// �Ԕv�Ȃ�
		wsprintf(gui->snd_mes, "{\"type\":\"daiminkan\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\",\"%s\"]}\n",   ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 1 ){
		// �Ԕv1��
		wsprintf(gui->snd_mes, "{\"type\":\"daiminkan\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%s\",\"%sr\"]}\n",  ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 2 ){
		// �Ԕv1��
		wsprintf(gui->snd_mes, "{\"type\":\"daiminkan\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%s\",\"%sr\",\"%sr\"]}\n",  ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}else if( tehai_aka_count == 3 ){
		// �Ԕv2��
		wsprintf(gui->snd_mes, "{\"type\":\"daiminkan\",\"actor\":%d,\"target\":%d,\"pai\":\"%s\",\"consumed\":[\"%sr\",\"%sr\",\"%sr\"]}\n", ply_mjai_id, ply_target, tmp_naki_hai_chr, tmp_tehai_chr, tmp_tehai_chr, tmp_tehai_chr);
	}

}

/* ---------------------------------------------------------------------------------------------- */
// �����Ȃ����b�Z�[�W��`
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::ActSndNoneMes(MJSGui *gui){

	// send���b�Z�[�W�ݒ�
	wsprintf(gui->snd_mes, res_none);

}

/* ---------------------------------------------------------------------------------------------- */
// �v�ԍ��擾
/* ---------------------------------------------------------------------------------------------- */
int MJSMjaiClient::Get_hainum(char hai_str[]){

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

/* ---------------------------------------------------------------------------------------------- */
// �v�����擾
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Get_haichr(int hai_num, bool hai_aka, char hai_str[]){

	// ���v����
	if(hai_num > 30){

		if(hai_num == 31){
			wsprintf(hai_str, "E");
		}else if(hai_num == 32){
			wsprintf(hai_str, "S");
		}else if(hai_num == 33){
			wsprintf(hai_str, "W");
		}else if(hai_num == 34){
			wsprintf(hai_str, "N");
		}else if(hai_num == 35){
			wsprintf(hai_str, "P");
		}else if(hai_num == 36){
			wsprintf(hai_str, "F");
		}else if(hai_num == 37){
			wsprintf(hai_str, "C");
		}else{
			wsprintf(hai_str, "-");
		}

	}else if (hai_num > 0 && hai_num < 10){
		if(hai_aka==true){
			wsprintf(hai_str, "%dmr", hai_num%10);
		}else{
			wsprintf(hai_str, "%dm" , hai_num%10);
		}
	}else if (hai_num > 10 && hai_num < 20){
		if(hai_aka==true){
			wsprintf(hai_str, "%dpr", hai_num%10);
		}else{
			wsprintf(hai_str, "%dp" , hai_num%10);
		}
	}else if (hai_num > 20 && hai_num < 30){
		if(hai_aka==true){
			wsprintf(hai_str, "%dsr", hai_num%10);
		}else{
			wsprintf(hai_str, "%ds" , hai_num%10);
		}
	}

}

/* ---------------------------------------------------------------------------------------------- */
// ��A�N�V�����̃��O�o��
/* ---------------------------------------------------------------------------------------------- */
void MJSMjaiClient::Output_Actionlog(MJSTkinfo *tk, int kyoku_index){

		// �w�b�_�[�\��
		wsprintf(clientlog_buf, "ACT_ID:%d", tk->kyoku[kyoku_index].act_count);

		// �A�N�V�����\��
		if ( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYNOACT){
			wsprintf(clientlog_buf, "%s ��`�Ȃ�", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == HAIPAI){
			wsprintf(clientlog_buf, "%s �z�v�@�@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTTSUMO){
			wsprintf(clientlog_buf, "%s ���́@�@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYRINSHAN){
			wsprintf(clientlog_buf, "%s ��㎩��", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTSUTE){
			wsprintf(clientlog_buf, "%s �̔v�@�@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTTSUMOGIRI){
			wsprintf(clientlog_buf, "%s ���̐؂�", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTPON){
			wsprintf(clientlog_buf, "%s �|���@�@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTANKAN){
			wsprintf(clientlog_buf, "%s �Þȁ@�@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTMINKAN){
			wsprintf(clientlog_buf, "%s ���ȁ@�@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTKAKAN){
			wsprintf(clientlog_buf, "%s ���ȁ@�@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTCHI){
			wsprintf(clientlog_buf, "%s �`�[�@�@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTRIICH){
			wsprintf(clientlog_buf, "%s ���[�`�@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYTSUMOAGARI){
			wsprintf(clientlog_buf, "%s ���̘a��", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == PLYACTRON){
			wsprintf(clientlog_buf, "%s �����a��", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == RYUKYOKU){
			wsprintf(clientlog_buf, "%s ���ǁ@�@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == KYOKURESULT){
			wsprintf(clientlog_buf, "%s �ǌ��ʁ@", clientlog_buf);
		}else if( tk->kyoku[kyoku_index].act_stat[tk->kyoku[kyoku_index].act_count] == KYOKUEND){
			wsprintf(clientlog_buf, "%s �ǏI���@", clientlog_buf);
		}else{
			wsprintf(clientlog_buf, "%s �s���@�@", clientlog_buf);
		}

		// Ply���E�v���̒ǋL
		wsprintf(clientlog_buf, "%s �v�ԍ��G%d ACT�v���[���[�F%d ��ACT�v���[���[�F%d\n", 
		clientlog_buf,
		tk->kyoku[kyoku_index].act_hai  [tk->kyoku[kyoku_index].act_count],
		tk->kyoku[kyoku_index].act_ply  [tk->kyoku[kyoku_index].act_count], 
		tk->kyoku[kyoku_index].react_ply[tk->kyoku[kyoku_index].act_count]);

		// ���O�o��
		clientlog->CorelogPrint(clientlog_buf);

		// �d�؂��
		wsprintf(clientlog_buf, "----\n");
		clientlog->CorelogPrint(clientlog_buf);

}

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
