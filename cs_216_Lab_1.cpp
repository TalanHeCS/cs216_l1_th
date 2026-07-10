#include <iostream>
#include <fstream>
using namespace std;

//check if given list is empty
bool is_Empty(ifstream& MyFile) {
    return MyFile.peek() == ifstream::traits_type::eof();
}

//printing array---------------------------------------------------------
void print_array(const int array[], int size)
{
    for (int i=0; i<size; i++)
    {
        cout<<array[i]<<" ";
    }
}


//sorting list------------------------------------------------------------------------------------------------------------
void sort_list(int array[], int size)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < size - i; j++)
        {
            if (array[j] > array[j + 1]) 
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

//calculate mean and get sum---------------------------------------------------------------------------------
double get_mean(int array[], int size, int& sum)
{
    //check if list is empty/not empty
    if (size == 0)
    {
        sum = 0;
        return 0;
    }

    sum = 0;
    for(int i=0; i<size; i++)
    {
        sum = sum + array[i];
    }
    double average = (1.0 * sum) / size; //prevent integer division
    return average;
}

//median-------------------------------------------------------------------------------------------------
double get_median(int array[], int size)
{
    if (size == 0)
    {
        return 0;
    }

    int temp_array[size];
    for (int i = 0; i < size; i++)
    {
        temp_array[i] = array[i];
    }

    sort_list(temp_array, size);

    double median = 0;
    if (size % 2 != 0)
    {
        median = temp_array[size / 2];
    }
    else
    {
        median = (temp_array[(size / 2) - 1] + temp_array[size / 2]) / 2.0;
    }

    return median;
}
//print descending--------------------------------------------------------------------------------------
void print_descending(int array[], int size)
{
    if (size == 0)
    {
        cout<<"\nThis list has no values.";
        return;
    }

    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < size - i; j++)
        {
            if (array[j] < array[j + 1]) 
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main()
{
    //create & open file, named myFile
    ifstream myFile("numbers.txt");
    if (is_Empty(myFile))
    {
        cout<<"This file is empty." <<endl;
        return 0;
    }

    int listSize = 0;
    int temp;
    //count amount of integers in given file
    while (myFile >> temp)
    {
        listSize++;
    }
    
    // reset stream before reading values
    myFile.clear();
    myFile.seekg(0, ios::beg);


    //defining the different arrays
    int array[listSize] = {};
    int array_5[listSize] = {};
    int array_7[listSize] = {};
    int misc_array[listSize] = {};
    //copy integers from file to an array
    for (int i=0; i < listSize; i++)
    {
        myFile >> array[i];
    }

    //sorting based off divisibility
    int count5 = 0;
    int count7 = 0;
    int count_misc = 0;
    for (int j = 0; j < listSize; j++)
    {
        if (array[j] % 5 == 0)
        {
            array_5[count5] = array[j];
            count5++;
        }
        else if (array[j] % 7 == 0)
        {
            array_7[count7] = array[j];
            count7++;
        }
        else
        {
            misc_array[count_misc] = array[j];
            count_misc++;
        }
    }
    myFile.close();



    //Menu creation--------------------------------------------------------------------------------------------------------------
    int choice = 0;
    while(choice != 3)
    {
        cout<<"\n-------Menu--------";
        cout<<"\n1) Print values stored in each array along with the average, median, and sum of the numbers stored in each array"<<endl;
        cout<<"\n2) Print values in each array sorted in descending order"<<endl;
        cout<<"\n3) Quit and write arrays and their stats into an output file"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;

         switch (choice)
        {
            case 1:
            {
                int sum;
                
                cout << "\nValues divisible by 5:" << endl;
                print_array(array_5, count5);
                cout << "Mean: " << get_mean(array_5, count5, sum) << endl;
                cout << "Sum: " << sum << endl;
                cout << "Median: " << get_median(array_5, count5) << endl;

                cout << "\nValues divisible by 7:" << endl;
                print_array(array_7, count7);
                cout << "Mean: " << get_mean(array_7, count7, sum) << endl;
                cout << "Sum: " << sum << endl;
                cout << "Median: " << get_median(array_7, count7) << endl;

                cout << "\nMisc values:" << endl;
                print_array(misc_array, count_misc);
                cout << "Mean: " << get_mean(misc_array, count_misc, sum) << endl;
                cout << "Sum: " << sum << endl;
                cout << "Median: " << get_median(misc_array, count_misc) << endl;

                break;
            }

            case 2:
            {
                cout << "\nValues divisible by 5 in descending order:" << endl;
                print_descending(array_5, count5);
                print_array(array_5, count5);

                cout << "\nValues divisible by 7 in descending order:" << endl;
                print_descending(array_7, count7);
                print_array(array_7, count7);

                cout << "\nMisc values in descending order:" << endl;
                print_descending(misc_array, count_misc);
                print_array(misc_array, count_misc);

                break;
            }

            case 3:
            {
                ofstream outFile("output.txt");

                int sum;

                outFile << "Values divisible by 5:" << endl;
                for (int i = 0; i < count5; i++)
                {
                    outFile << array_5[i] << ", ";
                }
                outFile << endl;
                outFile << "Mean: " << get_mean(array_5, count5, sum) << endl;
                outFile << "Sum: " << sum << endl;
                outFile << "Median: " << get_median(array_5, count5) << endl;

                outFile << "\nValues divisible by 7:" << endl;
                for (int i = 0; i < count7; i++)
                {
                    outFile << array_7[i] << ", ";
                }
                outFile << endl;
                outFile << "Mean: " << get_mean(array_7, count7, sum) << endl;
                outFile << "Sum: " << sum << endl;
                outFile << "Median: " << get_median(array_7, count7) << endl;

                outFile << "\nMisc values:" << endl;
                for (int i = 0; i < count_misc; i++)
                {
                    outFile << misc_array[i] << ", ";
                }
                outFile << endl;
                outFile << "Mean: " << get_mean(misc_array, count_misc, sum) << endl;
                outFile << "Sum: " << sum << endl;
                outFile << "Median: " << get_median(misc_array, count_misc) << endl;

                outFile.close();
                cout << "Stats copied to output.txt" << endl;
                return 0;
            }

            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    }
}

//output
/*
-------Menu--------
1) Print values stored in each array along with the average, median, and sum of the numbers stored in each array
2) Print values in each array sorted in descending order
3) Quit and write arrays and their stats into an output file
Enter your choice: 1

Values divisible by 5:
5 10 100 10 290 Mean: 83
Sum: 415
Median: 10

Values divisible by 7:
7 Mean: 7
Sum: 7
Median: 7

Misc values:
1 2 3 4 6 8 9 39 34 Mean: 11.7778
Sum: 106
Median: 6
-------Menu--------
1) Print values stored in each array along with the average, median, and sum of the numbers stored in each array
2) Print values in each array sorted in descending order
3) Quit and write arrays and their stats into an output file
Enter your choice:


*/