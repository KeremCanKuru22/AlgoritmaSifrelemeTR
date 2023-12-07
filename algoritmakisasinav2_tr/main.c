#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

void encrypt(char password[], int scroll){
    unsigned int lenght = strlen(password);  //Dizinin uzunluğunu tuttuğumuz değer.
    char character;
    for (int i = 0; i < lenght; i++) {           //Şifreleme Operasyonumuz
        if(isalpha(password[i])){                   //isalpha fonksiyonuyla girilen harfin alfabede olup olmadığını kontrol ediyoruz.
            character = islower(password[i])? 'a':'A';         //islower fonksiyonuyla harfin büyük ya da küçük olduğunu kontrol ediyoruz. Eğer küçükse a harfini değilse A harfini character değişkenine atıyoruz.
            password[i]= character+(password[i]-character +scroll%26+26)%26;                     //Önce a harfini çıkarıyoruz sonra öteleme miktarını buluyoruz ve a harfine ekliyoruz.
        }
    }
}

void deencrypt(char text[], int key) {
    encrypt(text, -key);
}
char fileusing(char text[]){     //Dosyadan okuma veya dosyaya yazma operasyonu.
    FILE *fp;
    char c;
    int i=0,answer;
    wprintf(L"Dosya Oluşturup Okutmak İçin : 1\nDosyayı Okutmak İçin : Herhangi Bir Tuşa Basın \n");
    scanf("%d",&answer);

    if(answer == 1){                                 //Cevaba göre sadece okuyor veya hem yazıp hem de okuyoruz.
        fp= fopen("input.txt","w");   //Yazma işlemi için dosyayı w(write) şeklinde açıyoruz.
        //Buradaki dosya adını isteğinize göre değiştirebilirsiniz.
        if(fp==NULL){
            wprintf(L"Dosya Açılamadı\n");        //Dosyanın geçerliliğini kontrol ediyoruz.
            return 1;
        }
        wprintf(L"Lütfen Dosyanın İçeriğini Giriniz\n");
        gets(text);                         //gets fonksiyonlarıyla metnimizi alıyoruz.
        gets(text);                          //Kullanıcıdan metni alıyoruz.
        fputs(text,fp);         	    //Aldığımız metni dosyaya yazıyoruz.
        fclose(fp);                               //Ve dosyayı kapatıyoruz.
    }

    fp=fopen("input.txt","r");          //Okuma işlemi için dosyayı r(read) şeklinda açıyoruz.
    if(fp==NULL){
        wprintf(L"Dosya Bulunamadı\n");
        return 2;
    }


    while((c= fgetc(fp))!=EOF){  //Dosya bitene kadar her bir harfi text değişkenine atıyoruz.
        text[i]=c;
        ++i;
    }
    fclose(fp);
    return 0;
}

char encryptsystem(){
    //Degişken tanımlama
    char text[600];
    int answer, key;
    //İşlem seçimini sorma ve öğrenme
    wprintf(L"Şifrelemeyi Seçtiniz\nLütfen Kullanmak İstediğiniz Yöntemi Seçiniz:\n Dosya İle Yapmak İçin: 1\n Metin Girerek Kullanmak İçin Herhangi Bir Tuşa Basınız:");
    scanf("%d",&answer);
    if (answer==1) {
        fileusing(text);
        if (strlen(text) == 0) {
            return 1;
        }
    }
        if(answer!=1){
            // Kullanıcıdan şifrelenecek metni alma
            wprintf(L"Lütfen Şifrelenmesini İstediğiniz Metni Giriniz: \n");
            getpasswordagain:
            gets(text); gets(text);
            // Metin uzunluğunu kontrol etme
            if(strlen(text)>600){
                printf("Metin En Fazla 600 Karakter Olabilir!\n");
                fflush(stdin);
                goto getpasswordagain;

            }
        }
            // Kullanıcıdan anahtar değeri alma
            wprintf(L"Lütfen Öteleme Miktarını Giriniz: ");
            getkeyagain:
            if(scanf("%d", &key)!=1){
                fflush(stdin);
                wprintf(L"Lütfen Sadece Sayı Değeri Giriniz!\n");
                goto getkeyagain;
            }

            // Şifreleme
            encrypt(text, key);
            wprintf(L"Şifrelenmiş Metniniz: %s\n", text);
}
char deencryptsystem(){
    //Degişken tanımlama
    char text[600];
    int answer, key;
    //İşlem seçimini sorma ve öğrenme
    wprintf(L"Deşifrelemeyi Seçtiniz\nLütfen Kullanmak İstediğiniz Yöntemi Seçiniz:\n Dosya İle Yapmak İçin: 1\n Metin Girerek Kullanmak İçin Herhangi Bir Tuşa Basınız:");
    scanf("%d",&answer);
    if (answer==1) {
        //Dosya fonksiyonuna gönderme
        fileusing(text);
        if (strlen(text) == 0) {
            return 1;
        }
    }
    if(answer!=1){
        // Kullanıcıdan şifrelenecek metni alma
       wprintf(L"Lütfen Deşifrelenmesini İstediğiniz Metni Giriniz: \n");
        getpasswordagain:
        gets(text); gets(text);
        if(strlen(text)>600){
            printf("Metin En Fazla 600 Karakter Olabilir!\n");
            fflush(stdin);
            goto getpasswordagain;
        }
    }
    // Kullanıcıdan anahtar değeri alma
    wprintf(L"Lütfen Geri Öteleme Miktarını Giriniz: ");
    getkeyagain:
    if(scanf("%d", &key)!=1){
        fflush(stdin);
        wprintf(L"Lütfen Sadece Sayı Değeri Giriniz!\n");
        goto getkeyagain;
    }

    // Şifreleme
    deencrypt(text, key);
    wprintf(L"Deşifrelenmiş Metniniz: %s\n", text);
    return 0;
}
int main() {
    int key;
    char text[600];
    int choice,answer;
    setlocale(LC_ALL,"Turkish");
    // Kullanıcıya şifreleme veya deşifreleme işlemlerinden hangi seçeneği seçeceğini sorma
    wprintf(L"Yapılacak İşlemi Seçiniz:\n");
    choosingpart:
    wprintf(L"  1 - Metin Şifreleme\n");
    wprintf(L"  2 - Metin Deşifreleme\n");
    wprintf(L"  3 - Programı Sonlandır\n");
    wprintf(L"Lütfen Seçiminizi Yapınız (1/2/3): ");
    //scanf("%d", &choice);
    if(scanf("%d", &choice)!=1){         //Girilen değerin sayı olup olmadığını kontrol ediyoruz.
        wprintf(L"Lütfen Sadece Belirtilen Sayı Değerlerini Giriniz!\n\n");
        fflush(stdin);
        goto choosingpart;}


    switch (choice) {
        case 1:
            encryptsystem();
            wprintf(L"Program Başa Dönüyor\n\n");
            goto choosingpart;

        case 2:
            // Deşifreleme
            deencryptsystem();
            wprintf(L"Program Başa Dönüyor\n\n");
            goto choosingpart;

        case 3:
            //Programı sonlandırma
            wprintf(L"Çıkışınız Yapıldı.\n\n");
            break;

        default:
            //Tanımlanmayan değerlerde hata verme
            wprintf(L"Hatalı Seçim. Lütfen Geçerli Bir İşlem Seçiniz.\n\n");
            goto choosingpart;
    }

    return 0;
}
