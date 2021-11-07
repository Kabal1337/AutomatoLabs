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
        // If a string is acceptable, then this variable is set to YES;
        // NO, otherwise.

public:
    inline AppClass();
        // Default constructor.

    ~AppClass() {};
        // Destructor.

    inline bool CheckString(const char*);
      
    inline void Acceptable()
    { isAcceptable = true; };

    inline void Unacceptable()
    { isAcceptable = false; };
    inline void SetStr(std::string str) 
    {
        this->str = str;
    }
    inline void AddRel();
    inline void ShowRels(std::string name1);
    inline void ShowRels(std::string name1, std::string name2);
};

#endif
