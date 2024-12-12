# testare_proiect_asc

ATENTIE! Inainte de a va testa codul, asigurati-va ca dati flush dupa fiecare printf.

Mi-e destul de greu sa generez teste daca nu am restrictii / precizari clare la problema :(

Daca da OK pe toate testele, asta inseamna ca cel mai probabil codul tau e corect. (Am incercat sa fac testele sa fie cat mai bune)

# Problema unidimensionala

- Descarca folder-ul teste_full.
- Salvezi continutul folder-ului instalat in folder-ul in care ai proiectul.
- Executi urmatoarea comanda:
```
sudo chmod +x test_asm.sh
```
- Dupa, executi urmatoarea comanda:
```
./test_asm.sh {numele_proiectului_vostru}.s
```
- Sau executi urmatoarea comanda (daca vrei sa testezi doar un anumit test):
```
./test_asm.sh {numele_proiectului_vostru}.s {nr_test}
```
- Apoi, vei primi verdictul pentru fiecare test (OK sau WRONG_ANSWER). Daca da OK pe toate testele, inseamna ca solutia ta va lua (cel mai probabil) punctaj maxim la evaluarea finala.
- Toate testele contin toate tipurile de operatii (ADD, GET, DELETE, DEFRAGMENTATION)
- Testul 6 reprezinta exemplul din enunt.

# Problema bidimensionala

- Descarca folder-ul teste_2d.
- Salvezi continutul folder-ului instalat in folder-ul in care ai proiectul.
- Executi urmatoarea comanda:
```
sudo chmod +x test_asm.sh
```
- Dupa, executi urmatoarea comanda (daca vrei sa testezi toate testele):
```
./test_asm.sh {numele_proiectului_vostru}.s
```
- Sau executi urmatoarea comanda (daca vrei sa testezi doar un anumit test):
```
./test_asm.sh {numele_proiectului_vostru}.s {nr_test}
```
- Apoi, vei primi verdictul pentru fiecare test (OK sau WRONG_ANSWER). Daca da OK pe toate testele, inseamna ca ai scris corect operatiile ADD, GET, DELETE, DEFRAGMENTATION si CONCRETE si vei obtine (cel mai probabil) punctaj maxim la evaluarea finala.
- Testele 1-3 contin toate tipurile de operatii (ADD, GET, DELETE, DEFRAGMENTATION). Testele 4-5 contin doar 3 tipuri de operatii (ADD, GET, DELETE). Testul 6 contine doar operatia ADD. Testul 7 se compune intr-o maniera dinamica (pentru mai multe informatii, uita-te pe discord) si contine toate operatiile: ADD, GET, DELETE, DEFRAGMENTATION si CONCRETE.
