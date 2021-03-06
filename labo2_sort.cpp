/*********************************/
/*  Gruppo 11                    */
/*                               */
/*  Klodiana Breza   (S4712271)  */
/*  Andrea Celotto   (S4676081)  */
/*  Giovanni Minotti (S4396239)  */
/*********************************/

#include "labo2_sort.h"


void scambia(vector<int>& v, int i, int j)
{
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}


/**************************************************************************************
				SELECTION SORT
***************************************************************************************/
void selectionSort(vector<int>& v)
{
   int current_min_index;
   unsigned int size = v.size();
   for (unsigned int i=0; i<size; ++i)
   {
     current_min_index = i;
     for (unsigned int j=i+1;j<size; ++j)
        if (v[current_min_index] > v[j])
            current_min_index = j;
     scambia(v, i, current_min_index);
   }
}



/**************************************************************************************
				INSERTION SORT
***************************************************************************************/
void insertionSort(vector<int>& v)
{
   int current, prev;
   unsigned int size = v.size();
   for (unsigned int i=1; i<size; ++i)
   { current=i;
     prev=i-1;
     while(prev>=0 && v[current]<v[prev])
        {
         scambia(v, current, prev);
         --current;
         --prev;
        }
   }
}


/**************************************************************************************
				BUBBLESORT
***************************************************************************************/
void bubbleSort(vector<int>& v)
{
   unsigned int size = v.size();
   bool scambiati;
   for (unsigned int i=1; i<size; ++i)
      {
      scambiati = false;
      for (unsigned int j=0; j<size-i; ++j)
          if(v[j]>v[j+1])
            {
              scambia(v, j, j+1);
              scambiati = true;
            }
      if (!scambiati) return;
      }
}



/**************************************************************************************
				   MERGESORT
***************************************************************************************/
void fondi(vector<int>& v, unsigned int inizio, unsigned int centro, unsigned int fine)
{
   vector<int> vsinistra, vdestra;

   for (unsigned int i=inizio; i<=centro; ++i)
      vsinistra.push_back(v[i]);

   for (unsigned int i=centro+1; i<=fine; ++i)
      vdestra.push_back(v[i]);

   unsigned int indicesinistra = 0;
   unsigned int maxsin = vsinistra.size();
   unsigned int indicedestra = 0;
   unsigned int maxdes = vdestra.size();

   for (unsigned int i=inizio; i<=fine; ++i)
   {
      if (indicesinistra < maxsin && indicedestra < maxdes)
         {
         if (vsinistra[indicesinistra]<vdestra[indicedestra])
            {
             v[i] = vsinistra[indicesinistra];
             indicesinistra++; continue;
             }
         else
            {
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
            }
         }

      if (indicesinistra == maxsin && indicedestra < maxdes)
         {
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
         }

       if (indicedestra == maxdes && indicesinistra < maxsin)
         {
            v[i] = vsinistra[indicesinistra];
            indicesinistra++; continue;
         }
   }
}

void ms(vector<int>& v, unsigned int inizio, unsigned int fine)
{
    if (inizio < fine)
      {
          unsigned int centro = (inizio+fine)/2;
          ms(v, inizio, centro);
          ms(v, centro+1, fine);
          fondi(v, inizio, centro, fine);
      }
}


void mergeSort(vector<int>& v)
{
   if (v.size() != 0)
      ms(v, 0, v.size()-1);
}

/*******************************************************/


int part (vector<int>& v, int l, int r) {
    int pivot = v[l]; // Il mio pivot e' il primo elemento dell'intervallo

    int i = l+1; // Parto a scrivere gli elementi dalla seconda posizione dell'intervallo
    for (int j=i; j<=r; j++) // Parto a interare dalla seconda posizione dell'intervallo
        if (v[j] <= pivot) // Se l'elemento e' minore del pivot
            scambia(v, i++, j); // Posizione l'elemeno nella parte iniziale dell'intervallo (e incremento il contatore i che identifica la futura posizione del pivot)

    scambia(v, i-1, l); // Metto il pivot nella posizione giusta (suggerita dal contatore i)

    return i-1; // Restituisco la posizione del pivot
}

int partRandom (vector<int>& v, int l, int r) {
    int random = (rand() % (r-l)) + l; // Ottengo un numero casuale da l a r
    scambia(v, random, l); // Sposto il pivot scelto al primo posto per poter utilizzare il codice di part
    return part(v, l, r); // Chiamo part con il pivot spostato
}

void quickSort (vector<int>& v, int l, int r, bool randPivot) {
    if (l >= r) // Se non posso piu' partizionare l'array
        return; // Termino

    int pivot_index = randPivot ? partRandom(v, l, r) : part(v, l, r); // Partiziono su indice causale se indicati, altrimenti sul primo

    quickSort(v, l, pivot_index-1, randPivot); // Chiamo il quickSort sulla prima parte (minore del pivot)
    quickSort(v, pivot_index+1, r, randPivot); // Chiamo il quickSort sulla seconda parte (maggiore del pivot)
}


/**************************************************************************************
				QUICKSORT CON SCELTA "BANALE" DEL PIVOT
***************************************************************************************/

void quickSortTrivial(vector<int>& v) {
    quickSort(v, 0, v.size()-1, false);
}


/**************************************************************************************
				QUICKSORT RANDOMIZZATO
***************************************************************************************/

void quickSortRandom(vector<int>& v)
{
   srand(time(NULL));

   quickSort(v, 0, v.size()-1, true);
}
