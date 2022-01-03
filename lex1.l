%{
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <string.h>
#include<stdbool.h>


FILE* out;
extern FILE* yyin;
int num = 0, res;
int start, stop;
int size = 4;
static void AddRel(const char* RelName)
{
	out = fopen("rellist.txt", "a+");
	fprintf(out, "%s\n", RelName);
	fclose(out);
	//size++;
}

char* f_readln(FILE* file)
{
	
	 char *ptr = (char*)malloc(1 * sizeof(char*));
	 *ptr = NULL;
	char buf[10];
	int n, len = 0;
	do {
		n = fscanf(file, "%9[^\n]", buf);
		if (n == -1)
		{
			return NULL;
		}
		if (n == 0)
			fscanf(file, "%*c");
		else
		{
			len = len + strlen(buf) + 1;
			ptr = (char*)realloc(ptr, len);
			strcat(ptr, buf);
		}

	} while (n > 0);
	if (ptr[0] == '\0') ptr = NULL;

	return ptr;
}

char* Get_Name(char* Rel)
{
	char* ptr = (char*)malloc(strlen(Rel) * sizeof(char));
	*ptr = NULL;
	for (int i = 0; i < strlen(Rel); i++)
	{
		if (Rel[i] == '(') break;
		char buf[] = { Rel[i], '\0' };
		strcat(ptr, buf);
	}
	return ptr;
}
static void ShowRel(const char* RelName)
{
	
	FILE* in = fopen("rellist.txt", "r");
	bool join = false;
	char* name1 = (char*)malloc(strlen(RelName) * sizeof(char));
	char* name2 = (char*)malloc(strlen(RelName) * sizeof(char));
	*name1 = NULL;
	*name2 = NULL;
	
	for (int i = 0; i < strlen(RelName); i++)
	{
		char buf1[] = { RelName[i], '\0' };
		
		if (RelName[i] == ' ')
		{
			join = true;
			for (int j = i+6; j < strlen(RelName); j++)
			{
				char buf2[] = { RelName[j], '\0' };
				strcat(name2, buf2);
			}
			break;
		}
		strcat(name1, buf1);

	}
	char** arr = (char**)malloc(size * sizeof(char*));
	if (join == false)
	{
		

		
		for (int i = 0; i < size; i++)
		{

			char* temp = f_readln(in);
			
			//printf("%s", temp);
			arr[i] = (char*)malloc(strlen(temp) * sizeof(char));
			arr[i] = temp;
		}

		for (int i = 0; i < size; i++)
		{
			
			char* temp = (char*)malloc(strlen(arr[i]) * sizeof(char));
			*temp = NULL;
			//int len = 0;
			
			for (int j = 0; j < (strlen(arr[i])); j++)
			{
				
				if (arr[i][j] == '(') break;
				//len++;
				char buf[] = { arr[i][j], '\0' };
				// temp = (char*)realloc(temp, len);
				
				strcat(temp, buf);

			}
			if (strcmp(temp, RelName) == 0)
			{
				printf("%s", arr[i]);
				return;
				
			}
		}
		printf("No such relation");
	}
	else
	{
		for (int i = 0; i < size; i++)
		{

			char* temp = f_readln(in);

			//printf("%s", temp);
			arr[i] = (char*)malloc(strlen(temp) * sizeof(char));
			arr[i] = temp;
		}
		int ind_n1 = -1;
		int ind_n2 = -1;

		for (int i = 0; i < size; i++)
		{
			if (strcmp(Get_Name(arr[i]), name1)==0)
			{
				ind_n1 = i;
			}
			if (strcmp(Get_Name(arr[i]), name2)==0)
			{
				ind_n2 = i;
			}
		}
		if (ind_n2 == -1 || ind_n1 == -1)
		{
			printf("There is no such relation");
			return;
			
		}
		printf("Atributs of ");
		printf("%s", name1); printf(" and "); printf("%s", name2); printf(": ");
		
		char** atr1 = (char**)malloc(size+1 * sizeof(char*));
		int atr1_size = 0;
		int m = 0;
		int k = 0;
		while (arr[ind_n1][k] != '(') 
			k++;
		k++;
		atr1[m] = (char*)malloc(strlen(arr[ind_n1]) * sizeof(char));
		*atr1[m] = NULL;
		for (int i = k; i < strlen(arr[ind_n1]); i++)
		{
			
			if (arr[ind_n1][i] != ',' && arr[ind_n1][i] != ')')
			{
				char t_atr[] = { arr[ind_n1][i], '\0' };
				
				
				strcat(atr1[m], t_atr);
			}
			else
			{
				atr1_size++;
				m++;
				atr1[m] = (char*)malloc(strlen(arr[ind_n1]) * sizeof(char));
				*atr1[m] = NULL;
			}
		}
		char** atr2 = (char**)malloc(size * sizeof(char*));
		int atr2_size = 0;
		m = 0;
		k = 0;
		while (arr[ind_n2][k] != '(') 
			k++;
		k++;
		atr2[m] = (char*)malloc(strlen(arr[ind_n1]) * sizeof(char));
		*atr2[m] = NULL;
		for (int i = k; i < strlen(arr[ind_n2]); i++)
		{
			if (arr[ind_n2][i] != ',' && arr[ind_n2][i] != ')')
			{
				char t_atr[] = { arr[ind_n2][i], '\0' };
				
				
				strcat(atr2[m], t_atr);
				
			}
			else
			{
				atr2_size++;
				m++;
				atr2[m] = (char*)malloc(strlen(arr[ind_n2]) * sizeof(char));
				*atr2[m] = NULL;
			}
		}
		
		
		for (int j = 0; j < atr1_size; j++)
		{
			bool same = false;
			for (int i = 0; i < atr2_size; i++)
			{
				if (strcmp(atr1[j], atr2[i])==0)
				{
					same = true;
				}


			}
			if (same == false) { printf("%s", atr1[j]);  printf(", "); }
			else { printf("%s", atr1[j]); printf("."); printf("%s", name1); printf(", ");}
		}
		for (int j = 0; j < atr2_size; j++)
		{
			bool same = false;
			for (int i = 0; i < atr2_size; i++)
			{
				if (strcmp(atr2[j], atr1[i]) == 0)
				{
					same = true;
				}


			}
			if (same == false) { printf("%s", atr2[j]);  printf(", "); }
			else { printf("%s", atr2[j]); printf("."); printf("%s", name2); printf(", "); }
		}
	}
}
%}
REG_BEGIN_C [c][r][e][a][t]
REG_BEGIN_J [a-zA-Z][a-zA-Z0-9]*
VAR1 [a-zA-Z][a-zA-Z0-9]*[\(][a-zA-Z][a-zA-Z0-9]*([\,][a-zA-Z][a-zA-Z0-9]*)*[\)]
VAR2 [a-zA-Z][a-zA-Z0-9]*|[a-zA-Z][a-zA-Z0-9]*[\ ][j][o][i][n][\ ][a-zA-Z][a-zA-Z0-9]*
EXP [&|\||\^]?
%x REG1
%x REG2
%x PRS1
%x PRS2
%%
{REG_BEGIN_C} {yyless(0); BEGIN(REG1);}
{REG_BEGIN_J} {yyless(0); BEGIN(REG2);}
<REG1>[c][r][e][a][t][\ ][a-zA-Z][a-zA-Z0-9]*[\(][a-zA-Z][a-zA-Z0-9]*([\,][a-zA-Z][a-zA-Z0-9]*)*[\)] {printf("Correct: %s\n",yytext); yyless(0); BEGIN(PRS1);}
<REG1>. {REJECT;}
<REG2>[a-zA-Z][a-zA-Z0-9]*|[a-zA-Z][a-zA-Z0-9]*[\ ][j][o][i][n][\ ][a-zA-Z][a-zA-Z0-9]* {printf("Correct: %s\n",yytext); yyless(0); BEGIN(PRS2);}
<REG2>. {REJECT;}
<PRS1>"creat"	{}
<PRS1>{VAR1}	{AddRel(yytext); BEGIN(INITIAL);}
<PRS2>{VAR2}  {ShowRel(yytext);}


%%
int main() {
printf("Working\n");

yyin = fopen("test.txt", "r");
out = fopen("yyout.txt", "w");

while(1)
{
start = clock();
res = yylex();
stop = clock();

if (!res) break;
fprintf(out, "%d ", stop);
fprintf(out, "%d ", start);
fprintf(out, "%d ", num);
fprintf(out, "time: %d", (stop-start));
num++;
}

printf("End Work\n");
return 0;
}