#include <stdexcept>
#include <algorithm>
#include <cmath>
#include "rational.h"

Rational::Rational()
{
    n = 0;
    d = 1;
}
Rational::Rational(int num, int denom)
{
    if (denom == 0) throw std::invalid_argument("Can't have denom = 0");
    // Continue your implementation below.
    // You should likely call this->reduce() and this->normalize0()
    if(num < 0 && denom < 0){
    	n = num *= -1;
    	d = denom *= -1;
    }
    else if(denom < 0){
    	n = num * -1;
    	d = denom * -1;
    }
    else{
    n = num;
    d = denom;
    }
    this->normalize0();
    this->reduce();
}
void Rational::normalize0()
{
    if (n == 0 && d != 1) d = 1;
}
void Rational::reduce()
{
	int temp;
	if(n<0)
		temp = gcd(-1*n, d);
	else
		temp = gcd(n, d);
	n /= temp;
	d /= temp;
}
std::ostream& operator<<(std::ostream& ostr, const Rational& r){
	if(r.d < 0)
		ostr << -1*r.n << "/" << -1*r.d;
	else
		ostr << r.n << "/" << r.d;
	return ostr;
}
std::istream& operator>>(std::istream& istr, Rational& r){
	char empty;
	istr >> r.n >> empty >> r.d;
	r.reduce();
	return istr;
}
int Rational::gcd(int a, int b){
	int gcd = 1; int great = std::max(a, b);
	for(int i = 2; i <= great/2; ++i){
		if(a%i == 0 && b%i == 0)
			gcd = i;
	}
	return gcd;
}
int Rational::lcm(int a, int b){
	int temp = a;
	while(temp%b != 0){
		temp += a;
	}
	if(temp<0)
		return temp*-1;
	return temp;
}
Rational Rational::operator+(const Rational& r){
	Rational temp;
	int fix = lcm(this->d, r.d);
	temp.n = fix/this->d * this->n + fix/r.d * r.n;
	temp.d = fix;
	temp.reduce();
	temp.normalize0();
	return temp;
}
Rational Rational::operator+(const int num){
	Rational temp;
	temp.n = this->n + num * this->d;
	temp.d = this->d;
	temp.reduce();
	return temp;
}
Rational operator+(const int num, const Rational& r){
	Rational temp;
	temp.n = r.n + num * r.d;
	temp.d = r.d;
	temp.reduce();
	return temp;
}
Rational Rational::operator*(const Rational& r){
	Rational temp;
	temp.n = this->n * r.n;
	temp.d = this->d * r.d;
	temp.reduce();
	return temp;
}
Rational Rational::operator*(const int num){
	Rational temp;
	temp.n = this->n * num;
	temp.d = this->d;
	temp.reduce();
	temp.normalize0();
	return temp;
}
Rational operator*(const int num, Rational& r){
	Rational temp;
	temp.n = r.n * num;
	temp.d = r.d;
	temp.reduce();
	return temp;
}
Rational Rational::operator^(const int num){
	Rational temp;
	temp.n = 1; temp.d = 1;
	if(num == 0)
		return temp;
	if(num > 0){
		for(int i = 1; i<=num; ++i){
			temp.n *= this->n;
			temp.d *= this->d;
		}
	}
	else{
		for(int i = 1; i<=-1*num; ++i){
			temp.n *= this->d;
			temp.d *= this->n;
		}
	}
	return temp;
}
bool Rational::operator==(const Rational& r){
	if(this->n == r.n && this->d == r.d)
		return true;
	return false;
}
bool Rational::operator!=(const Rational& r){
	if(this->n != r.n || this->d != r.d)
		return true;
	return false;
}
bool Rational::operator<(const Rational& r){
	int temp1, temp2;
	int fix = lcm(this->d, r.d);
	temp1 = fix/this->d * this->n;
	temp2 = fix/r.d * r.n;
	if(temp1 < temp2)
		return true;
	return false;
}
Rational Rational::operator+=(const Rational& r){
	Rational temp;
	int fix = lcm(this->d, r.d);
	temp.n = fix/this->d * this->n + fix/r.d * r.n;
	temp.d = fix;
	temp.reduce();
	temp.normalize0();
	return temp;
}
Rational Rational::operator+=(const int num){
	Rational temp;
	temp.n = this->n + num * this->d;
	temp.d = this->d;
	temp.reduce();
	return temp;
}
Rational Rational::operator*=(const Rational& r){
	Rational temp;
	temp.n = this->n * r.n;
	temp.d = this->d * r.d;
	temp.reduce();
	return temp;
}
Rational Rational::operator*=(const int num){
	this->n *= num;
	this->reduce();
	this->normalize0();
	return *this;
}