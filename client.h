/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.0.206(�J�����g�p�X�̎擾)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F client.h
 * �N���X��       �F MJSMjaiClient
 * �����T�v       �F Mjai�N���C�A���g�����N���X
 * Ver0.1.2�쐬�� �F 2023/11/19 21:38:17
 * �ŏI�X�V��     �F 2024/10/12 15:21:12
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <windows.h>
#include "stdafx.h"

#include "tkinfo.h"
#include "corelog.h"
#include "player.h"
#include "socket.h"
#include "readmjai.h"


/* ---------------------------------------------------------------------------------------------- */
// �N���X��`
/* ---------------------------------------------------------------------------------------------- */
class MJSMjaiClient
{

	// -----------------------------
	// ���J�֐���`
	// -----------------------------
	public:

	// �N���X��`
	MJSCorelog  *clientlog;   // �R�A���O�����N���X
	MJSSocket sock;           // Socket�N���X
	MJSReadMjai *mjai;        // MJAI���O�Ǎ��݃N���X

	// �Œ胁�b�Z�[�W
	const char* res_join = "{\"type\":\"join\",\"name\":\"tampopo\",\"room\":\"default\"}\n";
	const char* res_none = "{\"type\":\"none\"}\n";

	// Socket�f�o�O���O
	// char clientlog_name[50];       // ���O�t�@�C����
	char clientlog_buf[1024];      // ���O�o�b�t�@

	// -----------------------------
	// �R���X�g���N�^
	// -----------------------------

	// �R���X�g���N�^��`
	MJSMjaiClient() {};

	// �f�X�g���N�^��`
	~MJSMjaiClient() {};

	// -----------------------------
	// �֐���`
	// -----------------------------

	// �N���C�A���g�N���X�������E�I������
	void ClientInit(MJSTkinfo *tk, MJSGui *gui, MJSReadMjai *tmp_mjai);    // Mjai�N���C�A���g�̏����J�n
	void ClientPost(MJSGui *gui);                                          // Mjai�N���C�A���g�̏����I��

	// Socket�ʐM
	void ClientResponseMes(MJSGui *gui);     // ��M����
	void ClientSendMes(MJSGui *gui);         // ���M����

	// �V�X�e���֘A����
	void SetNowTime(MJSTkinfo *tk);          // ���ݓ����̎擾

	// -----------------------------
	// ���C������
	// -----------------------------
	void CheckTakuStatus(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, bool tmp_push_flg);

	// -----------------------------
	// ��M����
	// -----------------------------

	// MJAI���b�Z�[�W��M(���C������)
	void ChkResMesMain(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);

	// type���Ƃł̑�X�e�[��ݒ�(MJAI���b�Z�[�W��M�E�T�u����)
	void Set_possible_actions(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);                          // possible_actions���b�Z�[�W�m�F
	void Set_type_hello(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);                                // hello���b�Z�[�W�m�F
	void Set_type_startgame(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);            // ��Q�[���J�n����
	void Set_type_startkyoku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);           // �ǊJ�n����
	void Set_type_tsumo(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                // ���̏���
	void Set_type_dahai(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                // �̔v����
	void Set_type_riichi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);               // ���[�`����
	void Set_type_ankan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                // �Þȏ���
	void Set_type_kakan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                // ���ȏ���
	void Set_type_pon(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                  // �|������
	void Set_type_chi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                  // �`�[����
	void Set_type_minkan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);               // ���ȏ���
	void Set_type_reach_accepted(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);       // ���[�`�󂯓���m�F
	void Set_type_hora(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);                 // �a���m�F
	void Set_type_hora_yaku_check(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_yaku_num);    // ���m�F�����p�̃T�u�֐�
	void Set_type_ryukyoku(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui, int tmp_wk_num);             // ����
	void Set_type_endkyoku(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);                             // �ǏI��
	void Set_type_endgame(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);                              // ��Q�[���I��
	void Set_type_error(MJSTkinfo *tk, MJSGui *gui, int tmp_wk_num);                                // error���b�Z�[�W��M��
	void Set_type_others(MJSTkinfo *tk, MJSGui *gui);                                               // ��O����

	// -----------------------------
	// �A�N�V��������E���M����
	// -----------------------------

	void SetActTsumo(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                   // ���̃A�N�V��������
	void SetActSute(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                    // �̔v�A�N�V��������
	void SetActTsumogiri(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                               // ���̐؂�A�N�V��������
	void SetActRiichi(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                  // ���[�`�A�N�V��������
	void SetActkan(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                     // �ÞȃA�N�V��������
	void SetActNaki(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                    // ���A�N�V����(�`�[�E�|��)����
	void SetActNakiSute(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                                // ���̔v����
	void SetActNakiSuteSub(MJSTkinfo *tk, MJSPlayer *ply, MJSGui *gui);                             // ���̔v����(�T�u����)

	// -----------------------------
	// MJAI���b�Z�[�W���M
	// -----------------------------

	void ActSndJoinMes(MJSGui *gui);                                                                                                  // �W���C�����b�Z�[�W
	void ActSndDahaiMes(MJSGui *gui, int ply_mjai_id, int hai, bool aka_flg, bool tsumogiri_flg);                                     // �̔v���b�Z�[�W
	void ActSndRiichiMes(MJSGui *gui, int ply_mjai_id);                                                                               // ���[�`���b�Z�[�W
	void ActSndAnkanMes(MJSGui *gui, int ply_mjai_id, int ankan_hai, int tehai_aka_count);                                            // �Þȃ��b�Z�[�W
	void ActSndkakanMes(MJSGui *gui, int ply_mjai_id, int nakl_hai, bool naki_aka, int tehai_aka_count);                              // ���ȃ��b�Z�[�W
	void ActSndPonMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count);                // �|�����b�Z�[�W
	void ActSndChiMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int naki_idx, int tehai_aka_count);  // �`�[���b�Z�[�W
	void ActSndMinkanMes(MJSGui *gui, int ply_mjai_id, int ply_target, int nakl_hai, bool nakl_aka, int tehai_aka_count);             // ���ȃ��b�Z�[�W
	void ActSndHoraMes(MJSGui *gui, int ply_mjai_id, int ply_target, int agari_hai, bool agari_aka);                                  // �a��(�����E�c��)���b�Z�[�W
	void ActSndNoneMes(MJSGui *gui);                                                                                                  // �������b�Z�[�W

	// -----------------------------
	// �T�u�֐�
	// -----------------------------
	int  Get_hainum(char hai_str[]);                                  // �v�ԍ��擾
	void Get_haichr(int hai_num, bool hai_aka, char hai_str[]);       // Mjai�����v�����擾
	void Set_uradora(MJSTkinfo *tk, int hai_num, bool hai_aka);       // ���h���擾

	// �f�o�O�p
	void Output_Actionlog(MJSTkinfo *tk, int kyoku_index);            // ��A�N�V�����̃��O�o��

};

#endif/* CLIENT_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- 
 * �\�[�X�I��
 * ---------------------------------------------------------------------------------------------- */
