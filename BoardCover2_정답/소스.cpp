#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <string>

#include <vector>

#include <algorithm>

using namespace std;



//������ ����

int boardH, boardW; //board Height(����), board Width(����)

vector<string> board;

//����� ũ��

int blockSize;

//�������� �� ĭ�� ���������� ��Ÿ����

//1�̸� #�̰ų� �̹� ���� ĭ, 0�̸� .

int covered[10][10];

//����� ȸ���� ���¸� ����ϰ� ��� ��ǥ�� ������� ����

vector<vector<pair<int, int>>> rotations; //������ ����



//2���� �迭 arr�� �ð�������� 90�� ���� ��� ��ȯ

vector<string> rotate(const vector<string>& arr)

{

	vector<string> result(arr[0].size(), string(arr.size(), ' ')); //���ο� ���ΰ� �ڹٲ� vector ����

	for (int i = 0; i < arr.size(); i++)

		for (int j = 0; j < arr[0].size(); j++)

			result[j][arr.size() - i - 1] = arr[i][j]; //90�� ȸ��

	return result;

}



//block�� �װ��� ȸ�� ���¸� ����� �̵��� ��� ��ǥ�� ������� ��ȯ

void generateRotations(vector<string> block)

{

	rotations.clear();

	rotations.resize(4); //�װ��� ȸ��

	for (int rot = 0; rot < 4; rot++)

	{

		int originY = -1, originX = -1;

		for (int i = 0; i < block.size(); i++)

			for (int j = 0; j < block[i].size(); j++)

				if (block[i][j] == '#')

				{

					if (originY == -1)

					{

						//���� ���� �� ���ʿ� �ִ� ĭ�� '����'�� �ȴ�

						originY = i;

						originX = j;

					}

					//�� ĭ�� ��ġ�� �������κ����� �����ǥ�� ǥ��

					rotations[rot].push_back(make_pair(i - originY, j - originX));

				}

		//����� �ð� �������� 90�� ȸ��

		block = rotate(block);

	}

	//�װ��� ȸ�� ���� �� �ߺ��� ���� ��� �̸� ����

	sort(rotations.begin(), rotations.end());

	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());

	//����� �� ĭ ¥������ ����

	blockSize = rotations[0].size();

}



//(y, x)�� ���� ��ĭ���� �ؼ� �־��� ����� delta=1�̸� ����, -1�̸� ���ش�

//����� ���� �� �̹� ���� ����̳� #�� ��ġ�� ������, �ƴϸ� ���� ��ȯ

bool set(int y, int x, const vector<pair<int, int>> & block, int delta)

{

	//placed:���ݱ��� ���� ����� ��

	bool result = true;

	for (int i = 0; i < block.size(); i++)

	{

		//���� ���� �ִٸ�

		if (y + block[i].first >= 0 && y + block[i].first < boardH && x + block[i].second >= 0 && x + block[i].second < boardW)

		{

			covered[y + block[i].first][x + block[i].second] += delta;

			result = result && (covered[y + block[i].first][x + block[i].second] == 1);

		}

		else

			result = false;

	}

	return result;

}



int best; //���ݱ��� ã�� ������



//���� �� �ִ� ����� ���� �ܼ��� ���� �� ĭ�� ���� ����� ũ��� ���� ��

//�ű⿡ �̹� ���� ���� ������ �� ���� �����غ��� ���� ��� ������

int blockPrune(int placed) //����ġ��

{

	int cnt = 0;

	for (int i = 0; i < boardH; i++)

		for (int j = 0; j < boardW; j++)

			cnt += !(covered[i][j]) ? 1 : 0;

	return ((cnt / blockSize) + placed <= best);

}



void search(int placed) //placed:���ݱ��� ���� ����� ��

{

	if (blockPrune(placed)) //����ġ��

		return;

	//���� ä���� ���� �� ĭ �� ���� ���� ���ʿ� �ִ� ĭ�� ã�´�

	int y = -1, x = -1;

	for (int i = 0; i < boardH; i++)

	{

		for (int j = 0; j < boardW; j++)

		{

			if (covered[i][j] == 0)

			{

				y = i;

				x = j;

				break;

			}

		}

		if (y != -1)

			break;

	}

	//���� ���:�������� ��� ĭ�� ó���� ���

	if (y == -1)

	{

		best = max(best, placed);

		return;

	}

	//�� ĭ�� ���´�

	for (int i = 0; i < rotations.size(); i++)

	{

		if (set(y, x, rotations[i], 1))

			search(placed + 1);

		//�ٽ� ���ش�

		set(y, x, rotations[i], -1);

	}

	//�� ĭ�� ���� �ʰ� ���Ƶд�

	covered[y][x] = 1;

	search(placed);

	covered[y][x] = 0;

}



int solve(void)

{

	best = 0;

	//covered �迭 �ʱ�ȭ

	for (int i = 0; i < boardH; i++)

		for (int j = 0; j < boardW; j++)

			covered[i][j] = (board[i][j] == '#' ? 1 : 0);

	search(0);

	return best;

}



int main(void)

{
	freopen("Text.txt", "r", stdin);
	int test_case;

	cin >> test_case;

	if (test_case < 1 || test_case>100)

		exit(-1);



	for (int i = 0; i < test_case; i++)

	{

		board.clear();

		vector<string> block;

		int blockH, blockW; //����� ����, ���� ũ��

		cin >> boardH >> boardW >> blockH >> blockW;

		if (boardH < 1 || boardH>10 || boardW < 1 || boardW>10 || blockH < 1 || blockH>10 || blockW < 1 || blockW>10)

			exit(-1);



		//������ �Է�

		for (int j = 0; j < boardH; j++)

		{

			string temp;

			cin >> temp;

			board.push_back(temp);

		}

		//��� �Է�

		for (int j = 0; j < blockH; j++)

		{

			string temp;

			cin >> temp;

			if (temp.size() > blockW)

				exit(-1);

			block.push_back(temp);

		}

		generateRotations(block);

		cout << solve() << endl;

	}

	return 0;

}