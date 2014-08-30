//---------------------------------------------------------------------------
// csved_squash.h
//
// squash duplicate rows to single row
//
// Copyright (C) 2014 Neil Butterworth
//---------------------------------------------------------------------------


#include "csved_squash.h"
#include "csved_cli.h"
#include "csved_strings.h"

using std::string;

namespace CSVED {

//---------------------------------------------------------------------------
// Register squash command
//---------------------------------------------------------------------------

static RegisterCommand <SquashCommand> rc1_(
	CMD_SQUASH,
	"squash duplicate rows to single row"
);

//----------------------------------------------------------------------------
// Squash command help
//----------------------------------------------------------------------------

const char * const UNIQUE_HELP = {
	"squash duplicate rows to single row \n"
	"usage: csvfix squash [flags] [files ...]\n"
	"where flags are:\n"
	"  -f fields\tfields specifying key (required)\n"
	"  -n fields\toutput only duplicate rows (required)\n"
	"  -nn val\tvalue to use if -n field contains non-numeric value\n"
	"  -rn \t\ttreat -n fieals as real numbers rather than as integers\n"
	"#SMQ,SEP,IBL,IFN,OFL"

};

//---------------------------------------------------------------------------
// Standard ctor
//---------------------------------------------------------------------------

SquashCommand :: SquashCommand( const string & name,
								const string & desc )
		: Command( name, desc, UNIQUE_HELP) {

	AddFlag( ALib::CommandLineFlag( FLAG_COLS, true, 1 ) );
	AddFlag( ALib::CommandLineFlag( FLAG_NUM, true, 1 ) );
	AddFlag( ALib::CommandLineFlag( FLAG_NONUM, false, 1 ) );
	AddFlag( ALib::CommandLineFlag( FLAG_REALS, false, 0 ) );

}

//---------------------------------------------------------------------------
// Read inputs and squash rows with same key.
//---------------------------------------------------------------------------

int SquashCommand :: Execute( ALib::CommandLine & cmd ) {

	IOManager io( cmd );
	CSVRow row;

	while( io.ReadCSV( row ) ) {
	}
	return 0;
}



//------------------------------------------------------------------------

} // end namespace

// end

