// FileManager.h

#pragma once

#include "stdafx.h"

class ofstream;

class FileManager
{
public:
	FileManager();
	~FileManager();

	bool Write(const std::string &_filename, std::string _value);
	std::string Read(const std::string &_filename, const int _line);

	bool Append(const std::string &_filename, std::string _value);
private:
	bool DoWrite(const std::string &_filename, std::string _value, bool _append);
};