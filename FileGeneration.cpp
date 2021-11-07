#include "FileGeneration.h"
#define MAX_STRINGS 1
#define MAX_SIGNS 1000
#define MAX_ATR 1000


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
	for (int i = 0; i < MAX_STRINGS; i++)
	{
		fout << "creat ";

		
		name_size = this->rand_num(1, MAX_SIGNS);

		for (int k = 0; k < name_size; k++)
		{
			temp = 'a' + this->rand_num(0, 'z' - 'a');
			fout << temp;
		}

			
		
		fout << '(';
		atr_size = this->rand_num(1, MAX_ATR);
		for (int j = 0; j < atr_size; j++)
		{

			name_size = this->rand_num(1, MAX_SIGNS);
			for (int k = 0; k < name_size; k++)
			{	
					temp = 'a' + this->rand_num(0, 'z' - 'a');
					fout << temp;
			
			}
			if(j!=atr_size-1)
			fout << ',';
		}
		fout << ')'<<std::endl;
	}

	fout.close();
}