# Számítógépes grafika
2014/2015/2 félév

## 1. házi feladat
Készítsen elől-felül-oldalnézetes ortografikus 3D Renner spline görbeszerkesztőt, amelyben a pálya menti sebesség közelítőleg 1 m/sec. A 600x600 pixel felbontású alkalmazói ablak négy egyenlő részre van osztva, amelyekben az elől, felül és oldalnézetek látható, egy negyed pedig üres. A világ 3m x 3m x 3m-res kocka, amelynek középpontjában vettük fel az origót. A nézetekben a teljes világ vetületei látszanak, az origó értelemszerűen középen van. A transzformációkat „kézzel” kell számítani, az OpenGL mátrixok most még nem alkalmazhatók.

Amíg még nincs görbénk, az egyik nézetbeli egérkattintások kontrolpontokat vesznek fel, úgy, hogy a nézetre merőleges koordináta zérus. A további nézetekbe kattintva az ott legközelebbinek talált kontrollpont áthelyezhető, a nézetre merőleges koordináta változatlanul hagyásával. A pillanatnyi állapotot minden nézetben jelezni kell, a kontrolpontokat sárga körökkel, a 3D Renner spline-t pedig a fehéren rajzolt 2D merőleges vetületeivel.

A SPACE lenyomására egy kör indul el a görbe kezdőpontjából és a sebességvektorát farokként maga után húzva, kb. 1 m/sec pályamenti sebességgel végigcsúszik a görbén.

### Screen
![](https://raw.githubusercontent.com/kosztkas/grafika/master/g_elso.png)

## 2. házi feladat
Készítsen sugárkövető programot, amely 100 mm oldalhosszúságú, egyik oldalán nyitott dobozban lévő durván tesszellált, optikailag sima, tükröző arany tóruszt, és egy Schwarzschild típusú (azaz töltés nélküli és nem forgó) Föld tömegű fekete lyukat tartalmaz. A doboz oldalai diffúz+spekuláris visszaverődésűek, a diffúz tag procedúrálisan textúrázott. A színteret ambiensfény és legalább egy pontfényforrás világítja meg. Élhet azzal az egyszerűsítéssel, hogy a fekete lyuk a fényt csak az első visszaverődés után görbíti, azaz a pont fényforrás és a megvilágított felület között nem, de a rücskös és sima felületek között, valamint a felületek és a szem között igen (a másik alternatíva a fényforrásból kilépő fény görbítésére a fotontérkép módszer). A fény elgörbülését kellő tudásszomj esetén Einstein téregyenletének Schwarzschildtól származó megoldásával, egyébként pedig az ekvivalenciaelv és a klasszikus newtoni gravitációs formula felhasználásával, sugármasírozással kell szimulálni. A rendelkezésre álló CPU idő 120 sec, szükség esetén kisebb bontású kép átmintavételezésével, távolságtól függő lépés-nagysággal és befoglaló térfogatokkal lehet a programot gyorsítani.

A szükséges fizikai állandók: A fény sebessége: 300 000 km/sec; A föld kerülete: 40 000 km; A nehézségi gyorsulás a föld felszínén: 10 m/sec^2.

Az arany törésmutatója és kioltási tényezője: r: 0.17/3.1, g: 0.35/2.7, b: 1.5/1.9 A falak diffúz és spekuláris visszaverődési tényezője és shininess paramétere, valamint a textúra szabadon megválasztható.

### Screen
![](https://raw.githubusercontent.com/kosztkas/grafika/master/g_masodik.png)


Nem tökéletes megoldások, de a tárgy teljesítéséhez elegendők voltak.
