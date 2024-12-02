#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "distance.h"

int edit_distance_rec(const char *s1, const char *s2)
{
	if(*s1 == '\0')
	{
		return strlen(s2);
	}
	if(*s2 == '\0')
	{
		return strlen(s1);
	}
	if(*s1 == *s2)
	{
		return edit_distance_rec(s1+1, s2+1);
	}
	return 1 + (int)fmin(edit_distance_rec(s1, s2+1),edit_distance_rec(s1+1, s2));
}


int edit_distance(const char *s1, const char *s2)
{
    if(s1==NULL && s2==NULL)
    {
        return 0;
    }
	if(s1==NULL)
	{
		return strlen(s2);
	}
	if(s2==NULL)
	{
		return strlen(s1);
	}
	return edit_distance_rec(s1,s2);
}

int edit_distance_dyn_rec(const char *s1, const char *s2, int i, int j, int **tab) 
{
    if (i == 0) 
    {
    	return j;
    } 
    if (j == 0)
    {
        return i;
    } 

    if (tab[i][j] != -1) {
        return tab[i][j];
    }

    if (s1[i - 1] == s2[j - 1]) 
    {
        tab[i][j] = edit_distance_dyn_rec(s1, s2, i - 1, j - 1, tab);
    } 
    else {
        tab[i][j] = 1 + fmin(edit_distance_dyn_rec(s1, s2, i, j - 1, tab),edit_distance_dyn_rec(s1, s2, i - 1, j, tab));
    }

    return tab[i][j];
}

int edit_distance_dyn(const char *s1, const char *s2) 
{
    if(s1==NULL && s2==NULL)
    {
        return 0;
    }
    if (s1 == NULL)
    {
        return strlen(s2); 
    }
    if (s2 == NULL)
    {
        return strlen(s1); 
    }
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    int **tab = (int **)malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) 
    {
        tab[i] = (int *)malloc((len2 + 1) * sizeof(int));
        for (int j = 0; j <= len2; j++) 
        {
            tab[i][j] = -1;
        }
    }

    int res = edit_distance_dyn_rec(s1, s2, len1, len2, tab);

    for (int i = 0; i <= len1; i++) 
    {
        free(tab[i]);
    }
    free(tab);

    return res;
}
