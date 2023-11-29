#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXd;

MatrixXd getPermuationMatrix(size_t n, size_t i, size_t j)
{
	MatrixXd m(n, n);

	for (size_t k = 0; k < n; k++)
	{
		if (k == i)
		{
			m(j, k) = 1;
			continue;
		}
		if (k == j)
		{
			m(i, k) = 1;
			continue;
		}

		m(k, k) = 1;
	}

	return m;
}

MatrixXd matrixFixup(MatrixXd& m, size_t i)
{
	for (size_t j = i + 1; j < m.cols(); j++)
	{
		if (m(i, j) != 0)
		{
			return getPermuationMatrix(m.cols(), 0, j);
		}
	}
}

MatrixXd findB(MatrixXd m, size_t i = 0)
{
	if(m(i, i) == 0)
	{
		MatrixXd perm = matrixFixup(m, i);
		return perm * findB(perm.transpose() * m * perm, i);
	}

	// Find the current matrix
	MatrixXd B(m.rows(), m.cols());
	B.setIdentity();
	for (size_t j = i + 1; j < m.cols(); j++)
	{
		B(i, j) = -(m(i, j)/m(i, i));
	}

	if (i + 2 < m.rows())
		return B * findB(B.transpose() * m * B, i+1);

	return B;
}

int main()
{
	size_t n;
	std::cout << "Solves an n by n matrix. n is:" << std::endl;
	std::cin >> n;

	MatrixXd m(n, n);

	std::cout << "Write out the matrix:" << std::endl;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			std::cin >> m(i, j);
		}
	}

//	MatrixXd m(3, 3);
//	m(0,0) = 1;
//	m(0, 1) = 5;
//	m(0, 2) = 2;
//	m(1, 0) = 5;
//	m(1, 1) = 3;
//	m(1, 2) = 0;
//	m(2, 0) = 2;
//	m(2, 1) = 0;
//	m(2, 2) = 5;

	auto B = findB(m);

	std::cout << "The matrix B is:" << std::endl;
	std::cout << B << std::endl << std::endl;

	std::cout << "The resulting diagonal matrix is:" << std::endl;
	std::cout << B.transpose() * m * B << std::endl;

	return 0;
}