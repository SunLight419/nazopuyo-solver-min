#include "CHAIN.h"
#include "FIELD_ARRAY.h"
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <Windows.h>

using namespace std;

void CHAIN::fall() {
	// ������󔒂̐��𐔂���A�󔒂łȂ��Ȃ�󔒂̐�����������
	for (int j = 0; j < FIELD_WIDTH; ++j) {
		int blankNum = 0;
		for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
			if (this->at(j, i) == ' ') {
				blankNum++;
				continue;
			}
			else {
				if (blankNum == 0) continue;
				this->set_puyo(j, i + blankNum, this->at(j, i));
				this->set_puyo(j, i, ' ');
			}
		}
	}
}

void CHAIN::fall(int x) {
	// ������󔒂̐��𐔂���A�󔒂łȂ��Ȃ�󔒂̐�����������
	int blankNum = 0;
	for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
		if (this->at(x, i) == ' ') {
			blankNum++;
			continue;
		}
		else {
			if (blankNum == 0) continue;
			this->set_puyo(x, i + blankNum, this->at(x, i));
			this->set_puyo(x, i, ' ');
		}
	}
}

void CHAIN::fall(int x, int y) {
	// �񂲂ƂɘA�����N�������Œ��y��ۑ����Ă���ꍇ
	int blankNum = 0;
	for (int i = y; i >= 0; --i) {
		if (this->at(x, i) == ' ') {
			blankNum++;
			continue;
		}
		else {
			if (blankNum == 0) continue;
			this->set_puyo(x, i + blankNum, this->at(x, i));
			this->set_puyo(x, i, ' ');
		}
	}
}



// �ڍׂ͉��L�� chian_loop() ���Q��
bool CHAIN::chain(bool SHOW_CHAIN_SEQUENCE = false) {
	bool res = false;
	vector<bool> visited(FIELD_WIDTH * FIELD_HEIGHT, false);
	vector<pair<int, int>> dir{
		{1, 0}, {0, 1}, {-1, 0}, {0, -1}
	};
	int deleteX = 1 << 6; // �A���ɂ����fall���������
	//int lowestY = 1;
	;	for (int j = 0; j < FIELD_WIDTH; ++j) {
		for (int i = (FIELD_HEIGHT - 1); i > 0; --i) {
			// �����猩�Ă��������������ǂ�(�͂�)
			// 13�i��(i = 0)�͗H��A���ŃJ�E���g����Ȃ�
			if (visited[i * FIELD_WIDTH + j]) continue;
			visited[i * FIELD_WIDTH + j] = true;
			char nowColor = this->at(j, i);
			if (nowColor == ' ') {
				i = -1;
				continue;
			}
			queue<pair<int, int>> que;
			set<pair<int, int>> kouho;
			que.emplace(j, i); // x, y
			kouho.emplace(j, i);
			while (!que.empty()) {
				int x = que.front().first;
				int y = que.front().second;
				que.pop();
				for (int k = 0; k < 4; ++k) {

					int nx = x + dir[k].first;
					int ny = y + dir[k].second;

					if (0 <= nx && nx < FIELD_WIDTH &&
						1 <= ny && ny < FIELD_HEIGHT &&
						!visited[ny * FIELD_WIDTH + nx] &&
						this->at(nx, ny) == nowColor) {
						kouho.emplace(nx, ny);
						que.emplace(nx, ny);
						visited[ny * FIELD_WIDTH + nx] = true;
					}
				}

			}

			if (kouho.size() >= 4) {
				res = true;
				for (auto pos : kouho) {
					this->set_puyo(pos.first, pos.second, ' ');
					deleteX |= 1 << pos.first;
					//lowestY = min(lowestY, pos.second);
				}
			}
		}
	}

	if (SHOW_CHAIN_SEQUENCE) {
		this->show();
		Sleep(500);
	}
	//if (res) { this->fall(); }
	for (int i = 0; i < FIELD_WIDTH; ++i) {
		if (deleteX >> i && 1) fall(i);
	}
	if (SHOW_CHAIN_SEQUENCE) {
		this->show();
		Sleep(250);
	}

	return res;
}

int CHAIN::chainSim(bool SHOW_CHAIN_SEQUENCE = false) {
	int chainCount = 0;
	bool res; // �A�����{�������ǂ���
	while (true) {
		res = chain(SHOW_CHAIN_SEQUENCE);
		if (res) {
			chainCount++;
			continue;
		}
		else {
			break;
		}
	}


	return chainCount;
}

