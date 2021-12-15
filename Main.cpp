//
// The contents of this file are subject to the Mozilla Public
// License Version 1.1 (the "License"); you may not use this file
// except in compliance with the License. You may obtain a copy of
// the License at http://www.mozilla.org/MPL/
// 
// Software distributed under the License is distributed on an "AS
// IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
// implied. See the License for the specific language governing
// rights and limitations under the License.
// 
// The Original Code is State Machine Compiler (SMC).
// 
// The Initial Developer of the Original Code is Charles W. Rapp.
// Portions created by Charles W. Rapp are
// Copyright (C) 2000 - 2003 Charles W. Rapp.
// All Rights Reserved.
// 
// Contributor(s): 
//
// Function
//	Main
//
// Description
//  This routine starts the finite state machine running.
//
// RCS ID
// $Id$
//
// CHANGE LOG
// $Log$
// Revision 1.10  2014/09/07 07:19:00  fperrad
// exception const reference
//
// Revision 1.9  2014/09/06 19:53:15  fperrad
// remove hard tab
//
// Revision 1.8  2014/07/12 10:48:49  fperrad
// remove _rcs_id
//
// Revision 1.7  2006/06/03 19:39:24  cwrapp
// Final v. 4.3.1 check in.
//
// Revision 1.6  2006/04/22 12:45:24  cwrapp
// Version 4.3.1
//
// Revision 1.5  2005/06/08 11:09:12  cwrapp
// + Updated Python code generator to place "pass" in methods with empty
//   bodies.
// + Corrected FSM errors in Python example 7.
// + Removed unnecessary includes from C++ examples.
// + Corrected errors in top-level makefile's distribution build.
//
// Revision 1.4  2005/05/28 13:31:16  cwrapp
// Updated C++ examples.
//
// Revision 1.1  2004/09/06 15:23:39  charlesr
// Updated for SMC v. 3.1.0.
//
// Revision 1.0  2003/12/14 19:12:12  charlesr
// Initial revision
//
#ifndef _REGEX_MAX_COMPLEXITY_COUNT
#define _REGEX_MAX_COMPLEXITY_COUNT   0   /* set to 0 to disable */
#endif /* _REGEX_MAX_COMPLEXITY_COUNT */

#ifndef _REGEX_MAX_STACK_COUNT
#ifdef _WIN64
#define _REGEX_MAX_STACK_COUNT   0    /* set to 0 to disable */
#else /* _WIN64 */
#define _REGEX_MAX_STACK_COUNT   0   /* set to 0 to disable */
#endif /* _WIN64 */
#endif /* _REGEX_MAX_STACK_COUNT */
#include "AppClass.h"
#include "FileGeneration.h"
#include <string>
#include <vector>
#include <regex>
#include "AppClass.cpp"

#define _CRT_SECURE_NO_WARNINGS

using namespace std;
using namespace statemap;

