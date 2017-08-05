//Adrian
//Fuer diese .hpp gibt es keine .cpp Datei.
struct PrimeArray {
	unsigned long long primeArray[1000000];

	/*Ein neues Array fuer die LinkedList.*/
	static PrimeArray* initPrimeArray() {
		PrimeArray *primeArray = new PrimeArray;
		return  primeArray;
	}
};

