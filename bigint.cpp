#include "bigint.hpp"

void del_zero ( vector<unsigned char> & v )
{
        int i = 0;
        if ( v[i] == '-' ) {
                i++ ;
        }
        while ( v[i] == 0 ) {
                v.erase(v.begin() + i );
        }
}

void sys256 ( string & a , vector<unsigned char> & res )
{
        if ( a.size() > 3 || stoi(a) >= 256 ) {
		string r;
		string r1;
		int i = 3;
		int k = 0;
		char tmp1;
		int qn;
		int tmp = 0;
		r1.assign(a, 0, 3);
		k = stoi(r1);
		if( k < 256 ) {
			r1.assign(a, 0, 4);
			k = stoi(r1);
			i = 4;
		}
		qn = k / 256;
		tmp1 = qn + '0';
		r = r + tmp1;
		k =  k % 256;
		while ( i < a.size() ) {
			if ( k < 256 ) {
				tmp = a[i] - '0';
				k *= 10;
				k = k + tmp;
				i++;
				if ( k < 256 && i < a.size()) {
					tmp = a[i] - '0';
					k *= 10;
					k = k + tmp;
					r = r + '0';
					i++;
				}
			}
			qn = k / 256;
			tmp1 = qn + '0';
			r = r + tmp1;
			k =  k % 256;
		}
		res.push_back(k);
		sys256 ( r , res );
	}
        else {
                int k = stoi(a);
				res.push_back(k);
        }
}
void bigint::print()
{
        for ( int i = 0 ; i < dig.size(); i++ ) {
        	printf("%d",dig[i]);
                cout << " ";
        }
        cout << endl;
}


bigint bigint:: operator+( bigint & oth ) //gumarum
{
	vector<unsigned char> res;
	res.push_back(0);
	int c = 0;
	int k ;
	bigint a = *this;
	bogint b = oth;
	if ( dig == res ) {
		return oth;
	}
	if ( oth.dig == res ) {
		return *this;
	}
	res.clear();
	if ( a.dig[0] == 0 && b.dig[0] != 0 ) {
		a.dig.erase(a.begin());
		bigint r = oth - *this;
		return r;
	}
	if ( a.dig[0] != 0 && b.dig[0] == 0 ) {
		b.dig.erase(b.begin());
		bigint r = a - b;
		return r;
	}
	if ( a.dig[0] == 0 && b.dig[0] == 0 ) {
		a.dig.erase(a.begin());
		b.dig.erase(b.begin());
		res.push_back(0);
	}

	for ( int i = a.dig.size() - 1 , j = b.dig.size() - 1;  ; i-- , j-- ) {
		if ( i >= 0 && j >= 0) {
			k = (int)(a.dig[i]) + (int)(b.dig[j]) + c ;
			if ( k >= 256 ) {
				k = k - 256;
				c = 1;
			}
			else {
				c = 0;
			}
		}
		if ( i >= 0 && j < 0 ) {
			k = (int)(a.dig[i]) + c ;
			if ( k >= 256 ) {
				k = k - 256;
				c = 1;
			}
			else {
				c = 0;
			}
		}

		if ( i < 0 && j < 0 ) {
			break;
		}
		res.push_back(k);
	}
	if ( res[0] == 0 ) {
		res.erase(res.begin());
		res.push_back(0);
	}
	reverse(res.begin(), res.end());
	return bigint(res);
}


bigint bigint::operator-( bigint& oth )//hanum
{
	vector<unsigned char> res;
	res.push_back(0);
	int c = 0;
	int k ;
	if ( *this == oth ) {
		return bigint(res);
	}

	if ( oth.dig == res ) {
		return *this;
	}
	res.clear();
	for ( int i = dig.size() - 1 , j = oth.dig.size() - 1;  ; i-- , j-- ) {
		if ( i >= 0 && j >= 0) {
			if ( (int)(dig[i]) >= (int)(oth.dig[j]) ) {
					k = (int)(dig[i]) - (int)(oth.dig[j]) - c ;
					c = 0;
			}
			else {
				k = (int)(dig[i]) - (int)(oth.dig[j]) - c + 256 ;
				c = 1;
			}
		}
		if ( i >= 0 && j < 0 ) {
			k = (int)(dig[i]) - c ;
			c = 0;
		}
		if ( i < 0 && j < 0 ) {
			break;
		}
		res.push_back(k);
	}
	reverse(res.begin(), res.end());
	del_zero(res) ;
	return bigint(res);
}

