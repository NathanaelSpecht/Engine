
/* Copyright (C) 2022 - 2023 Nathanael Specht
 * API for vector and matrix math
 */

#ifndef NGVEC_H
#define NGVEC_H

#include "ngcore.h"

namespace ng {
	
	double sqlen (const Vec2& a);
	double len (const Vec2& a);
	double trace (const Mat2& A);
	double det (const Mat2& A);
	double dot (const Vec2& a, const Vec2& b);
	Vec2 unit (const Vec2& a);
	Mat2 transpose (const Mat2& A);
	Mat2 adj (const Mat2& A);
	Mat2 inv (const Mat2& A);
	
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
		double dot (const Vec2& b) const; // dot(this,b)
		double sqlen () const; // sqlen(this)
		double len () const; // len(this)
		Vec2 unit () const; // unit(this)
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
		double trace () const; // trace(this)
		double det () const; // det(this)
		Mat2 transpose () const; // transpose(this)
		Mat2 adj () const; // adj(this)
		Mat2 inv () const; // inv(this)
	};
	
	// might add this if needed for physics
	// tensor in R2x2x2
	/*
	class Tensor2 {
	public:
		Mat2 r;
		Mat2 s;
	}
	*/
	
} // ng

#endif // NGVEC_H


