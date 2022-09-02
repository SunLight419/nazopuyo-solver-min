#pragma once
#include "FIELD_ARRAY.h"

// �A���Ɋւ������

class CHAIN : public FIELD_ARRAY
{
public:
	// �Ղ�𗎉�������֐�
	// ���s���x�̖ʂł� fall(x) <= fall() ���ۂ��C������
	// fall(x, y)�� ���������� x, y ���L�^����̂��{�g���l�b�N�ɂȂ��đ����x��
	// 
	// �t�B�[���h���ׂĂ̂Ղ�𗎉�������
	// �A���J�n�O�ȂǂɎg�p
	void fall();

	// �����x ( 0 <= x < 6)�ɑ΂��Ă̂ݗ������s��
	void fall(int x);

	// �����x�̉�����y�i��"�ȏ�"�̂Ղ�ɑ΂��ė������s��
	// �\���I�ɂ͍��オ0�i�ڂƂ��Ă��邱�Ƃɒ���(y�ȉ��ɏ������s��)
	void fall(int x, int y);

	// �A�����������邩�ǂ���
	// �Ȃ��Ղ�T���̍ہA�ŏI��łȂ��ꍇ�ɘA�����N����΁A���̎}�̒T����ł��؂�
	bool isChain();

	// 1�A�����s��
	bool chain(bool SHOW_CHAIN_SEQUENCE);

	// �A�����N����Ȃ��Ȃ�܂� chain() ���J��Ԃ��֐�
	// �߂�l�͘A����
	// SHOW_CHAIN_SEQUENCE: �A���̉ߒ���\�����邩�ǂ���
	// ��ʂ̃V�~�����[�V�����ł� TRUE �����A�Ȃ��Ղ�T���ł� FALSE ���w�肷��
	// Kenny19chain benchmark �ł� 3ms/kenny �ق�
	int chainSim(bool SHOW_CHAIN_SEQUENCE);

	// �֐��̃I�[�o�[�w�b�h�������āA��L�� chainSim() �� while ���[�v�Ŏ�����������
	// �������̂ق���������Ƒ������� 2.95ms/kenny �ق�
	int chain_loop(bool SHOW_CHAIN_SEQUENCE);
};

