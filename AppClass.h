#ifndef _H_THECONTEXT
#define _H_THECONTEXT

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
// Name
//	AppClass
//
// Description
//	When a state map executes an action, it is really calling a
//	member function in the context class.
//
// RCS ID
// $Id$
//
// CHANGE LOG
// $Log$
// Revision 1.6  2015/08/02 19:44:34  cwrapp
// Release 6.6.0 commit.
//
// Revision 1.5  2014/09/06 19:53:15  fperrad
// remove hard tab
//
// Revision 1.4  2005/05/28 13:31:16  cwrapp
// Updated C++ examples.
//
// Revision 1.0  2003/12/14 19:11:44  charlesr
// Initial revision
//

#include "AppClass_sm.h"

#include <string>
#include <vector>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
#ifdef CRTP
class AppClass : public AppClassContext<AppClass>
#else

class AppClass
#endif
{
private:
#ifndef CRTP
    AppClassContext _fsm;
#endif
    std::string str;
    bool isAcceptable;
    struct Rel
    {
        std::string name;
        std::vector<std::string> atr;
    };
    std::vector<Rel> rels;
       

public:
    inline AppClass();
        // Default constructor.

    ~AppClass() {};
        // Destructor.

    inline bool CheckString(std::string str);
      
    inline void Acceptable()
    { isAcceptable = true; };

    inline void Unacceptable()
    { isAcceptable = false; };
    inline void SetStr(std::string str) 
    {
        this->str = str;
    }
    inline void AddRel(std::string t_string) 
    {
        Rel rel;
        int i = 0;
        while (t_string[i] != ' ') i++;
        i++;
        while (t_string[i] != '(')
        {

            rel.name.push_back(t_string[i]);
            i++;
        }
        i++;
        
        while (t_string[i] != ')')
        {   
            int j = 0;
            std::string atribute;
            while (t_string[i] != ')' && t_string[i] != ',')
            {
                int j = 0;
                
                atribute.push_back(t_string[i]);
                
                i++;
                j++;
            }
            if(atribute.length()!=0)
                rel.atr.push_back(atribute);
            else if(t_string[i] != ')')
                i++;
        }
        rels.push_back(rel);
        for (int i = 0; i < rels.size(); i++)
        {
            std::cout << rels[i].name << "(";
            for (int j = 0; j < rels[i].atr.size(); j++)
            {
                std::cout << rels[i].atr[j];
            }
            std::cout << ")" << std::endl;
        }

    }
    inline bool CheckCreat(std::string t_string, int &index)
    {
        if (t_string[0]=='c' && t_string[1] == 'r' && t_string[2] == 'e' && t_string[3] == 'a' && t_string[4]=='t')
        {
            
            index += 5;
            return true;
        }
        else return false;
    }
    inline bool CheckJoin(std::string t_string, int &index)
    {
        int i = 0;
        while (t_string[i] != ' ') 
        {
            i++;
        }
        i++;
        int j = i;
        int n = 0;
            while (t_string[j] != ' ' && t_string[i] != '\0')
            {
                j++;
                n++;
            }
        if (n < 4) return false;
        else if (t_string[i] == 'j' && t_string[i + 1] == 'o' && t_string[i + 2] == 'i' && t_string[i + 3] == 'n')
        {
            index += 4;
            return true;
        }
        else return false;
    }
    inline void ShowRels(std::string name1)
    {
        
        for (int i = 0; i < rels.size(); i++)
        {
            if (rels[i].name == name1)
            {
                std::cout << "Atributes of " << rels[i].name << ": ";
                for (int j = 0; j < rels[i].atr.size(); j++)
                {
                    if (j != rels[i].atr.size() - 1)
                        std::cout << rels[i].atr[j] << ',';
                    else std::cout << rels[i].atr[j] << std::endl;
                }
                return;
            }
        }
        std::cout << "There is no such relation" << std::endl;
    }
    inline void ShowRels(std::string name1, std::string name2)
    {
        int ind_n1=-1;
        int ind_n2=-1;
        for (int i = 0; i < rels.size(); i++)
        {
            if (rels[i].name == name1)
            {
               ind_n1 = i;
            }
            if (rels[i].name == name1)
            {
                ind_n2 = i;
            }
        }
        if (ind_n2 == -1 || ind_n1 == -1)
        {
            std::cout << "There is no such relation" << std::endl;
            return;
        }
        std::cout << "Atributs of " << name1 << " and " << name2;
       
        
        for (int j = 0; j < rels[ind_n1].atr.size(); j++)
        {
            bool same = false;
            for (int i = 0; i < rels[ind_n2].atr.size(); i++)
            {
                if (rels[ind_n1].atr[j] == rels[ind_n2].atr[i])
                {
                    std::cout << rels[ind_n1].atr[j] << "." << rels[ind_n1].name<<",";
                    same = true;
                }
                if (same == false) std::cout << rels[ind_n1].atr[j] << ",";

            }
            for (int i = 0; i < rels[ind_n1].atr.size(); i++)
            {
                if (rels[ind_n1].atr[j] == rels[ind_n2].atr[i])
                {
                    std::cout << rels[ind_n2].atr[j] << "." << rels[ind_n2].name << ",";
                    same = true;
                }
                if (same == false) std::cout << rels[ind_n2].atr[j] << ",";

            }
        }
    };
};

#endif
