void doub(int x) { x = x * 2; }
void trip(int * x) { *x = *x * 3; }
void quad(int & x) { x = x * 5; }

int main() {

	int y = 7;

	doub(y);
	trip(&y);
	quad(y);

	cout<<y<<endl;
	return 0;
}