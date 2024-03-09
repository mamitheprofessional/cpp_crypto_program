#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*bu proje kullanicidan bir metin aliyor aldigi metni once ters ceviriyor
sonra ters cevrilmis metni ortasindan ikiye ayiriyor
sonra her iki degiskeninde harflerini sayilarini ve bazi ozel karakterlerini atbash yontemiyle
ceviriyor fakat bunu yaparken birinci yarisina ayri ikinci yarisina ayri kural uyguluyor
sonra bu iki ters cevrilmis cümle parcasını ters bir sekilde birlestiriyor
en son bunlarin ascii tablosuna gore karsiligini .txt uzantılı belge uzerinden yazıp okuyor*/

string ters_cevir(string metin); //bu fonksiyon bir diziyi alip ters ceviriyor
void ikiye_bol(string metin, string &ilk_yarim, string &ikinci_yarim); //bu ise metnin ortasini 2 ye bolup 2 ayri degiskene atiyor
void harf_degistir_ilk_yarim(string &metin); //tum harfleri atbash yontemiyle a dan z ye sirali olarak degistirdi
void harf_degistir_ikinci_yarim(string &metin); //tum harfleri bu sefer atbash ile z den a ya sirali degistirdi
void sayi_karakter_degistir(string &metin); //tum sayilari ve bazi karakterleri degistiriyor
string ascii_donustur(string metin); //buda programi en son asciiye gore int tabanli degistirecek
//sifre kirici fonksyonlar
string asciiden_metine_donustur(string ascii_metin);
void sifre_kirici_ikiye_bol(string metin, string &sifrelenmis_ilk_yarim, string &sifrelenmis_ikinci_yarim);
void kirilmis_harf_degistirici_ilk_yarim(string &metin);
void kirilmis_harf_degistir_ikinci_yarim(string &metin);
string sifreli_metin_ters_cevir(string metin);
void sifrenin_sayi_karakter_degistir(string &metin);

int main() {
    string girilen_metin, ters_metin, ilk_yarim, ikinci_yarim;
    string ascii_kir, kirilacak_metin, sifreli_ilk_yarim, sifreli_ikinci_yarim;
    char secim;
    string tam_sifre,kirilacak_tam_sifre,kirilacak_tam_sifre_final;
    ofstream dosya_yaz;
    ifstream dosya_oku;
    cout << "--------------------------sifre programi----------------------------" << endl;
    cout << "Secim yapiniz:" << endl;
    cout << "'e' Sifreleme" << endl;
    cout << "'d' Sifre Cozme" << endl;
    cout << "Seciminiz: ";
    cin >> secim;
    cin.ignore(); //ne ise yaradigi hakkinda hicbir fikrim yok
    switch (secim) {
    case 'e':
        cout << "sifrelenecek metni giriniz: ";
        getline(cin, girilen_metin); //kullanicidan aldik
        ters_metin = ters_cevir(girilen_metin);
        ikiye_bol(ters_metin, ilk_yarim, ikinci_yarim);
        harf_degistir_ilk_yarim(ilk_yarim);
        harf_degistir_ikinci_yarim(ikinci_yarim);
        sayi_karakter_degistir(ilk_yarim);
        sayi_karakter_degistir(ikinci_yarim);
        tam_sifre = ikinci_yarim + ilk_yarim; //burda ters birlestir
        ascii_donustur(tam_sifre);            // ve finished...
        // dosya komutları
        dosya_yaz.open("sifreli_metin.txt");
        dosya_yaz<<ascii_donustur(tam_sifre);
        dosya_yaz.close();
        break;
    case 'd':
        cout << "kırılan: ";
        dosya_oku.open("sifreli_metin.txt");
        if(dosya_oku.is_open()){

        getline(dosya_oku, kirilacak_metin);
        dosya_oku.close();

        ascii_kir = asciiden_metine_donustur(kirilacak_metin);
        sifre_kirici_ikiye_bol(ascii_kir, sifreli_ilk_yarim, sifreli_ikinci_yarim);
        kirilmis_harf_degistirici_ilk_yarim(sifreli_ilk_yarim);
        kirilmis_harf_degistir_ikinci_yarim(sifreli_ikinci_yarim);
        sifrenin_sayi_karakter_degistir(sifreli_ilk_yarim);
        sifrenin_sayi_karakter_degistir(sifreli_ikinci_yarim);
        kirilacak_tam_sifre=sifreli_ikinci_yarim+sifreli_ilk_yarim;
        kirilacak_tam_sifre_final = sifreli_metin_ters_cevir(kirilacak_tam_sifre);
        cout << kirilacak_tam_sifre_final;
                                    }
        else{
            cout<<"dosya acilamadi";
        }
        break;
    default:
        cout << "hatali secim yaptiniz";
        break;
    }

    return 0;
}


