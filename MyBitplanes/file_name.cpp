#include "file_name.h"
#include <cctype>
#include <string>
using namespace std;
void findfile(string path, vector<string>& files, string mode)
{
	_finddata_t file;
	intptr_t HANDLE;
	string Onepath = path + "\\" + mode;
	HANDLE = _findfirst(Onepath.c_str(), &file);
	if (HANDLE == -1L)
	{
		cout << "can not match the folder path" << endl;
		system("pause");
	}
	do {
		//判断是否有子目录  
		if (file.attrib & _A_SUBDIR)
		{
			//判断是否为"."当前目录，".."上一层目录
			if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0))
			{
				string newPath = path + "\\" + file.name;
				findfile(newPath, files, mode);
			}
		}
		else
		{
			files.push_back(file.name);
		}
	} while (_findnext(HANDLE, &file) == 0);
	_findclose(HANDLE);
}

File::File(const char* str)
{
	//FILE* ff;
	_path = str;
	//bool fo = fopen_s(&ff, str, "r");
	//if (!fopen_s(&ff, str, "r")) {
	//	_isdir = true;
	//	
	string mode = "*.*";
	findfile(str, _files,mode);
		
	
}

std::string File::firstFrame(int start)
{
	_num = start;
	return _path + "\\" + _files[start];
}


std::string File::nextFrame(int stride)
{
	std::string str;
	_num = _num + stride;

	return _path+"\\"+_files[_num];
}

File::File()
{
}

File::~File()
{
}