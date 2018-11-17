#ifndef FILE_NAME_H
#define FILE_NAME_H
#include <string.h>
#include <iostream>
#include <vector>
#include <io.h>
class File
{
public:
	File();
	~File();
	File(const char* str);
	std::string nextFrame(int stride=1);
	std::string firstFrame(int start=0);

private:
	
	std::string _path;
	bool _isdir = false;
	std::vector<std::string> _files;
	uint8_t _num;
	
};


#endif