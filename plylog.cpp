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

#include "plylog.h"

/* --------------------------------------------------------------- */
// ��J�n
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogTakuStart(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// �t�@�C��������
		show.PlylogFileInit(logname);

		// ���ʊ֐��Ăяo��
		// show.ShowTakuStart(tk);
	
		// ����\��
		// show.ShowRule(tk);
	
		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// ��I��
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogTakuEnd(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// �t�@�C��������
		show.PlylogFileInit(logname);

		// ���ʊ֐��Ăяo��
		// show.ShowTakuEnd(tk);

		// �o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �ǊJ�n
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogKyokuStart(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// �t�@�C��������
		show.PlylogFileInit(logname);

		// ���ʊ֐��Ăяo��
		// show.ShowKyokuStart(tk);

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �ǏI��
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogKyokuEnd(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// �t�@�C��������
		show.PlylogFileInit(logname);

		// ���ʊ֐��Ăяo��
		// show.ShowKyokuEnd(tk);

		// �o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �z�v����(�S��)
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogAllHaipai(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// �t�@�C��������
		show.PlylogFileInit(logname);

		// ��؂��
		show.ShowBorder();

		//����\��
		// show.ShowAllHaipai(tk);
		// show.PlylogPrint("\n");

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �z�v����
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogHaipai(MJSTkinfo *tk,int pnum){

	if( loglevel > 0 ){

		// �t�@�C��������
		show.PlylogFileInit(logname);

		// ��؂��
		show.ShowBorder();

		// �A�N�V�����\��
		// show.ShowAct(tk, pnum);

		// ����\��
		// show.ShowHaipai(tk,pnum);
		show.PlylogPrint("\n");

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �c������v
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogTsumoHai(MJSTkinfo *tk,int pnum){

	if( loglevel > 0 ){

		//�t�@�C��������
		show.PlylogFileInit(logname);

		//��؂��
		show.ShowBorder();

		// ����\��
		// show.ShowKyokuInfo(tk);
		// show.PlylogPrint("\n");

		// �v���[���[���\��
		// show.ShowKyokuPlyInfo(tk, pnum);
		// show.PlylogPrint("\n");

		// �A�N�V�����\��
		// show.ShowAct(tk, pnum);

		// �c���v�\��
		// show.PlylogPrint("�c���v�@");
		// show.ShowNormalHai(tk->pinfo[pnum].Tsumo);
		// show.PlylogPrint("\n");

		// �͕\��
		// show.ShowSutehai(tk, pnum);
		// show.PlylogPrint("\n");

		//��v�\��
		show.ShowTehaiTsumo(tk, pnum);
		show.PlylogPrint("\n"); 

		// �������
		show.ShowShanten(tk, pnum);

		// �҂����
		show.ShowMatchiHai(tk, pnum);

		// �c��������
		show.ShowTsumoShanten(tk, pnum);

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �c���E�̔v�̏o��(�����̂�)
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogTsumoSute(MJSTkinfo *tk,int pnum){

	if( loglevel > 0 ){

		//�t�@�C��������
		show.PlylogFileInit(logname);

		//��؂��
		show.ShowBorder();

		//�v���[���[���\��
		show.ShowKyokuPlyInfo(tk, pnum);
		show.PlylogPrint("\n");

		//�A�N�V�����\��
		show.ShowAct(tk, pnum);

		//��؂��
		show.ShowBorder();

		//����\��
		show.ShowKyokuInfo(tk);
		show.PlylogPrint("\n");

		//�v���[���[���\��
		show.ShowKyokuPlyInfo(tk, pnum);
		show.PlylogPrint("\n");

		//�c���v�\��
		show.PlylogPrint("�@�@�@");
		show.PlylogPrint("�c���v�@");
		show.ShowNormalHai(tk->pinfo[pnum].Tsumo);
		show.PlylogPrint("\n");

		//�̔v�\��
		show.PlylogPrint("�@�@�@");
		show.ShowSutehai(tk, pnum);
		show.PlylogPrint("\n");

		//��v�\��
		show.ShowTsumoSute(tk, pnum);
		show.PlylogPrint("\n"); 

		//�������
		show.ShowShanten(tk, pnum);

		//�҂����
		show.ShowMatchiHai(tk, pnum);

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �̔v�o��(�S���E��v����)
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogAllTsumoSute(MJSTkinfo *tk){

	if( loglevel > 0 ){

		//�ϐ���`
		int i;

		//�t�@�C��������
		show.PlylogFileInit(logname);

		//��؂��
		show.ShowBorder();

		//����\��
		show.ShowKyokuInfo(tk);
		show.PlylogPrint("\n");

		//��v�\��
		for(i = 0; i < 4; i++){

			// ��؂��	
			show.PlylogPrint("\n");

			//�e�v���[���[���
			show.ShowKyokuPlyInfo(tk, i);
			show.PlylogPrint("\n");

			if( i == tk->pnum ){

				//�c���E�̂ĕ\��
				show.PlylogPrint("�c���v�@");
				show.ShowNormalHai(tk->pinfo[i].Tsumo);
				show.PlylogPrint("�@�@�@");

			}

			show.ShowSutehai(tk, i);
			show.PlylogPrint("\n");

			if( i == tk->pnum ){

				show.ShowTsumoSute(tk, i);
				show.PlylogPrint("\n"); 

			}else{

				show.ShowTehai(tk, i);
				show.PlylogPrint("\n"); 
			}

			//�������
			show.ShowShanten(tk, i);

			//�҂����
			show.ShowMatchiHai(tk, i);

		}

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �̔v�݂̂̏o��
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogSute(MJSTkinfo *tk,int pnum){

	if( loglevel > 0 ){

		//�t�@�C��������
		show.PlylogFileInit(logname);

		//��؂��
		show.ShowBorder();

		//�v���[���[���\��
		show.ShowKyokuPlyInfo(tk, pnum);
		show.PlylogPrint("\n");

		//�A�N�V�����\��
		show.ShowAct(tk, pnum);

		//��؂��
		show.ShowBorder();

		//����\��
		show.ShowKyokuInfo(tk);
		show.PlylogPrint("\n");

		//�v���[���[���\��
		show.ShowKyokuPlyInfo(tk, pnum);
		show.PlylogPrint("\n");

		//�̔v�\��
		show.ShowSutehai(tk, pnum);
		show.PlylogPrint("\n");

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �����̃��A�N�V�����\��
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogOwnReact(MJSTkinfo *tk){

	if( loglevel > 0 ){

		//�t�@�C��������
		show.PlylogFileInit(logname);

		//��؂��
		show.ShowBorder();

		//�v���[���[���\��
		show.PlylogPrint("���v���[���[�̃��A�N�V�����F");
		show.PlylogPrint("\n");

		//�A�N�V�����\��
		show.ShowAct(tk, tk->tkid);

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �S���̖��A�N�V�����\��
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogAllReact(MJSTkinfo *tk){

	int i;

	if( loglevel > 0 ){

		//�t�@�C��������
		show.PlylogFileInit(logname);

		//��؂��
		show.ShowBorder();

		//�v���[���[���\��
		show.ShowKyokuPlyInfo(tk, tk->pnum);
		show.PlylogPrint("\n");

		//����\��
		for(i = 0; i < 4; i++){

			//�A�N�V�����\��
			show.ShowAct(tk, i);

		}
	
		//�o�͏I������
		show.PlylogFilePost();

	}
}

/* --------------------------------------------------------------- */
// ���A�N�V�����\��
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogDisplayPlyNaki(MJSTkinfo *tk){

	if( loglevel > 0 ){

		//�t�@�C��������
		show.PlylogFileInit(logname);

		//��؂��
		show.ShowBorder();

		//����\��
		show.ShowKyokuInfo(tk);
		show.PlylogPrint("\n");

		//�v���[���[���\��
		show.ShowKyokuPlyInfo(tk, tk->pnum);
		show.PlylogPrint("\n");

		// ���A�N�V�����\��
		show.ShowNakiAct(tk, tk->pnum);

		// �o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �a���A�N�V�����\��
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogAgari(MJSTkinfo *tk,int pnum){

	if( loglevel > 0 ){

		//�t�@�C��������
		show.PlylogFileInit(logname);

		//��؂��
		show.ShowBorder();

		// �a���\��
		show.ShowAgariInfo(tk);

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// DLL�����̊ȈՔł̘a���\��
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogDisplayPlyAgari(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// �t�@�C��������
		show.PlylogFileInit(logname);

		// ��؂��
		show.ShowBorder();

		// �a���\��
		show.ShowClientCalcAgariInfo(tk);

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// ���ǌ��ʏo��
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogRyukyoku(MJSTkinfo *tk){

	if( loglevel > 0 ){

		// �t�@�C��������
		show.PlylogFileInit(logname);

		// ��؂��
		show.ShowBorder();

		// �a�����ʕ\��
		show.PlylogPrint("�@�@�@���ǁ@�@�@");

		// ���s
		show.PlylogPrint("\n");

		// ��؂��
		show.ShowBorder();

		// ���v�L��

		// �o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// PlaeyAI�ڍ׏��
/* --------------------------------------------------------------- */
void MJSPlylog::PlylogDisplayPlyAIinfo(MJSTkinfo *tk, MJSPlyAI *ai){

	if( loglevel > 0 ){

		//�t�@�C��������
		show.PlylogFileInit(logname);

		//AI���\��
		show.ShowPlyAIinfo(tk,ai);

		//�o�͏I������
		show.PlylogFilePost();

	}

}

/* --------------------------------------------------------------- */
// �t�@�C�������܂�
/* --------------------------------------------------------------- */
