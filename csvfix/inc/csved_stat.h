//---------------------------------------------------------------------------
// csved_stat.h
//
// produce record/field stats for CSV files
//
// Copyright (C) 2012 Neil Butterworth
//---------------------------------------------------------------------------

#ifndef INC_CSVED_STAT_H
#define INC_CSVED_STAT_H

#include "a_base.h"
#include "csved_command.h"
#include "csved_ioman.h"
#include <string>
#include <vector>
#include <climits>

namespace CSVED {

class FileStats {

    public:

        FileStats( const std::string & filename,
                    const CSVRow & fieldnames );

        void AddRow( const CSVRow & row );
        void Report( IOManager & io ) const;

    private:

        enum class FieldType {
            Empty, String, Number, Real, Date
        };


        struct FieldRecord {
            std::string mName;
            FieldType mType;
            int mMinLen, mMaxLen;

            FieldRecord( const std::string & fieldname )
                : mName( fieldname ), mType( FieldType::Empty ),
                    mMinLen( INT_MAX ), mMaxLen( INT_MIN ){}

        };

        typedef std::vector <FieldRecord> FieldList;
        typedef std::vector <std::string> FileHeader;

        std::string mFileName;
        FileHeader mFieldNames;
        FieldList mFields;
};


class StatCommand : public Command {


	public:

		StatCommand( const std::string & name,
					const std::string & desc );

		int Execute( ALib::CommandLine & cmd );


	private:

        void SimpleStats(  ALib::CommandLine & cmd );
        void FullStats(  ALib::CommandLine & cmd );

		void OutputStats( IOManager & io, const std::string & fname,
							int lines, int maxf, int minf,
							const std::vector <int> & lengths );
};

}

#endif

