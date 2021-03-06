#pragma once

#include "../Matrix.h"

namespace PDI {

	enum PBMFormat
	{
		P1,
		P2,
		P3,
		P4,
		P5,
		P6
	};

	struct PBMHeader
	{
		PBMFormat format;
		int width;
		int height;

		uint8_t limit;
	};

	struct PBMReader
	{
		PBMReader(std::ifstream& input)
			: m_Input(input)
		{

		}

		bool HasNext()
		{
			return !m_Input.eof();
		}

		int Next()
		{
			int n;
			m_Input >> n;
			return n;
		}

		std::ifstream &m_Input;
	};

	struct PBMWriter
	{
		PBMWriter(std::ofstream& output)
			: m_Output(output)
		{

		}

		void Write(int n)
		{
			m_Output << n << " ";
		}
		
		void NewLine()
		{
			m_Output << "\n";
		}

		std::ofstream& m_Output;
	};

	class PBMMatrix
	{
	public:
		static Matrix<int> Load(const std::string& path);
		static void Save(const std::string& path, const Matrix<int>& matrix);

		static Matrix<int> Negative(const Matrix<int>& matrix);
		static Matrix<int> Rotate90(const Matrix<int>& matrix);

	protected:
		static PBMHeader ReadHeader(std::ifstream& file);
		static void WriteHeader(std::ofstream& file, PBMFormat format, Matrix<int> matrix);
	};
}