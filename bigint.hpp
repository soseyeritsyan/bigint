#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class bigint
{
	private:
	vector<unsigned char> dig;

	public:
	bigint();
	bigint( string& s );
	bigint( vector<unsigned char> & v);
	void print();
//	~bigint();

	bigint operator+( bigint & oth );
	
	bigint operator-( bigint& oth );
	
	bigint operator*( const bigint& oth );
       
        bigint operator/( bigint & oth );
        
        bigint operator%( bigint & oth ); 
        
	friend void operator+=( bigint & ths , bigint & oth );
       
	friend void operator-=( bigint & ths , bigint & oth );
        
	friend void operator*=( bigint & ths , bigint& oth );
       
	friend void operator/=( bigint & ths , bigint & oth );

	bool operator<( bigint & oth );

	bool operator>( bigint & oth );

	bool operator==( bigint & oth );

	bool operator>=( bigint & oth );

	bool operator<=( bigint& oth );

	bool operator!=( bigint & oth );
};
