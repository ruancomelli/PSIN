#include <FileReader.h>

// Standard
#include <iostream>
#include <stdexcept>

// UtilsLib
#include <vectorIO.h>

// Constructor
FileReader::FileReader()
{
	this->isReady = false;
}

FileReader::FileReader(const string & fileName)
{
	this->isReady = false;
	openFile(fileName);
}

// Destructor
FileReader::~FileReader()
{
	this->file.close();
}

void FileReader::setFileName(const string & fileName)
{
	this->fileName = fileName;
}

string FileReader::getFileName(void) const
{
	return this->fileName;
}

bool FileReader::checkReady(void) const
{
	return this->isReady;
}

void FileReader::openFile(const string & fileName)
{
	this->fileName.clear();
	this->file.clear();

	if( !fileName.empty() ){

		this->file.open( fileName.c_str() );

		if( this->file.fail() )
		{
			std::cerr << "There is no file " << fileName << std::endl;
			this->isReady = false;
		}
		else
		{
			this->fileName = fileName;
			this->isReady = true;
		}
	}
	else
	{
		std::cerr << "Invalid fileName." << std::endl;
		this->isReady = false;
	}
}

bool FileReader::readAnyValue( const string & tag, Any & value, inputMethodType inputMethod )
{
	string buffer = "NULL";
	bool returnFlag = false;

	if( this->isReady )
	{
		this->file.clear();
		this->file.seekg( 0, std::ios::beg );	// Go to the beginning of the file

		while( stringCompare( buffer, tag ) && !this->file.eof() )	// Search for "tag" inside file
		{
			this->file >> buffer;
		}

		if( this->file.eof() )
		{ 
			std::cerr << "There is no " << tag << " in the file" << std::endl
					<< "Argument value not modified." << std::endl;
		}
		else
		{
			returnFlag = inputMethod( this->file, value );
		}

	}
	else
	{
		std::cerr << "FileReader is not ready." << std::endl;
	}

	this->file.clear();

	return returnFlag;
}