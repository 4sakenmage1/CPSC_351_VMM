#include <iostream>

using namespace std;

int arr[50];


struct TLB
{
public:
	int tlb[16];
	int addToTLB(int pg);
	int LRU(int pg);

private:
	int hit[16] = {0};
	int size = 0;



};


int main()
{
	int var = 2;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			var += (var * 2);
			var = var % 256;

			arr[i] = var;

		}
	}

	int returnValue;


	struct TLB currentTLB;

	for (int i = 0; i < 16; i++)
	{
		currentTLB.tlb[i] = -1;

	}
	for (int i = 0; i < 50; i++)
	{
		returnValue = currentTLB.addToTLB(arr[i]);

		cout << returnValue << endl << endl;

	}
	system("pause");
	return 0;
}

int TLB::addToTLB(int pg)
{
	bool hom = false;
	int i = 0;

	for (i = 0; i < 16; i++)
	{
		if (tlb[i] == pg)
		{
			hom = true;
			break;
		}

	}

	if (size == 16)
	{
		i = LRU(pg);
		//FIFO(pg);
		return tlb[i];
	}
	else
	{
		if (hom == false)
		{
			size++;
			for (int j = 0; j < 16; j++)
			{
				hit[j]--;
				if (tlb[j] == -1)
				{
					tlb[j] = arr[pg];
					hit[j] = 16;

					return tlb[j];
				}
			}
		}
		else
		{
			hit[i]++;
			return tlb[i];
		}

	}
}

int TLB::LRU(int pg)
{
	int bestfit;
	int index;

	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			bestfit = hit[i];
			index = 0;

		}
		else
		{
			if (hit[i] < bestfit)
			{
				bestfit = hit[i];
				index = i;
			}
		}
	}

	tlb[index] = pg;
	hit[index] = 16;
	return index;
};