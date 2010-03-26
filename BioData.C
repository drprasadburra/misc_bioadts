#include "BioData.h"

using namespace std;
BioData::BioData(){}

BioData :: BioData (const string& fileName)
{
  	checkNumberOfColumns(fileName);
   	setData(fileName);
}

BioData :: BioData (const string& fileName, const int& xCol,const  int& yCol)
{
		checkNumberOfColumns(fileName);
		setData(fileName, xCol, yCol);
}

BioData :: BioData (const string& fileName,const  int& xCol, string& yCol)
{
		checkNumberOfColumns(fileName);
		setData(fileName, xCol, yCol);
}

// TO BE ADDED:
BioData :: BioData(const vector < string >& xDataSet, const vector < double >& yDataSet)
{
     if( xDataSet.size() != yDataSet.size())
      {
         	cerr << "BOSERR- BioData(vector-string,vector-double): Mismatch between (X,Y) DataSets " ;
          	cerr<<"Press any Key to continue."<<endl;
		getchar();
     		exit(0);
      }
      	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

     xDataSet_ = xDataSet;
     yDataSets_.push_back(yDataSet);
}

BioData :: BioData(const vector < string >& xDataSet, const vector < int >& yDataSet)
{
     if( xDataSet.size() != yDataSet.size())
      {
         cerr << "BOSERR- BioData(vector-string,vector-int): Mismatch between (X,Y) DataSets " ;
         cerr<<"Press any key to continue"<<endl;
	 		getchar();exit(0);
      }
      	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

      vector< double > yDouble;

      for(int i=0;i< yDataSet.size();i++)
      yDouble.push_back(yDataSet[ i ]*1.0);
      
      xDataSet_ = xDataSet;
      yDataSets_.push_back(yDouble);
      yDouble.clear();
}


BioData :: BioData(const vector < double >& xDataSet, const vector < double >& yDataSet)
{
     if( xDataSet.size() != yDataSet.size())
      {
         cerr << "BOSERR- BioData(vector-double,vector-double): Mismatch between (X,Y) DataSets " ;
         cerr<<"Press any Key to continue."<<endl;
		      		getchar();exit(0);
      }
     	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

     vector <string> vst;
     for(unsigned int i =0 ;i < xDataSet.size() ; i++)
     vst.push_back(toString(xDataSet[i]));

     xDataSet_ = vst;
     yDataSets_.push_back(yDataSet);
     vst.clear();
}

BioData :: BioData(const vector < double >& xDataSet, const vector < int >& yDataSet)
{
       if( xDataSet.size() != yDataSet.size())
      {
         cerr << "BOSERR- BioData(vector-double,vector-int): Mismatch between (X,Y) DataSets " ;
     	cerr<<"Press any key to continue"<<endl;
	         		getchar(); exit(0);
      }
     
      	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

      
     vector <string> vst;
     for(unsigned int i =0 ;i < xDataSet.size() ; i++)
      vst.push_back(toString(xDataSet[i]));

      vector< double > yDouble;

      for(int i=0;i< yDataSet.size();i++)
      yDouble.push_back(yDataSet[i]*1.0);

     xDataSet_ = vst;
     yDataSets_.push_back(yDouble);
     vst.clear();
     yDouble.clear();
     
}

  
BioData :: BioData(const vector < int >& xDataSet, const vector < int >& yDataSet)
{
       if( xDataSet.size() != yDataSet.size())
      {
         cerr << "BOSERR- BioData(vector-int,vector-int): Mismatch between (X,Y) DataSets " ;
         cerr<<"Press any key to continue"<<endl;
	  		getchar();     exit(0);
      }
     	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

     vector <string> vst;
     for(unsigned int i =0 ;i < xDataSet.size() ; i++)
      vst.push_back(toString(xDataSet[i]));

      vector< double > yDouble;

      for(int i=0;i< yDataSet.size();i++)
      yDouble.push_back(yDataSet[i]*1.0);

     xDataSet_ = vst;
     yDataSets_.push_back(yDouble);
     vst.clear();
     yDouble.clear();
}

