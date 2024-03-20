#include<iostream>
#include<cstdlib>

using namespace std;

int main(int argc, char *argv[])
{

    float sum;
     if(argc <= 1 )
        cout << "Please input numbers to find average.";
    else
    {
        for(int i = 0; i < argc ; i++)
        {
            sum += atof(argv[i]);
        }
        sum = sum/(argc-1);

        cout << "---------------------------------\n";
        cout << "Average of " << argc - 1 << " numbers = " << sum << endl ;
        cout << "---------------------------------\n";
    }
    
    return 0;

}
