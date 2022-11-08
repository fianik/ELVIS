//							�������
/*	�� ���� ����������� ���������� ������ ���� � �������� � ������� � ��� ����� � ������������.
	� ������ ����� ������ � ����� ������������. ����� ������� ������ �� ��������� �� ����
	������������ � ������� ��������� � �������� ����. ������� ����� ���� � ��������� ������� �
	��������� ������ ���� ������� � ���� �������� ����. */

//							����������
/*
* ��������� ����������� ���� � ������, ������� ���������� ����������.
* �������� ������ ����� ab.txt � hd.txt, ����������� � �������� �����.
* ����� ������������� �� ��� ���, ���� �� ������ ������ ������.
* � ������� ����������� ���������� ��� �� ������� ����� Enter.
* �������� ����� ������� "!?."
* 
* ���������� ������� ������� �� ���������� �������������� ������.
* ������ ����� �������� � ��������� ������.
* ��� �������� � �������� ���� � ������� ������������ 
* ���������, ����, ������ ��� ����� � ����� ���������.
* 
* ��������� ������������ � �������� ���� out.txt, ����������� � �������� �����.
*/

#include <iostream>
#include <fstream>

#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

//��������� �������������
std::mutex mtx;

//������� ���������� �� ���������
void Split(std::string path, std::string nameOut, std::vector<std::string> bufferDelimetr)
{
	std::ifstream inFile(path);											//������� ����
	std::fstream outFile(nameOut, std::ios_base::in | std::ios_base::app);										//�������� ����


	std::string delimetr;												//�����������
	for (const auto& it : bufferDelimetr) delimetr += it;				//�������������� ������������ �� vector <string> � string


	if (!inFile.is_open())
	{
		mtx.lock();
		std::cout << "ERROR:: File " << path << " does not exist" << std::endl;
		mtx.unlock();
	}
	else
	{
		//������ ������ �� �����
		std::string str;												//������ �����
		int i = 0;
		getline(inFile, str, '\0');

		std::string token;												//��������� �����

		size_t beg, pos = 0;
		while ((beg = str.find_first_not_of(delimetr, pos)) != std::string::npos)
		{
			i += 1;														//����� ���������/�������� ������

			pos = str.find_first_of(delimetr, beg + 1);
			token = str.substr(beg, pos - beg);
			mtx.lock();

			//����� �� �������
			std::cout << "\tFile:\t" << path << "\tIteration:\t" << i << std::endl;
			std::cout << token << std::endl;

			//����� � �������� ����
			outFile << "\tFile:\t" << path << "\tSubstring number:\t" << i << std::endl;
			outFile << token << std::endl;

			mtx.unlock();
			
			std::this_thread::sleep_for(std::chrono::milliseconds(500)); //������������, ��� ������ �������� ������������
		}
	}

	std::cout << std::endl;
	std::cout << "\tFile:\t" << path << "\tis DONE\t" << std::endl;
	std::cout << std::endl;

	inFile.close();
	outFile.close();
}

int main()
{
	setlocale(LC_ALL, "ru");								//�� ������ ������ :)

	std::string path = "";									//���� � �������
	std::string del = "";									//����������� � �������

	std::string nameOut = "out.txt";						//�������� ��������� �����
	std::ofstream outFile(nameOut);							//�������� ����

	std::vector<std::string> bufferPath;					//��������� ����� ����� � �������
	std::vector<std::string> bufferDelimetr;				//��������� ����� ������������ � �������
	std::vector<std::thread> bufferThread;					//��������� ����� ������� � �������

	//������ �������������� ������ � �������
	do
	{
		std::cout << "Enter the path to the directory with file to split: ";
		std::getline(std::cin, path);
		if (!path.empty())
		{
			bufferPath.push_back(path);
		}
	} while (!path.empty());

	unsigned int vector_size = bufferPath.size();			//���������� ��������� �����
	bufferThread.reserve(vector_size);						//������������� ����� ��� ������� ������ ���������� �����
	
	//������ ������������ � �������
	do
	{
		std::cout << "Enter delimiter: ";
		std::getline(std::cin, del);
		if (!del.empty())
		{
			bufferDelimetr.push_back(del);
		}
	} while (!del.empty());

	//�������� ������� ������� ������� �� ����������					
	for (uint32_t i = 0; i < vector_size; ++i)
	{
		bufferThread.emplace_back(std::thread(Split, bufferPath[i], nameOut, bufferDelimetr)); //��������� - ���������� �����, ��� ��������� �����, ����� ������������
	}
	
	//������������� ������� � �������� ������
	for (auto& thread : bufferThread) { if (thread.joinable()) { thread.join(); } }

	return 0;
}