bigint bigint::operator*( const bigint& oth )
{
	vector<unsigned char> res;
	res.push_back(0);
	if ( dig == res || oth.dig == res ) {
		return bigint(res);
	}
	res.clear();
	res.push_back(1);
	if ( dig == res ) {
		return oth;
	}
	if ( oth.dig == res ) {
		return *this;
	}
	res.clear();
	for ( int i = 0 ; i < a.dig.size() + b.dig.size() ; i++ ) {
		res.push_back(0);
	}
	int carry;
	for ( int i = b.dig.size() - 1 ; i >= 0 ; --i ) {
		for ( int j = dig.size() - 1 ; j >= 0 ; j-- ) {
			int k = (int)(res[ i + j + 1 ]) + (int)(a.dig[j])*(int)(b.dig[i]);
			res[ i + j + 1 ] = k % 256 ;
			carry = k / 256;
			res[ i + j ] += carry;
		}
	}
	del_zero(res);
	return bigint(res);
}
bigint bigint::operator/( bigint & oth )//bajanum
{
	vector<unsigned char> res;
	if ( *this < oth ) {
		res.push_back(0);
		return bigint(res);
	}
	res.clear();
	res.push_back(1);
	if ( dig == res ) {
		return bigint(res);
	}
	res.clear();
	while ( b.dig.size() < a.dig.size() ) {
		b.dig.push_back(0);
		int count = 0;
		while ( a >= b ) {
			a = a - b ;
			++count;
		}
		res.push_back(count);
		if ( b.dig.size() <= oth.dig.size() ) {
			break;
		}
		b.dig.pop_back();
	}
	del_zero(res);
	return bigint(res);
}
bigint bigint::operator%( bigint & oth ) 
{
	bigint c;
	c = *this / oth;
	c = *this - c;
}
void operator+=( bigint & ths , bigint & oth )
{
	ths = ths + oth;
}

void operator-=( bigint & ths , bigint & oth )
{
	ths = ths - oth;
}

void operator*=( bigint & ths , bigint& oth )
{
	ths = ths * oth;
}

void operator/=( bigint & ths , bigint & oth )
{
	ths = ths / oth;
}
bool bigint::operator<( bigint & oth )
{
	if ( ths.dig.size() < oth.dig.size() ) {
		return true;
	}
	if ( ths.dig.size() > oth.dig.size() ) {
		return false;
	}
	if ( ths.dig.size() == oth.dig.size() ) {
		int i = 0;
		for ( i = 0 ; i < ths.dig.size(); i++ ) {
			if( (int)(ths.dig[i]) > (int)(oth.dig[i]) ) {
				return false;
			}
			if( (int)(ths.dig[i]) < (int)(oth.dig[i]) ) {
				return true;
			}
		}
	}
}

bool bigint::operator>( bigint & oth )
{
	if ( ths.dig.size() > oth.dig.size() ) {
		return true;
	}
	if ( ths.dig.size() < oth.dig.size() ) {
		return false;
	}
	if ( ths.dig.size() == oth.dig.size() ) {
		int i = 0;
		for ( i = 0 ; i < ths.dig.size(); i++ ) {
			if( (int)(ths.dig[i]) < (int)(oth.dig[i]) ) {
				return false;
			}
			if ( (int)(ths.dig[i]) > (int)(oth.dig[i]) ) {
				return true;
			}
		}
	}
}

bool bigint::operator==( bigint & oth )
{
	if ( ths.dig.size() != oth.dig.size() ) {
		return false;
	}
	else {
		for ( int i = 0 ; i < ths.dig.size() ; i++ ) {
			if ( (int)(ths.dig[i]) != (int)(oth.dig[i]) ) {
				return false;
			}
		}
		return true;
	}
}
bool bigint::operator>=( bigint & oth )
{
	if ( *this > oth || *this == oth ) {
		return true;
	}
	else {
		return false;
	}
}
bool bigint::operator<=( bigint& oth )
{
	if ( *this < oth || *this == oth ) {
		return true;
	}
	else {
		return false;
	}
}
bool bigint::operator!=( bigint & oth )
{
	if ( *this == oth ) {
		return false;
	}
	else {
		return true;
	}
}

bigint::bigint()
{
	dig.clear();
}

bigint::bigint( string & s )
{
	sys256( s , dig );
	reverse(dig.begin(), dig.end());
}

bigint::bigint( vector<unsigned char> & v )
{
	dig = v;
}
