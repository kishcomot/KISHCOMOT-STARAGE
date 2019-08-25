/*Первое задание
Реализовать простейший файловый менеджер с использованием ООП
(классы, наследование и так далее).
Файловый менеджер должен иметь возможность показывать содержимое
дисков, создавать папки / файлы, удалять папки / файлы, переименовывать пап -
ки / файлы, копировать / переносить папки / файлы, вычислять размер папки /
файла, и так далее.*/




// для проверки работы сразу создайте файл и директорию, двигаться по дерикториям CHANGDIR и ... возврат назад , SHOW - смотреть содержимое, 
// вверху всегда висит путь где находится курсор консоли , все работает я проверял, можно допуск :)))? 
#include <iostream>
#include <chrono>
#include <experimental\filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <conio.h>
#include <direct.h>


#pragma warning(disable : 4996)

using namespace std;
namespace fs = experimental::filesystem;
fs::path p = fs::current_path();
string base = p.string();

//создать file
void NewFile();
// Удалить файл
void DeleteFile();
//Переименовать существующий файл
void RenameFile();
//Удалить существующий файл
void MoveFile();
//Показать содержимое файла
void Show();


int main()

{
	ifstream ifs;
	ofstream ofs;
	string str;
	int command;
	string path1;
	string path2;
	int ch;
	do
	{
		system("CLS");
		cout << "<" << base << ">" << endl;
		cout << "HELLO! CHOSE OBJECT TO WORK WITH:\n1.File.\n2.Directory.\n3.Exit the program..\n";
		cin >> ch;
		switch (ch)
		{
		case 1:
		{
			do {
				//создать
				cout << "\n1 - New file\n";
				//Удалить
				cout << "2 - Delete\n";
				//Переименовать
				cout << "3 - Rename\n";
				//Переместить
				cout << "4 - Move\n";
				//Просмотреть и узнать размер файла
				cout << "5 - Show text in file and it's size \n";
				//Выход
				cout << "0 - Exit to main menu\n\n";
				cin >> ch;
				cin.ignore();
				//анализируем и вызываем
		//соответствующую функцию
				switch (ch)
				{
				case 1:
					NewFile();
					break;
				case 2:
					DeleteFile();
					break;
				case 3:
					RenameFile();
					break;
				case 4:
					MoveFile();
					break;
				case 5:
					Show();
					break;
				
				}
			} while (ch != 0); //Выход из программы
			cout << endl;
			
			break;

		}
		case 2:
		{
			do 
			{
				system("CLS");
				cout << "<" << base << ">";

				cout << "\nCHOSE THE COMMAND:\nCOPY   - 1\nDEL    - 2\nRENAME - 3\nMKDIR  - 4\nCHDIR  - 5\nMOVE   - 6\nSHOW   - 7\n\"../\"  - 8\nSIZE DIR - 9\nEXIT MAIN MENU - 0\n";
				cin >> command;

				switch (command)
				{
				case 1: // COPY 
				{
					cout << "input name DIR to copy FROM \n";
					cin >> path1;
					cout << "input name DIR to copy WHERE\n";
					cin >> path2;

					try {
						fs::copy(base + "\\" + path1,
							base + "\\" + path2,
							fs::copy_options::recursive);
					}
					catch (fs::filesystem_error& e) {
						try {
							fs::copy(path1,
								path2,
								fs::copy_options::recursive);
						}
						catch (fs::filesystem_error& e) {
							try {
								fs::copy(base + "\\" + path1,
									path2,
									fs::copy_options::recursive);
							}
							catch (fs::filesystem_error& e) {
								try {
									fs::copy(path1,
										base + "\\" + path2,
										fs::copy_options::recursive);
								}
								catch (fs::filesystem_error& e) {
									std::cout << e.what() << '\n';
								}
							}
						}
					}
					break;
				}
				case 2: //DEL
				{
					cout << "input name of DIR to DELETE dir\n";
					cin >> path1;
					try {
						fs::remove_all(base + "\\" + path1);
					}
					catch (fs::filesystem_error& e) {
						fs::remove_all(path1);
					}
					break;
				}
				case 3: //RENAME
				{	cout << "input name of DIR  to RENAME FROM  dir\n";
					cin >> path1;
					cout << "input new name of DIR  dir\n";
					cin >> path2;
					try {
						fs::rename(base + "\\" + path1, base + "\\" + path2);
					}
					catch (fs::filesystem_error& e) {
						try {
							fs::rename(path1, path2);
						}
						catch (fs::filesystem_error& e) {
							try {
								fs::rename(base + "\\" + path1, path2);
							}
							catch (fs::filesystem_error& e) {
								try {
									fs::rename(path1, base + "\\" + path2);
								}
								catch (fs::filesystem_error& e) {
									std::cout << e.what() << '\n';
								}
							}
						}
					}
					break;
				}
				case 4: //MKDIR 
				{
					cout << "input NAME of new DIR  \n";
					cin >> path1;
					try {
						fs::create_directories(base + "\\" + path1);
					}
					catch (fs::filesystem_error& e) {
						try {
							fs::create_directories(path1);
						}
						catch (fs::filesystem_error& e) {
							std::cout << e.what() << '\n';
						}
					}
					break;
				}
				case 5: //CHDIR 
				{
					cout << "input DIR to GO  dir\n";
					cin >> path1;
					base = base+"\\"+path1;
					_chdir(base.c_str());
					break;
				}
				case 6: //MOVE
				{
					cout << "input DIR to MOVE FROM  dir\n";
					cin >> path1;
					cout << "input DIR to MOVE WHERE  dir\n";
					cin >> path2;

					try {
						fs::rename(base + "\\" + path1, base + "\\" + path2);
					}
					catch (fs::filesystem_error& e) {
						try {
							fs::rename(path1, path2);
						}
						catch (fs::filesystem_error& e) {
							try {
								fs::rename(base + "\\" + path1, path2);
							}
							catch (fs::filesystem_error& e) {
								try {
									fs::rename(path1, base + "\\" + path2);
								}
								catch (fs::filesystem_error& e) {
									std::cout << e.what() << '\n';
								}
							}
						}
					}
					system("pause");
					break;
				}
				case 7: //SHOW DIR
				{
					for (auto p : fs::recursive_directory_iterator(base))
					{
						auto ftime = fs::last_write_time(p);
						time_t time = std::chrono::system_clock::to_time_t(ftime);
						cout << "Filename: " << p << '\n';
						if (!fs::is_directory(p)) {
							cout << "Size: " << (fs::file_size(p)) / 1024 << " kb , "
								<< (fs::file_size(p)) / 1024 / 1024 << " mb \n";
						}
						cout << "Last modified: " << std::asctime(std::localtime(&time)) << ' ';
					}
					system("pause");
					break;
				}
				case 8: //CHDIR ../
				{
					size_t found = base.find_last_of("\\");
					base = base.substr(0, found);
					break;
				}
				case 9:
				{
					// SHOW SIZE DIR
					int SZD = 0;
					for (auto p : fs::recursive_directory_iterator(base))
					{
						
						
						if (!fs::is_directory(p)) {
							SZD = SZD + (fs::file_size(p)) / 1024;
						}
						
					}
					cout << "Size of directory : " << base << " = " << SZD / 1024 << " kb , "
						<< SZD / 1024 / 1024 << " mb \n";
					system("pause");
					break;
				}
				
				}
			}while (command != 0);
			break;
					   
		}
		case 3:
			cout << "\nBY!BY!\n\n";
			break;
		}
			   		 	  	  	 
	} while (ch != 3);
	   	 	   	 
	system("pause");
	return 0;

}
//создать file
void NewFile()
{

	char name[50];

	cout << "\ninput file name with mask .txt : exaple (file.txt)   ";
	gets_s(name, 50);

	ofstream ofs(name, ios::trunc);
	ofs << (" Hallo World! ");
	ofs.close();
}
//Удалить существующий файл
void DeleteFile()
{

	char name[50];
	cout << "input file name with mask .txt : exaple (file.txt)   ";
	gets_s(name, 50);


	//Удаляем файл и проверяем результат
	if (remove(name) != 0)
		cout << "Error!\n Couldn't remove file.	Check filename...\n";
	else
		cout << "Ok...\n";

}

