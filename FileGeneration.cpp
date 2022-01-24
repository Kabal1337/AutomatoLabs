#include "FileGeneration.h"
#define MAX_STRINGS 1
#define MAX_SIGNS 100
#define MAX_ATR 100


int FileGeneration::rand_num(int first, int last)
{
	return (first + rand() % last);
}

void FileGeneration::generate(std::string file_name)
{
	std::ofstream fout;
	fout.open(file_name, std::ios_base::out);

	char temp;
	int name_size;
	int atr_size;
	int mist;
	for (int i = 0; i < MAX_STRINGS; i++)
	{
		fout << "create ";

		
		name_size = this->rand_num(1, MAX_SIGNS);
		mist = this->rand_num(0, 10);
		if (mist == 1)
		{
			name_size++;
			temp = '1';
			fout << temp;
		}
		for (int k = 0; k < name_size; k++)
		{
			
			temp = 'a' + this->rand_num(0, 'z' - 'a');
			fout << temp;
		}

			
		mist = this->rand_num(0, 10);
		if (mist != 1)
		fout << '(';
		atr_size = this->rand_num(1, MAX_ATR);
		for (int j = 0; j < atr_size; j++)
		{
			mist = this->rand_num(0, 10);
			if (mist == 1)
			{
				name_size++;
				temp = '1';
				fout << temp;
			}
			name_size = this->rand_num(1, MAX_SIGNS);
			for (int k = 0; k < name_size; k++)
			{		
					
					temp = 'a' + this->rand_num(0, 'z' - 'a');
					fout << temp;
			
			}
			if(j!=atr_size-1)
			fout << ',';
		}
		mist = this->rand_num(0, 10);
		if (mist != 1)
		fout << ')'<<std::endl;
	}

	fout.close();
}

