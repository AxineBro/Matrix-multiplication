#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>
#include <cmath>

using namespace std;

vector<double> getColumn(const vector<vector<double>>& matrix, int index);
vector<double> getRow(const vector<vector<double>>& matrix, int index);
double calculateNumber(const vector<double>& row, const vector<double>& column);
void printMatrix(const vector<vector<double>>& matrix, const string& title = "");
double inputNumber(const string& str, const bool& isInteger, const bool& isPositive);
vector<vector<double>> readMatrix(const string& str);

vector<vector<double>> multiplyNumbers(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2) {
    if (matrix1.empty() || matrix2.empty() || matrix1[0].size() != matrix2.size()) {
        throw invalid_argument("Matrices cannot be multiplied: incompatible dimensions");
    }

    int rows = matrix1.size();
    int cols = matrix2[0].size();
    vector<vector<double>> matrixResult(rows, vector<double>(cols, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            vector<double> row = getRow(matrix1, i);
            vector<double> column = getColumn(matrix2, j);
            matrixResult[i][j] = calculateNumber(row, column);
        }
    }

    return matrixResult;
}

vector<double> getColumn(const vector<vector<double>>& matrix, int index) {
    vector<double> column(matrix.size());
    for (int i = 0; i < matrix.size(); i++) {
        column[i] = matrix[i][index];
    }
    return column;
}

vector<double> getRow(const vector<vector<double>>& matrix, int index) {
    return matrix[index];
}

double calculateNumber(const vector<double>& row, const vector<double>& column) {
    int sum = 0;
    for (int i = 0; i < row.size(); i++) {
        sum += row[i] * column[i];
    }
    return sum;
}

void printMatrix(const vector<vector<double>>& matrix, const string& title) {
    if (!title.empty()) {
        cout << title << ":" << endl;
    }

    if (matrix.empty()) {
        cout << "Empty matrix" << endl;
        return;
    }

    int max_width = 0;
    for (const auto& row : matrix) {
        for (int num : row) {
            int width = to_string(num).length();
            if (width > max_width) {
                max_width = width;
            }
        }
    }

    for (const auto& row : matrix) {
        cout << "| ";
        for (int num : row) {
            cout << setw(max_width) << num << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}

double inputNumber(const string& str, const bool& isInteger, const bool& isPositive) {
    double number;
    while (true) {
        cout << str;
        cin >> number;
        if (cin.fail() || cin.peek() != '\n') {
            cout << "ERROR: INCORRECT DATA ENTERED" << endl;
            cout << "Please try again" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (isInteger && fabs(number - round(number)) > 1e-10) {
            cout << "ERROR: YOU NEED TO ENTER AN INTEGER" << endl;
            cout << "Please try again" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (isPositive && number <= 0) {
            cout << "ERROR: YOU NEED TO ENTER AN POSITIVE" << endl;
            cout << "Please try again" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        return number;
    }
}

vector<vector<double>> readMatrix(const string& str) {
    cout << str << endl;
    int height = inputNumber("Enter the height of the matrix: ", true, true);
    int width = inputNumber("Enter the width of the matrix: ", true, true);
    vector<vector<double>> inputMatrix(height, vector<double>(width, 0));
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            inputMatrix[i][j] = inputNumber("Enter the elemen (" + to_string(i + 1) + ", " + to_string(j + 1) + ") : ", false, false);
        }
    }

    return inputMatrix;
}


int main() {
    try {
        cout << "Demo:\n\n";

        vector<vector<double>> A = {
            {1, 2, 3},
            {4, 5, 6}
        };

        vector<vector<double>> B = {
            {7, 8},
            {9, 10},
            {11, 12}
        };

        printMatrix(A, "Matrix A");
        printMatrix(B, "Matrix B");

        auto result = multiplyNumbers(A, B);

        printMatrix(result, "Multiplication result A x B");

        cout << endl << endl;

        vector<vector<double>> C = readMatrix("Enter the matrix C:");
        vector<vector<double>> D = readMatrix("Enter the matrix D:");

        printMatrix(C, "Matrix C");
        printMatrix(D, "Matrix D");

        auto result2 = multiplyNumbers(C, D);

        printMatrix(result2, "Multiplication result C x D");
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}