string ters_cevir(string metin) {
    int n = metin.length();
    for(int i = 0; i < n/2; i++) {
        char temp = metin[i];
        metin[i] = metin[n-i-1];
        metin[n-i-1] = temp;
    }
    return metin;
}


string ascii_donustur(string metin) {
    string ascii_metin = "";
    int index = 0;
    while (index < metin.length()) {
        char karakter = metin[index];
        int ascii = karakter;
        ascii_metin += to_string(ascii); // ASCII değerini stringe çevirerek ekle
        index++;
    }
    return ascii_metin;
}


void harf_degistir_ilk_yarim(string &metin) {
    for (int i = 0; i < metin.length(); ++i) {
        switch (metin[i]) {
            case 'a':
                metin.replace(i, 1, "z");
                break;
            case 'b':
                metin.replace(i, 1, "y");
                break;
            case 'c':
                metin.replace(i, 1, "x");
                break;
            case 'd':
                metin.replace(i, 1, "w");
                break;
            case 'e':
                metin.replace(i, 1, "v");
                break;
            case 'f':
                metin.replace(i, 1, "u");
                break;
            case 'g':
                metin.replace(i, 1, "t");
                break;
            case 'h':
                metin.replace(i, 1, "s");
                break;
            case 'i':
                metin.replace(i, 1, "r");
                break;
            case 'j':
                metin.replace(i, 1, "q");
                break;
            case 'k':
                metin.replace(i, 1, "p");
                break;
            case 'l':
                metin.replace(i, 1, "o");
                break;
            case 'm':
                metin.replace(i, 1, "n");
                break;
            case 'n':
                metin.replace(i, 1, "m");
                break;
            case 'o':
                metin.replace(i, 1, "l");
                break;
            case 'p':
                metin.replace(i, 1, "k");
                break;
            case 'q':
                metin.replace(i, 1, "j");
                break;
            case 'r':
                metin.replace(i, 1, "i");
                break;
            case 's':
                metin.replace(i, 1, "h");
                break;
            case 't':
                metin.replace(i, 1, "g");
                break;
            case 'u':
                metin.replace(i, 1, "f");
                break;
            case 'v':
                metin.replace(i, 1, "e");
                break;
            case 'w':
                metin.replace(i, 1, "d");
                break;
            case 'x':
                metin.replace(i, 1, "c");
                break;
            case 'y':
                metin.replace(i, 1, "b");
                break;
            case 'z':
                metin.replace(i, 1, "a");
                break;
        }
    }
}

void harf_degistir_ikinci_yarim(string &metin) {
    for (int i = 0; i < metin.length(); ++i) {
        switch (metin[i]) {
            case 'z':
                metin.replace(i, 1, "a");
                break;
            case 'y':
                metin.replace(i, 1, "b");
                break;
            case 'x':
                metin.replace(i, 1, "c");
                break;
            case 'w':
                metin.replace(i, 1, "d");
                break;
            case 'v':
                metin.replace(i, 1, "e");
                break;
            case 'u':
                metin.replace(i, 1, "f");
                break;
            case 't':
                metin.replace(i, 1, "g");
                break;
            case 's':
                metin.replace(i, 1, "h");
                break;
            case 'r':
                metin.replace(i, 1, "i");
                break;
            case 'q':
                metin.replace(i, 1, "j");
                break;
            case 'p':
                metin.replace(i, 1, "k");
                break;
            case 'o':
                metin.replace(i, 1, "l");
                break;
            case 'n':
                metin.replace(i, 1, "m");
                break;
            case 'm':
                metin.replace(i, 1, "n");
                break;
            case 'l':
                metin.replace(i, 1, "o");
                break;
            case 'k':
                metin.replace(i, 1, "p");
                break;
            case 'j':
                metin.replace(i, 1, "q");
                break;
            case 'i':
                metin.replace(i, 1, "r");
                break;
            case 'h':
                metin.replace(i, 1, "s");
                break;
            case 'g':
                metin.replace(i, 1, "t");
                break;
            case 'f':
                metin.replace(i, 1, "u");
                break;
            case 'e':
                metin.replace(i, 1, "v");
                break;
            case 'd':
                metin.replace(i, 1, "w");
                break;
            case 'c':
                metin.replace(i, 1, "x");
                break;
            case 'b':
                metin.replace(i, 1, "y");
                break;
            case 'a':
                metin.replace(i, 1, "z");
                break;
        }
    }
}

