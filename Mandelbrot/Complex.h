/*
struct of complex number with real part and image part
*/
struct Complex{
	double real,img;
	
	Complex(){}  // construction
	Complex(double real_part,double img_part){  // parameterized construction
		real = real_part; img = img_part;
	}
	Complex(const Complex& complex){  // parameterized construction
		real = complex.real; img = complex.img;
	}

	Complex operator+(const Complex& complex) const{ // addition operation
		return Complex(real + complex.real, img + complex.img);
	}

	Complex operator*(const Complex& complex) const{  // multiple with another complex number operation
		double real_part = real * complex.real - img * complex.img;
		double image_part = real * complex.img + img * complex.real;
		return Complex(real_part,image_part);
	}

	double modulus(){  // calculus the absolute value of a complex number
		return real*real + img *img;
	}
};
