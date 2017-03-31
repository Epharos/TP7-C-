class col_chaine
{
	char *D;
	char **I;
	int nbc;
	int nbi;
	int max_nbc;
	int max_nbi;

	public:
		col_chaine(int mnbc, int mnbi);
		~col_chaine();
		bool ajout(char *s);
		void afficher();
		bool present(char *s);
		void etendre(int f);
		void trier();
		int leplusgrand(int n);
		bool present_trie(char *s);

		// ---------------------------

		col_chaine(const col_chaine&);
		bool operator == (const col_chaine&);
		col_chaine & operator = (const col_chaine&);
		col_chaine & operator << (char *);
		col_chaine & operator += (const col_chaine&);
		col_chaine & operator + (const col_chaine&);
		col_chaine & operator + (const char*);
};

