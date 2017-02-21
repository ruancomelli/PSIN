#ifndef FILE_READER_H
#define FILE_READER_H

// Standard
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

// UtilsLib
#include <vectorIO.h>
#include <StringUtils.h>

using namespace std;

class FileReader
{
	public:
		FileReader();
		FileReader(const string fileName);
		virtual ~FileReader();
			

		void setFileName(const string fileName);
		string getFileName(void) const;

		bool checkReady(void){ return this->isReady; }

		void openFile(const string fileName);

		template <class type> void readValue( const char* tag, type & value );
		
	private:
		string fileName;
		ifstream file;
		bool isReady;
};

#include <FileReader.tpp>

#endif
