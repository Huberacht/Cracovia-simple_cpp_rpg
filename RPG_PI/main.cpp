//
//  main.cpp
//  RPG_IO
//
//  Created by Hubert on 10/12/2020.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string>
#include <curses.h>

int ZB=10,W=20,Wengle=50,HP=45;//ZB-Zdolność_Bojowa-decyduje o obrażeniach w czasie walki,W-decyduje ile ciosów można wytrzmyać przed przyjęciem obrażen do puntków życia,HP-punkty życia,gdy się wyczerpią twoja przygoda się skończy,Wengle-waluta
int skills[6];//0-Kamuflaż,1-Łowiectwo,2-Finezja,3-Błyskawica,4-Regeneracja,5-Geniusz
int x,y;//współrzędne gracza na mapie
char playerName[6];//nazwa gracza
int weapon_main;//broń główna
bool game_map1=false;
bool game_map2=false;
bool death=false;//gracz żyje czy nie
//Ekwipunek,przedmioty podstawowe
int woda=0;//ilosc butelek wody w ekwipunku
int hp_potion=0;//ilosc mikstur HP w ekwipunku
int w_potion=0;//ilosc mikstur W w ekwipunku
int zb_potion=0;//ilosc mikstur ZB w ekwipunku
int food=20;//ilosc jedzenia w ekwipunku
//
//Ekwipunek,przedmioty kluczowe
int scroll_main=0;
int amulet_main=0;
int portal_fragment=0;
int kara=(arc4random() % 2);//wydarzenie losowe
//
//statystyki końcowe
int killed_end=0;//ilosc pokonanych przeciwnikow
int money_end=0;//ilosc zebranych pieniedzy
int move_end=0;//ilosc ruchow
//
//

int happened=0;
int random_event=0;
bool event0=false;
bool event1=false;
bool event2=false;
bool event3=false;
bool event4=false;
bool event5=false;
//
//Ceny w losowo generowanym sklepie plus loot waluty z losowych walk
int cena_hp=0;
int cena_w=0;
int cena_zb=0;
int cena_woda=0;
int cena_weapon4=0;
int cena_weapon5=0;
int cena_weapon6=0;
int buy;
int loot=0;
int in_shop=0;
int hunt;
//
//Mapa poziomu nr 1
char map1[5][12] =
{"###########",
 "# # # # # #",
 "H    ?    !",
 "# # # # # #",
 "###########"};
//
//Mapa poziomu nr 2
char map2[9][106] =
{"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^",
 "^^^^^^^           ^^^^^^               {########^^        -           ~~~~~%%%%%%%%%%%%%%%%%%%%%%%%%%%%%^",
 "H                     !                {# # # # #^^     ||$||        ~~~~~%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%^",
 "^^^^^^^^^       ^^^^^^                  {# # # #^^                    =====     %%%%%%%%%%%%%%%%%%%%%%%%^",
 "^  ^^^^^^^     ^^^^^^       %%%         {# # # #^^^                  ~~~~~%%%%    %%%%         %%%%%%%%%^",
 "^ ^^^^^^^^^   ^^^^^^      %%   %% ##   #  { # # #^^ ###     ####%%%%%%~~~~~%%%%  %%%%   %%%  %%%%%%%%%%%^",
 "^ ^^^^^^^^^^ ^^^^^^^      %%   %%###   ### {# # #^^  ##   ####%%%%%%~~~~~%%%%%%         %%%%    %%%%%%%%^",
 "^             ^^^^^^        %%% ###(   )  { # #^^    #(   )#%%%%~~~~~%%%%%%%%%%%%%%%%%%%%              !^",
 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
};
//przestrzen nazw std
using namespace std;
//
//Funkcja odpowiedzialna za pauze
void pauza()
{
    char ch;
    cout<<endl;
    cout<<endl<<"Naciśnij dwukrotnie enter aby kontynuować..."<<endl;
        getchar();
        while ((ch = getchar()) != '\n' && ch != EOF)
            continue;
    for (int i=0; i<50; i++) {
        cout<<endl;
    }
    
    
    
}
    
   


