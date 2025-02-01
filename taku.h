/* ---------------------------------------------------------------------------------------------- 
 * 
 * �v���O�����T�v �F New�����疃��(MJAI�N���C�A���g������)
 * �o�[�W����     �F 0.1.2.0.168(�L���v���[�g����)
 * �v���O������   �F mjs.exe
 * �t�@�C����     �F taku.h
 * �N���X��       �F MJSTaku
 * �����T�v       �F ������Q�[�������N���X
 * Ver0.0.8�쐬�� �F 2011/11/23 21:26:17
 * Ver0.0.8�X�V�� �F 2012/05/04 08:58:06
 * Ver0.1.0�쐬�� �F 2022/06/04 10:13:26
 * Ver0.1.1�쐬�� �F 2022/06/30 21:19:01
 * Ver0.1.2�쐬�� �F 2022/08/31 22:19:54
 * �ŏI�X�V��     �F 2024/05/25 09:28:29
 * 
 * Copyright (c) 2010-2024 Techmilestone, All rights reserved.
 * 
 * ---------------------------------------------------------------------------------------------- */

#ifndef TAKU_H_INCLUDED
#define TAKU_H_INCLUDED

#include <windows.h>
#include "stdafx.h"

#include "tkinfo.h"
#include "player.h"

/* ---------------------------------------------------------------------------------------------- 
 * �N���X��`
 * ---------------------------------------------------------------------------------------------- */

class MJSTaku
{

	// ���J��`
	public:

	/* ----------------------------------------------------------------------
	 * �R���X�g���N�^
	 * ---------------------------------------------------------------------- */

	//�R���X�g���N�^
    MJSTaku(){};

	//�f�X�g���N�^
    ~MJSTaku(){};

	/* ----------------------------------------------------------------------
	 * �֐�
	 * ---------------------------------------------------------------------- */

	// ��N���X�������E�I������
	void TakuInit();                    // ��N���X�̏���������
	void TakuPost();                    // ��N���X�̏I������

	// �V�X�e���֘A����
	void SetNowTime(MJSTkinfo *tk);     // ���ݓ����̎擾

	// ���C������
	void CheckTakuStatus(MJSTkinfo *tk, MJSPlayer *ply, bool tmp_push_flg);

	// ��J�n����
	void TakuGameInit(MJSTkinfo *tk, MJSPlayer *ply);

	// �ǊJ�n����
	void KyokuInit(MJSTkinfo *tk, MJSPlayer *ply);

	// �v���[���[�̐Ȍ���
	void SetPlySeki(MJSTkinfo *tk, MJSPlayer *ply);   // �v���[���[�̐Ȍ���

	// �v�R�ݒ�
	void ActSeepai(MJSTkinfo *tk);                    // ���v����
	void SetTimeSeedNum(MJSTkinfo *tk);               // ���Ԃɂ��V�[�h�l�̐ݒ�
	void SetYamahai(MJSTkinfo *tk);                   // �v�R�ݒ�(�w��̒l������)

	// �h���ݒ�
	void SetDora(MJSTkinfo *tk);

	// �z�v����
	void SetHaipai(MJSTkinfo *tk, MJSPlayer *ply);

	// �c������
	void TakuActTsumo(MJSTkinfo *tk, MJSPlayer *ply, int tmp_tsumo_hai, int tmp_tsumo_hai_index, bool tmp_rinshan_mode);

	// ���̌�A�N�V��������(�̂āA�c���a�����̏������`)
	void TakuActPostTsumo(MJSTkinfo *tk, MJSPlayer *ply);                  // ���C���p
	void TakuActPostTsumo_HumPly(MJSTkinfo *tk);                           // HUM�p
	void TakuActPostTsumo_ComPly(MJSTkinfo *tk, MJSPlayer *ply);           // COM�p

	// ���̌�A�N�V���������E�ʏ���
	void TakuActSutehai(MJSTkinfo *tk, int sute_hai, bool sute_aka);       // �̔v����
	void TakuActTsumoGiri(MJSTkinfo *tk);                                  // ���̐؂菈��
	void TakuActTsumoAgari(MJSTkinfo *tk);                                 // ���̘a��
	void TakuActRiichi(MJSTkinfo *tk);                                     // ���[�`����
	void TakuActAnkan(MJSTkinfo *tk, int kan_hai);                         // �Þȏ���
	void TakuActKakan(MJSTkinfo *tk, int kan_hai, int kan_aka);            // ���ȏ���

	// ����A�N�V��������(���̂ď����̒�`)
	void TakuActPostNaki(MJSTkinfo *tk, MJSPlayer *ply);                   // ���C���p
	void TakuActPostNaki_HumPly(MJSTkinfo *tk);                            // HUM�p
	void TakuActPostNaki_ComPly(MJSTkinfo *tk, MJSPlayer *ply);            // COM�p

	// ���m�F
	void ChkPlayNaki(MJSTkinfo *tk, MJSPlayer *ply);                       // ���C���p

	// �����s�E�ʏ���
	void SetPlayNaki(MJSTkinfo *tk, MJSPlayer *ply);
	void TakuActRonAgari(MJSTkinfo *tk);
	void TakuActPon(MJSTkinfo *tk);
	void TakuActChi(MJSTkinfo *tk);
	void TakuActMinkan(MJSTkinfo *tk);

	// �a������
	void SetAgari(MJSTkinfo *tk, MJSPlayer *ply);

	// �r�v����
	void SetHowanpai(MJSTkinfo *tk, MJSPlayer *ply);

	// ���Ǐ���������
	void KyokuNextInit(MJSTkinfo *tk, MJSPlayer *ply);

	// ��I�����ݒ�
	void SetTakuReSult(MJSTkinfo *tk, MJSPlayer *ply);

	// ��I������
	void TakuGameEnd(MJSTkinfo *tk, MJSPlayer *ply);

};

#endif /* TAKU_H_INCLUDED */

/* ---------------------------------------------------------------------------------------------- 
 * �\�[�X�I��
 * ---------------------------------------------------------------------------------------------- */
