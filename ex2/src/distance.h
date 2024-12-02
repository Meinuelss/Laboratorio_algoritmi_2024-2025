#ifndef DISTANCE_H 
#define DISTANCE_H
/**
 * @brief A helper function that computes the edit distance between two strings
 *        using recursive approach.
 * 
 * This function calculates the minimum number of insertions or deletions 
 * required to transform one substring into another, using recursion.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The computed edit distance for the given substrings.
 */
int edit_distance_rec(const char *s1, const char *s2);

/**
 * @brief Computes the edit distance between two strings using a recursive approach.
 * 
 * The edit distance is defined as the minimum number of insertions or deletions 
 * required to transform one string into another.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The computed edit distance.
 */
int edit_distance(const char *s1, const char *s2);

/**
 * @brief A helper function that computes the edit distance between two strings
 *        using dynamic programming (recursive version).
 * 
 * This function computes the minimum number of insertions or deletions required 
 * to transform one substring into another, storing results in a table.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @param i The current index in string s1.
 * @param j The current index in string s2.
 * @param tab The table storing intermediate results.
 * @return The computed edit distance for the given substrings.
 */
int edit_distance_dyn_rec(const char *s1, const char *s2, int i, int j, int **tab);

/**
 * @brief Computes the edit distance between two strings using dynamic programming.
 * 
 * This function uses a table to optimize the computation by avoiding 
 * redundant calculations of subproblems. It supports strings of any length.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The computed edit distance.
 */
int edit_distance_dyn(const char *s1, const char *s2);
#endif /* EX2_H */