BioData :: BioData(const vector < int >& xDataSet, const vector < double >& yDataSet)
{
       if( xDataSet.size() != yDataSet.size())
      {
         cerr << "BOSERR- BioData (vector-int,vector-double): Mismatch between (X,Y) DataSets " ;
               cerr<<"Press any key to continue"<<endl;
	       		getchar();exit(0);
      }
     	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

     vector <string> vst;
     for(unsigned int i =0 ;i < xDataSet.size() ; i++)
      vst.push_back(toString(xDataSet[i]));

     xDataSet_ = vst;
     yDataSets_.push_back(yDataSet);
     vst.clear();
}


void BioData::setData(const string& fileName,const  int& xcolumn, string& ycolumn )
{
	ifstream fi(fileName.c_str());
     	string str;
	       	
	
	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();
	
	vector < int > ycols = processStringForColumns(ycolumn);
/******************* Checking for CRAZY Column Numbers (if Given) ***********************/
	vector< double > yDouble;
      for(int i=0;i< ycols.size();i++)
      yDouble.push_back(ycols[i]*1.0);
	
	if ( (int)BioStatistics::getMaximum(yDouble) >= numberOfColumns_ )
   	{
      		cerr <<" BOSERR- BioData, setData(srn,ern,many-y): Unknown Y column Number: ";
		cerr<< (int)BioStatistics::getMaximum(yDouble)<<": specified."<<endl;
      		cerr<<"Press any Key to continue."<<endl;
		     		getchar();exit(0);
   	}
   yDouble.clear();
/******************* Checking for CRAZY Column Numbers (if Given) ***********************/	
	vector < double > oneYSet;
	// creating number of columns to be stored ...based on the string passed.
	for ( unsigned int i = 0; i <  ycols.size(); i++)
	yDataSets_.push_back(oneYSet);

	long rowNumber = 0;
     	while(getline(fi,str))
      	{
		istringstream iss(str);
		string j;
		int columnNumber = 0;
          	
		while ( iss >> j )
          	{
          		if ( columnNumber ==  xcolumn )
            		{

            			xDataSet_.push_back ( j );
             			break;
              		}

              		columnNumber++;
          	}
									
		for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		{
			istringstream issy(str);
			string jy;
			int columnNumber1 = 0;
			
			while ( issy >> jy )
			{
              			if ( columnNumber1 == ycols[i])
              			{
              				if ( checkDouble(jy) )
						yDataSets_[i].push_back(stringToDouble(jy));
					else
					{
					cerr<<"BOS-ERR: BioData,setData(fn,x,many-y): The Value ";
					cerr<<jy<<" is NOT Numerical."<<endl;
					cerr<<"at row, column: ("<<rowNumber<<","<<columnNumber<<")"<<endl;
					cerr<<"Please Check the Data!!!!"<<endl;
					cerr<<"Press any Key to continue."<<endl;
							getchar();exit(0);
					}
				}
				columnNumber1++;
			}
		 }
	}
}

void BioData::setData(const string& fileName,const  int& xcolumn, const int& ycolumn)
{
    	ifstream fi(fileName.c_str());
     	string str;
	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

     	vector < double > oneYSet;

     	yDataSets_.push_back(oneYSet);
	int rowNumber = 0;
     	while ( getline(fi, str) )
     	{
     		istringstream iss(str);
          	string j;
		int columnNumber = 0;
          	while ( iss >> j )
          	{
          		if ( columnNumber ==  xcolumn )
            		xDataSet_.push_back ( j );
						
              		if ( columnNumber == ycolumn)
              		{
              			if ( checkDouble(j) )
					yDataSets_[0].push_back(stringToDouble(j));
				else
				{
					cerr<<"BOS-ERR: BioData,setData(fn,x,y): The Value "<<j<<" is NOT Numerical."<<endl;
					cerr<<"at row, column: ("<<rowNumber<<","<<columnNumber<<")"<<endl;
					cerr<<"Please Check the Data!!!!"<<endl;
					cerr<<"Press any Key to continue."<<endl;
							getchar();exit(0);
				}
			}
			columnNumber++;
          	}
		rowNumber++;
	}
}