void sayi_karakter_degistir(string &metin) {
    for (int i = 0; i < metin.length(); ++i) {
        switch (metin[i]) {
            case '1':
                metin.replace(i, 1, "9");
                break;
            case '2':
                metin.replace(i, 1, "8");
                break;
            case '3':
                metin.replace(i, 1, "7");
                break;
            case '4':
                metin.replace(i, 1, "6");
                break;
            case '6':
                metin.replace(i, 1, "4");
                break;
            case '7':
                metin.replace(i, 1, "3");
                break;
            case '8':
                metin.replace(i, 1, "2");
                break;
            case '9':
                metin.replace(i, 1, "1");
                break;
            case '+':
                metin.replace(i, 1, "-");
                break;
            case '.':
                metin.replace(i, 1, "?");
                break;
            case ',':
                metin.replace(i, 1, "|");
                break;
        }
    }
}

void ikiye_bol(string metin, string &ilk_yarim, string &ikinci_yarim) {
    int n = metin.length();
    int orta_nokta = n / 2;

    if (n % 2 == 0) {
        // Karakter sayısı çift ise
        ilk_yarim = metin.substr(0, orta_nokta);
        ikinci_yarim = metin.substr(orta_nokta);
    } else {
        // Karakter sayısı tek ise
        ilk_yarim = metin.substr(0, orta_nokta + 1);
        ikinci_yarim = metin.substr(orta_nokta);
    }
}


//----------------burdan sonrasi sifre kirici fonksyonlar-----------------//

string asciiden_metine_donustur(string ascii_metin) {
    string metin = ""; //bos bir string ile programi baslattim
    int index = 0;
    while (index < ascii_metin.length()) {
        int ascii = stoi(ascii_metin.substr(index, 3)); // stoi bir stringi integer a donusturur ayrica max 3 haneli asciileri tek tek substr ile seciyoruz
        char donusum_karakter = static_cast<char>(ascii); //static_cast<tür> bir degiskeni baska degiskene donusturur burda ascii yi char a donusturduk ve char turunde donusum_karakter adli degiskene atadik
        metin += donusum_karakter; // ascii okunan metindeki her bir karakteri tek tek okuyup aynı anda donusum karakterle donusturulmus char ifadeyi metin degiskenine ekliyor
        index += 3; // Sonraki ASCII koduna geç
    }
    return metin;
}

void kirilmis_harf_degistirici_ilk_yarim(string &metin) {
    for (int i = 0; i < metin.length(); ++i) {
        switch (metin[i]) {
             case 'z':
                metin.replace(i, 1, "a");
                break;
            case 'y':
                metin.replace(i, 1, "b");
                break;
            case 'x':
                metin.replace(i, 1, "c");
                break;
            case 'w':
                metin.replace(i, 1, "d");
                break;
            case 'v':
                metin.replace(i, 1, "e");
                break;
            case 'u':
                metin.replace(i, 1, "f");
                break;
            case 't':
                metin.replace(i, 1, "g");
                break;
            case 's':
                metin.replace(i, 1, "h");
                break;
            case 'r':
                metin.replace(i, 1, "i");
                break;
            case 'q':
                metin.replace(i, 1, "j");
                break;
            case 'p':
                metin.replace(i, 1, "k");
                break;
            case 'o':
                metin.replace(i, 1, "l");
                break;
            case 'n':
                metin.replace(i, 1, "m");
                break;
            case 'm':
                metin.replace(i, 1, "n");
                break;
            case 'l':
                metin.replace(i, 1, "o");
                break;
            case 'k':
                metin.replace(i, 1, "p");
                break;
            case 'j':
                metin.replace(i, 1, "q");
                break;
            case 'i':
                metin.replace(i, 1, "r");
                break;
            case 'h':
                metin.replace(i, 1, "s");
                break;
            case 'g':
                metin.replace(i, 1, "t");
                break;
            case 'f':
                metin.replace(i, 1, "u");
                break;
            case 'e':
                metin.replace(i, 1, "v");
                break;
            case 'd':
                metin.replace(i, 1, "w");
                break;
            case 'c':
                metin.replace(i, 1, "x");
                break;
            case 'b':
                metin.replace(i, 1, "y");
                break;
            case 'a':
                metin.replace(i, 1, "z");
                break;

        }
    }
}

