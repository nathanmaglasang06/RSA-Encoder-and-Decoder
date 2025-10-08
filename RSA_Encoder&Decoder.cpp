//
// Created by Nathan Maglasang on 18/9/2025.

//Amazing Videos by Eddie Woo
//Part 1: https://youtu.be/4zahvcJ9glg?si=royT9xRM5mkBgZk0
//Part 2: https://youtu.be/oOcTVTpUsPQ?si=j8zTFfKQvDq5bi0S

//https://www.cryptool.org/en/cto/rsa-step-by-step/

//
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

//sqr mult comp 5 vid

using namespace std;
using lint = long long int;

lint modPow(lint base, lint exponent, lint modulus) {
    lint result = 1;
    base = base % modulus;
    for (lint i = 0; i < exponent; i++) {
        result = (result * base) % modulus;
    }
    return result;
}

string encode(string encryptString, lint encrypt[]) {
    cout << encryptString << encrypt[0] << encrypt[1] << endl;
    vector<lint> numericTranslation;
    vector<lint> numericTransformation;
    string encodedString;

    for (char c : encryptString) {
        if (c >= 'a' && c <= 'z') {
            numericTranslation.push_back(c - 'a' + 1);
        } else {
            numericTranslation.push_back(0);
        }
    }
    cout << "Numeric translation: ";
    for (lint num : numericTranslation) {
        cout << num << " ";
        if (num >= 1) {
            numericTransformation.push_back(modPow(num, encrypt[0], encrypt[1]));
        }
    }
    cout << "\nNumeric transformation: ";
    for (lint num : numericTransformation) {
        cout << num << " ";
    }
    for (lint num : numericTransformation) {
        if (num >= 1 && num <= 26) {
            char c = 'a' + (num - 1);
            encodedString.push_back(c);
        } else {
            encodedString.push_back(' ');
        }
    }
    cout << "\nEncoded String: " << encodedString << "\n\nNote that the values in the numeric transformation can\n"
                                                     "be larger or less that 1-26, causing misrepresentation within\n"
                                                     "the encoded string please use the numeric output when decrypting";
    cout << endl;
    return encodedString;
}

/*string decode(string decryptString, lint decrypt[]) {

    cout << decryptString << decrypt[0] << decrypt[1] << endl;
    vector<lint> numericTransformation;
    string decodedString;

    cout << "\nNumeric transformation: ";
    for (lint num : decryptString) {
        cout << num << " ";
        if (num >= 1) {
            numericTransformation.push_back(modPow(num, decrypt[0], decrypt[1]));
        }
    }
    cout << "\nEncoded String: " << decodedString;
    cout << endl;
    return decodedString;
}*/

lint keygen(lint &p, lint &q, lint &n, lint &d, lint &e) {
    lint response = 0;
    lint eco = 0;
    cout << "Do you have your own values for p and q?\n1. Yes\n2. No\nResponse: ";
    cin >> response;
    switch (response) {
        case 1:
            cout << "Input p: ";
            cin >> p;
            cout << "Input q: ";
            cin >> q;
            n = p * q;
            eco = (p-1) * (q-1);
            cout << "Choose a value for e, noting that it must be coprime to " << eco << ": ";
            cin >> e;
            while (true) {
                while (!(cin>>e)) {
                    cout << "Ensure the value for e is an integer: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                if (gcd(e, eco) == 1) {
                    break;
                } else {
                    cout << "Ensure the value for e is coprime to " << eco << ": ";
                }
            }
            //(e*d) mod (phi(n)) = 1
            //d= e^−1 * modφ(n)
            d = (lint) pow(e, -1) % eco;



            break;

        case 2:
            cout << "No";
            break;

    }


return p, q, n, d, e;
}


int main() {
    lint encrypt[2]; //(e,n)
    lint decrypt[2]; //(d,n)
    lint selection;
    string encryptString, decryptString;



    cout << "RSA (Rivest Shamir Adelman) Encoder and Decoder App"
    "\nWould you like to encrypt or decrypt your message? \nYou can also generate your own RSA key set"
    "\n1. Encrypt\n2. Decrypt\n3. Generate RSA Keys\nSelection: ";
    cin >> selection;
    cin.clear();
    cin.ignore(10000, '\n');

    while (selection != 1 && selection != 2 && selection != 3) {
        cout << "\n\nInvalid Selection, Try Again: \n1. Encrypt\n2. Decrypt\n3. Generate Keys\nSelection: ";
        cin >> selection;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    switch (selection) {
        case 1:
            cout << "\nRSA Encryption"
            "\nFor the public key (e, n) enter the integer value for e: ";

            while (!(cin >> encrypt[0])) {
                cout << "Ensure the value for e is an integer: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << "Now for the public key (e, n) enter the integer value for n: ";

            while (!(cin >> encrypt[1])) {
                cout << "Ensure the value for n is an integer: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout  << "Input the alpha numeric string to encrypt [a-z]: ";
            cin >> encryptString;
            encode(encryptString, encrypt);
            break;
//WIP
        case 2:
            cout << "\nRSA Decryption";




/*
            cout << "\nFor the private key (d, n) enter the linteger value for d: ";

            while (!(cin >> decrypt[0])) {
                cout << "Ensure the value for d is an linteger: ";
                cin >> decrypt[0];
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << "\nNow for the key (d, n) enter the linteger value for n: ";

            while (!(cin >> decrypt[1])) {
                cout << "Ensure the value for n is an linteger: ";
                cin >> decrypt[1];
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout  << "\n\nInput the Encrypted numeric string [1-0]: ";
            cin >> decryptString;

            decode(decryptString, decrypt);
            */
            break;

        case 3:
            cout << "\nRSA Key Generation\n";
            lint p, q, n, d, e;
            p = q = n = d = e = 0;
            keygen(p, q, n, d, e);

            cout << "\np: " << p << ", q: " << q << ", n: " << n << ", d: " << d << ", e: " << e;

            break;

    }

    return 0;
}