void BioData::setData( const string& fileName )
{
      ifstream fi(fileName.c_str());
			string str;
	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

			vector < double > oneYSet;

			for ( int i = 1; i < numberOfColumns_; i++)
			yDataSets_.push_back(oneYSet);

			long rowNumber = 0;
			while(getline(fi,str))
      {
					istringstream iss(str);
					string j;

					iss >> j;
					xDataSet_.push_back(j);

					int colNumber = 0;
					while (iss >> j )
					{
						if ( checkDouble(j) )
						{
						yDataSets_[colNumber].push_back(stringToDouble(j));
						colNumber++;
						}
						else
						{
							cerr<<"BOS-ERR:BioData,setData(filename):The Value ";
							cerr<<j<<" is NOT Numerical."<<endl;
							cerr<<"at row, column: ("<<rowNumber<<","<<colNumber<<")"<<endl;
							cerr<<"Please Check the Data!!!!"<<endl;
							cerr<<"Press any key to continue"<<endl;
									getchar();exit(0);
						}
					}

					rowNumber++;
			}
}


void BioData :: setData(const vector < string >& xDataSet,const  vector < double >& yDataSet)
{
     	if( xDataSet.size() != yDataSet.size())
      	{
         	cerr << "BOSERR- BioData,setData(vector-string,vector-double): Mismatch between (X,Y) DataSets " ;
         	cerr<<"Press any Key to continue."<<endl;
				getchar();exit(0);
      	}
     	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

     
     xDataSet_ = xDataSet;
     yDataSets_.push_back(yDataSet);
}

void BioData ::  setData(const vector < string >& xDataSet, const vector < int >& yDataSet)
{
       if( xDataSet.size() != yDataSet.size())
      {
         cerr << "BOSERR- BioData, setData(vector-string,vector-int) : Mismatch between (X,Y) DataSets " ;
               cerr<<"Press any key to continue"<<endl;
	       		getchar();exit(0);
      }
      	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

      vector< double > yDouble;

      for(int i=0;i< yDataSet.size();i++)
      yDouble.push_back(yDataSet[i]*1.0);

     for ( int i = 0; i < yDataSets_.size(); i++)
      	yDataSets_[i].clear();
     yDataSets_.clear();
   
     xDataSet_ = xDataSet;
     yDataSets_.push_back(yDouble);
	yDouble.clear();
}

void BioData ::  setData(const vector < double >& xDataSet, const vector < int >& yDataSet)
{
       if( xDataSet.size() != yDataSet.size())
      {
         cerr << "BOSERR- BioData, setData(vector-double, vector-int) : Mismatch between (X,Y) DataSets " ;
               cerr<<"Press any key to continue"<<endl;
	       		getchar();exit(0);
      }
	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

     vector <string> vst;
     for(unsigned int i =0 ;i < xDataSet.size() ; i++)
      vst.push_back(toString(xDataSet[i]));

      vector< double > yDouble;

      for(int i=0;i< yDataSet.size();i++)
      yDouble.push_back(yDataSet[i]*1.0);

     for ( int i = 0; i < yDataSets_.size(); i++)
      	yDataSets_[i].clear();

        yDataSets_.clear();

     xDataSet_ = vst;
     yDataSets_.push_back(yDouble);
     vst.clear();
     yDouble.clear();
}