int CHAIN::chain_loop(bool SHOW_CHAIN_SEQUENCE) {
	// �ċA�Ăяo���ł͂Ȃ�while�Ń��[�v����ver
	// Kenny���x���`�ł� 0.1ms ���炢�͂₻��
	int chainCount = 0;
	bool loopFlag = true; // ���[�v���n�܂�^�C�~���O�� false �ɂȂ�A�A������������� true �ɂȂ�

	// �t�B�[���h�� fall �ς݂ł����Ă�������
	while (loopFlag) {
		bool res = false; // �S�ȏ�A�����Ă���Ղ悪���邩�ǂ���
		vector<bool> visited(FIELD_WIDTH * FIELD_HEIGHT, false); // �T���ς݂̃}�X���L�^ vector����Ȃ�������������
		vector<pair<int, int>> dir{
			{1, 0}, {0, 1}, {-1, 0}, {0, -1}
		};
		// dir: direction. ���ꂪ����� BFS �̎������y
		int deleteX = 1 << 6; // �A���ɂ����fall���������(bit���Z)
		for (int j = 0; j < FIELD_WIDTH; ++j) {
			for (int i = (FIELD_HEIGHT - 1); i > 0; --i) {
				// �����猩�Ă��������������ǂ�(�͂�) (��̃}�X���󔒂Ȃ�A���̏�̃}�X���󔒂̂͂��Ȃ̂�)
				// 13�i��(i = 0)�͗H��A���ŃJ�E���g����Ȃ�
				if (visited[i * FIELD_WIDTH + j]) continue; // ���łɒT���ς݂Ȃ� continue
				visited[i * FIELD_WIDTH + j] = true; // �T���ς݂ɂ���
				char nowColor = this->at(j, i); // ���̃}�X�̂Ղ�̐F
				if (nowColor == ' ') { // �󔒂Ȃ�΁A�E�̗�Ɉڂ�
					i = -1;
					continue;
				}
				queue<pair<int, int>> que; // �T������ꏊ��queue
				set<pair<int, int>> kouho; // �����ꏊ�̌�� ����� size() ��4�ȏ�Ȃ�΁A����̒��g�̂Ղ���t�B�[���h�������
				// ���݂̏ꏊ��ǉ�����
				que.emplace(j, i); // x, y
				kouho.emplace(j, i);

				// que ����ɂȂ�܂�(= �����F����������)������
				while (!que.empty()) {
					// ���݂� x, y ���W
					int x = que.front().first;
					int y = que.front().second;
					que.pop();
					for (int k = 0; k < 4; ++k) {
						// ���݂̃}�X�ɑ΂���㉺���E�̃}�X��T������
						// dir ������Ƃ��ꂪ�y
						int nx = x + dir[k].first; // new x
						int ny = y + dir[k].second; // new y

						if (0 <= nx && nx < FIELD_WIDTH &&
							1 <= ny && ny < FIELD_HEIGHT && // x, y ���t�B�[���h�̊O�ɂ͂ݏo���Ă��Ȃ���
							!visited[ny * FIELD_WIDTH + nx] && // ���łɒT���ς݂Ȃ�T�����Ȃ�
							this->at(nx, ny) == nowColor) { // �����F�łȂ���ΒT�����Ȃ�
							kouho.emplace(nx, ny); // kouho, que �� nx, ny ��ǉ����A�T���𑱂���
							que.emplace(nx, ny);
							visited[ny * FIELD_WIDTH + nx] = true;
						}
					}

				}

				if (kouho.size() >= 4) { // 4�A���ȏ�Ȃ�΂Ղ�������i�󔒂�}���j
					res = true;
					for (auto pos : kouho) {
						this->set_puyo(pos.first, pos.second, ' ');
						deleteX |= 1 << pos.first; // �������N�������L�^
					}
				}
			}
		}
		if (!res) {
			loopFlag = false;
			break;
		}
		else {
			chainCount++;
		}

		if (SHOW_CHAIN_SEQUENCE) { // �r�����ʕ\���p
			this->show();
			Sleep(500);
		}
		//if (res) { this->fall(); }
		for (int i = 0; i < FIELD_WIDTH; ++i) {
			if (deleteX >> i && 1) fall(i);
		}
		if (SHOW_CHAIN_SEQUENCE) {
			this->show();
			Sleep(250);
		}

	}

	return chainCount;

}

bool CHAIN::isChain() {
	bool res = false;
	vector<bool> visited(FIELD_WIDTH * FIELD_HEIGHT, false);
	vector<pair<int, int>> dir{
		{1, 0}, {0, 1}, {-1, 0}, {0, -1}
	};
	for (int j = 0; j < FIELD_WIDTH; ++j) {
		for (int i = (FIELD_HEIGHT - 1); i > 0; --i) {
			if (res) break; // �A������������̂Ȃ�ΒT����ł��؂�
			// �����猩�Ă��������������ǂ�(�͂�)
			// 13�i��(i = 0)�͗H��A���ŃJ�E���g����Ȃ�
			if (visited[i * FIELD_WIDTH + j]) continue;
			visited[i * FIELD_WIDTH + j] = true;
			char nowColor = this->at(j, i);
			if (nowColor == ' ') {
				i = -1;
				continue;
			}
			queue<pair<int, int>> que; // ���͕s�v
			int kouho = 1;
			que.emplace(j, i); // x, y
			while (!que.empty()) {
				int x = que.front().first;
				int y = que.front().second;
				que.pop();
				for (int k = 0; k < 4; ++k) {

					int nx = x + dir[k].first;
					int ny = y + dir[k].second;

					if (0 <= nx && nx < FIELD_WIDTH &&
						1 <= ny && ny < FIELD_HEIGHT &&
						!visited[ny * FIELD_WIDTH + nx] &&
						this->at(nx, ny) == nowColor) {
						que.emplace(nx, ny);
						kouho++;
						if (kouho >= 4) {
							res = true;
							return true;
						}
						visited[ny * FIELD_WIDTH + nx] = true;
					}
				}

			}

			if (kouho >= 4) {
				res = true;
				return true;
				break;
			}
		}
	}

	return res;
}
