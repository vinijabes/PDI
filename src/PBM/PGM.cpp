#include "PGM.h"

namespace PDI {
	Matrix<int> PGM::Load(Matrix<int>& matrix, PBMReader& input)
	{
		auto data = matrix.GetData();
		int i = matrix.GetWidth() * matrix.GetHeight();
		while (i--)
		{
			*data++ = input.Next();
		}

		std::cout << i << std::endl;
		return matrix;
	}

	void PGM::Save(const Matrix<int>& matrix, PBMWriter& output)
	{
		int i = matrix.GetHeight() * matrix.GetWidth();
		auto data = matrix.GetData();
		while (i--)
		{
			output.Write(*data++);
			if (i % matrix.GetWidth() == 0)output.NewLine();
		}
	}
}
