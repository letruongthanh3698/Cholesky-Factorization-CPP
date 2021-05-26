// Multifrontal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <cmath>
#include <sstream>

using namespace std;

#include "main.h"
#include "Matrix.h"
#include "Node.h"
#include "ShortenMatrix.h"
#include "BinarySearch.h"

#define mETREE_PRINTED	true

uint64_t nodecnt_U64;
Node* Nodes;
Node* ETreeNodes;
vector<sElement> L_VE;
uint64_t precision = 15;
string filename = "s3rmt3m1.mtx";

static void RestoreSystem(vector<sElement> input_VE);
static void ConstructEliminationTree();
static void CalculateLMatrix();

int main()
{
	cout << "Cholesky Factorization based on Multifrontal method!\n";
	cout << "Enter Data filename (without \"txt\"):";
	cin >> filename;
	ifstream input_file(filename + ".txt");
	if (!input_file.is_open())
		throw "Can not open file!";

	cout << "Data loading!\n";

	uint64_t row, col, numberelement;
	input_file >> row >> col;
	input_file >> numberelement;

	nodecnt_U64 = row;
	vector<sElement> input_VE;
	sElement element;
	for (uint64_t index = 0; index < numberelement; index++)
	{
		input_file >> element.rowindex_U64 >> element.colindex_U64 >> element.value_D;
		input_VE.push_back(element);
	}

	cout << "Load Data Successfully!\n";
	cout << "Calculating!\n";

	clock_t start, end;
	double cpu_time_used;

	start = clock();

	RestoreSystem(input_VE);
	input_VE.clear();
	ConstructEliminationTree();
#if mETREE_PRINTED
	for (uint64_t i = 0; i < nodecnt_U64; i++)
		cout << "Node name:" << i + 1 << ", Parent:" << ETreeNodes[i].Parent + 1 << "\n";
#endif

	CalculateLMatrix();

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << "Executation time: " << cpu_time_used << ". Saving!\n";

	ofstream output_file(filename + ".M.result.txt");
	//output_file.setf(ios::fixed);
	output_file.setf(ios::showpoint);
	output_file.precision(precision);

	output_file << row << " " << col << "\n";
	output_file << L_VE.size() << "\n";

	uint64_t cnt = 0;
	for (uint64_t i = 0; i < L_VE.size(); i++)
		output_file << L_VE.at(i).rowindex_U64 << " " << L_VE.at(i).colindex_U64 << " " << L_VE.at(i).value_D << "\n";

	output_file.close();
	cout << "Save done. Press Enter to continue!\n";
	cin.get();
	cin.get();
	return 0;
}

void RestoreSystem(vector<sElement> input_VE)
{
	Nodes = new Node[nodecnt_U64];//(Node*)calloc(nodecnt_U64,sizeof(Node));
								  //for (uint64_t i=0;i<nodecnt_U64;i++)
	for (uint64_t i = 0; i < nodecnt_U64; i++)
		Nodes[i] = Node(i);

	for (uint64_t i = 0; i < input_VE.size(); i++)
		Nodes[input_VE[i].rowindex_U64].AddChild(input_VE[i].colindex_U64, input_VE[i].value_D, NONEEDSORT);
}

void ConstructEliminationTree()
{
	ETreeNodes = new Node[nodecnt_U64];//(Node*)calloc(nodecnt_U64,sizeof(Node));
	uint64_t index;
	uint64_t start;
	tNODENAME nodename;
	tNODENAME superparentname;
	bool IsChildNodeExist;
	for (uint64_t i = 0; i < nodecnt_U64; i++)
	{
		ETreeNodes[i] = Node(i);
		index = i;
		start = Nodes[i].Child.size();
		for (int64_t j = start - 1; j >= 0; j--)
		{
			nodename = Nodes[i].Child.at(j).NodeName;
			if (nodename < i)
			{
				superparentname = ETreeNodes[nodename].GetSuperParent(ETreeNodes);
				if (superparentname != i)
				{
					ETreeNodes[superparentname].UpdateParent(i);
					ETreeNodes[i].AddChild(superparentname, 0, NONEEDSORT);


					IsChildNodeExist = Nodes[i].IsChildNodeExist(superparentname);

					if (!IsChildNodeExist)
					{
						Nodes[i].AddChild(superparentname, 0, NEEDSORT);
					}
				}
				ETreeNodes[nodename].SuperParent = i;
			}
		}
	}
}

