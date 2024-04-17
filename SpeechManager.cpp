#include "SpeechManager.h"


//����
SpeechManager::SpeechManager()
{
	//��ʼ������
	this->init();

	//����12��ѡ��
	this->createSpeaker();

	//�Ӵ��̶�ȡ����
	this->loadRecord();

}
//չʾ�˵�
void SpeechManager::showMenu()
{

	cout << "****************************************************" << endl;
	cout << "****************** ��ӭ�μ��ݽ����� ****************" << endl;
	cout << "****************** 1.��ʼ�ݽ����� ******************" << endl;
	cout << "****************** 2.�鿴�����¼ ******************" << endl;
	cout << "****************** 3.��ձ�����¼ ******************" << endl;
	cout << "****************** 0.�˳��������� ******************" << endl;
	cout << "****************************************************" << endl;
	cout << endl;

}

//�˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);

}

//���Գ�ʼ��
void SpeechManager::init()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();

}

//ѡ�ִ���
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];
		
		Speaker sp;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;
		}
		sp.m_Name = name;
		//�����һ������
		this->v1.push_back(10001+i);
		//����<int,Speaker>
		this->m_Speaker.insert(make_pair(10001 + i, sp));
	}

}

//��ʼ����
void SpeechManager::startContest()
{
	//��һ�ֳ�ǩ
	this->draw();
	//����
	this->speechContest();
	//��ʾ���
	this->showScore();
	
	this->m_Index++;

	//�ڶ��ֳ�ǩ
	this->draw();
	//����
	this->speechContest();
	//��ʾ���
	this->showScore();

	//�����¼
	this->saveRecord();

	cout << "���������ϣ�" << endl;

	system("pause");
	system("cls");

	//����״̬
	this->init();
	this->createSpeaker();
	this->loadRecord();
}

//��ǩ
void SpeechManager::draw()
{

	cout << "�� <<" << this->m_Index << ">> �ֱ���ѡ�����ڳ�ǩ..." << endl;
	cout << "----------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1)
	{
		//ϴ��
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
	}
	else
	{
		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
	}
	cout << endl;
	cout << "----------------------------" << endl;
	system("pause");

}


//����
void SpeechManager::speechContest()
{
	cout << "----------------�� " << this->m_Index << " ����ʽ������ʼ-----------------" << endl;
	vector<int> src;
	if (this->m_Index == 1)
	{
		src = this->v1;
	}
	else
	{
		src = this->v2;
	}
	//ÿ����һ��
	multimap<double, int,greater<double>>groupMod6;
	//��¼��ǰ����������
	int indexSpeaker = 0;

	for (vector<int>::iterator it = src.begin(); it != src.end(); it++)
	{

		indexSpeaker++;
		//��¼��ί���
		deque<double> sc;
		//ѭ�����10��
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600)/10.f;
			sc.push_back(score);
		}

		//��������
		sort(sc.begin(), sc.end(), greater<double>());

		//ȥͷȥβ
		sc.pop_front();
		sc.pop_back();

		//��ƽ����

		double sum =accumulate(sc.begin(), sc.end(),0.0f);
		double avg = sum / (double)sc.size();
		//ͨ��������ƽ���ִ���ά����<int,Speaker>��
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//���鴦��
		groupMod6.insert(make_pair(avg, *it));


		//��6�˹���С��������
		if (indexSpeaker % 6 == 0)
		{
			//�������С����������ӡ��������

			cout << "��" << indexSpeaker/6 << "С��������Σ�" << endl;
			for (multimap<double, int,greater<double>>::iterator mit = groupMod6.begin(); mit != groupMod6.end(); mit++)
			{
				cout << "��ţ�" << mit->second << "\t������" << this->m_Speaker[mit->second].m_Name << "\t�ɼ���" <<
					mit->first << endl;
			}
			cout << endl;
			//�ٴα���ǰ����
			int bfThree = 0;
			for (multimap<double, int, greater<double>>::iterator mit = groupMod6.begin(); mit != groupMod6.end() && bfThree<3; mit++, bfThree++)
			{
				if (this->m_Index == 1)
				{
					this->v2.push_back(mit->second);
				}
				else
				{

					this->vVictory.push_back(mit->second);
				}
			}
			//���С������
			groupMod6.clear();
		}

	}
	cout << "----------------�� " << this->m_Index << " �ֱ�����ϣ�-----------------" << endl;
	system("pause");

}

//��ʾ�������
void SpeechManager:: showScore()
{
	cout << "----------------��" << this->m_Index << "�ֽ���ѡ�����£�----------------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = this->v2;
	}
	else
	{
		v = this->vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << "\t������" << this->m_Speaker[*it].m_Name << "\t�÷֣�" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;

	}
	system("pause");
	system("cls");
	this->showMenu();
}

//�����¼
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("./speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[this->m_Index - 1] << ",";
	}
	ofs << endl;			//һ��һ�м�¼��bug:���ó�cout�ᵼ��ÿ���¼����ͬһ��
	ofs.close();
	cout << "��¼�ѱ��棡" << endl;
	this->fileIsEmpty = false;

}

//��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs("./speech.csv",ios::in);

	//�ļ�������
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "��¼Ϊ��" << endl;
		ifs.close();
		return;
	}

	//�ļ������Ҽ�¼��Ϊ��
	this->fileIsEmpty = false;

	//���ص�һ���ַ�
	ifs.putback(ch);

	int index = 0;		//����
	string rowData;		//һ������
	while (ifs >> rowData)			//���ж�ȡ
	{
		int pos = -1;				//��¼����λ��
		int start =0;				//�Ӵ���ʼλ��
		vector<string> v6;		//��¼һ����������

		while (true)
		{
			pos = rowData.find(",",start);		//bug:����һ��ʼ©�˵ڶ�������������ÿ��Ĭ�ϴ�0���������� ȡ�Ӵ�����ֵ ��ѭ��
			if (pos == -1)
			{
				//cout << "δ�ҵ�" << endl;
				break;
			}
			string temp = rowData.substr(start, pos - start);
			v6.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v6));
		index++;

	}
	ifs.close();		//bug:��ŵ�ѭ�����ڻᵼ��ֻ�ܶ�һ��
}

//��ʾ�����¼
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "<��" << i + 1 << "��>" << endl;
		cout << "�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << "\t"
			<< "�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << "\t"
		 << "������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager:: clearRecord()
{
	cout << "ȷ����գ�" << endl;
	int select = 2;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("./speech.csv", ios::trunc);

		//����״̬
		this->fileIsEmpty = true;
		this->init();
		this->createSpeaker();
		this->loadRecord();

		cout << "��¼����գ�" << endl;
		ofs.close();

	}
	system("pause");
	system("cls");
}
//����
SpeechManager::~SpeechManager()
{


}