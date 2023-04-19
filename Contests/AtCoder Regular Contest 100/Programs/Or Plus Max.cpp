#include <iostream>
#include <vector>

using namespace std;

int is_bit_set(int n, int bit)
{
    return ( ( n & (1 << bit) ) != 0 );
}

void update(int n, int &largest, int &second_largest, vector <int> &A)
{
    //cout << "Updating " << A[n] << "\n";
    if(n == largest || n == second_largest)
    {   //cout << "Return";
        return;
    }

    if(largest == -1 || A[n] > A[largest])
    {
        second_largest = largest;
        largest = n;
    }
    else if(second_largest == -1 || A[n] >= A[second_largest])
    {
        second_largest = n;
    }

    //cout << "Largest = " << A[largest] << " " << A[second_largest] << "\n";
}

int main()
{
    int no_of_elements;
    cin >> no_of_elements;

    int max_mask = 1 << no_of_elements;
    vector <int> A(max_mask + 1);
    for(int i = 0; i < max_mask; i++)
    {
        cin >> A[i];
    }

    vector <int> largest(max_mask, -1), second_largest(max_mask, -1), sum(max_mask);
    largest[0] = second_largest[0] = 0;
    for(int m = 1; m < max_mask; m++)
    {
        //cout << "At " << m << " ";
        update(0, largest[m], second_largest[m], A);
        update(m, largest[m], second_largest[m], A);

        for(int bit = 0; bit < no_of_elements; bit++)
        {
            if(is_bit_set(m, bit))
            {
                int submask_without_this_bit = m^(1 << bit);
                //cout << " At old " << submask_without_this_bit << "\n";
                update(largest[submask_without_this_bit], largest[m], second_largest[m], A);
                update(second_largest[submask_without_this_bit], largest[m], second_largest[m], A);
            }
        }
    }

    for(int m = 1; m < max_mask; m++)
    {
        sum[m] = max(sum[m - 1], A[largest[m]] + A[second_largest[m]]);
    }

    for(int m = 1; m < max_mask; m++)
    {
        cout << sum[m] << "\n";
    }

    return 0;
}
