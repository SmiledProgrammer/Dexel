#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

using namespace std;

/**
 * \brief Funkcja wczytująca zawartość pliku.
 *
 * Funkcja wczytująca zawartość pliku do zmiennej tekstowej.
 *
 * \param absolutePath - Ścieżka do pliku.
 * \return Tekst stanowiący zawartość pliku.
 */
extern string readFileToString(const string& absolutePath);

#endif
