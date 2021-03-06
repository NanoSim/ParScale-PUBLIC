/*------------------------------------------------------------------------------------*\

                                      /$$$$$$                      /$$          
                                     /$$__  $$                    | $$          
        /$$$$$$   /$$$$$$   /$$$$$$ | $$  \__/  /$$$$$$$  /$$$$$$ | $$  /$$$$$$ 
       /$$__  $$ |____  $$ /$$__  $$|  $$$$$$  /$$_____/ |____  $$| $$ /$$__  $$
      | $$  \ $$  /$$$$$$$| $$  \__/ \____  $$| $$        /$$$$$$$| $$| $$$$$$$$
      | $$  | $$ /$$__  $$| $$       /$$  \ $$| $$       /$$__  $$| $$| $$_____/
      | $$$$$$$/|  $$$$$$$| $$      |  $$$$$$/|  $$$$$$$|  $$$$$$$| $$|  $$$$$$$
      | $$____/  \_______/|__/       \______/  \_______/ \_______/|__/ \_______/
      | $$                                                                      
      | $$                                                                      
      |__/        A Compilation of Particle Scale Models

     Copyright (C): 2012 - 2014 DCS Computing GmbH (www.dcs-computing.com), Linz, Austria
                    2012 - 2014 Department of Particulate Flow Modelling, JKU Linz
                              (www.jku.at/pfm), Linz, Austria

   This file was originally part of LIGGGHTS (www.cfdem.com), and is now re-distributed
   under LGPL as part of ParScale with the permission of the copyright holders
---------------------------------------------------------------------------------------
License
    ParScale is licensed under the GNU LESSER GENERAL PUBLIC LICENSE (LGPL).

    Everyone is permitted to copy and distribute verbatim copies of this license
    document, but changing it is not allowed.

    This version of the GNU Lesser General Public License incorporates the terms
    and conditions of version 3 of the GNU General Public License, supplemented
    by the additional permissions listed below.

    You should have received a copy of the GNU Lesser General Public License
    along with ParScale. If not, see <http://www.gnu.org/licenses/lgpl.html>.

	This code is designed to simulate transport processes (e.g., for heat and
	mass) within porous and no-porous particles, eventually undergoing
	chemical reactions.

	Parts of the code were developed in the frame of the NanoSim project funded
	by the European Commission through FP7 Grant agreement no. 604656.
\*-----------------------------------------------------------------------------------*/

#ifndef PSC_MEMORY_NS_H
#define PSC_MEMORY_NS_H

#include "stdlib.h"
#include "psctype.h"

using namespace PASCAL_NS;

namespace PASCAL_MEMORY_NS {

/* ----------------------------------------------------------------------
   create a 1d array
------------------------------------------------------------------------- */

  template <typename TYPE>
    TYPE *create(TYPE *&array, int n)
    {
      bigint nbytes = ((bigint) sizeof(TYPE)) * n;
      array = (TYPE *) malloc(nbytes);
      return array;
    }


/* ----------------------------------------------------------------------
   grow or shrink 1d array
------------------------------------------------------------------------- */

  template <typename TYPE>
    TYPE *grow(TYPE *&array, int n)
    {
      if (array == NULL) return create(array,n);

      bigint nbytes = ((bigint) sizeof(TYPE)) * n;
      array = (TYPE *) realloc(array,nbytes);
      return array;
    }


/* ----------------------------------------------------------------------
   destroy a 1d array
------------------------------------------------------------------------- */

  template <typename TYPE>
    void destroy(TYPE *array)
    {
      free(array);
    }

  /* ----------------------------------------------------------------------
     create a 2d array
  ------------------------------------------------------------------------- */

    template <typename TYPE>
      TYPE **create(TYPE **&array, int n1, int n2)
      {
        bigint nbytes = ((bigint) sizeof(TYPE)) * n1*n2;
        TYPE *data = (TYPE *) malloc(nbytes);
        nbytes = ((bigint) sizeof(TYPE *)) * n1;
        array = (TYPE **) malloc(nbytes);

        bigint n = 0;
        for (int i = 0; i < n1; i++) {
          array[i] = &data[n];
          n += n2;
        }
        return array;
      }

  /* ----------------------------------------------------------------------
     grow or shrink 1st dim of a 2d array
     last dim must stay the same
  ------------------------------------------------------------------------- */

    template <typename TYPE>
      TYPE **grow(TYPE **&array, int n1, int n2)
      {
        if (array == NULL) return create(array,n1,n2);

        bigint nbytes = ((bigint) sizeof(TYPE)) * n1*n2;
        TYPE *data = (TYPE *) realloc(array[0],nbytes);
        nbytes = ((bigint) sizeof(TYPE *)) * n1;
        array = (TYPE **) realloc(array,nbytes);

        bigint n = 0;
        for (int i = 0; i < n1; i++) {
          array[i] = &data[n];
          n += n2;
        }
        return array;
      }

  /* ----------------------------------------------------------------------
     destroy a 2d array
  ------------------------------------------------------------------------- */

    template <typename TYPE>
      void destroy(TYPE **array)
      {
        if (array == NULL) return;
        free(array[0]);
        free(array);
      }

    /* ----------------------------------------------------------------------
       create a 3d array
    ------------------------------------------------------------------------- */

      template <typename TYPE>
        TYPE ***create(TYPE ***&array, int n1, int n2, int n3)
        {
          bigint nbytes = ((bigint) sizeof(TYPE)) * n1*n2*n3;
          TYPE *data = (TYPE *) malloc(nbytes);
          nbytes = ((bigint) sizeof(TYPE *)) * n1*n2;
          TYPE **plane = (TYPE **) malloc(nbytes);
          nbytes = ((bigint) sizeof(TYPE **)) * n1;
          array = (TYPE ***) malloc(nbytes);

          int i,j;
          bigint m;
          bigint n = 0;
          for (i = 0; i < n1; i++) {
            m = ((bigint) i) * n2;
            array[i] = &plane[m];
            for (j = 0; j < n2; j++) {
              plane[m+j] = &data[n];
              n += n3;
            }
          }
          return array;
        }

    /* ----------------------------------------------------------------------
       grow or shrink 1st dim of a 3d array
       last 2 dims must stay the same
    ------------------------------------------------------------------------- */

      template <typename TYPE>
        TYPE ***grow(TYPE ***&array, int n1, int n2, int n3)
        {
          if (array == NULL) return create(array,n1,n2,n3);

          bigint nbytes = ((bigint) sizeof(TYPE)) * n1*n2*n3;
          TYPE *data = (TYPE *) realloc(array[0][0],nbytes);
          nbytes = ((bigint) sizeof(TYPE *)) * n1*n2;
          TYPE **plane = (TYPE **) realloc(array[0],nbytes);
          nbytes = ((bigint) sizeof(TYPE **)) * n1;
          array = (TYPE ***) realloc(array,nbytes);

          int i,j;
          bigint m;
          bigint n = 0;
          for (i = 0; i < n1; i++) {
            m = ((bigint) i) * n2;
            array[i] = &plane[m];
            for (j = 0; j < n2; j++) {
              plane[m+j] = &data[n];
              n += n3;
            }
          }
          return array;
        }

    /* ----------------------------------------------------------------------
       destroy a 3d array
    ------------------------------------------------------------------------- */

      template <typename TYPE>
        void destroy(TYPE ***array)
        {
          if (array == NULL) return;
          free(array[0][0]);
          free(array[0]);
          free(array);
        }
}

#endif
