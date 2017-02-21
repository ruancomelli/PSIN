
template <class type> 
bool FileReader::readValue( const string & tag, type & value )
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
			this->file >> value;
			returnFlag = true;
		}

	}
	else
	{
		cerr << "FileReader is not ready." << endl;
	}

	this->file.clear();

	return returnFlag;
}