//
//Funkcja ruchu po mapie
void Move(int V,int H){
    int y2=y+V;
    int x2=x+H;
    
    if ((map1[y][x2] ==' ') || (map1[y][x2] =='?') || (map1[y][x2] =='!') || (map2[y][x2] ==' ') || (map2[y][x2] =='?') || (map2[y][x2] =='!'))
    {
        map1[y][x]=' ';
        map2[y][x]=' ';
    x+=H;
    map1[y][x]=playerName[0];
    map2[y][x]=playerName[0];
    }
    if ((map1[y2][x] ==' ') || (map1[y][x2] =='?') || (map1[y][x2] =='!') || (map2[y2][x] ==' ') || (map2[y][x2] =='?') || (map2[y][x2] =='!'))
    {
        map1[y][x]=' ';
        map2[y][x]=' ';
        y += V;
        map1[y][x]=playerName[0];
        map2[y][x]=playerName[0];
        
    }
    
}
void Input()
{   cout<<"E - Ekwipunek"<<endl<<"K - Karta postaci"<<endl<<"U - użyj przedmiotu"<<endl<<"W - ruch w górę"<<endl<<"A - ruch w lewo"<<endl<<"S - ruch w dół"<<endl<<"D - ruch w prawo"<<endl;
    char c = 0;
    cin>>c;
    switch (c)
    {
        case 117:
            
            if(hp_potion>0){
                cout<<"1 - Wypij miksturę HP"<<endl;
            }
            if(zb_potion>0){
                cout<<"2 - Wypij miksturę ZB"<<endl;
            }
            if(w_potion>0){
                cout<<"3 - Wypij miksturę W"<<endl;
            }
            if(woda>0){
                cout<<"4 - Wypij butelkę wody"<<endl;
                
            }
            int action;
            cin>>action;
            if (action==1)
            {cout<<"Wypiłeś miksturę HP"<<endl;
                HP=+15;
                hp_potion=-1;
            }
            if (action==2)
            {cout<<"Wypiłeś miksturę W"<<endl;
                W=+15;
                w_potion=-1;
            }
            if (action==3)
            {cout<<"Wypiłeś miksturę ZB"<<endl;
                zb_potion=-1;
            }
            if (action==4)
            {cout<<"Wypiłeś butelkę wody"<<endl;
                woda=-1;
            }
            
            pauza();
            cout<<endl;
            break;
            case 101:
            if(weapon_main==0)
                cout<<"Twoja aktualna broń to krótki miecz"<<endl<<"OBR 2-7"<<endl;
            if(weapon_main==1)
                cout<<"Twoja aktualna broń to sztylet"<<endl<<"OBR 4"<<endl;
            if(weapon_main==2)
                cout<<"Twoja aktualna broń to topór"<<endl<<"OBR 1-9"<<endl;
            if(weapon_main==3)
                cout<<"Twoja aktualna broń to długi miecz"<<endl<<"OBR 6-13"<<endl;
            if(weapon_main==4)
                cout<<"Twoja aktualna broń to podwójne sztylety"<<endl<<"OBR 9"<<endl;
            if(weapon_main==5)
                cout<<"Twoja aktualna broń to morgensztern"<<endl<<"OBR 1-25"<<endl;
            if(Wengle>0)
                cout<<"Posiadasz "<<Wengle<<" Wengli"<<endl;
            if(hp_potion>0){
                cout<<"Posiadasz "<<hp_potion<<" mikstur HP"<<endl;
            }
            if(hp_potion>0){
                cout<<"Posiadasz "<<zb_potion<<" mikstur ZB"<<endl;
            }
            if(w_potion>0){
                cout<<"Posiadasz "<<w_potion<<" mikstur W"<<endl;
            }
            if(woda>0){
                cout<<"Posiadasz "<<woda<<" butelek wody"<<endl;
                
            }
            if(food>0)
                cout<<"Posiadasz "<<food<<" racji żywnościowych"<<endl;
            if(portal_fragment>0)
                cout<<"Posiadasz "<<portal_fragment<<" fragmentów portalu"<<endl;
            if(scroll_main>0)
                cout<<"Posiadasz zwój,który musisz dostarczyć do króla"<<endl;
            if(amulet_main>0)
                cout<<"Posiadasz amulet swojego mistrza"<<endl;
            pauza();
            cout<<endl;
            break;
        case 107:
            cout<<"Karta postaci "<<playerName<<endl;
            cout<<"Punkty Zdrowia - "<<HP<<endl;
            cout<<"Zdolność bojowa - "<<ZB<<endl;
            cout<<"Wytrzymałość - "<<W<<endl;
            cout<<"Wengle - "<<Wengle<<endl;
            cout<<"Umiejętności - ";
            if (skills[0]==1){
                cout<<"Kamuflaż ";
            }
            if (skills[1]==1){
                cout<<"Łowiectwo ";
            }
            if (skills[2]==1){
                cout<<"Finezja ";
            }
            if (skills[3]==1){
                cout<<"Błyskawica ";
            }
            if (skills[4]==1){
                cout<<"Regeneracja ";
            }
            if (skills[5]==1){
                cout<<"Geniusz ";
            }
            pauza();
            cout<<endl;
            break;
    case 119:
            Move(-1,0);
            food=-1;
            move_end+=1;
            cout<<endl;
        break;
    case 115:
            Move(1,0);
            food=-1;
            move_end+=1;
            cout<<endl;
        break;
    case 97:
            Move(0,-1);
            food=-1;
            move_end+=1;
            cout<<endl;
        break;
    case 100:
            Move(0,1);
            food=-1;
            move_end+=1;
            cout<<endl;
            
            
            
        break;
    default:
            cout<<"Coś poszło nie tak :("<<endl;
        break;
        
    }
    }

//