void BioData :: setData(const vector < double >& xDataSet, const vector < double >& yDataSet)
{
     if( xDataSet.size() != yDataSet.size())
      {
         cerr << "BOSERR- BioData,setData(vector-double,vector-double): Mismatch between (X,Y) DataSets " ;
         cerr<<"Press any Key to continue."<<endl;
				getchar();      exit(0);
      }  
	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

     vector <string> vst;
     for(unsigned int i =0 ;i < xDataSet.size() ; i++)
     vst.push_back(toString(xDataSet[i]));
      
     xDataSet_ = vst;
     for ( int i = 0; i < yDataSets_.size(); i++)
        	yDataSets_[i].clear();
			yDataSets_.clear();
      
     yDataSets_.push_back(yDataSet); 
     vst.clear();		
}


void BioData ::  setData(const vector < int >& xDataSet, const vector < int >& yDataSet)
{
       if( xDataSet.size() != yDataSet.size())
      {
         cerr << "BOSERR- BioData, setData(vector-int,vector-int) : Mismatch between (X,Y) DataSets " ;
               cerr<<"Press any key to continue"<<endl;
	       		getchar();exit(0);
      }
	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

    vector <string> vst;
     for(unsigned int i =0 ;i < xDataSet.size() ; i++)


      vst.push_back(toString(xDataSet[i]));

      vector< double > yDouble;

      for(int i=0;i< yDataSet.size();i++)
      yDouble.push_back(yDataSet[i]*1.0);

     for ( int i = 0; i < yDataSets_.size(); i++)
   	yDataSets_[i].clear();
     yDataSets_.clear();
   
     xDataSet_ = vst;
     yDataSets_.push_back(yDouble);
     vst.clear();
	yDouble.clear();
}

void BioData ::  setData(const vector < int >& xDataSet, const vector < double >& yDataSet)
{
       if( xDataSet.size() != yDataSet.size())
      {
         cerr << "BOSERR- BioData, setData(vector-int, vector-double) : Mismatch between (X,Y) DataSets " ;
               cerr<<"Press any key to continue"<<endl;
	       		getchar();exit(0);
      }
	xDataSet_.clear();
	for ( unsigned int i = 0; i < yDataSets_.size(); i++)
		yDataSets_[i].clear();

    vector <string> vst;
     for(unsigned int i =0 ;i < xDataSet.size() ; i++)
      vst.push_back(toString(xDataSet[i]));

     xDataSet_ = vst;
     
     for ( int i = 0; i < yDataSets_.size(); i++)
        	yDataSets_[i].clear();
     yDataSets_.clear();
     
     yDataSets_.push_back(yDataSet);
     vst.clear();
}

void BioData :: pushYDataSet(const vector < int >& yDataSet)
{

      if(yDataSet.size() == 0 || yDataSet.size() != xDataSet_.size() )
      {
           cerr << "BOSERR- BioData, pushYDataSet(vector-int): yDataSet is EMPTY";
             cerr<<"Press any key to continue"<<endl;
	       		getchar();exit(0);
      }
      vector< double > yDouble;

      for(int i=0;i< yDataSet.size();i++)
      yDouble.push_back(yDataSet[i]*1.0);

      yDataSets_.push_back(yDouble);
}


void BioData :: pushYDataSet ( const vector < double >& yDataSet)
{
     if(yDataSet.size() == 0 || yDataSet.size() != xDataSet_.size() )
      {
           cerr << "BOSERR- BioData, pushYDataSet(vector-double): yDataSet is EMPTY";
           cerr<<"Press any Key to continue."<<endl;
		  		getchar();exit(0);
      } 
 
      yDataSets_.push_back(yDataSet); 		
}


