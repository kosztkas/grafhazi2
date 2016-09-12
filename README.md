# Számítógépes grafika
2014/2015/2 félév

##1. házi feladat
Készítsen „**Síkon táncoló kontrollpontok**” programot. A felhasználó az egér balgomb egyszeri lenyomással/elengedéssel veszi fel a kontrollpontokat (max 10-et), amelyekhez 2cm sugarú kisebb fekete köröket rendelünk. Ha a kontrollpontok száma legalább kettő, azokra egy türkiszkék színű, kitöltött konvex burkot, piros Bézier görbét, nulla kezdő és végsebességű, a kontrollpont lehelyezésének idejét paraméterként használó zöld Catmull-Rom spline-t és kék Catmull-Clark görbét illeszt.
A háttér világosszürke. Legnagyobb prioritása a kontrollpontoknak van, majd a görbék jönnek, végül jön a konvex burok.
Space lenyomására a kontrollpontok egy-egy 5 cm-es kör tetejéről elindulva, 5 másodpercenként egy teljes fordulatot téve, elkezdenek keringeni, mégpedig a páros indexűek az óramutató járásával megegyező, a páratlan indexűek pedig azzal ellentétes irányban. A konvex burok és a görbék követik a kontrollpontokat. Mindezt a felhasználó egy 58cm x 68 cm-es kameraablakon keresztül látja. Ha a felhasználó az egér jobb gombbal rábök egy kontrollpontra, akkor a kameraablakot ehhez köti, a kontrollpont elmozdulása automatikusan a kameraablakot is arrébb viszi.

### Screen
![](https://raw.githubusercontent.com/kosztkas/grafika/master/g_elso.png)

## 2. házi feladat
Készítsen sugárkövető programot, amely 100 mm oldalhosszúságú, egyik oldalán nyitott dobozban lévő durván tesszellált, optikailag sima, tükröző arany tóruszt, és egy Schwarzschild típusú (azaz töltés nélküli és nem forgó) Föld tömegű fekete lyukat tartalmaz. A doboz oldalai diffúz+spekuláris visszaverődésűek, a diffúz tag procedúrálisan textúrázott. A színteret ambiensfény és legalább egy pontfényforrás világítja meg. Élhet azzal az egyszerűsítéssel, hogy a fekete lyuk a fényt csak az első visszaverődés után görbíti, azaz a pont fényforrás és a megvilágított felület között nem, de a rücskös és sima felületek között, valamint a felületek és a szem között igen (a másik alternatíva a fényforrásból kilépő fény görbítésére a fotontérkép módszer). A fény elgörbülését kellő tudásszomj esetén Einstein téregyenletének Schwarzschildtól származó megoldásával, egyébként pedig az ekvivalenciaelv és a klasszikus newtoni gravitációs formula felhasználásával, sugármasírozással kell szimulálni. A rendelkezésre álló CPU idő 120 sec, szükség esetén kisebb bontású kép átmintavételezésével, távolságtól függő lépés-nagysággal és befoglaló térfogatokkal lehet a programot gyorsítani.

A szükséges fizikai állandók: A fény sebessége: 300 000 km/sec; A föld kerülete: 40 000 km; A nehézségi gyorsulás a föld felszínén: 10 m/sec^2.

Az arany törésmutatója és kioltási tényezője: r: 0.17/3.1, g: 0.35/2.7, b: 1.5/1.9 A falak diffúz és spekuláris visszaverődési tényezője és shininess paramétere, valamint a textúra szabadon megválasztható.

### Screen
![](https://raw.githubusercontent.com/kosztkas/grafika/master/g_masodik.png)


Nem tökéletes megoldások, de a tárgy teljesítéséhez elegendők voltak.