//Funkcja odpowiedzialna za walke(i dodawanie broni)
void walka( int HP_player=1, int W_player=1,int ZB_player=1,int HP_enemy=1, int W_enemy=1,int ZB_enemy=1,string enemyName="?")
{   cout<<"Walka zostaje rozpoczęta!"<<endl;
    for(int i=1;;i++)
    { cout<<"RUNDA "<<i<<endl;
        ZB_player=ZB;
        //Dodawanie dodatkowych broni
        
    if (weapon_main==1)
    {ZB_player=ZB_player+(arc4random()%5 + 2);}
    if(weapon_main==2)
    {ZB_player=ZB_player+4;}
    if(weapon_main==3)
    {ZB_player=ZB_player+(arc4random()%8+1);}
    if(weapon_main==4)
    {ZB_player=ZB_player+(arc4random()%8 + 6);}
    if(weapon_main==5)
    {ZB_player=ZB_player+9;}
    if(weapon_main==6)
    {ZB_player=ZB_player+(arc4random()%25 + 1);}
        //
    cout<<playerName<<"| HP : "<<HP_player<<", W : "<<W_player<<", ZB : "<<ZB_player<<" |"<<endl;
    cout<<enemyName<<"| HP : "<<HP_enemy<<", W : "<<W_enemy<<", ZB : "<<ZB_enemy<<" |"<<endl;
    cout<<playerName<<" uderza "<<enemyName<<" za "<<ZB_player<<" punktów obrażeń!"<<endl;
    if(W_enemy>0)
    {W_enemy=W_enemy-ZB_player;}
    else
    {HP_enemy=HP_enemy-ZB_player;}
    if (HP_enemy<=0)
        {cout<<"Wygrana!"<<endl;
            ZB+=1;
            W+=1;
            loot=arc4random()%35+10;
            Wengle=+loot;
            killed_end+=1;
            break;}
    cout<<enemyName<<"| HP : "<<HP_enemy<<" W : "<<W_enemy<<" |"<<endl;
    cout<<enemyName<<" uderza "<<playerName<<" za "<<ZB_enemy<<" punktów obrażeń!"<<endl;
    if(W_player>0)
    {W_player=W_player-ZB_enemy;}
    else
    {HP_player=HP_player-ZB_enemy;}
        if(HP_player<=0)
        {cout<<"Zostajesz zabity przez "<<enemyName<<endl;
         cout<<"Twoja przygoda dobiegła końca"<<endl;
            death=true;
            break;}
        
        
   
    }
    HP=HP_player;
    W=20;
    pauza();
}
//
//Ekspozycja 1
void wprowadzenie_past()
{
    cout<<"W rozciągającej się na wschodzie krainie Cracovii od wieków,zgodnie ze zwyczajem,rodzice wysyłali swoje najzdolniejsze dzieci do klasztoru Agie-hu,gdy nadchodziły ich siódme urodziny.Tam młodych adeptów uczono specjalnych umiejętności oraz sztuk walki,udoskonalonych przez ich czcigodnych przodków.";
        pauza();
        cout<<"Do wojowniczego zakonu Agie-hu należą mistrzowie tych dyscyplin,a dzieci pod ich opieką obdarzają swoich nauczycieli miłością i szacunkiem,pomimo surowego treningu,jakiemu są poddawane.Bowiem pewnego dnia,gdy wreszcie opanują dyscypliny Agie-hu,będą mogły wrócić do swoich domów,wyposażone w umysł i ciało,które umożliwiają im obronę siebie samych oraz ich krajan przed nieprzemijającym zagrożeniem wojną z Mrocznymi Władcami Smoggu";
        pauza();
        cout<<"W dawnych czasach,podczas Ery Duszności,w Krakovii toczyła się wojna z Mrocznymi Władcami.Konflikt ten był długim i gorzkim starciem sił,które zakończyło się zwycięstwem dynastii Gazuv w wielkiej bitwie w wąwozie Kościelisko.Król Gaz I,rozbił armie Mrocznych Władców i zepchnął je w Otchłań Czadu z której wypełzli.Od tamtej pory Władcy poprzysięgli zemstę na rodzinie króla...";
        pauza();
}
//
//Ekspozycja 2
void wprowadzenie_present()
{
cout<<
     "   Dziś jest przeddzień święta Bar-bur-ki.Zgodnie ze starą tradycją,Agiehowcy zbierają się w ten dzień w swoim klasztorze u stóp góry Trzech Koron,aby odnowić swe przysięgi wobec klasztoru.Wielu obieżyświatów oraz emisariuszy podróżuje z daleka,aby zdążyć na jutrzejsze uroczystości,które wyznaczają początek nowego roku w Cracovii.";
    pauza();
    cout<<"Jak cię zwą młody Agiehowcu?"<<endl;
    for( int i = 0; i < 6; i++){
            
            cin >> playerName[i];
        }
    cout<<"Jesteś młodym kadetem Agie-hu,zwanym "<<playerName<<".";
    cout<<"Jesteś inicjantem tego zacnego zakonu i to będzie twój ósmy rok,gdy bierzesz udział w świętowaniu Bar-bur-ki.Przepełniają cię uczucia dumy i ekscytacji,takie same jak wtedy,gdy przybyłeś tu ze swojej rodzinnej wioski,nieco ponad połowę twego krótkiego żywota temu.";
    pauza();
    cout<<"Kilka ostatnich dni to był emocjonujący czas dla ciebie i twoich bratnich kadetów.Obieżyświaty powtarzają swoje opowieści o wygranych bitwach i przeżytych Karczmach,największych biesiadach w królestwie,a wszystkich ogarnia radość oraz pełne nadziei wyczekiwania,by Nowy Rok przyniósł dalszy pokój i dobrobyt twojej ukochanej ojczyźnie.";
    pauza();
    cout<<"Klasztor tętni życiem,gdy dokańczane są ostatnie przygotowania na jutrzejsze święto,ale dla ciebie i pozostałych kadetów codzienna rutyna nie zmieniła się zbytnio.Twój trening i nauka przebiegają jak zwykle,chociaż teraz wyjątkowo trudno ci się skoncentrować,kiedy twój nauczyciel-Mistrz Agie-hu Zeet-ko-wykłada klasie o ceplusplusii,starożytnej metodzie magii.";
    pauza();
    cout<<"- "<<playerName<<"! - woła,wytrącając cię nagle z marzeń."<<endl<<"- Może łaskawie zechcesz nas oświecić?Podaj nam nazwę sposobu wywołania zmiennej magicznej bez znaku runicznego."<<endl<<"Wachasz się,w milczeniu siedząc z otwartymi ustami,zaskoczony pytaniem nauczyciela."<<endl<<"- Mmm...Tak jak myślałem-powiada,potrząsając głową z dezaprobatą. - To nie pierwszy raz,gdy nie zaszczycasz mnie swoją uwagą.Być może kara,jaką odbędziesz teraz,posłuży do wyostrzenia twojej koncentracji w przyszłości.";
    pauza();
    cout<<"Na swojej drodze napotkasz wiele zdarzeń,o których wynikach zadecyduje losowość.Czasami pozytywny skutek doprowadzi cię do nowej linii dialogowej,czasami negatywny spowoduje rozpoczęcie walki.Możesz zwiększyć swoje szansę na konkretny wynik posiadając odpowiednie umiejętności lub przedmioty.Pamiętaj że czasami zdarzenia z początku niefortunne mogą zaowocować w przyszłości...";
    pauza();
    cout<<"- Niechaj los zdecyduje o twojej naganie."<<endl<<"Rzuca złotą monetą w powietrze i łapie ją zręcznie na wierzchu swojej lewej dłoni.Spoglądając na świeżo wybitą podobiznę króla Gaza I,mówi głośno:"<<endl;
    
    if (kara==0)
    {
        cout<<"- Niech zatem tak będzie.Dodatkowy trening bronią.Jutro z rana.Na godzinę przed świtem.Pokażesz mi się wyposażony i gotowy na placu ćwiczebnym.Czy wszystko jasne?"<<endl<<"- Tak,mój panie - odpowiadasz z pokorą.";
        pauza();
    }
        else if (kara==1){
            
            cout<<"- Niech zatem tak będzie.Dodatkowe ćwiczenia fizyczne.Jutro z rana.Na godzinę przed świtem.Pokażesz mi się wyposażony i gotowy na placu ćwiczebnym.Czy wszystko jasne?"<<endl<<"- Tak,mój panie - odpowiadasz z pokorą.";
            pauza();
        }
}
//
//Kreator postaci
void kreator(){
    cout<<"Podczas swojego treningu w klasztorze Agie-hu udoskonaliłeś znajomość walki - Zdolność Bojowa(ZB) oraz rozwinąłeś kondycję fizyczną - Wytrzymałość(W).Bazowa wartość ZB wynosi 10,zas W - 20.Prócz tego rozwinąłeś specjalną umiejętność i zebrałeś nieco Wengli,waluty królestwa.Zanim wyruszysz na przygodę,musisz określić swoją przeszłość w zakonie.";
    pauza();
    cout<<"Wybierz swoją przeszłość przed opuszczeniem swojej rodzinnej wioski i dołączeniem do zakonu Agie-hu: "<<endl;
    cout<<"1 - Syn Kowala (ZB+5,W+5)"<<endl;
    cout<<"2 - Myśliwy (ZB+3,Umiejętność Łowiectwo odblokowana)"<<endl;
    cout<<"3 - Uczony (W+3,Umiejętność Geniusz odblokowana)"<<endl;
    cout<<"4 - Złodziejaszek (W+1,ZB+1,Wengle+50)"<<endl;
    int player_past;
    cin>>player_past;
    
    if (player_past==1)
    {ZB+=4;
        W+=4;}
    else if(player_past==2)
    {ZB+=3;
        skills[0]=1;}
    else if(player_past==3)
    {W+=3;
        skills[5]=1;
    
    }
    else if(player_past==4)
    {W+=1;
    ZB+=1;
    Wengle+=50;
    
    }
    cout<<"Wybierz umiejętność opanowaną w czasie swojej nauki: "<<endl;
    cout<<"1 - Kamuflaż"<<endl;
    cout<<"2 - Łowiectwo"<<endl;
    cout<<"3 - Finezja"<<endl;
    cout<<"4 - Błyskawica"<<endl;
    cout<<"5 - Regeneracja"<<endl;
    cout<<"6 - Geniusz"<<endl;
    int skill_choice;
    cin>>skill_choice;
    switch(skill_choice)
    {case 1:
        skills[0]=1;
        break;
        case 2:
            skills[1]=1;
            break;
        case 3:
            skills[2]=1;
            break;
        case 4:
            skills[3]=1;
            break;
        case 5:
            skills[4]=1;
            break;
        case 6:
            skills[5]=1;
            break;
        default:cout<<"błąd";
            break;
    }
    cout<<"Ukończyłeś kreację swojej postaci.Twoje statystyki: "<<endl;
    cout<<"Punkty Zdrowia - "<<HP<<endl;
    cout<<"Zdolność bojowa - "<<ZB<<endl;
    cout<<"Wytrzymałość - "<<W<<endl;
    cout<<"Wengle - "<<Wengle<<endl;
    cout<<"Umiejętności - ";
    if (skills[0]==1){
        cout<<"Kamuflaż ";
    }
    if (skills[1]==1){
        cout<<"Łowiectwo ";
    }
    if (skills[2]==1){
        cout<<"Finezja ";
    }
    if (skills[3]==1){
        cout<<"Błyskawica ";
    }
    if (skills[4]==1){
        cout<<"Regeneracja ";
    }
    if (skills[5]==1){
        cout<<"Geniusz ";
    }
    cout<<endl;
    
}
//
//Funckja w której gracz uczy się na czym polega walka
void trening()
{
    cout<<"Ze snu budzi cię mechaniczny dzwonek czasomierza,który poprzedniego wieczora ustawiłeś obok swojej poduszki.W przyćmionym świete świecy w dormitorium inicjantów wstajesz z posłania i szybko zakładasz swoją zieloną koszulę oraz płaszcz.Potem opuszczasz śpiących towarzyszy.Nie masz zamiaru spóźnić się na sesję treningową z Mistrzem Zeet-ko.Wchodzisz przez północne drzwi dormitorium,otwierające się bezpośrednio na plać ćwiczebny pośrodku klasztoru.";
    pauza();
    cout<<"Mistrz Zeet-ko już czeka tam na ciebie.Ubrany jest w swój ceremonialny strój,gotowy na dzisiejsze uroczystości.W bladym świetle bardzo wczesnego poranka twoje bystre oczy dostrzegają tego groźnego wojownika,oczekującego obok stojaka z bronią w centrum placu ćwiczebnego.Wita cię skinieniem głowy i mówi,abyś wybrał jedną z broni ze stojaka.Wybierasz: "<<endl;
    cout<<"1 - Krótki Miecz (OBR 2-7)"<<endl;
    cout<<"2 - Sztylet (OBR 4)"<<endl;
    cout<<"3 - Topór (OBR 1-9)"<<endl;
    cin>>weapon_main;
    cout<<"Wartość OBR jest losowana z zakresu dla każdego uderzenia w walce(więcej o tym później),po czym dodawana do twojej wartośći ZB";
     pauza();
     cout<<"Twój mistrz cierpliwie przeprowadza trening,na który skazałeś się swoja nieuwagą."<<endl;
    if (kara==0)
    {cout<<"ZB+1"<<endl;
        ZB+=1;
    }
    if (kara==1)
    {cout<<"W+1"<<endl;
        W+=1;
    }
    cout<<"- Dobrze,na koniec możesz zaprezentować mi czego udało ci się nauczyć przez te wszystkie lata. -  "<<endl<<"mówi skazując palcem na kukłę stojącą w rogu sali.Wyciągasz swoją broń i ze skupieniem widocznym na swojej twarzy zbliżasz się do swojego pierwszego przeciwnika.Kukła patrzy na ciebie zuchwale,w jej oczach widzisz powątpiewanie w twoje umiejętności.Och,jak bardzo się myli."<<endl;
    pauza();
    cout<<"Czas na twoją pierwszą walkę.Rezultat walki zawsze zostanie wyświetlony.Dzięki wielu latom treningu twoja zwinność i szybkość nie ma sobie równych,zawsze więc jako pierwszy zadajesz cios.Wartości statystyk przeciwnika(HP,ZB,W)zostają podane przed rozpoczęciem walki.Ilość zadanych obrażeń to twoja całkowita wartość ZB(włącznie z OBR z broni).Obaj uczestniczy walki muszą najpierw wyzerować wartość wytrzymałości przeciwnika,aby móc zadawać obrażenia Punktom Zdrowia.Oznacza to że nawet 1 W może uratować cię przed przyjęciem obrażeń od wroga.W momencie gdy którykolwiek z walczących straci wszystkie punkty zdrowia,walka kończy się.Jeśli to ty jesteś tym nieszczęśliwcem,twoja przygoda kończy się.Po każdej walce twoje W odnawia się do wartości początkowej,ale HP pozostaje na poziomie z końca walki.By je odnowić musisz wykorzystać przedmiot leczący lub natrafić na odpowiednią opcję dialogową w czasie przygody,ale nie możesz przekroczyć wartości bazowej.Wartość bazowa zawsze wynosi 45.Po każdej wygrane walce otrzymujesz jeden punkt W oraz ZB.";
    pauza();
    cout<<"Rzucasz się na kukłę!"<<endl;
    walka(HP,W,ZB,10,25,0,"Kukła");
    cout<<"Kukła pada pod naporem twoich ciosów!"<<endl<<" - Dobra robota, "<<playerName<<".Możesz chwilę odpocząć.Zdaje się,że swoją nieuwagę w klasie nadrabiasz naturalnym talentem do broni.Twoje postępy są bardzo obiecujące.Jeśli tylko włożysz podobny wysiłek w naukę,wówczas być może pewnego dnia ty także osiągniesz rangę Mistrza Agie-ha."<<endl<<"Dziękujesz Mistrzowi Zeet-ko za jego pochwałę i radę.Nigdy nie chwali nikogo bez przyczyny,a słowa jakimi cię docenił,sprawiają,że postanawiasz już więcej nie pogrążać się w marzeniach podczas lekcji.Podchodzisz do beczułki w rogu sali i napełniasz bukłak świeżą wodą."<<endl<<"Otrzymano przedmiot Woda x1 !"<<endl<<"Bierzesz pierwszy łyk, gdy nagle ciszę otoczenia rozrywa łomot dzwonu strażniczego.Uderzono na alarm dla klasztoru!";
    woda+=1;
    pauza();
    cout<<"Mistrz Zeet-ko cicho przeklina pod nosem.Wpatruje się z napięciem w stronę zachodu,ku niebu,które z każdą mijającą chwilą staje się dziwnie ciemniejsze.W pierwszej chwili nie widzisz nic poza półmrokiem,ale wtedy twoje oczy spostrzegają coś poruszającego się w gęstych ciemnościach.Do klasztoru zbliżają się tysiące czarnych,kudłatych stworów."<<endl<<"- Czadodzicy - rzuca Mistrz Zeet-ko."<<endl<<"Ponure łomotanie dzwonu alarmowego obudziło wszystkich w klasztorze.Kilku Mistrzów i niższych rangą wypadło z dormitoriów.Większość nie ma swoich pancerzy bojowych,ale każdy jest uzbrojony i gotowy do obrony twierdzy przed atakiem.";
    pauza();
    cout<<"Zza okno zauważasz,że kilka stworów dotarło niemal do głównych wrót.Zamierzają dostać się do środkla,zanim wielkie kraty nie opadną i nie odetną im drogi."<<endl<<" - "<<playerName<<",za mną! - rozkazuje Mistrz Zeet-ko,po czym odwraca się i biegnie w kierunku wejścia do strażnicy.";
    pauza();
    cout<<"Mistrz Zeet-ko biegnąc dobywa swojego miecza.Spogląda przez ramię,po czym rzuca w twoją stronę małą,czerwoną buteleczkę.Łapiesz ją w locie i od razu rozpoznajesz jej zawartość.To jeden z leczniczych wywarów Be-gie-hu,zaopatrującego twój zakon w przeróżne przydatne,magiczne specyfiki."<<endl<<"Otrzymano mikstury HP,W i ZB!"<<endl<<"Twoje zmysły są rozbudzone i napięte w oczekiwaniu na prawdziwą bitwę,jaka wkrótce się zacznie.Mistrz Zeet-ko rzuca się na Czadodzikich.Błyskawicznym,zabójczym cięciem w górę uderza pierwszego wroga,rozcinając jego brzydką twarz od policzka do skroni.Ciało Czadodzikiego upada w tył,zostawiając w powietrzu łuk wstrętnej czarnej posoki.Mistrz Zeet-kko wykonuje serię cięć mieczem,ścinając głowy trzech następnych stworów.Kolejny tuzin biegnie naprdzód,chcąc opaść na twojego Mistrza całą liczną gromadą.";
    hp_potion+=3;
    w_potion+=3;
    zb_potion+=3;
    pauza();
    cout<<" - Zostaw te szumowiny mnie - rozkazuje Mistrz.-Ruszaj i zamknij bramę!"<<endl<<"Okrwawioną głowicą swojego miecza wskazuje dźwignie osadzoną w pobliskiej wieży,oddzielonej od was pasmem dormitoriów twoich przyjaciół akalitów z zakonu.Natychmiast odwracasz się i biec w tamtą stronę,chcąc wykonać ten rozkaz jak najszybciej.Brakuje ci tylko kilku metrów do dormitorii,gdy nagle jeden z Czadodzikich odłącza się od walki i rusza mając zamiar odciąć ci drogę.Z mrożącym krew w żyłach warkotem obniża swą włócznię i szykuje się,by nadziać cię na jej grot z czarnego żelaza.";
    pauza();
    walka(HP,W,ZB,10,15,15,"Czadodziki z włócznią");
    cout<<"Udało ci się poskromić pierwszego Czadodzikiego w życiu.Niestety,nie czas na świętowanie.Biegiem wpadasz do dormitoriów.Jedyne co napotykasz to niepokojącą ciszę...";
    pauza();
}
void ucieczka(){
    cout<<"Pociągasz za dźwignię.Niemal natychmiast słyszysz jak wrota do klasztoru uderzają z łoskotem na ziemię.Nie masz jednak czasu na na odpoczynek.Zrywasz się biegiem by pomóc swojemu mistrzowi.Niestety,gdy tylko opuszczasz dormitoria,napotyka cię przerażający widok.Twój mistrz klęczy oparty o swój miecz,z jego licznych ran sączy się krew.Podbiegasz do niego czym prędzej."<<endl<<"- "<<playerName<<"- mówienie sprawia mu wiele bólu. - Obawiam się że to mój koniec.Nie możesz pozwolić by to co spotkało dziś nasz klasztor powtórzyło się w stolicy.Weź ten zwój i dostarcz go królowi,on będzie wiedział co robić.Prócz tego mój amulet - nigdy się z nim nie rozstawaj.Pomoże ci w momencie największej próby."<<endl<<"Twój mistrz wciska ci do ręki dwa niewielkie przedmioty.Całe twoje ciało przeszywa chłód.Wiesz,że w żaden sposób nie uda ci się mu pomóc.Przyciskasz zwój i amulet bliżej siebie,w twoich oczach widać determinację."<<endl<<"- Dobrze,"<<playerName<<".Nie zapomnij tego dnia.Bądź odważny i silny.A teraz pędź,pędź jak nigdy dotąd!"<<endl<<"Ze łazmi w oczach zeskakujesz z muru i zaczynasz biec przed siebie.Żaden z czadodzikich nie jest w stanie cię dogonić.Kiedy dobiegasz do odległego wzgórza,ostatni raz obracasz się by spojrzeć na klasztor.Wszystko leży w gruzach,a w powietrzu unosi się czarny dym.Zanim odwracasz się by pomknąć przed siebie,zastanawiasz się jeszcze czy ktokolwiek oprócz ciebie przeżył i zdołał uciec.";
    scroll_main=1;
    amulet_main=1;
    pauza();
    
    
}
void event_0(){
    cout<<"Nie możesz uwierzyć własnym oczom.Na ziemi walają się ciała adeptów.Nad nimi stoi pochylonych dwóch Czadodzikich.Gdy tylko cię zauważają,rzucają się na ciebie!"<<endl;
    walka(HP,W,ZB,20,20,15,"Para Czadodzikich");
    event0=true;
}
void event_1(){
    cout<<"Kontynuujesz swoją przeprawę przez góry gdy nagle z oddali słyszysz okrzyki o pomoc.Biegniesz w kierunku odgłosów.Jakiś męzczyzna chowa się za głazami przed Trollem Skalnym!Pamiętając swoje nauki w zakonie rzucasz się z pomocą!"<<endl;
    walka(HP,W,ZB,10,35,35,"Skalny Troll");
    cout<<"Uratowany człowiek dziękuję ci.Okazuje się że to jeden z rycerzy królestwa którego celem była naprawa portalu na wschód stąd by pozostałości z zachodnich oddziałów mogły dotrzeć do stolicy.Armie Władców Smoggu rozbili obóz i uniemożliwiają podróż na zachód.Wyjaśniasz mu swoją misję.Rycerz kiwa głową po czym wyjmuje z plecaka odłamek portalu.Okazuje się że potrzeba jeszcze 2 by być w stanie uaktywnić portal.Obiecujesz mu że się tym zajmiesz po czym wasze drogi się rozchodzą."<<endl;
    pauza();
    map2[6][37]='!';
    portal_fragment+=1;
    event1=true;
    
    
}
void koniec()
{
    cout<<"Udało ci się dotrzeć do zamku.Przebiegasz koło zazkoczonych strażników.Po kilku minutach udało ci się dotrzeć do sali tronowej.Z hukiem wyważasz drzwi.Podnosisz w ręku zwój i głośno krzyczysz że muszą cię wysłuchać.Wszyscy w sali wydają się patrzeć na ciebie jak na wariata.Zaczynasz krzyczeć o nadchodzącym niebezpieczeństwie.Zaczynasz opowiadać co wydarzyło się w klasztorze.Gdy ze łzami w oczach wspominasz mistrze Zeet-ko,nagle zza kuluaru wysowa się wysoka postać."<<endl<<" - O czym ty mówisz "<<endl<<"Nie możesz uwierzyć własnym oczom.Postać to sam Mistrz Zeet-ko!Ale to niemożliwe.Zaczynasz jąkliwie powtarzać że to przecież niemożliwe."<<endl<<" - Królu,ten młodzik ewidentnie postradał zmysły.Nic nam nie grozi.Pozwól mi się z nim rozprawić a następnie wrócimy do planowania bankietu dla wszystkich szlachciców królestwa.";
    pauza();
    if(amulet_main==0)
    {cout<<"Mistrz Zeet-ko rzuca się na ciebie!"<<endl;
        walka(HP,W,ZB,100,100,100,"Mistrz Zeet-ko");}
    else
        cout<<"Mistrz Zeet-ko zbliża się do ciebie i wyciąga swój miecz.Nagle jednak coś zaczyna iskrzyć w twojej sakiewce.To amulet który otrzymałeś od niego w klasztorze.Twarz twojego dawnego mistrza blednieje"<<endl<<" - Nie!NIE!Odłóż to!"<<endl<<"Nagle jego skóra zaczyna wrzeć,po czym topi się i odpada.Pod nią czaiła się obrzydliwa czarna niczym smoła postać.To nie mistrz Zeet-ko tylko sługa Władców Smoggu!Musisz go powstrzymać nim komuś na sali stanie się krzywda!"<<endl;
    walka(HP,W,ZB,50,20,50,"Mroczny sługa");
    cout<<"Ciało mrocznego sługi opada z łoskotem na ziemię.Cała sala patrzy na nie w osłupieniu.Niektórzy dopiero teraz zrozumieli co się stało."<<endl<<"-Władcy Smoggu!Władcy Smoggu powrócili!-ktoś krzyczy."<<"Głośno potwierdzasz jego obawy,na tyle głośno by każdy obecny usłyszał - królestwo jest w niebezpieczeństwie!Po tych słowach podchodzi do ciebie sam król!Od razu upadasz na kolana."<<endl<<"Nie wygłupiaj się,dziecko.Wygląda na to że uratowałeś nam dzisiaj życie!Powstań i idź odpocząć.Słudzy!Wyrzućcie ciało tego robaka z mojej sali tronowej!A ty,chłopcze,lepiej się przygotuj.Wygląda na to że wojna dopiero się rozpoczęła!"<<endl;
    pauza();
    cout<<"DZIĘKUJĘ ZA ZAGRANIE W MOJĄ GRĘ!TWÓJ WYNIK TRAFIŁ DO SALI SŁAW!BRAWO!LECZ NIE CIESZ SIĘ ZA BARDZO - MROCZNI SŁUDZY NADCHODZĄ W SEQUELU(NIE NO SPOKOJNIE RACZEJ NIE)"<<endl;
    pauza();
        
}
void event_2(){
    cout<<"Po środku starych ruin wśród mroźnych szczytów odnajdujesz odłamek potrzebny do otwarcia portalu.Niestety gdy chcesz go podnieść zlatuje się stado harpii.Wzdychasz cicho po czym wyciągasz broń."<<endl;
    walka(HP,W,ZB,20,25,25,"Stado Harpii");
    cout<<"Podnosisz fragment po czym udajesz się w dalszą drogę"<<endl;
    portal_fragment+=1;
    event2=true;
    map2[7][37]='!';
    pauza();
    
}
void portal(){
    cout<<"Wkładasz 3 brakujące fragmenty do portalu.Portal tli się lekko po czym przejście się otwiera.Nie tracąc czasu wskakujesz do niego"<<endl;
    map2[3][69]='!';
    
    x=56;
    y=7;
    map2[7][56]=playerName[0];
    map2[7][37]=' ';
    pauza();
    portal_fragment=0;
    
}
void bandyci(){
    cout<<"W drodze do portalu napotykasz grupkę bandytów.Chowając się w krzakach podsłuchujesz rozmowę ich herszta.Wygląda na to że są w posiadaniu fragmentu portalu i chcą go zniszczyć by uniemożliwić nikomu dotarcie do stolicy.Zapewne są już na usługach Władców Smoggu!Nie namyślając się długo rzucasz się w kierunku ich obozu by zabezpieczyć fragment!"<<endl;
    walka(HP,W,ZB,60,15,15,"Zgraja Bandytów");
    cout<<"Udało ci się wybić każdego z rzezimieszków nie licząc ich herszta.Wchodzisz do jego namiotu.Ku twojemu zdziwieniu podaje ci fragment po czym zaczyna błagać byś darował mu życie.Obiecuje,że jeżeli puścisz go wolno to powie ci gdzie znaleźć ostatni fragment."<<endl;
    cout<<"-Dzięki ci,o Panie!Wiem że źle robiłem i przysięgam że przejdę ponownie na jasną ścieżkę!Ostatni fragment znajduje się głęboko w ruinach na zachodzie.-herszt zaznacza na mapie miejsce gdzie znajduje się ostatni fragment po czym ucieka biegiem z obozu.Wzdychasz tylko i także opuszczasz to miejsce."<<endl;
    portal_fragment+=1;
    map2[4][2]='!';
    event3=true;
    pauza();
    
}
void most()
{   cout<<"Wygląda na to że na moście rozgorzała bitwa pomiędzy Oddziałem Czadodzikich,a grupką straży granicznej.Twoja wewnętrzna duma nie pozwala ci przeczekać walki.Musisz wesprzeć swoich rodaków!"<<endl;
    pauza();
    cout<<"Wskakujesz na most.Tylna straż Czadodzikich zauważa cię dopiero po kilku chwilach.Skrzęcząc przygotowują się na twoje natarcie.";
    walka(HP,W,ZB,30,30,30,"Tylna Straż Czadodzikich");
    cout<<"Po pokonaniu tylnej straży przesz naprzód.Następni na twojej drodze są kusznicy.";
    walka(HP,W,ZB,20,20,20,"Kusznicy Czadodzikich");
    cout<<"Wygląda na to że straż graniczna zauważyła twoje poczynania i z okrzykiem rzucili się ochoczo na pogrążonych w chaosie nieprzyjaciół.Nagle jednak nienaturalnie wysoki i umięśniony Czadodziki z wielką maczugą zauważa cię i staje ci na drodze do reszty rycerzy.Musisz się przebić!"<<endl;
    walka(HP,W,ZB,25,25,25,"Zmutowany Czadodziki");
    cout<<"Wszyscy zaczynają wiwatować po wygranej walce.Potrząsasz kilka rąk po czym ruszasz dalej.Wcale nie jesteś wesoły - wygląda na to że oddziały Władców Smoggu dotarli aż tak głęboko w kraju"<<endl;
    
    x=75;
    y=3;
    map2[3][75]=playerName[0];
    map2[3][69]=' ';
    event4=true;
    pauza();
}
void random_fight(){
    
    int enc=arc4random()%3;
    cout<<enc;
    if(enc==0)
    {cout<<"Napotkałeś zwiad Czadodzikich!";
        walka(HP,W,ZB,12,12,12,"Zwiadowcy Czadodzikich");
        
    }
    if (enc==1)
    {cout<<"Zostałeś napadnięty przez bandytów!";
        walka(HP,W,ZB,14,14,14,"Bandyci");
        
    }
    if (enc==2)
    {cout<<"Zaatakowała cię grupka goblinów!";
        walka(HP,W,ZB,13,13,13,"Gobliny");
        
    }
    
}
void random_shop(){
    cena_hp=arc4random()%30+10;
    cena_w=arc4random()%30+10;
    cena_zb=arc4random()%30+10;
    cena_woda=arc4random()%30+10;
    cena_weapon4=arc4random()%30+25;
    cena_weapon5=arc4random()%30+25;
    cena_weapon6=arc4random()%30+25;
    int weapon_av4=arc4random()%2;
    int weapon_av5=arc4random()%2;
    int weapon_av6=arc4random()%2;
    cout<<"Napotkałeś obwoźnego handlarza różnościami!"<<endl;
    cout<<" - Co chciałbyś zakupić,przyjacielu? - pyta handlarz"<<endl;
    cout<<"0-Opuść sklep"<<endl;
    cout<<"1-Kup miksturę HP za "<<cena_hp<<endl;
    cout<<"2-Kup miksturę W za "<<cena_w<<endl;
    cout<<"3-Kup miksturę ZB za "<<cena_zb<<endl;
    cout<<"4-Kup butelkę wody za"<<cena_woda<<endl;
    if(weapon_av4==1)
    cout<<"5-Kup długi miecz (OBR 6-13)"<<cena_weapon4<<endl;
    if(weapon_av5==1)
    cout<<"6-Kup podwójne sztylety (OBR 9)"<<cena_weapon5<<endl;
    if(weapon_av6==1)
    cout<<"7-Kup morgensztern (OBR 1-25)"<<cena_weapon6<<endl;
    in_shop=1;
    while(in_shop==1)
    if(buy==0)
    {cout<<"Wyszedles ze sklepu"<<endl;
        in_shop=0;
    }
    if(buy==1)
    {hp_potion=+1;
        Wengle=Wengle-cena_hp;
        cout<<"Kupiono miksturę HP!";
    }
    if(buy==2)
    {w_potion=+1;
        Wengle=Wengle-cena_w;
        cout<<"Kupiono miksturę W!";
    }
    if(buy==3)
    {zb_potion=+1;
        Wengle=Wengle-cena_zb;
        cout<<"Kupiono miksturę ZB!";
    }
    if(buy==4)
    {woda=+1;
        Wengle=Wengle-cena_hp;
        cout<<"Kupiono butelke wody!";
    }
    if(buy==5)
    {hp_potion=+1;
        Wengle=Wengle-cena_weapon4;
        cout<<"Kupiono długi miecz!";
    }
    if(buy==6)
    {hp_potion=+1;
        Wengle=Wengle-cena_weapon5;
        cout<<"Kupiono podwójne sztylety!";
    }
    if(buy==7)
    {hp_potion=+1;
        Wengle=Wengle-cena_weapon6;
        cout<<"Kupiono morgensztern!";
    }
    
}
void random_food(){
    cout<<"Napotkałeś i upolowałeś dziką zwierzynę!";
    hunt=arc4random()%10+1;
    cout<<"Zdobyto"<<hunt<<" racji żywnościowych";
    food=food+hunt;
}
//
//Funckja główna,właściwa gra
int main()
{
for( int i = 0; i < 5; i++){
            
    skills[i]=0;
    }
    
    {
    wprowadzenie_past();
    wprowadzenie_present();
    kreator();
    trening();
    x=0;
    y=2;
    game_map1=true;
        while(game_map1==true)
        {   for(int i=0;i<20;i++)
            {cout<<endl;}
        for(int i = 0;i<5;i++)
    {
        cout<<map1[i]<<endl;
        
    }   if(x==10 && y==2)
    {
        game_map1=false;
    } else if(x==5 && y==2 && event0==false)
    {event_0();}
        else
        Input();
    
    }
        ucieczka();
        map2[2][10]=' ';
        map2[2][0]=playerName[0];
        x=0;
        y=2;
        
        game_map2=true;
            while(game_map2==true)
            {   random_event=arc4random()%101;
            for(int i=0;i<20;i++)
            {cout<<endl;}
            for(int i = 0;i<9;i++)
        {
            cout<<map2[i]<<endl;
            
        }
            if(x==103 && y==7)
        {
            game_map2=false;
            koniec();
            money_end=Wengle;
            
            return 0;
        }
            if(x==37 && y==7 && portal_fragment<3)
            {cout<<"Portal jest zamknięty"<<endl;
                Input();
            }
            if(x==37 && y==7)
            {portal();
                for(int i = 0;i<9;i++)
            {
                cout<<map2[i]<<endl;
                
            }
            }
            if(x==22 && y==2 && event1==false)
            {event_1();
                for(int i = 0;i<9;i++)
            {
                cout<<map2[i]<<endl;
                
            }
            }
            if(x==2 && y==4 && event2==false)
            {event_2();
                for(int i = 0;i<9;i++)
            {
                cout<<map2[i]<<endl;
                
            }
            }
            if(x==37 && y==6 && event3==false)
            {bandyci();
                for(int i = 0;i<9;i++)
            {
                cout<<map2[i]<<endl;
                
            }
            }
            if(x==69 && y==3 && event4==false)
            {most();
                for(int i = 0;i<9;i++)
            {
                cout<<map2[i]<<endl;
                
            }
            }
            if(random_event>0 && random_event<=3)
            {random_fight();
                random_event=0;
                for(int i = 0;i<9;i++)
            {
                cout<<map2[i]<<endl;
                
            }
            }
            if(random_event>3 && random_event<=6)
            {random_shop();
                random_event=0;
                
            }
            if(random_event>6 && random_event<=9)
            {random_food();
                random_event=0;
                
                
            }
            if(random_event>9 && random_event<=100)
            {cout<<"Póki co podróż przebiega spokojnie"<<endl;}
                Input();
        
            }
    }}
