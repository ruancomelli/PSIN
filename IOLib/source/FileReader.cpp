#include <FileReader.h>

// Constructor
FileReader::FileReader()
{
	this->isReady = false;
}

FileReader::FileReader(const string fileName)
{
	this->isReady = false;
	openFile(fileName);
}

// Destructor
FileReader::~FileReader()
{
	this->file.close();
}

void FileReader::setFileName(const string fileName)
{
	this->fileName = fileName;
}

string FileReader::getFileName(void) const
{
	return this->fileName;
}

void FileReader::openFile(const string fileName)
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

bool FileReader::readAnyValue( const string & tag, boost::any & value, bool (*inputMethod)(ifstream & in, boost::any & value) )
{
	string buffer = "NULL";
	bool returnFlag = false;

	if( this->isReady )
	{
		this->file.clear();
		this->file.seekg( 0, ios::beg );	// Go to the beginning of the file

		while( stringCompare( buffer, tag ) && !this->file.eof() )	// Search for "tag" inside file
		{
			this->file >> buffer;
		}

		if( this->file.eof() )
		{ 
			cerr << "There is no " << tag << " in the file" << endl
					<< "Argument value not modified." << endl;
		}
		else
		{
			returnFlag = inputMethod( this->file, value );
		}

	}
	else
	{
		cerr << "FileReader is not ready." << endl;
	}

	this->file.clear();

	return returnFlag;
}