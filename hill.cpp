#include <iostream>
using namespace std;

const int MOD = 26;

// Function to find the determinant of a 3x3 matrix mod 26
int determinant(int K[3][3]) {
    int det = K[0][0] * (K[1][1] * K[2][2] - K[1][2] * K[2][1]) -
              K[0][1] * (K[1][0] * K[2][2] - K[1][2] * K[2][0]) +
              K[0][2] * (K[1][0] * K[2][1] - K[1][1] * K[2][0]);
    det = det % MOD;
    if (det < 0)
        det += MOD;  // Ensure positive modulus
    return det;
}

// Function to find the modular inverse of a number mod 26
int modInverse(int det) {
    for (int i = 1; i < MOD; i++) {
        if ((det * i) % MOD == 1)
            return i;
    }
    return -1;  // If no inverse exists
}

// Function to find the adjugate of a 3x3 matrix mod 26
void adjugate(int K[3][3], int adj[3][3]) {
    adj[0][0] = (K[1][1] * K[2][2] - K[1][2] * K[2][1]) % MOD;
    adj[0][1] = (-(K[0][1] * K[2][2] - K[0][2] * K[2][1])) % MOD;
    adj[0][2] = (K[0][1] * K[1][2] - K[0][2] * K[1][1]) % MOD;

    adj[1][0] = (-(K[1][0] * K[2][2] - K[1][2] * K[2][0])) % MOD;
    adj[1][1] = (K[0][0] * K[2][2] - K[0][2] * K[2][0]) % MOD;
    adj[1][2] = (-(K[0][0] * K[1][2] - K[0][2] * K[1][0])) % MOD;

    adj[2][0] = (K[1][0] * K[2][1] - K[1][1] * K[2][0]) % MOD;
    adj[2][1] = (-(K[0][0] * K[2][1] - K[0][1] * K[2][0])) % MOD;
    adj[2][2] = (K[0][0] * K[1][1] - K[0][1] * K[1][0]) % MOD;

    // Ensure positive mod 26
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (adj[i][j] < 0)
                adj[i][j] += MOD;
        }
    }
}

// Function to find the inverse of a 3x3 matrix mod 26
void inverseMatrix(int K[3][3], int inv[3][3]) {
    int det = determinant(K);
    int detInv = modInverse(det);

    if (detInv == -1) {
        cout << "Matrix is not invertible!" << endl;
        return;
    }

    int adj[3][3];
    adjugate(K, adj);

    // Multiply adjugate by determinant's inverse
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inv[i][j] = (adj[i][j] * detInv) % MOD;
            if (inv[i][j] < 0)
                inv[i][j] += MOD;  // Ensure positive mod 26
        }
    }
}

// Function to perform matrix multiplication
void matrixMultiply(int a[3], int b[3][3], int result[3]) {
    for (int i = 0; i < 3; i++) {
        result[i] = 0;
        for (int j = 0; j < 3; j++) {
            result[i] += a[j] * b[j][i];
        }
        result[i] %= MOD;
        if (result[i] < 0) result[i] += MOD;  // Ensure positive mod 26
    }
}

// Function to convert plaintext to numerical form
void textToNumbers(char text[4], int num[3], bool &isUppercase) {
    isUppercase = isupper(text[0]);  // Check if the first letter is uppercase

    for (int i = 0; i < 3; i++) {
        if (isupper(text[i])) {
            num[i] = text[i] - 'A';  // If uppercase, convert accordingly
        } else {
            num[i] = text[i] - 'a';  // If lowercase, convert accordingly
        }
    }
}

// Function to convert numerical form back to text, respecting case
void numbersToText(int num[3], char text[4], bool isUppercase) {
    for (int i = 0; i < 3; i++) {
        if (isUppercase) {
            text[i] = (num[i] + 'A');  // Convert back to uppercase
        } else {
            text[i] = (num[i] + 'a');  // Convert back to lowercase
        }
    }
    text[3] = '\0';  // Null-terminate the string
}

int main() {
    int K[3][3], K_inv[3][3];
    char text[4];
    int P[3], C[3], D[3];
    int choice;
    bool isUppercase;

    // Taking key matrix input from the user
    cout << "Enter 3x3 key matrix (mod 26): " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> K[i][j];
            K[i][j] %= MOD;  // Ensure mod 26
        }
    }

    while (true) {
        // Menu for choosing between encryption and decryption
        cout << "\nChoose an option:\n";
        cout << "1. Encryption\n";
        cout << "2. Decryption\n";
        cout << "3. Exit\n";
        cin >> choice;

        if (choice == 1) {
            // Encryption

            // Taking plaintext input from the user (e.g., act or ACT)
            cout << "Enter 3-letter plaintext: ";
            cin >> text;

            // Convert plaintext to numbers
            textToNumbers(text, P, isUppercase);

            // Encrypt the plaintext: C = P * K mod 26
            matrixMultiply(P, K, C);

            // Convert ciphertext numbers back to text, respecting case
            numbersToText(C, text, isUppercase);

            cout << "Encrypted text: " << text << endl;

        } else if (choice == 2) {
            // Decryption

            // Taking ciphertext input from the user
            cout << "Enter 3-letter ciphertext: ";
            cin >> text;

            // Convert ciphertext to numbers
            textToNumbers(text, C, isUppercase);

            // Find the inverse of the key matrix
            inverseMatrix(K, K_inv);

            // Decrypt the ciphertext: P = C * K_inv mod 26
            matrixMultiply(C, K_inv, D);

            // Convert decrypted numbers back to text, respecting case
            numbersToText(D, text, isUppercase);

            cout << "Decrypted text: " << text << endl;

        } else if (choice == 3) {
            // Exit the loop
            cout << "Exiting program." << endl;
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