BioData BioData ::  getData(const long& startingRowNumber,const  long& endingRowNumber)
{
     if( startingRowNumber > endingRowNumber )
      {
         cerr << "BOSERR- BioData, getData(starting_row_no,ending_row_no): ";
	 cerr<<"startingRowNumber must be less than endingRowNumber";
          cerr<<"Press any Key to continue."<<endl;
		    		getchar(); exit(0);
      }

     if( startingRowNumber <0 || endingRowNumber >= xDataSet_.size())
      {
         cerr << "BOSERR- BioData, getData(starting_row_no,ending_row_no) : Out Of Range " ;
         cerr<<"Press any Key to continue."<<endl;
				getchar();exit(0);
      }  

     vector <string> vst;
     vector <double> vd;

//RETRIEVING xDataSet & yDataSet VALUES
     for(long i= startingRowNumber; i<=endingRowNumber; i++)
     {
         vst.push_back(xDataSet_[i]);      
         vd.push_back(yDataSets_[0][i]);      
     }
    
   BioData bd(vst, vd);  // CREATING BioData OBJECT
   vd.clear();
   vst.clear();

// RETRIEVING yDataSet VALUES
   for(unsigned int j=1; j < yDataSets_.size(); j++)    
   {

     for(long i= startingRowNumber; i<=endingRowNumber; i++)
         vd.push_back(yDataSets_[j][i]);      

     bd.pushYDataSet(vd);
     vd.clear();
   } 

  return bd; 
} 

BioData BioData :: getData(const long& startingRowNumber, const long& endingRowNumber, const int& yColumnNumber) 
{
     if( startingRowNumber > endingRowNumber )
      {
         cerr << "BOSERR- BioData, getData (srn,ern,columnNumber): startingRowNumber must be less than endingRowNumber";
          cerr<<"Press any Key to continue."<<endl;
		    		getchar(); exit(0);
      }
     if( startingRowNumber <0 || endingRowNumber >= xDataSet_.size())
      {
         cerr << "BOSERR- BioData, getData(srn,ern,columnNumber) : Out Of Range " ;
         cerr<<"Press any Key to continue."<<endl;
		      		getchar();exit(0);
      }  
     if( yColumnNumber <0 || yColumnNumber >=yDataSets_.size())
      {
         cerr << "BOSERR- BioData, getData (srn,ern,columnNumber): Out Of Range " ;
         cerr<<"Press any Key to continue."<<endl;
		     		getchar(); exit(0);
      }  

     vector <string> vst;
     vector <double> vd;


//RETRIEVING xDataSet VALUES
     for(long i= startingRowNumber; i <= endingRowNumber; i++)
     {
         vst.push_back(xDataSet_[i]);      
         vd.push_back(yDataSets_[yColumnNumber][i]);     
     } 

     BioData bd(vst, vd);  // CREATING BioData OBJECT
     vd.clear();
     vst.clear();

  return bd; 
} 

BioData BioData :: getData(const long& startingRowNumber, const long& endingRowNumber, string& yColumnNumber) 
{
     if( startingRowNumber > endingRowNumber )
      {
         cerr << "BOSERR- BioData, getData(srn,ern,many-y): startingRowNumber must be less than endingRowNumber";
          cerr<<"Press any Key to continue."<<endl;
		         		getchar(); exit(0);
      }
     if( startingRowNumber <0 || endingRowNumber >= xDataSet_.size())
      {
         cerr << "BOSERR- BioData, getData(srn,ern,many-y) : Out Of Range " ;
         cerr<<"Press any Key to continue."<<endl;
		          		getchar(); exit(0);
      }  
     vector <string> vst;
     vector <double> vd;
     vector <int> vyc;
     
   vyc = processStringForColumns(rmBlank(yColumnNumber));
   if(vyc.size() > yDataSets_.size())
   {
      cerr <<" BOSERR- BioData, getData(srn,ern,many-y): Too many Y columns";
      cerr<<"Press any Key to continue."<<endl;
		     		getchar();exit(0);
   }
   if(vyc.size() == 0)
   {
      cerr <<" BOSERR- BioData, getData(srn,ern,many-y): No Y column is specified";
      cerr<<"Press any Key to continue."<<endl;
		     		getchar();exit(0);
   }
   
       vector< double > yDouble;

      for(int i=0;i< vyc.size();i++)
      yDouble.push_back(vyc[i]*1.0);
	
	if ( (int)BioStatistics::getMaximum(yDouble) >= yDataSets_.size() )
   	{
      		cerr <<" BOSERR- BioData, getData(srn,ern,many-y): Unknown Y column Number: ";
		cerr<< (int)BioStatistics::getMaximum(yDouble)<<": specified."<<endl;
      		cerr<<"Press any Key to continue."<<endl;
		     		getchar();exit(0);
   	}
   yDouble.clear();

//RETRIEVING xDataSet VALUES
     for(long i= startingRowNumber; i<=endingRowNumber; i++)
     {
         vst.push_back(xDataSet_[i]);      
         vd.push_back(yDataSets_[vyc[0]][i]);     
     } 
     
   BioData bd(vst, vd);  // CREATING BioData OBJECT
   vd.clear();
   vst.clear();
   
// RETRIEVING yDataSet VALUES
   for(unsigned int j=1; j < vyc.size(); j++)    
   {
     
     for(long i= startingRowNumber; i<=endingRowNumber; i++)
         vd.push_back(yDataSets_[vyc[j]][i]);      
     bd.pushYDataSet(vd);
     vd.clear();
   } 
  return bd; 
} 


