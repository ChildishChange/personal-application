#include"stdafx.h"
//#include"stdfx.h"
#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>
#include<algorithm>
#define MAX 1000
#define Inf 1000000 
using namespace std;

int adj[MAX][MAX];


class SubLine
{
public:
	string LineName;
	vector<string> Stations;
	bool isCircle = false;
	bool isTwoDir = true;
};
class Station
{
public:
	int LastStation = -1;
	string Line;
	string Name;
};
void dijkstra(string start, string end, vector<Station> all);
void print(int destination, int origin, vector<Station> all);
void cmdhandle(int argc, char *argv[], vector<Station> all);
void setTransPortWeight(string start, string end, int weight, vector<Station> all);


void dijkstra(string start, string end, vector<Station> all)
{
	int size = all.size();
	//	cout<<"size:"<<size<<endl; 
	int origin = -1;
	int destination = -1;
	if (start == end)
	{
		cout <<"1"<< endl;
		cout << start << endl;
		return;
	}
	int *dist = new int[size];
	bool *update = new bool[size];
	for (int i = 0; i != size; i++)
	{
		update[i] = true;
		dist[i] = Inf;
		if (origin == -1 && all[i].Name == start)
		{
			origin = i;
			//			cout<<"��㣺"<<all[i].Name<<endl; 
			continue;
		}
		if (destination == -1 && all[i].Name == end)
		{
			destination = i;
			//			cout<<"�յ㣺"<<all[i].Name<<endl; 
			continue;
		}
	}
	//	cout<<"origin:"<<origin<<" destination:"<<destination<<endl; 
	if (origin == -1)
		cout << "ERROR!THERE IS NO STATION NAMED:" << start << endl;
	if (destination == -1)
		cout << "ERROR!THERE IS NO STATION NAMED:" << end << endl;
	if (origin == -1 || destination == -1)
		return;

	dist[origin] = 0;
	update[origin] = false;

	for (int i = 0; i != size; i++)
	{
		if (i == origin)
			continue;
		if (adj[origin][i] == Inf)
			continue;
		else
		{
			all[i].LastStation = origin;
			dist[i] = adj[origin][i];
		}
	}

	bool result = false;
	for (int i = 0; i != size; i++)
		result = result | update[i];

	while (result != false)
	{
		for (int i = 0; i != size; i++)
		{
			update[i] = false;
		}
		result = false;
		for (int i = 0; i != size; i++)
		{
			if (i == origin)
				continue;
			for (int j = 0; j != size; j++)
			{
				if (j == origin)
					continue;
				if (adj[i][j] + dist[i]<dist[j])
				{
					dist[j] = adj[i][j] + dist[i];
					all[j].LastStation = i;
					update[i] = true;
				}
				else
				{
					continue;
				}

			}
			result = result | update[i];
		}
	}
	print(destination, origin, all);
/*	cout<<"distance:"<<dist[destination]<<endl; 
	if(dist[destination]>=Inf)
	{
		cout<<"������������·��"<<endl;
		return ; 
	}
	do
	{
		cout<<all[destination].Name <<endl;
		if(all[destination].LastStation==origin)
		{
			cout<<all[origin].Name<<endl; 
			break;
		}
		destination = all[destination].LastStation;
			
	}while(destination!=origin);

	*/	
}
void print(int destination, int origin, vector<Station> all)
{
	vector<Station> Path;

	do
	{
		//		cout<<all[destination].Name <<endl;
		Path.push_back(all[destination]);
		if (all[destination].LastStation == origin)
		{
			Path.push_back(all[origin]);
			//			cout<<all[origin].Name<<endl; 
			break;
		}
		destination = all[destination].LastStation;

	}while (destination != origin);
	//cout<<Path.size()<<endl; 

//	for (int i = 0; i != Path.size(); i++)
//		cout << Path[i].Name << endl;

	reverse(Path.begin(), Path.end());
	int PathNum = 0;
	for (int i = 0; i != Path.size(); i++)
	{
		if (i != 0 && Path[i].Name == Path[i - 1].Name)
		{
			continue;
		}
		PathNum++;
	}
	cout << PathNum << endl;
	for (int i = 0; i != Path.size(); i++)
	{
		if (Path[i].Name == Path[i + 1].Name)//���ֻ��� 
		{
			if (Path[i].Line == Path[i + 1].Line)
			{
				continue;
			}
			if (i == 0)//�ʼ�ǻ��� 
				continue;
			if (i == Path.size() - 2)//��������ǻ��� 
			{
				cout << Path[i].Name << endl;
				break;
			}
			else//������� 
			{
				cout << Path[i].Name << "����" << Path[i + 1].Line << endl;
				i+=2;
				if (i == Path.size() - 1)//�����ڶ��͵��������ǻ��� 
				{
					cout << Path[i].Name << endl;
					break;
				}
				i--;
				continue;
			}
		}
		if (i == Path.size() - 2)
		{
			cout << Path[i].Name << endl;
			cout << Path[i + 1].Name << endl;
			break;
		}
		cout << Path[i].Name << endl;
	}
}



