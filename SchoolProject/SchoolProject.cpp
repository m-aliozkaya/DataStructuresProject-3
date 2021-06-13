
#include <iostream>
#include "tree.h"

StudentTree data1;
StudentTree data2;
StudentTree data3;

bool islemyap(char secim);
void menuyazdir();
StudentTree *SelectData();

int main()
{
    data1.CreateTree("data1.txt");
    data2.CreateTree("data2.txt");
    data3.CreateTree("data3.txt");

    bool bitir = false;
    char selectionProcess;
    while (!bitir)
    {
        menuyazdir();

        cout << "Bir secenek giriniz {A, L, E, S, C} : ";
        cin >> selectionProcess;

        bitir = islemyap(selectionProcess);
    }

    data1.CloseTree();
    data2.CloseTree();
    data3.CloseTree();
}

void menuyazdir()
{
    cout << endl << endl;
    cout << "Ogrenci Listesi Uygulamasi" << endl;
    cout << "Bir islem seciniz" << endl;
    cout << "A: Arama Yap" << endl;
    cout << "L: Ogrencileri Listele" << endl;
    cout << "S: Ogrenci Sil" << endl;
    cout << "C: Cikis" << endl;
    cout << endl;
}

bool islemyap(char secim)
{
    char x = '*';
    string a, b;
    bool sonlandir = false;
    StudentTree* tree;
    switch (secim)
    {
    case 'A':
    case 'a':
        tree = SelectData();
        tree->SearchStudent();
        break;
    case 'L':
    case 'l':
        tree = SelectData();
        tree->ListStudents();
        break;
    case 'S':
    case 's':
        tree = SelectData();
        tree->DeleteStudent();
        break;
    case 'C':
    case 'c':
        cout << "Programi sonlandirmak istediginize emin misiniz? (E/H):";
        cin >> secim;
        if (secim == 'E' || secim == 'e')
            sonlandir = true;
        break;
    default:
        cout << "Hata: Yanlis giris yaptiniz" << endl;
        cout << "Tekrar deneyiniz {A, E, G, S, B, C} :";
        cin >> secim;
        sonlandir = islemyap(secim);
        break;
    }
    return sonlandir;
}

StudentTree *SelectData() {
    char selectionData;

    cout << "Ýslem yapmak istediginiz dosyayi seciniz" << endl;
    cout << "data1.txt icin: 1" << endl;
    cout << "data2.txt icin: 2" << endl;
    cout << "data3.txt icin: 3" << endl << endl;
    cout << "Seciminizi giriniz";
    cin >> selectionData;

    switch (selectionData)
    {
    case '1': return &data1; break;
    case '2': return &data2; break;
    case '3': return &data3; break;
    default:
        SelectData();
        break;
    }
}