BioData operator+(BioData d1, BioData d2)
{

   if(d1.getNumberOfYDataSets() != d2.getNumberOfYDataSets() )  
   {
     cerr << "BOSERR- BioData, operator + : Mismatch between The Objects,especially check sizes.";
      cerr<<"Press any Key to continue."<<endl;
		   		getchar(); exit(0);
   }  
   
   vector <string> vs1, vs2;
   vector <double> vd1,vd2;

   vs1 = d1.getXDataSet();
   vs2 = d2.getXDataSet();
   vd1 = d1.getYDataSet(0);
   vd2 = d2.getYDataSet(0);
  
   for(unsigned int i =0; i < vs2.size(); i++)
   {
      vs1.push_back(vs2[i]);    
      vd1.push_back(vd2[i]);    
   }

 
   BioData bd(vs1,vd1);
   vd1.clear();
   vd2.clear();
   vs1.clear();
   vs2.clear();
 
   for(long i = 1 ;i <d1.getNumberOfYDataSets(); i++)
   {
     vd1 = d1.getYDataSet(i);
     vd2 = d2.getYDataSet(i);
     
     for(unsigned int j =0; j < vd2.size(); j++)
        vd1.push_back(vd2[j]);   
 
     bd.pushYDataSet(vd1);

     vd1.clear();
     vd2.clear();
   }  
  return bd;
}

void BioData :: showData(ostream & os)
{
  
   for(unsigned int i=0; i<xDataSet_.size() ; i++)
   {
       align(xDataSet_[i],10,1,os);
       align(" ",3,0,os);
       for(unsigned int j=0; j<yDataSets_.size() ; j++)
       {
           string st = toString(yDataSets_[j][i]); 
           align(st,10,0,os);
	         align(" ",3,0,os);           
       }

       os<<endl;
   }

}

void BioData::checkNumberOfColumns(const string& fileName)
{
      	ifstream fi(fileName.c_str());
	string str;
	int column_ = 0;
	getline(fi,str);
	istringstream iss(str);
	string j;
	while ( iss >> j )
	column_++;


	int i = 1;
	while(getline(fi,str))
      	{
		istringstream iss(str);
		string j;
		int tempColumn_ = column_;
		column_ = 0;
			while (iss >> j )
			column_++;

			if ( tempColumn_ != column_ )
			{
			 	cerr<<"BioData Error: Column mismatch error!!! at "<<i<<"th row."<<endl;
				cerr<<"Please check the Data in file: "<<fileName<<endl;
			  	cerr<<"Press any Key to continue."<<endl;
				  		getchar();exit(0);
			}
		i++;
      	}

      numberOfColumns_ = column_;
      numberOfRows_ = i;
}