void cmdhandle(int argc, char *argv[], vector<Station> all)
{
	char input[100];
	string command;
	string word;
	int arg = argc;
	vector<string> temp;
	for (int i = 0; i<argc; i++)
	{
		word = argv[i];
		temp.push_back(word);
	}

	/*����������*/
	while (true)
	{
		if (arg == 2)//���������·
		{
			int p =-1;
			for (int i = 0; i != all.size(); i++)
				if (all[i].Line == temp[1])
				{
					p = i;
					break;
				}
			if (p ==-1)
			{
				cout << "ERROR!THERE IS NO SUBWAY LINE NAMED:" << temp[1] << endl;
				
				//					break; 
			}
			else
			{
				while (all[p].Line == temp[1])
				{
					cout << all[p].Name << endl;
					p++;
					if (p == all.size())
						break;
				}
			}
			//			break;
		}
		else if (arg == 4)//�������·��
		{
			if (temp[1] == "-b")
			{
				setTransPortWeight(temp[2],temp[3],0, all);

				dijkstra(temp[2], temp[3], all);
				//	continue;
				//	break;
			}
			else if (temp[1] == "-c")
			{
				setTransPortWeight(temp[2],temp[3],1000, all);
				dijkstra(temp[2], temp[3], all);

				//	continue;
				//break;
			}
			else
			{
				cout << "WARNING!UNDEFINED COMMAND!" << endl;
				//	continue; 
				//	break;
			}
		}
		else
		{
			cout << "WARNING!UNDEFINED COMMAND!" << endl;
		}

		//�˴�Ӧ�ü����������� ������
		temp.erase(temp.begin(), temp.end());

		fgets(input,80,stdin);
		command = input;

		//		cout<<endl;
		//		cout<<"command:"<<command<<endl; 
		//			cout<<endl;

		stringstream ss(command);
		temp.push_back("subway.exe");
		while (ss >> word)
			temp.push_back(word);
		//		for(int j = 0;j!=temp.size();j++)
		//			cout<<temp[j]<<endl;
		arg = temp.size();
		//		cout<<"arg:"<<arg<<endl;
		if (arg == 2 && temp[1] == "FINISH")
			break;

	}

}

