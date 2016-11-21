#ifndef FILE_READER_H
#define FILE_READER_H

// Standard
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <string>

using namespace std;

class FileReader
{
	public:
		FileReader();
		FileReader(const string & fileName);
		virtual ~FileReader();
			

		void setFileName(const string & fileName);
		string getFileName(void) const;

		bool checkReady(void){ return this->isReady; }

		void openFile(const string & fileName);

		template <class type> void readValue( const char* tag, type & value )
		{
			char buffer[800] = "NULL";

			if( this->isReady )
			{
				this->file.seekg( 0, ios::beg );	// Go to the beginning of the file

				while( strcmp( buffer, tag ) && !this->file.eof() )	// Search for "tag" inside file
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
		
	private:
		string fileName;
		ifstream file;
		bool isReady;
};

#endif
