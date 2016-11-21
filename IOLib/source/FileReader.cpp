#include <FileReader.h>

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

void FileReader::openFile(const string & fileName)
{
	this->fileName.clear();
	this->file.clear();

	if( !fileName.empty() ){

		this->file.open( fileName.c_str() );

		if( this->file.fail() )
		{
			cerr << "There is no file " << fileName << endl;
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
		cerr << "Invalid fileName." << endl;
		this->isReady = false;
	}
}