void setTransPortWeight(string start, string end, int weight, vector<Station> all)
{
	for (int i = 0; i != all.size(); i++)
	{
		for (int j = 0; j<i; j++)
		{
			if (all[i].Name == all[j].Name)
			{
				if (all[i].Name == start || all[i].Name == end)
				{
					adj[i][j] = 0;
					adj[j][i] = 0;
					continue;//�����������и�����,��Ҫ��ԭ�����ȣ�����ֻ��Ӱ�쵽����վ����Ȼ���´�����֮ǰ��Ȼ��Ҫ���£�����ϴ���Ϊs\e
							//�ĳ�վ���û����Ϊ�����ᱻ���¸�ֵΪweight�����⣬����ֻ����s��eΪ����վʱ����������໻��վ�ճ�����ˡ�����������û�д�����
				}
				adj[i][j] = weight;
				adj[j][i] = weight;
			}
		}
	}
	

}
int main(int argc, char *argv[])
{

	int Total_Stations = 0;
	int Total_Line = 0;
	char buf[50];
	vector<Station> all_station;
	vector<SubLine> Sub_Sys;



	ifstream ifs("G:�γ�\\�������\\beijing-subway.txt");
	string LineName;
	string StationName;
	//	Station temp;
	int LineHead = 0;
	int flag = 0;
	if (!ifs.is_open())
	{
		cout << "���ļ�ʧ�ܣ�������ֹ��" << endl;
	}
	for (int i = 0; i<MAX; i++)
		for (int j = 0; j<MAX; j++)
		{
			adj[i][j] = Inf;
		}


	while (!ifs.eof())
	{

		ifs.getline(buf, 50, '\n');
		//	cout<<buf<<endl;
		if (strncmp(buf, "����", 4) == 0)
		{
			Total_Line++;
			LineName = buf;
		}
		/*--------------------------------------------*/
		else if (strncmp(buf, "˫����ʻ", 8) == 0)
			flag = 2;
		/*--------------------------------------------*/
		else if (strncmp(buf, "������ʻ", 8) == 0)
			flag = 1;
		/*--------------------------------------------*/
		else if (strncmp(buf, "end", 3) == 0)
		{
			//			cout<<buf<<endl;
			if (all_station[LineHead].Name == all_station[all_station.size() - 1].Name)
			{//��ʱ���һ����վ�Ѿ���ǰһ����վ��������ϵ�������Ҫ������һ����վ��ǰһ����վ����ϵ������flag��ֵ��ͬʱ���������ڶ�����վ����ʼվ������ϵ������flag���á����pop_back//total station-1
				if (flag == 2)
				{
					adj[all_station.size() - 2][all_station.size() - 1] = Inf;
					adj[all_station.size() - 1][all_station.size() - 2] = Inf;

					adj[all_station.size() - 2][LineHead] = 1;
					adj[LineHead][all_station.size() - 2] = 1;
				}
				else
				{
					adj[all_station.size() - 2][all_station.size() - 1] = Inf;

					adj[all_station.size() - 2][LineHead] = 1;
				}
				all_station.pop_back();
				Total_Stations--;
			}
		}
		/*--------------------------------------------*/
		else
		{
			if (strlen(buf) == 0)
				continue;
			Station temp;
			temp.Name = buf;
			temp.Line = LineName;
			all_station.push_back(temp);
			Total_Stations++;
			adj[all_station.size() - 1][all_station.size() - 1] = 0;
			if (flag == 2)
			{
				if (all_station.size() == 1)//���Ǳ�����ĵ�һ����վ	
					continue;
				else
				{
					if (all_station[all_station.size() - 2].Line == all_station[all_station.size() - 1].Line)//ͬһ����·
					{
						adj[all_station.size() - 2][all_station.size() - 1] = 1;
						adj[all_station.size() - 1][all_station.size() - 2] = 1;
					}
					else//������·
					{
						LineHead = all_station.size() - 1;
						continue;
					}
				}

			}
			else if (flag == 1)
			{
				if (all_station.size() == 1)//���Ǳ�����ĵ�һ����վ
					continue;
				else
				{
					if (all_station[all_station.size() - 2].Line == all_station[all_station.size() - 1].Line)//ͬһ����·
					{
						adj[all_station.size() - 2][all_station.size() - 1] = 1;
					}
					else//������·
					{
						LineHead = all_station.size() - 1;
						continue;
					}
				}

			}
		}

	}
	//setTransPortWeight(0, all_station);
	//	for(int i = 0;i<Total_Stations;i++)
	//	{
	//		for(int j = 0;j<Total_Stations;j++)
	//			cout<<adj[i][j]<<" ";
	//		cout<<endl;
	//	}
	//	cout<<all_station.size()<<endl;
	//	cout<<Total_Stations<<endl;
	//	for(int i = 0;i!=all_station.size()-1;i++)
	//	{
	//		cout<<all_station[i].Line<<":"<<all_station[i].Name<<endl;
	//	}


	/*����������*/
	cmdhandle(argc, argv, all_station);



	//	dijkstra("�Ƹ�ׯ","�Ź�ׯ",all_station);
	/*dijkstra�㷨*/


	//	system("pause");
	return 0;
}
