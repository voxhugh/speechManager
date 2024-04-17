#include <iostream>
using namespace std;
#include "SpeechManager.h"


int main()
{

	//随机数种子
	srand((unsigned int)time(NULL));

	SpeechManager sm;
	
	while (true)
	{

		sm.showMenu();
		cout << "请输入您需要的服务：" << endl;
		int select;
		cin >> select;
		switch (select)
		{
		case 1:
			sm.startContest();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}

	}

	system("pause");
	return 0;
}