
/* Copyright (C) 2022 - 2023 Nathanael Specht
 * API for vector and matrix math
 */

#ifndef NGVEC_H
#define NGVEC_H

#include "ngcore.h"

namespace ng {
	
	// matrix functions in R2
	double sqlen (const Vec2& a);
	double len (const Vec2& a);
	double trace (const Mat2& A);
	double det (const Mat2& A);
	double det (double a, double b, double c, double d);
	double dot (const Vec2& a, const Vec2& b);
	Vec2 unit (const Vec2& a);
	Vec2 project (const Vec3& a);
	Mat2 project (const Mat3& A);
	Mat2 transpose (const Mat2& A);
	Mat2 adj (const Mat2& A);
	Mat2 inv (const Mat2& A);
	
	// matrix functions in R3
	double sqlen (const Vec3& a);
	double len (const Vec3& a);
	double trace (const Mat3& A);
	double det (const Mat3& A);
	double dot (const Vec3& a, const Vec3& b);
	Vec3 unit (const Vec3& a);
	Vec3 affine (const Vec2& a);
	Mat3 affine (const Mat2& A, const Vec2& b);
	Mat3 transpose (const Mat3& A);
	Mat3 minor (const Mat3& A);
	Mat3 adj (const Mat3& A);
	Mat3 inv (const Mat3& A);
	
	// affine transforms for R2
	Mat3 scale (double i, double j);
	Mat3 scale (double srci, double srcj, double desti, double destj);
	Mat3 origin (const Vec2& p); // change of origin
	Mat3 origin (double x, double y);
	Mat3 basis (const Vec2& i, const Vec2& j); // change of basis
	Mat3 basis (double i, double j);
	Mat3 rotate (double a);
	Mat3 space (const Mat3& origin);
	Mat3 space (const Mat3& origin, const Mat3& basis);
	Mat3 space (const Mat3& origin, const Mat3& basis, const Mat3& rotate);
	Mat3 space (double x, double y);
	Mat3 space (double x, double y, double i, double j);
	Mat3 space (double x, double y, double i, double j, double a);
	
	// vector in R2
	class Vec2 {
	public:
		double x;
		double y;
		Vec2 ();
		Vec2 (double x, double y);
		Vec2 (const Vec& a);
		void set (double x, double y);
		Vec2 operator+ (double x) const;
		Vec2 operator+ (const Vec2& b) const;
		Vec2 operator* (double x) const;
		double operator* (const Vec2& b) const; // dot(this,b)
	};
	
	// matrix in R2x2
	class Mat2 {
	public:
		double a; double b;
		double c; double d;
		Mat2 ();
		Mat2 (double a, double b, double c, double d);
		Mat2 (const Mat2& A);
		void set (double a, double b, double c, double d);
		void set_cols (const Vec2& a, const Vec2& b);
		void set_rows (const Vec2& a, const Vec2& b);
		Vec2 col1 () const;
		Vec2 col2 () const;
		Vec2 row1 () const;
		Vec2 row2 () const;
		Mat2 operator+ (double x) const;
		Mat2 operator+ (const Mat2& B) const;
		Mat2 operator* (double x) const;
		Vec2 operator* (const Vec2& b) const;
		Mat2 operator* (const Mat2& B) const;
	};
	
	// vector in R3, or affine vector for R2
	class Vec3 {
	public:
		double x;
		double y;
		double z;
		Vec3 ();
		Vec3 (double x, double y, double z);
		Vec3 (const Vec3& a);
		void set (double x, double y, double z);
		Vec3 operator+ (double x) const;
		Vec3 operator+ (const Vec3& b) const;
		Vec3 operator* (double x) const;
		double operator* (const Vec3& b) const; // dot(this,b)
	};
	
	// matrix in R3x3, or affine matrix for R2x2
	class Mat3 {
	public:
		double a; double b; double c;
		double d; double e; double f;
		double g; double h; double i;
		Mat3 ();
		Mat3 (double a, double b, double c,
			double d, double e, double f,
			double g, double h, double i);
		Mat3 (const Mat3& A);
		void set (double a, double b, double c,
			double d, double e, double f,
			double g, double h, double i);
		void set_cols (const Vec3& a, const Vec3& b, const Vec3& c);
		void set_rows (const Vec3& a, const Vec3& b, const Vec3& c);
		Vec3 col1 () const;
		Vec3 col2 () const;
		Vec3 col3 () const;
		Vec3 row1 () const;
		Vec3 row2 () const;
		Vec3 row3 () const;
		Mat3 operator+ (double x) const;
		Mat3 operator+ (const Mat3& B) const;
		Mat3 operator* (double x) const;
		Vec3 operator* (const Vec3& b) const;
		Mat3 operator* (const Mat3& B) const;
	};
	
} // ng

#endif // NGVEC_H


