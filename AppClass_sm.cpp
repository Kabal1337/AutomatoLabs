//
// ex: set ro:
// DO NOT EDIT.
// generated by smc (http://smc.sourceforge.net/)
// from file : AppClass.sm
//


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
// State Map
//	This state map is recognizes the regular expression 0*1*.
//
// RCS ID
// $Id$
//
// CHANGE LOG
// $Log$
// Revision 1.5  2005/05/28 13:31:16  cwrapp
// Updated C++ examples.
//
// Revision 1.1  2005/02/21 14:19:18  charlesr
// Added spaces around header file name to test SMC.
//
// Revision 1.0  2003/12/14 19:11:57  charlesr
// Initial revision
//


#include "AppClass.h"
#include "D:\AutomatoLabs\Test\AppClass_sm.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace statemap;

// Static class declarations.
Map1_Start Map1::Start("Map1::Start", 0);
Map1_Creat_Rel Map1::Creat_Rel("Map1::Creat_Rel", 1);
Map1_See_Rel Map1::See_Rel("Map1::See_Rel", 2);
Map1_Space_See_Rel Map1::Space_See_Rel("Map1::Space_See_Rel", 3);
Map1_Join Map1::Join("Map1::Join", 4);
Map1_First_Letter_NM Map1::First_Letter_NM("Map1::First_Letter_NM", 5);
Map1_List_Atr Map1::List_Atr("Map1::List_Atr", 6);
Map1_First_Letter_AT Map1::First_Letter_AT("Map1::First_Letter_AT", 7);
Map1_Comma Map1::Comma("Map1::Comma", 8);
Map1_space_NM Map1::space_NM("Map1::space_NM", 9);
Map1_EndBracket Map1::EndBracket("Map1::EndBracket", 10);
Map1_OK Map1::OK("Map1::OK", 11);
Map1_Error Map1::Error("Map1::Error", 12);

void AppClassState::Alth(AppClassContext& context, std::string t_string1, int& index)
{
    Default(context);
}

void AppClassState::Bracket_left(AppClassContext& context)
{
    Default(context);
}

void AppClassState::Bracket_left_q(AppClassContext& context)
{
    Default(context);
}

void AppClassState::Bracket_right(AppClassContext& context)
{
    Default(context);
}

void AppClassState::Bracket_right_q(AppClassContext& context)
{
    Default(context);
}

void AppClassState::Creat(AppClassContext& context)
{
    Default(context);
}

void AppClassState::EOS(AppClassContext& context)
{
    Default(context);
}

void AppClassState::EOS(AppClassContext& context, std::string t_string)
{
    Default(context);
}

void AppClassState::EOS(AppClassContext& context, std::string t_string1, std::string t_string2)
{
    Default(context);
}

void AppClassState::Num(AppClassContext& context)
{
    Default(context);
}

void AppClassState::Space(AppClassContext& context)
{
    Default(context);
}

void AppClassState::Unknown(AppClassContext& context)
{
    Default(context);
}

void AppClassState::W_Creat(AppClassContext& context)
{
    Default(context);
}

void AppClassState::com(AppClassContext& context)
{
    Default(context);
}

void AppClassState::eps(AppClassContext& context)
{
    Default(context);
}

void AppClassState::Default(AppClassContext& context)
{
    throw (
        TransitionUndefinedException(
            context.getState().getName(),
            context.getTransition()));

}