void kirilmis_harf_degistir_ikinci_yarim(string &metin) {
    for (int i = 0; i < metin.length(); ++i) {
        switch (metin[i]) {
            case 'a':
                metin.replace(i, 1, "z");
                break;
            case 'b':
                metin.replace(i, 1, "y");
                break;
            case 'c':
                metin.replace(i, 1, "x");
                break;
            case 'd':
                metin.replace(i, 1, "w");
                break;
            case 'e':
                metin.replace(i, 1, "v");
                break;
            case 'f':
                metin.replace(i, 1, "u");
                break;
            case 'g':
                metin.replace(i, 1, "t");
                break;
            case 'h':
                metin.replace(i, 1, "s");
                break;
            case 'i':
                metin.replace(i, 1, "r");
                break;
            case 'j':
                metin.replace(i, 1, "q");
                break;
            case 'k':
                metin.replace(i, 1, "p");
                break;
            case 'l':
                metin.replace(i, 1, "o");
                break;
            case 'm':
                metin.replace(i, 1, "n");
                break;
            case 'n':
                metin.replace(i, 1, "m");
                break;
            case 'o':
                metin.replace(i, 1, "l");
                break;
            case 'p':
                metin.replace(i, 1, "k");
                break;
            case 'q':
                metin.replace(i, 1, "j");
                break;
            case 'r':
                metin.replace(i, 1, "i");
                break;
            case 's':
                metin.replace(i, 1, "h");
                break;
            case 't':
                metin.replace(i, 1, "g");
                break;
            case 'u':
                metin.replace(i, 1, "f");
                break;
            case 'v':
                metin.replace(i, 1, "e");
                break;
            case 'w':
                metin.replace(i, 1, "d");
                break;
            case 'x':
                metin.replace(i, 1, "c");
                break;
            case 'y':
                metin.replace(i, 1, "b");
                break;
            case 'z':
                metin.replace(i, 1, "a");
                break;
        }
    }
}
void sifrenin_sayi_karakter_degistir(string &metin) {
    for (int i = 0; i < metin.length(); ++i) {
        switch (metin[i]) {
            case '9':
                metin.replace(i, 1, "1");
                break;
            case '8':
                metin.replace(i, 1, "2");
                break;
            case '7':
                metin.replace(i, 1, "3");
                break;
            case '6':
                metin.replace(i, 1, "4");
                break;
            case '5':
                metin.replace(i, 1, "5");
                break;
            case '4':
                metin.replace(i, 1, "6");
                break;
            case '3':
                metin.replace(i, 1, "7");
                break;
            case '2':
                metin.replace(i, 1, "8");
                break;
            case '-':
                metin.replace(i, 1, "+");
                break;
            case '?':
                metin.replace(i, 1, ".");
                break;
            case '|':
                metin.replace(i, 1, ",");
                break;
        }
    }
}

void sifre_kirici_ikiye_bol(string metin, string &sifrelenmis_ilk_yarim, string &sifrelenmis_ikinci_yarim) {
    int n = metin.length(); //n degiskenine fonksyonun sayisal uzunlugunu atadim
    int orta_nokta = n / 2; //2 ye bolup orta noktaya atadim

    sifrelenmis_ilk_yarim = metin.substr(0, orta_nokta); //substr ile metin dizisini ilk karakterden kesilmis orta noktaya kadar aldim ve en son ilk yarim dizisine atadim
    sifrelenmis_ikinci_yarim = metin.substr(orta_nokta, n - orta_nokta); //kalan yarısınıda ikinci yarima atadim
}

string sifreli_metin_ters_cevir(string metin) {
    int n = metin.length();

        for(int i = 0; i < n/2; i++) {
            char temp = metin[i];
            metin[i] = metin[n-i-1];
            metin[n-i-1] = temp;
                                     }

    return metin;
}

