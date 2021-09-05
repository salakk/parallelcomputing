#include <algorithm>
#include <iostream>
#include <vector>
#include<cmath>
#include<time.h>
#include <chrono>
#include <bits/stdc++.h>
using namespace std::chrono;
using namespace std;
//to eliminate duplicate pairs
void duplicate(vector< pair<int, pair<int, int> > > A, int m,int n)
{
        int start = 0;
        int end = m-1;
        int endd=n-1;
        for(int i=0;i<A.size();i++)
        {
        int in=A[i].second.first;
        int im=A[i].second.second;
        for(int j=i+1;j<A.size();j++)
        {
	int* p;
        int* q;
	if((in==A[j].second.first) && (im==A[j].second.second))
        {
        p=&in;
        in=start + rand() % (end - start + 1);
        q=&im;
        im=start + rand() % (endd - start + 1);
//if generated pair are not equal to previous pairs
	if((in!=*p)&&(im!=*q))
        {
        A[j].second.first=in;
        A[j].second.second=im;
	delete p;
	delete q;
//make sure newly generated pairs are not same as other pairs
	duplicate(A,m,n);
        }
        else
        {
        j--;
        }
        }
        }
        }
}
//rendomly generating  matrix and storing in vector in triplet form using pair class;
vector< pair<int, pair<int, int> > > sparse_matrix(int m,int n,int t)
{
        int start = 0;
        int end = m-1;
	int endd=n-1;
	int frq=0;
	int startt=1;
	int enddd=10;
//srand((unsigned) time(0));
	vector< pair<int, pair<int, int> > > matrix_A;
        for(int j=0;j<t;j++)
        { 
	int a=startt + rand() % (enddd-startt+1);
        int b=start + rand() % (end - start + 1);
        int c=start + rand() % (endd - start + 1);
        matrix_A.push_back(make_pair(a, make_pair(b,c)));
	}
//make sure that there is no duplicate pairs  generated
	duplicate(matrix_A,m,n);
	return matrix_A;
}

//elements generated for sparse matrix are stored with there respective values and rest of the location with zero
vector< pair<int, pair<int, int> > > Dense_matrix(vector< pair<int, pair<int, int> > > A, int m,int n)
{
 	vector< pair<int, pair<int, int> > > matrix_B;
	for(int i=0;i<m;i++)
	{
	for(int j=0;j<n;j++)
	{
	for(int k=0;k<A.size();++k)
	{
	if((i==A[k].second.first) && (j==A[k].second.second))
	{
	matrix_B.push_back(make_pair(A[k].first,make_pair(A[k].second.first,A[k].second.second)));
	break;
	}
	else if(A.size()-1==k)
	{
	matrix_B.push_back(make_pair(0,make_pair(i,j)));
	}
	}
	}
	}
	return matrix_B;
}
void  Matrix_Multiplication(vector< pair<int, pair<int, int> > > A , vector< pair<int, pair<int, int> > > B )
{
	vector< pair<int, pair<int, int> > >  V;

	for(int i=0;i<A.size();i++)
	{
	for(int j=0;j<B.size();j++)
	{
	if(A[i].second.second==B[j].second.first)
	{
	int ar=A[i].first*B[j].first;
	int x=A[i].second.first;
	int y=B[j].second.second;
	V.push_back(make_pair(ar, make_pair(x,y)));
	}
	}
	}
/*	 for (int i=0; i<V.size(); i++)
        {
           cout<<V[i].first<<"=("<<V[i].second.first<<","<<V[i].second.second<<")"<<" ";
         }
*/
	int joy;
	for(int i=0;i<V.size();i++)
	{
	int sum=0;
	for(int j=i+1;j<V.size();j++)
	{
	if((V[i].second.first==V[j].second.first) && (V[i].second.first==V[j].second.second))
	{
	sum=sum+V[j].first;
	}
	}
	sum=sum+V[i].first;
/*	cout<<sum<<"=("<<V[i].second.first<<","<<V[i].second.second<<")"<<endl;
*/
	}
}

