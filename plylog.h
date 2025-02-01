/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(Ver0.1.2�F���O�r���A�[������)
 * �o�[�W����     �F 0.1.2.12(�������E���[�`����)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F plylog.h 
 * �N���X��       �F MJSPlylog
 * �����T�v       �F Ply���O����
 * Ver0.0.1�쐬�� �F 2010/10/03 00:00:00
 * Ver0.0.8�쐬�� �F 2011/11/26 17:31:00
 * Ver0.1.2�쐬�� �F 2022/10/23 23:38:32
 * �ŏI�X�V��     �F 2022/10/31 22:29:08
 * 
 * Copyright (c) 2010-2022 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#ifndef PLYLOG_H_INCLUDED
#define PLYLOG_H_INCLUDED

#include "corelog.h"

/* --------------------------------------------------------------- */
// �ϐ���`
/* --------------------------------------------------------------- */

class MJSPlylog
{

	/* ----------------------------- */
	// ���J�֐���` 
	/* ----------------------------- */

	// ���J�֐���`
	public:

	// �ʃ��O�o��
	MJSCorelog corelog;

	// ���O��
	char *logname;

	// ���O�o�̓��x��
	int loglevel;

	/* ----------------------------- */
	// �֐���`
	/* ----------------------------- */

	// �R���X�g���N�^��`
    MJSPlylog(){};

	// �f�X�g���N�^��`
    ~MJSPlylog(){};

	/* ----------------------------- */
	// Player�N���X�����֐�
	/* ----------------------------- */

	// �N���X�������E�㏈��
	void PlylogInit();                                    // ���_�v�Z�N���X�̏�����
	void PlylogPost();                                    // ���_�v�Z�N���X�̏I������

	// ��J�n�E�I��
	void PlylogTakuStart(MJSTkinfo *tk);
	void PlylogTakuEnd(MJSTkinfo *tk);

	// �ǊJ�n�E�I��
	void PlylogKyokuStart(MJSTkinfo *tk);
	void PlylogKyokuEnd(MJSTkinfo *tk);

	// �z�v����
	void PlylogAllHaipai(MJSTkinfo *tk);
	void PlylogHaipai(MJSTkinfo *tk,int pnum);

	// ���̏���
	void PlylogTsumoHai(MJSTkinfo *tk,int pnum);

	// ���̎̔v����
	void PlylogTsumoSute(MJSTkinfo *tk,int pnum);
	void PlylogAllTsumoSute(MJSTkinfo *tk);
	void PlylogSute(MJSTkinfo *tk,int pnum);

	// �v���[���[���
	void PlylogPlayer(MJSTkinfo *tk, int pnum);
	void PlylogDisplayPlyinfo(MJSTkinfo *tk);

	// ��
	void PlylogOtherNaki(MJSTkinfo *tk);
	void PlylogDisplayPlyNaki(MJSTkinfo *tk);

	// ���A�N�V�����\��
	void PlylogOwnReact(MJSTkinfo *tk);

	// �S���̃��A�N�V�������ʂ̕\��
	void PlylogAllReact(MJSTkinfo *tk);

	// �a���A�N�V�����\��
	void PlylogAgari(MJSTkinfo *tk,int pnum);

	// �a�����ʏo��
	void PlylogDisplayPlyAgari(MJSTkinfo *tk);
	void PlylogNormalYaku(MJSTkinfo *tk);
	void PlylogYakuman(MJSTkinfo *tk);

	// ����
	void PlylogRyukyoku(MJSTkinfo *tk);
	void PlylogyHaigire(MJSTkinfo *tk);

	/* ----------------------------- */
	// AI�����֐�
	/* ----------------------------- */
	// PlaeyAI�ڍ׏��
	void PlylogDisplayPlyAIinfo(MJSTkinfo *tk, MJSPlyAI *ai);

};

#endif/* PLYLOG_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- */
// �\�[�X�I��
/* ---------------------------------------------------------------------------------------------- */
