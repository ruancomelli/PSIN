#ifndef FILE_READER_TPP
#define FILE_READER_TPP

// Standard
#include <iostream>

namespace psin {

template <class type> 
bool FileReader::readValue( const string & tag, type & value )
{
	string buffer = "NULL";
	bool returnFlag = false;

	if( this->isReady )
	{
		this->file.clear();
		this->file.seekg( 0, std::ios::beg );	// Go to the beginning of the file

		while( psin::stringCompare( buffer, tag ) and !this->file.eof() )	// Search for "tag" inside file
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
			this->file >> value;
			returnFlag = true;
		}

	}
	else
	{
		std::cerr << "FileReader is not ready." << std::endl;
	}

	this->file.clear();

	return returnFlag;
}

} // psin

#endif
