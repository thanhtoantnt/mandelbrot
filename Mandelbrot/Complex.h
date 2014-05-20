struct Complex{
	double real,img;
	
	Complex(){}
	Complex(double real_part,double img_part){
		real = real_part; img = img_part;
	}
	Complex(const Complex& complex){
		real = complex.real; img = complex.img;
	}

	Complex operator+(const Complex& complex) const{
		return Complex(real + complex.real, img + complex.img);
	}

	Complex operator*(const Complex& complex) const{
		double real_part = real * complex.real - img * complex.img;
		double image_part = real * complex.img + img * complex.real;
		return Complex(real_part,image_part);
	}

	double modulus(){
		return real*real + img *img;
	}
};
