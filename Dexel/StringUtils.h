#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>

using namespace std;

/**
 * \brief Funkcja usuwająca symbole nowej linii.
 *
 * Funkcja usuwająca symbole nowej linii, wykorzystywana przy wczytywaniu poleceń wieloliniowych.
 *
 * \param str - Tekst, z którego mają być usunięte symbole nowej linii.
 * \return Tekst z usuniętymi symbolami nowej linii.
 */
extern string removeNewlines(const string& str);

#endif
