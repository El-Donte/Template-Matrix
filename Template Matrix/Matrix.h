#pragma once
#include <iostream>

void StopProgramm(std::string message) {
	std::cout << message << std::endl;
	std::cout << "press any key to exit programm" << std::endl;
	std::exit(1);
}

template <class T>
class Matrix
{
protected:
	int height;
	int width;
	T** mat;
	void clear() {
		if (mat != nullptr) {
			for (int ii = 0; ii < height; ii++) {
				delete[] mat[ii];
			}
			delete[] mat;
		}
		mat = nullptr;
	}
private:
	bool allocate(int h, int w) {
		if (h <= 0 && w <= 0) {
			return false;
		}
		height = h;
		width = w;
		mat = new T * [height];
		for (int ii = 0; ii < height; ii++) {
			mat[ii] = new T[width];
			for (int jj = 0; jj < width; jj++) {
				mat[ii][jj] = T();
			}
		}
		return true;
	}
	
	void copyTo(T** from) {
		for (int ii = 0; ii < height; ii++) {
			for (int jj = 0; jj < width; jj++) {
				mat[ii][jj] = from[ii][jj];
			}
		}
	}
	
public:

	Matrix(int h, int w) {
		if (h <= 0 || w <= 0) {
			StopProgramm("matrix is empty");
		}
		if (!allocate(h, w)) StopProgramm("matrix is empty");
	}
	Matrix(int size):Matrix(size,size){}
	Matrix():height{0},width{0}, mat{nullptr}{}
	Matrix(const Matrix& matrix) {
		clear();
		allocate(matrix.height,matrix.width);
		copyTo(matrix.mat);
	}
	~Matrix() {
		clear();
	}
	
	auto& operator()(int j, int i) {
		if (j < 0 || j >= height || i < 0 || i >= width)
			StopProgramm("Matrix index error!");
		return mat[j][i];
	}

	auto getMin() {
		auto min = this->mat[0][0];
		for (int j = 0; j < this->height; j++) {
			for (int i = 0; i < this->width; i++) {
				if (this->mat[j][i] < min) min = this->mat[j][i];
			}
		}
		return min;
	}

	auto getMax() {
		auto max = this->mat[0][0];
		for (int j = 0; j < this->height; j++) {
			for (int i = 0; i < this->width; i++) {
				if (this->mat[j][i] > max) max = this->mat[j][i];
			}
		}
		return max;
	}


	friend std::ostream& operator<<(std::ostream& out, const Matrix& m) {
		if (m.mat == nullptr) out << "Empty matrix" << std::endl;
		for (int i = 0; i < m.height; i++) {
			for (int j = 0; j < m.width; j++) {
				out << m.mat[i][j] << " ";
			}
			out << std::endl;
		}
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Matrix& m) {
		for (int i = 0; i < m.height; i++) {
			for (int j = 0; j < m.width; j++) {
				in >> m.mat[i][j];
			}
		}
		return in;
	}
};

template <class T>
class NumberMatrix : public Matrix<T> {
public:
	NumberMatrix(int h, int w): Matrix<T>(h,w){}
	NumberMatrix(int size): Matrix<T>(size){}
	NumberMatrix() :Matrix<T>() {};
	~NumberMatrix() {
		this->clear();
	};

	void SetRand(int max = 100, int min = 0) {
		for (int ii = 0; ii < this->height; ii++) {
			for (int jj = 0; jj < this->width; jj++) {
				this->mat[ii][jj] = (T)(min + rand() % (max - min + 1));
			}
		}
	}

	friend NumberMatrix<T> operator+(const NumberMatrix<T>& mat1, const NumberMatrix<T>& mat2) {
		if (mat1.height != mat2.height || mat1.width != mat2.width) StopProgramm("Matrix not even");
		NumberMatrix<T> mRes(mat1.height, mat1.width);
		for (int ii = 0; ii < mRes.height; ii++) {
			for (int jj = 0; jj < mRes.width; jj++) {
					mRes.mat[ii][jj] = mat1.mat[ii][jj] + mat2.mat[ii][jj];
			}
		}
		
		return mRes;
	}

	friend NumberMatrix<T> operator-(const NumberMatrix<T>& mat1, const NumberMatrix<T>& mat2) {
		if (mat1.height != mat2.height || mat1.width != mat2.width) StopProgramm("Matrix not even");
		NumberMatrix<T> mRes(mat1.height, mat1.width);
		for (int ii = 0; ii < mRes.height; ii++) {
			for (int jj = 0; jj < mRes.width; jj++) {
				mRes[ii][jj] = mat1.mat[ii][jj] - mat2.mat[ii][jj];
			}
		}
		return mRes;
	}

	friend NumberMatrix<T> operator*(const NumberMatrix<T>& mat1, const NumberMatrix<T>& mat2) {
		if (mat1.height != mat2.height || mat1.width != mat2.width) StopProgramm("Matrix not even");
		NumberMatrix<T> mRes(mat1.height, mat1.width);
		for (int ii = 0; ii < mRes.height; ii++) {
			for (int jj = 0; jj < mRes.width; jj++) {
				mRes[ii][jj] = mat1.mat[ii][jj] * mat2.mat[ii][jj];
			}
		}
		return mRes;
	}

	friend NumberMatrix<T> operator/(const NumberMatrix<T>& mat1, const NumberMatrix<T>& mat2) {
		if (mat1.height != mat2.height || mat1.width != mat2.width) StopProgramm("Matrix not even");
		NumberMatrix<T> mRes(mat1.height, mat1.width);
		for (int ii = 0; ii < mRes.height; ii++) {
			for (int jj = 0; jj < mRes.width; jj++) {
				mRes[ii][jj] = mat1.mat[ii][jj] / mat2.mat[ii][jj];
			}
		}
		return mRes;
	}
};