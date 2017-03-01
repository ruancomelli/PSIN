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

// boost
#include <boost/any.hpp>

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

		template <class type> bool readValue( const string & tag, type & value );

		bool readAnyValue( const string & tag, boost::any & value, bool (*inputMethod)(ifstream & in, boost::any & value) );
		
	private:
		string fileName;
		ifstream file;
		bool isReady;
};

#include <FileReader.tpp>

#endif
