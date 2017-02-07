#pragma once

#include <cassert>
#include <vector>
#include <iostream>

template <typename T>
class PasswordGenerator 
{
	int m_fromChar;
	int m_toChar;

	int m_fSym;
	int m_eSym;
	int m_f1Sym;
	int m_e1Sym;
	std::vector <T> m_password;

	public:
		PasswordGenerator (int fromChar, int toChar, T fSym, T eSym, T f1Sym, T e1Sym):
				  m_fromChar(fromChar),
				  m_toChar(toChar),
				  m_fSym(fSym),
				  m_eSym(eSym),
				  m_f1Sym(f1Sym),
				  m_e1Sym(e1Sym),
				  m_password(toChar,0)
				  
		{
		//	assert(m_fromChar<m_toChar);
			assert(m_eSym<f1Sym);
			assert(m_fSym<m_eSym);
			assert(m_f1Sym<m_e1Sym);
			
			for (int i=0; i<fromChar; ++i)
			{
				m_password[i]=fSym;
			}
		} 

		bool isEndBorder()
		{	
			for (auto i:m_password)
			{
				if (i!=m_e1Sym)
					return false;
			}
			
			return true;
		}
		
		bool generateNext()
		{
			if (isEndBorder())
				return false;

			for (int i=0;i<m_password.size();++i)
			{
				int sym = m_password[i];
				static const int term = 0;

				if (sym==term)
					sym = m_fSym;
				else
					sym++;

				if ( sym>m_eSym && sym<m_f1Sym)
				{
					sym = m_f1Sym;
				}

				if (sym>m_e1Sym)
				{
					m_password[i]=m_fSym;
				}
				else
				{
					m_password[i]=sym;
					break;
				}
			}
			return true;
		}

		void print()
		{
			using namespace std;
			int i = m_password.size();
			while (i--)
			{
				cout << "|" <<(int)m_password[i]<<" "<<(char)m_password[i] << "|";
			}
			cout << endl;
		}

		const T* get() const 
		{
			return &m_password[0];
		}
		
		
};


