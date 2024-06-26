#ifndef ADDON_H
#define ADDON_H
#include "number.h"
#endif // ADDON_H

template <class number>
number det_mat(number** M, int n)
{
    if(n==1)
    {
        return M[0][0];
    }
    if(n==2)
    {
        number s = (M[0][0]*M[1][1])-(M[1][0]*M[0][1]);
        return s;
    }
    else
    {
        number res = 0;
        bool bo = false;
        bool ob = false;

        number **A = new number*[n];
        for(int i=0;i<n;i++) A[i] = new number[n];

        for(int i=0;i<n;i++)for(int j=0;j<n;j++)A[i][j]=M[i][j];

        number **B = new number*[n-1];
        for(int i=0;i<(n-1);i++) B[i] = new number[n-1];

        for(int d=0;d<n;d++)
        {
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<n;k++)
                {
                    if(k!=d)
                    {
                        if(j!=0)
                        {
                            if(!bo) B[j-1][k] = A[j][k]; else B[j-1][k-1] = A[j][k];
                        }
                    }
                    else bo = true;
                }
                bo = false;
            }


            if(((d+2)%2)==0) res = res + A[0][d]*det_mat(B,n-1); else res = res - A[0][d]*det_mat(B,n-1);

        }

        delete[] A;
        delete[] B;

        return res;

    }

}
