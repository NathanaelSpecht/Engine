
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
	Mat2 transpose (const Mat2& A);
	Mat2 adj (const Mat2& A);
	Mat2 inv (const Mat2& A);
	
	// transforms for R2
	Vec2 origin ();
	Vec2 origin (double x, double y);
	Mat2 scale ();
	Mat2 scale (double i, double j);
	Mat2 scale (const Vec2& dim);
	double scale (double src, double dest);
	Mat2 rotate ();
	Mat2 rotate (double a);
	
	// boxes and rects in R2
	Box2 box (double x, double y, double rx, double ry);
	Box2 box (const Vec2& p, const Vec2& dim);
	Rect2 rect (double x, double y, double w, double h);
	Rect2 rect (const Vec2& p, const Vec2& dim);
	
	// spaces in R2
	Space2 space (double x, double y);
	Space2 space (double x, double y, double a);
	Space2 space (double x, double y, double i, double j);
	Space2 space (double x, double y, double i, double j, double a);
	Space2 space (const Vec2& p);
	Space2 space (const Vec2& p, double a);
	Space2 space (const Vec2& p, const Vec2& dim);
	Space2 space (const Vec2& p, const Vec2& dim, double a);
	
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
		Vec2 operator- (double x) const;
		Vec2 operator- (const Vec2& b) const;
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
		Mat2 operator- (double x) const;
		Mat2 operator- (const Mat2& B) const;
		Mat2 operator* (double x) const;
		Vec2 operator* (const Vec2& b) const;
		Mat2 operator* (const Mat2& B) const;
	};
	
	// box in R2
	class Box2 {
	public:
		double x; // (x,y) is center
		double y;
		double rx; // w/2
		double ry; // h/2
		Box2 ();
		Box2 (double x, double y, double rx, double ry);
		Box2 (const Box2& box);
		Box2 (const Rect2& rect);
		void set (double x, double y, double rx, double ry);
		void set_p (const Vec2& p);
		void set_dim (const Vec2& dim);
		Vec2 p () const; // {x,y}
		Vec2 dim () const; // {rx,ry}
		//Vec2 i () const; // {rx,0}
		//Vec2 j () const; // {0,ry}
		Box2& operator= (const Rect2& rect);
		bool contains (const Vec2& p) const;
	};
	
	// rect in R2
	class Rect2 {
	public:
		double x; // (x,y) is corner
		double y;
		double w;
		double h;
		Rect2 ();
		Rect2 (double x, double y, double w, double h);
		Rect2 (const Rect2& rect);
		Rect2 (const Box2& box);
		void set (double x, double y, double w, double h);
		void set_p (const Vec2& p);
		void set_dim (const Vec2& dim);
		Vec2 p () const; // {x,y}
		Vec2 dim () const; // {w,h}
		//Vec2 i () const; // {w,0}
		//Vec2 j () const; // {0,h}
		Rect2& operator= (const Box2& box);
		bool contains (const Vec2& p) const;
	};
	
	// space in R2 and matrix representation
	class Space2 {
	private:
		Vec2 origin;
		Mat2 scale; // represents scale by i and j along x and y axes.
		Mat2 inv_scale;
		Mat2 rotate; // represents rotation by a.
		Mat2 inv_rotate;
	public:
		double x;
		double y;
		double i;
		double j;
		double a;
		Space2 ();
		Space2 (double x, double y, double i, double j, double a);
		Space2 (const Space2& space);
		// set and recompute.
		void set (double x, double y, double i, double j, double a);
		// set x and y and recompute origin.
		void set_p (const Vec2& p);
		// set i and j and recompute scale and inv_scale.
		void set_dim (const Vec2& dim);
		// set a and recompute rotate and inv_rotate.
		void set_a (double a);
		// get x and y as p.
		Vec2 p () const;
		// get i and j as dim.
		Vec2 dim () const;
		// get a. (Included for consistency. You don't have to use this)
		double a () const;
		
		// These functions mimic the vector transform Av+b,
		// or the affine transform [A b][v],
		//                         [0 1][1]
		// where A is the basis, and b is the origin.
		// The affine transform is NOT used, so basis and origin may change independently.
		// Likewise, the basis is represented by independent scale and rotation.
		// The inverse matrices are pre-computed, so divide is as fast as multiply.
		
		// Remove this space from v. (Make v absolute from space).
		// Multiply to remove a space, as you multiply to remove a basis.
		Vec2 operator* (const Vec2& v) const;
		Box2 operator* (const Box2& box) const;
		Rect2 operator* (const Rect2& rect) const;
		double operator* (double a) const;
		Space2 operator* (const Space2& space) const;
		// Apply this space to v. (Make v relative to space).
		// Divide to apply a space, as you divide (multiply by inverse) to apply a basis.
		Vec2 operator/ (const Vec2& v) const;
		Box2 operator/ (const Box2& box) const;
		Rect2 operator/ (const Rect2& rect) const;
		double operator/ (double a) const;
		Space2 operator/ (const Space2& space) const; // nested space
	};
	
	/*
	// matrix functions in R3
	double sqlen (const Vec3& a);
	double len (const Vec3& a);
	double trace (const Mat3& A);
	double det (const Mat3& A);
	double dot (const Vec3& a, const Vec3& b);
	Vec3 unit (const Vec3& a);
	Vec3 affine (const Vec2& a);
	Mat3 affine (const Mat2& A, const Vec2& b);
	Vec2 project (const Vec3& a);
	Mat2 project (const Mat3& A);
	Mat3 transpose (const Mat3& A);
	Mat3 minor (const Mat3& A);
	Mat3 adj (const Mat3& A);
	Mat3 inv (const Mat3& A);
	
	// affine transforms for R2
	Mat3 scale (double i, double j);
	Mat3 scale (double src_dim, double dest_dim);
	Mat3 origin (const Vec2& p); // change of origin
	Mat3 origin (double x, double y);
	Mat3 basis (double i, double j); // change of basis
	Mat3 rotate (double a);
	Mat3 space (const Mat3& origin);
	Mat3 space (const Mat3& origin, const Mat3& basis);
	Mat3 space (const Mat3& origin, const Mat3& basis, const Mat3& rotate);
	Mat3 space (double x, double y);
	Mat3 space (double x, double y, double i, double j);
	Mat3 space (double x, double y, double i, double j, double a);
	
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
	*/
	
} // ng

#endif // NGVEC_H


