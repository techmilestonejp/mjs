/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F �����疃��(Ver0.1.2�F�J����)
 * �o�[�W����     �F 0.1.2.1.225(MJAI���O�\���F3�v���[�����̖����\���̒�`)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F tklog.cpp
 * �N���X��       �F MJSTklog
 * �����T�v       �F ���񃍃O�N���X
 * �쐬��         �F 2018/11/18 10:12:12
 * Ver0.0.1�쐬�� �F 2022/04/11 15:57:39
 * Ver0.1.2�쐬�� �F 2022/08/31 22:19:54
 * �ŏI�X�V��     �F 2024/11/07 19:11:07
 * 
 * Copyright (c) 2010-2024 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#include "tklog.h"

/* ---------------------------------------------------------------------------------------------- */
// ���O�����J�n����
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_init(char *logname){

	// �N���X��`
	core_log = new MJSCorelog;         // �R�A���O�N���X�̏�����

	// �R�A���O������
	core_log->CorelogInit(logname);

	// �t�@�C��������
	tklog_file_init(logname);

}

/* ---------------------------------------------------------------------------------------------- */
// ���O�����I������
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_post(){

	// �R�A���O�㏈��
	core_log->CorelogPost();

	// �N���X�폜
	delete core_log;

	// �t�@�C���N���[�Y
	tklog_file_close();

}

/* ---------------------------------------------------------------------------------------------- */
// �t�@�C��������
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_file_init(char *logname){

	// �t�@�C���|�C���g��`
	hFile = CreateFile( logname, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// �����m�F
	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, "�t�@�C���Ǎ��G���[�ł�", "���b�Z�[�W", MB_OK);
	}

	// �|�C���^����ԍŌ�ɂ��ĒǋL��������
	SetFilePointer( hFile, 0, NULL, FILE_END );

}

/* ---------------------------------------------------------------------------------------------- */
// �t�@�C���N���[�Y
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_file_close(){

	// �t�@�C���N���[�Y
	CloseHandle(hFile);

}

/* ---------------------------------------------------------------------------------------------- */
// ���O�o�́E���C������
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_print(char *msg){

	// �������ݏ����J�n
	WriteFile(hFile, msg, (DWORD)strlen(msg), &dwBytes, NULL);

}

/* ---------------------------------------------------------------------------------------------- */
// �󔒏o��
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_space(){

	wsprintf(tmp_msg, "�@");
	tklog_print(tmp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// ���s�o��
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_cr(){

	wsprintf(tmp_msg, "\n");
	tklog_print(tmp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// ���ԏo��
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_time(){

	// �֐���` 

    time_t jikan = time(NULL);
    struct tm imanojikan;
	errno_t error;

	int year, mon, day;
	int hour, min, sec;

	// ���݂̓������擾 
	error = localtime_s(&imanojikan, &jikan);

	year = imanojikan.tm_year + 1900;
	mon  = imanojikan.tm_mon  + 1;
	day  = imanojikan.tm_mday ;

	hour = imanojikan.tm_hour;
	min  = imanojikan.tm_min;
	sec  = imanojikan.tm_sec;

	wsprintf(tmp_msg,"%d/%02d/%02d %02d:%02d:%02d",year,mon,day,hour,min,sec);
	tklog_print(tmp_msg);

}

/* ---------------------------------------------------------------------------------------------- */
// MJS���O�o�́E���C������
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_print(MJSTkinfo *tk, int log_ver1, int log_ver2, int log_ver3, int log_ver4){

	// ���O�J�n����
	tklog_000_MJSlogStart(log_ver1, log_ver2,log_ver3,log_ver4); // 000�FMJS���O�J�n

	// ��J�n����
	tklog_011_TakuStart(tk);                                     // 011�F��J�n���
	tklog_012_PlayerInfo(tk);                                    // 012�F�v���[���[���

	// �Ǐ��
	for (int tmp_i = 0; tmp_i < tk->kyoku_index+1; tmp_i++){
		tklog_101_KyokuStart(tk, tmp_i);                         // 101�F�ǊJ�n
		tklog_11x_HaipaiInfo(tk, tmp_i);                         // 11x�F�z�v
		tklog_201_Actinfo(tk, tmp_i);                            // 201�F�A�N�V�������
		tklog_21x_Nakiinfo(tk, tmp_i);                           // 21x�F�����
		tklog_901_AgariInfo(tk, tmp_i);
		tklog_902_YakuInfo(tk, tmp_i);
		tklog_903_kyokuScore(tk, tmp_i);
	}

	// ��I������
	tklog_911_TakuEndScore(tk);                                  // 911�F���_����
	tklog_919_TakuEnd(tk);                                       // 919�F��I�����

	// ���O�I������
	tklog_999_MJSlogEnd(log_ver1, log_ver2,log_ver3,log_ver4);   // 999�FMJS���O�I��
	
	// ���s(���O�I���m�F�p�̋󔒍s)
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 000�FMJS���O�J�n
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_000_MJSlogStart(int log_ver1, int log_ver2, int log_ver3, int log_ver4){

	// ���O�o��
	wsprintf(tmp_msg, "000 MJSlog START %d %d %d %d ", log_ver1, log_ver2, log_ver3, log_ver4);
	tklog_print(tmp_msg);

	// �����\��
	tklog_time();

	// ���s
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 999�FMJS���O�I��
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_999_MJSlogEnd(int log_ver1, int log_ver2, int log_ver3, int log_ver4){

	// ���O�o��
	wsprintf(tmp_msg, "999 MJSlog END %d %d %d %d ", log_ver1, log_ver2, log_ver3, log_ver4);
	tklog_print(tmp_msg);

	// �����\��
	tklog_time();

	// ���s
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 011�F��J�n
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_011_TakuStart(MJSTkinfo *tk){

	// ���O�o��
	wsprintf(tmp_msg, "011 %s %s %s %s %s", tk->tkgname, tk->tkname, tk->tkno, tk->startdate, tk->starttime);
	tklog_print(tmp_msg);

	// �����\��
	// tklog_time();

	// ���s
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 012�F�v���[���[���
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_012_PlayerInfo(MJSTkinfo *tk){

	// ���O�o��
	wsprintf(tmp_msg, "012 %d 0 %s R1500 1 %s R1500 2 %s R1500 3 %s R1500", tk->init_score, tk->plyname[0], tk->plyname[1], tk->plyname[2], tk->plyname[3]);
	tklog_print(tmp_msg);

	// ���s
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 101�F�ǊJ�n
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_101_KyokuStart(MJSTkinfo *tk, int kyoku_index){

	// ���O�o��
	wsprintf(tmp_msg, "101 %d %d %d %d ", kyoku_index, tk->kyoku[kyoku_index].kyoku ,tk->kyoku[kyoku_index].tsumibo , tk->kyoku[kyoku_index].riichbo);
	tklog_print(tmp_msg);

	// ���s
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 11x�F�z�v���
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_11x_HaipaiInfo(MJSTkinfo *tk, int kyoku_index){

	// �z�v�\��
	for (int tmp_ply_num = 0; tmp_ply_num < PLAYER_MAX; tmp_ply_num++){

		// �w�b�_�[�\��
		wsprintf(tmp_msg, "11%d", tmp_ply_num+1);

		// �v��`
		for (int tmp_i = 0; tmp_i < PAI_MAX; tmp_i++){
			for (int tmp_j = 0; tmp_j < tk->kyoku[kyoku_index].tehai[tmp_ply_num][tmp_i]; tmp_j++){
				// �v��`
				wsprintf(tmp_msg, "%s %d", tmp_msg, tmp_i);
			}
		}

		// ���O�o��
		tklog_print(tmp_msg);
		tklog_cr();

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 201�F�A�N�V�������
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_201_Actinfo(MJSTkinfo *tk, int kyoku_index){

	// act_count�̎d�l�𗝗R�Ƃ��Ēl�����Z����
	// tk->kyoku[kyoku_index].act_count++;

	// �A�N�V�������̃��O�o��
	for (int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].act_count; tmp_i++){

		// �w�b�_�[�\��
		wsprintf(tmp_msg, "201 %d", tmp_i);

		// �A�N�V�����\��
		if ( tk->kyoku[kyoku_index].act_stat[tmp_i] == HAIPAI){
			wsprintf(tmp_msg, "%s �z�v�@�@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTTSUMO){
			wsprintf(tmp_msg, "%s ���́@�@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTSUTE){
			wsprintf(tmp_msg, "%s �̔v�@�@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTTSUMOGIRI){
			wsprintf(tmp_msg, "%s ���̐؂�", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTPON){
			wsprintf(tmp_msg, "%s �|���@�@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTANKAN){
			wsprintf(tmp_msg, "%s �Þȁ@�@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTMINKAN){
			wsprintf(tmp_msg, "%s ���ȁ@�@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTKAKAN){
			wsprintf(tmp_msg, "%s ���ȁ@�@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTCHI){
			wsprintf(tmp_msg, "%s �`�[�@�@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTRIICH){
			wsprintf(tmp_msg, "%s ���[�`�@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYTSUMOAGARI){
			wsprintf(tmp_msg, "%s ���̘a��", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == PLYACTRON){
			wsprintf(tmp_msg, "%s �����a��", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == RYUKYOKU){
			wsprintf(tmp_msg, "%s ���ǁ@�@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == KYOKURESULT){
			wsprintf(tmp_msg, "%s �ǌ��ʁ@", tmp_msg);
		}else if( tk->kyoku[kyoku_index].act_stat[tmp_i] == KYOKUEND){
			wsprintf(tmp_msg, "%s �ǏI���@", tmp_msg);
		}else{
			wsprintf(tmp_msg, "%s �s���@�@", tmp_msg);
		}

		// Ply���E�v���̒ǋL
		wsprintf(tmp_msg, "%s %d %d %d", tmp_msg, tk->kyoku[kyoku_index].act_ply[tmp_i], tk->kyoku[kyoku_index].react_ply[tmp_i], tk->kyoku[kyoku_index].act_hai[tmp_i]);

		// ���O�o��
		tklog_print(tmp_msg);
		tklog_cr();

	}

}

/* ---------------------------------------------------------------------------------------------- */
// 21x�F�����
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_21x_Nakiinfo(MJSTkinfo *tk, int kyoku_index){

	// ���\��
	for (int tmp_ply_num = 0; tmp_ply_num < PLAYER_MAX; tmp_ply_num++){

		// �������̊m�F
		if(tk->kyoku[kyoku_index].naki_count[tmp_ply_num] == 0){

			// 0���\��
			wsprintf(tmp_msg, "21%d 0 ���� 0 0 0 0", tmp_ply_num+1);

			// ���O�o��
			tklog_print(tmp_msg);
			tklog_cr();

		}else{

			// �����\��
			for (int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].naki_count[tmp_ply_num]; tmp_i++){

				// �w�b�_�[�\��
				wsprintf(tmp_msg, "21%d %d", tmp_ply_num, tmp_i);

				// �����c���
				if ( tk->kyoku[kyoku_index]. naki_stat[tmp_ply_num][tmp_i] == MINSHUN){
					wsprintf(tmp_msg, "%s ����", tmp_msg);
				}else if( tk->kyoku[kyoku_index]. naki_stat[tmp_ply_num][tmp_i] == MINKO){
					wsprintf(tmp_msg, "%s ����", tmp_msg);
				}else if( tk->kyoku[kyoku_index]. naki_stat[tmp_ply_num][tmp_i] == ANKAN){
					wsprintf(tmp_msg, "%s �Þ�", tmp_msg);
				}else if( tk->kyoku[kyoku_index]. naki_stat[tmp_ply_num][tmp_i] == MINKAN){
					wsprintf(tmp_msg, "%s ����", tmp_msg);
				}else if( tk->kyoku[kyoku_index]. naki_stat[tmp_ply_num][tmp_i] == KAKAN){
					wsprintf(tmp_msg, "%s ����", tmp_msg);
				}else{
					wsprintf(tmp_msg, "%s �s���@�@", tmp_msg);
				}

				// �v���
				wsprintf(tmp_msg, "%s %d %d %d %d", tmp_msg, tk->kyoku[kyoku_index].naki_actid[tmp_ply_num][tmp_i], tk->kyoku[kyoku_index].naki_hai[tmp_ply_num][tmp_i], tk->kyoku[kyoku_index].naki_idx[tmp_ply_num][tmp_i], tk->kyoku[kyoku_index].naki_aka[tmp_ply_num][tmp_i]);

				// ���O�o��
				tklog_print(tmp_msg);
				tklog_cr();

			}

		}

	}

	// �������\��
	wsprintf(tmp_msg, "215 %d %d %d %d", tk->kyoku[kyoku_index].naki_count[0], tk->kyoku[kyoku_index].naki_count[1], tk->kyoku[kyoku_index].naki_count[2], tk->kyoku[kyoku_index].naki_count[3]);

	// ���O�o��
	tklog_print(tmp_msg);
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 901�F�a�����
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_901_AgariInfo(MJSTkinfo *tk, int kyoku_index){

}

/* ---------------------------------------------------------------------------------------------- */
// 902�F�����
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_902_YakuInfo(MJSTkinfo *tk, int kyoku_index){
/*
	// �Ǔ��_���
	for (int tmp_i = 0; tmp_i < tk->kyoku[kyoku_index].ply_agari_yk[tk->kyoku[kyoku_index].agari_ply_count].yakucount; tmp_i++){

		// ��\��
		wsprintf(tmp_msg, "902 %s", tk->kyoku[kyoku_index].yakuname[tmp_i]);

		// ���O�o��
		tklog_print(tmp_msg);
		tklog_cr();

	}
*/
}

/* ---------------------------------------------------------------------------------------------- */
// 903�F�ǂ̍��v���_
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_903_kyokuScore(MJSTkinfo *tk, int kyoku_index){

	// �w�b�_�[�\��
	wsprintf(tmp_msg, "903");

	// �Ǔ��_���
	for (int tmp_ply_num = 0; tmp_ply_num < PLAYER_MAX; tmp_ply_num++){
			wsprintf(tmp_msg, "%s %d %d", tmp_msg, tmp_ply_num, tk->kyoku[kyoku_index].ply_agari_yk[tk->kyoku[kyoku_index].agari_ply_count].kyoku_score[tmp_ply_num]);
	}

	// ���O�o��
	tklog_print(tmp_msg);
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 911�F���_����
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_911_TakuEndScore(MJSTkinfo *tk){

	// �w�b�_�[�\��
	wsprintf(tmp_msg, "911");

	// �Ǔ��_���
	for (int tmp_ply_num = 0; tmp_ply_num < PLAYER_MAX; tmp_ply_num++){
		wsprintf(tmp_msg, "%s %d %d", tmp_msg, tk->plyjun[tmp_ply_num], tk->plyEndscore[tmp_ply_num]);
	}

	// ���O�o��
	tklog_print(tmp_msg);
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// 919�F��I��
/* ---------------------------------------------------------------------------------------------- */
void MJSTklog::tklog_919_TakuEnd(MJSTkinfo *tk){

	// ���O�o��
	wsprintf(tmp_msg, "919 %s %s %s %s %s", tk->tkgname, tk->tkname, tk->tkno, tk->enddate, tk->endtime);
	tklog_print(tmp_msg);

	// �����\��
	// tklog_time();

	// ���s
	tklog_cr();

}

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
