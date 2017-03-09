#ifndef FILE_READER_H
#define FILE_READER_H

// Standard
#include <fstream>
#include <string>

// UtilsLib
#include <Any.h>
#include <StringUtils.h>
#include <vectorIO.h>

using std::string;

class FileReader
{
	public:
		typedef bool (*InputMethodType)(std::ifstream & in, Any & value);

		FileReader();
		FileReader(const string & fileName);
		virtual ~FileReader();
			

		void setFileName(const string & fileName);
		string getFileName(void) const;

		bool checkReady(void) const;

		void openFile(const string & fileName);

		template <class type> 
		bool readValue( const string & tag, type & value );

		bool readAnyValue( const string & tag, Any & value, InputMethodType inputMethod );
		
	private:
		string fileName;
		std::ifstream file;
		bool isReady;
};

#include <FileReader.tpp>

#endif