void Map1_Default::W_Creat(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::Unknown(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::Alth(AppClassContext& context, std::string t_string1, int& index)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::Bracket_right(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::Bracket_left(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::Space(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::com(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::Num(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::Bracket_right_q(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::Bracket_left_q(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::Creat(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Default::EOS(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_Start::Alth(AppClassContext& context, std::string t_string1, int& index)
{
    AppClass& ctxt = context.getOwner();

    if ( ctxt.CheckCreat(t_string1, index) )
    {
        context.getState().Exit(context);
        // No actions.
        context.setState(Map1::Creat_Rel);
        context.getState().Entry(context);
    }
    else
    {
        context.getState().Exit(context);
        context.setState(Map1::See_Rel);
        context.getState().Entry(context);
    }

}

void Map1_Start::EOS(AppClassContext& context, std::string t_string)
{
    AppClass& ctxt = context.getOwner();

    context.getState().Exit(context);
    context.clearState();
    try
    {
        ctxt.Acceptable();
        ctxt.AddRel(t_string);
        context.setState(Map1::OK);
    }
    catch (...)
    {
        context.setState(Map1::OK);
        throw;
    }
    context.getState().Entry(context);

}

void Map1_Creat_Rel::Alth(AppClassContext& context, std::string t_string1, int& index)
{

    context.getState().Exit(context);
    context.setState(Map1::First_Letter_NM);
    context.getState().Entry(context);

}

void Map1_See_Rel::Alth(AppClassContext& context, std::string t_string1, int& index)
{


}

void Map1_See_Rel::EOS(AppClassContext& context, std::string t_string)
{
    AppClass& ctxt = context.getOwner();

    context.getState().Exit(context);
    context.clearState();
    try
    {
        ctxt.Acceptable();
        ctxt.ShowRels(t_string);
        context.setState(Map1::OK);
    }
    catch (...)
    {
        context.setState(Map1::OK);
        throw;
    }
    context.getState().Entry(context);

}

void Map1_See_Rel::Num(AppClassContext& context)
{


}

void Map1_See_Rel::Space(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Space_See_Rel);
    context.getState().Entry(context);

}

void Map1_Space_See_Rel::Alth(AppClassContext& context, std::string t_string1, int& index)
{
    AppClass& ctxt = context.getOwner();

    if ( ctxt.CheckJoin(t_string1, index) )
    {
        context.getState().Exit(context);
        // No actions.
        context.setState(Map1::Join);
        context.getState().Entry(context);
    }
    else
    {
         Map1_Default::Alth(context, t_string1, index);
    }

}

void Map1_Join::Alth(AppClassContext& context, std::string t_string1, int& index)
{


}

void Map1_Join::EOS(AppClassContext& context, std::string t_string1, std::string t_string2)
{
    AppClass& ctxt = context.getOwner();

    context.getState().Exit(context);
    context.clearState();
    try
    {
        ctxt.Acceptable();
        ctxt.ShowRels(t_string1, t_string2);
        context.setState(Map1::OK);
    }
    catch (...)
    {
        context.setState(Map1::OK);
        throw;
    }
    context.getState().Entry(context);

}

void Map1_Join::Num(AppClassContext& context)
{


}

void Map1_First_Letter_NM::Alth(AppClassContext& context, std::string t_string1, int& index)
{


}

void Map1_First_Letter_NM::Bracket_right(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::List_Atr);
    context.getState().Entry(context);

}

void Map1_First_Letter_NM::Num(AppClassContext& context)
{


}

void Map1_First_Letter_NM::com(AppClassContext& context)
{


}

void Map1_List_Atr::Alth(AppClassContext& context, std::string t_string1, int& index)
{

    context.getState().Exit(context);
    context.setState(Map1::First_Letter_AT);
    context.getState().Entry(context);

}

void Map1_List_Atr::Bracket_left(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::EndBracket);
    context.getState().Entry(context);

}

void Map1_List_Atr::com(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Comma);
    context.getState().Entry(context);

}

void Map1_First_Letter_AT::Alth(AppClassContext& context, std::string t_string1, int& index)
{


}

void Map1_First_Letter_AT::Bracket_left(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::EndBracket);
    context.getState().Entry(context);

}

void Map1_First_Letter_AT::Num(AppClassContext& context)
{


}

void Map1_First_Letter_AT::com(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Comma);
    context.getState().Entry(context);

}

void Map1_Comma::Alth(AppClassContext& context, std::string t_string1, int& index)
{

    context.getState().Exit(context);
    context.setState(Map1::First_Letter_AT);
    context.getState().Entry(context);

}

void Map1_space_NM::Alth(AppClassContext& context, std::string t_string1, int& index)
{

    context.getState().Exit(context);
    context.setState(Map1::First_Letter_NM);
    context.getState().Entry(context);

}

void Map1_space_NM::Bracket_left(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_space_NM::Bracket_right(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Error);
    context.getState().Entry(context);

}

void Map1_space_NM::Space(AppClassContext& context)
{


}

void Map1_EndBracket::EOS(AppClassContext& context, std::string t_string)
{
    AppClass& ctxt = context.getOwner();

    context.getState().Exit(context);
    context.clearState();
    try
    {
        ctxt.Acceptable();
        ctxt.AddRel(t_string);
        context.setState(Map1::OK);
    }
    catch (...)
    {
        context.setState(Map1::OK);
        throw;
    }
    context.getState().Entry(context);

}

void Map1_OK::eps(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Start);
    context.getState().Entry(context);

}

void Map1_Error::EOS(AppClassContext& context)
{
    AppClass& ctxt = context.getOwner();

    AppClassState& endState = context.getState();

    context.clearState();
    try
    {
        ctxt.Unacceptable();
        context.setState(endState);
    }
    catch (...)
    {
        context.setState(endState);
        throw;
    }

}

void Map1_Error::eps(AppClassContext& context)
{

    context.getState().Exit(context);
    context.setState(Map1::Start);
    context.getState().Entry(context);

}

//
// Local variables:
//  buffer-read-only: t
// End:
//
