#ifndef BIODATA_H
#define BIODATA_H

#include "BioStatistics.h"
#include "BioUtilities.h"

using namespace std;

class BioData
{
	friend bool operator >(const BioData& , const BioData&);
	friend bool operator <(const BioData& , const BioData&);
	friend bool operator ==(const BioData& , const BioData&);

	vector< vector < double > > yDataSets_;
	vector< string > xDataSet_;

	long numberOfColumns_;
	long numberOfRows_;

  void checkNumberOfColumns(const string& file);
  bool checkDouble(const string&);
  bool checkInt(const string&);
  vector<int> processStringForColumns( string );
	
	public:
		BioData(); 
		// This Constructor Takes the 1st Column
		// as X_Data_Set and all the Remaining Columns as Y_Data_Sets.
		// All Y_Data_Sets ****SHOULD**** be NUMERICAL Values.
		BioData (const string& filename);
		BioData ( const string& filename, const int& x_column, const int& y_column);
		BioData ( const string& filename, const int& x_column, string& y_columns);

 BioData(const vector < string >& xDataSet, const vector < double >& yDataSet);
 BioData(const vector < double >& xDataSet, const vector < double >& yDataSet);

 //BioData constructors overloaded w.r.t dataTypes
 BioData(const vector < string >& xDataSet, const vector < int >& yDataSet);
 BioData(const vector < int >& xDataSet, const vector < int >& yDataSet);
 BioData(const vector < int >& xDataSet, const vector < double >& yDataSet);
 BioData(const vector < double >& xDataSet, const vector < int >& yDataSet);


		void setData(const string& file );
		void setData( const string& filename, const  int& x_column, const int& y_column);
		void setData (const  string& filename,const  int& x_column,  string& y_columns);

		void setData(const vector < string >& xDataSet, const vector < double >& yDataSet);
		void setData(const vector < double >& xDataSet,const vector < double >& yDataSet);

// set functions overloaded w.r.t dataTypes          
    		void setData(const vector < string >& xDataSet, const vector < int >& yDataSet);
		void setData(const vector < int >& xDataSet, const vector < int >& yDataSet);
		void setData(const vector < int >& xDataSet, const vector < double >& yDataSet);
		void setData(const vector < double >& xDataSet, const vector < int >& yDataSet);

		long getNumberOfRows();

		vector < string > getXDataSet();
		vector < double > getDoubleXDataSet();

		double getMaximumOfYDataSets();
		double getMinimumOfYDataSets();
		
		vector < double > getYDataSet(const unsigned int& index );
		int getNumberOfYDataSets();
 
 void pushYDataSet(const vector < double >& yDataSet);
 //overloaded pushYDataSet w.r.t dataType
 void pushYDataSet(const vector < int >& yDataSet);
 
 BioData getData(const long& startingRowNumber, const long& endingRowNumber);  
 BioData getData(const long& startingRowNumber, const long& endingRowNumber, const int& yColumnNumber);  
 BioData getData(const long& startingRowNumber, const long& endingRowNumber, string& yColumnNumber);  
 friend BioData operator+(BioData d1, BioData d2);
 void showData(ostream & os = cout );

};
#endif