static double GetNameOfU(void *array, int64_t pos_I64);
static double GetNameOfChild(void *array, int64_t pos_I64);
void CalculateLMatrix()
{
	vector<ShortenMatrix> U_VSM;
	vector<tNODENAME> UName_V;
	uint64_t len;
	bool *mark = (bool*)calloc(nodecnt_U64, sizeof(bool));
	uint64_t left;
	uint64_t right;
	uint64_t cur;
	uint64_t cnt;
	int64_t pos;
	vector<tNODENAME> indextemp_V;
	BinarySearch bs;
	ShortenMatrix *U_PSM = 0;
	Matrix *matrixtemp_PM = 0;
	sElement element;

	Matrix U_M;
	Matrix V_M;
	Matrix VT_M;
	Matrix VVT_M;
	Matrix VVT_d_B_M;
	vector<tNODENAME> queue_V;
	ShortenMatrix temp;
	ShortenMatrix F;

	for (uint64_t index = 0; index < nodecnt_U64; index++)
	{
		len = U_VSM.size();
		queue_V.clear();
		queue_V.push_back(index);
		left = 0;
		right = 0;
		// U_PSM=0;
		if (U_PSM != NULL)
		{
			U_PSM->Free();
			free(U_PSM);
			U_PSM = 0;
		}

		while (left <= right)
		{
			cur = queue_V.at(left);
			left++;
			pos = -1;
			if ((int64_t)(UName_V.size()) > 0)
				pos = bs.ExactlySearch(0, (int64_t)(UName_V.size()) - 1, cur, (void*)&UName_V[0], GetNameOfU);

			if (pos != -1)
			{
				if (U_PSM == 0)
				{
					U_PSM = (ShortenMatrix*)calloc(1, sizeof(ShortenMatrix));
					*U_PSM = U_VSM.at(pos);
				}
				else
					*U_PSM = U_PSM->ExtendAdd(U_VSM.at(pos));

				U_VSM.at(pos).Free();
				U_VSM.erase(U_VSM.begin() + pos);
				UName_V.erase(UName_V.begin() + pos);
			}

			for (uint64_t i = 0; i < ETreeNodes[cur].Number_of_Child_U64; i++)
				if (mark[ETreeNodes[cur].Child.at(i).NodeName] == false)
				{
					right++;
					queue_V.push_back(ETreeNodes[cur].Child.at(i).NodeName);
					mark[ETreeNodes[cur].Child.at(i).NodeName] = true;
				}
		}

		//Create F_Node
		pos = bs.ExactlySearch(0, (int64_t)Nodes[index].Child.size() - 1, index, (void*)&Nodes[index].Child[0], GetNameOfChild);
		cnt = Nodes[index].Number_of_Child_U64 - pos;
		matrixtemp_PM = (Matrix*)calloc(1, sizeof(Matrix));
		// if (matrixtemp_PM!=NULL)
		// {
		//     matrixtemp_PM->Free();
		//     free(matrixtemp_PM);
		//     matrixtemp_PM=NULL;
		// }
		matrixtemp_PM = new Matrix(cnt, cnt);
		indextemp_V.clear();

		double val;
		for (uint64_t i = 0; i < cnt; i++)
		{
			val = Nodes[index].Child.at(i + pos).Value;
			matrixtemp_PM->UpdateData(i, 0, val);
			matrixtemp_PM->UpdateData(0, i, val);
			indextemp_V.push_back(Nodes[index].Child.at(i + pos).NodeName);//the same as indextemp_V[i]
		}

		// temp=ShortenMatrix(indextemp_V,*matrixtemp_PM);
		if (U_PSM == 0)
			F = ShortenMatrix(indextemp_V, *matrixtemp_PM);
		else
		{
			temp = ShortenMatrix(indextemp_V, *matrixtemp_PM);
			F = temp.ExtendAdd(*U_PSM);
			temp.Free();
		}

		matrixtemp_PM->Free();

		// if (U_PSM!=NULL)
		// {
		//     U_PSM->Free();
		//     U_PSM=0;
		// }

		//calculate L and Ui
		uint64_t ii = F.Index_PU64.at(0);
		element.colindex_U64 = ii;
		element.rowindex_U64 = ii;
		double res = sqrt(F.Matrix_M.data_V2D.at(0).at(0));
		element.value_D = res;
		L_VE.push_back(element);
		for (uint64_t i = 1; i < F.Matrix_M.row_U64; i++)
		{
			element.rowindex_U64 = index;
			element.colindex_U64 = F.Index_PU64[i];
			element.value_D = F.Matrix_M.data_V2D.at(0).at(i) / res;
			L_VE.push_back(element);
		}

		F.Index_PU64.erase(F.Index_PU64.begin());
		if (F.Index_PU64.size() > 0)
		{
			U_M = F.Matrix_M.Copy(1, F.Matrix_M.row_U64 - 1, 1, F.Matrix_M.col_U64 - 1);
			V_M = F.Matrix_M.Copy(1, F.Matrix_M.row_U64 - 1, 0, 0);
			VT_M = V_M.Transpose();
			VVT_M = V_M.MultipleMatrix(&VT_M);
			VVT_d_B_M = VVT_M.DevideNumber(res*res);
			U_M = U_M.SubMatrix(&VVT_d_B_M);
			U_VSM.push_back(ShortenMatrix(F.Index_PU64, U_M));
			UName_V.push_back(index);

			U_M.Free();
			V_M.Free();
			VT_M.Free();
			VVT_M.Free();
			VVT_d_B_M.Free();
		}
		F.Free();
	}
}

double GetNameOfU(void *array, int64_t pos_I64)
{
	return (double)((tNODENAME*)array)[pos_I64];
}

double GetNameOfChild(void *array, int64_t pos_I64)
{
	return ((tLINK*)array)[pos_I64].NodeName;
}
