//---------------------------------------------------------------------------
// csved_stat.cpp
//
// produce record/field stats for CSV files
//
// Copyright (C) 2012 Neil Butterworth
//---------------------------------------------------------------------------

#include "a_base.h"
#include "a_collect.h"
#include "csved_cli.h"
#include "csved_stat.h"
#include "csved_strings.h"
#include <string>
using std::string;

namespace CSVED {


//---------------------------------------------------------------------------
// Register stat command
//---------------------------------------------------------------------------

static RegisterCommand <StatCommand> rc1_(
	CMD_STAT,
	"produce record/field stats for CSV files"
);


//----------------------------------------------------------------------------
// Help
//----------------------------------------------------------------------------

const char * const STAT_HELP = {
	"produce record/field statistics for CSV files\n"
	"usage: csvfix stat [flags] [file ...]\n"
	"where flags are:\n"
	"#ALL"
};

//----------------------------------------------------------------------------
// The stat command
//----------------------------------------------------------------------------

StatCommand :: StatCommand( const string & name, const string & desc )
				: Command( name, desc, STAT_HELP ) {
}


//---------------------------------------------------------------------------
// Helper to record max field lengths
//---------------------------------------------------------------------------

void RecordLengths( const CSVRow & row, std::vector <int> & lengths ) {
    for ( unsigned int i = 0; i < row.size(); i++ ) {
        if ( i >= lengths.size() ) {
            lengths.push_back( row[i].size() );
        }
        else {
            lengths[i] = std::max( lengths[i], (int) row[i].size() );
        }
    }
}

//----------------------------------------------------------------------------
// Stat the files in the IO manager, reporting file name, number of records
// (not not number of lines!) and min and max field counts.
// Now also output max lengths of all fields.
//----------------------------------------------------------------------------

int StatCommand :: Execute( ALib::CommandLine & cmd ) {

	IOManager io( cmd );

	string filename;
	int lines = 0, fmin = INT_MAX, fmax = 0;
	CSVRow row;
    std::vector <int> lengths;
	while( io.ReadCSV( row ) ) {
		if ( filename != io.CurrentFileName() ) {
			if ( filename != "" ) {
				OutputStats( io, filename, lines, fmin, fmax, lengths );
			}
			filename = io.CurrentFileName();
			lines = 0; fmin = INT_MAX; fmax = 0; lengths.clear();
		}
		RecordLengths( row, lengths );
		lines++;
		fmin = std::min( fmin, (int) row.size() );
		fmax = std::max( fmax, (int) row.size() );
	}
	if ( filename != "" ) {
		OutputStats( io, filename, lines, fmin, fmax, lengths );
	}
	return 0;
}

//----------------------------------------------------------------------------
// Output stats as CSV row
//----------------------------------------------------------------------------

void StatCommand :: OutputStats( IOManager & io, const string & fname,
									int lines, int minf, int maxf,
									const std::vector <int> & lengths )  {
	CSVRow row;
	row.push_back( fname );
	row.push_back( ALib::Str( lines ) );
	row.push_back( ALib::Str( minf ) );
	row.push_back( ALib::Str( maxf ) );
	for ( int i : lengths ) {
        row.push_back( ALib::Str( i ));
    }
	io.WriteRow( row );
}



//----------------------------------------------------------------------------

} // namespace





