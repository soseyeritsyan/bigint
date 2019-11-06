#include "bigint.hpp"

int main()
{
	string a;
	cout << "input first number - A " << endl;
	cin >> a;
	bigint A(a);
	A.print();
	string b;
	cout << "input second number - B " << endl;
	cin >> b;
	bigint B(b);
	B.print();

	if ( A > B ) {
		cout << " A bigger than B !" << '\n';
	}
	else if ( A < B ) {
		cout << " B bigger than A !" << '\n';
	}
	else if ( A == B ) {
		cout << " A equal B !" <<'\n';
	}

	bigint C;
	C = A + B;
	cout << "A + B = ";
	C.print();

	C = A - B;
	cout << "A - B = ";
	C.print();

	C = A * B;
	cout << "A * B = ";
	C.print();

	C = A / B;
	cout << "A / B = ";
	C.print();

	C = A % B;
	cout << "A % B = ";
	C.print();
	
	return 0;
}