//main body of the program
int main()
{
        int n,m,p,z;
        typedef std::vector<int> vi;
        float spA,spB,spC,spD;
        cout<<"enter dimension of your matrix m,n,p;"<<endl;
        cin>>m>>n>>p;
        cout<<"enter sparsity spA,spB"<<endl;
        cin>>spA>>spB;

	cout<<"give me two more sparsity value just for comparision"<<endl;
	cin>>spC>>spD;


//start measuring time for sparse matrix
// m*n*spA implies percentage  of entries in matrix which hold data in value ,i have taken ceil value
//calling matrix multiplication 
//stop time 
	auto start = high_resolution_clock::now();
	vector< pair<int, pair<int, int> > > A = sparse_matrix(m,n,ceil(m*n*spA));
	vector< pair<int, pair<int, int> > > B = sparse_matrix(n,m,ceil(n*p*spB));
	Matrix_Multiplication(A,B);
	auto stop = high_resolution_clock::now();

	auto starttt = high_resolution_clock::now();
        vector< pair<int, pair<int, int> > > C = sparse_matrix(m,n,ceil(m*n*spC));
        vector< pair<int, pair<int, int> > > D = sparse_matrix(n,m,ceil(n*p*spD));
        Matrix_Multiplication(C,D);
        auto stoppp = high_resolution_clock::now();

//print generated matrix

/*	cout<<"matrix A"<<endl;
	for (int i=0; i<A.size(); i++)
        {
        cout<<A[i].first<<"=("<<A[i].second.first<<","<<A[i].second.second<<")"<<endl;
        }
	cout<<endl<<"matrix B"<<endl;
 	for (int i=0; i<B.size(); i++)
        {
        cout<<B[i].first<<"=("<<B[i].second.first<<","<<B[i].second.second <<")"<<endl;
        }
	 cout<<endl<<"sparse matrix multiplication"<<endl;
*/

//start measuring time for dense matrix
//A and B are passed to Dense_matrix to keep track of which element holds data
//calling matrix multiplication
//stop time
	auto st = high_resolution_clock::now();	
	vector< pair<int, pair<int, int> > > E = Dense_matrix(A,m,n);
	vector< pair<int, pair<int, int> > > F = Dense_matrix(B,n,p);
        Matrix_Multiplication(E,F);
        auto sto = high_resolution_clock::now();


	auto stt = high_resolution_clock::now();
	vector< pair<int, pair<int, int> > > G = Dense_matrix(C,m,n);
        vector< pair<int, pair<int, int> > > H = Dense_matrix(D,n,p);
        Matrix_Multiplication(G,H);
	auto spp = high_resolution_clock::now();


//print function for Dense matrix
/*      cout<<"Dense matrix A"<<endl;
        for (int i=0; i<C.size(); i++)
        {
        cout<<C[i].first<<"=("<<C[i].second.first<<","<<C[i].second.second<<")"<<endl;
        }
        cout<<endl<<"Dense matrix B"<<endl;
        for (int i=0; i<D.size(); i++)
        {
        cout<<D[i].first<<"=("<<D[i].second.first<<","<<D[i].second.second<<")"<<endl;
        }
	cout<<endl;
	cout<<"dense matrix multiplication"<<endl;
*/


//calculate time and print

	auto duration = duration_cast<microseconds>(stop - start);
	auto duratin = duration_cast<microseconds>(stoppp - starttt);
	auto durationn = duration_cast<microseconds>(sto - st);
	auto durationnn = duration_cast<microseconds>(spp - stt);


//excucation time taken by sparse and dense matrix
	cout<<"        SPARSE MATRIX"<<endl<<endl;
	cout<<"|DENSITY A    "<<"|DENSITY B    "<<"|TIME IN MICRO|"<<endl<<endl;
	cout<<spA<<"           "<<spB<<"              "<<duration.count()<<endl;
	cout<<spC<<"           "<<spD<<"              "<<duratin.count()<<endl;

	cout<<"\n\n\n";

	cout<<"        DENSE MATRIX"<<endl<<endl;
        cout<<"|DENSITY A    "<<"|DENSITY B    "<<"|TIME IN MICRO|"<<endl<<endl;
        cout<<spA<<"           "<<spB<<"              "<<durationn.count()<<endl;
        cout<<spC<<"           "<<spD<<"              "<<durationnn.count()<<endl;
	cout<<"\n\n";
	cout<<" \n  IF U WANT TO SEE MATRIX AND THERE MULTIPLICATION\n";
	cout<<"JUST REMOVE MILTILINE COMMENTS FROM THE PROGRAM i.e /*...*//"<<endl;
	return 0;
}

