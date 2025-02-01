/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F �����疃��(Ver0.1.2.1�F�J����)
 * �o�[�W����     �F 0.1.2.1.222(Main�N���X�̓���)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F main.h
 * �N���X��       �F MJSMain
 * �����T�v       �F ���C������
 * Ver0.0.8.0�쐬 �F 2012/07/29 11:09:51
 * Ver0.1.0.0�쐬 �F 2022/05/03 18:50:06
 * Ver0.1.1.0�쐬 �F 2022/06/30 21:19:01
 * Ver0.1.2.0�쐬 �F 2022/08/31 22:19:54
 * Ver0.1.2.1�쐬 �F 2024/10/30 16:40:44
 * �ŏI�X�V��     �F 2024/11/02 09:38:41
 * 
 * Copyright (c) 2010-2024 TechMileStoraJP, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#pragma once

#ifndef MJSMAIN_H_INCLUDED
#define MJSMAIN_H_INCLUDED

#include <windows.h>
#include "stdafx.h"
#include "DxLib.h"

#include "display.h"
#include "gui.h"

#include "taku.h"
#include "tkinfo.h"
#include "player.h"
#include "client.h"

#include "tklog.h"
#include "tpread.h"

/* ---------------------------------------------------------------------------------------------- */
// �N���X��`
/* ---------------------------------------------------------------------------------------------- */
class MJSMain
{

	// ------------------------------------------------------------------- 
	// �o�[�W�������
	// ------------------------------------------------------------------- 
	public:

	// �o�[�W�������
	int ver1;
	int ver2;
	int ver3;
	int ver4;
	int ver5;

	// �o�[�W�������(MJSlog)
	int log_ver1;
	int log_ver2;
	int log_ver3;
	int log_ver4;

	// ------------------------------------------------------------------- 
	// �t���[������
	// ------------------------------------------------------------------- 

	// �t���[�������p�萔
	int SAMPLE_FRAME_COUNT = 60;        // �t���[���̃T���v����
	int FPS                = 60;        // �z���FPS�l (�҂����Ԃ̎Z�o�p)

	// FPS�Z�o�p�ϐ�(�t���[����`)
	int frame_count;                    // �T���v���t���[���̃J�E���^��
	int total_frame_count;              // ���������t���[���̍��v��

	// FPS�Z�o�p�ϐ�(���Ԓ�`)
	int checkpoint_time;                // ��_����(�`�F�b�N�|�C���g���Ƃ̎���)
	int wait_time;                      // �҂�����(Sleep�֐��𗘗p���邽�߂ɒP�ʂ̓~���b)

	// FPS�Z�o�p�ϐ�(FPS��)
	float ave_fps;                      // ������FPS�l

	// ------------------------------------------------------------------- 
	// ���[�h��`
	// ------------------------------------------------------------------- 

	// �r���[�A�[���[�h�̗L��
	bool haifu_read_mode;

	// ------------------------------------------------------------------- 
	// �N���X��`
	// ------------------------------------------------------------------- 

	// �N���X��`
	MJSGui gui;                         // GUI����N���X(�}�E�X������)
	MJSTkinfo tk;                       // ����N���X
	MJSTaku taku;                       // ������Q�[�������N���X
	MJSPlayer* ply;                     // �v���[���[�N���X(�|�C���^��`)
	MJSDisplay dsp;                     // ��ʕ\�������N���X
	MJSMjaiClient cli;                  // MJAI�N���C�A���g�N���X
	MJSReadTplog tp;                    // ���������O�Ǎ��N���X
	MJSReadMjai  mjai;                  // MJAI���O�Ǎ��݃N���X
	MJSTklog log;                       // mjs��Q�[�����O�N���X

	/* ----------------------------- */
	// �R���X�g���N�^
	/* ----------------------------- */

	// �R���X�g���N�^��`
	MJSMain(){};

	// �f�X�g���N�^��`
	~MJSMain(){};

	/* ----------------------------- */
	// �֐���`
	/* ----------------------------- */

	// �S�̏���
	void MainInit();                    // �J�n����
	void MainExe();                     // ���s����
	void MainExe_ChkStat();             // ���s�������̃X�e�[�^�X�m�F
	void MainPost();                    // �I������

	// Fps�Z�o����
	void FpsParamInit();
	void FpsUpdate();
	void FpsWait();

	// ��X�e�[�^�X�̏������ƏI������
	void MainTakuInit();                // ���C���N���X����̑�Q�[���J�n����
	void MainTakuPost();                // ���C���N���X����̑�Q�[���I������

	// �I�[�v�j���O���
	void OpeningInit();
	void OpeningExe();
	void OpeningPost();

	// �Q�[�����[�h
	void PlayingInit();
	void PlayingExe();
	void PlayingPost();

	// �r���[�A�[���[�h
	void ViewingInit();
	void ViewingExe();
	void ViewingPost();

	// ���؃��[�h
	void RunningInit();
	void RunningExec();
	void RunningPost();

	// Mjai�N���C�A���g���[�h
	void ClientInit();
	void ClientExec();
	void ClientPost();

	// Mjai�T�[�o���[�h
	void MJServerInit();
	void MJServerExe();
	void MJServerPost();

	// �ݒ���
	void SettingInit();
	void SettingExe();
	void SettingPost();

};

#endif/* MJSMAIN_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