//Переименовать существующий файл
void RenameFile()
{
	char oldName[50], newName[50];
	//В одной переменной запомним существующее имя
	//(oldName),
	cout << "Enter old name:";
	cin >> oldName;
	//А в другой новое имя(newName)
	cout << "Enter new name:";
	cin >> newName;
	cin.ignore();
	//Произведем переименование и проверку результата
	if (rename(oldName, newName) != 0)
		cout << "Error!\n Couldn't rename file.	Check old and new filename...\n\n";
	else
		cout << "Ok...\n\n";
}

void MoveFile() // перемещает содержимое файла в выбранный файл в указаной папке
{
	char name[50], name_move[50];

	cout << "\ninput file name with mask .txt : exaple (file.txt) which we want to move:   ";
	gets_s(name_move, 50);

	char path[70];
	cout << "\nEnter full path where we must move file (for example, C:\\folder\\ ):";
	gets_s(path, 70);

	cout << "input file name with mask .txt Where we want to move : exaple (file.txt)   ";
	gets_s(name, 50);
	strcat_s(path, name);
	ifstream ifs(name_move);
	ofstream ofs(path, ios::trunc);
	if (!ifs.is_open())
	{
		cout << "\nCan`t open file....\n";
	}
	else
	{
		char ch;
		while (ifs.get(ch))
		{
			ofs << ch << endl;
		}
	}

	ifs.close();
	ofs.close();
	if (remove(name_move) != 0)
		cout << "Error!\n Couldn't remove file.	Check filename...\n";
	else
		cout << "Ok...\n";

}
//Показать содержимое файла
void Show()
{


	char name[50];
	cout << "input file name with expansion .txt : exaple (file.txt)   ";
	gets_s(name, 50);

	ifstream ifs(name);
	if (!ifs.is_open())
	{
		cout << "\nCan`t open file....\n";
	}
	else
	{
		char ch;
		while (ifs.get(ch))
		{
			cout << ch << endl;
		}
		ifstream file(name, ios::binary | ios::ate);
		cout<< "Size of file ="<< file.tellg() <<" byte" ;
	}

}