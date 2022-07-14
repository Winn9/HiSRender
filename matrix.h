#pragma once
#include <cassert>
#include <iostream>


template<size_t ROW_SIZE, size_t COL_SIZE, typename T> class Matrix;


template<size_t SIZE, typename T> struct dt {
	static T det(const Matrix<SIZE, SIZE, T>& src)
	{
		T ret = 0;
		for (size_t i = SIZE; i--; ret += src[0][i] * src.cofactor(0, i));
		return ret;
	}
};

template<typename T> struct dt<1, T> {
	static T det(const Matrix<1, 1, T>& src)
	{
		return src[0][0];
	}
};


template<size_t ROW_SIZE, size_t COL_SIZE, typename T> class Matrix
{
private:
	Vector<COL_SIZE, T> rows[ROW_SIZE];
public:
	Matrix() {};
	Vector<COL_SIZE, T>& operator[](const size_t idx)
	{
		assert(idx < ROW_SIZE);
		return rows[idx];
	}

	const Vector<COL_SIZE, T>& operator[](const size_t idx) const
	{
		assert(idx < ROW_SIZE);
		return rows[idx];
	}

	Vector<ROW_SIZE, T> getCol(const size_t idx) const
	{
		assert(idx < COL_SIZE);
		Vector<ROW_SIZE, T> ret;
		for (size_t i = ROW_SIZE; i--; ret[i] = rows[i][idx]);
		return ret;
	}

	void setCol(size_t idx, Vector<ROW_SIZE, T> v)
	{
		assert(idx < COL_SIZE);
		for (size_t i = ROW_SIZE; i--; rows[i][idx] = v[i]);
	}

	static Matrix<ROW_SIZE, COL_SIZE, T> identity()
	{
		Matrix<ROW_SIZE, COL_SIZE, T> ret;
		for (size_t i = ROW_SIZE; i--; )
			for (size_t j = COL_SIZE; j--; ret[i][j] = (i == j));
		return ret;
	}


	Matrix<COL_SIZE, ROW_SIZE, T> transpose()
	{
		Matrix<COL_SIZE, ROW_SIZE, T> ret;
		for (size_t i = COL_SIZE; i--; ret[i] = this->getCol(i));
		return ret;
	}

	Matrix<ROW_SIZE - 1, COL_SIZE - 1, T> get_minor(size_t row, size_t col) const
	{
		Matrix<ROW_SIZE - 1, COL_SIZE - 1, T> ret;
		for (size_t i = ROW_SIZE - 1; i--; )
			for (size_t j = COL_SIZE - 1; j--; ret[i][j] = rows[i < row ? i : i + 1][j < col ? j : j + 1]);
		return ret;
	}


	T det() const
	{
		return dt<COL_SIZE, T>::det(*this);
	}


	T cofactor(size_t row, size_t col) const
	{
		return get_minor(row, col).det() * ((row + col) % 2 ? -1 : 1);
	}


	Matrix<ROW_SIZE, COL_SIZE, T> adjugate() const
	{
		Matrix<ROW_SIZE, COL_SIZE, T> ret;
		for (size_t i = ROW_SIZE; i--; )
			for (size_t j = COL_SIZE; j--; ret[i][j] = cofactor(i, j));
		return ret;
	}


	Matrix<ROW_SIZE, COL_SIZE, T> invert_transpose()
	{
		Matrix<ROW_SIZE, COL_SIZE, T> ret = adjugate();
		T tmp = ret[0] * rows[0];
		return ret / tmp;
	}

	
	Matrix<ROW_SIZE, COL_SIZE, T> invert()
	{
		return invert_transpose().transpose();
	}
};

template<size_t ROW_SIZE, size_t COL_SIZE, typename T> Vector<ROW_SIZE, T> operator*(const Matrix<ROW_SIZE, COL_SIZE, T>& lhs, const Vector<COL_SIZE, T>& rhs)
{
	Vector<ROW_SIZE, T> ret;
	for (size_t i = ROW_SIZE; i--; ret[i] = lhs[i] * rhs);
	return ret;
}

template<size_t R1, size_t C1, size_t C2, typename T>Matrix<R1, C2, T> operator*(const Matrix<R1, C1, T>& lhs, const Matrix<C1, C2, T>& rhs)
{
	Matrix<R1, C2, T> result;
	for (size_t i = R1; i--; )
		for (size_t j = C2; j--; result[i][j] = lhs[i] * rhs.getCol(j));
	return result;
}

template<size_t ROW_SIZE, size_t COL_SIZE, typename T>Matrix<COL_SIZE, ROW_SIZE, T> operator/(Matrix<ROW_SIZE, COL_SIZE, T> lhs, const T& rhs)
{
	for (size_t i = ROW_SIZE; i--; lhs[i] = lhs[i] / rhs);
	return lhs;
}

template <size_t ROW_SIZE, size_t COL_SIZE, class T> std::ostream& operator<<(std::ostream& out, Matrix<ROW_SIZE, COL_SIZE, T>& m)
{
	for (size_t i = 0; i < ROW_SIZE; i++) out << m[i] << std::endl;
	return out;
}

typedef Matrix<4, 4, float> Matrix4f;
typedef Matrix<3, 3, float> Matrix3f;