vector< int >  BioData::processStringForColumns(string row)
{
	string rowcheck = rmBlank(row);
	replace(rowcheck.begin(), rowcheck.end(),',',' ');
	replace(rowcheck.begin(),rowcheck.end(),'-',' ');
	for ( int i = 0; i < rowcheck.length();i++)
	{
		if ( isalpha(rowcheck[i]) != 0  || row.length() == 0)
		{
		cerr<<"BOS-ERR: BioData: Please check the format of String Representation of Y Columns."<<row<<endl;
		cerr<<"Press any Key to continue."<<endl;
		  		getchar();exit(0);
		}
	}
	row = rmBlank(row);
	replace(row.begin(), row.end(), ',', ' ');

	istringstream iss(row);
	string j;
	vector < int > ycolnumbers;
	
	while ( iss >> j )
	{
		if ( checkInt(j) )
			ycolnumbers.push_back( stringToInt(j) );
		else
		{
			string j2 = j;
			replace( j2.begin(), j2.end(), '-',' ');
			istringstream ssi(j2);
			int k1, k2;
			ssi>>k1>>k2;
				for ( int i = k1; i<=k2; i++ )
				ycolnumbers.push_back(i);
		}
	}
	
	return ycolnumbers;
}


long BioData::getNumberOfRows()
{
	return xDataSet_.size();
}

vector < string > BioData::getXDataSet()
{
	return xDataSet_;
}

vector < double > BioData::getYDataSet(const unsigned int& index)
{
	return yDataSets_[index];
}

int BioData::getNumberOfYDataSets()
{
	return yDataSets_.size();
}
	
double BioData::getMaximumOfYDataSets()
{
		unsigned int total = getNumberOfYDataSets();
		double max_ = -100000000.00;
		for ( unsigned int i = 0; i < total; i++)
		{
				if ( BioStatistics::getMaximum ( yDataSets_[i] )  > max_ )
				max_ = BioStatistics::getMaximum ( yDataSets_[i] );
		}
		return max_;
}

double BioData::getMinimumOfYDataSets()
{
		unsigned int total = getNumberOfYDataSets();
		double max_ = 999999999.99;
		for ( unsigned int i = 0; i < total; i++)
		{
				if ( BioStatistics::getMinimum ( yDataSets_[i] )  < max_ )
				max_ = BioStatistics::getMinimum ( yDataSets_[i] );
		}
		return max_;
}

vector < double > BioData::getDoubleXDataSet()
{

	vector < double > db;

	for ( unsigned int i = 0; i < xDataSet_.size(); i++ )
	{
		if ( checkDouble ( xDataSet_[i] ) )
		{
			db.push_back(stringToDouble(xDataSet_[i]));
		}
		else
		{
			cerr<<"BOS-ERR:BioData,getDoubleXDataSet:The Value "<<xDataSet_[i]<<" is NOT Numerical."<<endl;
			cerr<<"at row: "<<i<<endl;
			cerr<<"Please Check the Data!!!!"<<endl;
			cerr<<"Press any key to continue!"<<endl;
			  		getchar();exit(0);
		}
	}

	return db;
}

bool BioData::checkInt(const string& j)
{
	for (unsigned int i = 0; i < j.length(); i++)
	{
		if ( isdigit(j[i]) != 0 ); //dont do any thing...
		else return false;
	}

	return true;
}
	
bool BioData::checkDouble(const string& j)
{
	 int dash_count = count(j.begin(), j.end(), '-');
		int dot_count = count(j.begin(), j.end(), '.');

		if ( dash_count > 1 || dot_count > 1 ) return false;
	
	for ( unsigned int i = 0; i < j.length(); i++)
	{
		if ( isdigit(j[i]) != 0 || j[i] == '.' || j[0] == '-');
		else return false;
	}

	return true;
}
		
bool operator<( const BioData& x, const BioData& y)
{
                       return true;
}

bool operator>( const BioData& x, const BioData& y)
{
                       return true;
}

bool operator==( const BioData& x, const BioData& y)
{
                      return true;
}


