 
#include <iostream>
#include <string>
#include <cctype>

using namespace std;
const int rows = 5;
const int columns = 24;

static bool isValidNumber(string possibleNumber) {

    if (possibleNumber.empty() || possibleNumber.length() > 6) {
        return false;
    }
    for (char ch : possibleNumber) {
        if (!isdigit(ch)) {
            return false;
        }
    }

     int number = std::stoi(possibleNumber);
     if (number < 0 || number > 999999) {
         return false;
     }

    return true;
}
static string getLastDigits(string str, int digits) {
    if (digits >= str.length()) { 
        return str;
    }  
        return str.substr(str.length() - digits); 
}
static bool** initMatrix() { 
    bool** matrix = new bool* [rows];
    for (int i = 0; i < rows; ++i) {
        //matrix[i] = new bool[columns](); 
        matrix[i] = new bool[columns];
        for (int j = 0; j < columns; ++j) {
           matrix[i][j] = false;
        } 
    }
    return matrix;
}
static void deleteMatrix(bool** matrix) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];  
    }
    delete[] matrix;  
}
static void printLEDMatrix(bool** ledMatrix) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            char ledValue = ledMatrix[i][j] ? '⬛' : ' ';
            /*if (ledMatrix[i][j]) {
                char ledValue =  '⬛';
            }
            else {
                char ledValue = ' ';
            }*/
            std::cout << ledValue; 
        }
        std::cout << std::endl;  
    }
}

static void setLightOnAllLeds(bool** ledMatrix, int position) {
    for (int row = 0; row < 5; ++row) {
        for (int col = position; col < position + 3; ++col) {
            ledMatrix[row][col] = true;
        }
    }

}

static void setOAsLed(bool** ledMatrix, int position) {
    setLightOnAllLeds(ledMatrix, position);
    ledMatrix[1][position + 1] = false;
    ledMatrix[2][position + 1] = false;
    ledMatrix[3][position + 1] = false;
}

static void setZeroAsLed(bool** ledMatrix, int position) {
    setOAsLed(ledMatrix, position);
   
}
static void setOneAsLed(bool** ledMatrix, int position) {
    for (int row = 0; row < 5; ++row) {
        ledMatrix[row][position + 2] = true;
    }
}

static void setTwoAsLed(bool** ledMatrix, int position) { 
    setLightOnAllLeds(ledMatrix, position);
     
    ledMatrix[1][position] = false;       
    ledMatrix[1][position + 1] = false;
    ledMatrix[3][position + 1] = false;   
    ledMatrix[3][position + 2] = false;   
}

static void setThreeAsLed(bool** ledMatrix, int position) {
    setLightOnAllLeds(ledMatrix, position);

    ledMatrix[1][position] = false;       
    ledMatrix[1][position + 1] = false;   
    ledMatrix[3][position] = false;       
    ledMatrix[3][position + 1] = false;
}

static void setFourAsLed(bool** ledMatrix, int position) {
    for (int row = 0; row < 3; ++row) {
        ledMatrix[row][position] = true;         
    }
    for (int row = 0; row < 5; ++row) {
        ledMatrix[row][position+2] = true;
    }
   
     ledMatrix[2][position + 1] = true; 
}

static void setFiveAsLed(bool** ledMatrix, int position) {
    setLightOnAllLeds(ledMatrix, position);

    ledMatrix[1][position + 1] = false;   
    ledMatrix[1][position + 2] = false;   
    ledMatrix[3][position] = false;       
    ledMatrix[3][position+1] = false;
}

static void setSixAsLed(bool** ledMatrix, int position) {
    setLightOnAllLeds(ledMatrix, position);

    ledMatrix[1][position + 1] = false;   
    ledMatrix[1][position + 2] = false;   
    ledMatrix[3][position + 1] = false;
}

static void setSevenAsLed(bool** ledMatrix, int position) {
    for (int col = position; col < position + 3; ++col) {
        ledMatrix[0][col] = true;
    }
     
    for (int row = 1; row < 5; ++row) {
        ledMatrix[row][position + 2] = true;
    }
}

static void setEightAsLed(bool** ledMatrix, int position) {
    setOAsLed(ledMatrix, position);
    ledMatrix[2][position + 1] = true; 
}

static void setNineAsLed(bool** ledMatrix, int position) {
    setLightOnAllLeds(ledMatrix, position);

    ledMatrix[1][position+1] = false;       
    ledMatrix[3][position ] = false;
    ledMatrix[3][position + 1] = false;
}

//TODO: Mejorar con polimorfismo
static void setDigitAsLed(bool** ledMatrix, char digit, int position) { 
    if (digit == '0') {
        setZeroAsLed(ledMatrix, position);
        return;
    }
    if (digit == '1') {
        setOneAsLed(ledMatrix, position);
        return;
    }
    if (digit == '2') {
        setTwoAsLed(ledMatrix, position);
        return;
    }
    if (digit == '3') {
        setThreeAsLed(ledMatrix, position);
        return;
    }
    if (digit == '4') {
        setFourAsLed(ledMatrix, position);
        return;
    }
    if (digit == '5') {
        setFiveAsLed(ledMatrix, position);
        return;
    }
    if (digit == '6') {
        setSixAsLed(ledMatrix, position);
        return;
    }
    if (digit == '7') {
        setSevenAsLed(ledMatrix, position);
        return;
    }
    if (digit == '8') {
        setEightAsLed(ledMatrix, position);
        return;
    }
    if (digit == '9') {
        setNineAsLed(ledMatrix, position);
        return;
    }
    // NOTE: Innecesary
    //if (digit == ' ') {
    //    return;
    //}
}

static void loadFormattedDataIntoLEDMatrix(bool** ledMatrix, const std::string& formattedData) {
    const int space = 1;
    const int widthPerDigit = 3+ space; 
    for (int i = 0; i < formattedData.size(); i++) {
        char digit = formattedData[i];
        int position = i * widthPerDigit;
        setDigitAsLed(ledMatrix, digit, position);
    }
}

int main() {
    bool** ledMatrix;
    ledMatrix =initMatrix();
    string numberAsString;
    cout << "Ingrese un número entero positivo de hasta 6 dígitos: ";
    cin >> numberAsString;
    
    while (!isValidNumber( numberAsString)) {
        cout << "Número inválido. Ingrese un número entero positivo de hasta 6 dígitos: ";
        cin >> numberAsString;
    }
    string formattedData = getLastDigits("     " + numberAsString,6);

    loadFormattedDataIntoLEDMatrix( ledMatrix, formattedData);
    printLEDMatrix(ledMatrix);
     
    deleteMatrix(ledMatrix);

    return 0;
}