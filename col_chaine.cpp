#include "col_chaine.h"
#include <string.h>
#include <iostream>

using namespace std;

col_chaine::col_chaine(int mnbc, int mnbi)
{
	max_nbc=mnbc;
	max_nbi=mnbi;

	D=new char[mnbc];
	I=new char *[mnbi];

	nbc=0;
	nbi=0;
}


col_chaine::~col_chaine()
{
	delete [] D;
	delete [] I;
}

bool col_chaine::ajout(char *s)
{
	int nbcr=max_nbc-nbc;
	int l=strlen(s)+1;


	if(l>nbcr || nbi==max_nbi) return false;
	if(nbi==0) I[nbi]=D;
	else I[nbi]=I[nbi-1]+l;
	strcpy(I[nbi],s);
	nbi++;
	nbc+=l;
	return true;
}

void col_chaine::afficher()
{
	for(int i=0;i<nbi;i++) cout<<I[i]<<" ";
	cout<<endl;
}

bool col_chaine::present(char *s)
{
	for(int i=0;i<nbi;i++)
	{
		if(strcmp(s,I[i])==0) return true;
	}
	return false;
}

void col_chaine::etendre(int factor)
{
	col_chaine * n = new col_chaine(factor * max_nbc, factor * max_nbi);

	for(int i = 0 ; i < nbi ; i++)
	{
		n->ajout(I[i]);
	}

	delete [] D;
	delete [] I;

	max_nbc *= factor;
	max_nbi *= factor;
	D = n->D;
	I = n->I;
}

int col_chaine::leplusgrand(int n)
{
	int ip=0;
	for(int i=0;i<n;i++)
	{
		if(strcmp(I[i],I[ip])>0) ip=i;
	}
	return ip;
}

void col_chaine::trier()
{
	for(int n=nbi;n>1;n--)
	{
		int ip=leplusgrand(n);
		char *aux=I[ip];
		I[ip]=I[n-1];
		I[n-1]=aux;
	}
}

bool col_chaine::present_trie(char *s)
{
	if(strcmp(s,I[0])<0 || strcmp(s,I[nbi-1])>0 ) return false;
	int d=0,f=nbi;
	while((f-d)>1)
	{
		int m=(f+d)/2;
		if(strcmp(s,I[m])<0) f=m;
		else d=m;
	}
	if(strcmp(s,I[d])==0) return true;
	else return false;
}



//  ---------------------------------------------------

col_chaine::col_chaine(const col_chaine& copy) : col_chaine(copy.max_nbc, copy.max_nbi)
{
	for(int i = 0 ; i < copy.nbi ; i++)
	{
		ajout(copy.I[i]);
	}
}

bool col_chaine::operator == (const col_chaine& c)
{
	if(nbi != c.nbi)
	{
		return false;
	}

	for(int i = 0 ; i < nbi ; i++)
	{
		if(!present(c.I[i]))
		{
			return false;
		}
	}

	return true;
}

col_chaine& col_chaine::operator = (const col_chaine& c)
{
	max_nbc = c.max_nbc;
	max_nbi = c.max_nbi;

	D = new char[c.max_nbc];
	I = new char*[c.max_nbi];

	nbc = 0;
	nbi = 0;

	for(int i = 0 ; i < c.nbi ; i++)
	{
		ajout(c.I[i]);
	}

	return *this;
}

col_chaine& col_chaine::operator << (char * c)
{
	ajout(c);
	return *this;
}

col_chaine& col_chaine::operator += (const col_chaine& c)
{
	for(int i = 0 ; i < c.nbi ; i++)
	{
		if(!ajout(c.I[i]))
		{
			etendre(2);
			i--;
		}
	}

	return *this;
}

col_chaine& col_chaine::operator + (const col_chaine& c)
{
	col_chaine * n = new col_chaine(c);

	(*n) += (*this);

	return (*n);
}
