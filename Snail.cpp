#include <iostream>
#include <iomanip>
#include <stdexcept>


void InputSize(int32_t&, int32_t&);
void InputMatrixElements(int32_t**, int32_t);
void FillSnailMatrix(int32_t**, int32_t);
void PrintArray(int32_t**, int32_t);
void DeleteMatrix(int32_t**, int32_t);

int main() {
    try {
    
        int32_t columns = 0;
        int32_t rows = 0;
        
        InputSize(columns, rows);
        
        
        if (columns != rows) {
            throw std::invalid_argument("Matrix must be square for snail filling");
        }
        
        int32_t** matrix = new int32_t*[rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int32_t[columns];
        }
        
        InputMatrixElements(matrix, rows);
        FillSnailMatrix(matrix, rows);
        PrintArray(matrix, rows);
        
        DeleteMatrix(matrix, rows);
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

void InputSize(int32_t& columns, int32_t& rows) {
    std::cout << "Enter matrix size (n x n): ";
    std::cin >> rows;
    columns = rows;

    if (columns <= 0 || rows <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
}

void InputMatrixElements(int32_t** matrix, int32_t size) {
    std::cout << "Enter " << size*size << " matrix elements:" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

void FillSnailMatrix(int32_t** matrix, int32_t size) {
    int32_t** temp = new int32_t*[size];
    for (size_t i = 0; i < size; ++i) {
        temp[i] = new int32_t[size];
        for (size_t j = 0; j < size; ++j) {
            temp[i][j] = matrix[i][j];
        }
    }

    int32_t index {};
    int32_t  top {};
    int32_t bottom = size - 1;
    int32_t left {};
    int32_t right = size - 1;
    
    while (top <= bottom && left <= right) {
       
        for (size_t i = left; i <= right; ++i) {
            matrix[top][i] = temp[index/size][index%size];
            index++;
        }
        top++;
        
        
        for (size_t i = top; i <= bottom; ++i) {
            matrix[i][right] = temp[index/size][index%size];
            index++;
        }
        right--;
        
        if (top <= bottom) {
            for (size_t i = right; i >= left; --i) {
                matrix[bottom][i] = temp[index/size][index%size];
                index++;
            }
            bottom--;
        }
        
        
        if (left <= right) {
            for (size_t i = bottom; i >= top; --i) {
                matrix[i][left] = temp[index/size][index%size];
                index++;
            }
            left++;
        }
    }

    
    for (size_t i = 0; i < size; ++i) {
        delete[] temp[i];
    }
    delete[] temp;
}

void PrintArray(int32_t** matrix, int32_t size) {
    std::cout << "Snail matrix:" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << std::setw(4) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void DeleteMatrix(int32_t** matrix, int32_t rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