struct Rel
{
    string name;
    string atr;
};
vector<Rel> rels;
bool CheckStringRegex(string str)
{
    try {
        regex regular("[c][r][e][a][t][\ ][a-zA-Z][a-zA-Z0-9]*[\(][a-zA-Z][a-zA-Z0-9]*([\,][a-zA-Z][a-zA-Z0-9]*)*[\)]|[a-zA-Z][a-zA-Z0-9]*|[a-zA-Z][a-zA-Z0-9]*[\ ][j][o][i][n][\ ][a-zA-Z][a-zA-Z0-9]*");
        return regex_match(str.c_str(), regular);
    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
    }

}
int main()
{
    
    FileGeneration fg;
    fg.generate("test.txt");

    clock_t start, stop;

    std::ifstream fin;
    fin.open("test.txt", ios_base::in);

    std::ofstream fout;
    fout.open("time.txt", ios_base::out);

    if (!fin.is_open())
    {
        cout << "Can`t open the test.txt!" << endl;
        return -1;
    }

    if (!fout.is_open())
    {
        cout << "Can`t open the time.txt!" << endl;
        return -2;
    }
    string word;
    
   // while (!fin.eof())
   // {
        fin >> word;
        std::string temp;
        fin >> temp;
       /* word += ' ';
        word += temp;*/
        std::string argv;
        getline(cin, argv);
        int index = 0;
        //int argc = word.length();
        int argc = argv.length();
        AppClass thisContext;
        bool isAcceptable;
        //thisContext.SetStr(argv);
        int retcode = 0;

        if (argc == 0)
        {
            cerr << "No string to check." << endl;
            retcode = 2;
        }
        else if (argc == 1)
        {
            cerr << "Only one argument is accepted." << endl;
            retcode = 3;
        }
        else
        {
            //cout << "The string \"" << word << "\" is ";

            try
            {
                /*if(regex_match(word.c_str(), result, regular)==false)
                cout << "In regex: " << "false" << endl;
                else  cout << "In regex: " << "true" << endl;*/
                start = clock();
                //isAcceptable = thisContext.CheckString(word.c_str());
                isAcceptable = thisContext.CheckString(argv);
                //isAcceptable = CheckStringRegex(word);
                stop = clock();
                if (!isAcceptable)
                {
                    //fout << index << " is not acceptable, " << "time: " << (stop - start)<< endl;
                    cout << " is not acceptable, " << std::endl;
                    index++;

                }
                else
                {
                    //fout << index << " is acceptable, " << "time: " << (stop - start) << endl;
                    cout << " is acceptable, " << std::endl;
                    index++;
                    //if (argv[0] == 'c' && argv[1] == 'r' && argv[2] == 'e' && argv[3] == 'a' && argv[4] == 't')
                    //{
                    //    Rel rel;
                    //    int i = 0;
                    //    while (argv[i] != ' ') i++;
                    //    i++;
                    //    while (argv[i] != '(')
                    //    {

                    //        rel.name.push_back(argv[i]);
                    //        i++;
                    //    }
                    //    i++;
                    //    while (argv[i] != ')') 
                    //    {
                    //        rel.atr.push_back(argv[i]);
                    //        i++;
                    //    }
                    //    rels.push_back(rel);
                    //    //cout << "name: " << rels[0].name;
                    //}
                    //else 
                    //{
                    //    
                    //    string name1;
                    //    string name2;
                    //    int i = 0;
                    //    
                    //    while(argv[i] != '[')
                    //    {
                    //        name1.push_back(argv[i]);
                    //        i++;
                    //        
                    //    }
                    //    i++;
                    //    while (argv[i] != ']') 
                    //    {
                    //        name2.push_back(argv[i]);
                    //        i++;
                    //    }
                    //    //cout << name1 << ' ' << name2 << endl;
                    //    if (name1 == "" || name2 == "")
                    //    {
                    //        if (name1 != "")
                    //            for (int i = 0; i < rels.size(); i++)
                    //            {
                    //                if (rels[i].name == name1) cout << "name: " << name1 << endl << "atributes: " << rels[i].atr<<endl;
                    //            }
                    //        if (name2 != "")
                    //            for (int i = 0; i < rels.size(); i++)
                    //            {
                    //                if (rels[i].name == name1) cout << "name: " << name1 << endl << "atributes: " << rels[i].atr<<endl;
                    //            }
                    //    }
                    //    else
                    //    {
                    //        cout << "Relations names: " << name1 << ", " << name2 << endl;
                    //        for (int i = 0; i < rels.size(); i++)
                    //        {
                    //            if (rels[i].name == name1) cout << rels[i].atr << ", ";
                    //            if (name2 != name1) if (rels[i].name == name2) cout << rels[i].atr << endl;
                    //        }

                    //    }
                    //}

                }
            }
            catch (const SmcException& smcex)
            {
                cout << "not acceptable - "
                    << smcex.what()
                    << '.'
                    << endl;

                retcode = 1;
            }
        }
   // }
    fin.close();
    fout.close();
       // return retcode;
    
}



