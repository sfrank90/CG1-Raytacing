#include "Vec3f.h"
#include "Triangle.h"
#include <iostream>

std::ostream& operator<<(std::ostream& ostr, cg1::Vec3f const& v)  { 
	ostr << "( " << v.x << " | " << v.y << " | " << v.z << " )";
	return ostr;
}

int main() {
	/*float pArray[] = {2.0f,2.0f,0.0f};

	cg1::Vec3f v1(1.0f),
		       v2(0.0f, -1.0f, 0.0f),
			   v3(pArray);

	std::cout << "Vectors:" << std::endl
		      << "v1 = " << v1 << std::endl
			  << "v2 = " << v2 << std::endl
			  << "v3 = " << v3 << std::endl;

	std::cout << "v1 + v2 = " << v1+v2 << std::endl;
	std::cout << "v2 - v3 = " << v2-v3 << std::endl;
	std::cout << "v1 * v3 (dot) = " << v1*v3 << std::endl;
	std::cout << "Length of v3 = " << v3.length() << std::endl << std::endl;


	std::cout << "v1,v2,v3 are defining a triangle t. " << std::endl;
	cg1::Triangle t(v1,v2,v3);
	std::cout << "Normal vector of t: " << t.getNormal() << std::endl;*/

	//Test section for comparision with written calculations
	std::cout << "\nTest section for comparision with written calculations" << std::endl;

	//Test Vectors for addition
	cg1::Vec3f vecAdd1a(3.0f,4.0f,1.0f), vecAdd1b(1.0f,0.0f,1.0f),
			   vecAdd2a(1.0f,1.0f,1.0f), vecAdd2b(-1.0f,2.0f,3.0f),
			   vecAdd3a(0.0f,0.0f,1.0f), vecAdd3b(2.0f,2.0f,2.0f);

	std::cout << "\nTest section addition:" << std::endl;
	std::cout << "a " << vecAdd1a << " + b " << vecAdd1b << " = " << vecAdd1a+vecAdd1b << std::endl;
	std::cout << "a " << vecAdd2a << " + b " << vecAdd2b << " = " << vecAdd2a+vecAdd2b << std::endl;
	std::cout << "a " << vecAdd3a << " + b " << vecAdd3b << " = " << vecAdd3a+vecAdd3b << std::endl;

	//Test Vectors for subtraction
	cg1::Vec3f vecSub1a(3.0f,3.0f,3.0f), vecSub1b(1.0f,2.0f,3.0f),
			   vecSub2a(0.0f,0.0f,1.0f), vecSub2b(1.0f,2.0f,2.0f),
			   vecSub3a(4.0f,4.0f,3.0f), vecSub3b(2.0f,1.0f,0.0f);

	std::cout << "\nTest section subtraction:" << std::endl;
	std::cout << "a " << vecSub1a << " - b " << vecSub1b << " = " << vecSub1a-vecSub1b << std::endl;
	std::cout << "a " << vecSub2a << " - b " << vecSub2b << " = " << vecSub2a-vecSub2b << std::endl;
	std::cout << "a " << vecSub3a << " - b " << vecSub3b << " = " << vecSub3a-vecSub3b << std::endl;

	//Test Vectors for length
	cg1::Vec3f vecLen1(3.0f,1.0f,4.0f),
			   vecLen2(1.0f,3.0f,0.0f),
			   vecLen3(1.0f,1.0f,1.0f);

	std::cout << "\nTest section length calculation:" << std::endl;
	std::cout << "Length of a " << vecLen1 << " = " << vecLen1.length() << std::endl;
	std::cout << "Length of a " << vecLen2 << " = " << vecLen2.length() << std::endl;
	std::cout << "Length of a " << vecLen3 << " = " << vecLen3.length() << std::endl;

	//Test Vectors for dot product
	cg1::Vec3f vecDot1a(2.0f,1.0f,4.0f), vecDot1b(1.0f,3.0f,3.0f),
			   vecDot2a(0.0f,3.0f,4.0f), vecDot2b(7.0f,4.0f,1.0f),
			   vecDot3a(10.0f,-4.0f,1.0f), vecDot3b(3.0f,7.0f,5.0f);

	std::cout << "\nTest section dot product:" << std::endl;
	std::cout << "a " << vecDot1a << " dot b " << vecDot1b << " = " << vecDot1a*vecDot1b << std::endl;
	std::cout << "a " << vecDot2a << " dot b " << vecDot2b << " = " << vecDot2a*vecDot2b << std::endl;
	std::cout << "a " << vecDot3a << " dot b " << vecDot3b << " = " << vecDot3a*vecDot3b << std::endl;

	//Test section normal of a triangle
	std::cout << "\nTest section normal of a triangle:" << std::endl;

	cg1::Vec3f vec1_0(3.0f,3.0f,1.0f), vec1_1(1.0f,7.0f,4.0f), vec1_2(5.0f,4.0f,1.0f);
	cg1::Triangle t1(vec1_0,vec1_1,vec1_2);
	std::cout << "Vectors of triangle t1: v0 " << vec1_0 << ", v1 " << vec1_1 << ", v2 " << vec1_2 << std::endl;
	std::cout << "Normal vector of t1: " << t1.getNormal() << std::endl;

	cg1::Vec3f vec2_0(10.0f,3.0f,1.0f), vec2_1(7.0f,5.0f,-3.0f), vec2_2(1.0f,2.0f,5.0f);
	cg1::Triangle t2(vec2_0,vec2_1,vec2_2);
	std::cout << "Vectors of triangle t2: v0 " << vec2_0 << ", v1 " << vec2_1 << ", v2 " << vec2_2 << std::endl;
	std::cout << "Normal vector of t2: " << t2.getNormal() << std::endl;

	cg1::Vec3f vec3_0(7.0f,5.0f,6.0f), vec3_1(13.0f,14.0f,3.0f), vec3_2(17.0f,7.0f,4.0f);
	cg1::Triangle t3(vec3_0,vec3_1,vec3_2);
	std::cout << "Vectors of triangle t3: v0 " << vec3_0 << ", v1 " << vec3_1 << ", v3 " << vec3_2 << std::endl;
	std::cout << "Normal vector of t3: " << t3.getNormal() << std::endl;

	std::cin.get();
	return 0;
}