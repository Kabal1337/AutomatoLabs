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



bool CheckStringRegex(string str, vector<Rel>& rels)
{
    bool t = false;
    cmatch m;
    regex regular("(create)[\ ]([a-zA-Z][a-zA-Z0-9]*)[\(]([a-zA-Z][a-zA-Z0-9]*([\,][a-zA-Z][a-zA-Z0-9]*)*)[\)]|([a-zA-Z][a-zA-Z0-9]*)|([a-zA-Z][a-zA-Z0-9]*)[\ ][j][o][i][n][\ ]([a-zA-Z][a-zA-Z0-9]*)");
    try {
        t = regex_match(str.c_str(), m, regular);
        if (t == false) return t;
        
        
    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
    }
    
    if (m[1] == "create")
    {
        Rel rel;
        rel.name = m[2];
        if (m[4] != false)
        {
            std::string str_t;
            std::string atrib;
            str_t = m[3];
           
            int j = 0;
            for (int i = 0; i < str_t.size(); i++)
            {
                if (str_t[i] == ',')
                {
                    
                    rel.atr.push_back(atrib);
                    atrib.clear();
                    continue;
                }
                atrib.push_back(str_t[i]);
            }
            if (atrib.size() != 0) rel.atr.push_back(atrib);
            rels.push_back(rel);
        }
    }
    else if (m[5].str().size()!=0)
    {
   
            for (int i = 0; i < rels.size(); i++)
            {
                if (rels[i].name == m[5])
                {
                    std::cout << rels[i].name << ": ";
                        for (int j = 0; j < rels[i].atr.size(); j++)
                        {
                            if (j != rels[i].atr.size() - 1) cout << rels[i].atr[j] << ',';
                            else
                                cout << rels[i].atr[j] << endl;
                        }
                }
                
            }
        
    }
    else
    {
        int ind_n1 = -1;
        int ind_n2 = -1;
        for (int i = 0; i < rels.size(); i++)
        {
            if (rels[i].name == m[6])
            {
                ind_n1 = i;
            }
            if (rels[i].name == m[7])
            {
                ind_n2 = i;
            }
        }
        if (ind_n2 == -1 || ind_n1 == -1)
        {
            std::cout << "There is no such relation" << std::endl;
            return t;
        }
        std::cout << "Atributs of " << m[6] << " and " << m[7] << ": ";


        for (int j = 0; j < rels[ind_n1].atr.size(); j++)
        {
            bool same = false;
            for (int i = 0; i < rels[ind_n2].atr.size(); i++)
            {
                if (rels[ind_n1].atr[j] == rels[ind_n2].atr[i])
                {
                    same = true;
                }


            }
            if (same == false) std::cout << rels[ind_n1].atr[j] << ", ";
            else  std::cout << rels[ind_n1].atr[j] << "." << m[6] << ", ";
        }
        for (int j = 0; j < rels[ind_n2].atr.size(); j++)
        {
            bool same = false;
            for (int i = 0; i < rels[ind_n1].atr.size(); i++)
            {
                if (rels[ind_n2].atr[j] == rels[ind_n1].atr[i])
                {
                    same = true;
                }


            }
            if (same == false) std::cout << rels[ind_n2].atr[j] << ", ";
            else  std::cout << rels[ind_n2].atr[j] << "." << m[7] << ", ";
        }
    }
    return t;
    
}

int main()
{
    vector<Rel> rels;
    FileGeneration fg;
    fg.generate("test.txt");

    clock_t start, stop;

    std::ifstream fin;
    fin.open("test.txt", ios_base::in);

    std::ofstream fout;
    fout.open("time.txt", ios_base::app);

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
   AppClass thisContext;
   while (1)
   {
       
        //fin >> word;
        std::string temp;
        //fin >> temp;
       /* word += ' ';
        word += temp;*/
        std::string argv;
        //getline(cin, argv);
        if (!getline(fin, argv)) break;
        int index = 0;
        //int argc = word.length();
        int argc = argv.length();
        
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
                thisContext.SetStr(argv);
                //isAcceptable = thisContext.CheckString(word.c_str());
                isAcceptable = thisContext.CheckString(argv);
                cmatch m;
                //isAcceptable = CheckStringRegex(argv, rels);
                for (int i = 0; i < m.size(); i++) cout << m[i] << endl;
                stop = clock();
                if (!isAcceptable)
                {
                    //fout << index << " is not acceptable, " << "time: " << (stop - start)<< endl;
                    cout << argv << " is not acceptable, " << std::endl;
                    fout << (stop - start) << endl;
                    
                }
                else
                {
                    //fout << index << " is acceptable, " << "time: " << (stop - start) << endl;
                    cout<< argv << " is acceptable, " << std::endl;
                    fout << (stop - start) << endl;
                   

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
   }
    fin.close();
    fout.close();
       // return retcode;
    
}



