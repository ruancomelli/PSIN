
template <class type> 
void FileReader::readValue( const char* tag, type & value )
{
	char buffer[800] = "NULL";

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
			this->file >> value;
		}

	}
	else
	{
		cerr << "FileReader is not ready." << endl;
	}

	this->file.clear();
}