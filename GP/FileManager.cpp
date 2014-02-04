// FileManager.cpp

#include "stdafx.h"

#include "FileManager.h"
#include <iostream>

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

bool FileManager::Write(const std::string &_filename, std::string _value)
{
	return DoWrite(_filename, _value, false);
}

bool FileManager::Append(const std::string &_filename, std::string _value)
{
	return DoWrite(_filename, _value, true);
}

bool FileManager::DoWrite(const std::string &_filename, std::string _value, bool _append)
{
	std::ofstream stream;

	if ( _append)
	stream.open(_filename, std::ios::out | std::ios::app);
	else stream.open(_filename);

	if ( stream.is_open())
	{
		stream << _value;

		stream.flush();
		stream.close();
		return true;
	}

	stream.flush();
	stream.close();
	return false;
}

std::string FileManager::Read(const std::string &_filename, const int _line)
{
	std::ifstream stream;

	stream.open(_filename);
	if (stream.is_open())
	{
		unsigned int i = 0;
		std::string temp;
		while( !stream.eof() )
		{
			std::getline(stream, temp,'\n');

			if ( i == _line)
			{
				stream.close();
				return temp;
			}
			i++;
		}
	}

	stream.close();
	return "";
}