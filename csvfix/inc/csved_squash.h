//---------------------------------------------------------------------------
// csved_squash.h
//
// squash duplicate rows to single row
//
// Copyright (C) 2014 Neil Butterworth
//---------------------------------------------------------------------------

#ifndef INC_CSVED_SQUASH_H
#define INC_CSVED_SQUASH_H

#include "a_base.h"
#include "csved_command.h"
#include <map>
#include <vector>

namespace CSVED {

//---------------------------------------------------------------------------

class SquashCommand : public Command {

	public:

		SquashCommand( const std::string & name,
							const std::string & desc );

		int Execute( ALib::CommandLine & cmd );


	private:


};

//------------------------------------------------------------------------

}	// end namespace

#endif

