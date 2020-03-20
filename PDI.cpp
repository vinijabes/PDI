// PDI.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <time.h>

#include "src/Matrix.h"
#include "src/PBM/PBMMatrix.h"

class MatrixProxy
{
protected:
	struct ProxyValue
	{
		ProxyValue(int& element) :
			m_Element(element)
		{}

		int& operator=(const int& other)
		{
			if (other > 100)
				m_Element = 100;
			else if (other < 0)
				m_Element = 0;
			else
				m_Element = other;

			return m_Element;
		}

		operator int()
		{
			return m_Element;
		}

		int& m_Element;
	};

	struct ProxyElement
	{
		ProxyElement(int* element)
			: m_Elements(element)
		{}

		ProxyValue operator[](int index)
		{
			auto value = ProxyValue(m_Elements[index]);
			return value;
		}

		int* m_Elements;
	};

public:
	MatrixProxy(PDI::Matrix<int>& matrix)
		: m_Matrix(matrix)
	{}

	MatrixProxy(PDI::Matrix<int>&& matrix)
		: m_Matrix(std::move(matrix))
	{}

	ProxyElement operator[](int index)
	{
		return ProxyElement((m_Matrix)[index]);
	}

	operator PDI::Matrix<int>() { return m_Matrix; }

	operator PDI::Matrix<int>& () { return m_Matrix; }

	PDI::Matrix<int>& operator*()
	{
		return m_Matrix;
	}

private:
	PDI::Matrix<int> m_Matrix;
};

typedef void (PDI::Matrix<int>::* pointer)();

int main()
{
	pointer teste = &PDI::Matrix<int>::Print;

	std::cout << "INIT" << std::endl;
	PDI::Matrix<int> lena = PDI::PBMMatrix::Load("lena640.pgm");

	PDI::PBMMatrix::Save("lenaminus640.pgm", lena - 100);
	PDI::PBMMatrix::Save("lenaplus640.pgm", lena + 40);
	PDI::PBMMatrix::Save("lenanegative640.pgm", PDI::PBMMatrix::Negative(lena));

	auto rotated = PDI::PBMMatrix::Rotate90(lena);
	PDI::PBMMatrix::Save("lenarotate640.pgm", rotated);

	/*(*c) = (*a + *b);
	PDI::Matrix<int>::Save("teste.txt", *c);*/
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
